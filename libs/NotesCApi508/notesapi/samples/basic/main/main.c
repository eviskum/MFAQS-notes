/*************************************************************************

   PROGRAM:    main

   FILE:       main.c 

   PURPOSE:    Shows the basic structure of a main() routine that calls
               Lotus C API for Domino and Notes functions. The program 
			   gets the title of a Domino database and prints it to the screen.

   SYNTAX:     main  <database filename>

*************************************************************************/

/* OS and C include files */

#include <stdlib.h>
#include <stdio.h>


/* Lotus C API for Domino and Notes include files */

#include "global.h"
#include "nsfdb.h"
#include "nsfdata.h"
#include "osmisc.h"

#if defined(OS400)
#include "lapiplat.h"
#endif

#if defined(OS390) && (__STRING_CODE_SET__==ISO8859-1 /* ascii compile */)
#include <_Ascii_a.h>   /* NOTE: must be the LAST file included */
#endif /* OS390, ascii compile */

/* define exit codes if they are not defined elsewhere */

#ifndef EXIT_SUCCESS
   #define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
   #define EXIT_FAILURE 1
#endif



/* Local function prototypes */

void print_api_error (STATUS);


/* Program declaration */
#if defined(HPUX)
int main(int argc, char *argv[])
#else
VOID main (int argc, char *argv[])
#endif
{
    /* Local data declarations */
    
    char       *path_name;             /* pathname of database */
    DBHANDLE   db_handle;              /* database handle */
    char       buffer[NSF_INFO_SIZE];  /* database info buffer */
    char       title[NSF_INFO_SIZE];   /* database title */
    STATUS  error;                     /* error code from API calls */
#if defined(OS390) || defined (OS400)
    char LMBCSArg[MAXPATH];         /* translation buffer */
#endif /* OS390 || OS400 */
    
    /* Get the pathname of the database from the command line. */

    if (argc != 2)
    {
#if defined(OS390) && (__STRING_CODE_SET__==ISO8859-1 /* ascii compile */)
        OSNativeToLMBCS(argv[0], MAXWORD, LMBCSArg, MAXPATH); 
        printf( "\nUsage:  %s  <database filename>\n", LMBCSArg);
#elif defined(OS400)
        OSTranslate(OS_TRANSLATE_NATIVE_TO_LMBCS, argv[0], MAXWORD, LMBCSArg, MAXPATH);
        printf( "\nUsage:  %s  <database filename>\n", LMBCSArg);
#else
        printf( "\nUsage:  %s  <database filename>\n", argv[0] );
#endif 
       exit (EXIT_SUCCESS);
    }
#if defined(OS390)
    OSNativeToLMBCS(argv[1], MAXWORD, LMBCSArg, MAXPATH); 
    path_name = LMBCSArg;
#elif defined(OS400)
    OSTranslate(OS_TRANSLATE_NATIVE_TO_LMBCS, argv[1], MAXWORD, LMBCSArg, MAXPATH);
    path_name = LMBCSArg;
#else
    path_name = argv[1];
#endif 

    error = NotesInitExtended (argc, argv);                

    if (error)
    {
        fprintf (stderr, "\nError initializing Notes.\n");
        exit (EXIT_FAILURE);
    }
    
    /* Open the database. */
    
    if (error = NSFDbOpen (path_name, &db_handle))
    {
        print_api_error (error);
        NotesTerm();
        exit (EXIT_FAILURE);
    }
    
    /* Get the database title. */
    
    if (error = NSFDbInfoGet (db_handle, buffer))
    {
        print_api_error (error);
        NSFDbClose (db_handle);
        NotesTerm();
        exit (EXIT_FAILURE);
    }
    
    NSFDbInfoParse (buffer, INFOPARSE_TITLE, title, NSF_INFO_SIZE - 1);
    
    /* Print the title. */
    
#if defined(OS390) && (__STRING_CODE_SET__!=ISO8859-1 /* ebcdic compile */)
    OSLMBCSToNative(title, MAXWORD, LMBCSArg, sizeof(LMBCSArg));
    printf ("\nThe title of this database is:\n\n%s\n", LMBCSArg);
#else
    printf ("\nThe title of this database is:\n\n%s\n", title);
#endif /* OS390, ebcdic compile */
    
    /* Close the database. */
    
    if (error = NSFDbClose (db_handle))
    {
        print_api_error (error);
        NotesTerm();
        exit (EXIT_FAILURE);
    }
    
    /* Terminate Domino and Notes. */
    
    NotesTerm();
    
    /* End of main program. */
    
    exit (EXIT_SUCCESS);
}


/* This function prints the Lotus C API for Domino and Notes error message 
   associated with an error code. */

void print_api_error (STATUS api_error)
    
{
    STATUS  string_id = ERR(api_error);
    char    error_text[200];  
    WORD    text_len;
    
    /* Get the message for this Lotus C API for Domino and Notes error code 
	   from the resource string table. */
    
    text_len = OSLoadString (NULLHANDLE, 
                             string_id,
                             error_text, 
                             sizeof(error_text));
    
    /* Print it. */

#if defined(OS390) && (__STRING_CODE_SET__!=ISO8859-1 /* ebcdic compile */)
    OSLMBCSToNative(error_text, MAXWORD, error_text, sizeof(error_text));
#endif /* OS390, ebcdic compile */
    
    fprintf (stderr, "\n%s\n", error_text);
    
}

