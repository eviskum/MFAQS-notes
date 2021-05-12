/***********************************************************************

   File:        hotspot.c

   Program:     hotspot

   Purpose:     shows how to create popups, sections, buttons, a URL,
                and a file attachment in a rich text field.

   Description:

       First, this program opens the database MAKEFORM.NSF and creates a
       new note in which to place the various objects. It then
       allocates a buffer in which to construct the rich text item. In
       this buffer it creates the following sequence of data structures:

       To define the popup:

       -  A CDHOTSPOTBEGIN record, with the flag member set to
          HOTSPOTREC_REC_POPUP, and with the other data members
          appropriately. The packed string containing the text to be
          displayed when the popup is clicked upon is appended to the
          CDHOTSPOTBEGIN record.

       -  A CDTEXT record, containing the text upon which one would click
          to display the popup text.

       -  A CDHOTSPOTEND record, to mark the end of the popup definition.

       To separate the popup from the button that follows:

       -  Two CDPARAGRAPH records. Since each paragraph starts on a new line,
          this has the effect of inserting a blank line after the popup above.

       To define the button:

       -  A CDHOTSPOTBEGIN record, with the flag member set to
          HOTSPOTREC_REC_BUTTON, and with the other data members
          appropriately. The formula to be run when the button is
          activated is appended to the CDHOTSPOTBEGIN record.

       -  A CDBUTTON record, which defines the appearance of the button.

       -  A CDHOTSPOTEND record, to mark the end of the button definition.

       To separate the button from the bar that follows:

       -  Two CDPARAGRAPH records. Since each paragraph starts on a new line,
          this has the effect of inserting a blank line after the button above.

       To define the bar:

       -  A CDV4HOTSPOTBEGIN record, with the type set to HOTSPOTREC_TYPE_BUNDLE,
          and with the other data members appropriately. 
 
       -  A CDBAR record that will contain the section title and other 
          information for the section.
 
       -  An empty CDTEXT record.
 
       -  A CDPARAGRAPH structure to the buffer;
 
       -  Append a CDPABREFERENCE structure in the buffer;
 
       -  A CDTEXT record that will contain the contents of the section.
 
       -  A CDV4HOTSPOTEND record to mark the end of the hotspot.
 
       To separate the bar from the Action that follows:

       -  Two CDPARAGRAPH records. Since each paragraph starts on a new line,
          this has the effect of inserting a blank line after the bar above.

       To define the Action:

       -  A CDV4HOTSPOTBEGIN record with the type set to 
          HOTSPOTREC_TYPE_HOTREGION.

       -  A word containing TYPE_ACTION appended to the buffer.

       -  A CDACTIONHEADER structure to the buffer.

       -  A CDACTIONSENDMAIL structure to the buffer.
 
       -  A CDTEXT record that will contain the hotspot to click on. 
      
       -  A CDV4HOTSPOTEND record to mark the end of the hotspot.
 
       To separate the action from the URL that follows:

       -  Two CDPARAGRAPH records. Since each paragraph starts on a new line,
          this has the effect of inserting a blank line after the bar above.

       To define the URL:

       -  A CDV4HOTSPOTBEGIN record with the type set to 
          HOTSPOTREC_TYPE_HOTLINK.
 
       -  A CDTEXT record that will contain the URL address. 
      
       -  A CDV4HOTSPOTEND record to mark the end of the hotspot.
 
       To separate the URL from the file attachment that follows:

       -  Two CDPARAGRAPH records. Since each paragraph starts on a new line,
          this has the effect of inserting a blank line after the bar above.

       To define the file attachment:

       -  Call NSFNoteAttachFile to create a $FILE item.
 
       -  A CDHOTSPOTBEGIN record with the type set to HOTSPOTREC_TYPE_FILE.
 
       -  A CDTEXT record that will contain the name of the attached file. 
      
       -  A CDHOTSPOTEND record to mark the end of the hotspot.
 
       The buffer thus created is then appended to the note's rich text
       field. The note is updated is then updated and closed, the database
       is closed, and the program exits.



************************************************************************/

/*
 *  OS includes
 */

#if !defined(MAC)
#if !defined(UNIX)
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif
#include <stdio.h>
#include <stdlib.h>  
#endif
#include <string.h>

/*
 *  Lotus C API for Domino and Notes includes
 */

#include <lapicinc.h>

#include <global.h>
#include <nsf.h>
#include <osmem.h>
#include <ods.h>
#include <names.h>
#include <editods.h>
#include <editdflt.h>
#include <nsfnote.h>
#include <ixport.h>
#include <ixedit.h>
#include <osmisc.h>
#include <oserr.h>
#include <stdnames.h>
#include <kfm.h>

#include <lapiplat.h>

/*
 *  Local includes
 */

#include "hotspot.h"

/*
 *  Forward Declaration
 */ 

STATUS InsertRichText(NOTEHANDLE hNote);

STATUS InsertPopup(NOTEHANDLE hNote,
                              char FAR * FAR *ppCDBuffer,
                              WORD FAR *pwItemSize,
                              WORD wBufferSize);
                              
STATUS InsertButton(NOTEHANDLE hNote,
                               char FAR * FAR *ppCDBuffer,
                               WORD FAR *pwItemSize,
                               WORD wBufferSize);
                                                        
   
STATUS InsertBar(NOTEHANDLE hNote,
                               char FAR * FAR *ppCDBuffer,
                               WORD FAR *pwItemSize,
                               WORD wBufferSize);
 

STATUS InsertAction(NOTEHANDLE hNote,
                               char FAR * FAR *ppCDBuffer,
                               WORD FAR *pwItemSize,
                               WORD wBufferSize);      
         
STATUS InsertURL(NOTEHANDLE hNote,
                               char FAR * FAR *ppCDBuffer,
                               WORD FAR *pwItemSize,
                               WORD wBufferSize);                           

STATUS InsertFile(NOTEHANDLE hNote,
                               char FAR * FAR *ppCDBuffer,
                               WORD FAR *pwItemSize,
                               WORD wBufferSize);                           

/*
 *  Body of main program
 */

LAPI_MAIN
{

    char        *szNSFFile;
    HANDLE      hNewNote;
    DBHANDLE    hDbNSFFile;
    STATUS      sError = NOERROR;

    /*   Start by calling Notes Init.  */

    LAPI_INIT(sError);
    if (sError)
      LAPI_INIT_ERROR;

    szNSFFile  = "makeform.nsf";


    /* Open the Database, assuming it's been created with the   */
    /* template shipped with this demo.                         */
    
    if (sError = NSFDbOpen(szNSFFile, &hDbNSFFile))
        LAPI_RETURN (ERR(sError));


    /* Create a Note */
    
    if (sError = NSFNoteCreate(hDbNSFFile, &hNewNote))
    {
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }

    /* Add the Form name  */
    
    if (sError = NSFItemSetText(hNewNote,
                                 "Form",
                                 "Simple Form",
                                 (WORD) strlen("Simple Form")))
    {
        NSFNoteClose(hNewNote);    /* ERROR - Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }

    /* Set CompanyName field  */
    
    if (sError = NSFItemSetText(hNewNote,
                                 "CompanyName",
                                 "IBM LOTUS",
                                 (WORD) strlen("IBM LOTUS")))
    {
        NSFNoteClose(hNewNote);    /* ERROR - Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }


    /*
     *  Create the richtext item, which will contain objects.
     */

    if (sError = InsertRichText(hNewNote))
    
    {
        NSFNoteClose(hNewNote);    /* Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }

    /* write the note */

    if (sError = NSFNoteUpdate(hNewNote, 0))
    {
        NSFNoteClose(hNewNote);    /* ERROR - Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }

    /* Start cleaning up.  First, Close the Note */
    
    NSFNoteClose(hNewNote);

    /* Now close the database.              */
    
    if (sError = NSFDbClose(hDbNSFFile))
        LAPI_RETURN (ERR(sError));


    printf ("\nProgram completed successfully.\n");

    LAPI_RETURN (NOERROR);            /* Return normally.  */
}

/***********************************************************************
 *
 * InsertRichText
 *
 *      Allocate a buffer in which to build the rich text item. Insert a
 *      popup and a button, separated by two CDPARAGRAPH records. Then
 *      append the buffer to the note.
 *
 * Inputs:   hNote   - handle to the new note being created.
 *
 * Outputs:  None.
 *
 ************************************************************************/


STATUS InsertRichText(NOTEHANDLE hNote)

{
    HANDLE    hMem;
    STATUS    sError;         /* Domino and Notes error status        */
    char FAR  *pCDBuffer;
    char FAR  *pCDBufferStart;
    char      szPopUpContentsString[] = "This is the text of the popup";
    char      szPopUpText[] = "Click Here";
    WORD      wItemSize = 0, wBufferSize = MAXONESEGSIZE;

/*
 *  Allocate a buffer and build the CD record containing the popup and
 *  the button.
 */

    if (sError = OSMemAlloc(0, wBufferSize, &hMem))
        return (ERR_MEMORY);
        
    if ((pCDBuffer = (char far *) OSLockObject(hMem)) == NULL)
        return (ERR_MEMORY);
        
    memset(pCDBuffer, '\0', wBufferSize);
    pCDBufferStart = pCDBuffer;

/*
 * First insert a popup in the rich text field.
 */

    if (sError = InsertPopup(hNote, &pCDBuffer, &wItemSize, wBufferSize))

    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (ERR(sError));
    }

/*
 *  Now insert two CDPARAGRAPH records.
 */
 
    sError = PutPara(&pCDBuffer,
                (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    }

    sError = PutPara(&pCDBuffer,
               (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    }

/*
 * Next, insert a button into the rich text field.
 */

    if (sError = InsertButton(hNote, &pCDBuffer, &wItemSize, wBufferSize))
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (ERR(sError));
    }

/*
 *  Now insert two CDPARAGRAPH records.
 */
 
    sError = PutPara(&pCDBuffer,
        (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    }

    sError = PutPara(&pCDBuffer,
        (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    };

/*
 * Next, insert a bar into the rich text field.
 */

    if (sError = InsertBar(hNote, &pCDBuffer, &wItemSize, wBufferSize))
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (ERR(sError));
    }

/*
 *  Now insert two CDPARAGRAPH records.
 */
 
    sError = PutPara(&pCDBuffer,
        (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    }

    sError = PutPara(&pCDBuffer,
        (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    };

/*
 * Next, insert an action into the rich text field.
 */

    if (sError = InsertAction(hNote, &pCDBuffer, &wItemSize, wBufferSize))
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (ERR(sError));
    }

/*
 *  Now insert two CDPARAGRAPH records.
 */
 
    sError = PutPara(&pCDBuffer,
        (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    }

    sError = PutPara(&pCDBuffer,
        (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    };

/*
 * Next, insert a URL into the rich text field.
 */

    if (sError = InsertURL(hNote, &pCDBuffer, &wItemSize, wBufferSize))
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (ERR(sError));
    }

/*
 *  Now insert two CDPARAGRAPH records.
 */
 
    sError = PutPara(&pCDBuffer,
        (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    }

    sError = PutPara(&pCDBuffer,
        (WORD) (wBufferSize - (pCDBuffer - pCDBufferStart)));
 
    if (sError == FALSE)
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (sError);
    };

/*
 * Next, insert a file attachment into the rich text field.
 */

    if (sError = InsertFile(hNote, &pCDBuffer, &wItemSize, wBufferSize))
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (ERR(sError));
    }

/*
 *  All done creating the richtext field.  Now append it to the note.
 */

     if (sError = NSFItemAppend(hNote,
                                0,
                                "Body",
                                (WORD) strlen("Body"),
                                TYPE_COMPOSITE,
                                pCDBufferStart,
                                pCDBuffer-pCDBufferStart))

     {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
             return (ERR(sError));
     }
         
    OSUnlockObject(hMem);
    OSMemFree(hMem);
    
    return (NOERROR);
}


/***********************************************************************
 * InsertPopup
 *                The steps needed to do this are:
 *
 *                - Place a CDPARAGRAPH structure in the buffer;
 *
 *                - Append a CDPABDEFINITION structure in the buffer;
 *
 *                - Append a CDPABREFERENCE structure in the buffer;
 *
 *                - Create an appropriate CDHOTSPOTBEGIN record
 *                  and append it to the buffer. This record will
 *                  contain the text that will be displayed when the
 *                  popup is "popped up".
 *
 *                - Add a CDTEXT record that will comprise the area on which
 *                  to click in order to display the popup.
 *
 *                - Add a CDHOTSPOTEND record to mark the end of the hotspot.
 *
 *
 *
 * Inputs:     hNote        - handle to the new note being created.
 *             ppCDBuffer   - Handle to buffer containing CD record 
 *                            being created.
 *             pwItemSize   - current length of item.
 *             wBufferSize  - total size of CD buffer.
 *             
 * Outputs:    None.
 *************************************************************************/


STATUS InsertPopup(NOTEHANDLE hNote,
                   char FAR * FAR *ppCDBuffer,
                   WORD FAR *pwItemSize,
                   WORD wBufferSize)

{
    STATUS         sError;
    CDHOTSPOTBEGIN pHotSpotBegin;
    char           szPopUpContentsString[] = "This is the text of the popup";
    char           szPopUpText[] = "Click Here";
    char far      *bufPtr;
  
/*
 *  Set various flags 
 */
    
    pHotSpotBegin.Type = HOTSPOTREC_TYPE_POPUP;
    pHotSpotBegin.Flags = HOTSPOTREC_RUNFLAG_BEGIN | HOTSPOTREC_RUNFLAG_BOX;

/*
 *  Append data string, set length of data string in structure.
 */

    pHotSpotBegin.DataLength = sizeof(szPopUpContentsString); 

/*
 *  Set the header info.
 */
    
    pHotSpotBegin.Header.Signature = SIG_CD_HOTSPOTBEGIN;
    pHotSpotBegin.Header.Length = ODSLength(_CDHOTSPOTBEGIN)
                                    + pHotSpotBegin.DataLength;

 

    *pwItemSize += pHotSpotBegin.Header.Length;

    if (*pwItemSize %2)
        *pwItemSize +=1;


    ODSWriteMemory( (void far * far *)ppCDBuffer, _CDHOTSPOTBEGIN, &pHotSpotBegin, 1 );
        
    memcpy(*ppCDBuffer, 
    szPopUpContentsString, 
    sizeof(szPopUpContentsString));
        
    *ppCDBuffer += sizeof(szPopUpContentsString);
    if (((LONG)*ppCDBuffer) % 2)
        *ppCDBuffer += 1;

/*
 * Done with the CDHOTSPOTBEGIN. Now add a CDTEXT item that will deliniate
 * the area on which to click to activate the popup.  This could be
 * a graphic as well as a string.
 */
 
    bufPtr = *ppCDBuffer;

    sError = PutText(ppCDBuffer, szPopUpText, 
        (WORD)(wBufferSize - *pwItemSize), 0);

    if (sError == FALSE)
    {
        return (sError);
    }
        
    *pwItemSize += *ppCDBuffer - bufPtr;
    bufPtr = *ppCDBuffer;

        
/*
 * Done with the CDTEXT item.  Now insert a CDHOTSPOTEND item.
 */         

    if (sError = PutHotSpotEnd(ppCDBuffer,
                           (WORD)(wBufferSize - *pwItemSize),
                           pwItemSize))
    {
        return (ERR(sError));
    }
  
    *pwItemSize += *ppCDBuffer - bufPtr;
    
/*
 *  Done constructing popup.
 */
 
    return (NOERROR);
}

/*************************************************************************
 * InsertButton
 *      To define the button:
 *
 *      - Append to the CD buffer a CDHOTSPOTBEGIN record, with the
 *        flag member set to HOTSPOTREC_REC_BUTTON, and with the other
 *        data members set appropriately. The formula to be run when
 *        the button is activated is appended to the CDHOTSPOTBEGIN record.
 *
 *      - A CDBUTTON record, which defines the appearance of the button.
 *
 *      - A CDHOTSPOTEND record, to mark the end of the button definition.
 *
 *
 * Inputs:     hNote       - handle to the new note being created.
 *             ppCDBuffer  - handle to buffer containing CD record being 
 *                           created.
 *             pwItemSize  - current length of item.
 *             wBufferSize - total size of CD buffer.
 *             
 * Outputs:    None.
 *************************************************************************/

STATUS InsertButton(NOTEHANDLE hNote,
                    char FAR * FAR *ppCDBuffer,
                    WORD FAR *pwItemSize,
                    WORD wBufferSize)

{
    STATUS         sError;                   /* Domino and Notes error status        */
    CDHOTSPOTBEGIN pHotSpotBegin;
    char           szButtonText[] = "Print...";
    char           szButtonFormula[] = "@Command([FilePrint])";
    char far      *bufPtr;
        
    FORMULAHANDLE  hFormula;
    char *pFormula;        /* pointer to compiled formula. */
    WORD wFormulaLen = 0;
    WORD wdc;              /* "We Don't Care" - We're not interested in some 
                            * of the info passed back by NSFFormulaCompile(), 
                            * but the function call requires the addresses of 
                            * several words to be passed in. The address of 
                            * this word is used for all parameters in which 
                            * we have no interest.
                            */

    /*
     * Set various flags
     */
    
    pHotSpotBegin.Type = HOTSPOTREC_TYPE_BUTTON;
    pHotSpotBegin.Flags = HOTSPOTREC_RUNFLAG_BEGIN |
                                  HOTSPOTREC_RUNFLAG_NOBORDER;

/*
 *  Compile the button formula, append compiled formula to
 *  HotSpotBegin data structure.
 */

    sError = NSFFormulaCompile(NULL,
                               0,
                               szButtonFormula,
                               (WORD)strlen(szButtonFormula),
                               &hFormula,
                               &wFormulaLen,
                               &wdc, &wdc, &wdc, &wdc, &wdc);
                               
    if (sError)
    {
        return (ERR(sError));
    }
        
        pHotSpotBegin.DataLength = wFormulaLen;
        
/*
 *  Set the header info.
 */
    
    pHotSpotBegin.Header.Signature = SIG_CD_HOTSPOTBEGIN;
    pHotSpotBegin.Header.Length = ODSLength(_CDHOTSPOTBEGIN)
                                    + pHotSpotBegin.DataLength;

   
    *pwItemSize += pHotSpotBegin.Header.Length;

    if (*pwItemSize %2)
        *pwItemSize +=1;

    ODSWriteMemory( (void far * far *)ppCDBuffer, _CDHOTSPOTBEGIN, &pHotSpotBegin, 1 );
                
    pFormula = (char far *) OSLockObject(hFormula);
    
    memcpy(*ppCDBuffer, 
            pFormula, 
            wFormulaLen);

    OSUnlockObject(hFormula);    /* unlock and free formula's memory.  */

    OSMemFree(hFormula);         
        
    *ppCDBuffer += wFormulaLen;
        
    if (((LONG)*ppCDBuffer) % 2)
        *ppCDBuffer += 1;


/*
 * Done with the CDHOTSPOTBEGIN. Now add a CDBUTTON item to define the
 * appearance of the button being inserted.
 */
        
    bufPtr = *ppCDBuffer;
    if (sError = PutButton(ppCDBuffer,
                      (char *)szButtonText,
                      (WORD)(wBufferSize - *pwItemSize),
                      pwItemSize))
    {
        return (ERR(sError));
    }
        
    *pwItemSize += *ppCDBuffer - bufPtr;

/*
 * Done with the CDBUTTON item.  Now insert a CDHOTSPOTEND item.
 */         

    if (sError = PutHotSpotEnd(ppCDBuffer,
                           (WORD)(wBufferSize - *pwItemSize),
                           pwItemSize))
    {
        return (ERR(sError));
    }

/*
 *  Done defining the button.
 */
    
    return (NOERROR);
}

/***********************************************************************
 * InsertBar
 *                The steps needed to do this are:
 *
 *                - Create a CDV4HOTSPOTBEGIN record
 *                  and append it to the buffer. 
 *
 *                - Add a CDBAR record that will contain the section title
 *                  and other information for the section.
 *
 *                - Add an empty CDTEXT record
 *
 *                - Add a CDPARAGRAPH structure to the buffer;
 *
 *                - Append a CDPABREFERENCE structure in the buffer;
 *
 *                - Add a CDTEXT record that will contain the contents of the 
 *                  section.
 *
 *                - Add a CDV4HOTSPOTEND record to mark the end of the hotspot.
 *
 *
 *
 * Inputs:     hNote       - handle to the new note being created.
 *             ppCDBuffer  - Handle to buffer containing CD record being 
 *                           created.
 *             pwItemSize  - current length of item.
 *             wBufferSize - total size of CD buffer.
 *             
 * Outputs:    None.
 *************************************************************************/


STATUS InsertBar(NOTEHANDLE hNote,
                 char FAR * FAR *ppCDBuffer,
                 WORD FAR *pwItemSize,
                 WORD wBufferSize)

{
    STATUS         sError;
    CDHOTSPOTBEGIN HotSpotBegin;
    char           szBarString[] = "This is my section title";
    char           szSectionText[] = "This is text in my section";
    char far      *bufPtr;
  
/*
 *  Set various flags 
 */
    
    HotSpotBegin.Type = HOTSPOTREC_TYPE_BUNDLE;
    HotSpotBegin.Flags = HOTSPOTREC_RUNFLAG_BEGIN | HOTSPOTREC_RUNFLAG_NOBORDER;

/*
 *  Append data string, set length of data string in structure.
 */

    HotSpotBegin.DataLength = 0; 

/*
 *  Set the header info.
 */
    
    HotSpotBegin.Header.Signature = SIG_CD_V4HOTSPOTBEGIN;
    HotSpotBegin.Header.Length = ODSLength(_CDHOTSPOTBEGIN);

 

    *pwItemSize += HotSpotBegin.Header.Length;

    if (*pwItemSize %2)
        *pwItemSize +=1;


    ODSWriteMemory( (void far * far *)ppCDBuffer, _CDHOTSPOTBEGIN, &HotSpotBegin, 1 );
        
    bufPtr = *ppCDBuffer;

/*
 * Done with the CDHOTSPOTBEGIN. Now add a CDBAR item to define the
 * appearance of the bar being inserted.
 */

    if (sError = PutBar(ppCDBuffer,
                      (char *)szBarString,
                      (WORD)(wBufferSize - *pwItemSize),
                      pwItemSize))
    {
        return (ERR(sError));
    }
        
    *pwItemSize += *ppCDBuffer - bufPtr;
    bufPtr = *ppCDBuffer;

    sError = PutText(ppCDBuffer, "", (WORD)(wBufferSize - *pwItemSize), 0);

    if (sError == FALSE)
    {
        return (sError);
    }
        
    sError = PutPara(ppCDBuffer,(WORD) (wBufferSize - *pwItemSize));
 
    if (sError == FALSE)
    {
        return (sError);
    }

/*
 * Then write a CDPABREFERENCE
 */    

    if (sError = PutPabRef(ppCDBuffer,
                           (WORD)1,
                           (WORD)(wBufferSize - *pwItemSize),
                           pwItemSize))
    {
        return (sError);
    }

    sError = PutText(ppCDBuffer, szSectionText, (WORD)(wBufferSize - *pwItemSize), 0);

    if (sError == FALSE)
    {
        return (sError);
    }
        
/*
 * Done with the CDTEXT item.  Now insert a CDHOTSPOTEND item.
 */         

    if (sError = PutV4HotSpotEnd(ppCDBuffer,
                           (WORD)(wBufferSize - *pwItemSize),
                           pwItemSize))
    {
        return (ERR(sError));
    }
  
    *pwItemSize += *ppCDBuffer - bufPtr;
    
/*
 *  Done constructing popup.
 */
 
    return (NOERROR);
}

/***********************************************************************
 * InsertAction
 *                The steps needed to do this are:
 *
 *                - Create an appropriate CDV4HOTSPOTBEGIN record
 *                  and append it to the buffer. 
 *
 *                - Add a TYPE_ACTION word to the buffer.
 *                - Add a CDACTIONHEADER structure to the buffer.
 *                - Add a CDACTIONSENDMAIL structure to the buffer..
 *                - Add a CDTEXT record that will contain the URL address 
 *                - Add a CDV4HOTSPOTEND record to mark the end of the hotspot.
 *
 *
 * Inputs:     hNote       - handle to the new note being created.
 *             ppCDBuffer  - Handle to buffer containing CD record being 
 *                           created.
 *             pwItemSize  - current length of item.
 *             wBufferSize - total size of CD buffer.
 *             
 * Outputs:    None.
 *************************************************************************/


STATUS InsertAction(NOTEHANDLE hNote,
                    char FAR * FAR *ppCDBuffer,
                    WORD FAR *pwItemSize,
                    WORD wBufferSize)

{
    STATUS         sError;
    CDHOTSPOTBEGIN HotSpotBegin;
    WORD           ActionType = TYPE_ACTION;
    WORD           wToLength, wSubjectLength, wBodyLength;
    char           far *bufPtr;
    char           szTitleText[] = "This is an action that sends a message";

    /* ToInfo contains the name of the person the action will send the 
       mail to. */
    char           ToInfo[] = "Jan Doe/CAM/Lotus"; 

    char           SubjectField[] = "This is from an API program";
    char           BodyField[] = "This is the body of the message";  

/*
 *  Set various flags 
 */
    
    HotSpotBegin.Type = HOTSPOTREC_TYPE_HOTREGION;
    HotSpotBegin.Flags = HOTSPOTREC_RUNFLAG_BEGIN | HOTSPOTREC_RUNFLAG_ACTION 
                         | HOTSPOTREC_RUNFLAG_BOX;

/*
 *  Set data length
 */

    /* calculate string lengths and add the null, and if odd add padding byte */
    wToLength = strlen(ToInfo) + 1;
    if (wToLength % 2)
        wToLength += 1;
    
    wSubjectLength = strlen(SubjectField) + 1;
    if (wSubjectLength % 2)
        wSubjectLength += 1;
    
    wBodyLength = strlen(BodyField) + 1;
    if (wBodyLength % 2)
        wBodyLength += 1;
     
    HotSpotBegin.DataLength = 2 + (BYTE)ODSLength(_CDACTIONHEADER) + 
                             ODSLength(_CDACTIONSENDMAIL) + wToLength + wSubjectLength 
                             + wBodyLength; 
/*
 *  Set the header info.
 */
    
    HotSpotBegin.Header.Signature = SIG_CD_V4HOTSPOTBEGIN;
    HotSpotBegin.Header.Length = ODSLength(_CDHOTSPOTBEGIN) + 
                                 HotSpotBegin.DataLength;

 
    *pwItemSize += HotSpotBegin.Header.Length;

    if (*pwItemSize %2)
        *pwItemSize +=1;


    ODSWriteMemory( (void far * far *)ppCDBuffer, _CDHOTSPOTBEGIN, &HotSpotBegin, 1 );


    bufPtr = *ppCDBuffer;

/*
 * Done with the CDHOTSPOTBEGIN. Now add the action
 */

    if (sError = PutAction(ppCDBuffer,
                      (LPSTR)ToInfo,
                      (LPSTR)SubjectField,
                      (LPSTR)BodyField,
                      (WORD)(wBufferSize - *pwItemSize),
                      pwItemSize))
    {
        return (ERR(sError));
    }

    *pwItemSize += *ppCDBuffer - bufPtr;

    sError = PutText(ppCDBuffer, szTitleText, (WORD)(wBufferSize - *pwItemSize),0);

    if (sError == FALSE)
    {
        return (sError);
    }
        
/*
 * Done with the CDTEXT item.  Now insert a CDHOTSPOTEND item.
 */         

    if (sError = PutV4HotSpotEnd(ppCDBuffer,
                           (WORD)(wBufferSize - *pwItemSize),
                           pwItemSize))
    {
        return (ERR(sError));
    }
  
    *pwItemSize += *ppCDBuffer - bufPtr;
    
/*
 *  Done constructing Action.
 */
 
    return (NOERROR);
}


/***********************************************************************
 * InsertURL
 *                The steps needed to do this are:
 *
 *                - Create a CDV4HOTSPOTBEGIN record
 *                  and append it to the buffer. 
 *
 *                - Add a CDTEXT record that will contain the URL address 
 *                - Add a CDV4HOTSPOTEND record to mark the end of the hotspot.
 *
 *
 *
 * Inputs:     hNote       - handle to the new note being created.
 *             ppCDBuffer  - Handle to buffer containing CD record being 
 *                           created.
 *             pwItemSize  - current length of item.
 *             wBufferSize - total size of CD buffer.
 *             
 * Outputs:    None.
 *************************************************************************/


STATUS InsertURL(NOTEHANDLE hNote,
                 char FAR * FAR *ppCDBuffer,
                 WORD FAR *pwItemSize,
                 WORD wBufferSize)

{
    STATUS         sError;
    CDHOTSPOTBEGIN HotSpotBegin;
    char far       *bufPtr;
    char           szURL[] = "http://www.lotus.com";

/*
 *  Set various flags 
 */
    
    HotSpotBegin.Type = HOTSPOTREC_TYPE_HOTLINK;
    HotSpotBegin.Flags = HOTSPOTREC_RUNFLAG_BEGIN | 
                         HOTSPOTREC_RUNFLAG_NOBORDER | 
                         HOTSPOTREC_RUNFLAG_INOTES;

/*
 *  Set data length
 */

    HotSpotBegin.DataLength = sizeof(szURL); 

/*
 *  Set the header info.
 */
    
    HotSpotBegin.Header.Signature = SIG_CD_V4HOTSPOTBEGIN;
    HotSpotBegin.Header.Length = ODSLength(_CDHOTSPOTBEGIN) + 
                                 HotSpotBegin.DataLength;

 

    *pwItemSize += HotSpotBegin.Header.Length;

    if (*pwItemSize %2)
        *pwItemSize +=1;

    bufPtr = *ppCDBuffer;

    ODSWriteMemory( (void far * far *)ppCDBuffer, _CDHOTSPOTBEGIN, &HotSpotBegin, 1 );
        
    memcpy(*ppCDBuffer, szURL, sizeof(szURL));

    *ppCDBuffer += sizeof(szURL);
        
    if (((LONG) *ppCDBuffer) % 2)
        *ppCDBuffer += 1;


    sError = PutText(ppCDBuffer, szURL, 
        (WORD)(wBufferSize - *pwItemSize), HOTSPOTREC_TYPE_HOTLINK);

    if (sError == FALSE)
    {
        return (sError);
    }
        
/*
 * Done with the CDTEXT item.  Now insert a CDHOTSPOTEND item.
 */         

    if (sError = PutV4HotSpotEnd(ppCDBuffer,
                           (WORD)(wBufferSize - *pwItemSize),
                           pwItemSize))
    {
        return (ERR(sError));
    }
  
    *pwItemSize += *ppCDBuffer - bufPtr;
    
/*
 *  Done constructing URL.
 */
 
    return (NOERROR);
}


/***********************************************************************
 * InsertFile
 *                The steps needed to do this are:
 *
 *                - Call NSFNoteAttachFile to create a $FILE item.
 *
 *                - Create an appropriate CDHOTSPOTBEGIN record
 *                  and append it to the buffer. 
 *
 *                - Add a CDTEXT record that will contain the name of the 
 *                  attached file.
 *
 *                - Add a CDHOTSPOTEND record to mark the end of the hotspot.
 *
 *
 * Inputs:     hNote       - handle to the new note being created.
 *             ppCDBuffer  - Handle to buffer containing CD record being 
 *                           created.
 *             pwItemSize  - current length of item.
 *             wBufferSize - total size of CD buffer.
 *             
 * Outputs:    None.
 *************************************************************************/


STATUS InsertFile(
        NOTEHANDLE hNote,
        char FAR * FAR *ppCDBuffer,
        WORD FAR *pwItemSize,
        WORD wBufferSize)
{
    STATUS         sError;
    CDHOTSPOTBEGIN HotSpotBegin;
    char far       *bufPtr;

#if !defined(UNIX)
    char szSourceFileName[] = 
        "c:\\notesapi\\api_v5\\samples\\richtext\\hotspot\\readme.txt";
#else
    char szSourceFileName[] = 
        "/opt/lotus/notesapi/samples/richtext/hotspot/readme.txt";
#endif

    char szAttachLinkName[] = "attach.lnk";
    char szAttachFileName[] = "readme.txt";

    if (sError = NSFNoteAttachFile( hNote,
                                    ITEM_NAME_ATTACHMENT,
                                    (WORD) strlen(ITEM_NAME_ATTACHMENT),
                                    szSourceFileName,
                                    szAttachLinkName,
                                    EFLAGS_INDOC | HOST_LOCAL | COMPRESS_NONE))
    {
        return(ERR(sError));
    }

/*
 *  Set various flags 
 */
    
    HotSpotBegin.Type = HOTSPOTREC_TYPE_FILE;
    HotSpotBegin.Flags = HOTSPOTREC_RUNFLAG_BEGIN | HOTSPOTREC_RUNFLAG_NOBORDER;

/*
 *  Set data length
 */

    HotSpotBegin.DataLength = strlen(szAttachLinkName) + strlen(szAttachFileName) + 2;

/*
 *  Set the header info.
 */
    
    HotSpotBegin.Header.Signature = SIG_CD_HOTSPOTBEGIN;
    HotSpotBegin.Header.Length = ODSLength(_CDHOTSPOTBEGIN) + HotSpotBegin.DataLength;

    *pwItemSize += HotSpotBegin.Header.Length;

    if (*pwItemSize %2)
        *pwItemSize +=1;

    bufPtr = *ppCDBuffer;

    ODSWriteMemory( (void far * far *)ppCDBuffer, _CDHOTSPOTBEGIN, &HotSpotBegin, 1 );
        
    memcpy(*ppCDBuffer, szAttachLinkName, sizeof(szAttachLinkName));
    *ppCDBuffer += sizeof(szAttachLinkName);

    memcpy(*ppCDBuffer, szAttachFileName, sizeof(szAttachFileName));
    *ppCDBuffer += sizeof(szAttachFileName);

    if (((LONG) *ppCDBuffer) % 2)
        *ppCDBuffer += 1;

    sError = PutText(ppCDBuffer, szAttachFileName, (WORD)(wBufferSize - *pwItemSize), 0);

    if (sError == FALSE)
    {
        return (sError);
    }
        
/*
 * Done with the CDTEXT item.  Now insert a CDHOTSPOTEND item.
 */         

    if (sError = PutHotSpotEnd(ppCDBuffer,
                           (WORD)(wBufferSize - *pwItemSize),
                           pwItemSize))
    {
        return (ERR(sError));
    }
  
    *pwItemSize += *ppCDBuffer - bufPtr;
    
/*
 *  Done constructing file attachment.
 */
 
    return (NOERROR);
}
