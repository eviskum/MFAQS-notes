/****************************************************************************

    PROGRAM:    sendmail

    FILE:       sendmail.c

    PURPOSE:    Send a Domino and Notes Mail Message using the Notes Mail
               Gateway API functions.

    FUNCTIONS:

        MAINPROC - initializes applicaton.  Calls ProcessArgs and
                   SendMailMainProc.
        SendMailMainProc() - initializes "From" and "Date" fields and calls
                   SendMail.
        SendMail() - Creates and delivers mail message.

    DESCRIPTION:

    SENDMAIL creates a Domino and Notes mail message and transfers the message
    to the router. SENDMAIL uses the Domino and Notes Mail Gateway API functions.

    SendMail() creates the message as a note in the user's mail file.
    It transfers message to the router via mail.box. If successfull,
    it also saves the message in the user's mail file.

    The routine SendMail() handles the case where the system running this
    program is a remote system not connected to the LAN. When attempting
    to open the user's Domino and Notes mail file, SendMail first tries to open
   the mail file on the mail server. If unable to open the file because the
    LAN is not available, SendMail asks the user if they would like to save
    the message in the local MAIL.BOX. If the user selects YES, then SendMail
    opens the mail file on the local machine instead of on the mail server.
    Later, when transferring the message to the router, if we are saving locally,
    SendMail calls MailTransferMessageLocal to copy the message to the MAIL.BOX
    in the local system's Domino and Notes data directory.

    Otherwise, SendMail() opens the mail box on mail server and updates
    the message to the MAIL.BOX there.

****************************************************************************/

#include <string.h>                 /* strtok() */
#include <ctype.h>                  /* isspace() */
#include <stdio.h>
#include <stdlib.h>

/* Lotus C API for Domino and Notes header files */

#include <lapicinc.h>

#include <global.h>
#include <stdnames.h>                   /* FIELD_FORM, etc */
#include <osfile.h>                     /* OSPathNetConstruct */
#include <osmisc.h>                     /* OSLoadString */
#include <nsf.h>                        /* MAXUSERNAME, etc. */
#include <kfm.h>                        /* SECKFMGetUserName */
#include <textlist.h>                   /* ListAllocate, etc. */
#include <ostime.h>                     /* OSCurrentTIMEDATE */
#include <osmem.h>                      /* OSMemFree, etc. */
#include <osenv.h>                      /* OSGetEnvironmentString */
#include <mail.h>                       /* MAIL_SENDTO_ITEM_NUM, etc. */
#include <mailserv.h>                   /* MailOpenMessageFile */
#include <neterr.h>                     /* ERR_NO_NETBIOS */
#include <clerr.h>                      /* ERR_SERVER_NOT_RESPONDING */

#include <lapiplat.h>

#include "sendmail.h"        /* specific to this program */

/* Global variables */
int argc;
char *argv;
char          szErrStr[ERR_STR_LEN+1];
/* 'status' stores the value returned from Lotus C API for Domino and Notes functions. */
STATUS        status;
char          szSendTo[MAXUSERNAME+1];
char          szCopyTo[MAXUSERNAME+1];
char          szFrom[MAXUSERNAME+1];
TIMEDATE      tdDate;
char          szDate[MAXALPHATIMEDATE+1];
char          szSubject[255];
char          szBody[1024];
int           BodyLen;

/****************************************************************************

    FUNCTION:   main / LAPI_MAIN

    PURPOSE:    Main Lotus C API for Domino and Notes subroutine

****************************************************************************/

LAPI_MAIN
{
  LAPI_INIT(status);
  if (status)
    LAPI_INIT_ERROR;


  /* get program arguments */
  ProcessArgs(argc, argv, szSendTo, szCopyTo, szSubject, szBody);

  status = SendMailMainProc();

  LAPI_RETURN (NOERROR);
}

/****************************************************************************

    FUNCTION: SendMailMainProc()

    COMMENTS:
        Initialize "From" field with the user's name, and the "Date"
        field with the current date and time.  Call Sendmail routine to
        process and send mail message.

****************************************************************************/

int SendMailMainProc()
{
  WORD          wDateLen;

  /* Get user's name and initialize "From" field. */
  if (status = SECKFMGetUserName(szFrom))
    {  /* Unable to get user name. */
      printf ("Error: unable to get user name.\n");
      status = QuitSendMail();
    }

  /* Get current time and date. Initialize "Date" field */
  OSCurrentTIMEDATE(&tdDate);
  if (status = ConvertTIMEDATEToText (NULL, NULL,
                  &tdDate, szDate, MAXALPHATIMEDATE,
                  (WORD FAR*)&wDateLen))
    {   /* Unable to initialize date field */
      printf ("Error: unable to initialize Date field.\n");
      status = QuitSendMail();
    }

  szDate[wDateLen] = '\0';

  status = SendMail();

  return(status);

}

/****************************************************************************

    FUNCTION: SendMail()

    PURPOSE:  Creates message with strings szSendTo, etc., obtained from
              program arguments. Transfers message to the router via mail.box.
              Also saves a copy of the message in the user's mail file.

    ALGORITHM:
        1.  Get name of the user's mail server and mail file from the
            NOTES.INI variables "MailServer" and "MailFile".
        2.  Construct full network path to the mail file on mail server.
        3.  Open the mail file on the mail server. If unable to open
            because network not up or not available, then ask user if
            they would like to save locally. If so, set fLocal to TRUE
            and try to open to the local mail file.
        4.  Create a message
        5.  Allocate lists for SendTo, CopyTo, and Recipients items.
        6.  Parse SendTo string entered by user into the dialog box.
            Add each name to the SendTo list and also Recipients.
            This recognizes commas and semicolons as delimiters.
        7.  Parse CopyTo string entered by user into the dialog box.
            Add each name to the CopyTo list and also Recipients.
        8.  Add Recipients, SendTo, and CopyTo items to the message.
        9.  Add Form item to the message: "Memo".
        10. Add From item to the message.
        11. Add Subject item to the message.
        12. Add Delivery Priority item to the message: "N" = Normal.
        13. Add Delivery Report item to the message: "B" = Basic.
        14. Add Composed Date item to the message: use dialog box Date.
        15. Create a Body item. Append text from the global string szBody
            to the body item. Add body item to the message.
        16. Get the current time/date right now and add it to the
            message as the PostedDate item.
        17. Transfer the message to the router.
            a.  If we are saving locally because this is a remote laptop
                not connected to the LAN, try to transfer the message to
                the local MAIL.BOX by calling MailTransferMessageLocal.
                If successful transfering message to local MAIL.BOX,
                update the message to the user's local mail file.
            b   If we are connected to a LAN and saving to files on the
                mail server, construct a full net path to the router's
                MAIL.BOX file on the mail server. Try to open MAIL.BOX.
                If successful opening MAIL.BOX on mail server, then
                copy the message to the mail box on the server. Then
                update the message to the user's mail file on the server.
        18. Clean up: Unlock and free memory. Close messages and
            databases.
        19. Return.

****************************************************************************/

int SendMail()
{
  char        szMailServerName[MAXUSERNAME+1];
  char        szMailFileName[MAXUSERNAME+1];
  char        szMailFilePath[MAXPATH+1];
  char        szMailBoxPath[MAXPATH+1];
  char        szLocalMailBox[10];
  STATUS      error = NOERROR;
  DBHANDLE    hMailFile;
  DBHANDLE    hMailBox = NULLHANDLE;
  BOOL        fLocal = FALSE;
  NOTEHANDLE  hMsg;
  HANDLE      hRecipientsList = NULLHANDLE;
  HANDLE      hSendToList = NULLHANDLE;
  HANDLE      hCopyToList = NULLHANDLE;
  WORD        wRecipientsSize = 0, wSendToSize = 0, wCopyToSize = 0;
  WORD        wRecipientsCount = 0, wSendToCount = 0, wCopyToCount = 0;
  LIST        *plistRecipients, *plistSendTo, *plistCopyTo;
  char        *szNextName;        /* used when parsing szSendTo, etc. */
  char        szPriority[] = "N"; /* "Normal" */
  char        szReport[] = "B";   /* "Basic" */
  HANDLE      hBodyItem = NULLHANDLE;
  DWORD       dwBodyItemLen;
  DBHANDLE    hOrigDB;
  NOTEID      OrigNoteID;
  OID         OrigNoteOID, NewNoteOID;

  BodyLen = strlen(szBody);

  /* prepare the message strings */
  ConvertNewlinesToNulls(szBody, BodyLen);

  if (!OSGetEnvironmentString(MAIL_MAILSERVER_ITEM, /*"MailServer"*/
               szMailServerName, MAXUSERNAME))
    {   /* Unable to get mail server name */
      printf ("Error: unable to get mail server name.\n");
      error = QuitSendMail();
    }

  if (!OSGetEnvironmentString(MAIL_MAILFILE_ITEM, /*"MailFile"*/
               szMailFileName, MAXUSERNAME))
    {   /* Unable to get mail file name */
      printf ("Error: unable to get mail file name.\n");
      error = QuitSendMail();
    }

  /*  First try to open the user's mail file on the mail server.
      If unable to open because LAN not available, then ask user if
      they would like to save locally.
  */
  OSPathNetConstruct( NULL, szMailServerName, szMailFileName,
           szMailFilePath);

  status = MailOpenMessageFile(szMailFilePath, &hMailFile);

#if 0
  if ( (ERR(status) == ERR_NO_NETBIOS) ||
       (ERR(status) == ERR_SERVER_NOT_RESPONDING) )
#endif
  if ( (ERR(status) == ERR_SERVER_NOT_RESPONDING) )
    /* laptop not connected to server */
    {
      status = NOERROR;

      /* Ask user if they would like to deliver msg to local MAIL.BOX */
      printf("Would you like to deliver the mail message to your local Mail Box (YES/NO)?: ");
      fflush (stdout);
      gets(szLocalMailBox);

      /* Unable to reach Mail Server. Save in local MAIL.BOX? */
      if (stricmp(szLocalMailBox, "YES") == 0)
        {
          /* yes - create and save message in local mail file */
          fLocal = TRUE;
          status = MailOpenMessageFile(szMailFileName, &hMailFile);
        }
      else
        { /* no - user wants to connect to server. Error condition.*/
          status = ERR_SERVER_NOT_RESPONDING;
        }
    }

  if (status)
    { /* Unable to open user's Domino and Notes mail file */
      printf ("Error: unable to open user's mail file.\n");
      status = QuitSendMail();
    }

  if (status = MailCreateMessage(hMailFile, &hMsg))
    { /* Unable to create memo in mail file */
      printf ("Error: unable to create memo in mail file.\n");
      goto CloseFile;
    }

  if (status = ListAllocate(0, 0, TRUE, &hRecipientsList,
             &plistRecipients, &wRecipientsSize))
    {  /* Unable to allocate list */
      printf ("Error: unable to allocate list.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }
  OSUnlockObject(hRecipientsList);

  if (status = ListAllocate(0, 0, TRUE, &hSendToList,
             &plistSendTo, &wSendToSize))
    {
      printf ("Error: unable to allocate list.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }
  OSUnlockObject(hSendToList);

  if (status = ListAllocate(0, 0, TRUE, &hCopyToList,
             &plistCopyTo, &wCopyToSize))
    {
      printf ("Error: unable to allocate list.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }
  OSUnlockObject(hCopyToList);


  /* Parse SendTo string. Add names to SendTo and Recipients lists. */
  for (szNextName = strtok(szSendTo, ",");
       szNextName != (char*)NULL;
       szNextName = strtok(NULL, ","))
    {
      while (isspace(*szNextName))    /* Skip white space before name */
      szNextName++;

      if (status = ListAddEntry(hSendToList, TRUE, &wSendToSize,
                                wSendToCount++, szNextName,
                                (WORD)strlen(szNextName)))
        {   /* Unable to add name to SendTo list */
     printf ("Error: unable to add name to SendTo list.\n");
     error=SENDMAILERROR;
     goto CloseMsg;
        }

      if (status = ListAddEntry(hRecipientsList, TRUE, &wRecipientsSize,
                                wRecipientsCount++, szNextName,
                                (WORD)strlen(szNextName)))
        {   /* Unable to add name to Recipients list */
     printf ("Error: unable to add name to Recipients list.\n");
     error=SENDMAILERROR;
     goto CloseMsg;
        }
    }

  /* Parse CopyTo string. Add names to CopyTo and Recipients list. */

  for (szNextName = strtok(szCopyTo, ",");
       szNextName != (char*)NULL;
       szNextName = strtok(NULL, ","))
    {
      while (isspace(*szNextName))
      szNextName++;

      if (status = ListAddEntry(hCopyToList, TRUE, &wCopyToSize,
                                wCopyToCount++, szNextName,
                                (WORD)strlen(szNextName)))
        { /* Unable to add name to CopyTo list */
          printf ("Error: unable to add name to CopyTo list.\n");
          error=SENDMAILERROR;
          goto CloseMsg;
        }

      if (status = ListAddEntry(hRecipientsList, TRUE, &wRecipientsSize,
                                wRecipientsCount++, szNextName,
                                (WORD)strlen(szNextName)))

        {
          printf ("Error: unable to add name to Recipients list.\n");
          error=SENDMAILERROR;
          goto CloseMsg;
        }
    }

  /*  Suggested enhancements: You might want to add code here to verify
      that the name & address book on the mail server contains person or
      group documents for each of the named recipients. See Lotus C API
     for Domino and Notes function NAMELookup(). Possibly query user to
     resolve unknown recipient names. You might also want to check the
     recipients list to ensure it contains no duplicate names.
  */

  /* Add the Recipients item to the message. */
  if (wRecipientsCount == 0)  /* Mail memo has no recipients. */
    {
      printf ("Error: mail message has no recipients.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  if (status = MailAddRecipientsItem( hMsg, hRecipientsList,
                 wRecipientsSize))
    {
      /* Unable to set Recipient item in memo */
      printf ("Error: unable to set Recipient item in memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }
  /*  MailAddRecipientsItem and MailAddHeaderItemByHandle both attach
      the memory used by the list to the message. Set handle to NULL
      after these functions succeed so the code at CloseMsg: below does
      not attempt to free it.
  */
  hRecipientsList = NULLHANDLE;

  /* Add the SendTo and CopyTo items to the message. */

  if (status = MailAddHeaderItemByHandle( hMsg, MAIL_SENDTO_ITEM_NUM,
                hSendToList, wSendToSize, 0))
    {  /* Unable to set SendTo item in memo */
      printf ("Error: unable to set SendTo item in memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }
  hSendToList = NULLHANDLE;

  if (status = MailAddHeaderItemByHandle( hMsg, MAIL_COPYTO_ITEM_NUM,
                hCopyToList, wCopyToSize, 0))
    { /* Unable to set CopyTo item in memo */
      printf ("Error: unable to set CopyTo item in memo.\n");
      goto CloseMsg;
    }
  hCopyToList = NULLHANDLE;

  /* Add the Form item to the message */
  if (status = MailAddHeaderItem( hMsg, MAIL_FORM_ITEM_NUM,
             MAIL_MEMO_FORM,
             (WORD)strlen(MAIL_MEMO_FORM)))
    { /* Unable to set Form item in memo  */
      printf ("Error: unable to set Form item in memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  /* Add From, Subject, Delivery Priority, & etc. items to the message */
  if (status = MailAddHeaderItem( hMsg, MAIL_FROM_ITEM_NUM,
             szFrom, (WORD)strlen(szFrom)))
    { /* Unable to set From item in memo */
      printf ("Error: unable to set From item in memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  if (status = MailAddHeaderItem( hMsg, MAIL_SUBJECT_ITEM_NUM,
             szSubject, (WORD)strlen(szSubject)))
    { /* Unable to set Subject item in memo */
      printf ("Error: unable to set Subject item in memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  if (status = MailAddHeaderItem( hMsg, MAIL_DELIVERYPRIORITY_ITEM_NUM,
            szPriority, (WORD)strlen(szPriority)))
    { /* Unable to set Delivery Priority item in memo */
      printf ("Error: unable to set Delivery Priority item in memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  if (status = MailAddHeaderItem( hMsg, MAIL_DELIVERYREPORT_ITEM_NUM,
            szReport, (WORD)strlen(szReport)))
    { /* Unable to set Delivery Report into memo */
      printf ("Error: unable to set Delivery Report item in memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  /*  set "ComposedDate" to tdDate = when dialog box was initialized */
  if (status = MailAddHeaderItem( hMsg, MAIL_COMPOSEDDATE_ITEM_NUM,
             (char*)(&tdDate),
             (WORD)sizeof(TIMEDATE)))
    { /* Unable to set Composed Date in memo */
      printf ("Error: unable to set Composed Date item in memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  if (status = MailCreateBodyItem (&hBodyItem, &dwBodyItemLen))
    { /* Unable to create body item in message */
      printf ("Error: unable to create body item in memo.\n");
      hBodyItem = NULLHANDLE;
      error=SENDMAILERROR;
      goto CloseMsg;
    }
  if (status = MailAppendBodyItemLine (hBodyItem, &dwBodyItemLen,
                   szBody, (WORD)BodyLen))
    { /* Unable to append text to body */
      printf ("Error: unable to append text to body.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  if (status = MailAddBodyItemExt(hMsg, hBodyItem, dwBodyItemLen, NULL))
    { /* Unable to add Body item to memo */
      printf ("Error: unable to add body item to memo.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  /* Set "PostedDate" to the current time/date right now */
  OSCurrentTIMEDATE(&tdDate);
  if (status = MailAddHeaderItem( hMsg, MAIL_POSTEDDATE_ITEM_NUM,
             (char*)(&tdDate),
             (WORD)sizeof(TIMEDATE)))
    {
      printf ("Error: unable to set date.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }

  /*  Deliver the message. */
  /*  If local, transfer message to the local mail.box */
  if (fLocal)
    {
      if (status = MailTransferMessageLocal(hMsg))
        {
     /* Unable to transfer message to local mail box */
     printf ("Error: unable to transfer message to local mail box.\n");
     error=SENDMAILERROR;
     goto CloseMsg;
        }
      /* else we successfully transferred msg to local mail box */
      /* Save msg to user's mail file and clean up.*/
      if (status = NSFNoteUpdate(hMsg, UPDATE_NOCOMMIT))
        {   /* Unable to update message in local mail file */
          printf ("Error: unable to update message in local mail box.\n");
          error=SENDMAILERROR;
        }
      goto CloseMsg;
    }

  /*  System is connected to the LAN (fLocal == FALSE). Open the
      router's MAIL.BOX on the mail server, then copy msg there.
   */
  OSPathNetConstruct(NULL, szMailServerName, MAILBOX_NAME, szMailBoxPath);

  if (status = NSFDbOpen(szMailBoxPath, &hMailBox))
    {
      printf ("Error: unable to open mail box.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }
  /*  Copy the message, which is a note in the user's mail file,
      to the mail box. Perform this copy by changing the origin to
      the mail box then updating. Save the message's DBID, NOTEID,
      and OID. Set the DBID to the MAIL.BOX handle, the NOTEID to zero,
      and the OID to a newly generated OID associated with MAIL.BOX.
      Then update the message. This stores it in the MAIL.BOX file.
      Finally, restore the DBID, NOTEID, and OID.
   */
  NSFNoteGetInfo(hMsg, _NOTE_ID,  &OrigNoteID);
  NSFNoteGetInfo(hMsg, _NOTE_DB,  &hOrigDB);
  NSFNoteGetInfo(hMsg, _NOTE_OID, &OrigNoteOID);

  /* Set the message's OID database ID to match the mail box */
  if (status = NSFDbGenerateOID (hMailBox, &NewNoteOID))
    {
      /* Unable to generate originator ID for mail box */
      printf ("Error: unable to generate id for mail box.\n");
      error=SENDMAILERROR;
      goto CloseMsg;
    }
  NSFNoteSetInfo(hMsg, _NOTE_DB,  &hMailBox);
  NSFNoteSetInfo(hMsg, _NOTE_ID,  0);
  NSFNoteSetInfo(hMsg, _NOTE_OID, &NewNoteOID);

  /* Update message into MAIL.BOX on mail server. */
  if (status = NSFNoteUpdate(hMsg, UPDATE_NOCOMMIT))
    {
      /* Unable to update message to router mail box */
      printf ("Error: unable to update message to router mail box.\n");
      error=SENDMAILERROR;
    }
  else/* message successfully copied into router's mail box */
    {   /* restore msg to user's mail file and Update to save it there.*/
      NSFNoteSetInfo(hMsg, _NOTE_DB,  &hOrigDB);
      NSFNoteSetInfo(hMsg, _NOTE_ID,  &OrigNoteID);
      NSFNoteSetInfo(hMsg, _NOTE_OID, &OrigNoteOID);

      status = NSFNoteUpdate(hMsg, UPDATE_NOCOMMIT);
    }

return(status);

CloseMsg:
  if (hRecipientsList != NULLHANDLE)  OSMemFree(hRecipientsList);
  if (hSendToList != NULLHANDLE)      OSMemFree(hSendToList);
  if (hCopyToList != NULLHANDLE)      OSMemFree(hCopyToList);


  if (error == NOERROR)
    {
      if (status = MailCloseMessage(hMsg))
      { /* Unable to close memo */
          printf ("Error: unable to close memo.\n");
          error=SENDMAILERROR;
      }
      else
        if (hBodyItem != NULLHANDLE)  OSMemFree (hBodyItem);
    }
    else
      {
        status = MailCloseMessage(hMsg);
        if ((status == NOERROR) && (hBodyItem != NULLHANDLE))
          OSMemFree (hBodyItem);
      }
    if (hMailBox != NULLHANDLE)
        NSFDbClose (hMailBox);

CloseFile:
  if (error == NOERROR)
    {
      if (status = MailCloseMessageFile(hMailFile))
        { /* Unable to close mail file. */
          printf ("Error: unable to close mail file.\n");
          error=SENDMAILERROR;
        }
    }
  else /* have already encountered an error condition */
    {    /* so don't check for further errors closing */
      MailCloseMessageFile(hMailFile);
    }

  if (error == NOERROR)
    /* SendMail Success */
    printf ("SendMail successful.\n");

  status = QuitSendMail();

  return(status);
}

/************************************************************************

    FUNCTION:   QuitSendMail()

    PURPOSE:    Exit SendMail.

*************************************************************************/

int QuitSendMail() {

    NotesTerm();      /* we can't use macro LAPI_RETURN here because it
                      returns to SendMailMainProc */
    return(0);
}

/************************************************************************

    FUNCTION:   ConvertNewlinesToNulls(char* szBody, int BodyLen)

    PURPOSE:    Filter CR from body text. Replace with NUL char.

*************************************************************************/

void  LNPUBLIC  ConvertNewlinesToNulls(char* szBody, int BodyLen)
{
  int    wByte;

  for (wByte=0; wByte<BodyLen; wByte++)
    {
      if (szBody[wByte] == '\n' )
   szBody[wByte] = '\0';
    }

  return;
}

/****************************************************************************

    FUNCTION: BuildErrStr (char* errorstr)

    PURPOSE:  Build an error string based on the specified status code.

    INPUTS:   errorstr = an error string defined in the local application.

****************************************************************************/

char* BuildErrStr (char *errorstr)
{
  int wLen;

  strcpy(szErrStr, errorstr);
  if (status)
    {
      strcat(szErrStr, " - \n");
      wLen = strlen(szErrStr);
      OSLoadString ( NULLHANDLE, ERR(status), szErrStr+wLen,
          (WORD)(ERR_STR_LEN-wLen) );
    }
  return (szErrStr);
}


/****************************************************************************

    FUNCTION: ProcessArgs (int argc, char *argv[],
                             char *szSendTo, char *szCopyTo, char *szSubject,
                             char *szBody)

    PURPOSE:  Get command line arguments from user.

    INPUTS:   szSendTo  - Send message to User Name.
              szCopyTo  - Copy message to User Name.
              szSubject - Mail Message Subject.
              szBody    - Body of Mail Message.

****************************************************************************/


void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                             char *szSendTo, char *szCopyTo, char *szSubject,
                             char *szBody)
{
    if (argc != 5)
    {
        printf("Enter SendTo: ");
        fflush (stdout);
        gets(szSendTo);
        printf("\n");
        printf ("Enter CopyTo:  ");
        fflush (stdout);
        gets(szCopyTo);
        printf ("Enter Subject:  ");
        fflush (stdout);
        gets(szSubject);
        printf ("Enter Body of message:  ");
        fflush (stdout);
        gets(szBody);
    }
    else
    {
        strcpy(szSendTo, argv[1]);
        strcpy(szCopyTo, argv[2]);
        strcpy(szSubject, argv[3]);
        strcpy(szBody, argv[4]);
    } /* end if */
} /* ProcessArgs */


