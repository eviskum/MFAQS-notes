(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
readform - Sample Lotus C API for Domino and Notes Program: 
           shows how to read a Form note


PURPOSE
-------
This program reads the specified form note, displays a list of the
fields on the form and the datatypes of those fields.


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

readform.c   - Main program
readform.h   - Function prototypes and symbolic constants

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.


RUNNING readform
----------------
This sample program will run against the Domino database readform.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  You must copy 
this file to the Domino or Notes data directory before running this program.

- Under OS/2, Windows NT, Windows 95/98, or UNIX (AIX, HP-UX, Linux 
  and Solaris), type the following at the system command prompt:

  readform

