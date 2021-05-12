(c) 1996-1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
richtext - Notes C++ API sample program that demonstrates how to retrieve 
the contents of all different types of items that are stored in a note
and display them in rich text in another note.


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
	SUN Solaris SPARC
	X86 Solaris Intel Edition

The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++
	MacOS (7.x) Power PC


FILES
-----
richtext.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

richtext.def - Module definition (.def) file for 16-bit Borland C++ for Windows.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ 5.0 for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

readme.txt   - This file.  Specifies what is needed to use this example.

rtxtsamp.nsf - Sample Notes database (in NOTEDATA directory).


RUNNING richtext
----------------
This sample program is designed to work with the sample database 
rtxtsamp.nsf that is located in the notescpp\notedata directory.  
This database should be copied to your Notes data directory.  
On platforms other than Macintosh, the user must supply 
command-line parameters to specify the file pathname and, optionally, 
server for the database.  On the Macintosh, the user is prompted for the 
file pathname and server name. 

You may copy the rtxtsamp.nsf database into another file and supply
the new filename as the command-line argument. If you want to 
create another sample database to run against this sample - be careful: 
the program looks for a specific document (called "Rich Text sample") 
that was created using a specific form (RichTextSample). You may encounter 
errors if your document is different. 

- Under Windows 16-bit:  choose File Run from the Program Manager menu, 
  type in the full path and filename of this program, the Notes pathname
  of the database, and optionally the name of the server, and
  press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  type 'richtext' at the system command prompt, followed by the Notes
  pathname of the database, and optionally the name of the server.

- Under Macintosh:  double click on the program icon.  The program will
  prompt for the database pathname and optional server name.




EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if richtext worked correctly:

      Use Notes to open the database you used for input.

      Open the documents entitled "Rich Text sample" and "Rich Text sample 
	  results."

	  The body of the  "Rich Text sample results" document should contain 
	  the "printout" of the data in the items in the "Rich Text sample" 
	  document. Make sure that the values you see in "Rich Text sample results" 
	  match the values in "Rich Text sample. "

	 
