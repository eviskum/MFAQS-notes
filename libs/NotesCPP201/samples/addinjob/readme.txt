(c) 1997, 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.

PROGRAM
-------
addinjob - Notes C++ API program that demonstrates how to use the 
LNServerAddin class to create a server add-in task to periodically 
update a database. It creates a status line and sets its status, then 
performs certain operations at specific time intervals. It also ouputs the 
status line text and the add-in task name to the server log.nsf file.

ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition


FILES
-----
addinjob.cpp - Main program. 

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and
	       Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
	       IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
	       Borland C++ 5.0 for Windows.

os2_32.mak   - Make file OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

addinjob.nsf - Sample Notes database for add-in task output
               (in NOTEDATA directory).

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING addinjob
----------------
This sample program runs against a provided database, addinjob.nsf, which 
is used as the server add-in output database file. If you want to run a 
update database job within the server add-in task, copy addinjob.nsf to 
the Notes data directory.

To start addinjob automatically with the Notes server software, 
follow these steps:

1. Make sure the Notes server software is installed on the 
   current machine and the Notes data directory contains a server log file 
   (log.nsf). Either the existing log file may be used or a new one may be 
   created from the Notes Log template.
2. Copy the executable file for the add-in task to the Notes executable 
   directory.  
3. Make a backup copy of notes.ini, then open notes.ini for editing 
   and search for the line that begins "ServerTasks=".  This is a 
   comma-delimited list of server tasks that are invoked each time 
   the server is started.
4. Add the name of the add-in task to this list.
5. Save and close notes.ini.
6. If the Notes workstation software is running, exit from it.
7. Start the Notes server software.
8. After the Notes server has completed its startup processing, 
   you can confirm that the add-in task is running by typing 
   "show tasks" at the Notes server console. This will display 
   a list of all server tasks that are running, and the status of each 
   task.


To start the add-in task manually from the server console, follow these 
steps:

1. Make sure your Notes data directory contains a server log file (log.nsf). 
   You can use your existing log file or create a new one from the Notes Log 
   template.
2. Copy the executable file for the add-in task to the Notes executable
   directory. 
3. If the Notes workstation software is running, exit from it. 
4. Start the Notes server software. Wait until all server tasks have 
   started - about 30 seconds.
5. Press ENTER to get the Notes Server console prompt, >.
6. Load the add-in task by typing
       load <taskname>
   where taskname is the name of the add-in task.

   Note: The Notes server expects add-in task names to have a first character
   which denotes the server platform ('N' for NT, 'I' for OS/2, etc.).
   If you are explicitly loading your add-in task FROM ANY DIRECTORY OTHER
   THAN THE NOTES SERVER DIRECTORY you will have to rename 'addinjob.exe' 
   so that it is pre-fixed with the appropriate platform-specific character.
   You will also need to qualify the taskname with the full path name. 
   (So, for example, if you are running on Win32, you could rename the
   'addinjob.exe' file to 'nmyaddin.exe' and enter "ServerTasks=myaddin" in
   the Notes.ini file.)

7. Confirm that the add-in task is running by typing "show tasks"
   at the server console.

Note: This program should only be started from a Notes server. 
If started on a Notes server, addinjob can be terminated by typing
"tell addinjob quit" or by terminating the server task (typing "quit" in 
the server command window). If addinjob is not started from a Notes server, 
you may need to reboot the computer to stop it. Under Unix, you may issue 
a "kill" command to stop it.
