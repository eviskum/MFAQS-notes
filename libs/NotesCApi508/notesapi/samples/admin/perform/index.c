/****************************************************************************

    PROGRAM:    index

    FILE:       index.c

    DESCRIPTION:  
        This program updates an index in a Notes database. The program can
        be used as a performance test, or to create an index for 
        other testing.

****************************************************************************/

/* OS and C include files */

#include <stdio.h>

/* Notes API include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nif.h>
#include <ostime.h>
#include <misc.h>

#include <lapiplat.h>

/* Notes API subroutine */

LAPI_MAIN
{


/* Local data declarations */

   char           *db_path;      /* pathname of database */
   char           *view_name;    /* name of view to update */

   DBHANDLE       db_handle;     /* database handle */
   HCOLLECTION    coll_handle;   /* collection handle */
   NOTEID         view_id;       /* note ID of the view note */

   STATUS         error;

   LONG           time_delta;
   TIMEDATE       StartTime;        /* time to mark the start of the program */
   TIMEDATE       LastTime;         /*  time to mark the end of the program */

/* Get the input parameters. */

   if (argc != 3)
      {
      printf ("\nUsage:  INDEX  <database pathname>  <name of view>\n");
      LAPI_RETURN (NOERROR);
      }
   db_path = argv[1];
   view_name = argv[2];

   printf ("\n***** INDEX Test Begins ******\n");

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&StartTime);

/* Open the database. */

   if (error = NSFDbOpen (db_path, &db_handle))
      LAPI_RETURN (ERR(error));

/* Find the note ID of the view note. */

   if (error = NIFFindView (db_handle, view_name, &view_id))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Open the view (thereby updating it). */

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

/* Close the index. */

   if (error = NIFCloseCollection (coll_handle))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Close the database */

   if (error = NSFDbClose (db_handle))
      LAPI_RETURN (ERR(error));

/* ************************************************** */
/* Get System TIME  . */
/* ************************************************** */
 
   OSCurrentTIMEDATE(&LastTime);

   time_delta= TimeDateDifference (&LastTime, &StartTime);
 
   printf ("It took %i seconds to index\n", time_delta);
 
/* End of subroutine. */

   LAPI_RETURN (NOERROR);
}
