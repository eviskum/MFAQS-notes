Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1996, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
mailscan - Program to search and report mail messages on a specified topic.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	SUN Solaris SPARC
        Linux on Intel platforms


FILES
-----
mailscan.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING mailscan
----------------
This sample program runs against your Notes mail database.  You may 
optionally specify a different Notes mail database by specifying the
name of the database and, optionally, the server where the file resides.
You must supply command-line parameters for the program.

The first argument is used to locate messages with a matching Subject field.
This argument is case-sensitive, and must match the desired Subject field
exactly.

To run this program, type 'mailscan' at the system command prompt,
followed by the subject line to search for, and optionally the Notes
pathname of the desired mail database and the name of the mail server.

For example, to search for the subject line "New Notes C++ API", use the
command:

	mailscan "New Notes C++ API"

The output of the program is written to the output file mailscan.log (in
your current working directory). If there are three messages with that 
topic in your Notes mail database, the program will produce output similar to:

	------------------------
	------------------------
	    MailScan Log
	Scanning mail file for Adam Smith
	Search Formula:  (Subject = "New Notes C++ API") 
		| (Subject = "Re: New Notes C++ API")
	Document Count:  3
	------------------------
	--------
        From:    CN=Mary Jones/OU=BOS/O=Acme
        To:      CN=Adam Smith/OU=BOS/O=Acme
        cc:      
        Subject: New Notes C++ API
        Date:    11/16/2001 12:16:52
	--------
        From:    CN=Adam Smith/OU=BOS/O=Acme
        To:      CN=Mary Jones/OU=BOS/O=Acme
        cc:      
        Subject: Re: New Notes C++ API
        Date:    11/16/2001 12:25:05
	--------
        From:    CN=Mary Jones/OU=BOS/O=Acme
        To:      CN=Adam Smith/OU=BOS/O=Acme
        cc:      
        Subject: Re: New Notes C++ API
        Date:    11/16/2001 12:56:22
	------------------------
	    End of Mail Scan
	------------------------

