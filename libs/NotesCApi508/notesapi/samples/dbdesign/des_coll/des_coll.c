/****************************************************************************

    PROGRAM:    des_coll

    FILE:       des_coll.c

    SYNTAX:     des_coll  <database path>

    PURPOSE:    Shows how to read the design collection for a database.
		Prints the type and title of each design note found.

    DESCRIPTION:
	Every database contains a design collection. The design collection
	is like a view collection that contains entries corresponding to 
	every form, view, and macro in the database. To read the design 
	collection, call to NIFOpenCollection specifying ViewNoteID = 
	NOTE_ID_SPECIAL+NOTE_CLASS_DESIGN. This program reads through the 
	design collection and, for each design note, prints the note class 
	(Form, View, etc.) and the title.
									 
*************************************************************************/

/* OS and C include files */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <osmem.h>
#include <stdnames.h>
#include <names.h>
#include <misc.h>
#include <idtable.h>
#include <nsfdata.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsferr.h>
#include <nif.h>
#include <ods.h>
#include <textlist.h>

#include <lapiplat.h>

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], char *db_filename);

void LNPUBLIC PrintTitle (DWORD dwItem, WORD wClass, BYTE *summary);

#define  STRING_LENGTH  256

/************************************************************************

    FUNCTION:   NotesMain

*************************************************************************/

LAPI_MAIN
{
  STATUS      error=0;
  char       *szPathName;
  DBHANDLE    hDB;
  char        szDBInfo[NSF_INFO_SIZE];
  char        szDBTitle[NSF_INFO_SIZE];
  HCOLLECTION hCollection;
  COLLECTIONPOSITION CollPosition;
  HANDLE      hBuffer;
  BYTE       *pBuffer;
  BYTE       *pSummary;
  DWORD       dwEntriesFound, i;
  ITEM_TABLE  ItemTable;
  WORD        wClass;


  LAPI_INIT(error);
  if (error)
    LAPI_INIT_ERROR;


  /* Allocate memory for an input database path */
  szPathName = (char *) malloc(STRING_LENGTH);
  if (szPathName == NULL)
  {
    printf("Error: Out of memory.\n");
    LAPI_RETURN (NOERROR);
  }

  /* Get the pathname of the database. */
  ProcessArgs(argc, argv, szPathName);

  /* Open the database */
  if (error = NSFDbOpen (szPathName, &hDB))
  {
    printf ("Error: unable to open database '%s'.\n", szPathName);
    free(szPathName);
    LAPI_RETURN (ERR(error));
  }

  if (error = NSFDbInfoGet (hDB, szDBInfo))
  {
    printf("Error: unable to get title of database '%s'\n.", szPathName);
    NSFDbClose (hDB);
    free(szPathName);
    LAPI_RETURN (ERR(error));
  }

  NSFDbInfoParse (szDBInfo, INFOPARSE_TITLE, szDBTitle, NSF_INFO_SIZE-1);
 
  printf("Printing design collection for '%s'\n", szDBTitle);

  /* Open the special "design" collection, which contains an index of
     all nondata notes. */

  if (error = NIFOpenCollection(hDB, 
			    hDB, 
			    NOTE_ID_SPECIAL+NOTE_CLASS_DESIGN,
			    OPEN_DO_NOT_CREATE,
			    NULLHANDLE,
			    &hCollection,
			    NULL, NULL, NULL, NULL))
  {    /* Collection may not have been setup yet by the first user to 
	  open the file.*/
    printf("Unable to open the design collection for '%s'.\n", szDBTitle);
    NSFDbClose (hDB);
    free(szPathName);
    LAPI_RETURN(ERR(error));
  }

  CollPosition.Level = 0;
  CollPosition.Tumbler[0] = 1;

  if (error = NIFReadEntries(
	     hCollection,           /* handle to this collection */
	     &CollPosition,         /* where to start in collection */
	     NAVIGATE_CURRENT,      /* order to use when skipping */
	     0L,                    /* number to skip */
	     NAVIGATE_NEXT,         /* order to use when reading */
	     0xFFFFFFFF,            /* max number to read */
	     READ_MASK_NOTECLASS +  /* read the note class */
	     READ_MASK_SUMMARY,     /* and the summary buffer */
	     &hBuffer,              /* handle to info buffer (return)  */
	     NULL,                  /* length of info buffer (return) */
	     NULL,                  /* entries skipped (return) */
	     &dwEntriesFound,       /* entries read (return) */
	     NULL))
  {
    printf("No entries found in design collection for '%s'.\n", szDBTitle);
    NIFCloseCollection (hCollection);
    NSFDbClose (hDB);
    free(szPathName);
    LAPI_RETURN (ERR(error));
  }

  /* Check to make sure there was a buffer of information returned. */ 

  if (hBuffer == NULLHANDLE)
  {
    printf ("Empty buffer returned reading entries in design collection.\n");
    NIFCloseCollection (hCollection);
    NSFDbClose (hDB);
    free(szPathName);
    LAPI_RETURN (NOERROR);
  }

  pBuffer = (BYTE *) OSLockObject (hBuffer);

  printf ("Found %ld design notes in '%s'.\n",dwEntriesFound, szDBTitle);
  for (i = 0; i < dwEntriesFound; i++)
  {
    wClass = *(WORD*) pBuffer;
    pBuffer += sizeof (WORD);

    ItemTable = *(ITEM_TABLE*) pBuffer;

    /* Remember where the start of this entry's summary is. Then advance
    the main pointer over the summary. */
    pSummary = pBuffer;
    pBuffer += ItemTable.Length; 
 
    /* Call PrintTitle to print the type and title of the design note. */
    PrintTitle (i, wClass, pSummary);

  } /* End of loop that processes each entry. */

  /* Unlock the buffer returned from NIFReadEntries. */
  OSUnlockObject (hBuffer);

  /* Free the memory allocated by NIFReadEntries. */
  OSMemFree (hBuffer);

  error = NIFCloseCollection(hCollection);
  NSFDbClose(hDB);
  free(szPathName);
  LAPI_RETURN (ERR(error));
}

/************************************************************************

    FUNCTION:   PrintTitle

    PURPOSE:    print title and type of a design note

    DESCRIPTION:
	Prints the type of the design note (e.g. "Form") based on the
	Class (e.g. NOTE_CLASS_FORM). Then it gets the title of the
	form or view from the summary buffer and prints it.

*************************************************************************/

void LNPUBLIC PrintTitle (DWORD dwItem, WORD wClass, BYTE *summary)
{
  char       *szNoteType; /* e.g. "Form" */
  char       *pItemValue; /* initialized by NSFLocateSummaryValue */
  WORD        Length, Type;
  char        szTitleString[DESIGN_NAME_MAX];
	
  if (wClass & NOTE_CLASS_INFO)
    szNoteType = "help-about";
  else if (wClass & NOTE_CLASS_FORM)
    szNoteType = "Form";
  else if (wClass & NOTE_CLASS_VIEW)
    szNoteType = "View";
  else if (wClass & NOTE_CLASS_ICON)
    szNoteType = "Icon";
  else if (wClass & NOTE_CLASS_DESIGN)
    szNoteType = "design collection";
  else if (wClass & NOTE_CLASS_ACL)
    szNoteType = "A.C.L.";
  else if (wClass & NOTE_CLASS_HELP_INDEX)
    szNoteType = "Notes Help";
  else if (wClass & NOTE_CLASS_HELP)
    szNoteType = "Database Help";
  else if (wClass & NOTE_CLASS_FILTER)
    szNoteType  = "Macro";
  else if (wClass & NOTE_CLASS_FIELD)
    szNoteType  = "Field";          /* Notes 3.0 shared field */
  else if (wClass & NOTE_CLASS_REPLFORMULA)
    szNoteType  = "replication formula";
  else 
    szNoteType = "unknown";

  if (NSFLocateSummaryValue(summary, 
		    ITEM_NAME_TEMPLATE_NAME, /* "$TITLE" */
		    &pItemValue, 
		    &Length, 
		    &Type))
  {
	if (TYPE_TEXT_LIST == Type)
	{
		WORD    ListCount = 0;
		char    *pText;

		ListGetText((LIST *)pItemValue, FALSE, 0, &pText, &Length );
		memset( szTitleString, '\0', DESIGN_NAME_MAX );
		memcpy( szTitleString, pText, Length );
	}

	else if (TYPE_TEXT == Type) 
	{
			/* Make sure string is smaller than buffer! */
		if (Length >= DESIGN_NAME_MAX)
			Length = DESIGN_NAME_MAX - 1;
		memcpy (szTitleString, pItemValue, Length);
		szTitleString[Length] = '\0';
	}
	else
		strcpy (szTitleString, "unknown data type");
  }
  else
  {
    strcpy (szTitleString, "not available");
  }
	
  printf ("\tDesign Note %ld : Class = %s", dwItem+1, szNoteType);
  printf ("\tTitle = '%s'\n", szTitleString);

  return;
}


/************************************************************************
 
    FUNCTION:   ProcessArgs
 
    INPUTS:     argc, argv - directly from the command line
 
    OUTPUTS:    db_filename get data from the command line or from what
		the user types at a prompt
 
*************************************************************************/
 
void  LNPUBLIC  ProcessArgs (int argc, char *argv[], char *db_filename)
{
#ifndef MAC
  if (argc != 2)
  {
#endif
 
    printf("Enter name of database: ");
    fflush(stdout);
    gets(db_filename);
 
#ifndef MAC
  }
  else
  {
     strcpy(db_filename, argv[1]);
  } /* end if */
#endif
} /* ProcessArgs */
