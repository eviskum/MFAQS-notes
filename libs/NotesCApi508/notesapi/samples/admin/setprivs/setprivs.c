/**********************************************************************

    PROGRAM:    setprivs

    FILE:       setprivs.c

    PURPOSE:    Modify the read access privilege levels or read access
                name list of all documents in a specified view of a database.

    SYNTAX:     setprivs (db path) ("view") -M (numeric privilege)
                           OR
                setprivs (db path) ("view") 
                      -L ("name" or "[role]") [("name" or "[role]")...]


    DESCRIPTION:
        Given an existing database, a view name, and either a privilege mask
        or a name list (consisting of people, servers, groups, and/or roles), 
        set the read access of all documents (notes) in the view.

 **********************************************************************/


/* C includes */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes includes */

#include <lapicinc.h>

#include <global.h>
#include <osmisc.h>
#include <osmem.h>
#include <miscerr.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nif.h>
#include <stdnames.h>
#include <textlist.h>

#include <lapiplat.h>

#define LINEOFTEXT   256

typedef struct
{
    WORD NumEntries;
    char **pReaderEntries;
} READER_LIST;

#define DESIGN_READERS "$Readers"

/* Function protoyptes for local functions. */

STATUS UpdatePrivMask (NOTEHANDLE, WORD, DWORD *, DWORD *);
STATUS UpdateReaderList (NOTEHANDLE, READER_LIST,
                     DWORD *, DWORD *);
void LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *FileName, char *ViewName, short *SetReaderList, WORD *NewPrivileges, char **TheRList, WORD *numEntries, short *FreeList);
/************************************************************************

    FUNCTION:   NotesMain/Main

    PURPOSE:    Main Lotus C API for Domino and Notes subroutine

    ALGORITHM:
   1) Read the command line arguments.
      Parse them into the appropriate variables.  
      The user can specify whether to set a privilege mask or 
      a person, server, group and role name list.
      Open the specified database.

   2) Get the note ID of the specified view.
      Open the collection.
      Create a buffer in memory of the document noteIDs in the collection.
      Close the collection.

   3) If hBuffer not null, then lock the buffer memory.
         For every noteID in the buffer, 
            open the note,
            if privilege mask was specified
               save the current privilege levels,
               if the saved privilege levels were the same as the new ones,
                  then increment the number of notes not updated
               else 
                  set the privilege levels to the new ones and
                  increment the number of notes updated
            if a name list was specified
              if the $Reader text list field exists
                  delete it
              create $Reader text list field and add the text list.
            close the note
         unlock the buffer memory
         free the memory.

   4) Close the Domino database
      If no error, display the statistics
      Return with the error

*************************************************************************/

LAPI_MAIN
{
    STATUS error;
    char PathName[LINEOFTEXT];
    char ViewName[LINEOFTEXT];
    char *RList[256];
    short SetReaderList;
    READER_LIST ReaderList;
    DBHANDLE hDB;
    HCOLLECTION hCollection;
    NOTEID ViewNoteID;
    WORD NewPrivileges;
    DWORD NumUpdated = 0;
    DWORD NumNotUpdated = 0;
    short i;
    short FreeList;

    LAPI_INIT(error);
    if (error)
		LAPI_INIT_ERROR;

    /********************************************************************/
    /* Read the command line arguments,
       store them into the appropriate variables,
       open the specified database.
    */
    /********************************************************************/

    ProcessArgs (argc, argv, PathName, ViewName, &SetReaderList, &NewPrivileges, RList, &ReaderList.NumEntries, &FreeList);
    if (SetReaderList && ReaderList.NumEntries == 0)
    {
      printf("\nError: No read access name list specified.\n");
      LAPI_RETURN(NOERROR);
    }

    ReaderList.pReaderEntries = RList;


    /* Open the database specified on the command line. */
    if (error = NSFDbOpen(PathName, &hDB))
        LAPI_RETURN(error);

    /********************************************************************/
    /* Get the note ID of the specified view,
       open the collection, 
       create a buffer in memory of the document noteIDs in the collection,
       close the collection.
    */
    /********************************************************************/
    
    if (error = NIFFindView(hDB, ViewName, &ViewNoteID))
        {
        if (error == ERR_NOT_FOUND)
            {
            printf("View '%s' cannot be found\n", ViewName);
            error = NOERROR;
            }
        goto Done;
        }

    /* Open the collection of notes in the view at the current time.
       Return a handle to the collection to the variable hCollection. */

    if (error = NIFOpenCollection(hDB, hDB, ViewNoteID,
                            0,
                            NULLHANDLE,
                            &hCollection,
                            NULL, NULL, NULL, NULL))
        goto Done;

    {
    COLLECTIONPOSITION IndexPos;
    DWORD EntriesReturned;
    HANDLE hBuffer;
    WORD   SignalFlag;             /* signal and share warning flags */

    IndexPos.Level = 0;
    IndexPos.Tumbler[0] = 0;

    /* Create a buffer of note IDs copied from the collection and store the
       note IDs into a buffer with handle hBuffer. */
    do
        {
        error = NIFReadEntries(hCollection,
                               &IndexPos,
                               NAVIGATE_NEXT, 1L,
                               NAVIGATE_NEXT, MAXDWORD,
                               READ_MASK_NOTEID,
                               &hBuffer, NULL,
                               NULL, &EntriesReturned, &SignalFlag);

    
        /****************************************************************/
        /*   if hBuffer not null, then lock the buffer memory 
             for every noteID in the buffer, 
                open the note,
             if SetReaderList is specified
                 create and add the reader text list,
                 increment the number of notes updated
             else
                set the privilege levels to the new levels,
                if the saved privilege levels were the same as the new levels
                   then increment the number of notes not updated
                   else increment the number of notes updated
                close the note
             unlock the buffer memory
             free the memory
        */            
        /********************************************************************/

        if (hBuffer != NULLHANDLE)
            {
            char String[512];
            DWORD i;
  
            /* NIFReadEntries requires memory to be locked 
               (if hBuffer <> 0)   */
            NOTEID *entry = OSLock(NOTEID, hBuffer);

            /* process each individual noteID       */
            for (i=0; i < EntriesReturned; i++, entry++)
                {
                NOTEHANDLE hNote;
 
                /* skip this noteID if it is for a category entry  */
                if (*entry & NOTEID_CATEGORY)
                    continue;

                /* open each note separately, follow each with 
                   close of note */
                if (error = NSFNoteOpen(hDB, *entry, 0, &hNote))
                    {
                    OSLoadString(NULLHANDLE, ERR(error), String,
                                 sizeof(String)-1);
                    printf("Error '%s' reading docment %#lX -- %s\n",
                            String, *entry, " skipping it");
                    continue;
                    }


                if (SetReaderList)
                    error = UpdateReaderList (hNote, ReaderList, 
                                            &NumNotUpdated, &NumUpdated);
                else
                    error = UpdatePrivMask (hNote, NewPrivileges, 
                                            &NumNotUpdated, &NumUpdated);

                /* close each note   */
                NSFNoteClose(hNote);
                if (error)
                    {
                    OSLoadString(NULLHANDLE, ERR(error), String,
                                 sizeof(String)-1);
                    printf("Error '%s' writing document %#lX -- %s\n",
                           String, *entry, "skipping it");
                    continue;
                    }
                }

            /* finished with all noteIDs, unlock memory and free it   */
            OSUnlockObject(hBuffer);
            OSMemFree(hBuffer);
            }
        }  while (SignalFlag & SIGNAL_MORE_TO_DO);

       NIFCloseCollection(hCollection);
       if (error)
          goto Done;

    }

Done:
    /********************************************************************/
    /*
    Close the Domino database.
    If no error, display the statistics.
    Return with the error.
    */
    /********************************************************************/

    /* Close the database opened when program started */
    NSFDbClose(hDB);

    /* Display statistics about noteIDs updated and not updated   */
    if (!error)
        {
        if (NumUpdated)
            printf("%lu documents had their privileges updated\n",
                   NumUpdated);
        if (NumNotUpdated)
            printf("%lu documents already had the desired privileges\n",
                   NumNotUpdated);
        }

	/* Free the reader list */
	if (SetReaderList && FreeList)
	{
		for (i = 0; i < (short) ReaderList.NumEntries; i++)
			free(RList[i]);
	}
    LAPI_RETURN (error);
}


STATUS UpdatePrivMask (NOTEHANDLE hNote, WORD NewPrivMask, 
                     DWORD *pdwNumNotUpdated, DWORD *pdwNumUpdated)

/*    UpdatePrivMask - Updates the privilege mask of a note if
 *                     different than the note's current privilege
 *                     mask.
 *
 *    Inputs:
 *        hNote - handle to the note
 *        NewPrivMask - Privilege mask indicating which privilege levels 
 *                      to set
 *
 *    Outputs:
 *        pdwNumNotUpdated -Value pointed to is incremented if the note 
 *                       does not need to be updated (its privilege mask
 *                       is the same as the NewPrivMask.
 *        pdwNumUpdated   - Value pointed to is incremented if the note is 
 *                       updated with the new privilege mask.
 *        return       - Error code from Lotus C API for Domino and Notes call.
 */

{
    WORD OldPrivMask;
    STATUS error = NOERROR;

    /* get original privileges, check to see if different */
    NSFNoteGetInfo(hNote, _NOTE_PRIVILEGES, &OldPrivMask);
    if (OldPrivMask == NewPrivMask)
       (*pdwNumNotUpdated)++;
    else
        {
        NSFNoteSetInfo (hNote, _NOTE_PRIVILEGES, &NewPrivMask);
        if (!(error = NSFNoteUpdate(hNote, UPDATE_NOCOMMIT)))
            (*pdwNumUpdated)++;
        }
    return (error);
}


STATUS UpdateReaderList (NOTEHANDLE hNote, READER_LIST ReaderList,
                     DWORD *pdwNumNotUpdated, DWORD *pdwNumUpdated)

/*    UpdateReaderList - Updates the reader access name list of a note 
 *    by creating the $Readers text list field in the note and adding 
 *    the specified people, servers, groups, and roles.
 *    Roles are already enclosed in brackets.  
 *
 *    Inputs:
 *        hNote - handle to the note
 *        ReaderList - Information needed to create the text list
 *    Outputs:
 *        pdwNumNotUpdated -currently not used.  Value pointed to is 
 *                       incremented if the note does not need
 *                       to be updated (the note's privilege 
 *                       text list exists and is the same as the new
 *                       privilege text list.  Currently, if the privilege
 *                       text list field exists, it is deleted and re-
 *                       created.
 *        pdwNumUpdated   - Value pointed to is incremented if the note 
 *                       is updated with the new privilege text list.
 *        return       - Error code from Lotus C API for Domino and Notes call.
 */

{
    STATUS error = NOERROR;
    HANDLE hList;          /* handle to privilege text list */
    VOID *pList;           /* pointer to the privilege text list */
    WORD wListSize;         /* total size of text list structure */
    WORD i;
    char *pTextEntry;

    /* If the "$Readers" field exists, delete it. */

    if (NSFItemIsPresent(hNote, DESIGN_READERS , strlen(DESIGN_READERS)))
        if (error = NSFItemDelete (hNote, DESIGN_READERS, 
                               strlen(DESIGN_READERS)))
            return (error);

     pTextEntry = *(ReaderList.pReaderEntries);
     if (pTextEntry[0] == '\0')
         {
         /* Just update the note - the $Readers field is deleted */

         if (!(error = NSFNoteUpdate(hNote, UPDATE_NOCOMMIT)))
             (*pdwNumUpdated)++;
         return (error);
         }

    /* Create an empty text list structure */

    if (error = ListAllocate (0, 0, FALSE, &hList, &pList, &wListSize))
        return (error);

    OSUnlock (hList);
    pList = NULL;

    /* Add each text list entry */
    for (i = 0; i < ReaderList.NumEntries; i++)
        {
        pTextEntry = *(ReaderList.pReaderEntries + i);

        if (error = ListAddEntry (hList, FALSE, &wListSize, i,
                                  pTextEntry, strlen(pTextEntry)))
            {
            OSMemFree(hList);
            return (error);
            }

        }  /* for */

    /* Add the completed field to the note. */

    pList = OSLockObject (hList);

    error = NSFItemAppend (hNote, ITEM_SUMMARY | ITEM_READERS,
                               DESIGN_READERS, strlen (DESIGN_READERS),
                               TYPE_TEXT_LIST, pList, wListSize);

    /* Unlock and free the buffer that was holding the text list field. */

     OSUnlock(hList);
     OSMemFree(hList);
     if (error)
        return (error);

    /* Update the note */

    if (!(error = NSFNoteUpdate(hNote, UPDATE_NOCOMMIT)))
        (*pdwNumUpdated)++;

    return (error);
}


/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    FileName -     database name obtained from command line or
                              from prompt.
							 
				ViewName  -    the view name
				
				SetReaderList - specifies that we are setting the reader 
								reader list rather then the access privileges
								
				NewPrivileges - the value to set the privileges
				
				TheRList - the reader access list
				
				numEntries - the number of entries in the reader access list.
				
				Freelist - whether the reader list will need to be freed after use.
						   this will be False if arguments were provided on the command 
						   line.

*************************************************************************/

void LNPUBLIC  ProcessArgs (
int    argc,
char  *argv[],
char  *FileName,
char  *ViewName,
short *SetReaderList,
WORD  *NewPrivileges,
char **TheRList,
WORD  *numEntries,
short *FreeList)
{ 

  char  inputString[LINEOFTEXT];
  char *newString;
  int   i;

  *numEntries = 0;

#ifndef MAC
  if (argc < 5)  
  {
#endif
    printf("Enter file name: ");      
    fflush (stdout);
    gets(FileName);
    printf("\n");
    printf ("Enter the view name:  ");
    fflush (stdout);
    gets(ViewName);
	 printf("\n");
tryagain:
    printf("Choose whether to set read access list (L) or privilege mask (M): ");      
    fflush (stdout);
    gets(inputString);
    printf("\n");
    if (inputString[0] == 'L' || inputString[0] == 'l')
    {
      *SetReaderList = TRUE;
      *FreeList = TRUE;
      for (;;)
      {
        printf("Enter read access names or a / to indicate you are finished: ");     
        fflush (stdout);
        gets(inputString);
        printf("\n");
        if (inputString[0] == '/')
          break;
        else
        {
          (*numEntries)++;
          newString = malloc(LINEOFTEXT);
          strcpy(newString, inputString);
          TheRList[*numEntries - 1] = newString;
        }
      }
    }
    else if (inputString[0] == 'M' || inputString[0] == 'm')
    {
      printf("Enter privilege level: ");     
      *SetReaderList = FALSE;
      fflush (stdout);
      gets(inputString);
      printf("\n");
      *NewPrivileges = atoi(inputString) & 0x001F;
    }
    else
      goto tryagain;
#ifndef MAC
  }    
  else
  {
    strcpy(FileName, argv[1]);    
    strcpy(ViewName, argv[2]);    

    if ( !strcmp(argv[3], "-L") || !strcmp(argv[3], "-l") )
    {
      *numEntries = argc - 4;
		for (i=0; i<*numEntries; i++)
        TheRList[i] = *(argv + 4 + i);
      *SetReaderList = TRUE; 
      *FreeList = FALSE;
    }
    else if ( !strcmp(argv[3], "-M") || !strcmp(argv[3], "-m") )
    {
      *SetReaderList = FALSE;
      *NewPrivileges = atoi(argv[4]) & 0x001F;
    }

  } /* end if */
#endif
} /* ProcessArgs */
