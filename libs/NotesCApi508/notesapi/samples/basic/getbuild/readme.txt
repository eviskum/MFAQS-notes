(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
getbuild - Gets the Domino or Notes build number using the Lotus C API 
           for Domino and Notes API function NSFDbGetBuildVersion. 


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit) 
OS/2 (32-bit)
HP HP-UX
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
Linux ReadHat


FILES
-----
getbuild.c   - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux RedHat.
          
readme.txt   - This file. Specifies what is needed to use this example.


RUNNING getbuild
----------------
You may run this program against any Domino database.

- Under OS/2, Windows 32-bit or UNIX (Solaris, AIX, Linux 
  and HP-UX) type the following at the system command prompt:
        
        getbuild <database filename>
                or
        getbuild
   
  where:

  <database filename> is the filename of the Domino database to operate on.

  If the database filename is not specified, the program will prompt for it.
 

