(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C API Software Development
Kit Agreement (in the apilicns.txt file in the notesapi directory of
this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
--------
sendmail -  Send a Notes Mail Message using the Notes Mail Gateway API
            functions.


ENVIRONMENTS
------------
Windows NT (32-bit)
Windows 95/98 (32-bit)


FILES
-----
readme.txt    - This file.

sendmail.c    - Main program.

sendmail.h    - Program defines, control IDs, and function prototypes.

mswin32.mak   - Make file for Windows 32-bit.


OPERATING ENVIRONMENT REQUIREMENTS
----------------------------------

RUNNING sendmail
----------------
- To start to program, type:

       sendmail

  at the system command prompt.  The program will prompt for the
  following inputs.  For each input below, enter a string and
  press carriage return.

  SendTo <User Name to send Mail to, User Name to send Mail to, etc.>
  CopyTo <User Name to Copy to, User Name to Copy to, etc.>
  Subject <Mail Message Subject Name>
  Body    <Body of Mail Message - Maximum length 1024 characters>

  Note: Enter a comma to separate multiple User names.
