(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
srch_all - Search for and process all documents in a database.


PURPOSE
-------
Demonstrates how to use NSFSearch to process all documents in a database 
without the risk of processing the same note more than once.  This ensures 
that each document gets processed once and only once by building an ID 
table that is guaranteed to contain exactly one instance of each note ID. 
Once the search is completed and the ID table is full, then the program 
iterates over IDs in the table and processes each note once.


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
Power Macintosh


FILES
-----
srch_all.c   - Main C source file for the program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Mkae file for Linux RedHat.

readme.txt   - This file. Describes what is needed to use this program.


RUNNING srch_all
----------------
Run this sample program with the srch_all.nsf Domino database provided
with the Lotus C API for Domino and Notes toolkit.  You must copy the 
srch_all.nsf file to the Domino or Notes data directory before running
this program.

From Notes, open the srch_all.nsf target database and familiarize 
yourself with the "categorized" view. Most documents appear in category
"p". A few appear in category "q". One appears in category "r".

Run the program:

- Under OS/2, Windows 32-bit or UNIX (AIX, HP-UX, Linux and Solaris),
  type the following at the system command prompt:

         srch_all  srch_all.nsf

- On the Macintosh, double click on the application in the Finder.
  When prompted, enter srch_all.nsf for the command line argument.

        

CHECKING THE RESULT
-------------------
Open the target database go to the "categorized" view. Press F9 to 
refresh the view if you left the database open while running srch_all.
Note that all documents previously in category "p" now have category "q", and 
all documents previously in category "q" now have category "r". All docs
previously in category "r" remain in category "r". 

You may repeat the test by running srch_all again. After the second round,
note that all documents are in category "r".

If you attempt to run this sample again, no further change will
occur. Reset the database srch_all.nsf using the agent, "ChangeCatToP". 
This macro automatically changes the category of all documents to "p". 

