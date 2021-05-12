(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
runmacro - Lotus C API for Domino and Notes Sample Program: 
	   Run a macro in a database.


PURPOSE
-------
This shows how to run a filter macro or background macro in a Domino 
database via the API.


ENVIRONMENTS
------------
OS/2 (32-bit)
Windows NT (32-bit)
Windows 95/98 (32-bit)


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

runmacro.c   - Main program.
runmacro.h   - Definitions and function prototypes.

os2_32.mak   - Make file for OS/2 (32-bit).

mswin32.mak  - Make file for Windows 32-bit.


RUNNING runmacro:
-----------------

Before testing runmacro, make sure the target database "Problem Tracking 
(RUNMACRO)" is in the Domino data directory on your system. The file name 
is runmacro.nsf.  This example database contains several macros that you 
can run using runmacro as well as documents that will be processed by 
these macros.  Note that this database also contains several macros that 
can not be run from runmacro.

The example database runmacro.nsf contains the following macros that can 
be run from this program:

  "Transfer Silton to Blanchet"
  "Close all in Main View"
  "Assign Support Rep"
  "Create copy without Company Name"
  "Copy closed problems to Archive"
  "Escalate Low Prio Calls to Med"

From the system command prompt, in the directory for this sample, type 
the following command:

  runmacro <database> <macro>

where:

  <database> is the file name of the database containing the macro
  <macro> is the name of a macro in the database.
  If this argument contains spaces, it must be enclosed in double quotation
  marks.

NOTE: Before running the background macros "Copy closed problems to Archive" 
and "Escalate Low Prio Calls to Med", the design of these macros must be 
updated to set the system where the macro will run. Use the "-s" option of 
runmacro to do this; (using Domino Designer R5 or later will convert the 
macro to an agent.)

To update the system where a macro will run to match the name in the 
currently active user ID file, type the following command at the system 
command prompt:

  runmacro <database> <macro> -s

This change is necessary because background macros contain the name of the
Lotus Domino Server or workstation where that macro will run. The runmacro 
program compares the name of the Lotus Domino Server or workstation 
(stored in the macro note) with the name in the currently active user ID 
file. If these two names are not the same, runmacro prints an error 
message and does not run the macro.


EXAMPLE
-------   

  runmacro runmacro "Transfer Silton to Blanchet"

This program will display the following messages:

  Macro processing completed for 8 documents.


CHECKING THE RESULTS
--------------------
From the Notes user interface, add the icon for the target database
to your desktop.  Open the target database. If the database policy 
(About Problem Tracking) appears, press <escape> to see the main view. 

Notice that the view shows several problem tracking documents,
some open, some closed.  Each problem is assigned to a support 
representative.  Note that after running the macro "Transfer Silton 
to Blanchet" all open problems previously assigned to "Isabel Silton" 
are assigned to "Mario Blanchet".

Use the Notes Design menu to study the design of the other macros 
listed above.  When you understand what change to expect from one
of the supported macros (listed above), run the macro using the API
program.  Note that macro names are case sensitive.  Switch back to the
Notes user interface to see the results of the macro.  You may need to
press F9 to refresh the view in order to see the changes.
