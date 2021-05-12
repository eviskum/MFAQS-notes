/****************************************************************************

    PROGRAM:    addin    

    FILE:       addin.c

    PURPOSE:    sample Lotus Domino Server add-in task

    SYNTAX:     (at the Lotus Domino Server console) > load addin

    DESCRIPTION:
        This is a sample Lotus Domino Server add-in task. First, it sets the 
        default status line to be displayed by the Lotus Domino Server "show 
        tasks" command. Then it enters a loop where it performs certain 
        operations periodically. For each operation, it logs a message in
        the Lotus Domino Server log file.

        This add-in task is designed for portability to platforms such as 
        Unix. This sample differs from OS/2 and Windows 
        add-in samples in that it does not use a string table. A string 
        table is a resource that requires a resource compiler, normally 
        only available under OS/2 and Windows.

****************************************************************************/

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <global.h>
#include <addin.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <ostime.h>
#include <osmisc.h>

/* Local definitions */

#define DB_NAME "addintst"   /* database we will write to */


/* Function prototypes */

STATUS OurJob (char *);

/************************************************************************

    FUNCTION:   AddInMain

    PURPOSE:    Main entry point for all Lotus Domino Server add-in tasks 

    ALGORITHM:
         Get the default status line.  Delete it. Create a new status line
         with the task name "Sample Addin".  Set the default status line
         to this new status line. Set the status string to "Initializing".
         
         Enters a loop until the Lotus Domino Server terminates or an 
         error occurs.

         Within this loop:

            Once a day, set status to "Doing daily job" and write a
            message to the log file. 
            
            Once every 2 minutes, sets status to "Doing two-minute job" 
            and write a message to the log.

            Once every 20 seconds, set status to "Doing 20-second job". 
            Call OurJob to opens a test database, creates a new note, 
            write some data, then update and closes the database. Then 
            write a message to the log.



*************************************************************************/
 
STATUS LNPUBLIC  AddInMain (HMODULE hModule, int argc, char *argv[])
{
    
    /* Local data. */

    STATUS     error;           /* return code from API calls */
    HANDLE     hOldStatusLine;  /* handle to initial default status line*/
    HANDLE     hStatusLineDesc; /* handle to new default status line */
    HMODULE    hMod;            /* add-in task's module handle */

   /* 
      Initialization.

      Set the task name and status string of this add-in task. The task
      name and status string appear on the status line at the Lotus Domino
      Server in response to the 'show tasks' command. By default, the
      name in the status line is the name of the program (the value of 
      argv[0]). First get the handle to this default status line descriptor 
      and delete it. Then create a new status line and set the status to
      'Initializing'.
    */
 
    AddInQueryDefaults (&hMod, &hOldStatusLine);

    AddInDeleteStatusLine (hOldStatusLine);
   
    hStatusLineDesc = AddInCreateStatusLine("Sample Addin");

    AddInSetDefaults (hMod, hStatusLineDesc);

    AddInSetStatusText("Initializing");
    
    /* Initialization is complete */

    AddInLogMessageText("Add-in Test: Initialization complete.", NOERROR);
    AddInSetStatusText("Idle");     /* 'Idle' replaces 'Initializing' */

   /* Begin the main loop.  We give up control to the server at the start of 
      each iteration, and get control back when the server says it is OK to 
      proceed.  When AddInIdle returns TRUE, it is time to shut down this 
      task.
    */
 
    while (!AddInIdle())
    {
        
    /* For non-preemptive operating systems, give up control to 
       other tasks. OSPreemptOccasionally will do nothing in 
       preemptive operating systems.
     */

        OSPreemptOccasionally();

        /* Do the operations that we do each day. */

        if (AddInDayHasElapsed())
        {
            AddInSetStatusText("Doing daily job");
            AddInLogMessageText("Addin Test: Daily job complete.", 
                                NOERROR);
            AddInSetStatusText("Idle");
        }
 
        /* Do the operations that we do every other minute. */

        else if (AddInMinutesHaveElapsed(2))
        {
            AddInSetStatusText("Doing two-minute job");
            AddInLogMessageText("Addin Test: Two-minute job complete.", 
                                NOERROR);
            AddInSetStatusText("Idle");
        }
   
        /* Do the operations that we do every 20 seconds. */
   
        else if (AddInSecondsHaveElapsed(20))
        {        
            AddInSetStatusText("Doing 20-second job");
            if (error = OurJob(DB_NAME))  /* our local job */
                return (ERR(error));
            AddInLogMessageText("Add-in Test: 20-second job complete.", 
                                NOERROR);
            AddInSetStatusText("Idle");
        }
   
    }   /* End of main task loop. */
   
   /* We get here when the server notifies us that it is time to terminate.  
      This is usually when the user has entered "quit" to the server console. 
      Clean up anything we have been doing.  
    */
    AddInSetStatusText("Terminating");

    AddInLogMessageText("Add-in Test: Termination complete.", NOERROR);
    
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

    DBHANDLE   db_handle;       /* database handle */
    NOTEHANDLE note_handle;     /* note handle */
    TIMEDATE   timedate;        /* contents of a time/date field */
    STATUS     error;           /* return code from API calls */

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

    if (error = NSFItemSetText (note_handle, "Form", "AddInForm", MAXWORD))
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
