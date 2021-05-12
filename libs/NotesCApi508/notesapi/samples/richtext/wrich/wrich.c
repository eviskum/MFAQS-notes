/****************************************************************************

    PROGRAM:    wrich

    FILE:       wrich.c

    SYNTAX:     wrich  <database filename>

    PURPOSE:    create a new data note and fill in a rich-text field.

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
#include <ods.h>
#include <editods.h>
#include <editdflt.h>
#include <colorid.h>
#include <ostime.h>

#include <lapiplat.h>

/************************************************************************

    FUNCTION:   NotesMain

*************************************************************************/

LAPI_MAIN
{

/* Local constants */
#define RT_STRING1 "This is a left-justified "
#define RT_STRING1_LEN (strlen(RT_STRING1))
#define RT_STRING2 "paragraph"
#define RT_STRING2_LEN (strlen(RT_STRING2))
#define RT_STRING3 "This is a centered paragraph"
#define RT_STRING3_LEN (strlen(RT_STRING3))
#define INPUT_LENGTH  256

/* Local type definitions */

/* Local data declarations */

    char        *path_name;             /* pathname of database */
    DBHANDLE    db_handle;              /* database handle */
    NOTEHANDLE  note_handle;            /* note handle */
    TIMEDATE    timedate;               /* a time/date field */
    STATUS      error;                  /* return code from API calls */

    CDPABDEFINITION     def1;                    /* paragraph style definition */
    CDPABDEFINITION     def2;                    /* paragraph style definition */
    CDPARAGRAPH         para1;                   /* paragraph header */
    CDPABREFERENCE      ref1;                    /* style reference for this para */
    CDTEXT              text1;                   /* text header */
    char                string1[] = RT_STRING1;  /* text run */
    WORD                wstring1Len = RT_STRING1_LEN;
    CDTEXT              text2;                   /* text header */
    char                string2[] = RT_STRING2;  /* text run */
    WORD                wstring2Len = RT_STRING2_LEN;
    CDPARAGRAPH         para2;                   /* paragraph header */
    CDPABREFERENCE      ref2;                    /* style reference for this para */
    CDTEXT              text3;                   /* text header */
    char                string3[] = RT_STRING3;  /* text run */
    WORD                wstring3Len = RT_STRING3_LEN;
    FONTIDFIELDS        *font;                   /* font definitions in text header */

    BYTE                *rt_field;      /* allocated rich-text field */
    BYTE                *buff_ptr;      /* position in allocated memory */
    WORD                wBuffLen;       /* required CD buffer length */
    DWORD               rt_size;        /* size of rich-text field */

/* Get the pathname of the database. */

    LAPI_INIT(error);
    if (error)
      LAPI_INIT_ERROR;

    path_name = (char *) malloc(INPUT_LENGTH);
    if (path_name == NULL)
       {
        printf("Error: Out of memory.\n");
        LAPI_RETURN (NOERROR);
       }

    if (argc != 2)
        {
        printf("Enter the database filename: ");
        fflush(stdout);
        gets(path_name);
        }
    else
        strcpy(path_name, argv[1]);

/* Open the database. */

    if (error = NSFDbOpen (path_name, &db_handle))
        LAPI_RETURN (ERR(error));

/* Through with database name. */

    free(path_name);

/* Create a new data note. */

    if (error = NSFNoteCreate (db_handle, &note_handle))
        {
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
        }

/* Write a field named FORM to the note -- this field specifies the
default form to use when the note is displayed. */

    if (error = NSFItemSetText ( note_handle,
                    "FORM",
                    "RichTextForm",
                    MAXWORD))
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

/*     The next several sections of code create and write a rich-text field.
       A rich-text field consists of a series of CD records. This field
       will contain two CDPABDEFINITION, two CDPARAGRAPH record, two
       CDPABRFERENCE, and 3 CDTEXT records. A CDTEXT record consists of a CDTEXT
       structure followed by run of text.

       Allocate a buffer to hold this series of CD records. To calculate the
       size of the buffer required, add up the ODS lengths of each of the CD
       records it will contain. The length of a CDTEXT record is the ODS
       length of the CDTEXT structure, plus the number of characters in the
       text run. Force the number of characters in each text run to be even.
       If the string length is odd, add one to the string length so that the
       record length is even. You must ensure that all CD records begin on
       even byte boundaries.
*/

    wstring1Len += (wstring1Len%2);
    wstring2Len += (wstring2Len%2);
    wstring3Len += (wstring3Len%2);

    wBuffLen =  ODSLength( _CDPABDEFINITION ) +
                ODSLength( _CDPABDEFINITION ) +
                ODSLength( _CDPARAGRAPH )     +
                ODSLength( _CDPABREFERENCE )  +
                ODSLength( _CDTEXT )          +
                wstring1Len                   +
                ODSLength( _CDTEXT )          +
                wstring2Len                   +
                ODSLength( _CDPARAGRAPH )     +
                ODSLength( _CDPABREFERENCE )  +
                ODSLength( _CDTEXT )          +
                wstring3Len                   ;

    rt_field = (BYTE *) malloc ( wBuffLen );

    if( rt_field == (BYTE *)NULL )
    {
        printf("Error: unable to allocate %d bytes memory.\n", wBuffLen);
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        LAPI_RETURN (NOERROR);
    }

/* Keep a pointer to our current position in the buffer. */

    buff_ptr = rt_field;

/* Fill in the paragraph definition blocks. We use all defaults in the first
and centered justification in the second. */

    memset(&def1, 0 , sizeof(CDPABDEFINITION));

    def1.Header.Signature = SIG_CD_PABDEFINITION;
    def1.Header.Length = ODSLength( _CDPABDEFINITION );
    def1.PABID = 1;
    def1.JustifyMode = DEFAULT_JUSTIFICATION;
    def1.LineSpacing = DEFAULT_LINE_SPACING;
    def1.ParagraphSpacingBefore = DEFAULT_ABOVE_PAR_SPACING;
    def1.ParagraphSpacingAfter = DEFAULT_BELOW_PAR_SPACING;
    def1.LeftMargin = DEFAULT_LEFT_MARGIN;
    def1.RightMargin = DEFAULT_RIGHT_MARGIN;
    def1.FirstLineLeftMargin = DEFAULT_FIRST_LEFT_MARGIN;
    def1.Tabs = DEFAULT_TABS;
    def1.Tab[0] = DEFAULT_TAB_INTERVAL;
    def1.Flags = 0;
    def1.TabTypes = TAB_DEFAULT;
    def1.Flags2 = 0;

    memset(&def2, 0 , sizeof(CDPABDEFINITION));

    def2.Header.Signature = SIG_CD_PABDEFINITION;
    def2.Header.Length = ODSLength( _CDPABDEFINITION );
    def2.PABID = 2;
    def2.JustifyMode = JUSTIFY_CENTER;
    def2.LineSpacing = DEFAULT_LINE_SPACING;
    def2.ParagraphSpacingBefore = DEFAULT_ABOVE_PAR_SPACING;
    def2.ParagraphSpacingAfter = DEFAULT_BELOW_PAR_SPACING;
    def2.LeftMargin = DEFAULT_LEFT_MARGIN;
    def2.RightMargin = DEFAULT_RIGHT_MARGIN;
    def2.FirstLineLeftMargin = DEFAULT_FIRST_LEFT_MARGIN;
    def2.Tabs = DEFAULT_TABS;
    def2.Tab[0] = DEFAULT_TAB_INTERVAL;
    def2.Flags = 0;
    def2.TabTypes = TAB_DEFAULT;
    def2.Flags2 = 0;

/*     Call ODSWriteMemory to convert the two CDPABDEFINITION structures
       to Domino and Notes canonical format and write the converted structure 
	   into the buffer at location buff_ptr. This advances buff_ptr to the
       next byte in the buffer after the canonical format strucure.
*/

    ODSWriteMemory( &buff_ptr, _CDPABDEFINITION, &def1, 1 );
    ODSWriteMemory( &buff_ptr, _CDPABDEFINITION, &def2, 1 );


/* Start a new paragraph. */

    para1.Header.Signature = SIG_CD_PARAGRAPH;
    para1.Header.Length = (BYTE) ODSLength( _CDPARAGRAPH );
    ODSWriteMemory( &buff_ptr, _CDPARAGRAPH, &para1, 1 );


/* Specify that this paragraph will use definition block #1 (above). */

    ref1.Header.Signature = SIG_CD_PABREFERENCE;
    ref1.Header.Length = (BYTE) ODSLength( _CDPABREFERENCE );
    ref1.PABID = 1;
    ODSWriteMemory( &buff_ptr, _CDPABREFERENCE, &ref1, 1 );


/* Start a run of text within this paragraph. */

    text1.Header.Signature = SIG_CD_TEXT;
    text1.Header.Length = ODSLength( _CDTEXT ) + RT_STRING1_LEN;

/* Fill in the font information for this run of text. Note that we set a
pointer to the FontID data item within the CDTEXT header. Then we use the
pointer to set the individual fields within the FontID. */

    font = ( FONTIDFIELDS * ) &(text1.FontID);

    font->Face = FONT_FACE_SWISS;
    font->Attrib = ISBOLD;
    font->Color = NOTES_COLOR_BLUE;
    font->PointSize = 24;

    ODSWriteMemory( &buff_ptr, _CDTEXT, &text1, 1 );

/* Fill in the actual text of this text run and advance buffer pointer. Do not
append a null to the text run. */

    memcpy( (char *)buff_ptr, string1, wstring1Len );
    buff_ptr += wstring1Len;

/* Start another run of text (within the same paragraph). */

    text2.Header.Signature = SIG_CD_TEXT;
    text2.Header.Length = ODSLength( _CDTEXT ) + RT_STRING2_LEN;

/* Fill in the font information for this run of text. Note that we set a
pointer to the FontID data item within the CDTEXT header. Then we use the
pointer to set the individual fields within the FontID. */

    font = ( FONTIDFIELDS * ) &(text2.FontID);

    font->Face = FONT_FACE_ROMAN;
    font->Attrib = ISITALIC;
    font->Color = NOTES_COLOR_RED;
    font->PointSize = 18;

    ODSWriteMemory( &buff_ptr, _CDTEXT, &text2, 1 );

/* Fill in the actual text of this text run. Do not append a null to the
text run. */

    memcpy( (char *)buff_ptr, string2, wstring2Len );
    buff_ptr += wstring2Len;

/* Start a new paragraph. */

    para2.Header.Signature = SIG_CD_PARAGRAPH;
    para2.Header.Length = (BYTE) ODSLength( _CDPARAGRAPH );
    ODSWriteMemory( &buff_ptr, _CDPARAGRAPH, &para2, 1 );

/* Specify that this paragraph will use definition block #2 (above). */

    ref2.Header.Signature = SIG_CD_PABREFERENCE;
    ref2.Header.Length = (BYTE) ODSLength( _CDPABREFERENCE );
    ref2.PABID = 2;
    ODSWriteMemory( &buff_ptr, _CDPABREFERENCE, &ref2, 1 );

/* Start a run of text within this paragraph. */

    text3.Header.Signature = SIG_CD_TEXT;
    text3.Header.Length = ODSLength ( _CDTEXT ) + RT_STRING3_LEN;

/* Fill in the font information for this run of text. Note that we set a
pointer to the FontID data item within the CDTEXT header. Then we use the
pointer to set the individual fields within the FontID. */

    font = ( FONTIDFIELDS * ) &(text3.FontID);

    font->Face = FONT_FACE_TYPEWRITER;
    font->Attrib = ISBOLD + ISITALIC;
    font->Color = NOTES_COLOR_MAGENTA;
    font->PointSize = 12;

    ODSWriteMemory( &buff_ptr, _CDTEXT, &text3, 1 );

/* Fill in the actual text of this text run. Do not append a null to the
text run. */

    memcpy( (char *)buff_ptr, string3, wstring3Len );
    buff_ptr += wstring3Len;

/*     We are done filling the buffer with CD records. Now append the
       buffer to the note as a rich text field. First find the size of
       the buffer. Then add the rich-text field to the note by calling
       NSFItemAppend. NSFItemAppend copies the data out of the buffer
       specified by rt_field. Therfore, after calling NSFItemAppend, we
       can free the buffer.
*/

    rt_size = (DWORD)(buff_ptr - rt_field);

    error = NSFItemAppend( note_handle,
                0,
                "RICH_TEXT", (WORD) strlen("RICH_TEXT"),
                TYPE_COMPOSITE,
                rt_field, rt_size );

    free( rt_field );

    if (error)
    {
        NSFNoteClose( note_handle );
        NSFDbClose( db_handle );
        LAPI_RETURN ( ERR(error) );
    }

/* Add the entire new note (with all fields) to the database. */

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

/* Close the database */

    if (error = NSFDbClose (db_handle))
        LAPI_RETURN (ERR(error));

/* End of subroutine. */

    LAPI_RETURN (NOERROR);
}

