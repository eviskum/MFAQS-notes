/****************************************************************************

    PROGRAM:    add_res
                
    FILE:       add_res.c      

    SYNTAX:     load  <path to program> add_res

    PURPOSE:    Example Lotus Domino Server add-in task for Windows & OS/2

    DESCRIPTION:
        This code demonstrates a Lotus Domino Server add-in task for Windows
        and OS/2.  The task performs some operations periodically,
        sets the status of the task, and writes to the server log file.

****************************************************************************/

/* OS and C include files */


/* Lotus C API for Domino and Notes include files */

#include <global.h>
#include <addin.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <ostime.h>
#include <osmisc.h>

/* Local include files */

#include "add_res.h"


/* Local definitions */

#define DB_NAME "ADDINTST"   /* database we will write to */

/* Function prototypes */

STATUS OurJob (char *);

/************************************************************************

    FUNCTION:   AddInMain 

    PURPOSE:    Standard entry for all Lotus Domino Server add-in tasks

*************************************************************************/
 
STATUS LNPUBLIC  AddInMain (HMODULE hModule, int argc, char *argv[])
{
    STATUS       error;        /* return code from API calls */

/* Initialize this task. */

    AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Initializing");
    AddInLogMsg(ADDIN_MSG_FMT, (char far *) "Add-in Test: Initialization complete.");
    AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Idle");

/* Begin the main loop.  We give up control to the server at the start of 
each iteration, and get control back when the server says it is OK to 
proceed.  The server returns TRUE when it is time to shut down this task.
*/
 
    while (!AddInIdle())
    {

/* Give up control to other tasks. */

        OSPreemptOccasionally();

/* Do the operations that we do each day. */

        if (AddInDayHasElapsed())
        {
            AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Doing daily job");
            AddInLogMsg(ADDIN_MSG_FMT, (char far *) "Addin Test: Daily job complete.");
            AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Idle");
        }
 
/* Do the operations that we do every other minute. */

        else if (AddInMinutesHaveElapsed(2))
        {
            AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Doing two-minute job");
            AddInLogMsg(ADDIN_MSG_FMT, (char far *) "Addin Test: Two-minute job complete.");           
            AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Idle");
        }
 
/* Do the operations that we do every 20 seconds. */

        else if (AddInSecondsHaveElapsed(20))
        {
            AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Doing 20-second job");
            if (error = OurJob(DB_NAME))     /* our local job */
                return (ERR(error));
            AddInLogMsg(ADDIN_MSG_FMT, (char far *) "Add-in Test: 20-second job complete.");
            AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Idle");
        }
 
/* End of main task loop. */

    }

/* We get here when the server notifies us that it is time to terminate.  
This is usually when the user has entered "quit" to the server console. 
Clean up anything we have been doing.  */

    AddInSetStatus(ADDIN_MSG_FMT, (char far *) "Terminating");
    AddInLogMsg(ADDIN_MSG_FMT, (char far *) "Add-in Test: Termination complete.");
  
/* End of add-in task.  We must "return" here rather than "exit". */

    return (NOERROR);

}

/************************************************************************

    FUNCTION:   OurJob 

    PURPOSE:    Local function called by the main task loop.

*************************************************************************/

STATUS OurJob (char *db_name)
{

/* Local data declarations. */

    DBHANDLE    db_handle;    /* database handle */
    NOTEHANDLE  note_handle;  /* note handle */
    TIMEDATE    timedate;     /* contents of a time/date field */
    STATUS      error;        /* return code from API calls */

/* Open the database. */

    if (error = NSFDbOpen (db_name, &db_handle))
        return (ERR(error));

/* Create a new data note. */

    if (error = NSFNoteCreate (db_handle, &note_handle))
    {
        NSFDbClose (db_handle);
        return (ERR(error));
    }

/* Write the form name to the note. */

    if (error = NSFItemSetText (note_handle, "Form",
                "AddInForm", MAXWORD))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        return (ERR(error));
    }

/* Write a text field to the note. */

    if (error = NSFItemSetText (note_handle, "AddIn_Text",
                "This is a note written by the add-in task.",
                MAXWORD))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        return (ERR(error));
    }

/* Write the current time into the note. */

    OSCurrentTIMEDATE(&timedate);
    if (error = NSFItemSetTime (note_handle, "AddIn_Time", &timedate))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        return (ERR(error));
    }

/* Add the note to the database. */

    if (error = NSFNoteUpdate (note_handle, 0))
    {
        NSFNoteClose (note_handle);
        NSFDbClose (db_handle);
        return (ERR(error));
    }

/* Deallocate the new note from memory. */

    if (error = NSFNoteClose (note_handle))
    {
        NSFDbClose (db_handle);
        return (ERR(error));
    }

/* Close the database. */

    if (error = NSFDbClose (db_handle))
        return (ERR(error));

/* End of function. */

    return (NOERROR);
}
