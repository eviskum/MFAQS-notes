(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
intro - Introductory Lotus C API for Domino and Notes program that opens 
a Domino database and displays the database title.


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
IBM AS/400
LInux ReadHat


FILES
-----
intro.c      - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

os390.mak    - Make file for IBM S/390.

as4intmk.bat - Batch file for IBM AS/400 using Visual Age C++.

as400.mak    - Make file for IBM AS/400 using Visual Age C++.

mk_intro.clp - Make file for IBM AS/400 using the native C compiler.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING intro:
----------------
This sample program will run against the Domino database intro.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  You must 
copy this file to the Domino or Notes data directory before running
this program.

- Under OS/2, Windows 32-bit and UNIX (Solaris, AIX, S/390, Linux 
  or HP-UX): type 'intro' at the system command prompt.

- On the Macintosh, double click on the application in the Finder.

- Under AS/400, type 
	'rundomcmd/rundomcmd server(<servername>) cmd(call pgm(qntcsdk/intro))
	 batch(*no)'

The program should display the Lotus C API for Domino and Notes release
number followed by:

      The title for the database intro.nsf is...

      API Test Database (intro)


EXAMINING THE DOMINO DATABASE TO CHECK THE RESULT:
------------------------------------------------

To see if 'intro' worked correctly:

      Use Notes to open intro.nsf

      Choose File/Database/Properties...

      You should see the same database title as displayed by
      'intro'.

