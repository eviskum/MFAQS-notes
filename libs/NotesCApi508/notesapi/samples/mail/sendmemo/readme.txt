(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software
Development Kit Agreement (in the apilicns.txt file in the notesapi directory
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
sendmemo - Sends a Domino memo using NSF functions


ENVIRONMENTS
------------
Windows NT (32-bit)
Windows 95/98 (32-bit)


PURPOSE
-------
This program shows how to create and send a simple memo using only the NSF
family of API functions.  Alternative ways to access mail include the
Domino Mail Gateway family of functions and VIM.

This program sets the SendTo and the Recipients fields of the memo
to the SendTo value specified.  It also sets the Subject and Body according
to the command line.  The Composed Date is set to the current date and time,
and the Form field is set to "Memo".  The Delivery Priority is set to Normal,
the Delivery Report is set to basic, and the Return Receipt is set to No.
The SentTo value is not verified in the Address book. The memo is then placed
in the "mail.box" file on the mail server specified in the NOTES.INI file.


In the event of multiple "mail.box" files, if no mail server is
specified (local access), and the NOTES.INI parameter
"MAIL_ENABLE_MAILBOX_COMPATIBILITY =1" is set, then the memo is put in the
local "mail.box" file.  If no mail server is specified, and the NOTES.INI
parameter "MAIL_ENABLE_MAILBOX_COMPATIBILITY" is not set, the sample will
attempt to deposit the memo in the "mail2.box" file.

For more information on multiple "mail.box" files, please consult your
Domino documentation.



FILES
-----
readme.txt  - This file.
sendmemo.c  - Main C program.
mswin32.mak - Make file for Windows (32-bit).


RUNNING sendmemo
----------------
- At the command-line the syntax for this sample is:

      sendmemo  "SendTo"  "Subject"  "Body Text"

Only one recipient name may be specified, although this may be the name
of a group.


EXAMPLE
-------

     sendmemo  "Ernest Hemingway"  "Next novel"   "When are you
             going to finish that next novel?"


