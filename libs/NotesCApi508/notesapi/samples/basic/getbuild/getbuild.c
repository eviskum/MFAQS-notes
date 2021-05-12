/************************************************************************
 
   PROGRAM:    getbuild

   FILE:       getbuild.c

   PURPOSE:    Get the Domino and Notes major build number and print it 
               to the screen.

   SYNTAX:     getbuild
     
   COMMENTS:
       This program gets the Domino and Notes major build number using the 
	   Lotus C API for Domino and Notes function NSFDbGetBuildVersion(). 
	   This opens the specified database, calls NSFDbGetBuildVersion, 
	   and prints the information on the screen. 

**************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfdata.h>

#include <lapiplat.h>

void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                         char *db_filename); 
                         
#define  STRING_LENGTH  256

/* Lotus C API for Domino and Notes subroutine */

LAPI_MAIN
{
    
    char		*db_filename;				/* pathname of source database */
	DBHANDLE	db_handle;                  /* database handle */
    WORD        wbuild;
    STATUS		error = NOERROR;            /* error code from C API for Domino and Notes calls */
    char		database_name[STRING_LENGTH];

	db_filename = database_name;
	ProcessArgs(argc, argv, db_filename);

  LAPI_INIT(error);
  if (error)
    LAPI_INIT_ERROR;
    
    /* Open the database. */
    
    error = NSFDbOpen (db_filename, &db_handle);
    if (NOERROR != error)
    {
		printf("Error: unable to open database '%s'.\n", db_filename);
		LAPI_RETURN (ERR(error));
    }
    
    
    /* Get the major build number. */
    
    error = NSFDbGetBuildVersion (db_handle, &wbuild);
    if (NOERROR != error)
    {
		NSFDbClose (db_handle);
		LAPI_RETURN (ERR(error));
    }
    
    printf ("\nThe major build number is: %d\n", wbuild);
    
    /* Close the database. */
    
    error = NSFDbClose (db_handle);
    if (NOERROR != error)
		LAPI_RETURN (ERR(error));
    
    /* End of subroutine. */
    
    LAPI_RETURN (NOERROR);
}

/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    db_filename get data from the command line or from what 
                the user types at a prompt 

 *************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], char *db_filename)
{ 
#ifndef MAC
    if (argc != 2)  
    {
#endif

      printf("Enter name of database: ");      
      fflush(stdout);
      gets(db_filename);
      
#ifndef MAC
    }    
    else
    {
         strcpy(db_filename, argv[1]);    
    } /* end if */
#endif
} /* ProcessArgs */

