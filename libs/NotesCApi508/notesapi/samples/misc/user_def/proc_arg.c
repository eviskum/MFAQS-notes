/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsfsearc.h>
#include <osmem.h>
#include <nsferr.h>

#include <lapiplat.h>

/* Local include files */

#include "user_def.h"

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
