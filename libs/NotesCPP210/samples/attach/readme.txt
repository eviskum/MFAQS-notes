(c) 1996-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
attach - Notes C++ API sample program that creates a new document in the
test database provided, adds a TIFF image attachment to it and creates a
Text and Datetimes items for that document.

ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

    Windows NT (32-bit)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition
    Linux on Intel platforms


FILES
-----
attach.cpp   - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

rtxtsamp.nsf - Sample Notes database (in NOTEDATA directory).

image.tif    - Sample image file (in NOTEDATA directory.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING attach
----------------
This sample program is designed to work with the sample database 
RTXTSAMP.NSF and the sample TIFF image file IMAGE.TIF, in the 
notescpp\notedata directory.  Copy these files to your Notes data directory.  

To run this program, type 'attach' at the system command prompt, followed by
the Notes pathname of the database, and (optionally) the name of the server.

For example, assuming RTXTSAMP.NSF and IMAGE.TIF have been copied to your
Notes data directory, the command line for attach is:

	ATTACH RTXTSAMP


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if attach worked correctly:

Use Notes to open RTXTSAMP.NSF

Find a new document called 'Attachment' there. The attachment item should be
appended to the document. Look at the Properties of this document. Click on
Fields. You should find the entries called MyTextItem and MyDatesItem there.

