(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
add_res - Resource-based server add-in program.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
OS/2 (32-bit)


FILES
-----
add_res.c    - Main program.

add_res.h    - A local include file, used by both the compiler and the
               resource compiler.

add_res.rc   - The control file for the Windows resource compiler.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Makefile for OS/2 (32-bit).

readme.txt   - This file. Specifies what is needed to use this example.


OPERATING ENVIRONMENT REQUIREMENTS
----------------------------------
The file addintst.nsf, the database in which add_res will create notes,
must reside in the Domino data directory.


RUNNING add_res
--------------- 
1) Copy the executable file for the add-in task to the Domino software
directory. 

2) If the Notes workstation software is running, exit from it. 

3) Start the Lotus Domino Server software.

4) Wait until all server tasks have started - about 30 seconds.

5) Press ENTER to get the server console prompt, >.

6) Load the add-in task by typing

        load add_res

7) The task should immediately print "Add-in Test: Initialization
Complete" to the server console and also to the Domino and Notes log.

8) Confirm that the add-in task is running by typing "show tasks" at the
server console.  You should see the "Add-in Test" task displayed.

