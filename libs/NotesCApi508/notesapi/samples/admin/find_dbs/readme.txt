(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory of
this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
find_dbs - Lotus C API for Domino and Notes Sample Program: List all Domino 
           Databases in a directory.  Also lists sub directories.


PURPOSE
-------
This program finds all databases and subdirectories contained in a 
specified directory, and prints out the summary information for each 
database. 


ENVIRONMENTS
------------
OS/2 (32-bit)
Power Macintosh
IBM AS/400

FILES
-----
readme.txt     - This file. Specifies what is needed to use this example.

find_dbs.c     - Main program.

os2_32.mak     - Make file for OS/2 (32-bit).

as4fdbmak.bat  - Batch file for IBM AS/400 using Visual Age C++.

as400.mak      - Make file for IBM AS/400 using Visual Age C++.

mk_find_db.clp - Make file for IBM AS/400 using the native C compiler.


RUNNING find_dbs:
-----------------
- Under OS/2:
  type the following at the system command prompt:

  find_dbs <server> <directory>

- Under Macintosh
  Double click on the application icon and you will be prompted for the server 
  and directory information.

- Under AS/400:
  run:  rundomcmd/rundomcmd server(<server>) cmd(call pgm(qntcsdk/find_dbs)
	        parm('' <data directory>)) batch(*no)

where:

  <server> is the name of the Lotus Domino Server to be searched.
  To specify that the subdirectory to be searched is on the local machine,
  type two double quotes ("") in place of a server name.

  <directory> is the subdirectory to be searched.
  To specify that the Domino or Notes default data directory is to be searched,
  type two double quotes ("") in place of a directory name. 

EXAMPLE
-------

  find_dbs server1 notedata

Find_dbs finds all databases and subdirectories of the "notedata" 
directory on the Lotus Domino Server "server1", and prints the summary 
information for each.

