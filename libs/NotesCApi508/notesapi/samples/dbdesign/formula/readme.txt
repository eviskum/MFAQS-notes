(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
formula - Evaluate a formula, return a value.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
HP HP-UX
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
formula.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

hp.mak       _ Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING formula
---------------
This sample program will run against the Domino database, "Formula Evaluation 
Test Database", filename, formula.nsf, provided with the Lotus C API for
Domino and Notes toolkit.  You must copy this file to the Domino or Notes
data directory before running formula.

- Under OS/2, Windows 32-bit or UNIX (Solaris, AIX, Linux, and HP-UX),
  type:
      formula
  at the system prompt.
  The program takes no arguments.


This program creates a note containing a number field in the specified 
database, saves the note, and then runs a formula against the newly 
created note.  The formula simply returns the value of the number 
stored in the number field.
   
The program then displays the number value contained in the number 
field in the note.        
 
To check the results of this program, from Notes, add the icon for the 
test database to your desktop.  Open this database, then open the 
document that was just created.  Compare the value stored in the 
Number field to the value that was displayed as output from the program.


