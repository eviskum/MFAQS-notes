(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
THREADS - Text-based multithreaded server add-in task. Periodically writes
          and reads a database via multiple threads.

PURPOSE
-------
This is a sample multithreaded Lotus Domino Server add-in task.  It creates a 
status line and sets its status, then starts three worker threads that 
perform certain operations at specific time intervals. The main thread
communicates with the worker threads through Message Queues and tells the
threads when to perform their operations and when to terminate.
THREADS uses basic synchronization and file locking schemes to ensure that
all operations are performed to completion and without error.

This sample is designed for portability to platform such as 
Unix. This sample differs from comparable OS/2 and Windows 
samples in that it does not use a string table. A string table is a 
resource that requires a resource compiler, normally only available under 
OS/2 and Windows.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
OS/2 (32-bit)
HP HP-UX
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
IBM S/390
Linux RedHat


FILES
-----
threads.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Makefile for OS/2 (32-bit).

hp.mak       - Makefile for HP HP-UX.

aix.mak      - Makefile for IBM AIX.

sol_2x.mak   - Makefile for Solaris SPARC Edition.

sol_x86.mak  - Makefile for Solaris Intel Edition.

os390.mak    - Makefile for IBM S/390.

linux.mak    - Makefile for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.

 
OPERATING ENVIRONMENT REQUIREMENTS
----------------------------------
The file threads.nsf, the database in which THREADS will create notes,
must reside in the Domino data directory.  


STARTING THE ADD-IN AUTOMATICALLY WHEN SERVER STARTS
----------------------------------------------------
To start THREADS automatically with the Lotus Domino Server software, 
follow these steps:    

1) Make sure the Lotus Domino Server software is installed on the 
current machine and the Domino data directory contains a Lotus Domino 
Server log file (log.nsf). 
Either the existing log file may be used or a new one may be created from 
the Domino and Notes Log template.

2) Copy the executable file for the add-in task to the Domino program 
directory:

     For 32-bit Windows (NT) 
         the executable file name is nthreads.exe 

     For 32-bit Windows (DEC Alpha NT) 
         the executable file name is athreads.exe 

     For OS/2 (32-bit) 
         the executable file name is ithreads.exe

     For all UNIX platforms 
         the executable file name is threads

3) Make a backup copy of notes.ini, then open notes.ini for editing, and 
search for the line that begins "ServerTasks=".  This is a comma-delimited 
list of server tasks that are invoked each time the server is started.

4) Add the name of the add-in task (threads) to this list.

5) Close notes.ini, saving the changes that were made.

6) If the Notes workstation software is running, exit from it.

7) Start the Lotus Domino Server software.

8) After the Lotus Domino Server has completed its startup processing, 
the user may confirm that the add-in task is running by typing "show tasks" 
at the Lotus Domino Server console. This will display a list of all server 
tasks that are running, and the status of each task.  You should see a 
"Sample Multithreaded Addin" task listed.


STARTING THE ADD-IN MANUALLY
----------------------------
To start the add-in task manually from the server console, follow these 
steps:

1) Make sure your Domino data directory contains a Lotus Domino Server log  
file (log.nsf). You can use your existing log file or create a new one from 
the Domino and Notes Log template.

2) Copy the executable file for the add-in task to the Domino program 
directory:

     For 32 bit Windows (NT) 
         the executable file name is nthreads.exe 

     For 32 bit Windows (DEC Alpha NT) 
         the executable file name is athreads.exe 

     For OS/2 (32-bit) 
         the executable file name is ithreads.exe

     For all UNIX platforms 
         the executable file name is threads

3) If the Notes workstation software is running, exit from it. 

4) Start the Lotus Domino Server software.
Wait until all server tasks have started - about 30 seconds.

5) Press ENTER to get the Lotus Domino Server console prompt, >.

6) Load the add-in task by typing

        load threads

7) Confirm that the add-in task is running by typing "show tasks" at the 
server console. You should see a "Sample Multithreaded Addin" task listed.

Note: This program should only be started from a Lotus Domino Server. If 
      started on a Lotus Domino Server, THREADS may be terminated by 
      terminating the server task (typing "quit" in the server command 
      window). If THREADS is not started from a Lotus Domino Server you 
      may need to reboot the computer to stop it.


VALIDATING THE OPERATION OF THE ADD-IN
--------------------------------------
THREADS uses three worker threads to perform operations against the sample
database.  Specifically, 
     one thread writes a note to the database every 30 seconds, 
     another thread writes a note to the database every minute, and 
     the third thread reads and displays the notes in the database 
         every other minute.  
As THREADS runs, you should see console messages illustrating this
behavior.  

After six 30-second, three 1-minute, and two 2-minute operations,
THREADS will end the three threads and terminate.  You can then open up the
sample database and validate the written notes using the AddInView view.

Since THREADS illustrates a well behaved Notes addin task, you can validate
user invoked termination by either typing 

        tell threads quit

at the Lotus Domino Server console, or by exiting the Lotus Domino Server 
during execution of the sample.  You should see relevent thread 
termination messages prior to termination of the addin task or server.  
These messages mean the threads are no longer running on the server.
