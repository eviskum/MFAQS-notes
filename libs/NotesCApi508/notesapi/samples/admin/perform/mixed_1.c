/****************************************************************************

    PROGRAM:    mixed_1

    FILE:       mixed_1.c

    DESCRIPTION:  
        This program tests the performance of Domino and Notes for a mixed set 
		of transactions on the Name and Address book. This version of the
        test uses "optimal" transactions (minimal index building).

        For a given test size (N), the transactions are:

           .33N additions of new records with no index usage at all.

            1 build of the name index.

            .33N modifications of existing records, using an index 
            lookup to find each record. Once modified, a record is 
            not modified again.

            1 update of the name index.

            .33N deletions of records, using an index lookup to find 
            each record.

****************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nif.h>
#include <osmem.h>
#include <miscerr.h>
#include <ostime.h>
#include <misc.h>

#include <lapiplat.h>

/* Lotus C API for Domino and Notes subroutine */

LAPI_MAIN
{

/* Local data declarations */

   char                *db_path;            /* pathname of test database */
   int                 transactions;        /* total number of transactions */

   DBHANDLE            db_handle;           /* database handle */
   NOTEHANDLE          note_handle;         /* note handle */
   HCOLLECTION         coll_handle;         /* collection handle */
   HANDLE              buffer_handle;       /* handle to buffer of note ids */

   char                last_name[100];      /* last name in N&A book */
   char                count[10];           /* used to construct unique names */

   NOTEID              view_id;             /* note id of the view */
   COLLECTIONPOSITION  coll_pos;            /* position within collection */
   NOTEID              *id_list;            /* pointer to a note id */
   DWORD               notes_found;         /* number of notes found */
   DWORD               match_size;          /* number of notes matching key */

   int                 i;
   STATUS              error;

   LONG           time_delta;
   TIMEDATE       StartTime;        /* time to mark the start of the program */
   TIMEDATE       LastTime;         /*  time to mark the end of the program */
 

/* ************************************************** */
/* Get the input parameters. */
/* ************************************************** */

   if (argc != 3)
      {
      printf ("\nUsage:  MIXED_1  <database pathname>  <number of transaction>\n");
      LAPI_RETURN (NOERROR);
      }
   db_path = argv[1];
   transactions = atoi(argv[2]);

    printf ("\n***** MIXED_1 Test Begins ******\n");
 
/* ************************************************** */
/* Open the database. */
/* ************************************************** */

   if (error = NSFDbOpen (db_path, &db_handle))
      LAPI_RETURN (ERR(error));

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&StartTime);

/* ************************************************** */
/* Add new records, each with a different last name. */
/* ************************************************** */

/* Start a big loop for adding names. */

   for (i=0; i<(transactions/3); i++)
   {

/* Construct the last name. */

   strcpy (last_name, "Connell");
   sprintf(count, "%i", i);
   strcat (last_name, count);

/* Create the record. */

   if (error = NSFNoteCreate (db_handle, &note_handle))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Add all the fields. */

   if (error = NSFItemSetText ( note_handle, 
               "Form",
               "Person",
               MAXWORD))
      {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (error = NSFItemSetText ( note_handle,
               "Type",
               "Person",
               MAXWORD))
      {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (error = NSFItemSetText ( note_handle,
               "FirstName",
               "Charles",
               MAXWORD))
      {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (error = NSFItemSetText ( note_handle,
               "LastName",
               last_name,
               MAXWORD))
      {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (error = NSFItemSetText ( note_handle,
               "MailDomain",
               "NOTES",
               MAXWORD))
      {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (error = NSFItemSetText ( note_handle,
               "MailFile",
               "MAIL\\CCONNELL",
               MAXWORD))
      {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Write the new note to disk and close the note. */

   if (error = NSFNoteUpdate (note_handle, 0))
      {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (error = NSFNoteClose (note_handle))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* End of big loop that is adding records. */

   }

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&LastTime);
 
   time_delta= TimeDateDifference (&LastTime, &StartTime);
 
   printf ("It took %i seconds to add %i names with no index usage at all\n", time_delta, transactions/3);

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&StartTime);

/* ************************************************** */
/* Open the index on names. */
/* ************************************************** */

   if (error = NIFFindView (db_handle, "Contacts", &view_id))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (error = NIFOpenCollection(
         db_handle,      /* handle of db with view */
         db_handle,      /* handle of db with data */
         view_id,     /* note id of the view */
         0,        /* collection open flags */
         NULLHANDLE,     /* handle to unread ID list (input and return) */
         &coll_handle,      /* collection handle (return) */
         NULLHANDLE,     /* handle to open view note (return) */
         NULL,        /* universal note id of view (return) */
         NULLHANDLE,     /* handle to collapsed list (return) */
         NULLHANDLE))       /* handle to selected list (return) */
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&LastTime);

   time_delta= TimeDateDifference (&LastTime, &StartTime);
 
   printf ("It took %i seconds to index Contacts view\n", time_delta);


/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&StartTime);

/* ************************************************** */
/* Find even numbered records in the index and modify them. */
/* ************************************************** */

/* Start a big loop that will modify many records. */

   for (i=0; i<(transactions/3); i++)
   {

/* Construct a last name. */

   strcpy (last_name, "Connell");
   sprintf(count, "%i ", i);
   strcat (last_name, count);
   strcat (last_name,", Charles");

/* Look in the index for this name. */

   error = NIFFindByName (
          coll_handle,       /* collection to look in */
          last_name,         /* string to match on */
          FIND_CASE_INSENSITIVE,   /* match rules */
          &coll_pos,         /* where match begins (return) */
          &match_size);      /* how many match (return) */

   if (ERR(error) == ERR_NOT_FOUND) 
      {
      printf ("\nKey %s not found in the collection.\n",last_name);
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (NOERROR);
      }
   
   if (error)
      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Get the note IDs of all records with this key. */

   if (error = NIFReadEntries(
      coll_handle,      /* handle to this collection */
      &coll_pos,        /* where to start in collection */
      NAVIGATE_CURRENT,       /* order to use when skipping */
      0L,                  /* number to skip */
      NAVIGATE_NEXT,       /* order to use when reading */
      match_size,          /* max number to read */
      READ_MASK_NOTEID,       /* info we want */
      &buffer_handle,      /* handle to info (return)   */
      NULL,          /* length of buffer (return) */
      NULL,          /* entries skipped (return) */
      &notes_found,     /* entries read (return) */
      NULL))            /* signal and share warnings (return) */

      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (buffer_handle == NULLHANDLE)
      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      printf ("\nEmpty buffer returned by NIFReadEntries.\n");
      LAPI_RETURN (NOERROR);
      }

   id_list = (NOTEID *) OSLockObject (buffer_handle);

/* Open the first note with this key. */

   if (error = NSFNoteOpen (db_handle, id_list[0], 0, &note_handle))
      {
      OSUnlockObject (buffer_handle);
      OSMemFree (buffer_handle);
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Get rid of the buffer of note IDs since we don't need it anymore. */

   OSUnlockObject (buffer_handle);
   OSMemFree (buffer_handle);

/* Modify one of the fields in this note. */

   if (error = NSFItemSetText ( note_handle,
                                "FirstName",
                                "Janet",
                                MAXWORD))
      {
      NIFCloseCollection (coll_handle);
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Update the on-disk copy of the note and close it. */

   if (error = NSFNoteUpdate (note_handle, 0))
      {
      NIFCloseCollection (coll_handle);
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (error = NSFNoteClose (note_handle))
      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* End of big loop that is modifying many records. */

   }

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&LastTime);
 
   time_delta= TimeDateDifference (&LastTime, &StartTime);
 
   printf ("It took %i seconds to modify %i records \n", time_delta, transactions/3);

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&StartTime);

/* ************************************************** */
/* Rebuild the index. */
/* ************************************************** */

   if (error = NIFUpdateCollection(coll_handle))
      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&LastTime);
 
   time_delta= TimeDateDifference (&LastTime, &StartTime);
 
   printf ("It took %i seconds to rebuild the index \n", time_delta);

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&StartTime);

/* ************************************************** */
/* Find odd numbered records in the index and delete them. */
/* ************************************************** */

/* Start a big loop that will delete many records. */

   for (i=0; i<(transactions/3); i++)
   {

/* Construct a last name. */

   strcpy (last_name, "Connell");
   sprintf(count, "%i ", i);
   strcat (last_name, count);
   strcat (last_name,", Janet");

/* Look in the index for this name. */

   error = NIFFindByName (
          coll_handle,       /* collection to look in */
          last_name,         /* string to match on */
          FIND_CASE_INSENSITIVE,   /* match rules */
          &coll_pos,         /* where match begins (return) */
          &match_size);      /* how many match (return) */

   if (ERR(error) == ERR_NOT_FOUND) 
      {
      printf ("\nKey not found in the collection.\n");
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (NOERROR);
      }
   
   if (error)
      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Get the note IDs of all records with this key. */

   if (error = NIFReadEntries(
          coll_handle,      /* handle to this collection */
          &coll_pos,        /* where to start in collection */
          NAVIGATE_CURRENT,       /* order to use when skipping */
          0L,                  /* number to skip */
          NAVIGATE_NEXT,       /* order to use when reading */
          match_size,          /* max number to read */
          READ_MASK_NOTEID,       /* info we want */
          &buffer_handle,      /* handle to info (return)   */
          NULL,          /* length of buffer (return) */
          NULL,          /* entries skipped (return) */
          &notes_found,     /* entries read (return) */
          NULL))         /* signal and share warnings (return) */

      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

   if (buffer_handle == NULLHANDLE)
      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      printf ("\nEmpty buffer returned by NIFReadEntries.\n");
      LAPI_RETURN (NOERROR);
      }

   id_list = (NOTEID *) OSLockObject (buffer_handle);

/* Delete the first note with this key. */

   if (error = NSFNoteDelete (db_handle, id_list[0], 0))
      {
      OSUnlockObject (buffer_handle);
      OSMemFree (buffer_handle);
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Get rid of the buffer of note IDs. */

   OSUnlockObject (buffer_handle);
   OSMemFree (buffer_handle);

/* End of big loop that is deleting many records. */

   }

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&LastTime);
 
   time_delta= TimeDateDifference (&LastTime, &StartTime);
 
   printf ("It took %i seconds to delete %i records \n", time_delta, transactions/3);

/* ************************************************** */
/* Close the index. */
/* ************************************************** */

   if (error = NIFCloseCollection (coll_handle))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* ************************************************** */
/* Close the database */
/* ************************************************** */

   if (error = NSFDbClose (db_handle))
      LAPI_RETURN (ERR(error));

/* ************************************************** */
/* End of subroutine. */
/* ************************************************** */

   LAPI_RETURN (NOERROR);
}
