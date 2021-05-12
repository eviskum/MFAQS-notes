/****************************************************************************

    PROGRAM:    cdfread

    FILE:       cdfread.c

    SYNTAX:     cdfread

    PURPOSE:    Demonstrate function CompoundTextAssimilateFile.

    DESCRIPTION:
        This creates a new data note in the database, richtext.nsf 
        and fills in the rich text field of the note with the 
        compound text from a CD file, cd_recs.inp.  
        
        A CD file is a file containing Domino and Notes rich text data. 
		This data must be in Domino and Notes Canonical format. Use the 
		companion program "cdfwrite" to create this CD file.
        
        The database used in this program has a form named 
        "RichTextForm".  This form contains a time/date field named,
        TIME_DATE, and a rich text field named, RICH_TEXT.

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

/************************************************************************

    FUNCTION:   main or NotesMain Lotus C API for Domino and Notes subroutine

*************************************************************************/

LAPI_MAIN
{
    STATUS      nErr = NOERROR; /* return code from API calls */
    char       *szPathName;     /* pathname of database */
    char       *szCDFileName;   /* name of CD file to read in */
    DBHANDLE    hDB;            /* database handle */
    NOTEHANDLE  hNote;          /* note handle */
    TIMEDATE    timedate;       /* a time/date field */
    HANDLE      hCompound;      /* handle to CompoundText context */


    szPathName = "richtext.nsf";
    szCDFileName = CD_FILENAME;     /* "cd_recs.inp" */

    LAPI_INIT(nErr);
    if (nErr)
        LAPI_INIT_ERROR;

    /* Open the database. */

    if ( (nErr = NSFDbOpen (szPathName, &hDB)) != NOERROR )
    {
        printf( "Error: unable to open database '%s'.\n", szPathName );
        LAPI_RETURN (ERR(nErr));
    }
   
   /* Create a new data note. */

    if ( (nErr = NSFNoteCreate (hDB, &hNote)) != NOERROR )
    {
        printf( "Error: unable to create new document in database.\n" );
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Write a field named FORM to the note -- this field specifies the
      default form to use when the note is displayed. */

    nErr = NSFItemSetText( hNote, FIELD_FORM, "RichTextForm", MAXWORD );

    if (nErr != NOERROR)
    {
        printf( "Error: unable to set text in item '%s'.\n", FIELD_FORM );
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Get the current time/date and write it to a field named TIME_DATE. */

    OSCurrentTIMEDATE(&timedate);

    if ( (nErr = NSFItemSetTime (hNote, "TIME_DATE", &timedate)) != NOERROR )
    {
        printf( "Error: unable to set time in item 'TIME_DATE'.\n" );
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Create the CompoundText context. We get an Item Context (as opposed
      to a stand-alone context) by specifying the handle to an open note 
      and the name of a rich text field.
    */

    nErr = CompoundTextCreate (
                hNote,        /* handle of note */
                "RICH_TEXT",  /* item name */
                &hCompound);  /* returned handle to CompoundText context */

    if (nErr != NOERROR)
    {
        printf( "Error: unable to create CompoundText context for 'RICH_TEXT'.\n" );
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

    /* Add the data from the CD file to the CompoundText context.*/

    nErr = CompoundTextAssimilateFile (
                hCompound,          /* handle to CompoundText context */
                szCDFileName,       /* file of CD Records */
                0L);                /* reserved */

    if (nErr != NOERROR)
    {
        printf("Error: unable to assimilate CD record from file '%s'.\n",
                    szCDFileName);
        CompoundTextDiscard (hCompound);
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Add the CompoundText context to the note. Since this is an Item 
      Context, (associated with the newly created note), only specify 
      hCompound parameter. 
    */

    nErr = CompoundTextClose (
                hCompound,            /* handle to CompoundText context */
                NULL,                    
                NULL,
                NULL,
                0);

    if (nErr != NOERROR)
    {
        printf("Error: unable to close compound text context.\n");
        CompoundTextDiscard (hCompound);
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

   /* Add the new note to the database. */

    if ( (nErr = NSFNoteUpdate (hNote, 0)) != NOERROR )
    {
        printf("Error: unable to update new note to the database.\n");
        NSFNoteClose (hNote);
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }
   /* Close the new note. */

    if ( (nErr = NSFNoteClose (hNote)) != NOERROR )
    {
        NSFDbClose (hDB);
        LAPI_RETURN (ERR(nErr));
    }

    printf("New note successfully created.\n");

   /* Close the database */

    if ( (nErr = NSFDbClose (hDB)) != NOERROR )
        LAPI_RETURN (ERR(nErr));

   /* End of subroutine. */
    printf("\nProgram completed successfully\n");
    LAPI_RETURN (NOERROR);
}

