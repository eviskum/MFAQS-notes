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
HOTSPOT - Notes C++ API sample program that creates and manipulates
different kinds of hotspots.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux for Intel platforms


FILES
-----
hotspot.cpp  - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.

sampledb.nsf - Sample Notes database (in notedata directory).

script.txt   - Sample text file (in notedata directory).


RUNNING HOTSPOT
----------------
This sample program is designed to work with the sample database
sampledb.nsf and the sample "script.txt" file, provided in the
notescpp\notedata directory.  Copy these files to your Notes data 
directory. You must supply command line parameters to specify the
file pathname and, optionally, the server for the database.

To run this program, type 'hotspot' at the system command prompt,
followed by the Notes pathname of the database, and (optionally) the
name of the server.

For example, assuming sampledb.nsf and script.txt have been copied to your
Notes data directory, the command line for hotspot is:

      hotspot sampledb



EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if hotspot worked correctly:

      Use Notes to open sampledb.nsf.

      Open the doc with subject 'Hotspot Sample Document'.  The 
      document should contain 3 action hotspots, 3 buttons, and 3 popups,
	  each of which should perform a specific action when activated.

