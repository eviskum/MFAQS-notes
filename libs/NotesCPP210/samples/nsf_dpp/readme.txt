(c) 1997-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
nsf_dpp - Introductory Notes C++ API program that opens a Notes database
and dumps information about it to a plain text log file.

This program exercises many of the tasks you can perform with the C++ API.
It is roughly a C++ counterpart to the C API NSF_DUMP program.


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
nsf_dpp.cpp  - Main program.

nsf_dpp.hpp  - Include file for main program.

nsflog.cpp   - Implementation of the loging functions.

nsflog.hpp   - Abstract class definition for logging.

dumpme.nsf   - Example Notes database file (in NOTEDATA directory).

mswin32.mak  - Make file for Windows NT (32-bit) and
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING nsf_dpp
---------------
This sample program runs against any Notes database.  The program prompts
you for the source .nsf file pathname and server name.  For your convenience,
a sample source database, dumpme.nsf, is provided.  If you place dumpme.nsf
in the data subdirectory of your Notes directory, you can accept all 
defaults when prompted by the program. If you accept all the defaults
when prompted, the output will be placed in a file named: nsflog.txt

To run this program, type 'nsf_dpp' at the system command prompt.


EXAMINING THE LOG FILE TO CHECK THE RESULT
------------------------------------------------
To see if nsf_dpp worked correctly:

    Use Notepad to open nsflog.txt or the name you specified
    for the output log file during the command prompts.
    
    The data in the log file corresponds to all of the Notes, fields, and
    field records in the dumped database.
