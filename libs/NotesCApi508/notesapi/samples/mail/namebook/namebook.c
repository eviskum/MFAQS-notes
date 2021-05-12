/****************************************************************************
                
    PROGRAM:    namebook

    FILE:       namebook.c

    PURPOSE:    Demonstrate the Lotus C API for Domino and Notes function NAMEGetAddressBooks().

    SYNTAX:     namebook  <server name>  [options]

        if options = TITLES, this prints the title of each database in
        addition to file path.

****************************************************************************/

/* OS and C include files */
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */
#include <global.h>
#include <intl.h>
#include <nsf.h>
#include <acl.h>
#include <misc.h>
#include <osmem.h>
#include <osfile.h>                     /* OSPathNetParse */
#include <ostime.h>
#include <lookup.h>
#include <stdnames.h>
#include <textlist.h>
#include <editods.h>
#include <oserr.h>


/************************************************************************

    FUNCTION:   NotesMain

*************************************************************************/

STATUS LNPUBLIC NotesMain (int argc, char *argv[])
{
    PCHAR   szServer;
    PCHAR   szOptions;
    WORD    wOption;
    STATUS  error;
    WORD    wCount;
    WORD    wLength;
    WORD    wEntry;
    WORD    wEntryLen;
    HANDLE  hReturn;
    char   *pszReturn;    
    char    achPort[MAXPATH];
    char    achServer[MAXPATH];
    char    achFile[MAXPATH];

    if (argc<2 || argc>3)
    {
Syntax:
        printf ("Syntax: namebook  <server name>  [option]\n");
        printf (
        "where [option] = TITLES or nothing.\n");
        return NOERROR;
    }

    szServer = (strlen(argv[1])?argv[1]:NULL);
    wOption = 0;

    if (argc==3)
    {
        szOptions=argv[2];
        if (!strcmp(szOptions,"TITLES"))
            wOption = NAME_GET_AB_TITLES | NAME_DEFAULT_TITLES ;
        else
        {
            printf ("Error: unrecognized option '%s'\n", szOptions);
            goto Syntax;
        }
    }
        
    error = NAMEGetAddressBooks( 
                szServer,
                wOption,
               &wCount,
               &wLength,
               &hReturn);

    if (error) return(ERR(error));

    /* If there are no entries, return. */
    if (!wCount) 
    {
        printf ("No entries in NAMES.\n");
        return NOERROR;
    }

    /* Lock the return buffer. */

    pszReturn = OSLock(char, hReturn);

    /* Loop through the entries. */

    for (wEntry = 0; wEntry < wCount; wEntry++)
    {
         /* Get path length. */
        wEntryLen = strlen(pszReturn);

        /* Parse the path into components. */
        OSPathNetParse(pszReturn, achPort, achServer, achFile);

        /* process components */
        printf("Entry %d\n\tPort = %s\n\tServer = %s\n\tFile = %s\n",
                (wEntry+1), achPort, achServer, achFile);

        if (wOption & NAME_GET_AB_TITLES)
        {
            /* Advance to title. */
            pszReturn += wEntryLen+1;
            wEntryLen = strlen(pszReturn);
            printf ("\tTitle = '%s'\n", pszReturn);
        }
          
        /* Advance pointer to next entry. */
        pszReturn += wEntryLen+1;
    }

    /* Unlock and free the return buffer. */
    OSUnlock(hReturn);
    OSMemFree(hReturn);
    return NOERROR;
}

