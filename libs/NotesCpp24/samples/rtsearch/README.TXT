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
rtsearch - Notes C++ API sample program that searches for and replaces
a text string in a rich text item.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
rtsearch.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

rtsearch.nsf - Sample Notes database (in notedata directory).

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


BEFORE RUNNING rtsearch
-----------------------
This sample program is designed to work with the sample database 
rtsearch.nsf, in the notescpp\notedata directory.  Copy this database to your 
Notes data directory. Then:

      1. Use Notes to open rtsearch.nsf.
      2. Open one of the documents and verify that it contains the string 
         "Cplusplus".
      3. Close rtsearch.nsf.


RUNNING rtsearch
----------------
To run this program, type 'rtsearch' at the system command prompt,
followed by the Notes pathname of the database, and (optionally) the
name of the server.

For example, assuming rtsearch.nsf has been copied to your Notes data 
directory, the command line for rtsearch is:

	rtsearch rtsearch


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if rtsearch worked correctly:

      1. Re-open rtsearch.nsf.
      2. Open one of the documents and verify that the string "Cplusplus" 
         has been replaced with "C++".
