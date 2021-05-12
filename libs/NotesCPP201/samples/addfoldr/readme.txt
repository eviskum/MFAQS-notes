(c) 1996-1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
addfoldr - Notes C++ API sample program that creates new folders and 
copies documents into the new folders, based on the document subject.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition

The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++
	MacOS (7.x) Power PC


FILES
-----
addfoldr.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

addfoldr.def - Module definition (.def) file for 16-bit Borland C++ for Windows.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ 5.0 for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

view.nsf     - Sample Notes database (in NOTEDATA directory).
		
readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING addfoldr
----------------
This sample program is designed to work with the sample database 
VIEW.NSF, in the notescpp\notedata directory.  Copy this database to your 
Notes data directory.  On platforms other than Macintosh, you must supply 
command-line parameters to specify the file pathname and, optionally, the
server for the database.  On the Macintosh, you are prompted for the file 
pathname and the server name.

- Under Windows 16-bit:  Choose File - Run from the Program Manager menu, 
  type in the full path and filename of this program, the Notes pathname
  of the database, and (optionally) the name of the server, and
  press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  Type 'addfoldr' at the system command prompt, followed by the Notes
  pathname of the database, and (optionally) the name of the server.

- Under Macintosh:  Double-click the program icon.  The program prompts 
  for the database pathname and the optional server name.

For example, assuming VIEW.NSF has been copied to your Notes data directory,
the command line for addfoldr is:

	ADDFOLDR VIEW


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
addfoldr creates a folder for each quarter of the year (1stQuarter, 2ndQuarter,
and so on), and places documents in those folders based on the month specified
in the document's subject. To see if addfoldr worked correctly:

      1. Before running addfoldr, use Notes to open VIEW.NSF.
      2. Verify that the folders for each quarter do not exist.
      3. Close VIEW.NSF.
      4. Run addfoldr.
      5. Re-open VIEW.NSF.
      6. Verify that the new folders exist and that they contain the correct
         documents.
