(c) 1996-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
IEXPORT - Notes C++ API sample program that imports a CGM Image
file into a Lotus Notes document in the test database provided.  Then,
it will export the whole document of the very same database to a text file.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Windows NT (32-bit)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)

This sample supports Win32 and OS/2 platforms only.


FILES
-----
iexport.cpp  - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) and 
	       Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit)
	       using IBM VisualAge C++ for Windows.
	       
borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

readme.txt   - This file.  Specifies what is needed to use this example.

sampledb.nsf - Sample Notes database (in NOTEDATA directory).

graph.cgm    - A sample CGM Image file that gets imported. (in NOTEDATA directory).


RUNNING IEXPORT
---------------
This sample program is designed to work with the sample database
sampledb.nsf and the file graph.cgm, both provided in the toolkit
directory NOTEDATA. Before running the sample, copy these files to
your Notes data directory.

To run the sample, type 'iexport' at the system command prompt,
followed by the pathname of the database, and (optionally) the name
of the server. For example, assuming sampledb.nsf and graph.cgm have
been copied to your Notes data directory, run the sample by typing:

     iexport sampledb.nsf


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if IEXPORT worked correctly:

      Use Notes to open sampledb.nsf.

      Open the first note. The file graph.cgm should be imported
      in the rich text item of the first document. There should also
      be a new exported text file called expfile.txt.
