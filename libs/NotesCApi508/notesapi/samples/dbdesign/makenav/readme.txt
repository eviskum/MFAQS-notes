(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
MAKENAV - Creates a custom navigator in a database.   This program creates
a Navigator view and/or object (ellipse graphic) that acts as a doclink 
to the first note created in the database today.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
HP HP-UX
IBM S/390
Linux RedHat


FILES
-----
makenav.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP-UX

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

os390.mak    - Make file for IBM S/390.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING MAKENAV
---------------
This program opens and updates the Domino database makenav.nsf. The API kit 
provides this database in the notedata directory. You must copy this file to
the Domino or Notes data directory before running this sample.

Before running this sample, you need to create a note in the database.
From the Notes Workstation, open the makenav sample database.  Use the 
Create-MainForm menu to create a new document. Type some text in the edit 
field, for example "This document was created today.", and save.  You will 
see the document added to the MainView view.

- Under OS/2, Windows 32-bit, or UNIX (AIX, HP-UX, Solaris, Linux,  
  and S/390), type:
       makenav
  at the system prompt. The program takes no arguments.


VERIFYING MAKENAV
-----------------
Upon successful program execution, you can verify the result as follows:
1. Open the makenav.nsf database
2. From the "File-Database-Properties..." menu, click the "Launch" tab 
   (rocket). 
3. From the pull down list for "When opened in the Notes client", 
      select "Open designated Navigator"
   Then, from the pull down list for "Type of Navigator:",
      select "Standard Navigator"
   Finally, at the pull down list for "Name:",
      select "Sample Navigator".
4. Close the Database Properties window, and close the database.
5. Re-open the makenav.nsf database, and
   you should see an ellipse that is labelled with today's date. 
   When you click this navigator, the (first) document created on that date 
   will be opened.

You can create more navigators to the Sample Navigator view by rerunning 
the MAKENAV sample. If a document does not exist for the current date, 
no additional navigators will be added.  This sample simulates an 
environment where the database is updated daily by a different program, 
and subsequent MAKENAV execution would dynamically add a navigator to 
link to that document.
