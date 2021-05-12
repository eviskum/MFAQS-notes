/****************************************************************************

    PROGRAM:    twokey

    FILE:       twokey.c

    SYNTAX:     twokey  <First Key Value>  <Second Key Value>

    DESCRIPTION:
	This program finds the documents in a view that have a primary key 
	(the first sorted column in the view) of TYPE_TEXT and a secondary 
	key (the second sorted column in the view) of TYPE_NUMBER.  For each 
	document that matches, we get its noteID.

	We don't actually read the data in the notes.  Reading a note, 
	given its noteID, is shown in another example.

****************************************************************************/

/* C include files */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nif.h>
#include <osmem.h>
#include <miscerr.h>
#include <editods.h>

#include <lapiplat.h>

#define   MALLOC_AMOUNT	6048
#define   STRING_LENGTH  256

/* Function prototypes for local functions */
 
void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                               char *Key1, 
                               char *Key2);


LAPI_MAIN
{

/* Local data declarations */

   char     		dbFilename[11], ViewName[8];    
   DBHANDLE 		hDb;            
   NOTEID   		ViewID;         
   HCOLLECTION 		hCollection; 
   COLLECTIONPOSITION 	posCollection;   
   HANDLE   		hBuffer;        
   NOTEID  		*pNoteID;        
   DWORD     		NumNotesFound=0;     
   DWORD     		NumNotesMatch=0;     
   DWORD     		NoteCount = 0;     
   DWORD     		i;     
   STATUS   		error=0;
   char    		*Key1;   /* primary input key */
   char			*TranslatedKey;		/* Translated string key */
   char    		*Key2;   /* secondary input key */
   char    		*pTemp, *pKey;
   WORD     		Item1ValueLen, Item2ValueLen, signal_flag;
   WORD			TranslatedKeyLen;
   BOOL     		FirstTime = TRUE;    

   ITEM_TABLE 		Itemtbl;
   ITEM 		Item;
   WORD      		Word;
   double     		Double, dValue=0;

/* Initialize Domino and Notes */
 
   LAPI_INIT(error);
   if (error)
      LAPI_INIT_ERROR;

/* allocating memory for input keys 
   Do NOT forget to free it later */

   Key1 = (char *) malloc(STRING_LENGTH); 

   if (Key1 == NULL)    
   {
      printf("Error: Out of memory.\n");
      LAPI_RETURN (NOERROR);
   }

   TranslatedKey = (char *) malloc(STRING_LENGTH); 

   if (TranslatedKey == NULL)    
   {
	  free (Key1);
      printf("Error: Out of memory.\n");
      LAPI_RETURN (NOERROR);
   }

   Key2 = (char *) malloc(STRING_LENGTH); 

   if (Key2 == NULL)    
   {
	  free (Key1);
	  free (TranslatedKey);
      printf("Error: Out of memory.\n");
      LAPI_RETURN (NOERROR);
   }

/* Processing input arguments */

   ProcessArgs(argc, argv, Key1, Key2);

   strcpy(dbFilename,"twokey.nsf");
   strcpy(ViewName,"KeyView");

 
/* Open the database. */

   if (error = NSFDbOpen (dbFilename, &hDb))  
      LAPI_RETURN (ERR(error));

/* Get the note id of the view we want. */

   if (error = NIFFindView (hDb, 
			    ViewName, 
			    &ViewID))  
   {
      NSFDbClose (hDb);
      LAPI_RETURN (ERR(error));
   }

/* Get the current collection using this view. */

   if (error = NIFOpenCollection(
	 hDb,           /* handle of db with view */
	 hDb,           /* handle of db with data */
	 ViewID,        /* noteID  of the view */
	 0,             /* collection open flags */
	 NULLHANDLE,    /* handle to unread ID list (input and return) */
	 &hCollection,  /* collection handle (return) */
	 NULLHANDLE,    /* handle to open view note (return) */
	 NULL,          /* universal noteID  of view (return) */
	 NULLHANDLE,    /* handle to collapsed list (return) */
	 NULLHANDLE))   /* handle to selected list (return) */
   {
      NSFDbClose (hDb);
      LAPI_RETURN (ERR(error));
   }

   /* Translate the input key to LMBCS */
#ifndef OS400
   TranslatedKeyLen = OSTranslate (
	   OS_TRANSLATE_NATIVE_TO_LMBCS,
	   Key1,
	   (WORD) strlen (Key1),
	   TranslatedKey,
	   STRING_LENGTH);
#else
       strcpy(TranslatedKey, Key1);
       TranslatedKeyLen = strlen(TranslatedKey);
#endif

   Item1ValueLen = TranslatedKeyLen + sizeof(WORD);
   Item2ValueLen = sizeof(double) + sizeof(WORD);

   pKey = (char *) malloc(MALLOC_AMOUNT);

   if (pKey == NULL)    
   {
      printf("Error: Out of memory.\n");
      LAPI_RETURN (NOERROR);
   }

   pTemp = pKey;

   Itemtbl.Length = (	sizeof(Itemtbl) + 
			(2*(sizeof(Item))) + Item1ValueLen + Item2ValueLen);
   Itemtbl.Items = 2;
   memcpy (pTemp, &Itemtbl, sizeof(Itemtbl));
   pTemp += sizeof(Itemtbl);

   Item.NameLength = 0;
   Item.ValueLength = Item1ValueLen;
   memcpy (pTemp, &Item, sizeof(Item));
   pTemp += sizeof(Item);

   Item.NameLength = 0;  
   Item.ValueLength = Item2ValueLen;
   memcpy (pTemp, &Item, sizeof(Item));
   pTemp += sizeof(Item);

   Word = TYPE_TEXT;
   memcpy (pTemp, &Word, sizeof(Word));
   pTemp += sizeof(Word);

   memcpy (pTemp, TranslatedKey, TranslatedKeyLen);                
   pTemp += TranslatedKeyLen;

   Word = TYPE_NUMBER;
   memcpy (pTemp, &Word, sizeof(Word));
   pTemp += sizeof(Word);

   Double = atof(Key2);
   memcpy (pTemp, &Double, sizeof(Double));
   pTemp += sizeof(Double);

/* Search through the collection for the notes whose sort 
   column values match the given search keys: */

   error = NIFFindByKey(
	    hCollection,
	    pKey,          /* refer to key   */
	    FIND_CASE_INSENSITIVE,     /* match rules */
	   &posCollection, /* where match begins (return) */
	   &NumNotesMatch);/* how many match (return) */

/* Be nice: release what you've taken */
   free(pKey);
   free(Key1);
   free(Key2);
   free(TranslatedKey);
       
   if (ERR(error) == ERR_NOT_FOUND) 
   {
      printf ("\nKey not found in the collection.\n");
      NIFCloseCollection (hCollection);
      NSFDbClose (hDb);
      LAPI_RETURN (NOERROR);
   }
   
   if (error) 
   {
      NIFCloseCollection (hCollection);
      NSFDbClose (hDb);
      LAPI_RETURN (ERR(error));
   }

   do
   {

  /* Read entries in the collection */

      if (error = NIFReadEntries(
	     hCollection,        /* handle to this collection           */
	     &posCollection,      /* where to start in collection        */
	     (WORD) (FirstTime ? NAVIGATE_CURRENT : NAVIGATE_NEXT),
				  /* order to use when skipping */
	     FirstTime ? 0L : 1L, /* number to skip */
	     NAVIGATE_NEXT,      /* order to use when reading           */
	     NumNotesMatch - NoteCount,  /* max number to read                  */
	     READ_MASK_NOTEID,   /* info we want                        */
	     &hBuffer,            /* handle to info (return)             */
	     NULL,               /* length of buffer (return)           */
	     NULL,               /* entries skipped (return)            */
	     &NumNotesFound,      /* entries read (return)               */
	     &signal_flag))          /* signal and share warnings (return) */

      {
	 NIFCloseCollection (hCollection);
	 NSFDbClose (hDb);
	 LAPI_RETURN (ERR(error));
      }

      if (hBuffer == NULLHANDLE)
      {
	 NIFCloseCollection (hCollection);
	 NSFDbClose (hDb);
	 printf ("\nEmpty buffer returned by NIFReadEntries.\n");
	 LAPI_RETURN (NOERROR);
      }

      pNoteID = (NOTEID *) OSLockObject (hBuffer);

      printf ("\n");
      for (i=0; i<NumNotesFound; i++)
	 printf ("Note count is %lu. \t noteID  is: %lX\n", 
		 ++NoteCount, pNoteID[i]);
   
      OSUnlockObject (hBuffer);

      OSMemFree (hBuffer);

      if (FirstTime)
	 FirstTime = FALSE;

   }  while (signal_flag & SIGNAL_MORE_TO_DO);
   
/* Close the collection */

   if (error = NIFCloseCollection(hCollection))
   {
      NSFDbClose (hDb);
      LAPI_RETURN (ERR(error));
   }

/* Close the Database */

   if (error = NSFDbClose (hDb)) LAPI_RETURN (ERR(error));

   printf("\nProgram completed successfully.\n");
   LAPI_RETURN (NOERROR);
}


/************************************************************************
 
    FUNCTION:   ProcessArgs
 
    INPUTS:     argc, argv - directly from the command line
 
    OUTPUTS:    Key1, Key1 - data from the command line or
                from what the user types when prompted.
 
*************************************************************************/
 
void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                               char *Key1, char *Key2)
{
#ifndef MAC
    if (argc != 3)
    {
#endif
 
        printf("Enter the first key: ");
        fflush(stdout);
        gets(Key1);

	     printf("\n");
        printf("Enter the second key: ");
        fflush(stdout);
        gets(Key2);
 
#ifndef MAC
    }
    else
    {
         strcpy(Key1, argv[1]);
         strcpy(Key2, argv[2]);
 
    } /* end if */
#endif
} /* ProcessArgs */
