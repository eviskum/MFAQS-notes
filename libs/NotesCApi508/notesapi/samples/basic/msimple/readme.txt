(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
msimple - Modify a field of all documents in a database.


PURPOSE      
-------
This program finds all the documents in a database that contain a numeric 
field called "NUMBER", and adds one to the value in that field in all 
documents.


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
msimple.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.
 
os2_32.mak   - Make file for OS/2 (32-bit).

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING msimple
---------------
- Under OS/2, Windows 32-bit or UNIX (Solaris, AIX, Linux and HP-UX),
  type the following at the system command prompt:
  
        msimple  <database filename>       
                  or
        msimple

  where:
  <database filename> is the filename of the Domino database to be modified.
  If the database filename is not specified, the program will prompt for it.


NOTE:  This program searches for documents with the numeric field "NUMBER".  
In order to perform a valid test, you should run msimple against a 
database, like simple.nsf, that contains documents where this field 
is present.

