Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 2000, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
profile - Sample Notes C++ API program that opens a Notes database
and lists the name and owner of each profile document.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
profile.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform,

readme.txt   - This file.  Specifies what is needed to use this 
               example.


RUNNING profile
---------------
This sample takes two arguments. The first argument is the name of the
database that you want to search for profile documents; the second,
optional argument is the server where this database can be found. We
recommend that you run this sample against your mail database as that
will most likely contain several profile documents.

For example:

profile jdoe.nsf pluto


EXAMINING THE RESULTS
---------------------
The results will vary depending on the types of profile documents you
have in your mail database, but the output will look something like 
the following:

The name of profile number 0 is calendarprofile
The owner of this profile is cn=Jane Doe
