/****************************************************************************

    PROGRAM: reqnum

    FILE:    reqnum.c

    SYNTAX:  reqnum

    PURPOSE: create a file "reqnum.dat" containing NUMBER = 1
             for use by Lotus C API for Domino and Notes sample program tracker. 

    DESCRIPTION:
   
    Lotus C API for Domino and Notes  Sample program tracker requires a data file 
	with name "reqnum.dat" to manage a unique sequential request number
    service. Under OS/2, this file resides in "c:\" by default. Under
    UNIX it resides in the user's home directory as specified by "~/".
    This program creates this file containing the number 1.

****************************************************************************/

/* C include files */
#include <stdio.h>
#include <errno.h>

/* Lotus C API for Domino and Notes include files */
#include <global.h>                     /* NUMBER */
#include <names.h>                      /* MAXUSERNAME */
#include <nsfdb.h>                      /* DBHOOKVEC */
#include <nsfdata.h>                    /* LIST */

/* OS/2 include files */
#if defined(OS2)
#include <share.h>                      /* SH_DENYRW */
#endif

/* Application-specific include files */
#include "tracker.h"                    /* REQNUM_FILENAME */

/************************************************************************

    FUNCTION:   NotesMain

    PURPOSE:    Create the "next Request Number to Use" file reqnum.dat.
                Set the number to 1.

************************************************************************/

STATUS LNPUBLIC NotesMain (int argc, char *argv[])
{
    FILE       *pReqNumFile;
    NUMBER      ReqNumber;
    size_t      count;

#if defined(OS2)
    pReqNumFile = fopen(REQNUM_FILENAME, "wb");
#else /* UNIX */
    pReqNumFile = fopen(REQNUM_FILENAME, "w");
#endif

    if (pReqNumFile == (FILE*)NULL)
    {
        printf("Error: unable to open file '%s': %d.\n",
                            REQNUM_FILENAME, errno);
        return NOERROR;
    }

    ReqNumber = 1;
    count = fwrite(&ReqNumber, sizeof(NUMBER), 1, pReqNumFile);
    fclose(pReqNumFile);

    if (count != 1)
    {
        printf("Error: error writing file '%s' : %d.\n",
                            REQNUM_FILENAME, errno);
    }

    return NOERROR;
}
