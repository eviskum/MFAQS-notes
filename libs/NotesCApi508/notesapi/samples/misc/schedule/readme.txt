(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
schedule - Allows the user to add appointments, meeting invitations, 
           delete the scheduled events or get the busy/free time 
           information from their schedule.
           Note that to simplify the "adding meeting invitations" 
           process, this sample only demonstrates the procedure of 
           creating a meeting invitation, without sending the notice 
           to the invitees.


ENVIRONMENTS
------------
Windows NT (32-bit) (not including DEC Alpha)
Windows 95/98


FILES
-----
readme.txt   - This file. Specifies how to use this example.

cdrecord.c   - The sub-program creating CD records.

schedule.c   - The main program.

sched.h      - header file.

mswin32.mak  - Make file for Windows 32-bit.



RUNNING schedule:
-----------------

Note: Entering a date/time in the past is not supported by the API and 
      may return inaccurate results.

- Under Windows 32-bit, type
  the following at the system command prompt:
 
  schedule <command> <server> <mail file> <start time> <end time>
             or
  schedule
 
  where:
        <command>    is one of the following schedule commands to perform 
                        add-i : add an invitation
                        add-a : add an appointment
                        del   : delete a scheduled event
                        busy  : check busy schedule
        <server>     is the server name the user's mail database is on 
                     (ex. zathras).
        <mail file>  is the mail file name of the user (ex. mail\jdoe.nsf)
        <start time> is the start time of the range of time that you are
                     interested in (ex. 08/16/2001 02:00 pm") 
                     Note: you must enter any single digit date/time 
                     with a leading zero.
        <end time>   is the end time of the range of time that you are
                     interested in (ex. 08/16/2001 05:00 pm") 
                     Note: you must enter any single digit date/time 
                     with a leading zero.

  If no command line arguments are provided, the program will prompt for
  them.



EXAMPLE - ADD an appointment
----------------------------
  schedule add-a zathras mail\jdoe.nsf "08/16/2001 09:00 am" "08/16/2001 10:00 am"

  Note: Stay within a day's boundary for the add-a command.


EXAMPLE - ADD a meeting invitation
----------------------------------
  schedule add-i zathras mail\jdoe.nsf "08/16/2001 10:00 am" "08/16/2001 11:00 am"

  Note: Stay within a day's boundary for the add-i command.


EXAMPLE - DELETE scheduled entries
----------------------------------
  schedule del zathras mail\jdoe.nsf "08/16/2001 09:00 am" "08/16/2001 10:00 pm"

  Note: End time is not used in finding the schedule entry but must be 
        supplied.


EXAMPLE - Get BUSY/FREE time information
----------------------------------------
  schedule busy zathras mail\jdoe.nsf "08/16/2001 09:00 am" "08/16/2001 05:00 pm"

  Note: You must specify a time range that is at least 60 minutes.
        You also may specify a time that expands to the next day. 


CHECKING THE RESULTS
--------------------
This program must be run against a mail file that uses a 4.5 or higher mail
template and resides on a 4.5 or higher Lotus Domino Server.

- Verify Adding an appointment:

From Notes, open your calendar and confirm that there is an appointment for 
the date/time specified.


- Verify Adding a meeting invitation:

From Notes, open your calendar and confirm that there is a meeting 
invitation for the date/time specified.


- Verify Deleting scheduled entries:

From Notes, open your calendar and confirm that the scheduled entries for 
the date/time specified have been deleted.


- Verify Busy/Free time:

This program will print out the first free time and all the busy times
during the time periods you specified.

From Notes, open your calendar and look at the dates you typed in. Confirm 
that the program returned the correct information about your schedule for 
the days you typed in.

You can select daily allowable free time in your Calendar Profile:
If you have an R5 mail template:
   click the menu item Actions->Tools->Preferences, then Free Time tag.
If you have an R4 mail template:
   click the menu item Actions->Calendar Tools.

