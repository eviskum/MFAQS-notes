/****************************************************************************

    PROGRAM:    navigate

    FILE:       navigate.c

    SYNTAX:     navigate  <database path>  <view name>

    DESCRIPTION:
        This program shows how to do complex navigation within a collection.

        The inputs are the name of a database, and the name of a view that 
        has two levels of categories.

        The program navigates in the collection to the 2nd major category, 
        then into the 2nd subcategory within this main category. The 
        program then prints the note IDs of the main-topic documents 
        (no response notes) within the subcategory.

****************************************************************************/

/* C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nif.h>
#include <osmem.h>
#include <pool.h>
#include <nsferr.h>
#include <niferr.h>
#include <miscerr.h>

#include <lapiplat.h>

/* Function prototypes */
void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                               char *db_name, char *view_name); 

#define  STRING_LENGTH  256

/* Main API routine. */

LAPI_MAIN
{


/* Local data declarations. */

   char     db_filename[STRING_LENGTH];	/* pathname of the database */
   DBHANDLE db_handle;               	/* handle of the database */
   char     view_name[STRING_LENGTH];	/* name of the view we'll use */
   NOTEID      view_id;              	/* note id of the view */
   HCOLLECTION coll_handle;          	/* collection handle */
   STATUS      error;                	/* return status from API calls */
   HANDLE      buffer_handle;        	/* handle to buffer of note ids */
   NOTEID      *id_list;             	/* pointer to a note id */
   DWORD    notes_found;             	/* number of notes found */
   COLLECTIONPOSITION coll_pos;      	/* position within collection */
   DWORD i;                          	/* a counter */
   DWORD note_count = 0;            	/* ordinal number of the note */
   WORD     signal_flag;             	/* signal and share warnings (return) */
   BOOL     FirstTime = TRUE;        	/* used in NIFReadEntries loop */


    LAPI_INIT(error);
    if (error)
      LAPI_INIT_ERROR;

/* Get the command line parameters that the user entered. */
    ProcessArgs(argc, argv, db_filename, view_name); 


/* Open the database. */

   if (error = NSFDbOpen (db_filename, &db_handle))
      LAPI_RETURN (ERR(error));

/* Get the note id of the view we want. */

   if (error = NIFFindView (db_handle, view_name, &view_id))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Get a collection of notes using this view. */

   if (error = NIFOpenCollection (
         db_handle,      /* handle of db with view */
         db_handle,      /* handle of db with data */
         view_id,        /* note id of the view */
         0,              /* collection open flags */
         NULLHANDLE,     /* handle to unread ID list (input and return) */
         &coll_handle,   /* collection handle (return) */
         NULLHANDLE,     /* handle to open view note (return) */
         NULL,           /* universal note id of view (return) */
         NULLHANDLE,     /* handle to collapsed list (return) */
         NULLHANDLE))    /* handle to selected list (return) */

      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Set up the data structure, COLLECTIONPOSITION, that controls where in
the collection we will begin when we read the collection.  Specify that we
want to start at the beginning. */

   coll_pos.Level = 0;
   coll_pos.Tumbler[0] = 1;

/* Skip to start of 2nd major category. */

   if (error = NIFReadEntries (
          coll_handle,         /* handle to this collection */
          &coll_pos,           /* where to start in collection */
          NAVIGATE_NEXT_PEER,  /* order to skip entries */
          1L,                  /* number to skip */
          NAVIGATE_CURRENT,    /* order to use after skipping */
          0L,                  /* max return number */
          0L,                  /* info we want */
          NULLHANDLE,          /* handle to info (return)   */
          NULL,                /* length of buffer (return) */
          NULL,                /* entries skipped (return) */
          &notes_found,        /* number of notes (return) */
          NULL))               /* share warning (return) */

      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Go down one level, into subcategories. */

   if (error = NIFReadEntries (
          coll_handle,         /* handle to this collection */
          &coll_pos,           /* where to start in collection */
          NAVIGATE_CHILD,      /* order to skip entries */
          1L,                  /* number to skip */
          NAVIGATE_CURRENT,    /* order to use after skipping */
          0L,                  /* max return number */
          0L,                  /* info we want */
          NULLHANDLE,          /* handle to info (return)   */
          NULL,                /* length of buffer (return) */
          NULL,                /* entries skipped (return) */
          &notes_found,        /* number of notes (return) */
          NULL))               /* share warning (return) */

      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Advance one subcategory. */

       if (error = NIFReadEntries (
          coll_handle,         /* handle to this collection */
          &coll_pos,           /* where to start in collection */
          NAVIGATE_NEXT_PEER,  /* order to skip entries */
          1L,                  /* number to skip */
          NAVIGATE_CURRENT,    /* order to use after skipping */
          0L,                  /* max return number */
          0L,                  /* info we want */
          NULLHANDLE,          /* handle to info (return)   */
          NULL,                /* length of buffer (return) */
          NULL,                /* entries skipped (return) */
          &notes_found,        /* number of notes (return) */
          NULL))               /* share warning (return) */

      {
      NIFCloseCollection (coll_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Go down into main topics level, then read all main topics. */


   do
      {
      if (error = NIFReadEntries (
             coll_handle,         /* handle to this collection */
             &coll_pos,           /* where to start in collection */
             FirstTime ? NAVIGATE_CHILD : NAVIGATE_NEXT_PEER,
                                  /* order to skip entries */
             1L,                  /* number to skip */
             NAVIGATE_NEXT_PEER,  /* order to use after skipping */
             0xFFFFFFFF,          /* max return number */
             READ_MASK_NOTEID,    /* info we want */
             &buffer_handle,      /* handle to info (return)   */
             NULL,                /* length of buffer (return) */
             NULL,                /* entries skipped (return) */
             &notes_found,        /* number of notes (return) */
             &signal_flag))       /* more flag and share warning (return) */

         {
         NIFCloseCollection (coll_handle);
         NSFDbClose (db_handle);
         LAPI_RETURN (ERR(error));
         }

/* Check to see if we received a valid buffer handle. (If we had run off
the end of the collection before doing the last read, we get back a
null handle.) */

      if (buffer_handle == NULLHANDLE)
         {
         NIFCloseCollection (coll_handle);
         NSFDbClose (db_handle);
         printf ("\nEmpty buffer returned by NIFReadEntries.\n");
         LAPI_RETURN (NOERROR);
         }
 
/* Lock down (freeze the location) of the buffer of notes IDs. Cast
the resulting pointer to the type we need. */

      id_list = (NOTEID *) OSLockObject (buffer_handle);
  
/* Print out the list of all the note IDs in this collection. Check
for IDs that indicate a category entry.  These are dummy note IDs
that don't point to a real note. */

      for (i=0; i<notes_found; i++)
          if (!(NOTEID_CATEGORY & id_list[i]))
             printf ("Note ID number %lu is: %lX\n", ++note_count, id_list[i]);

/* Unlock the list of note IDs. */

      OSUnlockObject(buffer_handle);

/* Free the memory allocated by NIFReadEntries. */

      OSMemFree (buffer_handle);
      if (FirstTime)
         FirstTime = FALSE;

      }  while (signal_flag & SIGNAL_MORE_TO_DO);


/* Close the collection. */

   if (error = NIFCloseCollection (coll_handle))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Close the database. */

   if (error = NSFDbClose (db_handle))
      LAPI_RETURN (ERR(error));

/* End of subroutine. */

   printf("\nProgram completed successfully.\n");

   LAPI_RETURN (NOERROR);
}


/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    db_name -     database name obtained from command line or
                              from prompt.
							 
				view_name -   name of the view to navigate

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *db_name, char *view_name)
{ 
#ifndef MAC
    if (argc != 3)  
    {
#endif

        printf("Enter database name: ");      
        fflush (stdout);
        gets(db_name);
        printf("\n");
        printf ("Enter view name:  ");
        fflush (stdout);
        gets(view_name);

#ifndef MAC
    }    
    else
    {
        strcpy(db_name, argv[1]);    
        strcpy(view_name, argv[2]);    
    } /* end if */
#endif
} /* ProcessArgs */


