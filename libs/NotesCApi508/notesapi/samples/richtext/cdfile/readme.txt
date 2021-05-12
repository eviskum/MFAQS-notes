(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
cdfwrite -  Write text as in Domino rich text format to a CD file.
cdfread  -  Read Domino rich text from a CD file into a document.


PURPOSE
-------
These programs illustrate how to use the CompoundText routines to write 
text to a CD file and read text from a CD file into a rich text field.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux Redhat


FILES
-----
cdfwrite.c  - Main file for cdfwrite program.
cdfread.c   - Main file for cdfread program.
cdfile.h    - Symbolic constant definitions.
mswin32.mak - Make file for Windows 32-bit.
os2_32.mak  - Make file for OS/2 (32-bit).
aix.mak     - Make file for IBM AIX.
hp.mak      - Make file for HP HP-UX.
sol_2x.mak  - Make file for Solaris SPARC Edition.
sol_x86.mak - Make file for Solaris Intel Edition.
linux.mak   - Make file for Linux RedHat.
readme.txt  - This file. Specifies what is needed to use this example.


RUNNING cdfwrite
----------------
- Under OS/2, Windows NT, Windows 95/98, or UNIX (AIX, HP-UX, 
  Linux and Solaris), type the following at the system command prompt:

       cdfwrite
        or
       cdfwrite "text to write"

The program will prompt for the text to be included in the rich text 
field or let the user enter the text on the command line.  It then 
creates a CD file with file name, cd_recs.inp, writes the specified 
text into the file as CD records.


RUNNING cdfread
---------------
This program opens the Domino database richtext.nsf. The C API kit provides
this database in the notedata directory. You must copy this file to the 
data directory before running cdfread.

- Under OS/2, Windows NT, or Windows 95/98: type the following at the 
  system command prompt:

       cdfread
  The program takes no arguments.

This program creates a new document in the database, richtext.nsf
and reads the rich text from the CD file, cd_recs.inp into the 
RICH_TEXT field of the new document. 

CHECKING THE RESULTS
--------------------
Open the richtext.nsf database and display the document that was just 
created.  The RICH_TEXT field will contain the specified string.

