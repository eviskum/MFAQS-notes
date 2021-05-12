(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
extmngr - Example Extension Manager

This program registers and deregisters all of the Extension Manager
functions to show how they interact in an application and transforms
a non Domino database "animals.db" into a Domino database "animals.nsf"
when specific extension manager hooks are called.  

When the program traps an EM_NSFDBCREATE and EM_NSFDBCLOSE hook for the 
Database "animals.nsf", the data in the database is built from an the 
existing file "animals.db" containing information and transformed into a 
Domino Database. The extension manager hooks are deregistered when Domino or 
Notes is exited.  The log file OUTPUT.LOG, tracks extension manager calls 
and is created in the Domino or Notes data directory.


ENVIRONMENTS
------------
OS/2 (32-bit)
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
Power Macintosh


FILES
-----
extmngr.c    - Main C source code file for Extension Manager
cdrecord.c   - Source code needed for creating cdrecords.
createdb.c   - Source code needed for creating forms, notes, 
               and views in database.
extmngr.h    - Constants and function prototypes.
animals.db   - Non Notes database.

os2_32.mak   - Make file for OS/2 32-bit.
os2_32.def   - Module definition file for OS/2 32-bit.

mswin32.mak  - Make file for Windows 32-bit (including DEC Alpha).
mswin32.def  - Module definition file for Windows 32-bit.
mswin32a.def - Module definition file for DEC Alpha NT 32-bit.

extppc.r     - Resources for the Power PC version

extmngr.exp  - Exports for the Power PC

readme.txt   - This file. Specifies what is needed to use this example.


OPERATING ENVIRONMENT REQUIREMENTS
----------------------------------
To install and run this program:

    1.  Exit Domino or Notes if it is running.

    2.  For OS/2, copy IEXTMNGR.DLL to the Domino program directory.

    For Windows NT or Windows 95/98, copy NEXTMNGR.DLL to the Domino
    or Notes program directory.

    For Windows NT on DEC Alpha, copy AEXTMNGR.DLL to the Domino
    program directory.

    3.  Edit the notes.ini file.
        If an EXTMGR_ADDINS entry does not exist, 

    For OS/2, add the line:

        EXTMGR_ADDINS=IEXTMNGR

    For Windows NT or Windows 95/98, add the line:

        EXTMGR_ADDINS=NEXTMNGR

    For Windows NT on DEC Alpha, add the line:

        EXTMGR_ADDINS=AEXTMNGR

        Save the modified notes.ini file.

        Alternatively, for each of the operating systems above, you may
        omit the one-character prefix in the extension manager program
        name.  In other words, you can use:
        EXTMGR_ADDINS=EXTMNGR

        If an EXTMGR_ADDINS entry already exists in notes.ini, add
        ",EXTMNGR" to the end of the existing line. The one-character 
        prefix in the extension manager program name is optional.

	For the Macintosh:

	Use Resedit or a similar utility to modify the Notes Preference
	file. The file can be found in "System Folder:Preferences:"

	  1) Add a resource of type "TEXT" if it doesn't exist
	  2) Name the resource EXTMGR_ADDINS
	  3) Set the value of the resource to "EXTMNGR"
	  4) Close and save the preference file.
			
    4.  Copy "animals.db" to the Domino or Notes data directory.

    5.  Launch Notes or Domino.

    6.  From a Notes client, select File, Database, New.

    7.  If this sample is running on a server, enter the server name. 
        Tab to Title: and enter "animals".  The File Name will be 
        automatically filled in with "animals.nsf".  Click on OK.  If 
        the animals.nsf database already exists, click on YES to replace 
        the existing database.
    
    8.  At the Main View of the database select "Animals View".

    
CHECKING THE RESULTS
--------------------

    There should be 5 items in the Common Name Column.
    Click on the "Grizzly Bear" Common Name Item and the following 
    data should be displayed:

    Grizzly Bear

    Latin Name:  Ursus arctos horribilis

    Range:       North America

    Status:      Endangered

    EXTMNGR.DLL also creates a log file called OUTPUT.LOG in the Domino
    or Notes data directory.  It tracks all Extension Manager registration
    calls, EM_NSFDBCREATE and EM_NSFDBCLOSE Extension Manager hook calls to
    the "animals.nsf" database, and all deregistration calls when Domino or 
    Notes is exited.

    Exit Domino or Notes to deregister the Extension Manager hooks.
