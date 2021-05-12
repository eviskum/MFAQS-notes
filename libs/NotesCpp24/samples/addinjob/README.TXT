Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1997, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
addinjob - Notes C++ API program that demonstrates how to use the 
LNServerAddin and LNMessageQueue classes.  It creates a server add-in
task that periodically updates a database and gets and processes messages
from the Lotus Domino server command console.  It creates a status
line, sets its status, and performs certain operations at specific
time intervals.  The 20-second time interval task looks for any new
messages in the message queue and reports the receipt of each message
as it is read off the queue.  All output is logged in the server's
log.nsf file and also shows up on the console screen.

For more detailed information on creating and using server add-in tasks
and message queues, read the related topics on these subjects
in both the Lotus C++ API and Lotus C API User Guides.

ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
addinjob.cpp - Main program. 

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

addinjob.nsf - Sample Notes database for add-in task output
               (in notedata directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING addinjob
----------------
This sample program runs against a provided database, addinjob.nsf, which 
is used as the server add-in output database file. If you want to run an 
update database job within the server add-in task, copy addinjob.nsf to 
the Notes data directory.

To start addinjob automatically with the Domino server software, 
follow these steps:

1. Make sure the Domino server software is installed on the 
   current machine and the Notes data directory contains a server log file 
   (log.nsf). Either the existing log file may be used or a new one may be 
   created from the Notes Log template.

2. Copy the executable file for the add-in task to the Notes executable 
   directory. Rename the executable so that the name conforms to the
   requirements of the server platform. For details about name
   requirements, see the "About naming conventions" topic for your
   platform in Chapter 2 of the C++ API Toolkit User's Guide. For 
   example, on Microsoft Win32 platforms, rename the executable 
   "naddinjob.exe".

3. Make a backup copy of notes.ini, then open notes.ini for editing 
   and search for the line that begins "ServerTasks=".  This is a 
   comma-delimited list of server tasks that are invoked each time 
   the server is started.

4. Add the name of the add-in task to this list.

5. Save and close notes.ini.

6. If the Notes workstation software is running, exit from it.

7. Start the Domino server software.

8. After the server has completed its startup processing, 
   you can confirm that the add-in task is running by typing 
   "show tasks" at the server console. This will display 
   a list of all server tasks that are running, and the status of each 
   task.


To start the add-in task manually from the server console, follow these 
steps:

1. Make sure your Notes data directory contains a server log file (log.nsf). 
   You can use your existing log file or create a new one from the Notes Log 
   template.

2. Copy the executable file for the add-in task to the Notes executable
   directory.  Rename the executable so that it matches the task name used
   in the LNNotesSession::GetServerAddin call in the code, and prefix the
   name with the character which denotes the server platform (for example,
   'N' for NT).

3. If the Notes workstation software is running, exit from it. 

4. Start the Domino server software. Wait until all server tasks have 
   started - about 30 seconds.

5. Press ENTER to get the server console prompt, >.

6. Load the add-in task by typing:
       load <taskname>
   where taskname is the name of the add-in task.
   For example, from the server console prompt:
       > load ADDINJOB <enter>

7. Confirm that the add-in task is running by typing "show tasks"
   at the server console.

Note: This program should only be started from a Domino server. 
If started on a Domino server, addinjob can be terminated by typing
"tell addinjob quit" or by terminating the server task (typing "quit" in 
the server command window). If addinjob is not started from a Domino server, 
you may need to reboot or log-off the computer to stop it. Under Unix,
you may issue a "kill" command to stop it.
