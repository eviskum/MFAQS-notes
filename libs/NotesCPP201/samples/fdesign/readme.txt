(c) 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
fdesign - Notes C++ API sample program to manipulate the design elements of a form


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	SUN Solaris SPARC
	X86 Solaris Intel Edition

The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	MacOS (7.x) Power PC

Note that this sample does not currently support 16-bit Windows.


FILES
-----
fdesign.cpp  - Main program.

borwin32.mak - Make file for Windows NT and Windows 95 (32-bit) using Borland
	       C++.

mswin32.mak  - Make file for Windows NT (32-bit) (including DEC Alpha) and 
	       Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
	       IBM VisualAge C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

fdesign.ntf  - Sample Notes template database (in NOTEDATA directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING fdesign
----------------
This sample program is designed to work with the sample template database 
fdesign.ntf, in the notescpp\notedata directory.  This database should
be copied to your Notes data directory.  On platforms other than 
Macintosh, the user may supply optional command-line parameters to specify 
the file pathname and server for the database.  On the Macintosh, 
the user is prompted for the file pathname and server name.

Note: unlike most of the other samples, fdesign works with the database
template, which means that if you enter the database name on the command 
line it should be specified with the extension ntf:
	
	fdesign.ntf

otherwise the extension defaults to nsf.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390, or HP-UX):
  type 'fdesign' at the system command prompt, followed optionally
  by the Notes pathname of the database and the name of the server.

- Under Macintosh:  double click on the program icon.  The program will
  prompt for the database pathname and optional server name.

For example, the sample database fdesign.ntf may be copied to the
user's Notes data directory.  The command line for fdesign is:

	fdesign 

The program will create a copy of a master form stored in fdesign.ntf, 
add design elements to this copy, and modify properties of the
existing ones.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if fdesign worked correctly:

	Use Notes to open fdesign.ntf.

	Open two forms: "Master Form with Fields and a Subform",
			"Created Form with Fields and a Subform".

	Compare their content.

Note that you can only examine the forms in fdesign.ntf on platforms that
support a full Notes client. The Domino administration client on server-
only platforms, for example Notes 4.6x for OS/2, cannot be used to examine
forms in a database. You can, however, run the sample program on any of the
platforms listed in the ENVIRONMENTS section, above.
