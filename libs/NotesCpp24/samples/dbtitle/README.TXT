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
dbtitle - Introductory Notes C++ API program that opens a Notes database
and displays the database title.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
dbtitle.cpp  - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING dbtitle
---------------
This sample program will run against any Notes database.

To run this program, type 'dbtitle' at the system command prompt,
followed by the Notes pathname of the desired database, and optionally
the name of the server.

For example, the sample database richtext.nsf may be copied to the
user's Notes data directory.  The command line for dbtitle is:

	dbtitle richtext

The program should display:

	The database title is:  Rich-Text Test


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if dbtitle worked correctly:

Use Notes to open richtext.nsf

Choose File/Database/Properties...

You should see the same database title as displayed by
dbtitle.
