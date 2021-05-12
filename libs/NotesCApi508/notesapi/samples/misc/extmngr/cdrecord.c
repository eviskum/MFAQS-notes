/****************************************************************************

    PROGRAM:      makeform

    FILE:         cdrecord.c

    PURPOSE:      Functions for appending CD records to a buffer

****************************************************************************/

/* Include Windows header file only if compiling for Windows. */
 
#if defined (DOS) && defined (W)
#include <windows.h>
#endif

/* C header files */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <names.h>

/* Lotus C API for Domino and Notes header files      */

#include <global.h>
#include <editdflt.h>
#include <nsfnote.h>
#include <osmem.h>
#include <editods.h>
#include <colorid.h>


/**********************************************************************
 *
 *    PutPabDef
 *        API function to write a "rich text" paragraph 
 *        attribute block (PAB) definition segment to a 
 *        buffer that will be written as a rich text field to Domino 
 *        and Notes
 * 
 *   Arguments:
 *       char **ppBuf         address of pointer to next available byte in 
 *                            buffer containing the item being created.
 *       WORD wPabDefNumber   A unique ID to use for this PabDefinition.
 *       WORD wLength         Number of bytes remaining in the buffer. 
 *
 *    Returns:
 *        BOOL TRUE if Successful
 *        BOOL FALSE if Not Successful
 *
 *    Comments:
 *
 **********************************************************************/

BOOL LNPUBLIC PutPabDef(char far * far * ppBuf,
                          WORD wPabDefNumber,
                          WORD wLength)
{
    CDPABDEFINITION  CDPabDef;      /* style definition for this para */

    /* If not enough space in buffer for this struct, then exit.        */

    if (wLength < ODSLength(_CDPABDEFINITION))
        return (FALSE);
    
   /* Fill in paragraph definition block.  We use all defaults, except  */
   /* for centered justification.                                       */

    CDPabDef.Header.Signature       = SIG_CD_PABDEFINITION;
    CDPabDef.Header.Length          = ODSLength(_CDPABDEFINITION);
    CDPabDef.PABID                  = wPabDefNumber;
    CDPabDef.JustifyMode            = JUSTIFY_LEFT;
    CDPabDef.LineSpacing            = DEFAULT_LINE_SPACING;
    CDPabDef.ParagraphSpacingBefore = DEFAULT_ABOVE_PAR_SPACING;
    CDPabDef.ParagraphSpacingAfter  = DEFAULT_BELOW_PAR_SPACING;
    CDPabDef.LeftMargin             = DEFAULT_LEFT_MARGIN;
    CDPabDef.RightMargin            = DEFAULT_RIGHT_MARGIN;
    CDPabDef.FirstLineLeftMargin    = DEFAULT_FIRST_LEFT_MARGIN;
    CDPabDef.Tabs                   = DEFAULT_TABS;
    CDPabDef.Tab[0]                 = DEFAULT_TAB_INTERVAL;
    CDPabDef.Flags                  = 0;
    CDPabDef.TabTypes               = TAB_DEFAULT;
    CDPabDef.Flags2                 = 0;


/*
 *  Convert the PABDEFINITION item to Domino and Notes Canonical format and 
 *  store it in the ODS buffer.
 */

    ODSWriteMemory( (void far * far *)ppBuf, _CDPABDEFINITION, &CDPabDef, 1 );
     
    return (TRUE);
}


/**********************************************************************
 *    
 *   PutPara
 *       API function to write a CDPARAGRAPH segment to a buffer that will
 *       be written as a rich text field to Domino and Notes
 *
 *   Arguments:
 *       char far * far *ppBuf Address of pointer to next available byte in 
 *                             buffer containing the item being created.
 *       WORD wLength          Number of bytes remaining in the buffer. 
 *
 *    Returns:
 *        BOOL TRUE if Successful
 *        BOOL FALSE if Not Successful
 *     
 * 
 *   Comments:
 *    
 ***********************************************************************/

BOOL LNPUBLIC PutPara( char far * far *ppBuf,
                         WORD wLength )
{
    CDPARAGRAPH CDPara;
    BYTE        bLength =  (BYTE) ODSLength(_CDPARAGRAPH);
    BYTE        bSig  =  (BYTE)SIG_CD_PARAGRAPH;
    

    /* If not enough space in buffer for this paragraph, then exit.   */
    
    if (wLength < ODSLength(_CDPARAGRAPH))
        return (FALSE);

/* Fill in PARAGRAPH item structure  */
        
    CDPara.Header.Length = bLength;/* (BYTE) ODSLength(_CDPARAGRAPH); */
    CDPara.Header.Signature = bSig;/* SIG_CD_PARAGRAPH; */

/*
 *  Convert the CDPARAGRAPH item to Domino and Notes Canonical format 
 *  and store it in the ODS buffer.
 */

    ODSWriteMemory( (void far * far *)ppBuf, _CDPARAGRAPH, &CDPara, 1 );
     
    return (TRUE);
}

/**********************************************************************
 *
 *    PutPabRef
 *        API function to write a "rich text" paragraph 
 *        attribute block (PAB) reference segment to a 
 *        buffer that will be written as a rich text field to Domino 
 *        and Notes
 * 
 *   Arguments:
 *       char far * far *ppBuf  Address of pointer to next available byte in 
 *                            buffer containing the item being created.
 *       WORD wPabDefNumber   The paragraph definition to which this pabref
 *                            refers.
 *       WORD wLength         Number of bytes remaining in the buffer. 
 *
 *    Returns:
 *        BOOL TRUE if Successful
 *        BOOL FALSE if Not Successful
 *
 *
 *    Comments:
 *
 **********************************************************************/

BOOL LNPUBLIC PutPabRef(char far * far *ppBuf,
                          WORD wPabDefNumber,
                          WORD wLength)
{
    CDPABREFERENCE  CDPabRef;      /* style reference for this para */
    BYTE        bLength =  (BYTE) ODSLength(_CDPABREFERENCE);
    BYTE        bSig  =  (BYTE)SIG_CD_PABREFERENCE;
    

    /* If not enough space in buffer for this struct, then exit.      */

    if (wLength < ODSLength(_CDPABREFERENCE))
        return (FALSE);

    /* Fill in PABREF item structure.    */ 
    
    CDPabRef.Header.Signature = bSig;/* SIG_CD_PABREFERENCE; */
    CDPabRef.Header.Length    = bLength;/* (BYTE) ODSLength(_CDPABREFERENCE); */
    CDPabRef.PABID            = wPabDefNumber;


/*
 *  Convert the CDPABREFERENCE item to Domino and Notes Canonical format and 
 *  store it in the ODS buffer.
 */

    ODSWriteMemory( (void far * far *)ppBuf, _CDPABREFERENCE, &CDPabRef, 1 );
     
    return (TRUE);
}

/**********************************************************************
 *
 *    PutText
 *        API function to write a "rich text" text segment 
 *        to a buffer that will be written as a rich text field to Domino 
 *        and Notes.
 * 
 *   Arguments:
 *       char far * far *ppBuf Address of pointer to next available byte in 
 *                            buffer containing the item being created.
 *       char far * pText          Far ptr to text to go into CD record.
 *       WORD wLength         Number of bytes remaining in the buffer. 
 *
 *    Returns:
 *        BOOL TRUE if Successful
 *        BOOL FALSE if Note Successful
 *
 *    Comments:
 *
 **********************************************************************/

BOOL LNPUBLIC PutText(char far * far *ppBuf,
                        char far * pText,
                        WORD wLength)

{
    CDTEXT         CDText;      /* begin a run of text */
    FONTIDFIELDS   *pFont;        /* font definitions in rich text field */
    WORD           wTextLength;
    WORD           w;
    


    if (pText != NULL)
        wTextLength = strlen(pText);
    else
        wTextLength = 0;

    w = ODSLength(_CDTEXT)+wTextLength;
    
    if ( wLength < w)

    /* (ODSLength(_CDTEXT) + wTextLength) > wLength */

       
        return (FALSE);

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
 *  Convert the CDTEXT item to Domino and Notes Canonical format and 
 *  store it in the ODS buffer.
 */

    ODSWriteMemory( (void far * far *)ppBuf, _CDTEXT, &CDText, 1 );

    if (pText != NULL)
    {
        memcpy( *ppBuf, pText, wTextLength );  /* Append string to CDTEXT. */
        *ppBuf += wTextLength;
    }

    if (((LONG) *ppBuf) % 2)
        *ppBuf += 1;
        
    return (TRUE);
}

