(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
allflds - Finds all the fields in all the documents in a database.


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
allflds.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

hp.mak       - Make file for HP HP-UX.               

sol_2x.mak   - Make file for Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.            

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING allflds
---------------
This sample program will run against the Domino database simple.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  You must copy 
this file to the Domino or Notes data directory before running this program.


- Under OS/2, Windows 32-bit, or UNIX (Solaris, AIX, HP-UX and Linux),
  type:
       allflds
  at the system command prompt.

The program should print output that looks like this:

Note ID is: 8F6.                                                 
Found field named "Form" with data type "Text".                   
Found field named "plain_text" with data type "Text".             
Found field named "number" with data type "Number".               
Found field named "time_date" with data type "Time/Date".         
Found field named "text_list" with data type "Multi-Value Text".  
                                                                 
Note ID is: 8FA.                                                 
Found field named "Form" with data type "Text".                   
Found field named "plain_text" with data type "Text".             
Found field named "number" with data type "Number".               
Found field named "time_date" with data type "Time/Date".         
Found field named "text_list" with data type "Multi-Value Text".  
                                                                 
Note ID is: 8FE.                                                 
Found field named "Form" with data type "Text".                   
Found field named "plain_text" with data type "Text".             
Found field named "number" with data type "Number".               
Found field named "time_date" with data type "Time/Date".         
Found field named "text_list" with data type "Multi-Value Text".  

