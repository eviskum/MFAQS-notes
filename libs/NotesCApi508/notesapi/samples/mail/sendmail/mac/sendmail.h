/***************************************************************************

     SENDMAIL.H

***************************************************************************/
#include <Strings.h>                 /* strtok() */
#include <string.h>                 /* strtok() */
#include <ctype.h>                  /* isspace() */

#include <MacWindows.h>
#include <Resources.h>
#include <Fonts.h>
#include <Dialogs.h>
#include <Errors.h>
#include <QuickDraw.h>
#include <Menus.h>
#include <ToolUtils.h>

#include <Quickdraw.h>
#include <Dialogs.h>

#include <Types.h>
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
#include <clerr.h>							 /* ERR_SERVER_NOT_RESPONDING */

#include <lapiplat.h> 

#define Cancel       cancel
#define OK           ok
#define SENDTO_ITEM     Cancel+1
#define COPYTO_ITEM     Cancel+2
#define FROM_ITEM       Cancel+3
#define DATE_ITEM    Cancel+4
#define SUBJECT_ITEM Cancel+5
#define BODY_ITEM    Cancel+6
#define SEND_BTN     OK
#define CANCEL_BTN      Cancel

#define TITLE_LEN       30
#define ERR_STR_LEN     256


typedef  char  CString[512];


#define szMessageBoxTitle "Notes Send Mail Sample"


/****************************************************************************

   FUNCTION PROTOTYPES
   
****************************************************************************/
STATUS SendMail( void );


/* PLATFORM SPECIFIC FUNCTIONS */
short MessageBoxOKCancel( char * errorString, char * boxTitle );
void MessageBoxOK( char * errorString, char * boxTitle );
OSErr SendMailMainProc( void );
Boolean SendDialogProc( DialogPtr d, EventRecord *event, short * item );
char * BuildErrStr (STATUS error);
void ConvertNewlinesToNulls(char * szBody, WORD wBodyLen);
