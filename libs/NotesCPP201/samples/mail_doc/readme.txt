(c) 1997, 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
MAIL_DOC - Introductory Notes C++ API program that opens Notes documents
containing a rich text "Body" field and searches for a text string 
in each Body field. If the text string is found, the program mails the 
document to a recipient specified by the user.

This program shows how to use an LNRTCursor object to search stylized text 
in a rich text field. It also shows how to use LNDocument::MailTo to mail 
a Notes document.


ENVIRONMENTS
------------
We provide sample makefiles for the following environments:

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC
	Sun Solaris Intel Edition

The following environments rely on an Integrated Development Environment
(IDE) and do not require makefiles:

	MacOS (7.x) Power PC

Note that this sample does not currently support 16-bit Windows.


FILES
-----
mail_doc.cpp  - Main program.

mail_doc.cpp  - Include file for main program.

dumpme.nsf    - Notes database file that contains the documents to search
                (in NOTEDATA directory).

mswin32.mak   - Make file for Windows NT (32-bit, including DEC Alpha) and
                Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak  - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
                IBM VisualAge C++ for Windows.

borwin32.mak  - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
                Borland C++ 5.0 for Windows.

os2_32.mak    - Make file OS/2 (32-bit).

os390.mak     - Make file for OS/390.

hp.mak        - Make file for HP-UX.

sol_2x.mak    - Make file for SUN Solaris SPARC platform.

sol_x86.mak   - Make file for Sun Solaris Intel Edition platform.

aix.mak       - Make file for IBM AIX.

readme.txt    - This file.


RUNNING MAIL_DOC
----------------
- OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  At the system command prompt, type 'mail_doc' and optional command 
  arguments.

- Macintosh: double-click the program icon.

This sample program can run against any Notes database. The program prompts
you for the following:

Source Database [dumpme.nsf]      
Must have at least one document that contains a rich text "Body" field.

Source Server Path
To use the local server, specify a null string ("").

Search String
A string contained in at least one rich text "Body" field of at least one
document in the database.

User-Name
The e-mail address of a recipient for the found documents.
This must be a valid user name in order for the mail router to find the
recipient.

You can also supply the above information as command line arguments to the 
executable. If you provide command line arguments, enclose any input strings 
containing spaces in quotes. If you provide no arguments or incomplete 
arguments, the program prompts you for them. 

For your convenience, we have provided a sample source database, dumpme.nsf. 
If you place this file in your Notes data directory, you can accept 
all defaults, other than User-Name, when the program prompts you.


CHECKING THE RESULTS
--------------------
To see if the program worked, have the User-Name recipient you specified 
check his/her incoming e-mail for any documents found by the program.

