/****************************************************************************

    PROGRAM:    produce

    FILE:       produce.c

    PURPOSE:    Server add-in task that generates user-defined events.

    DESCRIPTION:
        This is an example of an event producer.  Every minute, this program
        adds an event of type EVT_MISC and severity SEV_NORMAL to the 
        event queue called "TEST_EVENT_QUEUE".

****************************************************************************/

/*
 *  OS and C include files
 */

#include <stdio.h>

/*
 *  Lotus C API for Domino and Notes include files
 */

#include <global.h>
#include <nsfdata.h>
#include <addin.h>
#include <event.h>
#include <osmisc.h>
#include <ostime.h>
#include <misc.h>
#include <osmem.h>

/*
 *  Local include files 
 */

#include "produce.h"

/************************************************************************

    FUNCTION:   AddInMain

    PURPOSE:    Standard entry for all Lotus Domino Server add-in tasks 

*************************************************************************/
 
STATUS LNPUBLIC AddInMain (HMODULE hModule, int argc, char *argv[])
{

char szQueueName[] = "TEST_EVENT_QUEUE";
char szDBName[]    = "EVENT.NSF";

TIMEDATE EventTimeDate;
BYTE     EventBuffer[EVENT_BUF_SIZE];
WORD     wLen;
STATUS   sError;

/*
 *  Initialize this task. 
 */

    AddInSetStatus(ADDIN_MSG_FMT, "Initializing");
    AddInLogMsg(ADDIN_MSG_FMT, "Event Producer Test: Initialization complete.");
    AddInSetStatus(ADDIN_MSG_FMT, "Idle");

/* 
 *  Start of code that gets executed each minute. 
 */

    while (!AddInIdle())
    {
        if (AddInMinutesHaveElapsed(1))
        {
        /*
         *  If a minute has passed, get the current time and date.  Then
         *  generate an event of type EVT_MISC and severity SEV_NORMAL.
         *  Pass a string containing the time and date as event-specific 
         *  data.
         */
         
            OSCurrentTIMEDATE(&EventTimeDate);
            ConvertTIMEDATEToText(NULL,
                                  NULL,
                                  &EventTimeDate,
                                  EventBuffer, 
                                  sizeof(EventBuffer)-1, 
                                  &wLen);

            sError = EventQueuePut(szQueueName,
                                   NULL,
                                   EVT_MISC,
                                   SEV_NORMAL,
                                   &EventTimeDate,
                                   TYPE_TEXT,
                                   wLen,
                                   (BYTE far *) EventBuffer);
                                   
            AddInLogMsg(ADDIN_MSG_FMT, "PRODUCE Test: Produced an event!");
        }
    }

/*
 *  We get here when the server notifies us that it is time to terminate.  
 *  This is usually when the user has entered "quit" to the server console. 
 * Clean up anything we have been doing.
 */

    AddInSetStatus(ADDIN_MSG_FMT, "Terminating");
    AddInLogMsg(ADDIN_MSG_FMT, "PRODUCE Test: Termination complete.");
  
/*
 *  End of add-in task.  We must "return" here rather than "exit". 
 */

    return (NOERROR);

}
