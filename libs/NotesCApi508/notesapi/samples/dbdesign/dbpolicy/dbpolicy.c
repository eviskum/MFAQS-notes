/****************************************************************************

    PROGRAM:    dbpolicy

    FILE:       dbpolicy.c

    SYNTAX:     dbpolicy  <database name>

    PURPOSE:    Shows how to create Help-About and Help-Using documents

    DESCRIPTION:
        This program creates a new database policy document (Help-About 
        Database document) and a new database help document (Help-Using 
        Database document) and fills in some rich text for each.

****************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <osmem.h>
#include <easycd.h>
#include <fontid.h>
#include <editdflt.h>
#include <colorid.h>
#include <nsferr.h>

#include <lapiplat.h>

#define POLICY_DOC 1
#define HELP_DOC 2

#define POLICY_STRING1 "DATABASE POLICY STATEMENT"
#define HELP_STRING1   "DATABASE HELP STATEMENT"
#define  STRING_LENGTH  256

#define POLICY_STRING2 "This is a sample policy document \
(Help-About Database document) for the API sample program, DBPOLICY."
#define HELP_STRING2   "This is a sample help document \
(Help-Using Database document) for the API sample program, DBPOLICY."

/* Function prototypes */

STATUS LNPUBLIC print_doc (DBHANDLE, NOTEID);
STATUS add_rich_text (short, NOTEHANDLE);
void  LNPUBLIC  ProcessArgs (int argc, char *argv[], char *db_name); 

/************************************************************************

    FUNCTION:   NotesMain/Main

    PURPOSE:    Lotus C API for Domino and Notes subroutine

*************************************************************************/

LAPI_MAIN
{

/* Local data declarations */

   char          path_name[STRING_LENGTH];       /* pathname of database */
   DBHANDLE      db_handle;        				 /* database handle */
   NOTEHANDLE    note_handle;      				 /* note handle */
   STATUS        error;            				 /* return code from API calls */
   int           note_class_value; 				 /* set to NOTE_CLASS_INFO - policy doc */
   NOTEID        note_ID;          				 /* to read the policy and help docs */

   LAPI_INIT(error);
   if (error)
		LAPI_INIT_ERROR;


/* Get the command line parameters that the user entered. */
    ProcessArgs(argc, argv, path_name); 


/* Initialize the paragraph definition blocks used in the rich text fields
   of the database policy document and of the database help document */

/* Open the database. */

   if (error = NSFDbOpen (path_name, &db_handle))
      LAPI_RETURN (ERR(error));

/* Exit program if either a database policy document exists or a 
   database help document exists */

   error = NSFDbGetSpecialNoteID (db_handle, 
                                  SPECIAL_ID_NOTE | NOTE_CLASS_INFO,
                                  &note_ID);
   if (error != ERR_SPECIAL_ID)
   {
      if (error == NOERROR)
      {
         printf ("A database policy document (Help-About document) exists ");
         printf ("in this database.\n");
         printf ("Program will not attempt to create any documents.\n");
         NSFDbClose (db_handle);
      }
      LAPI_RETURN(ERR(error));
   }

   error = NSFDbGetSpecialNoteID (db_handle, 
                                  SPECIAL_ID_NOTE | NOTE_CLASS_HELP,
                                  &note_ID);
   if (error != ERR_SPECIAL_ID)
   {
      if (error == NOERROR)
      {
         printf ("A database help document (Help-Using document) exists ");
         printf ("in this database.\n");
         printf ("Program will not attempt to create any documents.\n");
         NSFDbClose (db_handle);
      }
      LAPI_RETURN(ERR(error));
   }

/* Create a new note for the database policy document. */

   if (error = NSFNoteCreate (db_handle, &note_handle))
   {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Specify in the note header that this note is a database policy document */

   note_class_value = NOTE_CLASS_INFO | NOTE_CLASS_DEFAULT;

   NSFNoteSetInfo (note_handle, _NOTE_CLASS, &note_class_value);

   error = add_rich_text (POLICY_DOC, note_handle);

   if (error != NOERROR)
   {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Add the new note to the database. */

   if (error = NSFNoteUpdate (note_handle, 0))
   {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Close the new note. */

   if (error = NSFNoteClose (note_handle))
   {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Create a new note for the database help document */

   if (error = NSFNoteCreate (db_handle, &note_handle))
   {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Specify in the note header that this note is a database help document */

   note_class_value = NOTE_CLASS_HELP | NOTE_CLASS_DEFAULT;

   NSFNoteSetInfo (note_handle, _NOTE_CLASS, &note_class_value);

   error = add_rich_text (HELP_DOC, note_handle);

   if (error != NOERROR)
   {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Add the new note to the database. */

   if (error = NSFNoteUpdate (note_handle, 0))
   {
      NSFNoteClose (note_handle);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Close the new note. */

   if (error = NSFNoteClose (note_handle))
   {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Now open and print out the database policy document and the database
   help document */

/* Use NSFDbGetSpecialNoteID to get the note ID of the policy doc */

   if (error = NSFDbGetSpecialNoteID (db_handle, 
                                      SPECIAL_ID_NOTE | NOTE_CLASS_INFO,
                                      &note_ID))
   {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

   if (error = print_doc (db_handle, note_ID))
   {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

/* Use NSFDbGetSpecialNoteID to get the note ID of the help doc */

   if (error = NSFDbGetSpecialNoteID (db_handle, 
                                      SPECIAL_ID_NOTE | NOTE_CLASS_HELP,
                                      &note_ID))
   {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

   if (error = print_doc (db_handle, note_ID))
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


/************************************************************************

    FUNCTION:   add_rich_text

    PURPOSE:    adds rich text to the $BODY field of a database policy 
                document or database help document.

*************************************************************************/

STATUS add_rich_text (short doc_type, NOTEHANDLE note_handle)
{
   HANDLE hCompound;          /* handle to CompoundText context */
   STATUS error;
   char *header;              /* Doc header text */
   char *text;                /* Doc text */
   COMPOUNDSTYLE Style;
   DWORD         dwStyleID;
   FONTID        fid;
   FONTIDFIELDS    *fontfld;

   switch (doc_type)
   {
      case POLICY_DOC:
         header = POLICY_STRING1;
         text = POLICY_STRING2;
         break;

      case HELP_DOC:
         header = HELP_STRING1;
         text = HELP_STRING2;
         break;

      default:
         header = "DOC HEADER";
         text = "Text for the doc.";
         break;
   }

   if (error = CompoundTextCreate (note_handle, "$BODY", &hCompound))
      return (error);

   /* Add the header text for the document */

   CompoundTextInitStyle (&Style);    /* initializes Style to the defaults */

   Style.JustifyMode = JUSTIFY_CENTER;

   error = CompoundTextDefineStyle (
               hCompound,          /* handle to CompoundText context */
               "",                 /* style name - none */
               &Style,
               &dwStyleID);        /* style id */
 
   if (error != NOERROR)
   {
      CompoundTextDiscard (hCompound);
      return (error);
   }

   fontfld = (FONTIDFIELDS *)&fid;

   fontfld->PointSize = 14;
   fontfld->Color = NOTES_COLOR_BLUE;
   fontfld->Attrib = ISBOLD;
   fontfld->Face = FONT_FACE_SWISS;

   error = CompoundTextAddParagraphExt (
             hCompound,               /* handle to CompoundText context */
             dwStyleID,               /* style id */
             fid,                     /* font id */
             header,                  /* paragraph of text to add */
             (DWORD)strlen(header),   /* length of text to add */
             NULLHANDLE);             /* handle to CLS translation table */

   if (error != NOERROR)
   {
      CompoundTextDiscard (hCompound);
      return (error);
   }

   /* Add the text for the document */
   
   CompoundTextInitStyle (&Style);    /* initializes Style to the defaults */
   error = CompoundTextDefineStyle (
             hCompound,          /* handle to CompoundText context */
             "Normal",           /* style name */
             &Style,
             &dwStyleID);        /* style id */

   if (error != NOERROR)
   {
      CompoundTextDiscard (hCompound);
      return (error);
   }

   fontfld->PointSize = 12;
   fontfld->Color = NOTES_COLOR_RED;
   fontfld->Attrib = ISBOLD | ISITALIC;
   fontfld->Face = FONT_FACE_SWISS;

   error = CompoundTextAddParagraphExt (
             hCompound,               /* handle to CompoundText context */
             dwStyleID,               /* style id */
             fid,                     /* font id */
             text,                    /* paragraph of text to add */
             (DWORD)strlen(text),     /* length of text to add */
             NULLHANDLE);             /* handle to CLS translation table */

   if (error != NOERROR)
   {
      CompoundTextDiscard (hCompound);
      return (error);
   }

   /* Add the CompoundText context to the note */

   error = CompoundTextClose (
             hCompound,            /* handle to CompoundText context */
             NULL,                    
             NULL,
             NULL,
             0);

   if (error != NOERROR)
      CompoundTextDiscard (hCompound);

   return (ERR(error));

}

/************************************************************************

    FUNCTION:   print_doc

    PURPOSE:    prints out the policy and help documents

*************************************************************************/

STATUS LNPUBLIC print_doc (
         DBHANDLE db_handle, 
         NOTEID note_ID) 
{


/* Local data declarations. */

   NOTEHANDLE  note_handle;
   char        field_text[500];
   BLOCKID     field_block;
   DWORD       field_length, text_length;
   WORD        field_type;
   HANDLE      text_buffer;
   char        *text_ptr;
   STATUS      error;
   

/* Print the note ID. */

   printf ("\n\n       ************* Note ID is: %lX. *************\n", 
      note_ID);

/* Open the note. */

   if (error = NSFNoteOpen (
         db_handle,              /* database handle */
         note_ID,                /* note ID */
         0,                      /* open flags */
         &note_handle))          /* note handle (return) */
      
      return (ERR(error));

/* Look for the $BODY field within the note. This function tells us
whether the field is there, and if present, its location (BLOCKID) 
within Domino and Notes' memory. Check the return code for "field not 
found" versus a real error. */

   error = NSFItemInfo (
         note_handle,      /* note handle */
         "$BODY",          /* field we want */
         strlen("$BODY"),  /* length of above */
         NULL,             /* full field (return) */
         &field_type,      /* field type (return) */
         &field_block,     /* field contents (return) */
         &field_length);   /* field length (return) */

   if (error)
   {
      if (ERR(error) == ERR_ITEM_NOT_FOUND)
         printf ("\n Error:  $BODY field not found \n");
      NSFNoteClose (note_handle);
      return (ERR(error));
   }

/* Extract only the text from the rich-text field into an ASCII string. */

   if (error = ConvertItemToText (
         field_block,   /* BLOCKID of field */
         field_length,  /* length of field */
         "\n",          /* line separator for output */
         60,            /* line length in output */
         &text_buffer,  /* output buffer */
         &text_length,  /* output length */
         TRUE))         /* strip tabs */
   {
      NSFNoteClose (note_handle);
      return (ERR(error));
   }

/* Lock the memory allocated for the text buffer. Cast the resulting 
pointer to the type we need. */

   text_ptr = (char *) OSLockObject (text_buffer);

/* Move the text from the text buffer into a character array and
append a null to it. (We do this so that we now have a regular C 
text string.) */

   memcpy (field_text, text_ptr, (short) text_length);
   field_text[text_length] = '\0';

/* Print the text of the $BODY field. */

   printf ("\nThe text in this document is:\n\n%s\n", field_text); 

/* Unlock and free the text buffer. */

   OSUnlockObject (text_buffer);
   OSMemFree (text_buffer);

/* Close the note. */

   if (error = NSFNoteClose (note_handle))
      return (ERR(error));

/* End of subroutine. */

    return (NOERROR);

}


/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    db_name -     database name obtained from command line or
                              from prompt.

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *db_name)
{ 
#ifndef MAC
    if (argc != 2)  
    {
#endif

        printf("Enter database name: ");      
        fflush (stdout);
        gets(db_name);
        printf("\n");

#ifndef MAC
    }    
    else
    {
        strcpy(db_name, argv[1]);    
    } /* end if */
#endif
} /* ProcessArgs */
