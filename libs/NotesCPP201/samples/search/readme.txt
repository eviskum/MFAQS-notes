(c) 1996-1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
SEARCH - Notes C++ API program that searches the source database for
documents modified within a specified range of dates, and copies those
documents to the destination database.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit) (including DEC Alpha)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	SUN Solaris SPARC
	IBM AIX
	X86 Solaris Intel Edition

The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++

This sample does not currently support the Macintosh.


FILES
-----
search.cpp   - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) (including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

search.def   - Module definition (.def) file for 16-bit Borland C++ for Windows.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ 5.0 for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING search
--------------
This sample program will run against any Notes database. You must supply
command-line parameters to specify the file pathnames and the start and
end dates for the search.  

- Under Windows 16-bit:  choose File Run from the Program Manager menu, 
  type in the full path and filename of this program, the Notes pathname
  of the desired source and destination databases, and the start and end
  dates for the search, then press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  type 'search' at the system command prompt, followed by the Notes 
  pathname of the desired source and destination databases, and the start 
  and end dates for the search.

For example, the sample databases search1.nsf and search2.nsf may be 
copied to your Notes data directory.  The command line for search is:

	search search1 search2 7/13/93 8/2/96

The program will display:

	Copying notes from .\search1 to .\search2
	Number of documents found: 2


EXAMINING THE NOTES DATABASES TO CHECK THE RESULT
-------------------------------------------------
To see if search worked correctly:

    - Use Notes to open search1.nsf and search2.nsf

    - The database search2 should contain copies of those documents
      from search1 with modification dates in the specified range.
