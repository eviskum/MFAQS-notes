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
SEARCH - Notes C++ API program that searches the source database for
documents modified within a specified range of dates, and copies those
documents to the destination database.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	SUN Solaris SPARC
	IBM AIX
        Linux on Intel platforms


FILES
-----
search.cpp   - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING search
--------------
This sample program will run against any Notes database. You must supply
command-line parameters to specify the file pathnames and the start and
end dates for the search.  

Type 'search' at the system command prompt, followed by the Notes 
pathname of the desired source and destination databases, and the start 
and end dates for the search.

For example, the sample databases search1.nsf and search2.nsf may be 
copied to your Notes data directory.  The command line for search is:

	search search1 search2 7/13/93 8/2/96

The program will display:

        Copying notes from search1 to search2
	Number of documents found: 2


EXAMINING THE NOTES DATABASES TO CHECK THE RESULT
-------------------------------------------------
To see if search worked correctly:

    - Use Notes to open search1.nsf and search2.nsf

    - The database search2 should contain copies of those documents
      from search1 with modification dates in the specified range.
