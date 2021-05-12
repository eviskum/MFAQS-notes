(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
dumpfont - Locate and print out the font tables in all data notes.


PURPOSE:
-------
This program demonstrates the use of ODSReadMemory to convert a font
table from canonical format to host format. After converting to host
format, the contents of the font table is printed out to the screen.


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
readme.txt   - This file. Specifies what is needed to use this example.

dumpfont.c   - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.


RUNNING dumpfont
----------------
This program opens the Domino database richtext.nsf. The API kit provides
this database in the notedata directory. You must copy this file to the 
Domino or Notes data directory before running dumpfont.

- Under OS/2, Windows NT, Windows 95/98, or UNIX (AIX, HP-UX, Linux 
  and Solaris), type the following at the system prompt:

    dumpfont
  The program takes no arguments.


When the program runs correctly, it displays something like this:

Processing note 212A.
    Font 0:
       Face    = 5
       Family  = 34
       Name    = MS Sans Serif
    Font 1:
       Face    = 6
       Family  = 82
       Name    = Symbol
    Font 2:
       Face    = 7
       Family  = 34
       Name    = System
