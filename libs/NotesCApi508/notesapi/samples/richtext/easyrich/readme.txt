(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
easyrich - Shows how to use CompoundText routines.


PURPOSE
-------
This program illustrates how to use the CompoundText routines to write 
to a rich text field. It demonstrates how to append text and paragraphs
with various styles to the rich text field. It demonstrates how to 
assimilate rich text from another document into the rich text field, 
it demonstrates how to create a Doc Link in the rich text field, and it
demonstrates how to add a rendered note to the Compound text.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat

FILES
-----
easyrich.c   - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING easyrich:
-----------------
This program opens the Domino database richtext.nsf. The C API kit provides
this database in the notedata directory. You must copy this file to the 
Domino or Notes data directory before running easyrich.

- Under OS/2, Windows NT, Windows 95/98, or UNIX (AIX, HP-UX, Linux 
  and Solaris), type the following at the system command prompt:

        easyrich
  The program takes no arguments.


CHECKING THE RESULTS
--------------------
Open the target database and the document that was just created.  
The RICH_TEXT field will contain the text strings added by the program 
in various colors, font types, and sizes.

There will also be a DocLink pointing to the first note in the view and
a rendered note that contains the first note's contents.

