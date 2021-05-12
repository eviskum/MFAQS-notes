(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes 
Software Development Kit Agreement (in the apilicns.txt file in the 
notesapi directory of this toolkit), Restricted Rights for U.S. government 
users, and applicable export regulations.
 

PROGRAM
-------
auth_fld  - Example Lotus C API for Domino and Notes Program: Creates items 
	    with data type "Names", "Author Names", and "Reader Names".

PURPOSE
-------
This program demonstrates how to append author fields to documents. It
creates items with data type "Names", "Author Names", and "Reader Names".


ENVIRONMENTS
------------
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
IBM AS/400
Linux RedHat


FILES
-----
readme.txt     - This file. Specifies what is needed to use this example.

maindoc.txt    - An ASCII text file you can specify as <textfile1>
respdoc.txt    - An ASCII text file you can specify as <textfile2>

auth_fld.c     - Source code file.
auth_fld.h     - Header file with declarations and definitions.

os2_32.mak     - Make file for OS/2 (32-bit).

aix.mak        - Make file for IBM AIX.

hp.mak         - Make file for HP HP-UX.

sol_2x.mak     - Make file for Solaris SPARC Edition.

sol_x86.mak    - Make file for Solaris Intel Edition.

as4athmk.bat   - Batch file for IBM AS/400 using Visual Age C++.

as400.mak      - Make file for IBM AS/400 using Visual Age C++.

mk_auth_fl.clp - Make file for IBM AS/400 using the native C compiler.

linux.mak      - Make file for Linux RedHat.


RUNNING auth_fld:
-----------------
Prior to compiling this sample, it is suggested that the line,

  #define READERS1        "CN=Jane Doe/OU=Sales/O=ABCorp"

in the file "auth_fld.h", be modified to reflect your fully canonicalized 
user name.  If this is not done and you specify a database on a Lotus Domino 
server, the sample will run successfully, but the documents created will not 
be visible to you because you will not be listed in the Reader Names field.
 

- Under OS/2 or UNIX (AIX, HP-UX, Linux and Solaris),
  type the following at the system command prompt:

  auth_fld

      or

  auth_fld <server> <database> <textfile1> <textfile2>

where:

   <server> is the Lotus Domino server where the destination database
   resides. This option is required.  You may specify "" for <server> 
   to indicate the database is in the local Domino data directory.

   <database> must specify the name of a Domino discussion database that has
   the design of DISCUSS.NSF (included with the API toolkit).
   Also, the user running this API program must have author access or
   better to this database.

   <textfile1> must name an ASCII text file residing in the current
   working directory. A sample text file, MAINDOC.TXT, is provided in
   this directory for use as <textfile1>. The contents of <texfile1>
   becomes the body of the main topic document. The first line of
   <textfile1> is used as the subject of the main topic document.

   <textfile2> must name another ASCII text file residing in the current
   working directory. A sample text file, RESPDOC.TXT, is provided in
   this directory for use as <textfile2>. The entire contents of <texfile2>
   becomes the body of the response document. The first line of
   <textfile2> is used as the subject of the response.

   If no command line arguments are provided, the program will prompt
   for them.

EXAMPLE
-------

   auth_fld "" discuss maindoc.txt respdoc.txt

under AS/400 -
	change your current directory to your data directory or use absolute paths.
	to change the directory, 

	CD '<data directory>'

	run:  "rundomcmd/rundomcmd server(<server name>) cmd(call 
	       pgm(qntcsdk/auth_fld) parm('' discuss.nsf maindoc.txt respdoc.txt))
	       batch(*no)"

