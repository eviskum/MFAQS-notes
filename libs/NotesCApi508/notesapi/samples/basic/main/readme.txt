(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
main - Displays the database title.


PURPOSE:       
--------      
This program is simple example of a "C" program with entry point main() 
that calls the Lotus C API for Domino and Notes functions. This program
takes, as input, the file name of a Domino database. It opens the Domino
database and displays the title. 

This program is similar to the sample program 'intro', except 'main' is 
implemented as a "C" main() routine, while 'intro' is implemented as a 
NotesMain() subroutine.


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
IBM AS/400
Linux RedHat


FILES:
------
main.c       - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.               

os390.mak    - Make file for IBM S/390.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

as4maimk.bat - Batch file for IBM AS/400 using Visual Age C++.

as400.mak    - Make file for IBM AS/400 using Visual Age C++.

mk_main.clp  - Make file for IBM AS/400 using the native C compiler.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


IDENTIFY A TEST DATABASE:
-------------------------

Determine the name of a Domino database file, such as intro.nsf, that
resides in the Domino or Notes data directory on your system. Main will
work with any valid Domino database file.


RUNNING main:
-------------

The command line of main is  -

      main <database filename>

where:

      <database filename> is the filename of the Domino database to read


EXAMPLE:

Under OS/2, Windows 32-bit, or UNIX (AIX, HP-UX, Solaris, Linux, or S/390), 
type:

      main  intro

Under AS/400 type:
	'rundomcmd/rundomcmd server(<server name>) cmd(call pgm(qntcsdk/main)
	 parm(intro.nsf)) batch(*no)'

If the program runs correctly, it should display

      The title for this database is...

      API Test Database (intro)


EXAMINING THE DOMINO DATABASE TO CHECK THE RESULT:
--------------------------------------------------

To see if 'main' worked correctly:

      Use Notes to open intro.nsf

      Choose File/Database/Properties...

      You should see the same database title as displayed by this sample.
      

