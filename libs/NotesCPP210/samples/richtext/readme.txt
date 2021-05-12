(c) 1996-2000 Lotus Development Corporation.  All rights reserved.
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

        Windows NT (32-bit)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	SUN Solaris SPARC
	X86 Solaris Intel Edition
        Linux on Intel platforms


FILES
-----
richtext.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.

rtxtsamp.nsf - Sample Notes database (in NOTEDATA directory).


RUNNING richtext
----------------
This sample program is designed to work with the sample database 
rtxtsamp.nsf that is located in the notescpp\notedata directory.  
This database should be copied to your Notes data directory.  
The user must supply command-line parameters to specify the file
pathname and, optionally, server for the database.

You may copy the rtxtsamp.nsf database into another file and supply
the new filename as the command-line argument. If you want to 
create another sample database to run against this sample - be careful: 
the program looks for a specific document (called "Rich Text sample") 
that was created using a specific form (RichTextSample). You may encounter 
errors if your document is different. 

To run this program, type 'richtext' at the system command prompt,
followed by the Notes pathname of the database, and, optionally, the name
of the server.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if richtext worked correctly:

1. Use Notes to open the database you used for input.

2. Open the documents entitled "Rich Text sample" and "Rich Text sample 
   results."

   The body of the  "Rich Text sample results" document should contain:

   - "Rich text: ", followed by the multi-font rich text after "And this
     is the rich text:" in the "Rich Text sample" document.

   - This series of values:

     Datetime: 03/12/98
     Datetimes: 12/12/98;12/13/98
     Datetime range:12/12/98 - 12/13/98
     Datetime ranges:01/12/98 - 03/12/98;12/13/98 - 12/15/98
     Number: 123
     Numbers: 123;234
     Name: myname
     Names: myname;yourname
     Text: hello
     TextList: hello;again

     These values should match the values in the first part of the
     "Rich Text sample" document, which looks like:

    This is the datetime: 03/12/98
    This is a list of datetimes: 12/12/98, 12/13/98 
 
    This is a datetime range: 12/12/98 - 12/13/98
    This is a list of datetime ranges: 01/12/98 - 03/12/98; 12/13/98 - 12/15/98

    This is a number: 123
    This is a list of numbers: 123; 234

    This is some text: hello
    This is a text list: hello; again

    This is a name: myname
    This is a list of names: myname; yourname


	 
