/****************************************************************************
    PROGRAM:    viewids

    FILE:       viewids.c

    SYNTAX:     viewids

    PURPOSE:    Finds all the documents in the view. For each document, 
                get the note ID and print it. 

    DESCRIPTION:
        This sample shows how to open a view note, open the corresponding
        collection (index), and read the entries in the collection. For
        each entry, this reads the note ID. This just prints out the note
        ID, but note that, given the note ID, you could perform any 
        other operation on that note.

****************************************************************************/

/* C include files */

#include <stdio.h>
#include <string.h>

/* Lotus  API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nif.h>
#include <osmem.h>
#include <miscerr.h>

#include <lapiplat.h>

#ifdef OS390
#include <_Ascii_a.h>                /* NOTE: must be the LAST file included */
#endif

/* Notes API subroutine */

LAPI_MAIN
{
   char     DBFilename[]="simple.nsf";/* pathname of the database */
   char     ViewName[]="SimpleDataView";/* name of the view we'll read */
   DBHANDLE hDB;                    /* handle of the database */
   NOTEID      ViewID;              /* note id of the view */
   HCOLLECTION hCollection;         /* collection handle */
   COLLECTIONPOSITION CollPosition; /* position within collection */
   HANDLE      hBuffer;             /* handle to buffer of note ids */
   NOTEID      *IdList;             /* pointer to a note id */
   DWORD    EntriesFound;           /* number of entries found */
   DWORD    NotesFound=0;           /* number of documents found */
   WORD     SignalFlag;             /* signal and share warning flags */
   DWORD   i;                       /* a counter */
   STATUS   error = NOERROR;        /* return status from API calls */


   LAPI_INIT(error)
   if (error)
      LAPI_INIT_ERROR;

/* Open the database. */

   if (error = NSFDbOpen (DBFilename, &hDB))
      LAPI_RETURN (ERR(error));

/* Get the note id of the view we want. */

   if (error = NIFFindView (hDB, ViewName, &ViewID))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

/* Get a collection using this view. */

   if (error = NIFOpenCollection(
         hDB,            /* handle of db with view */
         hDB,            /* handle of db with data */
         ViewID,         /* note id of the view */
         0,              /* collection open flags */
         NULLHANDLE,     /* handle to unread ID list */
         &hCollection,   /* collection handle */
         NULLHANDLE,     /* handle to open view note */
         NULL,           /* universal note id of view */
         NULLHANDLE,     /* handle to collapsed list */
         NULLHANDLE))    /* handle to selected list */
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

/* Set up the data structure, COLLECTIONPOSITION, that controls where in
the collection we will begin when we read the collection.  Specify that we
want to start at the beginning. */

   CollPosition.Level = 0;
   CollPosition.Tumbler[0] = 0;

/* Get a buffer with information about each entry in the collection. 
   Perform this routine in a loop.  Terminate loop when SignalFlag
   indicates that there is no more information to get.   */

   do
   {
      if ( error = NIFReadEntries(
             hCollection,        /* handle to this collection */
             &CollPosition,      /* where to start in collection */
             NAVIGATE_NEXT,      /* order to use when skipping */
             1L,                 /* number to skip */
             NAVIGATE_NEXT,      /* order to use when reading */
             0xFFFFFFFF,         /* max number to read */
             READ_MASK_NOTEID,   /* info we want */
             &hBuffer,           /* handle to info buffer */
             NULL,               /* length of info buffer */
             NULL,               /* entries skipped */
             &EntriesFound,      /* entries read */
             &SignalFlag))       /* share warning and more signal flag */

      {
         NIFCloseCollection (hCollection);
         NSFDbClose (hDB);
         LAPI_RETURN (ERR(error));
      }

/* Check to make sure there was a buffer of information returned.
(We would crash if we tried to proceed with a null buffer.) */ 

      if (hBuffer == NULLHANDLE)
      {
         NIFCloseCollection (hCollection);
         NSFDbClose (hDB);
         printf ("\nEmpty buffer returned by NIFReadEntries.\n");
         LAPI_RETURN (NOERROR);
      }

/* Lock down (freeze the location) of the buffer of entry IDs. Cast
the resulting pointer to the type we need. */

      IdList = (NOTEID *) OSLockObject (hBuffer);

/* Print out the list of note IDs found by this search. Don't print a note 
ID if it is a "dummy" ID that stands for a category in the collection. */

      printf ("\n");
      for (i=0; i<EntriesFound; i++)
      {
         if (NOTEID_CATEGORY & IdList[i]) continue; 
         printf ("Note count is %lu. \t Note ID is: %lX\n", 
                 ++NotesFound, IdList[i]);
      }

/* Unlock the list of IDs. */

      OSUnlockObject (hBuffer);

/* Free the memory allocated by NIFReadEntries. */

      OSMemFree (hBuffer);

/* Loop if the end of the collection has not been reached because the buffer
   was full.  */

   }  while (SignalFlag & SIGNAL_MORE_TO_DO);

/* Close the collection. */

   if (error = NIFCloseCollection(hCollection))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

/* Close the database. */

   if (error = NSFDbClose (hDB))
      LAPI_RETURN (ERR(error));

/* End of subroutine. */

   printf("\nProgram completed successfully.\n");
   LAPI_RETURN (NOERROR);
}

