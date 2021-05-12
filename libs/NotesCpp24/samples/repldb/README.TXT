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
repldb - Introductory Notes C++ API program that creates a replica database,
duplicates one of the documents inside the original database and then
replicates the original to the replica.  The resulting databases will
reflect all of the changes.

ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
repldb.cpp   - Main program.

repldb.hpp   - Include file for repldb.cpp

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

repldb.nsf   - Sample Notes source database (in notedata directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING repldb
----------------
This sample program runs against any Notes database.  The program prompts
you for the source file path names and server names.  Otherwise, the default
replication test source database, repldb.nsf, will be used as the source
database file.  A new replica database, replica.nsf, is created.  Next, a 
document from the source database is duplicated in the source database.  
Finally the new replica.nsf database is replicated from the source database.  
After replication, the copied document will show up in both databases.

To run this program, type 'repldb' at the system command prompt.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if repldb worked correctly:

    Use Notes to open replica.nsf to see if the contents are the same
	as the source database after the replication.    
