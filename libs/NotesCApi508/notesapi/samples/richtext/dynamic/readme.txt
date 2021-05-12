(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
dynamic - Fill a RichText Field


PURPOSE
-------
This program shows how to create a rich text field by dynamically 
allocating a buffer, filling the buffer with CD records converted to 
Domino canonical format, and appending the buffer to a note as a 
rich-text field.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Power Macintosh
Linux RedHat

FILES
-----
dynamic.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING dynamic
---------------
This program opens the Domino database richtext.nsf. The C API kit provides
this database in the notedata directory. You must copy this file to the 
Domino or Notes data directory before running dynamic.

- Under OS/2, Windows NT, Windows 95/98, or UNIX (AIX, HP-UX, Linux 
  and Solaris), type the following at the system command prompt:

        dynamic
        

- On the Macintosh double click on the application in the Finder.

  The program takes no arguments.


CHECKING THE RESULTS
--------------------
Open the target database using Notes.

Double-click on the newly created document in order to read it. 
The text should say:

"Hello World...   So long world".

