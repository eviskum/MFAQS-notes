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
addfoldr - Notes C++ API sample program that creates new folders and 
copies documents into the new folders, based on the document subject.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
addfoldr.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

view.nsf     - Sample Notes database (in notedata directory).
		
readme.txt   - This file.  Specifies what is needed to use this example.


BEFORE RUNNING addfoldr
-----------------------
This sample program is designed to work with the sample database 
view.nsf, in the notescpp\notedata directory.  Copy this database to your 
Notes data directory.

addfoldr creates a folder for each quarter of the year (1stQuarter, 2ndQuarter,
and so on), and places documents in those folders based on the month specified
in the document's subject. Before running addfoldr, use Notes to open
view.nsf. Verify that the folders for each quarter do not exist, and then
close the database.


RUNNING addfoldr
----------------
To run this program, type 'addfoldr' at the system command prompt,
followed by the Notes pathname of the database, and (optionally) the name
of the server.

For example, assuming view.nsf has been copied to your Notes data directory,
the command line for addfoldr is:

        addfoldr view


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if addfoldr worked correctly:

      1. Re-open view.nsf.
      2. Verify that the new folders exist and that they contain the correct
         documents.
