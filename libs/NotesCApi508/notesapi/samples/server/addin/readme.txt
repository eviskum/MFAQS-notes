(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
addin - Text-based server add-in task. Periodically updates a database.


PURPOSE
-------
This is a sample Lotus Domino Server add-in task.  It creates a status line
and sets its status, then performs certain operations at specific time 
intervals. 

This sample is designed for portability to platform such as Unix. 
This sample differs from comparable OS/2 and Windows samples in that 
it does not use a string table. A string table is a resource that 
requires a resource compiler, normally only available under OS/2 and 
Windows.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
IBM AIX
HP HP-UX
IBM S/390
IBM AS/400
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat

FILES
-----
addin.c      - Main program.

mswin32.mak  - Make file for Windows 32-bit.

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris 2 SPARC Edition.

sol_x86.mak  - Make file for Solaris 2 Intel Edition.

os390.mak    - Make file for IBM S/390.

as4addmk.bat - Batch file for IBM AS/400 using Visual Age C++.

as400.mak    - Make file for IBM AS/400 using Visual Age C++.

mk_addin.clp - Make file for IBM AS/400 using the native C compiler.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.

 
OPERATING ENVIRONMENT REQUIREMENTS
----------------------------------
The file addintst.nsf, the database in which addin will create notes,
must reside in the Domino data directory.


STARTING THE ADD-IN AUTOMATICALLY WHEN SERVER STARTS
----------------------------------------------------
To start addin automatically with the Lotus Domino Server software, 
follow these steps:

1) Make sure the Lotus Domino Server software is installed on the 
current machine and the Domino data directory contains a Lotus Domino 
Server log file (log.nsf). 
Either the existing log file may be used or a new one may be created from 
the Domino and Notes Log template.

2) Copy the executable file for the add-in task to the Domino software 
directory.

3) Make a backup copy of Domino server's notes.ini file, then open the
Domino server's notes.ini file for editing, and search for the line that 
begins "ServerTasks=".  This is a comma-delimited list of server tasks 
that are invoked each time the server is started.

4) Add the name of the add-in task to this list.

5) Close notes.ini, saving the changes that were made.

6) If the Notes workstation software is running, exit from it.

7) Start the Lotus Domino Server software.

8) After the Lotus Domino Server has completed its startup processing, 
the user may confirm that the add-in task is running by typing 
"show tasks" at the Lotus Domino Server console. This will display a 
list of all server tasks that are running, and the status of each task.
You should see the "Sample Addin" task displayed.


STARTING AN ADD-IN MANUALLY
---------------------------

To start the add-in task manually from the server console, follow these 
steps:

1) Make sure your Domino data directory contains a Lotus Domino Server 
log file (log.nsf). You can use your existing log file or create a 
new one from the Domino and Notes Log template.

2) Copy the executable file for the add-in task to the Domino software
directory. 

3) If the Notes workstation software is running, exit from it. 

4) Start the Lotus Domino Server software.
Wait until all server tasks have started - about 30 seconds.

5) Press ENTER to get the Lotus Domino Server console prompt, >.

6) Load the add-in task by typing

        load addin

7) Confirm that the add-in task is running by typing "show tasks" at the 
server console.

Note: This program should only be started from a Lotus Domino Server. 
      If started on a Lotus Domino Server, addin may be terminated by 
      telling the task to "quit" (type "tell addin quit" in the server 
      command window). If addin is not started from a Lotus Domino Server 
      you may need to reboot the computer to stop it.  Under Unix, you 
      may issue a "kill" command to stop it.

Note: Starting an addin manually under OS/400 is not recommended because 
      the only way to stop it is by ending its process.  See the 
      Lotus C API User Guide for more detail on running addins.


VALIDATING THE OPERATION OF ADDIN
---------------------------------
Every 20 seconds, the add-in task displays the following message at the 
server console:

      add-in Test: 20-second job complete.


Every 2 minutes, the add-in task displays the following message at the
server console:

      add-in Test: Two-minute job complete.
