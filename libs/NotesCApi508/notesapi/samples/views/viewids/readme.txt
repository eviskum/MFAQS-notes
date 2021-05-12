(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
viewids - Gets the Note ID of each note in a view.


PURPOSE
-------
This program opens the view note for the specified view, then opens the
collection corresponding to that view. Next, it reads all the entries in 
the collection, obtaining the note IDs of all the notes in the view. It
prints out all the note IDs.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
IBM AIX
IBM S/390
Power Macintosh
Linux RedHat

FILES
-----
viewids.c    - Main program.
mswin32.mak  - Make file for Windows 32-bit.
os2_32.mak   - Make file for OS/2 (32-bit).
hp.mak       - Make file for HP HP-UX.
sol_2x.mak   - Make file for Solaris SPARC Edition.
sol_x86.mak  - Make file for Solaris Intel Edition.
aix.mak      - Make file for IBM AIX.
os390.mak    - Make file for IBM S/390.
linux.mak    - Make file for Linux RedHat.
readme.txt   - This file. Specifies what is needed to use this example.


RUNNING viewids
---------------
This sample program will run against the Domino database simple.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  You must copy 
this file to the Domino or Notes data directory before running this program.

- Under OS/2, Windows 32-bit or UNIX (Solaris, AIX, HP-UX, Linux 
  or S/390) type:

  viewids

  at the system command prompt.

- On the Macintosh, double click on the application in the Finder.

The viewids sample will print out a count and the note ID for each note in the 
view "SimpleDataView".

