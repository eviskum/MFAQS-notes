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
attach - Notes C++ API sample program that creates a new document in the
test database provided, adds a TIFF image attachment to it and creates a
Text and Datetimes items for that document.

ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
attach.cpp   - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

rtxtsamp.nsf - Sample Notes database (in notedata directory).

image.tif    - Sample image file (in notedata directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING attach
----------------
This sample program is designed to work with the sample database 
rtxtsamp.nsf and the sample TIFF image file image.tif, in the 
notescpp\notedata directory.  Copy these files to your Notes data directory.  

To run this program, type 'attach' at the system command prompt, followed by
the Notes pathname of the database, and (optionally) the name of the server.

For example, assuming rtxtsamp.nsf and image.tif have been copied to your
Notes data directory, the command line for attach is:

        attach rtxtsamp


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if attach worked correctly:

Use Notes to open rtxtsamp.nsf.

Find a new document called 'Attachment' there. The attachment item should be
appended to the document. Look at the Properties of this document. Click on
Fields. You should find the entries called MyTextItem and MyDatesItem there.

