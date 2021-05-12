/****************************************************************************

    PROGRAM:    addnames

    FILE:       addnames.c

    DESCRIPTION:  
        This program adds any number of unique names to a Domino and Notes Name 
        and Address book. The program may be used as its own performance 
        test or to pre-load a N&A book for other tests.

        NOTE: This program DOES NOT build any index (view) on the N&A
        book. It simply adds the names. You can use the companion program
        named INDEX to build an index in the N&A book.


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
#include <ostime.h>
#include <misc.h>

#include <lapiplat.h>

/* Lotus C API for Domino and Notes subroutine */

LAPI_MAIN
{


/* Local data declarations */

   char           *db_path;         /* pathname of test database */
   int            transactions;     /* total number of transactions */

   DBHANDLE       db_handle;        /* database handle */
   NOTEHANDLE     note_handle;      /* note handle */

   char           last_name[100];   /* last name in N&A book */
   char           count[10];        /* used to construct unique names */

   LONG           time_delta;
   TIMEDATE       StartTime;        /* time to mark the start of the program */
   TIMEDATE       LastTime;         /*  time to mark the end of the program */

   int            i;
   STATUS         error;


/* ************************************************** */
/* Get the input parameters. */
/* ************************************************** */

   if (argc != 3)
      {
      printf ("\nUsage:  ADDNAMES  <database pathname>  <number of names>\n");
      LAPI_RETURN (NOERROR);
      }
   db_path = argv[1];
   transactions = atoi(argv[2]);

   printf ("\n***** ADDNAMES Test Begins ******\n");

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */

   OSCurrentTIMEDATE(&StartTime);

/* ************************************************** */
/* Open the database. */
/* ************************************************** */

   if (error = NSFDbOpen (db_path, &db_handle))
      LAPI_RETURN (ERR(error));

/* ************************************************** */
/* Add new records, each with a different last name. */
/* ************************************************** */

/* Start a big loop for adding names. */

   for (i=0; i<transactions; i++)
   {

/* Construct the last name. */

   strcpy (last_name, "Smith");
   sprintf(count, "%i", i); /* itoa (i, count, 10); */
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
               "John",
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
               "MAIL\\JSMITH",
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
/* Close the database */
/* ************************************************** */

   if (error = NSFDbClose (db_handle))
      LAPI_RETURN (ERR(error));

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */

   OSCurrentTIMEDATE(&LastTime);

   time_delta= TimeDateDifference (&LastTime, &StartTime);

   printf ("It took %i seconds to add %i names\n", time_delta, transactions);

/* ************************************************** */
/* End of subroutine. */
/* ************************************************** */

   LAPI_RETURN (NOERROR);
}
