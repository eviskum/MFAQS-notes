/****************************************************************************

    PROGRAM:    w_usrdef

    FILE:       w_usrdef.c

    SYNTAX:     w_usrdef   <database filename>

    PURPOSE:    creates a field with a user-defined data type in a Domino and 
	            Notes document.

****************************************************************************/

/* C include files */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <ostime.h>

#include <lapiplat.h>

/* Local include files */

#include "user_def.h"


/* Lotus C API for Domino and Notes subroutine */

LAPI_MAIN
{

    /* Local data declarations */
    char           *path_name;                  /* pathname of database */
    DBHANDLE       db_handle;                   /* database handle */
    NOTEHANDLE     note_handle;                 /* note handle */
    TIMEDATE       timedate;                    /* contents of a time/date field */
    BYTE           my_field[MAX_USERDEF_FIELD]; /* field with custom data type */
    WORD           descrip_len;                 /* len of type description */
    WORD           my_field_len;                /* actual len of custom field */
    STATUS         error;                       /* return code from API calls */

    LAPI_INIT(error);
    if (error)
      LAPI_INIT_ERROR;

    /* Allocate memory for an input database path */
    path_name = (char *) malloc(STRING_LENGTH);
    if (path_name == NULL)
    {
        printf("Error: Out of memory.\n");
        LAPI_RETURN (NOERROR);
    }
 
    /* Get the pathname of the database. */
    ProcessArgs(argc, argv, path_name);

    /* Open the database. */
    if (error = NSFDbOpen (path_name, &db_handle))
    {
        free(path_name);   
        LAPI_RETURN (ERR(error));
    }

    /* Create a new data note. */
    if (error = NSFNoteCreate (db_handle, &note_handle))
    {
        NSFDbClose (db_handle);
        free(path_name);   
        LAPI_RETURN (ERR(error));
    }

    /* Write a field named FORM to the note -- this field specifies the
    default form to use when displaying the note. */
    if (error = NSFItemSetText ( note_handle, 
                    "Form",
                    "Form #1",
                    MAXWORD))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        free(path_name);   
        LAPI_RETURN (ERR(error));
    }

    /* Write a text field named PLAIN_TEXT to the note. */
    if (error = NSFItemSetText ( note_handle, 
                    "PLAIN_TEXT",
                    "This doc has a user-defined field.",
                    MAXWORD))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        free(path_name);   
        LAPI_RETURN (ERR(error));
    }

    /* Get the current time/date and write it to a field named TIME_DATE. */
    OSCurrentTIMEDATE(&timedate);

    if (error = NSFItemSetTime (note_handle, "TIME_DATE", &timedate))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        free(path_name);   
        LAPI_RETURN (ERR(error));
    }

    /* Create a field with a user-defined data type. */
    /* The first byte of the field is the length of the type description
    string. */

    descrip_len = strlen (MY_DATA_TYPE);
    my_field[0] = (BYTE) descrip_len;
    my_field_len = 1;

    /* Next comes the type description string. You may put whatever you want
    in this string. Its purpose is to allow you to distinguish between
    different user-defined data types. */

    memcpy (my_field+my_field_len, MY_DATA_TYPE, descrip_len);
    my_field_len += descrip_len;

    /* Next comes the actual data. Domino and Notes will make no attempt to 
	interpret the structure of this data or its meaning. (In this example, we 
	simply put some arbitrary hex numbers in the data.) */

    memset (my_field+my_field_len, 0xC3, MY_DATA_LEN);
    my_field_len += MY_DATA_LEN;

    /* Add the custom field to the note. We set the ITEM_SUMMARY flag so that
    the field can appear in a view selection formula or in an NSFSearch
    formula. */

    if (error = NSFItemAppend (note_handle, ITEM_SUMMARY,
                        MY_FIELD_NAME, strlen(MY_FIELD_NAME),
                        TYPE_USERDATA,
                        &my_field, my_field_len))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        free(path_name);   
        LAPI_RETURN (ERR(error));
    }

    /* Add the entire new note (with all fields) to the database. */

    if (error = NSFNoteUpdate (note_handle, 0))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        free(path_name);   
        LAPI_RETURN (ERR(error));
    }

    /* Close the note. (Remove its structure from memory.) */

    if (error = NSFNoteClose (note_handle))
    {
        NSFDbClose (db_handle);
        free(path_name);   
        LAPI_RETURN (ERR(error));
    }

    /* Close the database */

    if (error = NSFDbClose (db_handle))
        LAPI_RETURN (ERR(error));

    /* Free the the allocated space for database name*/

    free(path_name);   

    /* End of subroutine. */

    LAPI_RETURN (NOERROR);
}
