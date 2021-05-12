(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
sel_rep   - Sample Lotus C API for Domino and Notes Program: 
            Create a replication formula note.


ENVIRONMENTS
------------
Windows NT (32-bit) (not including DEC Alpha)
Windows 95/98


PURPOSE
-------
This program shows how to create a replication formula note. A replication 
formula note allows a database to perform selective replication.


FILES
-----
readme.txt  - This file.

sel_rep.c   - Main program.

sel_rep.h   - Contains symbolic definitions used by the main program.

mswin32.mak - Make file for Windows 32-bit.


RUNNING sel_rep
---------------
This sample program uses the Domino database, reptest.nsf, provided with
the Lotus C API for Domino and Notes toolkit.  You must copy this file to 
the Domino data directory on a Lotus Domino Server. 

Next, edit the source code file "sel_rep.c" and change the string defined 
in szServerName[] to the name of the server on which "reptest.nsf" was 
stored. Build the program executable.
   
- Under Windows 32-bit, from your Notes workstation type:
         sel_rep
  at the system prompt. The program takes no arguments.
  
sel_rep will create on the local workstation a replica copy of reptest.nsf. 
It will then create in the local copy of the database a replication
formula.
       
        
CHECKING THE RESULTS
-------------------- 
To check that the program worked properly:

Add the server database and local database to your workstation.
On the server copy of the database, use form 1 to create several documents. 
Create some documents with numberfield greater than 100 and some with 
numberfield less than 100.  On the workstation, open the local copy of 
the database, and force it to replicate with the server copy by choosing 
the menu item, File/Replication/Replicate.  Then choose Replicate with 
options.  Choose OK.  Check to make sure that the name of the server 
containing the database is specified.  Choose OK.  When Notes has finished 
replicating, press F9 to refresh the local copy of the database. The 
documents with values less than 100 in numberfield will have been 
replicated from the server copy to the local copy. 

