(c) 1997-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
linkdemo - Sample Notes C++ API program that opens two Notes databases and
opens a document in each that contains a "Body" rich text field. It creates
document links to both databases and inserts them into each other's database.
It then copies all the links from the source database's document to the
destination database's document.

ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

    Windows NT (32-bit)
	Windows 95 (32-bit)
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition
    Linux on Intel platforms


FILES
-----
linkdemo.cpp - Main program.

borwin32.mak - Make file for Windows NT and Windows 95 (32-bit) using Borland
               C++ for Windows.

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

linkdemo.nsf - The source database (in NOTEDATA directory).

rtsample.nsf - The destination database (in NOTEDATA directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING linkdemo
----------------
This sample does not take any arguments. Copy linkdemo.nsf and rtsample.nsf
from the NOTEDATA directory into your Notes data directory.

NOTE: The linkdemo.nsf database contains links to all of the databases in
the NOTEDATA directory.  You should copy all of the .nsf files to your local
Notes data directory if you want to make sure that the links work after running
the sample.  Even after copying all of the .nsf files to your local directory,
there is still a chance that some of the links may be broken, but this will
not have any effect on how the sample runs.

To run this program, type 'linkdemo' at the system command prompt.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if linkdemo worked correctly:

	Use Notes to open linkdemo.nsf. Open the document titled "A Document of Links".  
	On the first line you will see the phrase: *Here are some links for testing*.
	The "Habanero" hotspot on the next line contains a doc link to the rtsample.nsf
	database.  LINKDEMO created this link and you can click on it
	to get to that database. The rest of the links in this document are copied by 
	LINKDEMO from this document in linkdemo.nsf to the destination document in rtsample.nsf.

	After clicking on the first link to get to the database rtsample.nsf,
	open the document in that database titled:  
	"A Document for Rich Text C++ API Sample Apps"
	After opening this document you will see all the links that were copied by
	LINKDEMO from the source document in linkdemo.nsf as well as the link that was
	created by LINKDEMO pointing to the source database.

	NOTE: You may view the changes in the destination document when the program pauses 
	between each action.  
	However, you must close the destination document each time before running
	the program to the next pause point.  You should not edit the document
	while the program is executing, doing so will cause an error and the program 
	will terminate.

