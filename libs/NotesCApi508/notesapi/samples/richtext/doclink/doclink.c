/****************************************************************************

    PROGRAM:    doclink

    FILE:       doclink.c

    PURPOSE:    Shows how to create a Document link, View link, Database link,
                and Anchor link in a richtext field.

    DESCRIPTION:
        Creates notes in two different databases, one of the notes
        containing a Doc Link, View Link, Database Link, and Anchor Link to 
        the other note.

****************************************************************************/

/* Windows header file */
#if !defined(MAC)
#include <windows.h>

/* standard header files     */

#include <stdio.h>
#endif
#include <string.h>

/* Lotus C API for Domino and Notes Header files.  */

#include <lapicinc.h>

#include <global.h>
#include <nsfdata.h>
#include <nif.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <editods.h>
#include <colorid.h>

#include <lapiplat.h>

void CreateBody(char **ppBuf, WORD *pLength); 

void CreateDocLink(char **ppBuf, WORD *pLength, DBREPLICAINFO DBRep,
                   ORIGINATORID Note_OID, ORIGINATORID View_OID);

void CreateViewLink(char **ppBuf, WORD *pLength, DBREPLICAINFO DBRep,
                    ORIGINATORID Note_OID, ORIGINATORID View_OID);

void CreateDBLink(char **ppBuf, WORD *pLength, DBREPLICAINFO DBRep,
                  ORIGINATORID Note_OID, ORIGINATORID View_OID);

void CreateAnchorLink(char **ppBuf, WORD *pLength, DBREPLICAINFO DBRep, 
                   ORIGINATORID Note_OID, ORIGINATORID View_OID);

/************************************************************************

    FUNCTION:   WinMain

    PURPOSE:    Main Windows Entry Point

    ALGORITHM:
       1.  Open DOCLINK1.NSF, call NIFFindView to get the 
           NoteID of the "Main View" view note.
       2.  Open the View Note, get its ORIGINATORID (OID), close the
           view note.
       3.  Create a data note in DOCLINK1.NSF, then call NSFNoteUpdate to
           save it.
       4.  Get the ORIGINATORID from the updated data note, close the note.
       5.  Get the replica ID of DOCLINK1.NSF, then close the database.
       6.  Open DOCLINK2.NSF, create a new data note in it.
       7.  Call CreateDocLink to create a document link, CreateViewLink
           to create a view link, and call CreateDBLink to create
           a database link.
       8.  Fill in the 3 CDLINKEXPORT2 structures with the following: 
           (a) the replica ID of DOCLINK1.NSF (all 3 links) 
           (b) the View's Note Creation TIMEDATE (for doclink and viewlink)
           (c) the Note's Creation TIMEDATE (for doclink only)
       9.  Append the buffer as a CD field to the note in DOCLINK2.NSF, and
           update the note for each link.
       10. Close the note in DOCLINK2.NSF, then close the database.

*************************************************************************/
LAPI_MAIN 
{
    NOTEHANDLE hNote, hNote2; 
    NOTEHANDLE hViewNote;
    NOTEID ViewNoteID;
    STATUS sError = NOERROR;
    DBHANDLE hDB;
    ORIGINATORID    NoteOID;
    ORIGINATORID    ViewOID;
    DBREPLICAINFO DBReplica;
    char szViewName[] = "Main View";
    char szFileName1[] = "doclink1.nsf";
    char szFileName2[] = "doclink2.nsf"    ;
    char SubjectText1[] = "This is a document.";
    char SubjectText2[] = "Contains various links to a note in another database.";
    char szBuffer[3000];
    char *bufPtr;
    WORD bufLen;

    /*   Start by calling Notes Init.  */

    LAPI_INIT(sError);
    if (sError)
      LAPI_INIT_ERROR;


    /*
     * Open the first database
     */

    if (sError = NSFDbOpen(szFileName1, &hDB))
        LAPI_RETURN (sError);


    /*
     * Get the NoteID of the view note
     */

    if (sError = NIFFindView (hDB, szViewName, &ViewNoteID))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    /*
     * Open the View Note
     */

    if (sError = NSFNoteOpen (hDB, ViewNoteID, 0, &hViewNote))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    /*
     * Get the OID From the view note
     */

    NSFNoteGetInfo (hViewNote, _NOTE_OID, &ViewOID);

    /*
     * Close the View Note
     */

    if (sError = NSFNoteClose(hViewNote))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    /*
     * Create a note.
     */

    if (sError = NSFNoteCreate(hDB, &hNote))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    /*
     * Put some text in the Subject field.
     */

    if (sError = NSFItemSetText(hNote,                  /* Note handle */
                               "Subject",               /* Field name  */
                               SubjectText1,            /* Text to set */
                               sizeof(SubjectText1)))   /* Text length */
    {
        
        NSFDbClose(hDB);            /* Close database            */
        LAPI_RETURN (sError);
    }

    bufPtr = &szBuffer[0];           /* set bufPtr to start of szbuffer */
    bufLen = 0;
    
    /* create a Body for the document */
    CreateBody(&bufPtr, &bufLen);

    /*
     * Append the buffer as a CD field
     */

    if (sError = NSFItemAppend(hNote, 0, "Body", 4,
                               TYPE_COMPOSITE, szBuffer,
                               bufLen))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    memset(&szBuffer, 0, sizeof(szBuffer));    /* init buffer */
    bufPtr = &szBuffer[0];                     /* set bufPtr to start of szbuffer */
    bufLen = 0;            
 
    /*
     * Update the note
     */

    if (sError = NSFNoteUpdate(hNote, 0))
    {
        NSFDbClose(hDB);            /* Close database            */
        LAPI_RETURN (sError);
    }

    /*
     * Get the OID from the note AFTER it has been updated
     */

    NSFNoteGetInfo (hNote, _NOTE_OID, &NoteOID);

    /*
     * Close the note
     */

    if (sError = NSFNoteClose(hNote))
    {
        NSFDbClose(hDB);            /* Close database            */
        LAPI_RETURN (sError);
    }

    /*
     * Get the Database replica ID
     */

    if (sError = NSFDbReplicaInfoGet (hDB, &DBReplica))
    {
        NSFDbClose(hDB);            /* Close database            */
        LAPI_RETURN (sError);
    }
    
    /*
     * Close database 1.
     */

    if (sError = NSFDbClose(hDB))
        LAPI_RETURN (sError);

    /*
     * Open database 2
     */

    if (sError = NSFDbOpen(szFileName2, &hDB))
        LAPI_RETURN (sError);

    /*
     * Now create a note in database 2
     */

    if (sError = NSFNoteCreate(hDB, &hNote2))
    {
        NSFDbClose(hDB);            /* Close database            */
        LAPI_RETURN (sError);
    }

    /*
     * Put some text in the Subject field.
     */

    if (sError = NSFItemSetText(hNote2,                 /* Note handle */
                               "Subject",               /* Field name  */
                               SubjectText2,            /* Text to set */
                               sizeof(SubjectText2)))   /* Text length */
    {
        
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    
    bufPtr = &szBuffer[0];           /* set bufPtr to start of szbuffer */
    bufLen = 0;
    
    /* 
     * Create a Document Link.
     */

    CreateDocLink(&bufPtr, &bufLen, DBReplica, NoteOID, ViewOID);
    
    /*
     * Append the buffer as a CD field
     */

    if (sError = NSFItemAppend(hNote2, 0, "Body", 4,
                               TYPE_COMPOSITE, szBuffer,
                               bufLen))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    memset(&szBuffer, 0, sizeof(szBuffer));    /* init buffer */
    bufPtr = &szBuffer[0];                     /* set bufPtr to start of szbuffer */
    bufLen = 0;            
    
    /* 
     * Create a View Link.
     */

    CreateViewLink(&bufPtr, &bufLen, DBReplica, NoteOID, ViewOID);
    
    /*
     * Append the buffer as a CD field
     */

    if (sError = NSFItemAppend(hNote2, 0, "Body", 4,
                               TYPE_COMPOSITE, szBuffer,
                               bufLen))
    {
        NSFDbClose(hDB);            /* Close database            */
        LAPI_RETURN (sError);
    }

    memset(&szBuffer, 0, sizeof(szBuffer));  /* init buffer */
    bufPtr = &szBuffer[0];                   /* set bufPtr to start of szbuffer */
    bufLen = 0;
    
    /* 
     * Create a Database Link.
     */

    CreateDBLink(&bufPtr, &bufLen, DBReplica, NoteOID, ViewOID);
    
    /*
     * Append the buffer as a CD field
     */

    if (sError = NSFItemAppend(hNote2, 0, "Body", 4,
                               TYPE_COMPOSITE, szBuffer,
                               bufLen))
    { 
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }


    memset(&szBuffer, 0, sizeof(szBuffer));  /* init buffer */
    bufPtr = &szBuffer[0];           /* set bufPtr to start of szbuffer */
    bufLen = 0;
    
    /* 
     * Create an Anchor Link.
     */

    CreateAnchorLink(&bufPtr, &bufLen, DBReplica, NoteOID, ViewOID);
    
    /*
     * Append the buffer as a CD field
     */

    if (sError = NSFItemAppend(hNote2, 0, "Body", 4,
                               TYPE_COMPOSITE, szBuffer,
                               bufLen))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    memset(&szBuffer, 0, sizeof(szBuffer));    /* init buffer */
    bufPtr = &szBuffer[0];                     /* set bufPtr to start of szbuffer */
    bufLen = 0;            
 
    /*
     * Update the note
     */

    if (sError = NSFNoteUpdate(hNote2, 0))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    /* 
     * Close the note
     */

    if (sError = NSFNoteClose(hNote2))
    {
        NSFDbClose(hDB);             /* Close database            */
        LAPI_RETURN (sError);
    }

    /*
     * Close the database
     */


    if (sError = NSFDbClose(hDB))
        LAPI_RETURN (sError);

    /*
     * leave with no error
     */

    printf ("\nProgram completed successfully.\n");
     
    LAPI_RETURN (NOERROR);
}

 /**********************************************************************
 *
 *    CreateBody
 *        This function inserts text into the document body and adds
 *        an anchor to a line of text.
 * 
 *   Arguments:
 *       char **ppBuf               Address of pointer to next available 
 *                                  byte in buffer containing the item 
 *                                  being created.
 *       WORD *pLength              Length of buffer
 *
 *   Comments:
 *
 **********************************************************************/

void CreateBody(char **ppBuf, WORD *pLength) 
{
    CDPARAGRAPH     pCDPara[2];
    CDTEXT          CDText;        /* begin a run of text */
    FONTIDFIELDS    *pFont;        /* font definitions in rich text field */
    WORD            wTextLength;
    WORD            wAnchorTextLength;
    char            TextString[256];
    char            AnchorTextString[256];
    CDANCHOR        Anchor;
    int             i;
 
    /* 
     * Create a CDPARAGRAPH structure
     */

    pCDPara[0].Header.Signature = SIG_CD_PARAGRAPH;
    pCDPara[0].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    
    ODSWriteMemory( (void far * far *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure that will label the link type in the document
     */

    strcpy(TextString,"The following text contains information from the doclink sample's readme.txt file.");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    
    *pLength = ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"1. PROGRAM");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += (ODSLength(_CDPARAGRAPH)*2)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"doclink - Sample Notes API Program: shows how to create ");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"a Doc Link, a View Link, a Database Link and an Anchor Link.");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;
    
    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"2. RUNNING doclink");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += (ODSLength(_CDPARAGRAPH)*2)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"This sample program uses two Notes databases, doclink1.nsf and doclink2.nsf, ");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, "provided with the Notes API toolkit.  You must copy these files to the "); 
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, "Notes data directory before running this program.");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"- Under Windows 16-bit: From the program manager, choose "); 
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += (ODSLength(_CDPARAGRAPH)*2)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, " 'RUN' from the FILE menu, type in the full path and filename of this "); 
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, "program, and press <Return>.  This program takes no parameters.");  
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"- Under Windows 32-bit, ");
    wTextLength = strlen(TextString);


    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += (ODSLength(_CDPARAGRAPH)*2)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, "type: doclink ");
    wTextLength = strlen(TextString);


    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, "at the system prompt. The program takes no arguments.");
    wTextLength = strlen(TextString);


    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"- Under Macintosh: double click on the program icon."); 
    wTextLength = strlen(TextString);


    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += (ODSLength(_CDPARAGRAPH)*2)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* copy the anchor text */
    strcpy(AnchorTextString,"3");
    wAnchorTextLength = strlen(AnchorTextString);
    if (wAnchorTextLength % 2)
        wAnchorTextLength++;
        
    Anchor.Datalength = wAnchorTextLength;

    /* 
     * Create a CDANCHOR structure
     */

    Anchor.Header.Signature = SIG_CD_ANCHOR;
    Anchor.Header.Length = ODSLength(_CDANCHOR)+wAnchorTextLength;
    Anchor.Reserved = 0;

    /* write the structure to ppBuf */
    ODSWriteMemory( (void far * far *)ppBuf, _CDANCHOR, &Anchor, 1 );
      
    memcpy(*ppBuf, &AnchorTextString[0], wAnchorTextLength);  /* Append string to CDTEXT. */
    *ppBuf += wAnchorTextLength;

    /*if (((LONG) *ppBuf) % 2)
      *ppBuf += 1;*/
 
    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString,"3. CHECKING THE RESULTS");
    wTextLength = strlen(TextString);


    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += (ODSLength(_CDPARAGRAPH)*2)+ODSLength(_CDANCHOR)+wAnchorTextLength+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, "This will create one note in each of the two databases doclink1.nsf");
    wTextLength = strlen(TextString);


    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, "and doclink2.nsf.  The note in doclink2.nsf will contain a Doc Link,"); 
    wTextLength = strlen(TextString);


    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

    /* 
     * Create 1 CDPARAGRAPH structures
     */

    for (i=0; i<1; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 1 );

    /* 
     * Create a CDTEXT structure.
     */

    strcpy(TextString, "a View Link, a Database Link and an Anchor link to the note in doclink1.nsf.");
    wTextLength = strlen(TextString);


    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    if (wTextLength % 2)
        wTextLength += 1;
    
    *ppBuf += wTextLength;

    *pLength += ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength;

} 

 /**********************************************************************
 *
 *    CreateDocLink
 *        This function inserts text into the document body and creates 
 *        a document link to a note.
 * 
 *   Arguments:
 *       char **ppBuf               Address of pointer to next available 
 *                                  byte in buffer containing the item 
 *                                  being created.
 *       WORD *pLength              Length of buffer
 *       DBREPLICAINFO  DBRep       structure with replicator id
 *       ORIGINATORID   Note_OID    Note originator id
 *       ORIGINATORID   View_OID    Note View originator id
 *
 *   Comments:
 *
 **********************************************************************/

void CreateDocLink(char **ppBuf, WORD *pLength, DBREPLICAINFO DBRep, 
                   ORIGINATORID Note_OID, ORIGINATORID View_OID)

{
    CDPARAGRAPH     pCDPara;
    CDLINKEXPORT2   pCDLink;
    CDTEXT          CDText;        /* begin a run of text */
    FONTIDFIELDS    *pFont;        /* font definitions in rich text field */
    UNID            Note_UNID;
    UNID            View_UNID;
    WORD            wTextLength;
    WORD            wDocTextLength;
    char            TextString[51];
    char            DocTextString[256];
    char            NullString[]="\0\0\0";
         
    /* 
     * Create a CDPARAGRAPH structure
     */

    pCDPara.Header.Signature = SIG_CD_PARAGRAPH;
    pCDPara.Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    
    ODSWriteMemory( (void far * far *)ppBuf, _CDPARAGRAPH, &pCDPara, 1 );

    /* 
     * Create a CDTEXT structure that will label the link type in the document
     */

    strcpy(TextString,"Document Link-> ");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    *ppBuf += wTextLength;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;
        
    /* set up Title for Document Link */
    strcpy(DocTextString,"Database 'DocLink 1 Test database', View 'Main View', Document 'This is a document.'");
    wDocTextLength = strlen(DocTextString);
    if (wDocTextLength % 2)
        wDocTextLength++;

    /* 
     *  Create Export Link (CDLINKEXPORT2) structure
     */

     pCDLink.Header.Signature = SIG_CD_LINKEXPORT2;
     pCDLink.Header.Length = ODSLength(_CDLINKEXPORT2)+ wDocTextLength + 3;
    
    /*
     * Create the IDs for both of the notes (view and data)
     */

    Note_UNID.File = Note_OID.File;
    Note_UNID.Note = Note_OID.Note;

    View_UNID.File = View_OID.File;
    View_UNID.Note = View_OID.Note;

    /*
     * Fill in the CDLINKEXPORT2 structure
     */

    /* 1. File's replica ID for structure */
    pCDLink.NoteLink.File = DBRep.ID;

    /* 2. View's Note Creation TIMEDATE */

    /* doclink structure contains ViewUNID info */
    memmove(&pCDLink.NoteLink.View, &View_UNID, sizeof(UNID));
    
    /* 3. Note's Creation TIMEDATE */

    /* doclink structure contains NoteUNID info */
    memmove(&pCDLink.NoteLink.Note, &Note_UNID, sizeof(UNID));

    /* write the structure to ppBuf */
    ODSWriteMemory( (void far * far *)ppBuf, _CDLINKEXPORT2, &pCDLink, 1 );
    
    memcpy(*ppBuf, &DocTextString, wDocTextLength);  /* Append string */
    *ppBuf += wDocTextLength;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;

    memcpy(*ppBuf, &NullString[0], 3);  /* Append string */
    *ppBuf += 3;
    
    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;

    /* calc entire length of buffer */
    *pLength = ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength+(ODSLength(_CDLINKEXPORT2) + wDocTextLength + 3);
} 

 /**********************************************************************
 *
 *    CreateViewLink
 *        This function inserts text into the document body and creates 
 *        a view link to a note.
 * 
 *   Arguments:
 *       char **ppBuf               Address of pointer to next available 
 *                                  byte in buffer containing the item 
 *                                  being created.
 *       WORD *pLength              Length of buffer
 *       DBREPLICAINFO  DBRep       structure with replicator id
 *       ORIGINATORID   Note_OID    Note originator id
 *       ORIGINATORID   View_OID    Note View originator id
 *
 *   Comments:
 *
 **********************************************************************/

void CreateViewLink(char **ppBuf, WORD *pLength, DBREPLICAINFO DBRep, 
                    ORIGINATORID Note_OID, ORIGINATORID View_OID)

{
    CDPARAGRAPH     pCDPara[2];
    CDLINKEXPORT2   pCDLink;
    CDTEXT          CDText;        /* begin a run of text */
    FONTIDFIELDS    *pFont;        /* font definitions in rich text field */
    UNID            Note_UNID;
    UNID            View_UNID;
    WORD            wTextLength;
    WORD            wViewTextLength;
    char            TextString[51];
    char            ViewTextString[256];
    char            NullString[]="\0\0\0";
    int             i;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void far * far *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* 
     * Create a CDTEXT structure that will label the link type in the document
     */

    strcpy(TextString,"View Link-> ");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    *ppBuf += wTextLength;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;

    /* set up Title for View Link */
    strcpy(ViewTextString,"Database 'DocLink 1 Test database', View 'Main View'");
    wViewTextLength = strlen(ViewTextString);
    if (wViewTextLength % 2)
        wViewTextLength++;

    /* 
     *  Create Export Link (CDLINKEXPORT2) structure
     */

     pCDLink.Header.Signature = SIG_CD_LINKEXPORT2;
     pCDLink.Header.Length = ODSLength(_CDLINKEXPORT2) + wViewTextLength + 3;
    
    /*
     * Create the IDs for both of the notes (view and data)
     */

    Note_UNID.File = Note_OID.File;
    Note_UNID.Note = Note_OID.Note;

    View_UNID.File = View_OID.File;
    View_UNID.Note = View_OID.Note;

    /*
     * Fill in the CDLINKEXPORT2 structure
     */

    /* 1. File's replica ID for structure */
    pCDLink.NoteLink.File = DBRep.ID;

    /* 2. View's Note Creation TIMEDATE */

    /* viewlink structure contains ViewUNID info */
    memmove(&pCDLink.NoteLink.View, &View_UNID, sizeof(UNID));
    
    /* 3. Note's Creation TIMEDATE */

    /* viewlink structure - set to all zeros for viewlink */
    memset(&pCDLink.NoteLink.Note, 0, sizeof(UNID));

    /* write the structure to ppBuf */
    ODSWriteMemory( (void far * far *)ppBuf, _CDLINKEXPORT2, &pCDLink, 1 );
    
    memcpy(*ppBuf, &ViewTextString, wViewTextLength);  /* Append string */
    *ppBuf += wViewTextLength;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;

    memcpy(*ppBuf, &NullString[0], 3);  /* Append string */
    *ppBuf += 3;
    
    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;

    
    /* calc entire length of buffer */
    *pLength = (ODSLength(_CDPARAGRAPH)*2)+ODSLength(_CDTEXT)+wTextLength+(ODSLength(_CDLINKEXPORT2) + wViewTextLength + 3);
} 


 /**********************************************************************
 *
 *    CreateDBLink
 *        This function inserts text into the document body and creates 
 *        a database link to a note.
 * 
 *   Arguments:
 *       char **ppBuf               Address of pointer to next available 
 *                                  byte in buffer containing the item 
 *                                  being created.
 *       WORD *pLength              Length of buffer
 *       DBREPLICAINFO  DBRep       structure with replicator id
 *       ORIGINATORID   Note_OID    Note originator id
 *       ORIGINATORID   View_OID    Note View originator id
 *
 *   Comments:
 *
 **********************************************************************/

void CreateDBLink(char **ppBuf, WORD *pLength, DBREPLICAINFO DBRep, 
                  ORIGINATORID Note_OID, ORIGINATORID View_OID)

{
    CDPARAGRAPH     pCDPara[2];
    CDLINKEXPORT2   pCDLink;
    CDTEXT          CDText;        /* begin a run of text */
    FONTIDFIELDS    *pFont;        /* font definitions in rich text field */
    UNID            Note_UNID;
    UNID            View_UNID;
    WORD            wTextLength;
    WORD            wDBTextLength;
    char            TextString[51];
    char            DBTextString[256];
    char            NullString[]="\0\0\0";
    int             i;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* 
     * Create a CDTEXT structure that will label the link type in the document
     */

    strcpy(TextString,"Database Link-> ");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    *ppBuf += wTextLength;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;
  
    /* set up Title for Database Link */
    strcpy(DBTextString,"Database 'DocLink 1 Test database'");
    wDBTextLength = strlen(DBTextString);
    if (wDBTextLength % 2)
        wDBTextLength++;

    /* 
     *  Create Export Link (CDLINKEXPORT2) structure
     */

     pCDLink.Header.Signature = SIG_CD_LINKEXPORT2;
     pCDLink.Header.Length = ODSLength(_CDLINKEXPORT2) + wDBTextLength + 3;
    
    /*
     * Create the IDs for both of the notes (view and data)
     */

    Note_UNID.File = Note_OID.File;
    Note_UNID.Note = Note_OID.Note;

    View_UNID.File = View_OID.File;
    View_UNID.Note = View_OID.Note;

    /*
     * Fill in the CDLINKEXPORT2 structure
     */

    /* 1. File's replica ID for structure */
    pCDLink.NoteLink.File = DBRep.ID;

    /* 2. View's Note Creation TIMEDATE */

    /* database link structure - set to all zeros for database link */
    memset(&pCDLink.NoteLink.View, 0, sizeof(UNID));

    /* 3. Note's Creation TIMEDATE */

    /* database link structure - set to all zeros for database link */
    memset(&pCDLink.NoteLink.Note, 0, sizeof(UNID));

    /* write the structure to ppBuf */
    ODSWriteMemory( (void far * far *)ppBuf, _CDLINKEXPORT2, &pCDLink, 1 );
    
    memcpy(*ppBuf, &DBTextString, wDBTextLength);  /* Append string */
    *ppBuf += wDBTextLength;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;

    memcpy(*ppBuf, &NullString[0], 3);  /* Append string */
    *ppBuf += 3;
    
    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;

    /* calc entire length of buffer */
    *pLength = (ODSLength(_CDPARAGRAPH)*2)+ODSLength(_CDTEXT)+wTextLength+(ODSLength(_CDLINKEXPORT2) + wDBTextLength + 3);
}

 /**********************************************************************
 *
 *    CreateAnchorLink
 *        This function inserts text into the document body and creates 
 *        an anchor link to a note.
 * 
 *   Arguments:
 *       char **ppBuf               Address of pointer to next available 
 *                                  byte in buffer containing the item 
 *                                  being created.
 *       WORD *pLength              Length of buffer
 *       DBREPLICAINFO  DBRep       structure with replicator id
 *       ORIGINATORID   Note_OID    Note originator id
 *       ORIGINATORID   View_OID    Note View originator id
 *
 *   Comments:
 *
 **********************************************************************/

void CreateAnchorLink(char **ppBuf, WORD *pLength, DBREPLICAINFO DBRep, 
                   ORIGINATORID Note_OID, ORIGINATORID View_OID)

{
    CDPARAGRAPH     pCDPara[2];
    CDLINKEXPORT2   pCDLink;
    CDTEXT          CDText;        /* begin a run of text */
    FONTIDFIELDS    *pFont;        /* font definitions in rich text field */
    UNID            Note_UNID;
    UNID            View_UNID;
    WORD            wTextLength;
    WORD            wAnchorTextLength;
    WORD            wAnchorTextLength1;
    char            TextString[51];
    char            AnchorTextString[256];
    char            AnchorTextString1[10];
    char            NullString[2];
    int             i;

    /* 
     * Create 2 CDPARAGRAPH structures
     */

    for (i=0; i<2; i++)
    {
      pCDPara[i].Header.Signature = SIG_CD_PARAGRAPH;
      pCDPara[i].Header.Length = (BYTE) ODSLength(_CDPARAGRAPH);
    }
    
    ODSWriteMemory( (void * *)ppBuf, _CDPARAGRAPH, &pCDPara[0], 2 );

    /* 
     * Create a CDTEXT structure that will label the link type in the document
     */

    strcpy(TextString,"Anchor Link-> ");
    wTextLength = strlen(TextString);

    /* Fill in the TEXT item structure.       */
    
    CDText.Header.Signature = SIG_CD_TEXT;
    CDText.Header.Length = ODSLength(_CDTEXT) + wTextLength;
  
   /*
    *  Fill in the font information for this run of text. Note that
    *  we must overlay the FONTIDFIELDS structure onto the
    *  CDText.FontID data item.
    */

    pFont = (FONTIDFIELDS*)&CDText.FontID;
    pFont->Face = FONT_FACE_SWISS;
    pFont->Attrib = 0;
    pFont->Color = NOTES_COLOR_BLACK;
    pFont->PointSize = 10;

  /*
   *  Convert the CDTEXT item to Domino and Notes Canonical format and store it in
   *  the ODS buffer.
   */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    memcpy(*ppBuf, &TextString[0], wTextLength);  /* Append string to CDTEXT. */
    *ppBuf += wTextLength;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;
        
    /* 
     *  Create Export Link (CDLINKEXPORT2) structure
     */

    /* FORMAT of data in CDLINKEXPORT2 structure for an anchor link is:
     *  Title\0,\0,Anchor Text\0,\0 
     */
    strcpy(AnchorTextString,"Database 'DocLink 1 Test database', View 'Main View', Document 'This is a document.', Anchor '2'");
    wAnchorTextLength = strlen(AnchorTextString);
    if (wAnchorTextLength % 2)
        wAnchorTextLength++;
        
    /* here's the anchor text to link to */
    strcpy(AnchorTextString1,"3");
    wAnchorTextLength1 = strlen(AnchorTextString1);
    if (wAnchorTextLength1 % 2)
        wAnchorTextLength1++;
        
    NullString[0] = '\0';
    
    pCDLink.Header.Signature = SIG_CD_LINKEXPORT2;
    pCDLink.Header.Length = ODSLength(_CDLINKEXPORT2)+wAnchorTextLength+wAnchorTextLength1+4;

    /* 
     * Create the IDs for both of the notes (view and data)
     */

    Note_UNID.File = Note_OID.File;
    Note_UNID.Note = Note_OID.Note;

    View_UNID.File = View_OID.File;
    View_UNID.Note = View_OID.Note;

    /*
     * Fill in the CDLINKEXPORT2 structure
     */

    /* 1. File's replica ID for structure */
    pCDLink.NoteLink.File = DBRep.ID;

    /* 2. View's Note Creation TIMEDATE */

    /* doclink structure contains ViewUNID info */
    memmove(&pCDLink.NoteLink.View, &View_UNID, sizeof(UNID));
    
    /* 3. Note's Creation TIMEDATE */

    /* doclink structure contains NoteUNID info */
    memmove(&pCDLink.NoteLink.Note, &Note_UNID, sizeof(UNID));

    /* write the structure to ppBuf */
    ODSWriteMemory( (void far * far *)ppBuf, _CDLINKEXPORT2, &pCDLink, 1 );

    memcpy(*ppBuf, &AnchorTextString[0], wAnchorTextLength);  /* Append string */
    *ppBuf += wAnchorTextLength;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;
 
    memcpy(*ppBuf, &NullString[0], 1);  /* Append string */
    *ppBuf += 1;

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;
 
    memcpy(*ppBuf, &AnchorTextString1[0], wAnchorTextLength1);  /* Append string */
    *ppBuf += wAnchorTextLength1;
 
    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;
 
    memcpy(*ppBuf, &NullString[0], 1);  /* Append string */
      *ppBuf += 1;
 
    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;
 
    /* calc entire length of buffer */
    *pLength = 2*ODSLength(_CDPARAGRAPH)+ODSLength(_CDTEXT)+wTextLength+(ODSLength(_CDLINKEXPORT2)+wAnchorTextLength+wAnchorTextLength1+4);

}

