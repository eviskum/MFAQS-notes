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
adminp - Sample Notes C++ API program that creates an Administration 
Process request to rename a user in a Name and Address book.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
adminp.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this 
               example.


RUNNING adminp
--------------
This sample takes seven arguments: the name of the server containing 
the Name and Address book you wish to modify, the name of your 
certifier ID file, the password for the certifier ID, the hierarchical
name of the person you wish to rename, the new first name, the new
middle name and the new last name.

For example:

adminp verona romeo.id mercutio "Jane Doe/MIS/Acme" "Jane" "Doe" "Smith"


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
