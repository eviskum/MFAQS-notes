Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1996, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
copydb - Introductory Notes C++ API program that opens a Notes database,
copies its contents to a new destination database, and sets the new
database title.  The destination database can be either a replica or
non-replica copy.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
copydb.cpp   - Main program.

copydb.hpp   - Include file for main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING copydb
--------------
This sample program runs against any Notes database.  The user is prompted 
for the source and destination .nsf file path and server names, the
destination database title, and whether to create a replica or non-replica
copy.

To run this program, type 'copydb' at the system command prompt.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if copydb worked correctly:

Use Notes to open the .nsf file you just created.

Compare the copy to the original. The new database should have
the same design and documents as in the original.
