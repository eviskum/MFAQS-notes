/****************************************************************************

    PROGRAM:    easyrich

    FILE:       easyrich.c

    SYNTAX:     easyrich 

    PURPOSE:    Demonstrate CompoundText functions for creating rich text.

    DESCRIPTION:
        This creates a new data note in the specified database and 
        fills in the rich text field of this note using the CompoundText
        routines, including CompoundTextCreate, CompoundTextAddTextExt,
        CompoundTextAddDocLink, and CompoundTextAddRenderedNote.

****************************************************************************/

/* C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <editods.h>
#include <editdflt.h>
#include <stdnames.h>
#include <ostime.h>
#include <easycd.h>
#include <fontid.h>
#include <colorid.h>
#include <osmem.h>
#include <nif.h>

#include <lapiplat.h>

#define DBNAME   "richtext.nsf"
#define VIEWNAME "RichTextView"

/* Local function prototypes */
STATUS AddMiscText (HANDLE);
STATUS FindFirstNoteInfo (DBHANDLE, ORIGINATORID *, NOTEID *, short *);
STATUS AssimilateTextFromNote (DBHANDLE, NOTEID, HANDLE);
STATUS AddDocLink(DBHANDLE, NOTEID, ORIGINATORID, HANDLE);
STATUS AddRenderedNote(DBHANDLE, NOTEID, HANDLE);

/************************************************************************

    FUNCTION:   main or NotesMain C API for Domino and Notes subroutine

    PURPOSE:    Create a new note and append data to the rich text field.

    ALGORITHM:
        Open the target database
        Create a new note 
        Append Form field to the new note
        Append TIME_DATE field to the new note
        Create the CompoundText (CD) context
        Add text and paragraphs to the CompoundText context
        Find info about an "old" note that already exists in the database
        Assimilate the rich text field from the old note into the CD context
        Create a Doc Link in the CD context that point to the old note
        Add a rendered note from the old note to the CD context
        Close the CompoundText context, thereby adding it to the new note
        Update the new note, adding it to the database
        Close the new note
        Close the database

*************************************************************************/

LAPI_MAIN
{
    STATUS      nErr = NOERROR; /* return code from API calls */
    DBHANDLE    hDB;            /* database handle */
    NOTEHANDLE  hNote;          /* note handle */
    TIMEDATE    timedate;       /* a time/date field */
    HANDLE      hCompound;      /* handle to CompoundText context */
    ORIGINATORID ViewOID;       /* OID of view note */
    short       NoteFound;      /* indicates whether a data note exists */
    NOTEID      FirstNoteID;    /* note id of first data note */


    LAPI_INIT(nErr)
    if (nErr)
        LAPI_INIT_ERROR;
    
   /* Open the database. */
    if ( (nErr = NSFDbOpen (DBNAME, &hDB)) != NOERROR )
    {
        printf( "Error: unable to open database, %s.\n", DBNAME);
        LAPI_RETURN (ERR(nErr));
    }
   
   /* Create a new data note. */

    if ( (nErr = NSFNoteCreate (hDB, &hNote)) != NOERROR )
    {
        printf( "Error: unable to create new document in database.\n" );
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Write a field named FORM to the note -- this field specifies the
      default form to use when the note is displayed. */

    nErr = NSFItemSetText( hNote, 
                    FIELD_FORM, /*  "Form" */
                    "RichTextForm",
                    MAXWORD );

    if (nErr != NOERROR)
    {
        printf( "Error: unable to set text in item '%s'.\n", FIELD_FORM );
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Get the current time/date and write it to a field named TIME_DATE. */

    OSCurrentTIMEDATE(&timedate);

    if ( (nErr = NSFItemSetTime (hNote, "TIME_DATE", &timedate)) != NOERROR )
    {
        printf( "Error: unable to set time in item 'TIME_DATE'.\n" );
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* The next several sections of code create and write a rich-text field
      using the CompoundText routines. */

   /* Create the CompoundText context */
    nErr = CompoundTextCreate (
                hNote,        /* handle of note */
                "RICH_TEXT",  /* item name */
                &hCompound);  /* returned handle to CompoundText context */

    if (nErr != NOERROR)
    {
        printf( "Error: unable to create CompoundText context for 'RICH_TEXT'.\n" );
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Add text and paragraphs to the CompoundText context */
    nErr = AddMiscText(hCompound);

    if (nErr != NOERROR)
    {
        CompoundTextDiscard (hCompound);
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Find info about the first data note in this database.  Use this info
      to assimilate text from the rich text field of this note into the 
      CompoundText context. 
    */

    nErr = FindFirstNoteInfo (hDB, &ViewOID, &FirstNoteID, &NoteFound);

    if (nErr != NOERROR)
    {
        CompoundTextDiscard (hCompound);
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Add the rich text field of the first document in this database to the
      CompoundText Context */

    if (NoteFound)
        nErr = AssimilateTextFromNote (hDB, FirstNoteID, hCompound);

    if (nErr != NOERROR)
    {
        printf("Error: unable to assimilate text from note.\n");
        CompoundTextDiscard (hCompound);
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Use the info about the first data note in this database to create
      a Doc Link that points to the first note in this database and add
      this Doc Link to the Compound Text context. 
    */

    if (NoteFound)
        nErr = AddDocLink (hDB, FirstNoteID, ViewOID, hCompound);

    if (nErr != NOERROR)
    {
        CompoundTextDiscard (hCompound);
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }


   /* Add rendered Note to the CompoundText context. */
    if (NoteFound)
      nErr = AddRenderedNote(hDB, FirstNoteID, hCompound);

    if (nErr != NOERROR)
    {
        printf("Error: unable to add rendered note to text context.\n");
        CompoundTextDiscard (hCompound);
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }


   /* Add the CompoundText context to the note. Since this is an ItemContext
      (associated with the newly created note), only specify hCompound 
      parameter */

    nErr = CompoundTextClose (
                hCompound,            /* handle to CompoundText context */
                NULL,                    
                NULL,
                NULL,
                0);

    if (nErr != NOERROR)
    {
        printf("Error: unable to close compound text context.\n");
        CompoundTextDiscard (hCompound);
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Add the new note to the database. */

    if ( (nErr = NSFNoteUpdate (hNote, 0)) != NOERROR )
    {
        printf("Error: unable to update new note to the database.\n");
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }
   /* Close the new note. */

    if ( (nErr = NSFNoteClose (hNote)) != NOERROR )
    {
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

    printf("\nNew note successfully created.\n");

   /* Close the database */

    if ( (nErr = NSFDbClose (hDB)) != NOERROR )
        LAPI_RETURN (ERR(nErr));

   /* End of subroutine. */
    printf("\nProgram completed successfully.\n");
    LAPI_RETURN (NOERROR);
}

/************************************************************************

    FUNCTION:    AddMiscText

    PURPOSE:     Demonstrates how to use CompoundTextAddTextExt() and
                 CompoundTextAddParaExt() routines.
    INPUTS:      
        hCompound - handle to a compound text context

    RETURNS:   
        NOERROR or status from API calls

*************************************************************************/

STATUS AddMiscText (HANDLE hCompound)
{
    STATUS nErr;    /* return code from API calls */
    char szText[] = "CompoundText Demonstration\n\n";
    char szPara1[] = "This is a demonstration of the compound text routines.";
    char szPara2[] = "Assimilated text follows:";
    COMPOUNDSTYLE   Style;
    DWORD           dwStyleID;
    FONTID          fid;
    FONTIDFIELDS   *fontfld;

   /* add szText to CompoundText context */

    CompoundTextInitStyle (&Style);    /* initializes Style to the defaults */

    nErr = CompoundTextDefineStyle (
                hCompound,          /* handle to CompoundText context */
                "",                 /* style name - none */
                &Style,
                &dwStyleID);        /* style id */
 
    if (nErr != NOERROR)
    {
        printf( "Error: unable to define CompoundText style no. 1.\n" );
        return (nErr);
    }

    nErr = CompoundTextAddTextExt (
                hCompound,              /* handle to CompoundText context */
                dwStyleID,              /* style ID */
                DEFAULT_BOLD_FONT_ID,   /* font ID */
                szText,                 /* text to add */
                (DWORD) strlen (szText),/* length of text */
                "\r\n",                 /* newline delimiter - handle \r \n 
                                         and combinations of \r\n */
                COMP_PRESERVE_LINES,    /* preserve line breaks */
                NULLHANDLE);            /* handle of CLS translation table */

    if (nErr != NOERROR)
    {
        printf( "Error: unable to Add text to CompoundText context .\n" );
        return (nErr);
    }
          
   /* Add szPara1 to the CompoundText context.
      Style is already set to the defaults. */

    nErr = CompoundTextDefineStyle (
                hCompound,              /* handle to CompoundText context */
                "Normal",               /* style name */
                &Style,
                &dwStyleID);            /* style id */

    if (nErr != NOERROR)
    {
        printf("Error: unable to define CompoundText style no. 2.\n");       
        return (nErr);
    }
   
    nErr = CompoundTextAddParagraphExt (
                hCompound,              /* handle to CompoundText context */
                dwStyleID,              /* style id */
                DEFAULT_FONT_ID,        /* font id */
                szPara1,                /* paragraph of text to add */
                (DWORD)strlen(szPara1), /* length of text to add */
                NULLHANDLE);            /* handle to CLS translation table */

    if (nErr != NOERROR)
    {
        printf("Error: unable to add paragraph to Comp Text context.\n");       
        return (nErr);
    }
   

   /* Add szPara2 to the CompoundText context.
      Style is already set to the defaults. */

    Style.LeftMargin = DEFAULT_LEFT_MARGIN + ONEINCH/2;
    Style.FirstLineLeftMargin = Style.LeftMargin;
    Style.ParagraphSpacingBefore = DEFAULT_ABOVE_PAR_SPACING + 1;
   
    nErr = CompoundTextDefineStyle (
                hCompound,              /* handle to CompoundText context */
                "",                     /* no style name */
                &Style,
                &dwStyleID);            /* style id */

    if (nErr != NOERROR)
    {
        printf("Error: unable to define compound text style no.3\n");
        return (nErr);
    }
   

   /* Customize the font by casting a pointer to FONTID to a pointer to 
      FONTIDFIELDS and filling in the individual members */

    fontfld = (FONTIDFIELDS *)&fid;

    fontfld->PointSize = 18;
    fontfld->Color = NOTES_COLOR_RED;
    fontfld->Attrib = ISITALIC | ISBOLD;
    fontfld->Face = FONT_FACE_SWISS;

    nErr = CompoundTextAddParagraphExt (
                hCompound,              /* handle to CompoundText context */
                dwStyleID,              /* style id */
                fid,                    /* font id */
                szPara2,                /* paragraph of text to add */
                (DWORD)strlen(szPara2), /* length of text to add */
                NULLHANDLE);            /* handle to CLS translation table */

    if (nErr != NOERROR)
    {
        printf("Error: unable to add para to compound text context.\n");
    }

    return (nErr);
}

/************************************************************************

    FUNCTION:   FindFirstNoteInfo 

    PURPOSE:    Finds the view OID and note id of the first note in
                in the sample database.
    INPUTS:      
        hDB          - database handle

    OUTPUTS:     
        *pViewOID    - ViewOID of the view that contains the note
        *pNoteID     - Note ID
        *pNoteFound  - TRUE if a data note was found, otherwise FALSE
 
    RETURNS:   
        NOERROR or error status from API calls

*************************************************************************/

STATUS FindFirstNoteInfo (DBHANDLE hDB, ORIGINATORID *pViewOID, 
                          NOTEID *pNoteID, short *pNoteFound)
{
    STATUS nErr;                    /* return code from API calls */
    HCOLLECTION hCollection;        /* handle to a collection */
    NOTEID ViewNoteID;              /* view note id */
    NOTEHANDLE hViewNote;           /* view note handle */
    COLLECTIONPOSITION IndexPos;    /* position of entry in view */
    DWORD dwEntriesRet;             /* number entries in view    */
    HANDLE hBuffer;

    *pNoteFound = FALSE;

   /* Use NIFOpenCollection and NIFReadEntries to find the first
      note in the collection. */

    nErr = NIFFindView (hDB, VIEWNAME, &ViewNoteID);
    if (nErr != NOERROR)
    {
        printf("Error: unable to find view '%s' in database.\n", VIEWNAME);
        return (nErr);
    }
   
   /* Get the handle to the view note */
    nErr = NSFNoteOpen (hDB, ViewNoteID, 0, &hViewNote);
    if (nErr != NOERROR)
    {
        printf("Error: unable to open view note.\n");
        return (nErr);
    }

   /* Get the OID from the view note - used for the Doc Link */
    NSFNoteGetInfo (hViewNote, _NOTE_OID, pViewOID);

   /* Close the view note */
    nErr = NSFNoteClose(hViewNote);
    if (nErr != NOERROR)
    {
        printf("Error: unable to close view note.\n");
        return (nErr);
    }
   

    nErr = NIFOpenCollection (hDB, hDB, ViewNoteID, 0, NULLHANDLE, 
                             &hCollection, NULL, NULL, NULL, NULL);

    if (nErr != NOERROR)
    {
        printf("Error: unable to open collection.\n");
        return (nErr);
    }
   

    IndexPos.Level = 0;
    IndexPos.Tumbler[0] = 1;
    nErr = NIFReadEntries (hCollection, &IndexPos, NAVIGATE_CURRENT,
                          0, NAVIGATE_NEXT, MAXWORD - 1,
                          READ_MASK_NOTEID, &hBuffer, NULL, NULL,
                          &dwEntriesRet, NULL);
    if (nErr != NOERROR)
    {
        printf("Error: unable to read entries in collection.\n");
        return (nErr);
    }
   

    if (hBuffer != NULLHANDLE)
    {
        NOTEID *entry;
        DWORD i;

        entry = OSLock(NOTEID, hBuffer);

        for (i = 0; i < dwEntriesRet; i++, entry++)
        {
            /* skip this noteID if it is for a category entry */
            if (*entry & NOTEID_CATEGORY)
                continue;
         
            /* data note was found */
            *pNoteFound = TRUE;
            *pNoteID = *entry;
            break;
        }
        OSUnlockObject (hBuffer);
        OSMemFree(hBuffer);
    }
    else
    {
        printf("no entries in view.\n");
    }

    return (NOERROR);
}
 
/************************************************************************

    FUNCTION:   AssimilateTextFromNote 

    PURPOSE:    Demonstrates how to use CompoundTextAssimilateItem() to 
                copy a rich text field of one note to another.
    INPUTS:      
        hDB       - database handle
        IDNote    - note id of the note to assimilate the text from
        hCompound - handle to a compound text context

    RETURNS:   
        NOERROR or error status from API calls

*************************************************************************/

STATUS AssimilateTextFromNote (DBHANDLE hDB, NOTEID IDNote, HANDLE hCompound)
{
    STATUS nErr;                      /* return code from API calls */
    NOTEHANDLE hOldNote;

   /* open the note */
    nErr = NSFNoteOpen (hDB, IDNote, 0, &hOldNote);
    if (nErr != NOERROR)
    {
        printf("Error: unable to open note to assimilate text from.\n");
        return (nErr);
    }
   

   /* Add the "RICH_TEXT" field to the CompoundText context */
    nErr = CompoundTextAssimilateItem (
                hCompound,              /* handle to CompoundText context */
                hOldNote,               /* handle to note */
                "RICH_TEXT",            /* field name */
                0L);                    /* reserved */

    if (nErr != NOERROR)
    {
        printf("Error: unable to assimilate text from item into context.\n");
        return (nErr);
    }
   
   /* Close the note. */

    NSFNoteClose (hOldNote);
    return (nErr);
}

/************************************************************************

    FUNCTION:   AddDocLink 

    PURPOSE:    Demonstrates how to use CompoundTextAddDocLink to
                insert a DocLink into a CompoundTextContext

    INPUTS:      
    hDB       - handle to database that contains the note pointed to by 
                the Doc Link
    hCompound - handle to a compound text context
    IDNote    - ID of the note pointed to by the Doc Link
    ViewOID   - OID of view that contains the note pointed to by the 
                Doc Link

    RETURNS:   
        NOERROR or error status from API calls

*************************************************************************/

STATUS AddDocLink (DBHANDLE hDB, NOTEID IDNote, 
                   ORIGINATORID ViewOID, HANDLE hCompound)
{
    STATUS nErr;                    /* return code from API calls */
    NOTEHANDLE hOldNote;
    ORIGINATORID OldNoteOID;        /* OID of note Doc Link points to */
    DBREPLICAINFO DBReplica;        /* DB Replica of DB containing the
                                      note that the Doc Link points to. */
    UNID ViewUNID;                  /* UNID of view containing the
                                      note that the Doc Link points to -
                                      obtained from OID of view note. */
    UNID OldNoteUNID;               /* UNID of note that the Doc Link
                                      points to - obtained from note's 
                                      OID. */
   /* open the note */
    nErr = NSFNoteOpen (hDB, IDNote, 0, &hOldNote);
    if (nErr != NOERROR)
    {
        printf("Error: unable to open note identified by doc link.\n");
        return (nErr);
    }
   

   /* Get the OID from the note */
    NSFNoteGetInfo (hOldNote, _NOTE_OID, &OldNoteOID);

   /* Close the note. */
    NSFNoteClose (hOldNote);

   /* Get the Database replica - used for the Doc Link */
    nErr = NSFDbReplicaInfoGet (hDB, &DBReplica);
    if (nErr != NOERROR)
    {
        printf("Error: unable to get replia info from database.\n");
        return (nErr);
    }
   

   /* Use the View OID and Note OID to fill in the UNID
      structures used in CompoundTextAddDocLink */
    ViewUNID.File = ViewOID.File;
    ViewUNID.Note = ViewOID.Note;

    OldNoteUNID.File = OldNoteOID.File;
    OldNoteUNID.Note = OldNoteOID.Note;

   /* Add the DocLink to the CompoundText context */

    nErr = CompoundTextAddDocLink (
                hCompound,          /* handle to CompoundText context */
                DBReplica.ID,       /* DB Replica ID */
                ViewUNID,
                OldNoteUNID,
                "Doc Link to first Note",/* comment to appear when DocLink
                                            is selected. */
                0L);                /* reserved */

    if (nErr != NOERROR)
    {
        printf("Error: unable to add doc link to Compound Text context.\n");
    }
       
    return (nErr);
}


/************************************************************************

    FUNCTION:    AddRenderedNote

    PURPOSE:     Demonstrates how to use CompoundTextAddRenderedNote() and
                 CompoundTextAddTextExt() routines.
    INPUTS:      
        hDB       - handle to database
        NOTEID    - original note id
        hCompound - handle to a compound text context

    RETURNS:   
        NOERROR or status from API calls

*************************************************************************/

STATUS AddRenderedNote (DBHANDLE hDB, NOTEID IDNote, HANDLE hCompound)
{
    STATUS nErr;    /* return code from API calls */
    char szText[] = "\n\nThis is a demonstration of a rendered Note being added to the compound text.";
    COMPOUNDSTYLE   Style;
    DWORD           dwStyleID;
    NOTEHANDLE      hOldNote;
   
  /* open the note */
    nErr = NSFNoteOpen (hDB, IDNote, 0, &hOldNote);
    if (nErr != NOERROR)
    {
        printf("Error: unable to open note\n");
        return (nErr);
    }
   

   /* add szText to CompoundText context */

    CompoundTextInitStyle (&Style);    /* initializes Style to the defaults */

    nErr = CompoundTextDefineStyle (
                hCompound,          /* handle to CompoundText context */
                "",                 /* style name - none */
                &Style,
                &dwStyleID);        /* style id */
 
    if (nErr != NOERROR)
    {
        printf( "Error: unable to define CompoundText style no. 1.\n" );
        return (nErr);
    }

    nErr = CompoundTextAddTextExt (
                hCompound,              /* handle to CompoundText context */
                dwStyleID,              /* style ID */
                DEFAULT_FONT_ID,        /* font id */
                szText,                 /* text to add */
                (DWORD) strlen (szText),/* length of text */
                "\r\n",                 /* newline delimiter - handle \r \n 
                                         and combinations of \r\n */
                COMP_PRESERVE_LINES,    /* preserve line breaks */
                NULLHANDLE);            /* handle of CLS translation table */

    if (nErr != NOERROR)
    {
        printf( "Error: unable to Add text to CompoundText context .\n" );
        return (nErr);
    }
          

   /* add rendered note to CompoundText context */

    nErr = CompoundTextAddRenderedNote(
                hCompound, hOldNote, NULLHANDLE, 0);

    if (nErr != NOERROR)
    {
        printf( "Error: unable to Add rendered note to CompoundText context .\n" );
        return (nErr);
    }

   /* Close the note. */

    NSFNoteClose (hOldNote);
    
    return (nErr);
}

