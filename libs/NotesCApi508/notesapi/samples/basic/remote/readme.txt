(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
remote - Opens a database that resides on a server and displays the
         database title


PURPOSE
-------       
This program is an introductory Lotus C API for Domino and Notes program 
that opens a database on a server and displays the title.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
HP HP-UX
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
remote.c     - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING remote
--------------
First determine what server name and database filename you will use.
You can use the Notes UI to determine this information.  In the Notes 
UI, choose File/Database/Open.  A list of Lotus Domino Servers
visible to your workstation is displayed.  Selecting a server causes 
Notes to display a list of the titles of databases available on the 
selected server.  Highlighting one database title causes Notes to 
display the filename of that database.  Use one of the servers
visible to your workstation as the server name.  Use one of the file names
of a database available on that server as the database name.

- Under OS/2, Windows 32-bit or UNIX (Solaris, AIX, Linux, or HP-UX) type
  the following at the system command prompt:
  
        remote  <server name> <database filename>
                  or
        remote

  If either the server name or database filename is not specified, 
  the program will prompt for them.


EXAMPLE:

      remote  

If the program runs correctly, it displays the title of the specified
database.  For example, if a database with the title, Address 
Book is specified, the following will be displayed:
---------------------------------------------------------------------------

The title of this database is: Address Book

---------------------------------------------------------------------------



EXAMINING THE DOMINO DATABASE TO CHECK THE RESULT
-------------------------------------------------

To see if remote worked correctly:

Open names.nsf on the Domino server.

Choose File/Database/Properties...

Examine the text box labeled "Title:".

