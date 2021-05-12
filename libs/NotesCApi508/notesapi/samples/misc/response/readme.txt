(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
response - Create a main document and two response documents in a database.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
IBM AS/400
Linux RedHat


FILES
-----
readme.txt      -  This file. Specifies how to use this example.

response.c      -  The main program.

mswin32.mak      - Make file for Windows 32-bit.

os2_32.mak       - Make file for OS/2 (32-bit).

aix.mak          - Make file for IBM AIX.

hp.mak           - Make file for HP HP-UX.

sol_2x.mak       - Make file for Solaris SPARC Edition.

sol_x86.mak      - Make file for Solaris Intel Edition.

as4resmk.bat     - Batch file for IBM AS/400 using Visual Age C++.

as400.mak        - Make file for IBM AS/400 using Visual Age C++.

mk_response.clp  - Make file for IBM AS/400 using the native C compiler.
		 
linux.mak        - Make file for Linux RedHat.


RUNNING response:
-----------------
Copy the sample database, "response.nsf", to the Domino or the Notes
data directory on your system.  From the Notes user interface, add 
the database's icon to your Notes workspace.

- Under OS/2, Windows 32-bit or UNIX (AIX, HP-UX, Linux and Solaris):
  type the following at the system command prompt:
 
    response <database filename> <subject text>
	     or
    response
 
    where:
      <database filename> is the filename of the Domino database.
      <subject text> is the subject text string.  

    If no command line arguments are provided, the program will prompt for
    them.

  
  If entering arguments at the prompts instead of at the command line, do 
  not enclose them in quotation marks.


EXAMPLE
-------
    response response "How do you do?"

    - Under AS/400, type:
	rundomcmd/rundomcmd server(<server name>) cmd(call pgm(qntcsdk/response)
	parm(response.nsf 'How are you?')) batch(*no)



CHECKING THE RESULTS
--------------------
From Notes, open the "Response Test Database" (response.nsf).
The second document will be a response to the first document and will have
the subject "A Response to: How do you do?".

The third document will be a response to the second document and will have
the subject "Another Response to: A Response to: How do you do?".

