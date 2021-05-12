(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
makeform - Create a new form, a subform, and a frameset in a database.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
IBM S/390
Power Macintosh
Linux RedHat

FILES
-----
makeform.c   - Main program.

cdrecord.c   - Contains several functions used by the main program.

makeform.h   - Function prototypes and symbolic constants.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 32-bit.

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

os390.mak    - Make file for IBM S/390.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.

lotus.gif    - gif image file.

domino.gif   - gif image file.


BEFORE RUNNING THIS SAMPLE
--------------------------
Make sure the two .gif files have read/write access. 


RUNNING makeform
----------------
This program opens the Domino database makeform.nsf. The API kit provides
this database in the notedata directory. You must copy this file to the 
Domino or Notes data directory before running makeform.

- Under OS/2, Windows 32-bit, or UNIX (AIX, HP-UX, Solaris, Linux, and 
  S/390), type:
        makeform
  at the system prompt. The program takes no arguments.

- On the Macintosh, double click on the application in the Finder.

In all environments, makeform creates a form called "Test Form 1",
a subform, and a frameset in the database makeform.nsf. The subform is inserted 
into the main form and contains the gif image "domino".  The frameset is launched
when the database is opened and contains a View frame and Document frame.

To verify that the program ran successfully, use Notes to open the 
MakeForm test database, and choose "Create".  The Create menu should
list a form called "Test Form 1".  After creating and saving the form,
verify when selecting from the View frame, the Document frame
shows the contents of the form that was just created.

