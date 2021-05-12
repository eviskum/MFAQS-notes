(c) 1998-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
embedole - Sample program that demonstrates embedding an OLE 2 object
           into a note using the C++ API.

	This sample has been enhanced to obtain a bitmap from the OLE
	object and import that bitmap into Notes using the C++ API.  Due
	to some technical limitiations of the C and C++ APIs, there is no
	direct way for the C++ API to convert a bitmap from the internal
	format used by Windows to the storage format used by Notes.
	However, there is an indirect solution that an application
	developer can use:  store the bitmap in a file and import that
	file into a temporary LNRichText item, then copy the LNGraphic
	from the temporary item to the LNRTOLEObject.  This revised
	sample demonstrates the process.

	The old sample program was first restructured, in the (perhaps
	vain) hope of making the error handling simpler and the source
	code more readable.  Next, new code was added, embodied in the
	function GetGraphic(), to obtain the bitmap from the OLE object
	and import it into the C++ API.  Finally, code was added to
	EmbedInNotes() to replace the dummy icon with the bitmap.

	New in 2.1:  The bug in the function LNRTOLEObject::SetGraphic(),
	which failed to copy the graphic from the source container to the
	destination, has been fixed.  The work-around for this problem was
	removed from the sample.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32


FILES
-----
embedole.cpp - Main program.

msbitmap.c   - Windows bitmap conversion functions

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

lincoln.rtf  - Sample file to embed - Lincoln's Gettysburgh Address in
               Microsoft rich text format. 

rtsample.nsf - Sample Notes database (in NOTEDATA directory) recommended
               for use with this sample.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING embedole
----------------
This sample program will run against any Notes database, but using the
sample database rtsample.nsf is recommended.  The user must supply
command-line parameters to specify:

	* file pathname of object to embed
	* database file pathname
	* (optional) server for the database.

Any OLE object which has an OLE server application installed may be
used.  As a convenience, a sample file lincoln.rtf has been provided.
On most Windows NT and Windows 95 systems, rich text files are
processed by the WordPad application by default.
(Note: If you are using NT 3.51 this sample will not work since WordPad
is not provided with NT3.51)

- Under Windows NT and Windows 95:  type 'embedole' at the system
  command prompt, followed by the pathname of the OLE object file,
  the pathname of the desired Notes database, and, optionally, the
  name of the Notes server.

For example, the sample database rtsample.nsf may be copied to the
user's Notes data directory.  The command line for embedole is:

	embedole lincoln.rtf rtsample.nsf

The program should display:

	Created new document.
	Embedded OLE object from file lincoln.rtf using application WordPad Document
	All Done.  Hit return to exit:


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if embedole worked correctly:

	Use Notes to open rtsample.nsf
	The database should contain a new document with the title
		"Embedded OLE Object".
	Open the new document.  The bitmap for the embedded OLE object 
		should be displayed.
	Double-click on the embedded object to activate WordPad.
