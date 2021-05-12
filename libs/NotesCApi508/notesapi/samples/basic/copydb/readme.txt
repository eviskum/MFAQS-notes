(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
copydb - Creates a replica copy of a Domino database and sets the title.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat 

FILES
-----
copydb.c     - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING copydb
--------------
- Under OS/2, Windows 32-bit or UNIX (AIX, HP-UX, Solaris and Linux),
  type the following at the system command prompt:

         copydb  <input db>  <output db>  <output title>
                          or
         copydb

  where:

  <input db> is the filename of the Domino database to be copied

  <output db> is the filename of the resulting copy of the Domino database

  <output title> is the title of the resulting Domino database

  If no command line arguments are typed, then you will be prompted
  to enter them.


EXAMPLE:

      copydb  simple  simple2  "Copy of Simple"



CHECKING THE RESULT
-------------------
To see if copydb worked correctly:

From Notes, add the icon for the input database to your desktop. Open the
database and examine the contents.

Do the same for the output database. 

The icons, forms, views, and data notes of the two databases should be
identical. Only the title should be different.

