(c) 1997, 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
userregs - This program demonstrates how to use the LNCertifier 
class to register a new hierarchical organizational certifier, an 
organizational unit certifier, a server, and a workstation.

First it creates a new organization certifier, ABCorp, and sets the password 
in the certifier ID to "password". Then it creates a new organization unit 
certifier, Sales. This certifier is a descendent of the organization 
certifier. Then it registers a new server, OTTO, and 
certifies it with the organization certifier.  Finally, it registers a new 
user and certifies it with the organization unit certifier. 

New entries for the organization certifier, organization unit certifier, 
new server, and new user are placed in the server's NAMES.NSF.

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
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition


The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++


FILES
-----
userregs.cpp - Main program. 

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and
               Windows 95 (32-bit) using Microsoft Visual C++.

userregs.def - Module definition (.def) file for 16-bit Borland C++ for Windows.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

os2_32.mak   - Make file OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING userregs
----------------
This sample program runs on the Notes Server and creates 2 ID files. 
If you run this program under NT or OS/2, these ID files are written to 
disk A:.  Therefore, you should insert a formatted diskette in drive A: 
before running this program under OS/2 or NT.

If you run this program under UNIX, the ID files are written 
to /tmp.

For each ID created, this program creates new entries in NAMES.NSF
on the server specified on the command line. Therefore, you must have author 
access to that database. When the new user is registered, a mail file is 
created.

You can open NAMES.NSF on the server to check the newly created entries 
after the program is successfully run.

- Under OS/2 or UNIX (HP-UX, OS/390 and Solaris), type the following at
  the system command prompt:

        userregs  <Full server name>

where <Full server name> is the name of the Notes server with which you 
would like to register your new hierarchical organizational certifier, 
organizational unit certifier, server, and workstation.


- Under Windows 16-bit:  Choose File - Run from the Program Manager menu, 
  type in the full path and filename of this program and the Full server
  name, and press <Enter>.

- Under OS/2, Windows NT, Windows 95 and UNIX (Solaris, AIX, OS/390 or HP-UX):
  Type 'userregs <Full server name>' at the system command prompt.

- This sample does not run on the Macintosh as the Macintosh is not a 
  server platform.


CLEANING UP AFTER userregs
--------------------------
After the program ends, follow these steps to clean up:

  1. Open NAMES.NSF on the Notes server specified on the command line.
  2. Switch to the "Server\Certificates" view.
  3. Delete the entries "Sales/ABCorp/US" and "ABCorp/US".
  4. Switch to the "Server/Servers" view.
  5. Delete the entry "OTTO/ABCorp/US".
  6. Switch to the "People" view.
  7. Delete the entry "Doe, Jayne". 
  8. Close NAMES.NSF.
  9. Delete the file "JDOE.NSF" in the mail subdirectory of the Notes
     data directory on the server.
 10. Delete the 2 ID files abcorp.id, absales.id
