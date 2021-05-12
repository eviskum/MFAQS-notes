Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1998, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
schedule - Introductory Notes C++ API program that schedules an appointment 
if the requested time slot is available.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
        IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
schedule.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING schedule
----------------
This sample program will run against any Notes mail database.

To run it, type 'schedule' at the system command prompt, the Notes pathname
of the desired calendar, the name of the calendar owner, the start and end 
dates for the appointment, and the name of the server the 
calendar resides on ("" for the local machine), and then press <Enter>.

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

