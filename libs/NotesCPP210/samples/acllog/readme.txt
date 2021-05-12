(c) 1997 - 2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
acllog - Introductory Notes C++ API program that opens a Notes database
and logs the acl entry list information about it to another Notes Log 
database.


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
acllog.cpp  - Main program.

acllog.hpp -  Header file for acllog.cpp.

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

acllog.nsf   - Example Notes log database (in NOTEDATA directory,
               used for output).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING acllog
---------------
This sample program runs against any Notes database.  The program prompts
you for the source .nsf file pathname and server name. The provided database,
acllog.nsf, will be used as the output log database file.  Copy acllog.nsf
from the NOTEDATA directory into your Notes data directory.  If you want to 
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
