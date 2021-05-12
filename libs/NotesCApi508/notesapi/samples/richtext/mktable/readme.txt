(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
mktable - Sample Lotus C API for Domino and Notes program: 
          shows how to make tables in rich text fields.

ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

mktable.c    - Main program.
cdrecord.c   - A collection of buffer definition and creation routines.
cdtable.c    - A collection of richtext field table creation routines.
mktable.h    - Header file  for this sample.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.


RUNNING mktable
---------------
- Under Windows 32-bit, OS/2 or UNIX (AIX, HP-UX, Linux and Solaris),
  type the following at the system command prompt:

  mktable [<database>]

where:

  <database> is the filename of the Domino database to operate on.
  If this argument is omitted, the program will prompt for it.
  For testing, you should use the "Test of Tables" database, tabletst.nsf,
  included with the Lotus C API for Domino and Notes toolkit.


EXAMPLE
-------

  mktable tabletst


CHECKING THE RESULTS
--------------------
To see if mktable worked correctly:

  Open the Test of Tables database (tabletst.nsf).

  Open the newly created document.  You should see a brief paragraph
  followed by three different tables.
