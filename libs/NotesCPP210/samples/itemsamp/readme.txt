(c) 1996-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
itemsamp - Introductory Notes C++ API program that displays the name and
size of all the items in all the documents in a Notes database.


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
	SUN Solaris SPARC
	X86 Solaris Intel Edition
        Linux on Intel platforms


FILES
-----
itemsamp.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platforms.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING itemsamp
---------------
This sample program will run against any Notes database. You must
supply command-line parameters to specify the file pathname and,
optionally, server for the database.

To run this program, type 'itemsamp' at the system command prompt,
followed by the Notes pathname of the desired database, and optionally
the name of the server.

For example, the sample database richtext.nsf may be copied to the
your Notes data directory.  The command line for itemsamp is:

	itemsamp richtext

The program should display:

Document Number = 0

Item Number = 0   
Name = Form   
Size = 14

Item Number = 1   
Name = $Fonts   
Size = 110

Item Number = 2   
Name = time_date   
Size = 10

Item Number = 3   
Name = rich_text   
Size = 422

Item Number = 4   
Name = $Revisions   
Size = 22


Document Number = 1

Item Number = 0   
Name = Form   
Size = 14

Item Number = 1   
Name = $Fonts   
Size = 76

Item Number = 2   
Name = time_date   
Size = 10

Item Number = 3   
Name = rich_text   
Size = 346

Item Number = 4   
Name = $UpdatedBy   
Size = 36
