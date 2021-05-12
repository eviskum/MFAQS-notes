/*
        File:           SENDMAIL.R

        Purpose:        Resources needed by the sample application, sendmail.

*/



#include "SysTypes.r"
#include "Types.r"

/* FROM GLOBERR.H */
#define PKG_ADDIN               0x3300

#include "sendmerr.h"

/*
include "sendmail.rsrc";
*/

resource 'vers' (1) {
        0x01, 0x00, beta, 0x00,
        verUS,
        "1.0§0",
        "1.0§0, 1996 Copyright Lotus Development Corporation"
};

#if FALSE

/* here is the quintessential MultiFinder friendliness device, the SIZE resource */

resource 'SIZE' (-1) {
        dontSaveScreen,
        acceptSuspendResumeEvents,
        enableOptionSwitch,
        canBackground,                       /* we can background; we don't currently, but our sleep value */
                                             /* guarantees we don't hog the Mac while we are in the background */
        multiFinderAware,                    /* this says we do our own activate/deactivate; don't fake us out */
        backgroundAndForeground,             /* this is definitely not a background-only application! */
        dontGetFrontClicks,                  /* change this is if you want "do first click" behavior like the Finder */
        ignoreChildDiedEvents,               /* essentially, I'm not a debugger (sub-launching) */
        is32BitCompatible,                   /* this app should not be run in 32-bit address space */
        reserved,
        reserved,
        reserved,
        reserved,
        reserved,
        reserved,
        reserved,
        1024 * 1024 * 2,
        1024 * 1024 * 2 
};
#endif
resource 'DITL' (129, "MessageBox-OKCancel") {
        {       /* array DITLarray: 4 elements */
                /* [1] */
                {93, 188, 113, 246},
                Button {
                        enabled,
                        "OK"
                },
                /* [2] */
                {93, 267, 113, 325},
                Button {
                        enabled,
                        "Cancel"
                },
                /* [3] */
                {4, 10, 36, 42},
                Icon {
                        disabled,
                        1
                },
                /* [4] */
                {5, 50, 86, 330},
                StaticText {
                        disabled,
                        "^0"
                }
        }
};

resource 'DITL' (130) {
        {       /* array DITLarray: 14 elements */
                /* [1] */
                {34, 352, 52, 425},
                Button {
                        enabled,
                        "Send"
                },
                /* [2] */
                {59, 352, 77, 425},
                Button {
                        enabled,
                        "Cancel"
                },
                /* [3] */
                {37, 81, 53, 332},
                EditText {
                        enabled,
                        ""
                },
                /* [4] */
                {61, 81, 77, 332},
                EditText {
                        enabled,
                        ""
                },
                /* [5] */
                {85, 81, 101, 332},
                EditText {
                        enabled,
                        ""
                },
                /* [6] */
                {111, 81, 127, 332},
                EditText {
                        enabled,
                        ""
                },
                /* [7] */
                {138, 81, 154, 425},
                EditText {
                        enabled,
                        ""
                },
                /* [8] */
                {164, 10, 268, 425},
                EditText {
                        enabled,
                        ""
                },
                /* [9] */
                {37, 11, 53, 71},
                StaticText {
                        disabled,
                        "To:"
                },
                /* [10] */
                {61, 11, 77, 71},
                StaticText {
                        disabled,
                        "Cc:"
                },
                /* [11] */
                {85, 11, 101, 71},
                StaticText {
                        disabled,
                        "From:"
                },
                /* [12] */
                {111, 11, 127, 71},
                StaticText {
                        disabled,
                        "Date:"
                },
                /* [13] */
                {138, 9, 154, 69},
                StaticText {
                        disabled,
                        "Subject:"
                },
                /* [14] */
                {7, 194, 25, 242},
                StaticText {
                        disabled,
                        "MEMO"
                }
        }
};

resource 'DITL' (128, "MessageBox-OK") {
        {       /* array DITLarray: 3 elements */
                /* [1] */
                {95, 274, 115, 332},
                Button {
                        enabled,
                        "OK"
                },
                /* [2] */
                {4, 10, 36, 42},
                Icon {
                        disabled,
                        1
                },
                /* [3] */
                {5, 50, 86, 330},
                StaticText {
                        disabled,
                        "^0"
                }
        }
};

resource 'DLOG' (128, "MessageBox-OK") {
        {51, 20, 176, 365},
        movableDBoxProc,
        visible,
        noGoAway,
        0x0,
        128,
        "",
        centerMainScreen
};

resource 'DLOG' (129, "MessageBox-OKCancel") {
        {51, 20, 176, 365},
        movableDBoxProc,
        visible,
        goAway,
        0x0,
        129,
        "",
        centerMainScreen
};

resource 'DLOG' (130, "Send Notes Mail Dialog") {
        {40, 40, 328, 476},
        documentProc,
        invisible,
        goAway,
        0x0,
        130,
        "Send Notes Mail",
        centerMainScreen
};


resource 'STR ' (SENDMAIL_NAME) { "Notes Send Mail Sample" };
resource 'STR ' (SENDMAIL_VERSION) { "Version 1.0" };
resource 'STR ' (ERR_SENDMAIL_CANTINIT) { "Unable to Initialize Notes" };
resource 'STR ' (MSG_SENDMAIL_SUCCESS)  { "Successfully sent Notes mail."};
resource 'STR ' (ERR_SENDMAIL_CANTCREATEDLG)  { "Unable to create Send Dialog Box"};
resource 'STR ' (ERR_SENDMAIL_USERNAME)  { "Unable to get user name"};
resource 'STR ' (ERR_SENDMAIL_INITDATE)  { "Unable to initialize date field"};
resource 'STR ' (ERR_SENDMAIL_SERVERNAME)  { "Unable to get mail server name"};
resource 'STR ' (ERR_SENDMAIL_MAILFILENAME)  { "Unable to get mail file name"};
resource 'STR ' (ERR_SENDMAIL_CANTOPENMAILFILE)  { "Unable to open user's Notes mail file"};
resource 'STR ' (ERR_SENDMAIL_CANTCREATEMEMO)  { "Unable to create memo in mail file"};
resource 'STR ' (ERR_SENDMAIL_CANTALLOCATELIST)  { "Unable to allocate list"};
resource 'STR ' (ERR_SENDMAIL_CANTADDTOSENDLIST)  { "Unable to add name to SendTo list"};
resource 'STR ' (ERR_SENDMAIL_CANTADDTORECIPLIST)  { "Unable to add name to Recipients list"};
resource 'STR ' (ERR_SENDMAIL_CANTADDTOCOPYLIST)  { "Unable to add name to CopyTo list"};
resource 'STR ' (ERR_SENDMAIL_NORECIPIENTS)  { "Mail memo has no recipients."};
resource 'STR ' (ERR_SENDMAIL_CANTSETRECIPIENT)  { "Unable to set Recipient item in memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETSENDTO)  { "Unable to set SendTo item in memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETCOPYTO)  { "Unable to set CopyTo item in memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETFORM)  { "Unable to set Form item in memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETFROM)  { "Unable to set From item in memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETSUBJECT)  { "Unable to set Subject item in memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETPRIORITY)  { "Unable to set Delivery Priority item in memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETREPT)  { "Unable to set Delivery Report into memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETCOMPDATE)  { "Unable to set Composed Date in memo"};
resource 'STR ' (ERR_SENDMAIL_CANTCREATEBODY)  { "Unable to create body item in message"};
resource 'STR ' (ERR_SENDMAIL_CANTAPPENDBODYLINE)  { "Unable to append text to body"};
resource 'STR ' (ERR_SENDMAIL_CANTADDBODY)  { "Unable to add Body item to memo"};
resource 'STR ' (ERR_SENDMAIL_CANTSETPOSTDATE)  { "Unable to set Posted Date in memo"};
resource 'STR ' (MSG_SENDMAIL_ASKUSELOCAL)  { "Unable to reach Mail Server.\nSave in local MAIL.BOX?"};
resource 'STR ' (ERR_SENDMAIL_CANTTRANSFER)  { "Unable to transfer message to local mail box"};
resource 'STR ' (ERR_SENDMAIL_CANTOPENMAILBOX)  { "Unable to open mail box on server"};
resource 'STR ' (ERR_SENDMAIL_CANTGENOID)  { "Unable to generate originator ID for mail box"};
resource 'STR ' (ERR_SENDMAIL_CANTUPDATEFILE)  { "Unable to update message in local mail file"};
resource 'STR ' (ERR_SENDMAIL_CANTUPDATEBOX)  { "Unable to update message to router mail box"};
resource 'STR ' (ERR_SENDMAIL_CANTCLOSE)  { "Unable to close memo"};
resource 'STR ' (ERR_SENDMAIL_CANTCLOSEFILE)  { "Unable to close mail file"};


