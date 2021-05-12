(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
alarm - Processes an Alarm Message received from the Alarm Daemon.


PURPOSE
-------
This program demonstrates the use of the Alarm APIs.  The client application
registers with the Alarm Daemon and receives an Alarm Message through the 
Alarm Message Queue (the alarm was previously set through the Notes UI in
the users Mail database).  The Alarm information is then displayed to the 
screen.


ENVIRONMENTS
------------
Windows NT (32-bit) (not including DEC Alpha)
Windows 95/98


FILES
-----
alarm.c      - Main program.

mswin32.mak  - Make file for Windows 32-bit.

readme.txt   - This file. Specifies what is needed to use this example.


SETTING AN ALARM IN THE USER'S MAIL DATABASE
--------------------------------------------
To set an alarm in your mail database, follow these steps:

1) Make sure your Mail Database has Calendar and Scheduling functionality
(release 4.5 mail template or later) and resides on a 4.5 (or later) 
Lotus Domino Server.

2) Open your Mail database.

3) Make sure the alarms option has been enabled.  To enable alarms from
within the Notes client:

   for R4.x mail template:
      - select Actions - Calendar Tools - Calendar Profile, and check the 
        "Enable alarm notifications" checkbox.  

   for R5.0 mail template:
      - select Actions - Tools - Preferences - Calendar tab - Alarms tab, 
        and check the "Enable alarm notifications" checkbox.

4) Select the Calendar view, and create an appointment entry.  Set the 
appointment's starting time to 10 minutes from the current time.

5) for R4.x mail template:
      Click the Alarm Options, and set the Alarm time to 5 minutes before 
      the appointment's starting time.

   for R5.0 mail template:
      Clik the "Options" tab, check the "Notify me" box, then 
      the "Alarm settings..."  box.  From the "Alarm Options" screen,
      set the Alarm time to 5 minutes before the apointment's starting
      time.

6) Save the Calendar entry.

7) Exit the Notes client.

8) Run the alarm program as follows and wait for the alarm message.



RUNNING alarm:
-----------------

- Under Windows 32-bit,
  type the following at the system command prompt:
 
    alarm
 

CHECKING THE RESULTS
--------------------
This program will receive an alarm message and print out the alarm 
information to the screen.
