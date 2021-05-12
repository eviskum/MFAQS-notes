/****************************************************************************

    PROGRAM:    ftsearch

    FILE:       ftsearch.c

    DESCRIPTION:
        This program illustrates some of the full text search capabilities.

        The user specifies a database name and a query on the
        command line.

        First, the database is indexed for full text searching,
        using the database's default indexing options.
        
        Next, a full text search is performed on the specified
        query (including word variants).  
        
        The note ID's and the relevancy scores of the documents that meet the 
        search criteria are printed. The note ID's are also 
        stored in an IDTABLE structure for the next full
        text search.

        A second full text search is performed on the specified
        query, not including word variants and further refined
        by the IDTABLE created during the first full text 
        search.  The note ID's and the relevancy scores of the
        documents that meet the search criteria are printed.

        A third full text search is performed on the specified
        query, on a view containing a subset of documents. 
        In this search, the results are not explicitly returned to 
        the caller.  Instead, the search results are associated
        with the collection.  The note ID's and relevancy scores of 
        the documents that meet the search criteria are read from the
        collection and are printed.

****************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <ft.h>
#include <misc.h>
#include <osmem.h>
#include <nif.h>
#include <idtable.h>

#include <lapiplat.h>

#define VIEW_NAME "Main Topics Only"
#define STRING_LENGTH  256

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                             char *db_name, char *query);

/* Lotus C API for Domino and Notes subroutine */

LAPI_MAIN
{

/* Local data declarations */

   char     DBName[STRING_LENGTH];  /* pathname of database */
   DBHANDLE hDB;           /* database handle */
   STATUS   error=0;       /* error code from API calls */
   FT_INDEX_STATS Stats;   /* statistics from FTIndex */
   TIMEDATE retTime;       /* date that the database was last indexed */
   char szTD[MAXALPHATIMEDATE + 1];
   WORD wRetLen;
   char Query[STRING_LENGTH];       /* query */
   HANDLE hSearch;         /* handle to a search */
   DWORD dwRetDocs;        /* number of documents returned by the search */
   HANDLE hSearchResults;  /* handle to the results of the search */
   FT_SEARCH_RESULTS *pSearchResults;    /* pointer to the results of the 
                                            search */
   NOTEID *pNoteID;        /* pointer to the NOTEIDs found */
   BYTE *pScores;          /* pointer to the scores */
   DWORD i;
   HANDLE hIDTable;        /* handle to id table built with found NOTEIDs */

   char     *ViewName;              /* name of the view we'll read */
   NOTEID      ViewID;              /* note id of the view */
   HCOLLECTION hCollection;         /* collection handle */
   COLLECTIONPOSITION CollPosition; /* position within collection */
   HANDLE   hBuffer;                /* handle to buffer of note ids and
                                       relevancy scores */
   WORD     *IdList;                /* pointer to a buffer of note ids and
                                       relevancy scores */
   DWORD    EntriesFound;           /* number of entries found */
   WORD     SignalFlag;             /* signal and share warning flags */
   BOOL     FirstTime = TRUE;       /* used in NIFReadEntries loop */
   DWORD    Total = 0;              /* total number of entries found */

   LAPI_INIT(error);
   if (error)
      LAPI_INIT_ERROR;

   /* Get the command line parameters that the user entered. */
   ProcessArgs(argc, argv, DBName, Query); 


   /* Open the database. */

   if (error = NSFDbOpen (DBName, &hDB))
      LAPI_RETURN (ERR(error));

   /* Index the database */

   error = FTIndex(hDB, FT_INDEX_AUTOOPTIONS, NULL, &Stats);
   if (error)
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }
   printf ("Database:  %s\n", DBName);
   printf ("------------------------------------------------\n\n");
   printf("New documents added to index: %lu\n", Stats.DocsAdded);
   printf("Revised documents re-indexed: %lu\n", Stats.DocsUpdated);
   printf("Documents deleted from index: %lu\n", Stats.DocsDeleted);
   printf("%lu bytes indexed\n\n", Stats.BytesIndexed);

   /* Report the date/time that this database was indexed */

   memset (szTD, '\0',MAXALPHATIMEDATE + 1);
   if (error = FTGetLastIndexTime (hDB, &retTime))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   if (error = ConvertTIMEDATEToText (NULL, NULL, &retTime, szTD,
                                      MAXALPHATIMEDATE, &wRetLen))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   printf ("Time of Last Index:  %s\n\n", szTD);

   /* obtain a handle to a search */

   if (error = FTOpenSearch(&hSearch))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* do the search on the query */
   error = FTSearch (hDB,                  /* database handle */
                     &hSearch,             /* pointer to previously 
                                              allocated search handle */
                     (HCOLLECTION) NULLHANDLE, /* no collection specified - 
                                              query all docs */
                     Query,                /* query string */
                     FT_SEARCH_SCORES |    /* find relevancy scores */
                     FT_SEARCH_STEM_WORDS, /* find word variants */
                     0,                    /* maximum number of docs to
                                              return; 0 = unlimited */
                     NULLHANDLE,           /* no refining IDTABLE   */
                     &dwRetDocs,           /* returned number of docs */
                     NULL,                 /* reserved */
                     &hSearchResults);     /* returned info */
   if (error)
   {
      FTCloseSearch (hSearch);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* return if no document in the result */
   if (dwRetDocs == 0 )
   {
      printf("\n0 documents returned \n");
      FTCloseSearch (hSearch);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* obtain a pointer to the search results */
   pSearchResults = OSLock (FT_SEARCH_RESULTS, hSearchResults);

   /* check flag for single or multi database search. */
   /* This sample only handles single search.         */

   if (pSearchResults->Flags & FT_RESULTS_EXPANDED)
   {
     OSUnlockObject(hSearchResults);
     OSMemFree (hSearchResults);
     goto CloseSearch;
   }  


   /* Create an IDTABLE to further refine our search */

   if (error = IDCreateTable(sizeof(NOTEID), &hIDTable))
   {
      FTCloseSearch (hSearch);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }


   /* set up a pointer to the array of note id's that occur after
   the FT_SEARCH_RESULTS structure */

   pNoteID = (NOTEID *) (((char *) pSearchResults)
       + sizeof(FT_SEARCH_RESULTS));
 
   printf ("This is a Single Database Search...\n"); 
   printf ("-------------------------------------\n"); 
   printf ("%lu document(s) found on the query:  %s\n\n", 
           pSearchResults->NumHits, Query);
 
   if (pSearchResults->NumHits)
   {
      printf ("Note IDs        Relevancy Scores\n");
      printf ("--------        ----------------\n");
   }
   pScores = (BYTE *) (pNoteID + pSearchResults->NumHits);
   for (i = 0; i < pSearchResults->NumHits; i++, pNoteID++, pScores++)
   {
      printf ("%lX             %3d\n", *pNoteID, *pScores);

      /* save the note ids in the IDTABLE */

      if (error = IDInsert (hIDTable, *pNoteID, NULL))
      {
         OSUnlockObject(hSearchResults);
         OSMemFree (hSearchResults);
         FTCloseSearch (hSearch);
         IDDestroyTable (hIDTable);
         NSFDbClose (hDB);
         LAPI_RETURN (ERR(error));
      }
   }


   OSUnlockObject(hSearchResults);
   OSMemFree (hSearchResults);

   if (error = FTCloseSearch(hSearch))
   {
         IDDestroyTable (hIDTable);
         NSFDbClose (hDB);
         LAPI_RETURN (ERR(error));
   }

   /* Demonstrate a refined search, using the IDTABLE created above */

   if (error = FTOpenSearch(&hSearch))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* do the refined search on the query with no word variants */

   error = FTSearch (hDB,                  /* database handle */
                     &hSearch,             /* pointer to previously 
                                              allocated search handle */
                     (HCOLLECTION) NULLHANDLE, /* no collection specified - 
                                              query all docs */
                     Query,                /* query string */
                     FT_SEARCH_SCORES |    /* find relevancy scores */
                     FT_SEARCH_REFINE,     /* refine the search - use the
                                            * given id table */
                     0,                    /* maximum number of docs to
                                              return; 0 = unlimited */
                     hIDTable,             /* refining IDTABLE   */
                     &dwRetDocs,           /* returned number of docs */
                     NULL,                 /* reserved */
                     &hSearchResults);     /* returned info */
   if (error)
   {
      FTCloseSearch (hSearch);
      IDDestroyTable (hIDTable);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* return if no document in the result */
   if (dwRetDocs == 0 )
   {
      printf("\n0 documents returned \n");
      FTCloseSearch (hSearch);
      IDDestroyTable (hIDTable);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* obtain a pointer to the search results */
   pSearchResults = OSLock (FT_SEARCH_RESULTS, hSearchResults);

   /* set up a pointer to the array of note id's that occur after
      the FT_SEARCH_RESULTS structure */

   pNoteID = (NOTEID *) (((char *) pSearchResults)
           + sizeof(FT_SEARCH_RESULTS));
   printf ("\n%lu document(s) found on the refined query\n", 
           pSearchResults->NumHits);
   if (pSearchResults->NumHits)
   {
      printf ("Note IDs        Relevancy Scores\n");
      printf ("--------        ----------------\n");
   }
   pScores = (BYTE *) (pNoteID + pSearchResults->NumHits);
   for (i = 0; i < pSearchResults->NumHits; i++, pNoteID++, pScores++)
      printf ("%lX             %3d\n", *pNoteID, *pScores);

   OSUnlockObject (hSearchResults);
   OSMemFree (hSearchResults);
   IDDestroyTable (hIDTable);

   if (error = FTCloseSearch(hSearch))
   {
         NSFDbClose (hDB);
         LAPI_RETURN (ERR(error));
   }

   /* Demonstration of a search on a view - Main Topic Only */

   ViewName = VIEW_NAME;

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
         NULLHANDLE,     /* handle to unread ID list (input and return) */
         &hCollection,   /* collection handle (return) */
         NULLHANDLE,     /* handle to open view note (return) */
         NULL,           /* universal note id of view (return) */
         NULLHANDLE,     /* handle to collapsed list (return) */
         NULLHANDLE))    /* handle to selected list (return) */
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* obtain a handle to a search */

   if (error = FTOpenSearch(&hSearch))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* do the search on the query */
   error = FTSearch (hDB,                  /* database handle */
                     &hSearch,             /* pointer to previously 
                                              allocated search handle */
                     hCollection,          /* collection to search on */
                     Query,                /* query string */
                     FT_SEARCH_SET_COLL |  /* associate an FT_SEARCH_RESULTS
                                              table to the collection */
                     FT_SEARCH_SCORES |    /* to be able to read the
                                              relevancy score in 
                                              NIFReadEntries */
                     FT_SEARCH_STEM_WORDS, /* also find word variants */
                     0,                    /* maximum number of docs to
                                              return; 0 = unlimited */
                     NULLHANDLE,           /* no refining IDTABLE   */
                     &dwRetDocs,           /* returned number of docs */
                     NULL,                 /* reserved */
                     &hSearchResults);     /* pointer to returned info 
                                              handle, which is not filled
                                              in here, because we specify the
                                              FT_SEARCH_SET_COLL option */
   if (error)
   {
      FTCloseSearch (hSearch);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* return if no document in the result */
   if (dwRetDocs == 0 )
   {
      printf("\n0 documents returned \n");
      FTCloseSearch (hSearch);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Set up the data structure, COLLECTIONPOSITION, that controls where in
      the collection we will begin when we read the collection.  Specify 
      that we want to start at the beginning. */

   CollPosition.Level = 0;
   CollPosition.Tumbler[0] = 0;

   /* Read the hits from the collection.
      Get a buffer with information about each entry in the collection. 
      Perform this routine in a loop.  Terminate loop when SignalFlag
      indicates that there is no more information to get.   */

   do
   {
      if ( error = NIFReadEntries(
             hCollection,        /* handle to this collection */
             &CollPosition,      /* where to start in collection */
             NAVIGATE_NEXT_HIT,  /* order to use when skipping */
             1L,                 /* number to skip */
             NAVIGATE_NEXT_HIT,  /* order to use when reading
                                    same order as hit's relevancy score */
             0xFFFFFFFF,         /* max number to read */
             READ_MASK_NOTEID |  /* info we want - note ids and */
             READ_MASK_SCORE,    /* relevancy scores */
             &hBuffer,           /* handle to info buffer (return)  */
             NULL,               /* length of info buffer (return) */
             NULL,               /* entries skipped (return) */
             &EntriesFound,      /* entries read (return) */
             &SignalFlag))       /* share warning and more signal flag
                                    (return) */

      {
         NIFCloseCollection (hCollection);
         FTCloseSearch (hSearch);
         NSFDbClose (hDB);
         LAPI_RETURN (ERR(error));
      }

      /* Check to make sure there was a buffer of information returned. */

      if (hBuffer == NULLHANDLE)
      {
         NIFCloseCollection (hCollection);
         FTCloseSearch (hSearch);
         NSFDbClose (hDB);
         printf ("\nEmpty buffer returned by NIFReadEntries.\n");
         LAPI_RETURN (NOERROR);
      }

      /* Obtain a pointer to the buffer of entry IDs and relevancy scores. */

      IdList = (WORD *) OSLockObject (hBuffer);

      /* Print out the list of note IDs found by this search. */

      if (FirstTime)
      {
         printf ("\n\n% The following document(s) were found on the query ");
         printf ("of the view,\n%s\n", VIEW_NAME);
         printf ("Note IDs        Relevancy Scores\n");
         printf ("--------        ----------------\n");
         FirstTime = FALSE;
      }

      for (i=0; i<EntriesFound; i++)
      {
         printf ("%lX            ", *((NOTEID *)IdList));
         /* advance IdList to point to the relevancy score */
         IdList = (WORD *) (((char *)IdList) + sizeof(NOTEID));
         printf ("%3d\n", *IdList);
         /* advance to the next note ID */
         IdList = (WORD *) (((char *)IdList) + sizeof(WORD));
      }

      Total += EntriesFound;

      /* When done, print the total number of entries found */

      if ( !(SignalFlag & SIGNAL_MORE_TO_DO) )
         printf ("\n%lu document(s) found on the query of the view, %s\n", 
                 Total, VIEW_NAME);

      /* Unlock the list of IDs. */

      OSUnlockObject (hBuffer);

      /* Free the memory allocated by NIFReadEntries. */

      OSMemFree (hBuffer);

      /* Loop if the end of the collection has not been reached 
         because the buffer was full.  */

   }  while (SignalFlag & SIGNAL_MORE_TO_DO);


   /* Close the collection. */

   error = NIFCloseCollection(hCollection);

   
   /* Close the search */

CloseSearch:

   error = FTCloseSearch(hSearch);

   error = NSFDbClose(hDB);
   LAPI_RETURN (ERR(error));
}


/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    db_name -     database name obtained from command line or
                              from prompt.

                query  -     is the query string for the search

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *db_name, char *query)
{ 
#ifndef MAC
    if (argc != 3)  
    {
#endif

        printf("Enter database name: ");      
        fflush (stdout);
        gets(db_name);
        printf("\n");
        printf ("Enter the query string for the search:  ");
        fflush (stdout);
        gets(query);

#ifndef MAC
    }    
    else
    {
        strcpy(db_name, argv[1]);    
        strcpy(query, argv[2]);    
    } /* end if */
#endif
} /* ProcessArgs */

