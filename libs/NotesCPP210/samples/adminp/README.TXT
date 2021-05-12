(c) 2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software 
Development Kit Agreement (in the apilicns.txt file in the notescpp
directory of this toolkit), Restricted Rights for U.S. government 
users, and applicable export regulations.


PROGRAM
-------
adminp - Sample Notes C++ API program that creates an Administration 
Process request to rename a user in a Name and Address book.


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
adminp.cpp - Main program.

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

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this 
               example.


RUNNING adminp
--------------
This sample takes seven arguments: the name of the server containing 
the Name and Address book you wish to modify, the name of your 
certifier ID file, the password for the certifier ID, the name of the person you wish to
rename, the new first name, the new middle name and the new last name.

For example:

adminp verona romeo.id mercutio "Jane Doe" "Jane" "Doe" "Smith"


EXAMINING THE RESULTS
---------------------
To see if adminp worked correctly:

1. Open the Administration Requests database (admin4.nsf) on the 
server you specified. Check that there is a request to "Initiate 
Rename in Address Book".

2. Use Notes to open the Name and Address (names.nsf) book on the 
server you specified. Check that the name you requested to rename is
now renamed. There may be a delay between the time you place the 
request and the time it is performed, depending on the settings
for your server.
