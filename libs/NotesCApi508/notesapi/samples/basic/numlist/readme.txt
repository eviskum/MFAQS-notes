(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
numlist - Creates a number list field.


PURPOSE
-------
This program demonstrates how to create a number list field.  It creates 
a new note in the target database and appends text fields FORM and 
PLAIN_TEXT to the new note. Appends a number list field NUMBER to the 
note with the following values:  1,3,9703.4,-7,0.11592. 


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
numlist.c    - Main source code file for the program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING numlist
---------------
- Under OS/2, Windows 32-bit or UNIX (AIX, HP-UX, Linux
  and Solaris), type the following at the system command prompt:
  
       numlist <database filename>
                or
       numlist

  where <database filename> is the filename of the Domino database where
  the new document is created.  Use a target database that has a form
  named "SimpleDataForm" containing a text field named PLAIN_TEXT and a
  number list field named NUMBER.  The Number List Test database included
  with the API toolkit (file numlist.nsf) is appropriate.

  If the database filename is not specified, the program will prompt for it.


CHECKING THE RESULTS
--------------------
From Notes, open the "Number List Test" database.
Open the document with text "Created by sample NUMLIST.". Verify the
NUMBER field contains the values {1,3,9703.4,-7,0.11592}.
