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
acllog - Introductory Notes C++ API program that opens a Notes database
and logs the acl entry list information about it to another Notes Log 
database.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
acllog.cpp   - Main program.

acllog.hpp   - Header file for acllog.cpp.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

acllog.nsf   - Example Notes log database (in notedata directory,
               used for output).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING acllog
---------------
This sample program runs against any Notes database.  The program prompts
you for the source .nsf file pathname and server name. The provided database,
acllog.nsf, will be used as the output log database file.  Copy acllog.nsf
from the notedata directory into your Notes data directory.  If you want to 
iterate the acl entry list in names.nsf, you can accept all defaults when
prompted by the program.

To run the program, type 'acllog' at the system command prompt.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if acllog worked correctly:

    Use Notes to open acllog.nsf.
    
    Open the log document that corresponds to the .nsf file's acl entry 
	list you just specified.

    The data in the document corresponds to all the access control list
	entries in the specified database.
