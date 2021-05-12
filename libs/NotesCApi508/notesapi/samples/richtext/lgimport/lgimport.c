/****************************************************************************

    PROGRAM:    lgimport

    FILE:       lgimport.c

    PURPOSE:    Shows how to load and call a Domino and Notes import library 
	            to import a large file into a rich text field.

    SYNTAX:     lgimport <DBname> <DLL Path> <File Path> [<Second DLL Name>]

    DESCRIPTION:
             Creates a new note in a specified database and imports     
             a file into the Body field of the new note.  The file      
             imported may be in one of several formats.  The            
             accompanying README.TXT file explains the formats          
             supported and the DLLs that are needed for each.           
                                                                        
             LGIMPORT takes either three or four arguments:             
                                                                        
                 1) The filename of the database to which the note      
                    is to be added.  If the database is located outside 
                    of the local data directory, the full path must be  
                    specified.                                          
                 2) The full path and filename to the Import DLL        
                    used to import the selected file.                   
                 3) The full path and filename to the file being        
                    imported.                                           
                 4) The name of an additional DLL needed to import this 
                    file format.  This parameter is only necessary if   
                    importing a word processing document. Otherwise     
                    This parameter is omitted.  See the accompanying    
                    README.TXT file for more on this parameter.         
                                                                        
             This example is designed for a Domino database containing   
             a form called "Simple Form" with a rich text field called  
             "Body".  The LGIMPORT test database (lgimport.nsf) supplied 
             with the Lotus C API for Domino and Notes toolkit has these 
			 characteristics.                                           
                                                                        
****************************************************************************/

/* OS includes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

/* Lotus C API for Domino and Notes includes */

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

#include <lapiplat.h>

/* local includes  */

#include "lgimport.h"

/* Function specifications  */

STATUS LNPUBLIC ImportCD(CHAR *szModulePath,
                           CHAR *szFileName,
                           CHAR *szTempName,
                           CHAR *szDLL);

STATUS LNPUBLIC AppendImportItem(NOTEHANDLE hNote,
                                   CHAR  *pszImportFile, 
                                   CHAR  *pszItemName);


/* function specification for Domino and Notes DLLs    */

STATUS (LNCALLBACKPTR ProcAddress)(VOID *IXContext, WORD Flags, 
        HMODULE hModule, CHAR *AltLibraryName, CHAR *PathName);    

/************************************************************************

    FUNCTION:   NotesMain

    PURPOSE:    Lotus C API for Domino and Notes subroutine

    ALGORITHM:

        1) Open the database and the note.

        2) Set up an EDITIMPORTDATA structure which specifies a 
        temporary file name and some default font information.  

        3) Call the specified import DLL, passing it the filename of 
        the file to import.  

        4) The DLL converts the data file into Domino and Notes-internal 
		format, and stores it as a temporary file, using the filename 
		specified in the EDITIMPORTDATA structure.  

        5) Create an in-memory structure of type TYPE_COMPOSITE, which 
        consists of a CDPARAGRAPH structure, followed by a CDPABDEFINITION 
        structure, followed by a CDPABREFERENCE structure, followed by 
        the contents of the temporary file created by the DLL.

        6) The composite structure is added to the note as the Body field.

        7) The on-disk copy of the note is updated.

        8) The note and database are closed.       

*************************************************************************/

LAPI_MAIN
{
    CHAR    achTempName[MAXPATH];
    CHAR    *szModPath, *szFilePath, *szNSFFile, *szDLL;

    HANDLE      hNewNote;
    DBHANDLE    hDbNSFFile;
    STATUS      usError=0;

    LAPI_INIT(usError);
    if (usError)
        LAPI_INIT_ERROR;

    if (argc != 4 && argc != 5)
    {
        printf("\nUsage: \n\tlgimport <NSF Filename>");
        printf(" <Import/Export DLL Name> <Import File Path>"); 
        printf(" <Second DLL Name> (if necessary)\n"); 
        LAPI_RETURN (NOERROR);
    }

    szNSFFile    = argv[1];
    szModPath    = argv[2];
    szFilePath   = argv[3];

/*  If a 2nd DLL name was entered, set szDLL to it.  Otherwise, set */
/*  szDLL to null.                                                  */

    if (argc == 5)
        szDLL = argv[4];
    else 
        szDLL = 0;
    
    /* Call the appropriate Import/Export DLL with the appropriate  */
    /* source file to create a CHAR buffer containing the data      */
    /* that will be appended to a CD buffer.                        */

    if (usError = ImportCD(szModPath, szFilePath, achTempName, szDLL))
    {
        printf("\nUnable to create temporary file. Terminating...\n");
        goto Done;
    }

    /* Open the Database, assuming it's been created with the   */
    /* template shipped with this demo.                         */
    
    if (usError = NSFDbOpen(szNSFFile, &hDbNSFFile))
    {
        printf("\nCannot open database '%s'. Terminating...\n", szNSFFile);
        goto Done;
    }

    /* Create a Note */
    
    if (usError = NSFNoteCreate(hDbNSFFile, &hNewNote))
    {
        printf("\nCannot create new note. Terminating...\n");
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        goto Done;
    }

    /* Add the Form name  */
    
    if (usError = NSFItemSetText(hNewNote,
                                 "Form",
                                 "Simple Form",
                                 (WORD) strlen("Simple Form")))
    {
        printf("\nError while setting Form name. Terminating...\n");
        
        NSFNoteClose(hNewNote);    /* ERROR - Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        goto Done;
    }

    /*  Now add the imported data.  */
    
    if (usError = AppendImportItem(hNewNote, achTempName, "Body"))
    {
        printf("\nError while adding rich text.  Terminating...\n");
        NSFNoteClose(hNewNote);    /* ERROR - Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        goto Done;
    }

    /* write the note */

    if (usError = NSFNoteUpdate(hNewNote, 0))
    {
        printf("\nError writing new Note. Terminating..\n");
        NSFNoteClose(hNewNote);    /* ERROR - Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        goto Done;
    }

    /* Start cleaning up.  First, Close the Note */
    
    if (usError = NSFNoteClose(hNewNote))
            printf("\nUnable to close Note.  Terminating..\n");
    
    /* Now close the database.              */
    
    if (usError = NSFDbClose(hDbNSFFile))
        printf("\nError closing database '%s'. Terminating...\n, szNSFFile");

Done:
    LAPI_RETURN (ERR(usError));        /* Return Domino and Notes error code.  */
}


/**********************************************************************

   FUNCTION:   ImportCD

   PURPOSE:   Loads the specified DLL. Sets up an EDITIMPORTDATA         
              structure and invokes the DLL, passing this structure as  
              input.  The DLL converts the file to be imported to an    
              intermediate format and stores it in a temporary file.    
              Ths funtion then returns the name of the temp file in     
              szTempName.                                               
                                                                        
   Inputs:    szModulePath - name of import DLL                         
              szFileName   - name of file to be imported                
   Outputs:   szTempName   - Name of temp file containing imported data 

************************************************************************/

STATUS LNPUBLIC ImportCD(CHAR *szModulePath, CHAR *szFileName,
                           CHAR *szTempName, CHAR *szDLL)
{
    EDITIMPORTDATA EditImportData;  /* Import DLL data structure                 */
    HMODULE hmod;                   /* module handle                             */
    STATUS Error;                   /* Return status from Domino and Notes calls */
    CHAR *FileName;                 /* File name to be imported                  */
    CHAR TempName[] = "DEFAULT.CD"; /* Temp Filename for import.                 */
    CHAR *ModuleName;               /* pointer to DLL module name                */
    CHAR *SecondDLLName;

    ModuleName    = szModulePath;
    FileName      = szFileName;
    SecondDLLName = szDLL;
    
    /* Use OSLoadLibrary to load the import DLL and return a pointer to */
    /* the main entry point.                                             */
   
    if (Error = OSLoadLibrary (ModuleName, (DWORD)0, &hmod, &ProcAddress))
    {
        printf ("OSLoadLibrary failed.\n");
        goto Done;
    }

    /* Set up the EditImportData data structure with a Default          */
    /* filename for the library to do its report to.  If the import     */
    /* succeeds, this file will contain a set of compound document      */
    /* data strucures formatted in the  same manner as they would be    */
    /* if they were loaded in memory; the records start on even byte    */
    /* boundaries and contain a signature, length, the signature-       */
    /* specific data structure (if any), then the  signature-specific   */
    /* data.                                                            */

      strcpy (EditImportData.OutputFileName, TempName);
      printf ("Temp filename is %s.\n", EditImportData.OutputFileName);
   
    /* Assign the default fontid */

      EditImportData.FontID = DEFAULT_FONT_ID;

    /* Call the ProcAddress() function whose address we located within  */
    /* the DLL loaded above.  This is the SAME argument set that would  */
    /* be used by an import/export DLL written to handle a non-standard */
    /* file format.                                                     */
    /*                                                                  */
    /* The ProcAddress() function can import multiple files.  Since     */
    /* only one file is being imported in this example, the flags will  */
    /* indicate that the file is the first (and also last) file to be   */
    /* imported.                                                        */
    /*                                                                  */
    /* If a word processing document is being imported, the parameter   */
    /* SecondDLLName will be a pointer to the name of the second DLL    */
    /* that was entered on the command line.  See the README.TXT file   */
    /* for information on how to obtain the name of the 2nd DLL.  If a  */
    /* non-word processing document is being imported, this paramter    */
    /* was not entered on the command line, so SecondDLLName will be    */
    /* a pointer to a null string.                                      */
     

    if (Error = (*ProcAddress) (&EditImportData,    
        IXFLAG_FIRST | IXFLAG_LAST,         /* Both 1st and last import */
        0,                                  /* Use default hmodule      */
        SecondDLLName,                      /* 2nd DLL, if needed.      */
        FileName))                          /* File to import.          */
        {
            printf ("Call to DLL Entry point failed.\n");
            goto Done;
        }

    /* return the temp filename to calling routine */
    
    strcpy (szTempName, EditImportData.OutputFileName);

Done:
    /* Free the DLL and return */
	 OSFreeLibrary(hmod);
    return Error;

}

/************************************************************************

    FUNCTION:   AppendImportItem 
    
    PURPOSE:    Adds a Rich Text item to the note that is being      
                  created.  


    ALGORITHM:   The steps needed to do this are:             
                                                                         
                  - Allocate a buffer of length CD_BUFFER_LENTGTH;       
                                                                         
                  - Place a CDPARAGRAPH structure in the buffer;         
                                                                         
                  - Append a CDPABDEFINITION structure in the buffer;    
                                                                         
                  - Append a CDPABREFERENCE structure in the buffer;     
                                                                         
                  - Copy CD records from the temp file created by        
                    ImportCD into the buffer one at a time until the     
                    the buffer is roughly CD_HIGH_WATER_MARK bytes long. 
                                                                         
                  - Append the buffer to the note, in the "Body" field.  
                                                                         
                  - While there are more CD records in the temp file,    
                    copy them into the buffer (starting at the beginning 
                    of the buffer, and appending the buffer to the note  
                    when the buffer size reaches CD_HIGH_WATER_MARK.     
                                                                         
    INPUTS:
      hNote       - handle to the new note being created.       
      pszCDFile   - pointer to name of temporary file.          
      pszItemName - pointer to name of richtext item.           

*************************************************************************/
                                                                         
STATUS LNPUBLIC AppendImportItem(NOTEHANDLE hNote,
                                 CHAR *pszCDFile,
                                 CHAR *pszItemName)
{
    STATUS sError;         /* Domino and Notes error status                 */
    BOOL bError;           /* Returncode from PutPara, PutPabDef, PutPabRef */
    char *pCDBuffer;       /* Rich Text memory buffer                       */
    char *pCurrent;        /* Pointer to current location of buffer         */

    BYTE *pbSig;           /* Byte pointer to start of new CD record        */
    WORD wSig;             /* Signature of current CD record                */
    WORD wCDRecordLength;  /* Length of current CD record                   */

    long lCombinedLength;

    WORD wCDBufferLength = CD_BUFFER_LENGTH; /* Length of current CD buffer */
    long lLength;                            /* Length of current read buffer*/
    WORD wReadLength;                        /* Length of current read buffer*/

    WORD dwPos = sizeof(WORD);   /* Index for buffer manipulation           */
    long longpos = sizeof(WORD); /* Initialy seek past TYPE_COMPOSITE       */
                                 /*      at start of file                   */
    long ltmpItemLength ;
    WORD    wItemLength;         /* Index for buffer manipulation           */
    BOOL    bFlag = FALSE;       /* termination flag                        */
    int     CDFileFD;


    CDFileFD = open (pszCDFile, O_RDWR|O_BINARY);
    if (CDFileFD  <= 0)
    {
        /* Leave if error returned...                    */
			
        unlink (pszCDFile);
        return (ERR_APPEND_RICHTEXT_ERROR);
    }

    /* Allocate a buffer to read file into               */

    pCDBuffer = malloc(wCDBufferLength);
    if (pCDBuffer == (char *) NULL)
    {
        /* Leave if error returned...                    */

        close (CDFileFD);
        unlink (pszCDFile);
        return (ERR_APPEND_RICHTEXT_ERROR);
    }

	 /* Keep a pointer to our current position in the buffer. */
	 
	 pCurrent = pCDBuffer;

    /* Set start length to zero  */           

    wItemLength = 0;

    /*  Put a paragraph record in buffer.  */

    bError = PutPara(&pCurrent, 
                     (WORD)(wCDBufferLength-(pCurrent-pCDBuffer)));
                     
    if (bError == FALSE)
    {
        printf ("Error adding paragraph record.  Terminating...");
        free (pCDBuffer);
        close (CDFileFD);
        unlink (pszCDFile);
        return (ERR_APPEND_RICHTEXT_ERROR);

    }

    /* Setup a pabdef         */

    bError = PutPabDef(&pCurrent, 
                           (WORD) 1, 
                           (WORD)(wCDBufferLength-(pCurrent-pCDBuffer)),
                           JUSTIFY_LEFT);

    /* Leave if error returned...   */
        
    if (bError == FALSE)
    {
        printf ("Error adding paragraph definition record.  Terminating...");
        free (pCDBuffer);
        close (CDFileFD);
        unlink (pszCDFile);
        return (ERR_APPEND_RICHTEXT_ERROR);
    }

    
    /* Now add a pabref     */

    bError = PutPabRef(&pCurrent, 
                           (WORD) 1, 
                           (WORD)(wCDBufferLength-(pCurrent-pCDBuffer)));

	 wItemLength=pCurrent-pCDBuffer;

    /* Leave if error returned...    */

    if (bError == FALSE)

    {
        printf ("Error adding paragraph reference record.  Terminating...");
        free (pCDBuffer);
        close (CDFileFD);
        unlink (pszCDFile);
        return (ERR_APPEND_RICHTEXT_ERROR);
    }

    /* Keep on writing items until entire cd file hase been appended   */

    while (bFlag == FALSE)
    {
		 /* Seek file to end of previous CD record   */

        if (lseek (CDFileFD, longpos, SEEK_SET) != longpos)
        {
            /* Leave if error returned...           */

            free (pCDBuffer);
            close (CDFileFD);
            unlink (pszCDFile);
            return (ERR_APPEND_RICHTEXT_ERROR);
        }

        /* Read the contents of the file into memory  */

        wReadLength = read(CDFileFD, 
                           &pCDBuffer[wItemLength], 
                           (WORD)(wCDBufferLength - wItemLength));

        /* check for error    */

        if (wReadLength == 0xffff)
        {
            /* Leave if error returned...    */

            free (pCDBuffer);
            close (CDFileFD);
            unlink (pszCDFile);
            return (ERR_APPEND_RICHTEXT_ERROR);
        }

		
		/* See whether the contents will fit in current item....  */

        if (wReadLength < CD_HIGH_WATER_MARK)
        {
        /* we can fit what is left in a single buffer and leave  */

            bFlag = TRUE;
            wItemLength += wReadLength;
        }
        else
        {
        /* 
         * Parse the buffer one CD record at a time, adding up the lengths
         * of the CD records.  When the length approaches CD_HIGH_WATER_MARK,
         * append the buffer to the note.  Set the file pointer to the first 
         * record not parsed, read from the temp file into the buffer again,
         * and repeat until end of temp file.
         * 
         * All CD records begin with a signature word that indicates its
         * type and record length.  The low order byte is the type, and 
         * the high order byte is the length.  If the indicated length is 0,
         * then the next DWORD (32 bits) contains the record length.  If the 
         * indicated length is 0xff, the next WORD (16 bits) contains the 
         * recordlength.   Else, then the high order BYTE, itself, contains  
		 * the record length.
         */

            wCDRecordLength = 0 ;
            lLength = 0 ;

            lCombinedLength = wItemLength + wCDRecordLength ;

            while (lCombinedLength < CD_HIGH_WATER_MARK)
            {
               pbSig = &pCDBuffer[wItemLength];
               wSig =  *(WORD*)pbSig;
               pbSig++;

               /* find length of CD record.        */

               if (*pbSig == 0)    				/* record length is a DWORD  */
               {
                  pbSig++;
                  wCDRecordLength = (WORD)*(DWORD*)pbSig;				
			      }

               else if (*pbSig == 0xFF)        	/* record length is a WORD  */
	   		   {
                  pbSig++;
                  wCDRecordLength = *(WORD*)pbSig;				
   			   }

               else	                            /* record length is the BYTE */
                  wCDRecordLength = (WORD) *pbSig;				
				
               if (wCDRecordLength % 2)
                  wCDRecordLength++;

               lLength = lLength + (long)wCDRecordLength;
               ltmpItemLength = (long)wItemLength + (long)wCDRecordLength;
               if (ltmpItemLength < CD_BUFFER_LENGTH)
                  wItemLength += wCDRecordLength;
               lCombinedLength = (long)ltmpItemLength + (long)wCDRecordLength;
            }
        }
 
        /* Copy the imported item to the note if so    */

        if (wItemLength > 0)
        {
            if (sError = NSFItemAppend(hNote,
                                   (WORD) 0, 
                                   pszItemName, 
                                   (WORD) strlen(pszItemName),
                                   TYPE_COMPOSITE, 
                                   pCDBuffer, 
                                   (DWORD)wItemLength))
            {
                /* Leave if error returned...           */

                free (pCDBuffer);
                close (CDFileFD);
                unlink (pszCDFile);
                return (ERR(sError));
            }
        }

        longpos += lLength ;
        wItemLength = 0;
    }

    /* close up and leave        */

    free (pCDBuffer);

    close (CDFileFD);

    unlink (pszCDFile);
    
    return (NOERROR);
}
