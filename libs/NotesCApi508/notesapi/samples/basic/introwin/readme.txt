(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
introwin - Displays the database title.


PURPOSE
-------
This program is an introductory Lotus C API for Domino and Notes program 
that opens a Domino database and displays the title.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)


FILES
-----
introwin.c   - Main program.
introwin.h   - Local function prototypes and data definitions.
introwin.def - Windows definition file for this example.
introwin.rc  - Resource compiler file for this example.
mswin32.mak  - Make file for Windows 32-bit.
readme.txt   - This file. Specifies what is needed to use this example.
 

IDENTIFY A TEST DATABASE:
-------------------------

Determine the name of a Domino database file, such as intro.nsf, that
resides in the Domino or Notes data directory on your system. Introwin 
will work with any valid Domino database file.


RUNNING introwin:
-----------------

To run this program from Windows 32-bit, type, introwin, at the   
command prompt in the program's build directory.  The INTROWIN main window 
appears.  Choose Get Database Title from INTROWIN's File menu.  The dialog 
box displayed will prompt for the filename of a database. Enter the 
filename of any Domino database in the workstation's local data 
directory, such as, intro.nsf.  INTROWIN will open the specified database, 
read the database information, and display the database title in a message 
box.

