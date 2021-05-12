(c) 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
schedule - Introductory Notes C++ API program that schedules an appointment 
if the requested time slot is available.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC
	Sun Solaris Intel Edition


The following environments rely on the Integrated Development Environment
(IDE), and do not require makefiles:

	Windows (16-bit) using Borland C++
	MacOS (7.5 or later) Power PC


FILES
-----
schedule.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ 5.0 for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING schedule
---------------
This sample program will run against any Notes database.  On platforms
other than Macintosh, the user must supply command-line parameters.
On the Macintosh, the user is prompted for parameters by the program.

- Under Windows 16-bit: Choose File - Run from the Program Manager menu, 
  type in the full path and filename of this program, the Notes pathname
  of the desired calendar, the name of the calendar owner, the start and end 
  dates for the appointment, and, optionally, the name of the server the 
  calendar resides on, and then press <Enter>.

- Under OS/2, Windows NT, Windows 95, and UNIX (Solaris, AIX, OS/390, or HP-UX):
  Type 'schedule' at the system command prompt, the Notes pathname
  of the desired calendar, the name of the calendar owner, the start and end 
  dates for the appointment, and, optionally, the name of the server the 
  calendar resides on, and then press <Enter>.

- Under Macintosh: Double-click the program icon. The program will
  prompt for the Notes pathname of the desired calendar and the name of the 
  calendar owner, the start and end dates for the appointment, and the name 
  of the server the calendar resides on. If the calendar resides locally
  just press <Enter>.

A sample command line for schedule is:

schedule jdoe.nsf "Jane Doe" "07/08/98 9:00am" "07/08/98 10:00am" "Saturn"
Note: The date syntax is mm/dd/yy.  Also this sample could take a minute or
more to run if you have a large number of entries in your calendar.

The program should display:

	The description that was set was: My appointment
	The date that was set was: <your date>
	


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if schedule worked correctly:

      Use Notes to open the calendar you specified.

      In the calendar view, go to the date you specified and check to see 
      that your appointment is set.

