(c) 1996-1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
mailscan - Program to search and report mail messages on a specified topic.


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

This sample does not currently support the Macintosh.


FILES
-----
mailscan.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

mailscan.def - Module definition (.def) file for 16-bit Borland C++ for Windows.

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


RUNNING mailscan
----------------
This sample program runs against your Notes mail database.  You may 
optionally specify a different Notes mail database by specifying the
name of the database and, optionally, the server where the file resides.
You must supply command-line parameters for the program.

The first argument is used to locate messages with a matching Subject field.
This argument is case-sensitive, and must match the desired Subject field
exactly.

- Under Windows 16-bit:  choose File Run from the Program Manager menu, 
  type in the full path and filename of this program, the subject line to
  search for, and optionally the Notes pathname of the desired mail database 
  and the name of the mail server, and press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  type 'mailscan' at the system command prompt, followed by the subject line 
  to search for, and optionally the Notes pathname of the desired mail 
  database and the name of the mail server.

For example, to search for the subject line "New Notes C++ API", use the
command:

	mailscan "New Notes C++ API"

The output of the program is written to the output file mailscan.log (in
your current working directory). If there are three messages with that 
topic in your Notes mail database, the program will produce output similar
to:

	------------------------
	------------------------
	    MailScan Log
	Scanning mail file for Adam Smith
	Search Formula:  (Subject = "New Notes C++ API") 
		| (Subject = "Re: New Notes C++ API")
	Document Count:  3
	------------------------
	--------
	From:    Mary Jones
	To:      Notes API Team
	cc:      Amanda Barnes, Steve Chu, Robin Dyer
	Subject: New Notes C++ API
	--------
	From:    Adam Smith
	To:      Mary Jones
	cc:      Amanda Barnes, Steve Chu, Robin Dyer
	Subject: Re: New Notes C++ API
	--------
	From:    Mary Jones
	To:      Adam Smith
	cc:      Amanda Barnes, Steve Chu, Robin Dyer
	Subject: Re: New Notes C++ API
	------------------------
	    End of Mail Scan
	------------------------

