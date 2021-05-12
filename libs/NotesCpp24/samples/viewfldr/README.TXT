Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1998, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
VIEWFLDR - Notes C++ API sample program that demonstrates LNViewFolder 
features. It copies (without documents) a sample database to a database which
you specify.  If you enter a database name which already exists it will ask 
whether or not it should delete the existing database of that name. 
It then creates a document, sets the 'subject' and 'from' fields 
and saves this document. It then creates a folder, changes the name of that 
folder to 'My New Folder', and puts the newly created document in that folder. 
It then sets the background color of the folder and the heading, saves the 
folder and closes it. Finally it closes the new database.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
        IBM AIX
	SUN Solaris SPARC
        Linux on Intel platforms


FILES
-----
viewfldr.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.

view.nsf     - Sample Notes database (in notedata directory).


RUNNING VIEWFLDR
----------------
This sample program is designed to work with the sample database 
view.nsf, in the notescpp\notedata directory. Copy this database to 
your Notes data directory. 

To run this program, type 'viewfldr' at the system command prompt,
followed by the Notes pathname of the database, and, optionally, the
name of the server.

For example, assuming the sample database view.nsf has been copied to the
user's Notes data directory, the command line for viewfldr is:

	viewfldr <filename> [<serverName>]

where <filename> is the name to assign to the new copy of view.nsf. If
<filename> specifies the name of an existing database, the program will
ask if you really want to delete the existing database.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if viewfldr worked correctly:

      Use Notes to open the database that was created. Check to see if 
      your new folder ("My New Folder") is there and whether the new 
      document (with subject "This is the subject") is in that folder.


