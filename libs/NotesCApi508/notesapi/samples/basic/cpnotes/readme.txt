(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
cpnotes - Selectively copies notes from one database to another.


PURPOSE
-------
This program shows how to selectively copy notes from one database to
another. The selections are based on the kinds of note and their modification
times. The code shows much of the API's time/date handling.


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
cpnotes.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux Redhat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING cpnotes
---------------
- Under OS/2, Windows 32-bit or UNIX (AIX, HP-UX, Linux
  and Solaris), type the following at the system command prompt:

        cpnotes <input db> <output db> <output title>
                  or
        cpnotes

  where:

  <input db> is the filename of the Domino database to be copied

  <output db> is the filename of the resulting copy of the Domino database

  <output title> is the title of the resulting Domino database

  If the command line arguments are not specified, the program will
  prompt for them.


NOTE:
This program assumes that the syntax for time/date strings on the
target computer is:

      mm/dd/yy  hh:mm       for non-OS/2 systems

      mm-dd-yy  hh:mm       for OS/2 systems


If your computer is set to a different time/date syntax, you can:

Edit the source code statement that contains the time/date string and 
change it to your computer's time/date format. (You must then re-compile
the program.)


EXAMPLE:
This example uses the Domino database, simple.nsf provided with the Lotus 
C API for Domino and Notes toolkit.  Copy this file to the Domino or Notes 
data directory.  You may also want to create a new document in this database
or modify an existing document to ensure there is at least one document in 
this database that is less than one month old.

      cpnotes  simple  simple2  "Partial Copy of Simple"


CHECKING THE RESULT
-------------------
To see if cpnotes worked correctly:

Open the new copy of the database.

Choose File/Database/Properties...

This should display the title specified on the command line.

Note that all the forms and views are copied into the new copy. The notes 
in the original database that are less than a month old will all have been 
copied into the copy, and the Notes Help document will only have been 
copied if it has been modified since January 1, 1996.
