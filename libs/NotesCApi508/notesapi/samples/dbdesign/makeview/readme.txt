(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
makeview - Create a new view in a database.


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
makeview.c   - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 32-bit.

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING makeview
----------------
This program opens the Domino database makeview.nsf. The API kit provides
this database in the notedata directory. You must copy this file to the 
Domino or Notes data directory before running makeview.

- Under OS/2, Windows 32-bit, or UNIX (AIX, HP-UX, Linux and Solaris),
  type the following at the system command prompt:

       makeview
  The program takes no arguments.

To verify that the program ran successfully, use Notes to open the 
MakeView test database. The default view is "Simple View". The view
created by this sample program is "Test View".  Use the View menu
to select the Test View.

