/****************************************************************************

    PROGRAM:    onecat

    FILE:       onecat.c

    SYNTAX:     onecat  <db filename>  <view name>  <category (text)>

    DESCRIPTION:
        This program finds all the main-topic documents in a view category.
        We assume that the category is a main (left-most) category with 
        a text data type.

****************************************************************************/


/* C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nif.h>
#include <osmem.h>
#include <miscerr.h>

#include <lapiplat.h>


void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                         char *db_filename, 
                         char *view_name, 
                         char *category); 
						 
#define  STRING_LENGTH  256

/************************************************************************

    FUNCTION:   Main/NotesMain

    PURPOSE:    Lotus C API for Domino and Notes subroutine

*************************************************************************/

LAPI_MAIN
{


/* Local constants */

#define     CATEGORY_LEVEL_BEING_SEARCHED 0
#define  MAIN_TOPIC_INDENT    0

/* Local data declarations */

   char     db_filename[STRING_LENGTH];            /* pathname of the database */
   char     view_name[STRING_LENGTH];              /* name of the view we'll read */
   char     category[STRING_LENGTH];               /* category to search for in view */
   DBHANDLE db_handle;               			   /* handle of the database */
   NOTEID      view_id;              			   /* note id of the view */
   HCOLLECTION coll_handle;          			   /* collection handle */
   COLLECTIONPOSITION cat_index;     			   /* index of category entry */
   HANDLE      buffer_handle;        			   /* handle to buffer of info */
   BYTE     *buff_ptr;               			   /* pointer into info buffer */
   NOTEID      entry_id;             			   /* a collection entry id */
   WORD     entry_indent;            			   /* "indent level" of entry */
   WORD     entry_index_size;        			   /* size of index postion */
   COLLECTIONPOSITION entry_index;   			   /* an index position */
   DWORD     entries_found;          			   /* number of entries found */
   DWORD   main_topics_found=0; 				   /* number of main docs found */
   DWORD   i;                       		 	   /* a counter */
   STATUS      error;                			   /* return status from API calls */
   WORD     signal_flag;              			   /* signal and share warning flags */
   BOOL     FirstTime = TRUE;        			   /* used in NIFReadEntries loop */


    /*   Start by calling Notes Init.  */

    LAPI_INIT(error);
    if (error)
      LAPI_INIT_ERROR;

/* Get the command line parameters that the user entered. */

   ProcessArgs (argc, argv, 
             db_filename, view_name, category);
			 
/* Open the database. */

   if (error = NSFDbOpen (db_filename, &db_handle))
      LAPI_RETURN (ERR(error));

/* Get the note id of the view we want. */

   if (error = NIFFindView (db_handle, view_name, &view_id))
      {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
      }

/* Get the current collection using this view. */

   if (error = NIFOpenCollection(
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

/* Look for the given category (which must be of type text). We get back a 
COLECTIONPOSITION describing where the first document in the category is. 
Ignore the "match count" that this call returns, since it does not span 
subcategories. */

   error = NIFFindByName (
          coll_handle,             /* collection to look in */
          category,                /* string to match on */
          FIND_CASE_INSENSITIVE,   /* match rules */
          &cat_index,              /* where match begins (return) */
          NULL);                   /* how many match (return) */

   if (ERR(error) == ERR_NOT_FOUND) 
      {
      printf ("\nCategory not found in the collection.\n");
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

/*
Starting at the first doc in this category, get a buffer with information
about all the remaining entries in the collection. For each entry get the
following pieces of info: note ID, "indent level", and position in the
collection tree. The information is returned in a packed buffer.

In the returned buffer, first comes all of the info about the first entry,
then all of the info about the 2nd entry, etc. For each entry, the info is
arranged in the order of the bits in the READ_MASKs.
*/

   do
      {
      if (error = NIFReadEntries(
             coll_handle,            /* handle to this collection */
             &cat_index,             /* where to start in collection */
             FirstTime ? NAVIGATE_CURRENT : NAVIGATE_NEXT,
                                     /* order to use when skipping */
             FirstTime ? 0L : 1L,    /* number to skip */
             NAVIGATE_NEXT,          /* order to use when reading */
             0xFFFFFFFF,             /* max number to read */
             READ_MASK_NOTEID +      /* info we want */
             READ_MASK_INDENTLEVELS +
             READ_MASK_INDEXPOSITION,
             &buffer_handle,         /* handle to info buffer (return)  */
             NULL,                   /* length of info buffer (return) */
             NULL,                   /* entries skipped (return) */
             &entries_found,         /* entries read (return) */
             &signal_flag))          /* signal and share warnings (return) */
         {
         NIFCloseCollection (coll_handle);
         NSFDbClose (db_handle);
         LAPI_RETURN (ERR(error));
         }
 
/* Check to make sure there was a buffer of information returned. (This
is just for safety, since we know that the category exists and therefore
has some documents in it.) */ 

      if (buffer_handle == NULLHANDLE)
         {
         NIFCloseCollection (coll_handle);
         NSFDbClose (db_handle);
         printf ("\nEmpty buffer returned by NIFReadEntries.\n");
         LAPI_RETURN (NOERROR);
         }

/* Lock down (freeze the location) of the information buffer. Cast
the resulting pointer to the type we need. */

      buff_ptr = (BYTE *) OSLockObject (buffer_handle);

/* Start a loop that extracts the info about each collection entry from
the information buffer. */

      printf ("\n");
      for (i = 1; i <= entries_found; i++)
         {

/* Get the ID of this entry. */

         entry_id = *(NOTEID*) buff_ptr;
         buff_ptr += sizeof (NOTEID);

/* Get the "indent level" of this entry. For category entries, the indent
level is only used in multi-level columns (multiple levels of categories
within one column). For note entries, the indent level tells whether the
note is a main topic, response, response to response, etc. */

         entry_indent = *(WORD*) buff_ptr;
         buff_ptr += sizeof (WORD);

/* Find the size of this entry's index information. Each entry's index
info may be a different length, since it is truncated just to the length
needed. */

         entry_index_size = COLLECTIONPOSITIONSIZE
               ((COLLECTIONPOSITION*) buff_ptr);

/* Get the COLLECTIONPOSITION of the entry. */

         memcpy (&entry_index, buff_ptr, entry_index_size);
         buff_ptr += entry_index_size;

/* If this entry is a top-level category, then we have found all the notes
in the category we want. (We will have reached the next major category.) */

         if (entry_index.Level == CATEGORY_LEVEL_BEING_SEARCHED)
             {
             /* Indicate that there is no more to do. */
             signal_flag &= ~SIGNAL_MORE_TO_DO;
             break;
             }

/* If this entry is a lower-level category, skip over it. */

         if (NOTEID_CATEGORY & entry_id) continue;

/* If this entry is a response doc (or response to response, etc) skip
over it. */

         if (entry_indent != MAIN_TOPIC_INDENT) continue;

/* We have found a main-topic note. Print out its note ID. */

         printf ("Main topic count is: %lu.  \tNote ID is: %lX.\n",
                  ++main_topics_found, entry_id);

/* End of loop that gets info about each entry. */

         }

/* Unlock the list of note IDs. */

      OSUnlockObject (buffer_handle);

/* Free the memory allocated by NIFReadEntries. */

      OSMemFree (buffer_handle);
      if (FirstTime)
         FirstTime = FALSE;

      }  while (signal_flag & SIGNAL_MORE_TO_DO);

/* Close the collection. */

   if (error = NIFCloseCollection(coll_handle))
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
   
    OUTPUTS:    db_filename, view_name, category get data
                from the command line or from what the user types
                at a prompt 

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                         char *db_filename, 
                         char *view_name, 
                         char *category)
{ 
#ifndef MAC
    if (argc != 4)
    {       
#endif
      
      printf("Enter name of input database: ");   
      fflush(stdout);
      gets(db_filename);
           
      printf("\n");
      printf("Enter name of view to use: ");
      fflush(stdout);
      gets(view_name);

      printf("\n");
      printf("Enter name of category to select: ");      
      fflush(stdout);
      gets(category);

#ifndef MAC
   }  
   else
    {
      strcpy(db_filename, argv[1]);
      strcpy(view_name, argv[2]);
      strcpy(category, argv[3]);      
    } /* end if */
#endif
} /* ProcessArgs */
