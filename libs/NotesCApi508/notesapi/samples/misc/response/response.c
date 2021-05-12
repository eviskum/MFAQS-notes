/****************************************************************************

    PROGRAM:    response

    FILE:       response.c

    SYNTAX:     response  <dbpath_name>  "subject text"

    PURPOSE:    Shows how to create a response documents in a database.

    DESCRIPTION:
        Given an existing database and a text value for a subject field,
        this creates three notes in the database. The first is a Main
        document and has form name = "Document". The second is a response
        to the first, and has form name = "Response".  The third is a 
        response to the response and has form name = "ResponseToResponse".

****************************************************************************/

/* C include files */

#include <stdio.h>
#include <string.h>

#if defined(OS400)
#include <stdlib.h>
#endif

#if !defined(MAC) && !defined(OS400)
#include <malloc.h>
#endif

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <stdnames.h>
#include <nsf.h>
#include <misc.h>
#include <editods.h>
#include <oserr.h>

#include <lapiplat.h>

/* Function prototypes */
STATUS LNPUBLIC AddNewNote(DBHANDLE db_handle, char *form_name,
                     char *text_value, NOTEID *note_id_ptr);

STATUS LNPUBLIC MakeNoteResponse (DBHANDLE db_handle, NOTEID main_nid,
                                         NOTEID resp_nid);
										 
void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                               char *dbpath_name, char *subject); 

/************************************************************************

    FUNCTION:   NotesMain

    PURPOSE:    Main Lotus C API for Domino and Notes subroutine

    ALGORITHM:
    1)  Parse the command line into the separate variables and open the
        target database.
    2)  Call AddNewNote(), a local routine, three times, to create three
        new documents to the database.
    3)  Call MakeNoteResponse(), a local routine, to make the second
        document a response to the first.
    4)  Call MakeNoteResponse() again, this time to make the third
        document a response to the second.
    5)  Close the database and return.   

*************************************************************************/
LAPI_MAIN
{
    DBHANDLE 	db_handle;
    NOTEID  	note_id1,
            	note_id2,
            	note_id3;
    STATUS  	error = NOERROR;
    char    	*dbpath_name,
            	*subject;
    char 	thePath[MAXPATH];
    char	theSubject[MAXSPRINTF];
    char    	resp_subject[MAXSPRINTF] = "A Response to: ";
    char    	resp_resp_subject[MAXSPRINTF] = "Another Response to: ";


    LAPI_INIT(error);
    if (error)
      LAPI_INIT_ERROR;

    /* Parse the command line into the separate variables and open the
       target database.
    */

    dbpath_name = thePath;
    subject  = theSubject;
    ProcessArgs(argc, argv, dbpath_name, subject); 
	
    /*    Open the database */
    if (error = NSFDbOpen (dbpath_name, &db_handle))
    {
        LAPI_RETURN(ERR(error));
    }

    /*  
    Call AddNewNote(), a local routine, to add the first document, the
    response note and the response to the response. This section only 
    adds the notes; the relationship of one note to another is created 
    later by MakeNoteResponse(). Each call to AddNewNote() yields the
    noteID of the note it creates.
    */   

    /* Create Main note */
    if (error = AddNewNote(db_handle, "Document", subject, &note_id1))
    {
        NSFDbClose(db_handle);
        LAPI_RETURN (error);
    }

    /* Create Another note - soon to be a response note */

    strcpy(&resp_subject[strlen(resp_subject)], subject);

    if (error = AddNewNote(db_handle, "Response", resp_subject, 
                            &note_id2))
    {
        NSFDbClose(db_handle);
        LAPI_RETURN (error);
    }

    /* Create Another note - soon to be a response to a response */

    strcpy(&resp_resp_subject[strlen(resp_resp_subject)],
            resp_subject);

    if (error = AddNewNote(db_handle, "ResponseToResponse",
                              resp_resp_subject,&note_id3))
    {
        NSFDbClose(db_handle);
        LAPI_RETURN (error);
    }

    /* Call MakeNoteResponse() to make the note identified by note_id2 
       a response to the note identified by note_id1. MakeNoteResponse()
       is a local routine that creates a response reference list item and
       appends this item to the response note. This item establishes the
       relationship of the response note to the main note.
    */

    if (error = MakeNoteResponse(db_handle, note_id1, note_id2))
    {
        NSFDbClose(db_handle);
        LAPI_RETURN (error);
    }

    /*  Make the third note a response note to the second */
    if (error = MakeNoteResponse(db_handle, note_id2, note_id3))
    {
        NSFDbClose(db_handle);
        LAPI_RETURN (error);
    }

    /* Close the database and LAPI_RETURN. */
    error = NSFDbClose(db_handle);

	/* Let the user know it's done */
	
    printf("\nDone.\n"); 
    fflush(stdout);

    if (error == NOERROR)
      printf("\nProgram completed successfully.\n");

    LAPI_RETURN (ERR(error));
}

/************************************************************************

    FUNCTION:   AddNewNote

    PURPOSE:    Creates a new note in the database and LAPI_RETURN the Note ID.

    INPUTS:     takes a database handle, form name, and subject value.

    OUTPUTS:    LAPI_RETURNs the Note ID of the new note to *note_id_ptr.

*************************************************************************/

STATUS LNPUBLIC AddNewNote(DBHANDLE db_handle, char *form_name,
                             char *text_value, NOTEID *note_id_ptr)
{
    NOTEHANDLE note_handle;
    STATUS     error = NOERROR;
    char       *text_item_name = "Subject";

    /* Create a new note and get a handle to it */
    if (error = NSFNoteCreate (db_handle, &note_handle))
    {
        return(ERR(error));
    }

    /* Append the form name item to the new note */
    if (error = NSFItemSetText( note_handle,
                                FIELD_FORM,
                                form_name,
                                MAXWORD))
    {
        NSFNoteClose (note_handle);
        return(ERR(error));
    }

    /* Append the subject field to the new note */
    if (error = NSFItemSetText (note_handle, 
                                text_item_name,
                                text_value,
                                MAXWORD))
    {
        NSFNoteClose (note_handle);
        return(ERR(error));
    }

    /* Update the new note to disk. Then get the note ID of the new note.
       You must update before you get the note ID because the note ID 
       of a newly created note is zero until the first time it is updated 
       to disk.
    */
    if (error = NSFNoteUpdate (note_handle, 0))
    {
        NSFNoteClose (note_handle);
        return(ERR(error));
    }

    NSFNoteGetInfo (note_handle, _NOTE_ID, note_id_ptr);

    /* Close the new note */
    error = NSFNoteClose (note_handle);

    return(ERR(error));

}

/************************************************************************

    FUNCTION:   MakeNoteResponse

    PURPOSE:    Make the second note a response to the first

    INPUTS:
        db_handle  - handle to the open database containing both notes
        main_nid   - handle of note to be the main (parent) document
        resp_nid   - handle of note to be the response (child) document

    ALGORITHM:

    This function obtains the OID of the first note, and builds a 
    response reference list. A response reference list consists of a 
    LIST structure followed by the UNID of the main (parent) document.
    It appends this response reference list to the second note as a 
    field with name $REF and data type TYPE_NOTEREF_LIST. This $REF 
    field makes the second note into a response to the first note.

*************************************************************************/

STATUS LNPUBLIC MakeNoteResponse (DBHANDLE db_handle,
                                         NOTEID main_nid,
                                         NOTEID resp_nid)
{
    STATUS     error;
    OID        main_oid;
    TIMEDATE   lastmod_td;
    WORD       note_class;
    LIST       ListHdr;
    UNID       NoteUNID;
    NOTEHANDLE note_handle;
               /*  block of memory to hold the response reference list */
    char       *buf;

    buf = (char *) malloc(sizeof(LIST) + sizeof(UNID));
 
    if (buf == NULL)
    {
        printf ("malloc failed\n");
        return(ERR_MEMORY);
    }

    /* Get the OID (the ORIGINATORID) of the main (parent) document.
       NSFDbGetNoteInfo also yields the last modified time date and the 
       note class, but we do not need these values.
    */       
    if (error = NSFDbGetNoteInfo (db_handle, main_nid, &main_oid, 
                     &lastmod_td, &note_class))
    {
        return(ERR(error));
    }

    /* Initialize the LIST header part of the response reference list */
    ListHdr.ListEntries = (USHORT) 1;

    /* Initialize the UNID part of the response reference list */
    NoteUNID.File = main_oid.File; /* user-unique identifier */
    NoteUNID.Note = main_oid.Note; /* time/date when the note was created */

    /* Pack the LIST and the UNID members of the Noteref list into
       a memory block.
    */
    memcpy(buf, (char*)&ListHdr, sizeof(LIST));
    memcpy((buf+sizeof(LIST)), (char*)&NoteUNID, sizeof(UNID));

    /* Open the second note - the one to make into a response document. */
    if (error = NSFNoteOpen(db_handle, resp_nid, 0, &note_handle))
    {
        return(ERR(error));
    }

    /* Append the completed response reference list to the second note 
       as an item of type TYPE_NOTEREF_LIST.
    */
    if (error = NSFItemAppend ( note_handle, 
                                ITEM_SUMMARY,
                                FIELD_LINK,         /* $REF */
                                (WORD) strlen(FIELD_LINK),      
                                TYPE_NOTEREF_LIST,  /* data type */
                                buf,                /* populated RESPONSE */
                                (DWORD)(sizeof(LIST) + sizeof(UNID)) ))
    {
        NSFNoteClose(note_handle);
        return(ERR(error));
    }

    free(buf);

    /* Update the note  */
    if (error = NSFNoteUpdate(note_handle, 0))
    {
        NSFNoteClose(note_handle);
        return(ERR(error));
    }

    error = NSFNoteClose (note_handle);

    return(ERR(error));
}


/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    server_name - server name obtained from command line or
                              from prompt.
                db_name -     database name obtained from command line or
                              from prompt.

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *server_name, char *db_name)
{ 
#ifndef MAC
    if (argc != 3)  
    {
#endif

        printf("Enter database name: ");      
        fflush (stdout);
        gets(server_name);
	     printf("\n");
        printf ("Enter subject text:  ");
        fflush (stdout);
        gets(db_name);

#ifndef MAC
    }    
    else
    {
        strcpy(server_name, argv[1]);    
        strcpy(db_name, argv[2]);    
    } /* end if */
#endif
} /* ProcessArgs */
