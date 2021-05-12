(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
hotspot - Example Lotus C API for Domino and Notes Program. Shows how to 
create popups, buttons, collapsible sections, action items, URLs and file 
attachments in a rich text field in a note.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt  -  This file. Specifies what is needed to use this example.

hotspot.c   -  Main program.

cdrecord.c  -  Contains some subroutines used by the main program.

hotspot.h   -  Header file for this program.

mswin32.mak  - Makefile for Windows 32-bit.

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.


RUNNING hotspot:
----------------
First, ensure the variable "szSourceFileName" in the "InsertFile" function in
the file hotspot.c specifies the fully-qualified path to the input file
"readme.txt" (or some other valid file on your disk), which is
supplied with this sample. If "szSourceFileName" does not correctly identify
the location of the file, either copy the file to the location specified
by szSourceFileName, or edit szSourceFileName appropriately and rebuild the
program.

Next, modify the "ToInfo" value in the "InsertAction" function in the file
hotspot.c to be an appropriate e-mail address.

And finally ensure that the database makeform.nsf resides in your Domino
or Notes data directory.


- Under Windows 32-bit or UNIX (AIX, HP-UX, Linux and Solaris),
  at the system prompt type:

        hotspot

  The program takes no arguments.



The program will create a document in the database makeform.nsf. Contained
in the new document's rich text field will be a popup, a button, a 
collapsible section, an action that sends a message, a URL, and a 
file attachment.


CHECKING THE RESULT
-------------------
After running the hotspot program, open the database makeform.nsf and 
display the document that was just created.  The "Body" field will 
contain a popup, a collapsible section, a button, an action, a URL, and 
a file attachment.

Clicking on the "Click Here" popup will cause the following text to be
displayed:

   "This is the text of the popup"

Clicking on the "Print..." button will cause the formula 
"@Command([FilePrint]) to be executed, causing the "File\Print" 
dialog box to be displayed.

Clicking on the "This is my section title" collapsible section will 
cause the text associated with the section to be displayed. You will 
see "This is text in my section" displayed.

Clicking on the "This is an action that sends a message" action section 
will cause a mail message to be sent to the user specified in the 
hotspot.c source.

Clicking on the URL "http://www.lotus.com" will cause the specific Web site 
to be displayed.

Clicking on the file attachment "readme.txt" will display the Properties 
InfoBox for the file attachment.
