(c) 1997, 1998 Lotus Development Corporation.  All rights reserved.
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

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition


The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++
	MacOS (7.5 or later) Power PC


FILES
-----
linkdemo.cpp - Main program.

borwin32.mak - Make file for Windows NT and Windows 95 (32-bit) using Borland
               C++.

mswin32.mak  - Make file for Windows NT (32-bit) (including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

linkdemo.def - Module definition (.def) file for 16-bit Borland C++ for Windows.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ 5.0 for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linkdemo.nsf - The source database (in NOTEDATA directory).

rtsample.nsf - The destination database (in NOTEDATA directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING linkdemo
---------------
This sample does not take any arguments. Copy linkdemo.nsf and rtsample.nsf
from the NOTEDATA directory into your Notes data directory.

NOTE: The linkdemo.nsf database contains links to all of the databases in
the NOTEDATA directory.  You should copy all of the .nsf files to your local
Notes data directory if you want to make sure that the links work after running
the sample.  Even after copying all of the .nsf files to your local directory,
there is still a chance that some of the links may be broken, but this will
not have any effect on how the sample runs.

- Under Windows 16-bit:  Choose File - Run from the Program Manager menu, 
  type in the full path and filename of this program, and press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  Type 'linkdemo' at the system command prompt.

- Under Macintosh:  Double-click the program icon.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if linkdemo worked correctly:

	Use Notes to open linkdemo.nsf
	After opening the database open the first document you see.
	It's title is:  "A Document of Links"  After opening,
	you will see the phrase:  *Here are some links for testing*
	before the phrase you will see a doc link to the destination
	database.  LINKDEMO created this link and you can click on it
	to get to the destination database.

	The rest of the links in this document were here already and are
	copied by LINKDEMO from this document into the destination document.

	After clicking on the first Link to the destination database,
	open the only document in that database titled:  
	"A Document for Rich Text C++ API Sample Apps"
	After opening you will see a all of the links that were copied by
	LINKDEMO from the source document along with the link that was
	created by LINKDEMO pointing to the source database.

	NOTE: You could do the above on the fly while the program is running
	because it pauses during execution to allow you to see what is going
	on.  However, you must close the document each time before running
	the program to the next pause point.  You must not edit the document
	while the program is executing, otherwise you may get an error saying:
	Someone has altered the doc, causing the program to terminate.
