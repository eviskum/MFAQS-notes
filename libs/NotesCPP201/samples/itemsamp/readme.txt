(c) 1996-1998 Lotus Development Corporation.  All rights reserved.
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

        Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	SUN Solaris SPARC
	X86 Solaris Intel Edition

The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++

This sample does not currently support the Macintosh.


FILES
-----
itemsamp.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

itemsamp.def - Module definition (.def) file for 16-bit Borland C++ for Windows.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ 5.0 32 bit compiler for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING itemsamp
---------------
This sample program will run against any Notes database. You must
supply command-line parameters to specify the file pathname and,
optionally, server for the database.

- Under Windows 16-bit:  choose File Run from the Program Manager menu, 
  type in the full path and filename of this program, the Notes pathname
  of the desired database, and optionally the name of the server, and
  press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  type 'itemsamp' at the system command prompt, followed by the Notes
  pathname of the desired database, and optionally the name of the
  server.

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
Size = 348

Item Number = 4   
Name = $UpdatedBy   
Size = 36
