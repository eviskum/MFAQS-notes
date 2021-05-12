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
itemsamp - Introductory Notes C++ API program that displays the name and
size of all the items in all the documents in a Notes database.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	SUN Solaris SPARC
        Linux on Intel platforms


FILES
-----
itemsamp.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platforms.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING itemsamp
---------------
This sample program will run against any Notes database. You must
supply command-line parameters to specify the file pathname and,
optionally, server for the database.

To run this program, type 'itemsamp' at the system command prompt,
followed by the Notes pathname of the desired database, and optionally
the name of the server.

For example, the sample database richtext.nsf may be copied to the
your Notes data directory.  The command line for itemsamp is:

	itemsamp richtext

The program should display:

Document Number = 0

Item Number = 0   
Name = Form   
Size = 14

Item Number = 1   
Name = $Fonts   
Size = 110

Item Number = 2   
Name = time_date   
Size = 10

Item Number = 3   
Name = rich_text   
Size = 420

Item Number = 4   
Name = $Revisions   
Size = 22


Document Number = 1

Item Number = 0   
Name = Form   
Size = 14

Item Number = 1   
Name = $Fonts   
Size = 76

Item Number = 2   
Name = time_date   
Size = 10

Item Number = 3   
Name = rich_text   
Size = 346

Item Number = 4   
Name = $UpdatedBy   
Size = 36

All Done. Hit return to exit:

