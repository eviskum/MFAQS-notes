/****************************************************************************
    PROGRAM:    intro

    FILE:       intro.c

    SYNTAX:     intro

    PURPOSE:    Illustrates the basic structure of a Lotus C API for 
	            Domino and Notes subroutine.

    DESCRIPTION:
        This program illustrates the basic structure of a Lotus C API for 
		Domino and Notes program. This opens an existing Domino database, reads the 
        database title, and prints the information on the screen. 

****************************************************************************/

/* OS and C include files */

#include <stdio.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfdata.h>

#include <lapiplat.h>

#if defined(OS390) && (__STRING_CODE_SET__==ISO8859-1 /* ascii compile */)
#include <_Ascii_a.h>   /* NOTE: must be the LAST file included */
#endif /* OS390, ascii compile */


/************************************************************************

    FUNCTION:   main / NotesMain

    PURPOSE:    Main Lotus C API for Domino and Notes subroutine

*************************************************************************/

LAPI_MAIN
{
  char        path_name[]="intro.nsf";  /* pathname of database */
  DBHANDLE    db_handle;                /* database handle */
  char        buffer[NSF_INFO_SIZE];    /* database info buffer */
  char        title[NSF_INFO_SIZE];     /* database title */
  STATUS      error = NOERROR;          /* error code from API calls */
#if defined(OS390) && (__STRING_CODE_SET__!=ISO8859-1 /* ebcdic compile */)
  char        temp[NSF_INFO_SIZE];      /* temp buffer for ebcdic translate */
#endif /* OS390, ebcdic compile */
  
  LAPI_INIT(error);
  if (error)
    LAPI_INIT_ERROR;
 
  /* Open the database. */

#if defined(OS390) && (__STRING_CODE_SET__!=ISO8859-1 /* ebcdic compile */)
  OSNativeToLMBCS(path_name, MAXWORD, temp, NSF_INFO_SIZE);
  if (error = NSFDbOpen (temp, &db_handle))
    LAPI_RETURN (ERR(error));
#else
  if (error = NSFDbOpen (path_name, &db_handle))
    LAPI_RETURN (ERR(error));
#endif /* OS390, ebcdic compile */

  /* Get the database title. */
  
  if (error = NSFDbInfoGet (db_handle, buffer))
  {
    NSFDbClose (db_handle);
    LAPI_RETURN (ERR(error));
  }
  
  NSFDbInfoParse (buffer, INFOPARSE_TITLE, title, NSF_INFO_SIZE - 1);

  /* Print out the Lotus C API for Domino and Notes Release Number */
  printf ("\nLotus Notes C API Release %s Sample Application", 
          NOTESAPI_VERSION);

  /* Print the information. */
  
#if defined(OS390) && (__STRING_CODE_SET__!=ISO8859-1 /* ebcdic compile */)
  OSLMBCSToNative(title, MAXWORD, temp, NSF_INFO_SIZE);
  printf ("\n\n\nThe title for the database %s is...\n\n%s\n", path_name, temp);
#else
  printf ("\n\n\nThe title for the database %s is...\n\n%s\n", path_name, title);
#endif /* OS390, ebcdic compile */
  
  /* Close the database. */
  
  if (error = NSFDbClose (db_handle))
    LAPI_RETURN (ERR(error));
  
  /* End of subroutine. */
  printf("\nProgram completed successfully\n");
  LAPI_RETURN (NOERROR);
}


