#include "sendmail.h"
#include "sendmerr.h"


extern STATUS     status;
extern Boolean       gDone;
extern TIMEDATE      tdDate;
extern CString    szSubject;
extern char 	  *szBody;
extern char       szSendTo[MAXUSERNAME+1];
extern char       szCopyTo[MAXUSERNAME+1];
extern char       szFrom[MAXUSERNAME+1];
extern char       szDate[MAXALPHATIMEDATE+1];
extern WORD          wBodyLen;
Handle theBody;

/****************************************************************************

    FUNCTION: SendMailMainProc(HWND hWnd)

    PURPOSE:  Invoke and processe the "Sendmdlg" dialog box.

    COMMENTS:

        This routine creates a procedure instance for the modal dialog
        box "Sendmdlg". It calls DialogBox() to process the dialog box. The
        dialog box collects input from the user. When DialogBox returns,
        this processes the user input and calls the function SendMail().

        The Send dialog box returns TRUE if the user clicked SEND. In
        this case, call the function SendMail(). The function SendMail
        opens the MAIL.BOX file, creates a message, sets the items in
        the message, and transfers the message to the router. If the user
        closed the Send dialog box by pressing Cancel or choosing the
        System close command, then do not call SendMail.

        In other windows programs, routines like this would be called
        from a window procedure in response to a menu command message.
        Note that SENDMAIL has no menu and the main window is invisible.
        This function is called directly from WinMain.

****************************************************************************/

OSErr SendMailMainProc( void )
{
   BOOL     nSend;
   short    itemHit;
   Handle      theHdl;
   short    theType;
   Rect     theRect;
    WORD        wDateLen;
   DialogPtr   d;
   CString     tStr;


   
   gDone = FALSE;
   d = GetNewDialog ( 130, nil, (WindowPtr) -1);
   if ( !d ) 
   {
      nSend = -1;
      gDone = TRUE;
   } else {
      
      /* Get user's name and initialize "From" field. */
      if (status = SECKFMGetUserName(szFrom))
      {
         /* Unable to get user name. */
         MessageBoxOK ( BuildErrStr(ERR_SENDMAIL_USERNAME), ( char*)szMessageBoxTitle );
         return (TRUE);
      }

      GetDialogItem( d, FROM_ITEM, &theType, &theHdl, &theRect );
      strcpy( (char*)tStr, (char*)szFrom );
      SetDialogItemText( theHdl, *(Str255*)CtoPstr( (char*)tStr ) );

      /* Get current time and date. Initialize "Date" field */
      OSCurrentTIMEDATE(&tdDate);
      if (status = ConvertTIMEDATEToText (NULL, NULL,
                     &tdDate, szDate, MAXALPHATIMEDATE,
                     &wDateLen))
      {   /* Unable to initialize date field */
         MessageBoxOK( BuildErrStr(ERR_SENDMAIL_INITDATE), szMessageBoxTitle );
         return (TRUE);
      }

      szDate[wDateLen] = '\0';
      GetDialogItem( d, DATE_ITEM, &theType, &theHdl, &theRect );
      SetDialogItemText( theHdl, *(Str255*)CtoPstr( szDate ) );
      ShowWindow (d);
      SetPort(d);
   }


   while (gDone == FALSE )
   {
      ModalDialog(NewModalFilterProc(SendDialogProc), &itemHit);

      switch (itemHit) {
         case SEND_BTN:
            gDone = TRUE;
            nSend = TRUE;
            break;
         case Cancel:
            gDone = TRUE;
            nSend = FALSE;
            break;
      }
   }

   DisposeDialog( d );
   
    if (nSend == TRUE)      /* User pressed Send button in Send Dialog. */
    {
      SetCursor( *GetCursor(watchCursor) );

        status = SendMail();

		/* Free up the memory allocated for szbody */
		HUnlock ( theBody);
		DisposeHandle( theBody );
	 
      SetCursor( &qd.arrow );

        /*  'error' contains a value defined by this program. (See file
            SENDMERR.H.) SendMail returns one of these error codes. The
            global variable 'status' contains the value returned by Lotus C API
            for Domino and Notes functions. Concatenate the 2 error strings here.
         */
        if (status)
        {
            MessageBoxOK( BuildErrStr(status), szMessageBoxTitle );
        }
        else    /* Successfully sent Domino and Notes mail. */
        {
            MessageBoxOK( BuildErrStr(MSG_SENDMAIL_SUCCESS), szMessageBoxTitle );
        }
    }
    else if (nSend == FALSE)
    {
        /* User cancelled out of Send Dialog, or Domino and Notes error during
           dialog box initialization. No need for a message here.
         */
    }
    else if (nSend == -1)   /* Unable to create Send Dialog Box. */
    {
        MessageBoxOK( BuildErrStr(ERR_SENDMAIL_CANTCREATEDLG), szMessageBoxTitle );
    }
    return( status );
}

/****************************************************************************

    FUNCTION: SendDlgProc()

    PURPOSE:  Processes messages for "Sendmdlg" dialog box

    MESSAGES:

    SEND_BTN - Send button clicked
    CANCEL_BTN - Cancel button clicked

    COMMENTS:

        When user clicks the "Send" button, get contents of SendTo,
        CopyTo, Subject, and Body fields and save in global variables.
        Then close the dialog box and return TRUE.

        If the user clicks "Cancel", or selects Close Window from the
        System menu, or presses Escape, close the dialog box and return
        FALSE.

****************************************************************************/

Boolean SendDialogProc( DialogPtr d, EventRecord *event, short * item )
{
   Handle      theHdl;
   short    theType;
   Rect     theRect;
   Str255      tempPStr;
   char     *strPtr;
   short    i;
   Point    mPt;


   if ( event->what != mouseDown ) return( FALSE );
   
   mPt = event->where;
   GlobalToLocal(&mPt);
   i = FindDialogItem( d, mPt );   /* ... so mPt is in local coords */

    switch ( i+1 )
    {
      case SEND_BTN:
      {   /* "Send" button clicked */
         /* get SendTo string from Control */
         GetDialogItem( d, SENDTO_ITEM, &theType, &theHdl, &theRect );
         GetDialogItemText( theHdl, tempPStr );
         strPtr = PtoCstr( tempPStr );
         strcpy( szSendTo, strPtr );
         

         /* get CopyTo string from Control */
         GetDialogItem( d, COPYTO_ITEM, &theType, &theHdl, &theRect );
         GetDialogItemText( theHdl, tempPStr );
         strPtr = PtoCstr( tempPStr );
         strcpy( szCopyTo, strPtr );
         
         /* get Subject string from Control */
         GetDialogItem( d, SUBJECT_ITEM, &theType, &theHdl, &theRect );
         GetDialogItemText( theHdl, tempPStr );
         strPtr = PtoCstr( tempPStr );
         strcpy( szSubject, strPtr );

         /* get Body string from Control */
         GetDialogItem( d, BODY_ITEM, &theType, &theHdl, &theRect );
         GetDialogItemText( theHdl, tempPStr );
         wBodyLen = tempPStr[0];
		 strPtr = PtoCstr( tempPStr );
		 theBody = NewHandle( wBodyLen );
		 /* szbody is a global used in Sendmail */
		 HLockHi( theBody );
		 szBody = *theBody;
         strcpy( szBody, strPtr );


         ConvertNewlinesToNulls(szBody, wBodyLen);

         /* Finished getting user input. Close dialog box. */
         *item = SEND_BTN;
         return(TRUE);
      }
      
      case CANCEL_BTN:
         *item = CANCEL_BTN;
         return(TRUE);

      default:
         return(FALSE); /* Didn't process a message */
    }
}


void MessageBoxOK( char * errorString, char * boxTitle )
{
   DialogPtr   d;
   short    itemHit;
   
   
   d = GetNewDialog ( 128, nil, (WindowPtr) -1);
   if ( !d ) return ;
   SetWTitle( d, *(Str255*)CtoPstr( boxTitle ) );
   ParamText( *(Str255*)CtoPstr( errorString ), nil, nil, nil );  
   ShowWindow( d );
   
   itemHit = 0;
   while ( itemHit != OK )
   {
      ModalDialog( nil, &itemHit );
   }
   DisposeDialog(d);
   return;
   
}


short MessageBoxOKCancel( char * errorString, char * boxTitle )
{
   DialogPtr   d;
   short    itemHit;
   
   
   d = GetNewDialog ( 129, nil, (WindowPtr) -1);
   if ( !d ) return( resNotFound );
   SetWTitle( d, *(Str255*)CtoPstr( boxTitle ) );
   ParamText( *(Str255*)CtoPstr( errorString ), nil, nil, nil );  
   ShowWindow( d );
   
   itemHit = 0;
   while ( (itemHit != OK) && (itemHit != Cancel) )
   {
      ModalDialog( nil, &itemHit );
   }
   DisposeDialog(d);
   
   return( itemHit );
   
}

