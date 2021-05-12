/****************************************************************************

    PROGRAM:    r_usrdef

    FILE:       r_usrdef.c

    SYNTAX:     r_usrdef  <db filename>

    PURPOSE:    shows how to read a user-defined field in a document

    DESCRIPTION:
        This program finds all the documents that have a certain 
        user-defined field, then reads the contents of that field.

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
#include <nsfsearc.h>
#include <osmem.h>
#include <nsferr.h>

#include <lapiplat.h>

/* Local include files */

#include "user_def.h"


/* Function prototypes */

STATUS LNPUBLIC find_my_data (void *, SEARCH_MATCH *, ITEM_TABLE *);


/* Main Lotus C API for Domino and Notes routine */

LAPI_MAIN
{

    /* Local data declarations */
    char        *db_filename;   /* pathname of source database */
    DBHANDLE    db_handle;      /* handle of source database */
    char        ascii_formula[MAX_ASCII_FORMULA]; /* an ASCII selection formula */
    FORMULAHANDLE    compiled_formula;  /* a compiled selection formula */
    WORD        dc;             /* a word we don't care about */
    STATUS      error;          /* return status from API calls */
    STATUS      formula_error;  /* error in formulas */

    LAPI_INIT(error);
    if (error)
      LAPI_INIT_ERROR;

    /* Allocate memory for an input database path */
    db_filename = (char *) malloc(STRING_LENGTH);
    if (db_filename == NULL)
    {
        printf("Error: Out of memory.\n");
        LAPI_RETURN (NOERROR);
    }

    /* Get the pathname of the database. */
    ProcessArgs(argc, argv, db_filename);

    /* Open the database. */
    if (error = NSFDbOpen (db_filename, &db_handle))
    {
        free(db_filename);
        LAPI_RETURN (ERR(error));
    }

    /* Write an ASCII selection formula. */
    strcpy (ascii_formula, "@IsAvailable(");
        strcat (ascii_formula, MY_FIELD_NAME);
        strcat (ascii_formula, ")");

    /* Compile the selection formula. */
    error = NSFFormulaCompile (
        NULL,                   /* name of formula (none) */
        0,                      /* length of name */
        ascii_formula,          /* the ASCII formula */
        strlen(ascii_formula),  /* length of ASCII formula */
        &compiled_formula,      /* handle of compiled formula */
        &dc,                    /* compiled formula length */
        &formula_error,         /* error code from compile */
        &dc, &dc, &dc, &dc);    /* compile error info (don't care) */

    /* If there was an error in the formula, return that error. If there
    was some other kind of error (unlikely) return that instead. */
    if (ERR(error) == ERR_FORMULA_COMPILATION)
    {
        NSFDbClose (db_handle);
        free(db_filename);
        LAPI_RETURN (ERR(formula_error));
    }

    if (error)
    {
        NSFDbClose (db_handle);
        free(db_filename);
        LAPI_RETURN (ERR(error));
    }

    /* Call NSFSearch to find the notes that match the selection criteria.
    For each note found, the routine print_fields is called. (If you always
    want to find all the documents in the database, you can set the 2nd
    argument to NULLHANDLE and eliminate the formula compilation.) */

    if (error = NSFSearch (
        db_handle,              /* database handle */
        compiled_formula,       /* selection formula */
        NULL,                   /* title of view in selection formula */
        0,                      /* search flags */
        NOTE_CLASS_DATA,        /* note class to find */
        NULL,                   /* starting date (unused) */
        find_my_data,           /* action routine */
        &db_handle,             /* argument to action routine */
        NULL))                  /* returned ending date (unused) */

    {
        OSMemFree (compiled_formula);
        NSFDbClose (db_handle);
        free(db_filename);
        LAPI_RETURN (ERR(error));
    }

    /* Free the memory allocated to the compiled formula. */

    OSMemFree (compiled_formula);

    /* Close the database. */
    if (error = NSFDbClose (db_handle))
    {
        free(db_filename);
        LAPI_RETURN (ERR(error));
    }

    /* Free the the allocated space for database name*/

    free(db_filename);

    /* End of main routine. */

    LAPI_RETURN (NOERROR);
}





/* Action routine called by NSFSearch for each note that matches
the search criteria. */


STATUS LNPUBLIC find_my_data
            (void *db_handle, 
            SEARCH_MATCH far *pSearchMatch,
            ITEM_TABLE *summary_info)
{
    SEARCH_MATCH    SearchMatch;
    NOTEHANDLE      note_handle;
    BLOCKID         item_block;     /* block ID of whole field */
    BLOCKID         value_block;    /* block ID of field data */
    WORD            item_type;      /* Domino and Notes data type of field */
    DWORD           value_len;      /* length of field data */
    BYTE            *item_ptr;      /* pointer to field data */

    char  type_descrip[MAX_USER_DESCRIP]; /* user-define type description */
    BYTE            descrip_len; /* length of user-defined type description */
    BYTE            user_data[MAX_USERDEF_FIELD]; /* user-defined data */
    WORD            user_data_len;  /* length of user-defined data */
    unsigned int    i;
    STATUS          error;          /* return code from API calls */


    memcpy( (char*)&SearchMatch, (char*)pSearchMatch, sizeof(SEARCH_MATCH) );

    /* Skip this note if it does not really match the search criteria (it is
    now deleted or modified).  This is not necessary for full searches,
    but is shown here in case a starting date was used in the search. */

    /* if (SearchMatch.MatchesFormula != SE_FMATCH) V3 */
    if (!(SearchMatch.SERetFlags & SE_FMATCH))     /* V4 */
        return (NOERROR);

    /* Print the note ID. */

    printf ("\n\n***** Note ID is: %lX. *****\n", SearchMatch.ID.NoteID);

    /* Open the note. */

    if (error = NSFNoteOpen (
            *(DBHANDLE*)db_handle,  /* database handle */
            SearchMatch.ID.NoteID, /* note ID */
            0,                      /* open flags */
            &note_handle))          /* note handle (return) */
        
        return (ERR(error));

    /* Get the block ID of the field we are interested in. */

    error = NSFItemInfo (
            note_handle,
            MY_FIELD_NAME, strlen(MY_FIELD_NAME),
            &item_block, &item_type,
            &value_block, &value_len);

    if (ERR(error) == ERR_ITEM_NOT_FOUND)
    {
        printf ("\nField %s was NOT found in this note.\n", MY_FIELD_NAME);
        NSFNoteClose (note_handle);
        return (NOERROR);
    }

    if (error)
    {
        NSFNoteClose (note_handle);
        return (error);
    }

    /* Tell the user that we found the field. */

    printf ("\nField %s was found in this note.\n", MY_FIELD_NAME);

    /* Convert the BLOCKID of the field value into a memory pointer. We will
    advance this pointer as we extract the parts of the field. */

    item_ptr = OSLockBlock (BYTE, value_block);

    /* Skip over the Domino and Notes data type that is stored at the front of the field
    data. */

    item_ptr += sizeof (WORD);

    /* Get the length of the user-defined type description. It is stored in
    the first byte of the field's data. */

    descrip_len = *item_ptr;
    item_ptr++;

    /* Extract the user-defined type description string and print it out. */

    memcpy (type_descrip, item_ptr, descrip_len);
    item_ptr += descrip_len;

    type_descrip[descrip_len] = '\0';
    printf ("\nType description string is: %s.\n", type_descrip);

    /* Figure out the length of the user-defined data. This length is the
    total length of the Domino and Notes field, minus the two-byte data type at the
    front of the field, minus the one-byte size of the type descriptor
    string, minus the length of the descriptor. */

    user_data_len = ((WORD) value_len) - (sizeof(WORD) + 1 + descrip_len);

    /* Extract the data and print it out in hex. */

    memcpy (user_data, item_ptr, user_data_len);

    printf ("\nData is: ");
    for (i=0; i<user_data_len; i++) printf ("%X", user_data[i]);
    printf ("\n");

    /* Unlock the memory block holding this field. */

    OSUnlockBlock (value_block);

    /* Close the note. */

    if (error = NSFNoteClose (note_handle))
        return (ERR(error));

    /* End of subroutine. */

    return (NOERROR);

}
