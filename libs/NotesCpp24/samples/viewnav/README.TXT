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
viewnav - Notes C++ API sample program that navigates a view and outputs
the contents of the Subject item in each document in the view.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
viewnav.cpp  - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

view.nsf     - Sample Notes database (in notedata directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING viewnav
---------------
This sample program is designed to work with the sample database 
view.nsf in the notescpp\notedata directory.  Copy this database to your 
Notes data directory.

To run this program, type 'viewnav' at the system command prompt,
followed by the Notes pathname of the database, and (optionally) the
name of the server.

For example, assuming view.nsf has been copied to your Notes data directory,
the command line for viewnav is:

	viewnav view.nsf


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
This sample displays information about the entries in the All Documents view
in the specified database (view.nsf). To determine that the sample worked
correctly, open the All Documents view in the database and verify that the
sample output matches the view entries.
