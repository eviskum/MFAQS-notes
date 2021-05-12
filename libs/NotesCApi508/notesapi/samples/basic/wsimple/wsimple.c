/*************************************************************************

    PROGRAM:   wsimple

    FILE:      wsimple.c 

    PURPOSE:   Shows how to create a new data note and fill in fields with
               the simple data types.

    SYNTAX:    wsimple

    COMMENTS:
        This program opens the specified database, creates a new data note,
        and fills in fields with the simple data types.

*************************************************************************/

/* OS and C include files */

#include <stdio.h>

/* Notes API include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <ostime.h>

#include <lapiplat.h>


/* Notes API subroutine */

LAPI_MAIN
{
    char        path_name[]="simple.nsf";   /* pathname of database */
    DBHANDLE    db_handle;          /* database handle */
    NOTEHANDLE  note_handle;        /* note handle */
    NUMBER      num_field;          /* contents of a numeric field */
    TIMEDATE    timedate;           /* contents of a time/date field */
    STATUS      error = NOERROR;    /* return code from API calls */
    
    
    LAPI_INIT(error);
    if (error)
        LAPI_INIT_ERROR;
  
  /* Open the database. */
    
    if (error = NSFDbOpen (path_name, &db_handle))
        LAPI_RETURN (ERR(error));
    
    /* Create a new data note. */
    
    if (error = NSFNoteCreate (db_handle, &note_handle))
    {
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Write a field named FORM to the note -- this field specifies the
       default form to use when displaying the note. */
    
    if (error = NSFItemSetText ( note_handle, 
                "FORM",
                "SimpleDataForm", 
                MAXWORD))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Write a text field named PLAIN_TEXT to the note. */
    
    if (error = NSFItemSetText ( note_handle, 
                "PLAIN_TEXT",
                "The quick brown fox jumped over the lazy dogs.",
                MAXWORD))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Write a field named NUMBER to the note. */
    
    num_field = 125.007;
    
    if (error = NSFItemSetNumber (note_handle, "NUMBER", &num_field))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Get the current time/date and write it to a field named TIME_DATE. */
    
    OSCurrentTIMEDATE(&timedate);
    
    if (error = NSFItemSetTime (note_handle, "TIME_DATE", &timedate))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Create a text-list field and add it to the note. */
    
    if (error = NSFItemCreateTextList ( note_handle, 
                       "TEXT_LIST",
                       "Charles", 
                       MAXWORD))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Add several items to the text-list field. */
    
    if (error = NSFItemAppendTextList ( note_handle, 
                       "TEXT_LIST",
                       "Janet", 
                       MAXWORD,
                       TRUE))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    if (error = NSFItemAppendTextList ( note_handle, 
                       "TEXT_LIST",
                       "Chuck", 
                       MAXWORD,
                       TRUE))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Add the entire new note (with all fields) to the database. */
    
    if (error = NSFNoteUpdate (note_handle, 0))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Close the note. (Remove its structure from memory.) */
    
    if (error = NSFNoteClose (note_handle))
    {
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    /* Close the database */
    
    if (error = NSFDbClose (db_handle))
        LAPI_RETURN (ERR(error));
    
    /* End of subroutine. */
    printf("\nProgram completed successfully.\n");
    LAPI_RETURN (NOERROR);
}

