/****************************************************************************

    PROGRAM:    rrich

    FILE:       rrich.c

    SYNTAX:     rrich  <db filename>

    PURPOSE:    shows how to read the text within a rich-text field.

****************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsfsearc.h>
#include <ods.h>
#include <osmem.h>
#include <nsferr.h>
#include <odserr.h>

/* Function prototypes */

STATUS LNPUBLIC print_fields (void *, SEARCH_MATCH *, ITEM_TABLE *);

#define BUFSIZE 1000

/************************************************************************

    FUNCTION:   NotesMain

    PURPOSE:    Main Lotus C API for Domino and Notes routine

*************************************************************************/

STATUS LNPUBLIC NotesMain (int argc, char *argv[])
{

/* Local data declarations */

    char        *db_filename;   /* pathname of source database */
    DBHANDLE    db_handle;      /* handle of source database */
    char        *formula;       /* a note selection formula */
    FORMULAHANDLE    formula_handle; /* handle to compiled formula */
    STATUS        error;        /* return status from API calls */
    WORD        wdc;            /* a word we don't care about */


/* Get the command line parameters that the user entered. */

    if (argc != 2)
        {
        printf ("\nUsage:  RRICH  <db filename>  \n");
        return (NOERROR);
        }
    db_filename = argv[1];

/* Open the database. */

    if (error = NSFDbOpen (db_filename, &db_handle))
        return(error);

/* Write an ASCII selection formula. */

    formula = "@All";

/* Compile the selection formula. */

    if (error = NSFFormulaCompile (
        NULL,            /* name of formula (none) */
        0,            /* length of name */
        formula,        /* the ASCII formula */
        strlen(formula),    /* length of ASCII formula */
        &formula_handle,    /* handle to compiled formula */
        &wdc,            /* compiled formula length (don't care) */
        &wdc,             /* return code from compile (don't care) */
        &wdc, &wdc, &wdc, &wdc)) /* compile error info (don't care) */
        
        {
        NSFDbClose (db_handle);
        return (ERR(error));
        }

/* Call NSFSearch to find just the notes we want in the database. For each
note found, the routine print_fields is called. */

    if (error = NSFSearch (
        db_handle,        /* database handle */
        formula_handle,        /* selection formula */
        NULL,            /* title of view in selection formula */
        0,            /* search flags */
        NOTE_CLASS_DATA,    /* note class to find */
        NULL,            /* starting date (unused) */
        print_fields,        /* call for each note found */
        &db_handle,        /* argument to print_fields */
        NULL))            /* returned ending date (unused) */

        {
        NSFDbClose (db_handle);
        return (ERR(error));
        }

/* Free the memory allocated to the compiled formula. */

    OSMemFree (formula_handle);

/* Close the database. */

    if (error = NSFDbClose (db_handle))
        return (ERR(error));

/* End of main routine. */

    return (NOERROR);
}

/************************************************************************

    FUNCTION:   print_fields

    PURPOSE:    Action routine called by NSFSearch for each note found

    INPUTS:
        The first argument to this function is the optional argument
        that we supplied when we called NSFSearch.

        The second argument is supplied by NSFSearch.    It is
        a structure of information about the note that was found.

        The third argument is also supplied by NSFSearch and is
        the summary buffer for this note.

    COMMENTS:
        This is the routine that is called by NSFSearch for each note
        that matches the selection criteria.

*************************************************************************/

STATUS LNPUBLIC print_fields    
            (void *db_handle, 
            SEARCH_MATCH far *pSearchMatch,
            ITEM_TABLE *summary_info)
{

/* Local data declarations. */

    SEARCH_MATCH SearchMatch;
    NOTEHANDLE   note_handle;
    BOOL         field_found;
    char         field_text[BUFSIZE+1];
    BLOCKID      field_block;
    DWORD        field_length, text_length;
    WORD         field_type;
    HANDLE       text_buffer;
    char         *text_ptr;
    STATUS       error;
    

    memcpy( (char*)&SearchMatch, (char*)pSearchMatch, sizeof(SEARCH_MATCH) );

/* Skip this note if it does not really match the search criteria (it is
now deleted or modified).  This is not necessary for full searches,
but is shown here in case a starting date was used in the search. */

    if (!(SearchMatch.SERetFlags & SE_FMATCH))
        return (NOERROR);

/* Print the note ID. */

    printf ("\n\n       ************* Note ID is: %lX. *************\n", 
        SearchMatch.ID.NoteID);

/* Open the note. */

    if (error = NSFNoteOpen (
            *(DBHANDLE*)db_handle,  /* database handle */
            SearchMatch.ID.NoteID,  /* note ID */
            0,                      /* open flags */
            &note_handle))          /* note handle (return) */
        
        return (ERR(error));

/* Look for the RICH_TEXT field within the note. This function tells us
whether the field is there, and if present, its location (BLOCKID) 
within Domino and Notes' memory. Check the return code for "field not found" versus 
a real error. */

    error = NSFItemInfo (
            note_handle,        /* note handle */
            "RICH_TEXT",        /* field we want */
            strlen("RICH_TEXT"),    /* length of above */
            NULL,            /* full field (return) */
            &field_type,        /* field type (return) */
            &field_block,        /* field contents (return) */
            &field_length);        /* field length (return) */

    if (ERR(error) == NOERROR)
        field_found = TRUE;

    if (ERR(error) == ERR_ITEM_NOT_FOUND)
        {
        field_found = FALSE;
        error = NOERROR;
        }

    if (error)        
        {
        NSFNoteClose (note_handle);
        return (ERR(error));
        }

/* If the RICH_TEXT field is there, do the next few sections of code. */

    if (field_found)
        {

/* Extract only the text from the rich-text field into an ASCII string. */

        if (error = ConvertItemToText (
                field_block,    /* BLOCKID of field */
                field_length,    /* length of field */
                "\n",        /* line separator for output */
                60,        /* line length in output */
                &text_buffer,    /* output buffer */
                &text_length,    /* output length */
                TRUE))        /* strip tabs */

            {
            NSFNoteClose (note_handle);
            return (ERR(error));
            }

/* Lock the memory allocated for the text buffer. Cast the resulting 
pointer to the type we need. */

        text_ptr = (char *) OSLockObject (text_buffer);

/* Move the text from the text buffer into a character array,
truncate if necessary to fit the character array, and append a null
to it. (We do this so that we now have a regular C text string.) */

        text_length = (text_length > BUFSIZE ? BUFSIZE : text_length);
        memcpy (field_text, text_ptr, (short) text_length);
        field_text[text_length] = '\0';

/* Print the text of the RICH_TEXT field. */

        printf ("\nRICH_TEXT field is:\n\n%s\n", field_text); 

/* Unlock and free the text buffer. */

        OSUnlockObject (text_buffer);
        OSMemFree (text_buffer);
        } 

/* If the RICH_TEXT field is not there, print a message. */

    else
        printf ("\nRICH_TEXT field not found.\n"); 
        
/* Close the note. */

    if (error = NSFNoteClose (note_handle))
        return (ERR(error));

/* End of subroutine. */

    return (NOERROR);

}
