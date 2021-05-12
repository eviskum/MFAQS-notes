(c) 2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
frameset - Notes C++ API sample program which builds a frameset.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Windows NT (32-bit)
	Windows 95 (32-bit)
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	SUN Solaris SPARC
	X86 Solaris Intel Edition
        Linux for Intel platforms


FILES
-----
frameset.cpp  - Main program.

borwin32.mak - Make file for Windows NT and Windows 95 (32-bit) using Borland
	       C++.

mswin32.mak  - Make file for Windows NT (32-bit) and 
	       Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
	       IBM VisualAge C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform. 

frameset.nsf - Sample Notes template database (in NOTEDATA directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING frameset
----------------
This sample program is designed to work with the sample database 
frameset.nsf, in the notescpp\notedata directory.  This database should
be copied to your Notes data directory.  

The command line for frameset sample is:

	frameset 


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if frameset worked correctly:

	Use Notes Designer to open frameset.nsf and examine "Home Frameset" 
	frameset note.

	Check database properties, and ensure that "Home Frameset" is chosen to be 
	used when the database is opened from the Web.
	With Notes running start browser locally and open URL:

		http://localhost/frameset.nsf

    the frameset should show up as a home page.

Note 1: Ensure that your browser does not use proxy for "localhost".
Note 2: You may also copy database in the Domino server data directory
		and start browser on a remote machine, specifying URL:

		http://<server name>/frameset.nsf
