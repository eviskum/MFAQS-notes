(c) 1996-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
viewnav - Notes C++ API sample program that navigates a view and outputs
the contents of the Subject item in each document in the view.


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
viewnav.cpp  - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

view.nsf     - Sample Notes database (in NOTEDATA directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING viewnav
---------------
This sample program is designed to work with the sample database 
view.nsf in the notescpp\notedata directory.  Copy this database to your 
Notes data directory.

To run this program, type 'viewnav' at the system command prompt,
followed by the Notes pathname of the database, and (optionally) the
name of the server.

For example, assuming VIEW.NSF has been copied to your Notes data directory,
the command line for viewnav is:

	viewnav view.nsf


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
This sample displays information about the entries in the All Documents view
in the specified database (view.nsf). To determine that the sample worked
correctly, open the All Documents view in the database and verify that the
sample output matches the view entries.
