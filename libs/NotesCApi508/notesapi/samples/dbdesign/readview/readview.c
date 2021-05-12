/****************************************************************************

    PROGRAM:    readview

    FILE:       readview.c

    PURPOSE:    Shows how to read a view note in a database.

****************************************************************************/
 
/* C header files     */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Lotus C API for Domino and Notes Header files.  */

#include <lapicinc.h>

#include <global.h>
#include <nsfdata.h>
#include <nif.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <editods.h>
#include <osmem.h>
#include <osmisc.h>     /*  FOR OSLoadString */
#include <stdnames.h>
#include <nsfsearc.h>   /* For NSFFormulaDecompile */
#include <viewfmt.h>
#if defined(OS400)
#include <misc.h>
#endif



#include <lapiplat.h>

/*
 * Local header files
 */

#include "readview.h"

/************************************************************************

    FUNCTION:   main or NotesMain C API for Domino and Notes subroutine

    ALGORITHM:
      - readview first opens the database readview.nsf.  It finds the
        NoteID of the view note for the view called "View A" by
        calling NIFFindView.  readview then opens the view note.

      - The title of the database and the date/time of last modification
        is obtained by calling NSFItemInfo twice, once for each piece of info.
        (The database title is explicitly defined in this program, so this
        call was not really needed, but it demonstrates the NSFItemInfo
        function).

      - readview then calls the function NSFItemIsPresent() to see if a
        VIEW_FORMULA_TIME_ITEM is present.  If so, the view contains one or
        more time relative formulas.
        
      - The program then calls NSFItemInfo again to get the block of
        data describing the columns in the view.

*************************************************************************/
 
LAPI_MAIN
{
    NOTEHANDLE hNote; 
    STATUS sError = NOERROR;
    DBHANDLE hDB;

    char szViewName[] = "View A";
    char szFileName[] = "readview.nsf";

    char szTitleString[128];   /* View title will be constructed here.   */
    char szTimeDate[MAXALPHATIMEDATE + 1];
    char szColTitle[128];
    
    TIMEDATE   ModTimeDate;    
    DWORD      dwTextBufferLength = TEXT_BUFFER_LENGTH;
    WORD       ClassView = NOTE_CLASS_VIEW;
    DWORD      dwLength;
    WORD       wDataType;
    NOTEID     ViewNoteID;        /* Note id of the View document. */
    BLOCKID    ValueBlockID;
    char far   *pData;
    char far   *pPackedData;
    char far   *pFormula;
    char far   *pFormulaText, *pTemp;
    WORD       wFormulaTextLen;
    HANDLE     hFormulaText;
    
    WORD       wStringLen;
    BOOL       bTimeRelativeFormulae;
    WORD       wColumn;

    VIEW_FORMAT_HEADER *pHeaderFormat;
    VIEW_TABLE_FORMAT  *pTableFormat;
    VIEW_TABLE_FORMAT2  *pTableFormat2;
    VIEW_COLUMN_FORMAT *pColumnFormat;

    VIEW_FORMAT_HEADER  formatHeader;
    VIEW_TABLE_FORMAT tableFormat;
    VIEW_TABLE_FORMAT2   tableFormat2;
    VIEW_COLUMN_FORMAT   viewColumn;
    void *            tempPtr;
       
    /* Domino and Notes initialization */
    LAPI_INIT(sError);
    if (sError)
        LAPI_INIT_ERROR;
      
    printf("");
    fflush(stdout);

    /*
     * Now open the database, get the NoteID of the View note, and open the
     * View note.
     */

    if (sError = NSFDbOpen(szFileName, &hDB))
    {
        LAPI_RETURN( ERR(sError) );
    }

    if (sError = NIFFindView(hDB, szViewName, &ViewNoteID))
    {
        NSFDbClose(hDB);
        LAPI_RETURN( ERR(sError) );
    }

    if (sError = NSFNoteOpen(hDB, ViewNoteID, 0, &hNote))
    {
        NSFDbClose(hDB);
        LAPI_RETURN( ERR(sError) );
    }

    /*
     * Read the title of the View from the View note.
     */
 
    if (sError = NSFItemInfo(hNote,
                             ITEM_NAME_TEMPLATE_NAME,
                             sizeof(ITEM_NAME_TEMPLATE_NAME) - 1,
                             NULL,
                             &wDataType,
                             &ValueBlockID,
                             &dwLength))

    {
        NSFNoteClose(hNote);
        NSFDbClose(hDB);
        LAPI_RETURN( ERR(sError) );
    }

    /*
     *  Lock the block returned, write title of View to the output buffer.
     */

    pData = OSLockBlock(char, ValueBlockID);
    pData += sizeof(WORD);

    memmove(szTitleString, pData, (int) (dwLength - sizeof(WORD)));
    szTitleString[dwLength - sizeof(WORD)] = '\0';    
    printf ( "View Title:  %s\n", szTitleString);
    OSUnlockBlock(ValueBlockID);

    /*
     *  Get the time and date that the view was last modified.
     */

    NSFNoteGetInfo(hNote, _NOTE_MODIFIED, &ModTimeDate);
    if (sError = ConvertTIMEDATEToText(NULL,
                                       NULL,
                                       &ModTimeDate,
                                       szTimeDate,
                                       MAXALPHATIMEDATE,
                                       &wStringLen))
    {
        NSFNoteClose(hNote);
        NSFDbClose(hDB);
        LAPI_RETURN( ERR(sError) );
    }
                                       
    szTimeDate[wStringLen]='\0';
    printf ( "Date/Time of last modification:  %s\n",
              szTimeDate);

    /*
     * If a VIEW_FORMULA_TIME_ITEM is present, then this view contains one
     * or more time relative formulae ("@Now", for example).
     */

    bTimeRelativeFormulae = NSFItemIsPresent(hNote,
                                             VIEW_FORMULA_TIME_ITEM,
                                             sizeof(VIEW_FORMULA_TIME_ITEM) -1);
                                          
    printf ( "Time relative formulae %s exist in this view.\n", 
            (bTimeRelativeFormulae) ? "DO" : "DO NOT");


    /*
     * Get the format item.
     */

    sError = NSFItemInfo(hNote,
                          VIEW_VIEW_FORMAT_ITEM,
                          sizeof(VIEW_VIEW_FORMAT_ITEM) - 1,
                          NULL,
                          &wDataType,
                          &ValueBlockID,
                          &dwLength);

    if (sError || wDataType != TYPE_VIEW_FORMAT)
    {
        NSFNoteClose(hNote);
        NSFDbClose(hDB);
        LAPI_RETURN( ERR(sError) );
    }

    /*
     *  Lock the block returned, Get the view format and check the version.
     *  We need to do ODSMemory calls to ensure cross-platform compatibility.
     */

    pData = OSLockBlock(char, ValueBlockID);
    pData += sizeof(WORD);

    tempPtr = pData;
    ODSReadMemory( &tempPtr, _VIEW_FORMAT_HEADER, &formatHeader, 1 );
    pHeaderFormat = &formatHeader;
   
    if (pHeaderFormat->Version != VIEW_FORMAT_VERSION)
    {                   
        OSUnlockBlock(ValueBlockID);
        NSFNoteClose(hNote);
        NSFDbClose(hDB);
        LAPI_RETURN( ERR(sError) );
    }

    /*
     *  Read the table format ( which includes the view format header )
     */

    if ((pHeaderFormat->ViewStyle & VIEW_CLASS_MASK) == VIEW_CLASS_TABLE)
    {

        tempPtr = pData;
        ODSReadMemory( &tempPtr, _VIEW_TABLE_FORMAT, &tableFormat, 1 );
        pTableFormat = &tableFormat;
      
        pData += ODSLength(_VIEW_TABLE_FORMAT);  /* point past the table format */

        /*
         *  Get a pointer to the packed data, which is located after the
         *  column format structures. This data does not need to be converted
         *  into host-specific byte ordering
         */

        pPackedData = pData + (ODSLength(_VIEW_COLUMN_FORMAT) * pTableFormat->Columns);

        /*
         *  Now unpack and read the column data
         */

        for (wColumn = 1; wColumn <= pTableFormat->Columns; wColumn++)
        {
            /*
             *  Get the fixed portion of the column descriptor and
             *  validate the signature.
             */
   
            tempPtr = pData;
            ODSReadMemory( &tempPtr, _VIEW_COLUMN_FORMAT, &viewColumn, 1 );
            pColumnFormat = &viewColumn;
         
            pData += ODSLength(_VIEW_COLUMN_FORMAT);

            /*
             *  Column number
             */

            printf ( "\nColumn %d of %d\n", wColumn, pTableFormat->Columns );

            /*
             * Print Item Name, then advance data pointer
             * past it.
             */            

            memmove(szColTitle, pPackedData,pColumnFormat->ItemNameSize); 
            szColTitle[pColumnFormat->ItemNameSize] = '\0';    
            printf ( "\t\tItem Name:                  %s\n", szColTitle );
            pPackedData += pColumnFormat->ItemNameSize;

            /*
             * Get the Title string, then advance data pointer to next item.
             */  

            memmove(szColTitle, pPackedData, pColumnFormat->TitleSize);
            szColTitle[pColumnFormat->TitleSize] = '\0';    
            printf ( "\t\tTitle:                      \"%s\"\n", szColTitle);
            pPackedData += pColumnFormat->TitleSize;

            /*
             * Get the formula, advance data ptr to next item.
             */

            pFormula = pPackedData;
            pPackedData += pColumnFormat->FormulaSize;
            if (pColumnFormat->FormulaSize != 0)
            {
                sError = NSFFormulaDecompile(pFormula,
                                             FALSE,
                                             &hFormulaText,
                                             &wFormulaTextLen);
                                  
                if (sError)
                {
                    printf ( "\n# Error Decompiling Formula\n");
                    OSUnlockBlock(ValueBlockID);
                    NSFNoteClose(hNote);
                    NSFDbClose(hDB);
                    LAPI_RETURN( ERR(sError) );
                }

                /*
                 *  Get pointer to formula text.
                 */

                pFormulaText = OSLock(char, hFormulaText);
            
                /*
                 *  Copy formula text to temp storage, and null terminate it.
                 *  Then copy formula text to output buffer.
                 */

                pTemp = (char far *) malloc((size_t) wFormulaTextLen +1);

                if (pTemp != NULL)
                {                         
                    memmove(pTemp, pFormulaText, (int) wFormulaTextLen);                    
                    pTemp[wFormulaTextLen] = '\0';    

                    printf ( "\t\tFormula:                    %s\n", pTemp);
                    free (pTemp);
                }
            
                OSUnlock(hFormulaText);
                OSMemFree(hFormulaText);
            } /* end if */
                                         
            /*
             * We're not interested in the Constant Value string,
             * so advance data ptr to next item.
             */            

            pPackedData += pColumnFormat->ConstantValueSize;

            /*
             *  See if this column is a sort key or not.
             */

            printf ("\t\tSort Key:                   %s\n", 
               (pColumnFormat->Flags1 & VCF1_M_Sort) ? "YES" : "NO");

            /*
             *  See if this column is a category  or not.
             */

            printf ("\t\tCategory:                   %s\n",
               (pColumnFormat->Flags1 & VCF1_M_SortCategorize) ? "YES" : "NO");

            /*
             *  See how this column is sorted.
             */

            printf ("\t\tSort Order:                 %s\n",
               (pColumnFormat->Flags1 & VCF1_M_SortDescending) ? "Descending" : "Ascending");
            

            /*
             *  See if this column is hidden.
             */

            printf ("\t\tHidden:                     %s\n",
               (pColumnFormat->Flags1 & VCF1_M_Hidden) ? "YES" : "NO");
            

            /*
             *  See if this column is a response column.
             */

            printf ("\t\tResponse Column:            %s\n",
               (pColumnFormat->Flags1 & VCF1_M_Response) ? "YES" : "NO");
            

            /*
             *  See if this column shows details if it is a subtotaled column.
             */

            printf ("\t\tHide Detail if Subtotaled:  %s\n",
               (pColumnFormat->Flags1 & VCF1_M_HideDetail) ? "YES" : "NO");
            

            /*
             *  See if this column displays an icon INSTEAD of text as its title.
             */

            printf ("\t\tDisplay Icon:               %s\n",
               (pColumnFormat->Flags1 & VCF1_M_Icon) ? "YES" : "NO");
            

            /*
             *  See if this column is resizable at runtime.
             */

            printf ("\t\tResizable at Runtime:      %sresizable\n",
               (pColumnFormat->Flags1 & VCF1_M_NoResize) ? " NOT " : " ");

            /*
             *  See if this column is resortable at runtime.
             */

            printf ("\t\tResortable at Runtime:     %sresortable\n",
               (pColumnFormat->Flags1 & VCF1_M_ResortDescending) ? " " : " NOT ");

            if (pColumnFormat->Flags1 & VCF1_M_ResortDescending)
            {
                /*
                 *  See how this column is sorted, if resortable at runtime.
                 */

                printf ("\t\tResortable Sort Order:      %s\n",
                       (pColumnFormat->Flags1 & VCF1_S_ResortDescending) ? "Descending" : "Ascending");
            }

        } /*  End of for loop.  */


        /* At the end of the packed data is VIEW_TABLE_FORMAT2
         * We get a pointer to it, but don't display any of the data 
         * in this program 
         */
      
        tempPtr = pPackedData;
        ODSReadMemory( &tempPtr, _VIEW_TABLE_FORMAT2, &tableFormat2, 1 );
        pTableFormat2 = &tableFormat2;
        OSUnlockBlock(ValueBlockID);
      
        sError = NSFItemInfo (hNote, VIEW_FORMULA_ITEM,
                     sizeof (VIEW_FORMULA_ITEM) - 1, NULL, &wDataType,
                     &ValueBlockID, &dwLength);

        if (!sError && (wDataType == TYPE_FORMULA))
        {
            pFormula = OSLockBlock(char, ValueBlockID);      
            pFormula += sizeof(WORD);

            sError = NSFFormulaDecompile(pFormula,
                                         TRUE,
                                         &hFormulaText,
                                         &wFormulaTextLen);

            if ( !sError )
            {
                /*
                 *  Get pointer to formula text.
                 */

                pFormulaText = OSLock(char, hFormulaText);
               
                /*
                 *  Copy formula text to temp storage, and null terminate it.
                 *  Then copy formula text to output buffer.
                 */

                pTemp = (char far *) malloc((size_t) wFormulaTextLen +1);
   
                if (pTemp != NULL)
                {
                    memmove(pTemp, pFormulaText, (int) wFormulaTextLen);
                    pTemp[wFormulaTextLen] = '\0';    
      
                    printf ( "\n\nSelection View Formula: \"%s\"\n", pTemp);
                    free (pTemp);
                } /* end if */
            
                OSUnlock(hFormulaText);
                OSMemFree(hFormulaText);
            } /* end if */
                           
            if ( sError ) 
            {
                OSUnlockBlock(ValueBlockID);
                NSFNoteClose(hNote);
                NSFDbClose(hDB);
                LAPI_RETURN( sError );
            } /* end if */
        }
        else if ( sError )
        {
            NSFNoteClose(hNote);
            NSFDbClose(hDB);
            LAPI_RETURN( sError );
        } /* end if */

    } /* end if */

    /*
     *  Close the note and the database.
     */

    OSUnlockBlock(ValueBlockID);
    NSFNoteClose(hNote);
    NSFDbClose(hDB);
            
    /*
     * leave with no error
     */
    printf("\nProgram completed successfully.\n");         
    LAPI_RETURN( NOERROR );

} /* main */

