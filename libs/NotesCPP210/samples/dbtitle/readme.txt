(c) 1996-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
dbtitle - Introductory Notes C++ API program that opens a Notes database
and displays the database title.


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
	Sun Solaris SPARC
	Sun Solaris Intel Edition
        Linux on Intel platforms


FILES
-----
dbtitle.cpp  - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING dbtitle
---------------
This sample program will run against any Notes database.

To run this program, type 'dbtitle' at the system command prompt,
followed by the Notes pathname of the desired database, and optionally
the name of the server.

For example, the sample database richtext.nsf may be copied to the
user's Notes data directory.  The command line for dbtitle is:

	dbtitle richtext

The program should display:

	The database title is:  Rich-Text Test


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if dbtitle worked correctly:

Use Notes to open richtext.nsf

Choose File/Database/Properties...

You should see the same database title as displayed by
dbtitle.
