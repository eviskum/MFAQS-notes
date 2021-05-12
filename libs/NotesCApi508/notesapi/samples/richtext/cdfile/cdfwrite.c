/**************************************************************************

    PROGRAM:    cdfwrite
    
    FILE:       cdfwrite.c 

    SYNTAX:     cdfwrite 

    PURPOSE:    Creates a file containing Domino and Notes rich text data.

    DESCRIPTION:
        This program creates a CD file, cd_recs.inp, which contains 
        the specified text.  A CD file is a file containg Domino and Notes 
        rich text. You may use this CD file to test the API function 
        CompoundTextAssimilateFile(), which takes a CD file as input.

        A CD file starts with the datatype word TYPE_COMPOSITE. Following
        the datatype word is a series of Compound Document (CD) records.
        All data in the file is in Domino and Notes Canonical Format. 

****************************************************************************/

/* OS and C include files */

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
#include <osmem.h>
#include <nif.h>

#include <lapiplat.h>

/* local include files */
#include "cdfile.h"

void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                             char *szText); 
 

/**************************************************************************

    FUNCTION:   main or NotesMain Lotus C API for Domino and Notes subroutine

***************************************************************************/

LAPI_MAIN
{
    char           *szCDFileName;
    char            szText[128];
    STATUS          nErr = NOERROR;  /* return code from API calls */
    HANDLE          hCompound;       /* handle to CompoundText context */
    COMPOUNDSTYLE   Style;
    DWORD           dwStyleID;
    HANDLE          hCDBuffer;       /* handle to buffer of CD records */
    DWORD           dwBufferSize;
    SIZE_T          sBufferSize;
    char            szTempFileName[MAXPATH+1];  /* created by Domino and Notes */
    char           *pData;          /* pointer to buffer of CD records */
    FILE           *pCDFile;        /* output file stream */
    SIZE_T          sRetVal;        /* return value from fwrite() */

    szCDFileName = CD_FILENAME;
    LAPI_INIT(nErr);
    if (nErr)
        LAPI_INIT_ERROR;

#ifdef MAC
    SetPort( FrontWindow());
#endif
 
    /* process command line arguments or prompt user for arguments */
    ProcessArgs (argc, argv, szText);
    
    /* Create a "stand-alone" Compound Text context */

    nErr = CompoundTextCreate (
             NULLHANDLE,        /* no note handle */
             NULL,              /* no item name */
             &hCompound);       /* returned handle to CompoundText context */

    if (nErr != NOERROR)
    {
        printf( "Error: unable to create CompoundText context.\n" );
        LAPI_RETURN (ERR(nErr));
    }

    /* Add text from szString to the CompoundText context */

    CompoundTextInitStyle (&Style); /* initializes Style to the defaults */

    nErr = CompoundTextDefineStyle (
                hCompound,      /* handle to CompoundText context */
                "",             /* style name - none */
                &Style,
                &dwStyleID);    /* style id */
 
   if (nErr != NOERROR)
   {
       printf( "Error: unable to define CompoundText style no. 1.\n" );
       LAPI_RETURN (nErr);
   }

   nErr = CompoundTextAddTextExt (
             hCompound,               /* handle to CompoundText context */
             dwStyleID,               /* style ID */
             DEFAULT_FONT_ID,         /* font ID */
             szText,                  /* text to add */
             (DWORD) strlen (szText), /* length of text */
             "\n",                    /* newline delimiter */
             COMP_PRESERVE_LINES,     /* preserve line breaks */
             NULLHANDLE);             /* handle of CLS translation table */

    if (nErr != NOERROR)
    {
        printf( "Error: unable to Add text to CompoundText context .\n" );
        CompoundTextDiscard (hCompound);
        LAPI_RETURN (ERR(nErr));
    }

   /* Close the CompoundText context in stand-alone mode. This returns the
      sequence of CD records in a buffer, or, if more than 64K, in a file.
    */
   
    nErr = CompoundTextClose (
            hCompound,          /* handle to CompoundText context */
            &hCDBuffer,         /* if result is a buffer, handle goes here */
            &dwBufferSize,
            szTempFileName,     /* if this creates a file, name goes here */
            MAXPATH );
             
    if (nErr != NOERROR)
    {
        printf("Error: unable to close compound text context.\n");
        CompoundTextDiscard (hCompound);
        LAPI_RETURN (ERR(nErr));
    }

    if (hCDBuffer == NULLHANDLE)
    {
        /* Compound Text returned in a file, not in a buffer */

        if (strlen( szTempFileName ) == 0)
        {
            printf( "Error: no buffer and no file created.\n");
            LAPI_RETURN (PKG_ADDIN);
        }
            
        if (rename(szTempFileName, szCDFileName) == 0)
        {
            printf("Error: unable to rename temp file '%s' to '%s'.\n", 
                    szTempFileName, szCDFileName );
            LAPI_RETURN (PKG_ADDIN);
        }
   
        LAPI_RETURN( NOERROR );
    }

    /* else - Compound text returned in a buffer  */

    pData = OSLock( char, hCDBuffer );

    if (pData == NULL)
    {
        printf( "Error: unable to lock compount text buffer.\n" );
        LAPI_RETURN( NOERROR );
    }

    pCDFile = fopen( szCDFileName, FOPEN_MODE );

    if (pCDFile == (FILE*)NULL)
    {
        printf( "Error: unable to open output file '%s'.\n", szCDFileName );
        LAPI_RETURN( NOERROR );
    }

    sBufferSize = (SIZE_T)dwBufferSize ;

    sRetVal = fwrite( pData, sizeof(BYTE), sBufferSize, pCDFile );

    if (sRetVal != sBufferSize)
    {
        printf( "Error: did not write %d bytes to output file.\n", 
                sBufferSize);
    }
    else
    {
        printf( "Wrote %d bytes to file %s.\n", sRetVal, szCDFileName );
    }

    if (fclose( pCDFile ))
    {
        printf("Error: unable to close output file '%s'.\n", szCDFileName);
    }
    
    OSUnlockObject( hCDBuffer );

    OSMemFree( hCDBuffer );

    printf("\nProgram completed successfully.\n");
    LAPI_RETURN (NOERROR);
}

/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    text - gets rich text field text

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                             char *text)
{ 
    int i;

    text[0] = '\0';

#ifndef MAC
    if (argc == 1)
    {       
#endif
      
      printf("Enter text to be included in rich text field:\n");
      gets(text);

#ifndef MAC
   }  
   else
   {
      for (i=1; i<argc; i++)
      {
        strcat(text, argv[i]);
        strcat(text, " ");
      }
   } /* end if */
#endif
} /* ProcessArgs */

