(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
wsimple - Write Simple Data Types


PURPOSE      
-------
This program creates a note in a Domino database and writes simple data 
(text, number, text list, and time/date) in the appropriate fields.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
HP HP-UX
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
Power Macintosh
Linux RedHat


FILES
-----
wsimple.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

aix.mak      - Makefile for IBM AIX.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING wsimple
---------------

This sample program will run against the Domino database simple.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  You must copy 
this file to the Domino or Notes data directory before running this program.

- Under OS/2, Windows 32-bit, or UNIX (Solaris, AIX, Linux, and HP-UX),
  type:
       wsimple
  at the system command prompt.


- On the Macintosh double click on the application in the Finder.

This program will create a note in the database simple.nsf
containing data of types text, number, text list, and time/date.


EXAMINING THE DOMINO DATABASE TO SEE THE CHANGED DOCUMENTS:
---------------------------------------------------------
To see if wsimple worked correctly:

Open simple.nsf.

A new document will be displayed in the main view.  Open the document
and confirm that it contains data of types text, number, text list, and
time/date. 
