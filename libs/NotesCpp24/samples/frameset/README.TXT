Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 2000, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
frameset - Notes C++ API sample program which builds a frameset.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        32-bit Windows 
	IBM AIX
	SUN Solaris SPARC
        Linux for Intel platforms


FILES
-----
frameset.cpp  - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform. 

frameset.nsf - Sample Notes template database (in notedata directory).

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

	Use Domino Designer to open frameset.nsf and examine the "Home Frameset" 
	frameset note.  To see the frameset's appearance locally, while in 
	Designer, you can select Frame/Preview in Notes or Frame/Preview in 
	Web Browser from the menu.
	
	To view the frameset as a home page, check the database properties and
 	ensure that "Home Frameset" is chosen to be used when the database
 	is opened from the Web.  Copy the database to a Domino
 	server data directory and start the browser on a remote machine,
 	specifying URL:

		http://<server name>/frameset.nsf

	The frameset should show up as a home page.



