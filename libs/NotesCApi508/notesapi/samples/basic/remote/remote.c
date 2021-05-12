/*************************************************************************

    PROGRAM:   remote

    FILE:      remote.c 

    PURPOSE:   Shows how to access a Domino database that is on a remote
               Domino server.

    SYNTAX:    remote

    COMMENTS:
       This program uses the API function OSPathNetConstruct() to build 
       the full network path to the database given the server name and the
       database file name. It uses this full network path name to open the
       database. Then it gets the title of the database and prints it to 
       the screen.

*************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <osfile.h>
#include <nsfdb.h>
#include <nsfdata.h>
#include <names.h>

#include <lapiplat.h>


void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                               char *server_name, char *db_name); 

/* main or NotesMain Lotus C API for Domino and Notes subroutine */

LAPI_MAIN
{
    char        *server_name;           /* name of remote server */
    char        szServer[80];           /* server names are < 80 chars */
    char        *db_name;               /* name of database file */
    char        szDBName[MAXPATH];
    char        full_netpath[MAXPATH];  /* complete db pathname */
    DBHANDLE    db_handle;              /* database handle */
    char        buffer[NSF_INFO_SIZE];  /* database info buffer */
    char        title[NSF_INFO_SIZE];   /* database title */
    STATUS      error = NOERROR;        /* error from API calls */

    server_name = szServer;
    db_name = szDBName;
    ProcessArgs(argc, argv, server_name, db_name); 

    LAPI_INIT( error )
    if (error)
      LAPI_INIT_ERROR;
        
    if ( (int)(strlen(server_name) + strlen(db_name)) >= MAXPATH )
    {
        printf ("Error:  Server Name or Database Filename too long\n");
        LAPI_RETURN(0);
    }

    /* Use the server and database names to construct a full network path
       name. */       
    
    if (error = OSPathNetConstruct(NULL, server_name, db_name,
                   full_netpath))
        LAPI_RETURN (ERR(error));
    
    /* Open the database. */
    
    if (error = NSFDbOpen (full_netpath, &db_handle))
        LAPI_RETURN (ERR(error));
    
    /* Get the database title. */
    
    if (error = NSFDbInfoGet (db_handle, buffer))
    {
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }
    
    NSFDbInfoParse (buffer, INFOPARSE_TITLE, title, NSF_INFO_SIZE - 1);
    
    /* Print the title. */
    printf ("\n");    
    printf ("The title of this database is: %s\n", title);
    
    /* Close the database. */
    
    if (error = NSFDbClose (db_handle))
        LAPI_RETURN (ERR(error));
    
    /* End of subroutine. */
    printf("\nProgram completed successfully.\n");
    LAPI_RETURN (NOERROR);
}

/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    server_name - server name obtained from command line or
                              from prompt.
                db_name -     database name obtained from command line or
                              from prompt.

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *server_name, char *db_name)
{ 
#ifndef MAC
    if (argc != 3)  
    {
#endif

        printf("Enter server name: ");      
        fflush (stdout);
        gets(server_name);
        printf("\n");
        printf ("Enter database filename:  ");
        fflush (stdout);
        gets(db_name);

#ifndef MAC
    }    
    else
    {
        strcpy(server_name, argv[1]);    
        strcpy(db_name, argv[2]);    
    } /* end if */
#endif
} /* ProcessArgs */


