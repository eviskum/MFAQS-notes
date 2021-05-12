(c) 2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software 
Development Kit Agreement (in the apilicns.txt file in the notescpp
directory of this toolkit), Restricted Rights for U.S. government 
users, and applicable export regulations.


PROGRAM
-------
profile - Sample Notes C++ API program that opens a Notes database
and lists the name and owner of each profile document.


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
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition
        Linux on Intel platforms


FILES
-----
profile.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) 
               and Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 
               (32-bit) using IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 
               (32-bit) using Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform,

readme.txt   - This file.  Specifies what is needed to use this 
               example.


RUNNING profile
---------------
This sample takes two arguments. The first argument is the name of the
database that you want to search for profile documents; the second,
optional argument is the server where this database can be found.

For example:

profile jdoe.nsf pluto


EXAMINING THE RESULTS
---------------------
The results will vary depending on the types of profile documents you
have in your mail database, but the output will look something like 
the following:

The name of profile number 0 is calendarprofile
The owner of this profile is cn=Jane Doe
