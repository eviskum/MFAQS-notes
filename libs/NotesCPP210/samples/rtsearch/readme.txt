(c) 1996-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
rtsearch - Notes C++ API sample program that searches for and replaces
a text string in a rich text item.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Windows NT (32-bit)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition
        Linux on Intel platforms


FILES
-----
rtsearch.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

rtsearch.nsf - Sample Notes database (in NOTEDATA directory).

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING rtsearch
----------------
This sample program is designed to work with the sample database 
RTSEARCH.NSF, in the notescpp\notedata directory.  Copy this database to your 
Notes data directory.  You must supply command-line parameters to specify
the file pathname and, optionally, the server for the database.

To run this program, type 'rtsearch' at the system command prompt,
followed by the Notes pathname of the database, and (optionally) the
name of the server.

For example, assuming RTSEARCH.NSF has been copied to your Notes data 
directory, the command line for rtsearch is:

	rtsearch rtsearch


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if rtsearch worked correctly:

      1. Before running rtsearch, use Notes to open RTSEARCH.NSF
      2. Open one of the documents and verify that it contains the string 
         "Cplusplus".
      3. Close RTSEARCH.NSF.
      4. Run rtsearch.
      5. Re-open RTSEARCH.NSF.
      6. Open one of the documents and verify that the string "Cplusplus" 
         has been replaced with "C++".
