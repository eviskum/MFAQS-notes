/************************************************************************
 
   PROGRAM:    alarm

   FILE:       alarm.c

   PURPOSE:    Demonstrate the Alarm APIs functionality.

   SYNTAX:     alarm
	
   COMMENTS:
	       This program demonstrates the Alarm APIs functionality by
	       creating and opening a message queue for Alarm messages,
	       registering the client with the Alarms Daemon and waiting
	       for an Alarm Message that has been previously set by the UI.
	       Once the message is received the alarm information is displayed
	       and the client deregisters with the Alarm Daemon.

**************************************************************************/

/* OS and C include files */

#include <stdio.h>

#if defined(HPUX)
#include <string.h>
#endif

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfdata.h>
#include <mq.h>
#include <alarm.h>
#include <misc.h>
#include <miscerr.h>
#include <ods.h>
#include <osmem.h>

#include <lapiplat.h>

#define MAX_MESSAGE  (256)
#define NOTESCLIENT  "NOTESCLIENT"

/* Message queue name */
char MsgQueueName [] = MQPREFIX_FOR_CLIENT "NOTESCLIENT";
/* Note the implicit string concatenation!! */

/* Function declarations */
STATUS ProcessAlarmMessage (char *, WORD); 
void LNPUBLIC  GetTDString( TIMEDATE *, char * );

LAPI_MAIN
{
    STATUS      error = NOERROR;                  /* error code from API calls */
    MQHANDLE    hQueue;                           /* Handle to message queue */
    char        MsgBuffer [MAX_MESSAGE + 1];      /* Buffer for messages */
    WORD        MsgLen;                           /* Size of message */
    BOOL        bNO_ALARM_MSG = TRUE;
  
    /* initialize with Domino and Notes */
    LAPI_INIT(error);
    if (error)
      LAPI_RETURN (ERR(error));

    /*
	Create and open the message queue.
    */
    error = MQOpen (MsgQueueName, MQ_OPEN_CREATE, &hQueue);
    if (NOERROR != error)
      LAPI_RETURN (ERR(error));

    /* Register the client with the Alarms Daemon */
    error = Alarm_RegisterInterest (NOTESCLIENT, 0);
    if (NOERROR != error)
      LAPI_RETURN (ERR(error));

    /* Tell the Alarms Daemon to refresh it's list of alarms */
    error = Alarm_RefreshAlarms (NOTESCLIENT);
    if (NOERROR != error)
      LAPI_RETURN (ERR(error));

    /* Main loop to process Alarm message.  We'll wait for 5 minutes for a
    message and if we don't get one, we'll time out */

    while (bNO_ALARM_MSG)
    {
      printf("Waiting for message from the Alarms Daemon...\n");
      error = MQGet (hQueue, MsgBuffer, MAX_MESSAGE,
		     MQ_WAIT_FOR_MSG, (300 * 1000), &MsgLen);

      MsgBuffer[MsgLen] = '\0';

      if (NOERROR == error)
      {
	    printf("Received Alarm Message!\n\n");
	    error = ProcessAlarmMessage (MsgBuffer, MsgLen);

	    bNO_ALARM_MSG = FALSE; 
      }
      else if (ERR_MQ_TIMEOUT == error)
      {
	    printf("Received Timeout...\n");
	    bNO_ALARM_MSG = FALSE; 
      }
    }   /* End of main task loop. */
 
    /* deregister with the Alarm Daemon */
    error = Alarm_DeregisterInterest (NOTESCLIENT, 0);
    if (NOERROR != error)
      LAPI_RETURN (ERR(error));

    /* close the message queue */
    error = MQClose (hQueue, 0);
    if (NOERROR != error)
      LAPI_RETURN (ERR(error));

    /* End of subroutine. */
    printf("\nProgram completed successfully.\n");
    LAPI_RETURN (NOERROR);

}


/************************************************************************

    FUNCTION:   ProcessAlarmMessage

    PURPOSE:    Process and display the Alarm Message information.
    
    NOTE:       

*************************************************************************/

STATUS ProcessAlarmMessage (char *pMsg, WORD msgLen) 
{
    char        szEventTime[MAXALPHATIMEDATE + 1];
    char        szAlarmTime[MAXALPHATIMEDATE + 1];
    ALARM_MSG   pAlarmMsg;
    char far    *pData;
    ALARM_DATA  pAlarmData;
    STATUS      error = NOERROR;

    
    memcpy((ALARM_MSG *)&pAlarmMsg, (ALARM_MSG *)pMsg, sizeof(ALARM_MSG));
	    
    /* see what type of alarm message type we have */
    switch (pAlarmMsg.Type)
    {
      case ALARM_MSG_PENDING_ALARMS:
	printf("Alarm Message Type:%s\n","ALARM_MSG_PENDING_ALARMS");
      break;
      case ALARM_MSG_NEW_ALARM:
	printf("Alarm Message Type:%s\n","ALARM_MSG_NEW_ALARM");
      break;
      case ALARM_MSG_IS_TERMINATING:
	printf("Alarm Message Type:%s\n","ALARM_MSG_IS_TERMINATING");
      break;
      default:
	printf("Invalid Alarm Message Type!\n");
	LAPI_RETURN (NOERROR);
      break;
    }

    /* print out the data */
    printf("Number of Alarms:%d\n",pAlarmMsg.wNumOfAlarms);
    printf("Number of Alarms:%lx\n",pAlarmMsg.Flags);

    /* get a pointer to the ALARMS_DATA structure */
    pData = (char *)OSLockObject(pAlarmMsg.hAlarmsData);
    memcpy((ALARM_DATA *)&pAlarmData, (ALARM_DATA *)pData,
				      sizeof(ALARM_DATA));

    /* convert timedate info to string */
    GetTDString(&(pAlarmData.tmEventTime), szEventTime);
    GetTDString(&(pAlarmData.tmAlarmTime), szAlarmTime);

    /* print out the data */
    printf("Event Time:%s\n",szEventTime);
    printf("Alarm Time:%s\n",szAlarmTime);

    /* Tell Alarm Daemon to process Alarm... */
    error = Alarm_ProcessAlarm(NOTESCLIENT, 0, pAlarmData.EventUNID, 0);

    /* clean up... */
    OSUnlockObject(pAlarmMsg.hAlarmsData);
    OSMemFree(pAlarmMsg.hAlarmsData);

    if (NOERROR != error)
      LAPI_RETURN (ERR(error));

    return (NOERROR);
}


/************************************************************************

   FUNCTION:   GetTDString

*************************************************************************/

void LNPUBLIC  GetTDString( TIMEDATE * ptdModified, char * szTimedate )
{
    WORD            wLen;

    ConvertTIMEDATEToText( NULL, NULL, 
			    ptdModified, 
			    szTimedate, 
			    MAXALPHATIMEDATE,
			    &wLen );
    szTimedate[wLen] = '\0';
    return;
}

