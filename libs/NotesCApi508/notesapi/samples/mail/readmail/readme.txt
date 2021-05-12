(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
readmail    -  print the contents of a message (mail) file


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris Intel Edition
Solaris SPARC Edition
IBM AS/400
Linux RedHat


FILES
-----
readmail.c     - C source file for the program

mswin32.mak    - Make file for Windows 32-bit.

os2_32.mak     - Make file for OS/2 (32-bit).

aix.mak        - Make file for IBM AIX.

hp.mak         - Make file for HP HP-UX.

sol_x86.mak    - Make file for Solaris Intel Edition.

sol_2x.mak     - Make file for Solaris SPARC Edition.

as4rmlmk.bat   - Batch file for IBM AS/400 using Visual Age C++.

as400.mak      - Make file for IBM AS/400 using Visual Age C++.

mk_readmai.clp - Make file for IBM AS/400 using the native C compiler.

linux.mak      - Make file for Linux RedHat.

readme.txt     - This file. Documents READMAIL and provides example.


RUNNING readmail
----------------
  This sample program prints the entire contents of a Domino message file 
  to the screen.  Therefore, it might be desirable to test it on the small 
  message file hfinn.nsf included in the API toolkit. You must copy this 
  file to the Domino or Notes data directory before running this
  program.
   
   - Under OS/2, Windows 32-bit or UNIX (AIX, HP-UX, Linux and Solaris),
    type the following at the system command prompt:

	 readmail  <server>  <database>  
			  or
	 readmail

   - Under OS/400, type:
	rundomcmd/rundomcmd server(<server name>) cmd(call pgm(qntcsdk/readmail)
	parm(server database)) batch(*no)

  where:

  <server> is the name of the Domino mail server

  <database> is the filename of the Domino mail database

  If no command line arguments are typed, then you will be prompted
  to enter them.  If entering arguments at the prompts instead of at the
  command line, do not enclose your responses in quotation marks.


EXAMPLE:

    readmail  ""  "hfinn"

    Under OS/400, type:
	rundomcmd/rundomcmd server(<server name>) cmd(call pgm(qntcsdk/readmail)
	parm('' hfinn.nsf)) batch(*no)
    
    The empty quotes signify that the database resides on the local 
    machine in the Domino or Notes data directory.


CHECKING THE RESULT
--------------------        
    Note: All messages within a User's mail file will be returned 
	  (this includes inbox messages, sent messages, draft messages, 
	  etc.).  Only messages which were actually sent will have a 
	  recipient list.

    If you run the program against the hfinn.nsf database, it should 
    display something similar to the following:

    Mail file contains 1 message(s).

    Message #1: 
	    Originator = 'Martin Cox'
	    Number of Recipients = 1.
		    Recipient 1 = 'Charles Connell'  Domain = 'Lotus'
	    To: Charles Connell
	    Cc: Donna Amaral,Mark Yuska,Mark Wallace
	    From: Martin Cox
	    Date: 04/12/1992 04:31:17 PM
	    Subject: Re: APISUPP.NSF Stub attached
	    Body:
		    Attached please find the replica stub o
		    f the Notes API Support database 

		    (APISUPP.NSF).
	    Attachment 1 = 'APISUPP.NSF'

    Program completed successfully.
