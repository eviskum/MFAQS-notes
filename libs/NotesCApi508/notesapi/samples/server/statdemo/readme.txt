(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
statdemo  - Lotus C API for Domino and Notes Sample Program: 
            Query and update Server statistics


ENVIRONMENTS
------------
OS/2 (32-bit)
IBM S/390


PURPOSE
-------
This Domino Server Add-In program uses the Lotus C API for Domino and Notes 
statistics reporting routines to periodically query the Lotus Domino Server 
for statistics information.  Then it updates a database (statdemo.nsf) with 
the information gathered.


FILES
-----
statdemo.c   - Main program.

statdemo.rc  - Resource file for this sample program.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for IBM S/390.

readme.txt   - This file. Specifies what is needed to use this example.


STARTING THE ADD-IN AUTOMATICALLY WHEN SERVER STARTS
----------------------------------------------------
The file, statdemo.nsf, the database in which this add-in task will 
create notes, must reside in the Domino data directory.

- Under OS/2, the add-in task filename is istatdem.exe. 

To start statdemo automatically with the Lotus Domino Server software, follow 
these steps:

1) Make sure the Lotus Domino Server software is installed on the current 
machine and the Domino data directory contains a Lotus Domino Server log 
file (log.nsf).  Either the existing log file may be used or a new one may 
be created from the Domino and Notes Log template.

2) Copy the executable file for the add-in task to the Domino program
directory. 

3) Make a backup copy of notes.ini, then open notes.ini for editing, and
search for the line that begins "ServerTasks=".  This is a comma-delimited
list of server tasks that are invoked each time the server is started.

4) Add the name of the add-in task to this list, omitting the file's
extension.  For OS/2, also omit the leading character, i.

5) Close notes.ini, saving the changes that were made.

6) If the Notes workstation software is running, exit from it.

7) Start the Lotus Domino Server software.

8) After the Lotus Domino Server has completed its startup processing, the 
user may confirm that the add-in task is running by typing "show tasks" at 
the Lotus Domino Server console. This will display a list of all server tasks 
that are running, and the status of each task.


STARTING AN ADD-IN MANUALLY
---------------------------

To start the add-in task manually from the server console, follow these 
steps:

1) Make sure your Domino data directory contains a Lotus Domino Server log  
file (log.nsf). You can use your existing log file or create a new one from
the Domino and Notes Log template.

2) Copy the executable file for the add-in task to the Domino program
directory. 

3) If the Notes workstation software is running, exit from it. 

4) Start the Lotus Domino Server software.
Wait until all server tasks have started - about 30 seconds.

5) Press ENTER to get the Lotus Domino Server console prompt, >.

6) For OS/2, load the add-in task by typing

        load statdem

   For S/390, load the add-in task by typing

        load statdemo


7) Confirm that the add-in task is running by typing "show tasks" at the
server console.

Note: This program should only be started on a Lotus Domino Server.  If 
statdemo is not started from a Lotus Domino Server you may need to reboot 
the computer, to stop it.
