(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
userreg  - Example Lotus C API for Domino and Notes Program. 
	   Demonstrates user registration functions.


PURPOSE
-------
This program illustrates how to use the User Registration routines to 
register a new hierarchical organizational certifier, organizational unit 
certifier, server, workstation, and recertify a User ID.

First, a new Organization certifier, ABCorp, is created. The password in 
the certifier ID is set to "abcorp". Then, a new Organization Unit certifier, 
Sales, is created. This certifier is a descendent of the Organization 
certifier. Then, a new server, OTTO, is registered and certified with the 
Organization certifier.  A new user, Jayne Doe is registered and 
certified with the Organization Unit certifier and then is recertified with
the Organization Unit certifier. 

The entries for the Organization certifier, Organization Unit certifier, 
new server, and new user are then looked up in the Domino Directory (Server's wAddress book) 
and their Note IDs are printed out.


ENVIRONMENTS
------------
OS/2 (32-bit)
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
IBM AS/400
Linux RedHat


FILES
-----
readme.txt     -  This file. Specifies what is needed to use this example.

userreg.c      -  Main program.

os2_32.mak     - Make file for OS/2 (32-bit).

hp.mak         - Make file for HP HP-UX.

sol_2x.mak     - Make file for Solaris SPARC Edition.

sol_x86.mak    - Make file for Solaris Intel Edition.

as4usrmk.bat   - Batch file for IBM AS/400 using Visual Age C++.

as400.mak      - Make file for IBM AS/400 using Visual Age C++.

mk_userreg.clp - Make file for IBM AS/400 using the native C compiler.

linux.mak      - Make file for Linux RedHat.


RUNNING userreg
---------------

- Under OS/2 or UNIX (HP-UX, Linux and Solaris), type the following at
  the system command prompt:

	userreg  <Full server name>
	       or
	userreg

  where:

      <Full server name> is the name of the Lotus Domino Server with which
      you would like to register your new hierarchical organizational
      certifier, organizational unit certifier, server, and a workstation.

      if no server name is supplied the program assumes the Lotus Domino
      Server is a local server.

- Under AS/400 - type:
	rundomcmd/rundomcmd server(<server name>) cmd(call
		pgm(<AS/400 api library>/userreg)) BATCH(*NO)

This program creates four ID files. If this program is run under
OS/2, these ID files are written to disk A:.  Therefore, you should
insert a formatted diskette in drive A: before running this program
under OS/2. 

If you are running this program under Unix, the ID files are written 
to /tmp.

If you are running this program under AS/400, the files are written 
to the default data directory.

For each ID created, this also creates new entries in the Domino 
Directory of the server specified on the command line. Therefore, 
you must have author access to the Domino Directory on the server 
specified on the command line in order for this program to succeed.
When the new user, Jane Doe is registered, a mail file is created.

Status messages will be printed to the screen during registration.

This program opens the Domino Directory on the server, locates 
the newly created entries, and prints the note IDs of these new 
entries. 


Cleaning Up After userreg
-------------------------
After this program ends, follow these steps to clean up:

  1. Open the Domino Directory on the Lotus Domino Server specified on
     the command line (or local server name).

  2. Switch to the view, "Server\Certificates".

  3. Delete the entries "Sales/ABCorp/US" and "ABCorp/US".

  4. Switch to the view, "Server/Servers".

  5. Delete the entry, "OTTO/ABCorp/US".

  6. Switch to the view, "People".

  7. Delete the entry, "Doe, Jayne". 

  8. Close the Domino Directory.

  9. Delete the file "jdoe.nsf" in the "mail" subdirectory of the Notes
     data directory on the server.

 10. Delete the ID files abcorp.id, absales.id, otto.id, and jdoe.id.
