/****************************************************************************

    PROGRAM:    sendmail

    FILE:       sendmail.c

    PURPOSE:    Send a Domino and Notes Mail Message using the Domino and
               Notes Mail Gateway API functions.

    FUNCTIONS:


    DESCRIPTION:

    SENDMAIL creates a Domino and Notes mail message and transfers the
   message to the router. SENDMAIL uses the Domino and Notes Mail
   Gateway API functions. The purpose of SENDMAIL is to show how to
   mail-enable a Windows application using the Domino and Notes Mail
   Gateway API functions.

    SENDMAIL is a one-dialog box application. It immediately displays
    the modal "Send Notes Mail" dialog box to get user input. Then it
    processes the user input by sending a Domino and Notes mail message.
   SENDMAIL exits after sending one message.

    The dialog box contains fields similar to a Domino and Notes Memo
   form. The dialog box procedure initializes the "From" field with
   the user's name, and the "Date" field with the current date and time.
   These fields are not editable by the user. The user fills in "To",
   "Cc", "Subject" and "Body" fields. SNDMAIL parses the To and Cc fields
    for multiple recipients. The recipient names may be separated by
    commas or semicolons. The user may click SEND or CANCEL to close
    the dialog box.

    When user clicks SEND, the routine SendMailMainProc() gets the
    contents of the SendTo, CopyTo, Subject, and Body fields, and
    saves these strings in global variables. It filters the Body
    field, then it calls SendMail().

    SENDMAIL filters the Body field looking for CR/NL pairs that
    appear if the user pressed Return in the Body field. SENDMAIL
    replaces these CR/NL pairs with a space followed by a NUL
    character. Domino and Notes displays a hard carriage return when a
   NUL character appears in plain text or rich text.

    The routine SendMail() creates a message with the strings saved in
    the global variables. SendMail() creates the message as a note in
    the user's mail file. It transfers message to the router via
    mail.box. If successfull, it also saves the message in the user's
    mail file.

    The routine SendMail() handles the case where the system running this
    program is a remote laptop not connected to the LAN. When attempting
    to open the user's Domino and Notes mail file, SendMail first tries
   to open the mail file on the mail server. If unable to open the file
   because the LAN is not available, SendMail asks the user, via a dialog
   box, if they would like to save the message in the local MAIL.BOX. If
   the user selects OK, then SendMail opens the mail file on the local
   machine instead of on the mail server. Later, when transferring the
   message to the router, if we are saving locally, SendMail calls
    MailTransferMessageLocal to copy the message to the MAIL.BOX in
    the local system's Domino and Notes data directory.

    Otherwise, if SendMail() opens the mail box on mail server and updates
    the message to the MAIL.BOX there.

****************************************************************************/


#include "sendmail.h"        /* specific to this program */
#include "sendmerr.h"

/* used to check for SendTo name */
#define SEND_TO_NAME 5

/* Global variables */

WORD     wLen;
char     szErrStr[ERR_STR_LEN+1];
STATUS      status;
        /*  'status' stores the value returned from Lotus C API for Domino and
          Notes functions. It is a global so that SendMail() may return an
         application-specific error code, but SendMailMainProc() can
         determine what Lotus C API for Domino and Notes error caused
         SendMail to return unsuccessfully.
         */

CString     szSendTo;
CString     szCopyTo;
CString     szSubject;
char        *szBody;
char        szDate[MAXALPHATIMEDATE+1];
char     szFrom[MAXUSERNAME+1];
TIMEDATE    tdDate;
WORD        wBodyLen;
Boolean     gDone;



/****************************************************************************

   FUNCTION PROTOTYPES

****************************************************************************/

void ConvertNewlinesToNulls(char * szBody, WORD wBodyLen);




/****************************************************************************

    FUNCTION: LAPI_MAIN

    PURPOSE:  Initialize Domino and Notes and call SendMailProc.

****************************************************************************/

LAPI_MAIN
{
  LAPI_INIT(status);
  if ( !status ) SendMailMainProc();
  LAPI_RETURN(status);
}



/****************************************************************************

    FUNCTION: BuildErrStr (STATUS error)

    PURPOSE:  Build an error string based on the specified status code.

    INPUTS:   error = a string resource ID of an error string defined
              in the local application's resource table. An example
              would be ERR_SENDMAIL_SERVERNAME, "Unable to get mail
              server name".

    COMMENTS:

        Loads the error string associated with "error" into the global
        variable szErrStr by calling OSLoadString and specifying the
        module instance handle as the first parameter. Then, if the global
        variable "status" is non-zero, this calls OSLoadString again, this
        time specifying NULLHANDLE as the first parameter, to get the
        error message string associated with the Domino and Notes error code
      "status". This appends the Domino and Notes-defined string to the end
      of the string already in global variable szErrStr and returns szErrStr.

    RETURNS:
        This returns szErrStr.

****************************************************************************/

char * BuildErrStr (STATUS error)
{
    OSLoadString( NULLHANDLE, error, (char*)szErrStr, ERR_STR_LEN);
    if (status)
    {
        strcat( (char*)szErrStr, " - \n");
        wLen = strlen( (char*)szErrStr);
        OSLoadString ( NULLHANDLE, ERR(status),  (char*)szErrStr+wLen,
                                                ERR_STR_LEN-wLen );
    }
    return (szErrStr);
}


/************************************************************************

    FUNCTION:   ConvertNewlinesToNulls(char * szBody, WORD wBodyLen)

    PURPOSE:    Filter CR+NL pairs from body text. Replace with space+
                NUL char.

*************************************************************************/

void ConvertNewlinesToNulls(char * szBody, WORD wBodyLen)
{
    WORD    wByte;

    for (wByte=0; wByte<wBodyLen; wByte++)
    {
        if ( (szBody[wByte] == '\r') && (szBody[wByte+1] == '\n') )
        {
           szBody[wByte] = ' ';
           szBody[wByte+1] = '\0';
        }
    }

    return;
}

/****************************************************************************

    FUNCTION: SendMail()

    PURPOSE:  Creates message with strings szSendTo, etc., obtained from
              the dialog box. Transfers message to the router via mail.box.
              Also saves a copy of the message in the user's mail file.

    ALGORITHM:
        This assumes the global variables hSendTo, hCopyTo, szFrom, tdDate,
        etc., are initialized and contain the values specified by the user
        from the dialog box.

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

STATUS SendMail( void )
{
    char        szMailServerName[MAXUSERNAME+1];
    char        szMailFileName[MAXUSERNAME+1];
    char        szMailFilePath[MAXPATH+1];
    char        szMailBoxPath[MAXPATH+1];
    STATUS      error = NOERROR;    /* returned ERR_SENDMAIL_... value */
    DBHANDLE    hMailFile;
    DBHANDLE    hMailBox = NULLHANDLE;
    BOOL        fLocal = FALSE;
    NOTEHANDLE  hMsg;
    HANDLE      hRecipientsList = NULLHANDLE;
    HANDLE      hSendToList = NULLHANDLE;
    HANDLE      hCopyToList = NULLHANDLE;
    WORD        wRecipientsSize, wSendToSize, wCopyToSize;
    WORD        wRecipientsCount, wSendToCount, wCopyToCount;
    LIST       *plistRecipients, *plistSendTo, *plistCopyTo;
    char       *szNextName;        /* used when parsing szSendTo, etc. */
    char        szPriority[] = "N"; /* "Normal" */
    char        szReport[] = "B";   /* "Basic" */
    HANDLE      hBodyItem = NULLHANDLE;
    DWORD       dwBodyItemLen;
    DBHANDLE    hOrigDB;
    NOTEID      OrigNoteID;
    OID         OrigNoteOID, NewNoteOID;


   wSendToCount = wCopyToCount = 0;

    if (!OSGetEnvironmentString(MAIL_MAILSERVER_ITEM, /*"MailServer"*/
                       szMailServerName, MAXUSERNAME))
    {   /* Unable to get mail server name */
        error = ERR_SENDMAIL_SERVERNAME;
        goto Exit;
    }

    if (!OSGetEnvironmentString(MAIL_MAILFILE_ITEM, /*"MailFile"*/
                       szMailFileName, MAXUSERNAME))
    {   /* Unable to get mail file name */
        error = ERR_SENDMAIL_MAILFILENAME;
        goto Exit;
    }

    /*  First try to open the user's mail file on the mail server.
        If unable to open because LAN not available, then ask user if
        they would like to save locally.
     */
    OSPathNetConstruct( NULL, szMailServerName, szMailFileName,
                        szMailFilePath);

    status = MailOpenMessageFile(szMailFilePath, &hMailFile);

    if (ERR(status) == ERR_NO_NETBIOS || ERR(status) == ERR_SERVER_NOT_RESPONDING)   /* laptop not connected to server */
    {
        /* Ask user if they would like to deliver msg to local MAIL.BOX */
        status = NOERROR;
        /* Unable to reach Mail Server. Save in local MAIL.BOX? */
        if (OK == MessageBoxOKCancel( BuildErrStr(MSG_SENDMAIL_ASKUSELOCAL), szMessageBoxTitle ))
        {
            /* yes - create and save message in local mail file */
            fLocal = TRUE;
            status = MailOpenMessageFile(szMailFileName, &hMailFile);
        }
        else
        {   /* no - user wants to connect to server. Error condition.*/
            status = ERR_SERVER_NOT_RESPONDING;
        }
    }
    if (status)
    {   /* Unable to open user's Domino and Notes mail file */
        error = ERR_SENDMAIL_CANTOPENMAILFILE;
        goto Exit;
    }

    if (status = MailCreateMessage(hMailFile, &hMsg))
    {   /* Unable to create memo in mail file */
        error = ERR_SENDMAIL_CANTCREATEMEMO;
        goto CloseFile;
    }

    if (status = ListAllocate(0, 0, TRUE, &hRecipientsList,
                &plistRecipients, &wRecipientsSize))
    {
        /* Unable to allocate list */
        error = ERR_SENDMAIL_CANTALLOCATELIST;
        goto CloseMsg;
    }
    OSUnlockObject(hRecipientsList);

    if (status = ListAllocate(0, 0, TRUE, &hSendToList,
                &plistSendTo, &wSendToSize))
    {
        error = ERR_SENDMAIL_CANTALLOCATELIST;
        goto CloseMsg;
    }
    OSUnlockObject(hSendToList);

    if (status = ListAllocate(0, 0, TRUE, &hCopyToList,
                &plistCopyTo, &wCopyToSize))
    {
         error = ERR_SENDMAIL_CANTALLOCATELIST;
         goto CloseMsg;
    }
    OSUnlockObject(hCopyToList);

    /* check here to see if a name has been entered in SendTo field */
    if (strlen(szSendTo) < SEND_TO_NAME)
    {
      error = ERR_SENDMAIL_NORECIPIENTS;
      goto CloseMsg;
    }

    /* Parse SendTo string. Add names to SendTo and Recipients lists. */

    for (szNextName = strtok( (char*)szSendTo, ":,");
         szNextName != (char*)NULL;
         szNextName = strtok(NULL, ":,"))
    {
        while (isspace(*szNextName))    /* Skip white space before name */
            szNextName++;

        if (status = ListAddEntry(hSendToList, TRUE, &wSendToSize,
                                wSendToCount++, szNextName,
                                (WORD)strlen(szNextName)))
        {   /* Unable to add name to SendTo list */
            error = ERR_SENDMAIL_CANTADDTOSENDLIST;
            goto CloseMsg;
        }

        if (status = ListAddEntry(hRecipientsList, TRUE, &wRecipientsSize,
                                wRecipientsCount++, szNextName,
                                (WORD)strlen(szNextName)))
        {   /* Unable to add name to Recipients list */
            error = ERR_SENDMAIL_CANTADDTORECIPLIST;
            goto CloseMsg;
        }
    }

    /* Parse CopyTo string. Add names to CopyTo and Recipients list. */

    for (szNextName = strtok( (char*)szCopyTo, ":,");
         szNextName != (char*)NULL;
         szNextName = strtok(NULL, ":,"))
    {
        while (isspace(*szNextName))
            szNextName++;

        if (status = ListAddEntry(hCopyToList, TRUE, &wCopyToSize,
                                wCopyToCount++, szNextName,
                                (WORD)strlen(szNextName)))
        {   /* Unable to add name to CopyTo list */
            error = ERR_SENDMAIL_CANTADDTOCOPYLIST;
            goto CloseMsg;
        }

        if (status = ListAddEntry(hRecipientsList, TRUE, &wRecipientsSize,
                                wRecipientsCount++, szNextName,
                                (WORD)strlen(szNextName)))
        {
            error = ERR_SENDMAIL_CANTADDTORECIPLIST;
            goto CloseMsg;
        }
    }

    /*  Suggested enhancements: You might want to add code here to verify
        that the name & address book on the mail server contains person or
        group documents for each of the named recipients. See Lotus C API
      for Domino and Notes function NAMELookup(). Possibly query user
      to resolve unknown recipient names. You might also want to check
      the recipients list to ensure it contains no duplicate names.
     */

    /* Add the Recipients item to the message. */

    if (wRecipientsCount == 0)  /* Mail memo has no recipients. */
    {
        error = ERR_SENDMAIL_NORECIPIENTS;
        goto CloseMsg;
    }

    if (status = MailAddRecipientsItem( hMsg, hRecipientsList,
                                        wRecipientsSize))
    {
        /* Unable to set Recipient item in memo */
        error = ERR_SENDMAIL_CANTSETRECIPIENT;
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
    {
        /* Unable to set SendTo item in memo */
        error = ERR_SENDMAIL_CANTSETSENDTO;
        goto CloseMsg;
    }
    hSendToList = NULLHANDLE;

    if (status = MailAddHeaderItemByHandle( hMsg, MAIL_COPYTO_ITEM_NUM,
                                            hCopyToList, wCopyToSize, 0))
    {   /* Unable to set CopyTo item in memo */
        error = ERR_SENDMAIL_CANTSETCOPYTO;
        goto CloseMsg;
    }
    hCopyToList = NULLHANDLE;

    /* Add the Form item to the message */
    if (status = MailAddHeaderItem( hMsg, MAIL_FORM_ITEM_NUM,
                                    MAIL_MEMO_FORM,
                                    (WORD)strlen(MAIL_MEMO_FORM)))
    {   /* Unable to set Form item in memo  */
        error = ERR_SENDMAIL_CANTSETFORM;
        goto CloseMsg;
    }

    /* Add From, Subject, Delivery Priority, & etc. items to the message */
    if (status = MailAddHeaderItem( hMsg, MAIL_FROM_ITEM_NUM,
                                     (char*)szFrom, (WORD)strlen((char*)szFrom)))
    {   /* Unable to set From item in memo */
        error = ERR_SENDMAIL_CANTSETFROM;
        goto CloseMsg;
    }

    if (status = MailAddHeaderItem( hMsg, MAIL_SUBJECT_ITEM_NUM,
                                    (char*)szSubject, (WORD)strlen((char*)szSubject)))
    {   /* Unable to set Subject item in memo */
        error = ERR_SENDMAIL_CANTSETSUBJECT;
        goto CloseMsg;
    }

    if (error = MailAddHeaderItem( hMsg, MAIL_DELIVERYPRIORITY_ITEM_NUM,
                                   szPriority, (WORD)strlen(szPriority)))
    {   /* Unable to set Delivery Priority item in memo */
        error = ERR_SENDMAIL_CANTSETPRIORITY;
        goto CloseMsg;
    }

    if (error = MailAddHeaderItem( hMsg, MAIL_DELIVERYREPORT_ITEM_NUM,
                                   szReport, (WORD)strlen(szReport)))
    {   /* Unable to set Delivery Report into memo */
        error = ERR_SENDMAIL_CANTSETREPT;
        goto CloseMsg;
    }

    /*  set "ComposedDate" to tdDate = when dialog box was initialized */
    if (status = MailAddHeaderItem( hMsg, MAIL_COMPOSEDDATE_ITEM_NUM,
                                    (char*)(&tdDate),
                                    (WORD)sizeof(TIMEDATE)))
    {   /* Unable to set Composed Date in memo */
        error = ERR_SENDMAIL_CANTSETCOMPDATE;
        goto CloseMsg;
    }

    if (status = MailCreateBodyItem (&hBodyItem, &dwBodyItemLen))
    {   /* Unable to create body item in message */
        error = ERR_SENDMAIL_CANTCREATEBODY;
        hBodyItem = NULLHANDLE;
        goto CloseMsg;
    }

    if (status = MailAppendBodyItemLine (hBodyItem, &dwBodyItemLen,
                                        (char*)szBody, wBodyLen))
    {   /* Unable to append text to body */
        error = ERR_SENDMAIL_CANTAPPENDBODYLINE;
        goto CloseMsg;
    }

    if (status = MailAddBodyItemExt(hMsg, hBodyItem, dwBodyItemLen, NULL))
    {   /* Unable to add Body item to memo */
        error = ERR_SENDMAIL_CANTADDBODY;
        goto CloseMsg;
    }

    /* Set "PostedDate" to the current time/date right now */
    OSCurrentTIMEDATE(&tdDate);
    if (status = MailAddHeaderItem( hMsg, MAIL_POSTEDDATE_ITEM_NUM,
                                    (char*)(&tdDate),
                                    (WORD)sizeof(TIMEDATE)))
    {
        error = ERR_SENDMAIL_CANTSETPOSTDATE;
        goto CloseMsg;
    }

    /*  Deliver the message. */
    /*  If local, transfer message to the local mail.box */
    if (fLocal)
    {
        if (status = MailTransferMessageLocal(hMsg))
        {
            /* Unable to transfer message to local mail box */
            error = ERR_SENDMAIL_CANTTRANSFER;
            goto CloseMsg;
        }
        /* else we successfully transferred msg to local mail box */
        /* Save msg to user's mail file and clean up.*/
        if (status = NSFNoteUpdate(hMsg, UPDATE_NOCOMMIT))
        {   /* Unable to update message in local mail file */
            error = ERR_SENDMAIL_CANTUPDATEFILE;
        }
        goto CloseMsg;
    }

    /*  System is connected to the LAN (fLocal == FALSE). Open the
        router's MAIL.BOX on the mail server, then copy msg there.
     */
    OSPathNetConstruct(NULL, szMailServerName, MAILBOX_NAME, szMailBoxPath);

    if (status = NSFDbOpen(szMailBoxPath, &hMailBox))
    {
        error = ERR_SENDMAIL_CANTOPENMAILBOX;
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
        error = ERR_SENDMAIL_CANTGENOID;
        goto CloseMsg;
    }
    NSFNoteSetInfo(hMsg, _NOTE_DB,  &hMailBox);
    NSFNoteSetInfo(hMsg, _NOTE_ID,  0);
    NSFNoteSetInfo(hMsg, _NOTE_OID, &NewNoteOID);

    /* Update message into MAIL.BOX on mail server. */
    if (status = NSFNoteUpdate(hMsg, UPDATE_NOCOMMIT))
    {
       /* Unable to update message to router mail box */
       error = ERR_SENDMAIL_CANTUPDATEBOX;
    }
    else/* message successfully copied into router's mail box */
    {   /* restore msg to user's mail file and Update to save it there.*/
        NSFNoteSetInfo(hMsg, _NOTE_DB,  &hOrigDB);
        NSFNoteSetInfo(hMsg, _NOTE_ID,  &OrigNoteID);
        NSFNoteSetInfo(hMsg, _NOTE_OID, &OrigNoteOID);

        status = NSFNoteUpdate(hMsg, UPDATE_NOCOMMIT);
    }

CloseMsg:

    if (hRecipientsList != NULLHANDLE)  OSMemFree(hRecipientsList);
    if (hSendToList != NULLHANDLE)      OSMemFree(hSendToList);
    if (hCopyToList != NULLHANDLE)      OSMemFree(hCopyToList);

    if (error == NOERROR)
    {
        if (status = MailCloseMessage(hMsg))
        {   /* Unable to close memo */
            error = ERR_SENDMAIL_CANTCLOSE;
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
        {   /* Unable to close mail file. */
            error = ERR_SENDMAIL_CANTCLOSEFILE;
        }
    }
    else /* have already encountered an error condition */
    {    /* so don't check for further errors closing */
        MailCloseMessageFile(hMailFile);
    }
Exit:
    return(error);
}


