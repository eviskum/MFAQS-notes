(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
addmacro - Add three macro notes to a database.


ENVIRONMENTS
------------
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

addmacro.c   - Main program.

addmacro.h   - Constants and function prototypes.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.


RUNNING addmacro:
-----------------
This program adds macro notes to the specified target database.
Therefore, before running this program, create a copy of the
target database that does not contain the new macros.  The example
database PROBLEMS.NSF, included with the API kit, does not contain
any macros.  Use OS commands or Notes to create a copy of this
database in the Domino or Notes data directory. Specify this copy
as the target when you run the program.  That way, the original will
remain unchanged.

- Under OS/2 or UNIX (AIX, Solaris, Linux and HP-UX),
  type the following at the system command prompt:

  addmacro <database>

where:

  <database> is the full pathname of the Domino database to be modified.



EXAMPLE
-------

  addmacro problems


CHECKING THE RESULTS
--------------------

This program will print out the following messages:

  addmacro: successfully added 3 macros to 'problems'.

From the Notes user interface, add the icon for the target database
to your desktop.  Open the target database and navigate to the "Main View".

Notice that the view shows several problem tracking documents, all
open, of various levels of priority.

Run the "Transfer Silton to Sherman" Filter macro added by this program by
selecting "Transfer Silton to Sherman" from the Actions Macros menu.  Notice
that the macro runs.  Subsequently, all problems previously assigned to
"Isabel Silton" have been reassigned to "Alexander Sherman".

The macro "Escalate Low Prio Calls to Med" is a weekly scheduled macro.  
To see it work in UI, go to the Designer. Open the problems.nsf - Agent, 
and open this agent.  Change "When should this agent run on Local?" to 
"Manually from Actions Menu" and save it.  Now, you should be able to
see the "Escalate Low Prio Calls to Med" macro from the Actions Macros
menu.  Highlighting this Agent and selecting "Actions - Run" from the 
Notes menu. Notice that the macro runs.  Subsequently, all problem 
tracking documents that were previously low priority have been changed 
to medium.

Before running the Execute-Once macro added by this program, edit one
of the problem tracking documents and enter your own name into the 
field labeled "Support Rep."  This causes the macro to send the email
reminder notification to you.  Press escape and save the modified document.
You should see your own name in the "Support Rep" column of the view.

Make sure the modified document is highlighted. The cursor in the view
is positioned on the document that has your name as the Support Rep.
Select "Send reminder to Support Rep" from the "Actions" menu.  The macro
will run.  The macro will send an email message to you containing
the company name and Subject of the selected problem tracking document.
Check that this message was indeed sent by escaping out of the target
database and checking your Notes email.

