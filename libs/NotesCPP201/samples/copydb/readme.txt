(c) 1996-1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
copydb - Introductory Notes C++ API program that opens a Notes database,
copies its contents to a new destination database, and sets the new
database title.  The destination database can be either a replica or
non-replica copy.


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
	Sun Solaris SPARC
	Sun Solaris Intel Edition


The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++
	MacOS (7.x) Power PC


FILES
-----
copydb.cpp   - Main program.

copydb.hpp   - Include file for main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and
               Windows 95 (32-bit) using Microsoft Visual C++.

copydb.def   - Module definition (.def) file for 16-bit Borland C++ for Windows.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ 5.0 for Windows.

os2_32.mak   - Make file OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING copydb
--------------
This sample program runs against any Notes database.  The user is prompted 
for the source and destination .nsf file path and server names, the
destination database title, and whether to create a replica or non-replica
copy.

- Under Windows 16-bit:  Choose File Run from the Program Manager menu, 
  type in the full path and filename of this program, and press <Enter>.

- Under OS/2, Windows NT, Windows 95, and UNIX (Solaris, AIX, OS390, or HP-UX):
  Type 'copydb' at the system command prompt.

- Under Macintosh:  Double-click the program icon.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if copydb worked correctly:

Use Notes to open the .nsf file you just created.

Compare the copy to the original. The new database should have
the same design and documents as in the original.
