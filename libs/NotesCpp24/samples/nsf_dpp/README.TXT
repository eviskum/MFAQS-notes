Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1997, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
nsf_dpp - Introductory Notes C++ API program that opens a Notes database
and dumps information about it to a plain text log file.

This program exercises many of the tasks you can perform with the C++ API.
It is roughly a C++ counterpart to the C API NSF_DUMP program.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
nsf_dpp.cpp  - Main program.

nsf_dpp.hpp  - Include file for main program.

nsflog.cpp   - Implementation of the logging functions.

nsflog.hpp   - Abstract class definition for logging.

dumpme.nsf   - Example Notes database file (in notedata directory).

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

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
