Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1997, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


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
new server, and new user are placed in the server's names.nsf.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
userregs.cpp - Main program. 

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING userregs
----------------
This sample program runs on the Domino server and creates two ID files. 
If you run this program under Windows, these ID files are written to 
disk A:.  Therefore, you should insert a formatted diskette in drive A: 
before running this program under Windows.  During execution, you will
be prompted for a password in order to complete registration of the user.

If you run this program under UNIX, the ID files are written 
to /tmp.

For each ID created, this program creates new entries in names.nsf
on the server specified on the command line. Therefore, you must have author 
access to that database. When the new user is registered, a mail file is 
created.

To run this program, type the following at the system command prompt:

        userregs  <Full server name>

where <Full server name> is the name of the Domino server with which you 
would like to register your new hierarchical organizational certifier, 
organizational unit certifier, server, and workstation.

The program displays the following message:

The ID file being used is: OU=Sales/O=ABCorp/C=US

You are then prompted for a password. Enter "password" and press Enter.


CHECKING THE RESULTS
--------------------
To see if the program worked:

  1. Open names.nsf on the Domino server specified on the command line.
  2. Switch to the "Server\Certificates" view.
  3. Under "NotesCertifiers", go to "/ABCorp/US".
  4. Check that the view displays the new entries "Sales/ABCorp/US"
     and "ABCorp/US".
  5. Switch to the "Server/Servers" view.
  6. Under ABC, check that the view displays the new entry
     "OTTO/ABCorp/US".
  7. Switch to the "People" view.
  8. Under ABCorp, check that the view displays the new entry 
     "Doe, Jayne". 
  9. Check the new file "jdoe.nsf" exists in the mail subdirectory of
     the Notes data directory on the server.
 10. Check for the 2 new ID files, abcorp.id and absales.id (on drive
     A: under Windows, in /tmp under UNIX).


CLEANING UP AFTER userregs
--------------------------
After the program ends, follow these steps to clean up:

  1. Open names.nsf on the Domino server specified on the command line.
  2. Switch to the "Server\Certificates" view.
  3. Under "NotesCertifiers", go to "/ABCorp/US".
  4. Delete the entries "Sales/ABCorp/US" and "ABCorp/US".
  5. Switch to the "Server/Servers" view.
  6. Under ABC, delete the entry "OTTO/ABCorp/US".
  7. Switch to the "People" view.
  8. Under ABCorp, delete the entry "Doe, Jayne". 
  9. Close names.nsf.
 10. Delete the file "jdoe.nsf" in the mail subdirectory of the Notes
     data directory on the server.
 11. Delete the two ID files, abcorp.id and absales.id.
