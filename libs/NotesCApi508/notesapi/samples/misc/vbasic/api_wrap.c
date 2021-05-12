
/* This file contains wrapper functions for Lotus C API for 
Domino and Notes calls. The wrapper functions are linked into a 
Windows 32 Bit DLL that can be called from Visual Basic 4.0 32 Bit. 
Domino and Notes 4.X 32 Bit must be installed configured and in you 
path to run this sample.

Note about error handling:
Every function defined here returns a simple code of either "success" 
or "failure". The module also remembers the error code returned by 
the last call to the Lotus C API for Domino and Notes, and provides 
a function for getting the text of an API error. This allows the 
calling program to find out why an API call failed.
*/



/****** Operating system and C include files ******/


/****** Lotus C API for Domino and Notes include files ******/

#include <global.h>
#include <nsfdb.h>
#include <osmisc.h>

/****** Global constants ******/

/* These definitions are used to communicate with Visual Basic. Calls
to the wrapper functions return one of these values. */

#define API_SUCCESS 0
#define API_FAILURE 1

/* Miscellaneous constants */

#define MAX_API_ERR 200


/****** Global data ******/

    static STATUS saved_api_error;  /* error saved from last API call */
    static DBHANDLE db_handle;   /* the database that is currently open */



/* Wrapper function to initialize Domino and Notes. */

int LNPUBLIC Start_Notes (void)

{
/* Local data */

    STATUS error; /* Lotus C API for Domino and Notes error */

/* Executable code */

#if 0
    error = NotesInit();                             /* V3 */
#endif

    int      argc = NULL;
    char **  argv = NULL;
    error = NotesInitExtended(argc , argv);          /* V4 */

    if (error != NOERROR)
    {
        saved_api_error = NOERROR; 
        /* if NotesInit failed, error code is meaningless */
        return API_FAILURE;
    }
    else
    {
        saved_api_error = NOERROR;
        return API_SUCCESS;
    }
}



/* Wrapper function to exit from Domino and Notes. */

int LNPUBLIC Stop_Notes (void)

{
/* Executable code */

    NotesTerm();

    saved_api_error = NOERROR;
    return API_SUCCESS;
}




/* Wrapper function to open a Domino database. */

int LNPUBLIC Open_Notes_Database (char far *filename)

{
/* Local data */

    STATUS error; /* Lotus C API for Domino and Notes error */

/* Executable code */

    error = NSFDbOpen (filename, &db_handle);

    if (error != NOERROR)
    {
        saved_api_error = error;
        return API_FAILURE;
    }
    else
    {
        saved_api_error = NOERROR;
        return API_SUCCESS;
    }
}



/* Wrapper function to close a Domino database. */

int LNPUBLIC Close_Notes_Database (void)

{
/* Local data */

    STATUS error; /* Lotus C API for Domino and Notes error */

/* Executable code */

    error = NSFDbClose (db_handle);

    if (error != NOERROR)
    {
        saved_api_error = error;
        return API_FAILURE;
    }
    else
    {
        saved_api_error = NOERROR;
        return API_SUCCESS;
    }
}




/* Wrapper function to get the title of a Domino database. */

int LNPUBLIC Get_Notes_Db_Title (char far *title)

{
/* Local data */

    char   buffer[NSF_INFO_SIZE];    /* database info buffer */
    STATUS error; /* Lotus C API for Domino and Notes error */

/* Executable code */

    error = NSFDbInfoGet (db_handle, buffer);

    if (error != NOERROR)
    {
        saved_api_error = error;
        return API_FAILURE;
    }
    else
    {
        NSFDbInfoParse (buffer, INFOPARSE_TITLE, title, NSF_INFO_SIZE - 1);
        saved_api_error = NOERROR;
        return API_SUCCESS;
    }
}



/* Function to return the text associated with the last return code
from an API call. */

int LNPUBLIC Get_Notes_Error_Message (char far *error_text)

{

/* Local data */

    int   text_len;

/* Executable code. */

    text_len = OSLoadString (
         NULLHANDLE, 
         ERR(saved_api_error),
         error_text,
         MAX_API_ERR);

    saved_api_error = NOERROR;
    return API_SUCCESS;
}
