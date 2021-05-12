(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
rsimple - Read & display database fields.


PURPOSE:      
-------       
This program is an introductory Lotus C API for Domino and Notes program 
that opens a Domino database and searches for all the data notes. It opens 
and reads each data note, and displays the fields and their names.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
IBM S/390
Linux RedHat


FILES
-----
rsimple.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

os390.mak    - Make file for IBM S/390.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING rsimple:
----------------
This sample program is designed to run against the Domino database, 
simple.nsf, provided with the Lotus C API for Domino and Notes toolkit.  
You must copy this file to the Domino or Notes data directory before
running this program.


- Under OS/2, Windows 32-bit, or UNIX (AIX, HP-UX, Solaris, Linux, 
  and S/390), type the following at the system command prompt:
  
        rsimple simple.nsf
               or
        rsimple



EXAMPLE:

      rsimple  simple.nsf


If the program runs correctly, it should display something similar to the
following:

----------------------------------------------------------------------------

Note ID is: 8FE.                                                     
PLAIN_TEXT field is: The quick brown fox jumped over the lazy dogs.   
NUMBER field is: 125.007000                                              
TIME_DATE field is: 07/14/1993 03:14:44 PM                              
The last entry in TEXT_LIST is: Chuck                                 
                                                                     
Note ID is: 8F6.                                                     
PLAIN_TEXT field is: This is a line of simple text.                   
NUMBER field is: 0.000987                                             
TIME_DATE field is: 01/15/1988                                          
The last entry in TEXT_LIST is: four                                  
                                                                     
Note ID is: 8FA.                                                     
PLAIN_TEXT field is: This is another line of simple text.             
NUMBER field is: 836.000000                                                  
TIME_DATE field is: 07/04/1953 07:12:00 AM                              
The last entry in TEXT_LIST is: d                                     

-------------------------------------------------------------------------------


CHECKING THE RESULTS
--------------------

To see if rsimple worked correctly:

Open simple.nsf.

Double click on the documents to open them and check to see if the values in
the respective fields agree with what Notes displays.  Then, to see if the
names of the fields displayed agree with Notes, use File/Document Properties
to see the names of the fields.

