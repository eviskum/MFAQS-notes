(c) 1997, 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
repldb - Introductory Notes C++ API program that creates a replica database,
duplicates one of the documents inside the original database and then replicates
the original to the replica.  The resulting databases will reflect all of the changes.

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

This sample does not currently support the Macintosh.


FILES
-----
repldb.cpp   - Main program.

repldb.hpp   - Include file for repldb.cpp

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and
               Windows 95 (32-bit) using Microsoft Visual C++.

repldb.def   - Module definition (.def) file for 16-bit Borland C++ for Windows.

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

repldb.nsf   - Sample Notes source database (in NOTEDATA directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING repldb
----------------
This sample program runs against any Notes database.  The program prompts
you for the source file path names and server names.  Otherwise, the default
replication test source database, repldb.nsf will be used as the source
database file.  A new replica database, replica.nsf, is created.  Next, a 
document from the source database is duplicated in the source database.  
Finally the new replica.nsf database is replicated from the source database.  
After replication, the copied document will show up in both databases.

- Under Windows 16-bit:  choose File Run from the Program Manager menu, 
  type in the full path and filename of this program, and press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  type 'repldb' at the system command prompt.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if repldb worked correctly:

    Use Notes to open replica.nsf to see if the contents is the same
	as the source database after the replication.    
