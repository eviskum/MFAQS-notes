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
formula - Notes C++ API sample program that creates a formula and uses
the LNFormula class to run it against the documents in a database.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
formula.cpp  - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.

view.nsf     - Sample Notes database (in notedata directory).


BEFORE RUNNING formula
----------------------
This sample program is designed to work with the sample database 
view.nsf in the notescpp\notedata directory.  Copy this database to your 
Notes data directory. Then:

1. Use Notes to open view.nsf.
2. Open a main topic (unindented) document in the "All documents" view
   and check for the word 'Event' in the subject at the top of the page.
3. Close view.nsf.


RUNNING formula
---------------
To run this program, type 'formula' at the system command prompt,
followed by the Notes pathname of the database and (optionally) the name
of the server.

For example, assuming the sample database view.nsf has been copied to your
Notes data directory, the command line for formula is:

        formula view

The program creates and runs a formula that changes the text string in the 
Subject items of the main topic documents in view.nsf. 


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if formula works correctly:

1. Re-open view.nsf.
2. Re-open the main topic document. The word 'Event' in the subject 
   should be gone, replaced by the word 'Holiday'.
