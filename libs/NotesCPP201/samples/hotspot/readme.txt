(c) 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
HOTSPOT - Notes C++ API sample program that creates and manipulates
different kind of hotspots.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition

The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++

This sample does not currently support the Macintosh.


FILES
-----
hotspot.cpp  - Main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit)
               using IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit)
               using Borland C++ 5.0 for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

readme.txt   - This file.  Specifies what is needed to use this example.

sampledb.nsf - Sample Notes database (in NOTEDATA directory).

script.txt   - Sample text file (in NOTEDATA directory).


RUNNING HOTSPOT
----------------
This sample program is designed to work with the sample database
SAMPLEDB.NSF and the sample "script.txt" file, provided in the
notescpp\notedata directory.  Copy these files to your Notes data 
directory. You must supply command line parameters to specify the
file pathname and, optionally, the server for the database.

- Under Windows 16-bit:  Choose File - Run from the Program Manager menu, 
  type in the full path and filename of this program, the Notes pathname
  of the database, and (optionally) the name of the server, and
  press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390, or HP-UX):
  Type 'hotspot' at the system command prompt, followed by the Notes
  pathname of the database, and (optionally) the name of the server.

For example, assuming SAMPLEDB.NSF and script.txt have been copied to your
Notes data directory, the command line for HOTSPOT is:

      HOTSPOT SAMPLEDB



EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if HOTSPOT worked correctly:

      Use Notes to open SAMPLEDB.NSF

      Open the doc with subject 'Hotspot Sample Document'.  The 
      document should contain 3 action hotspots, 3 buttons, and 3 popups,
	  each of which should perform a specific action when activated.

