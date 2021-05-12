(c) 1997-1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
nsf_dpp - Introductory Notes C++ API program that opens a Notes database
and dumps information about it to a plain text log file.

This program exercises many of the tasks you can perform with the C++ API.
It is roughly a C++ counterpart to the C API NSF_DUMP program with the 
exception that it currently only dumps Document Notes in the database.

NOTE: Code that takes advantage of newer features of the C++ API,
      (i.e. Versions after the 4.12 release) Are not yet implemented
      in this sample.

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
nsf_dpp.cpp  - Main program.

nsf_dpp.hpp  - Include file for main program.

nsflog.cpp   - Implementation of the loging functions.

nsflog.hpp   - Abstract class definition for logging.

dumpme.nsf   - Example Notes database file (in NOTEDATA directory).

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and
               Windows 95 (32-bit) using Microsoft Visual C++.

nsf_dpp.def  - Module definition (.def) file for 16-bit Borland C++ for Windows.

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


RUNNING nsf_dpp
---------------
This sample program runs against any Notes database.  The program prompts
you for the source .nsf file pathname and server name.  For your convenience,
a sample source database, dumpme.nsf, is provided.  If you place dumpme.nsf
in the data subdirectory of your Notes directory, you can accept all 
defaults when prompted by the program. If you accept all the defaults
when prompted, the output will be placed in a file named: nsflog.txt

- Under Windows 16-bit:  choose File Run from the Program Manager menu, 
  type in the full path and filename of this program, and press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  type 'nsf_dpp' at the system command prompt.


EXAMINING THE LOG FILE TO CHECK THE RESULT
------------------------------------------------
To see if nsf_dpp worked correctly:

    Use Notepad to open nsflog.txt or the name you specified
    for the output log file during the command prompts.
    
    The data in the document corresponds to all the documents, fields, and
    field records in the dumped database.
