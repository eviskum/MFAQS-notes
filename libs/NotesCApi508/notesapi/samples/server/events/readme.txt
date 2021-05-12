(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
produce - Server Add-In program that produces events.
consume - Server Add-In program that consumes events.


ENVIRONMENTS
------------
OS/2 (32-bit)


PURPOSE
-------
These programs are simple examples that produce and consume user defined 
server events.  The program, consume, creates an event queue in which to 
receive events, and specifies the types of events that it will consume.  
The program, produce, creates events of the appropriate type in the event 
queue.
              

FILES
-----
consume.c     - The source file for the Event Consumer program.
consume.h     - The header file for the Event Consumer program.
consume.rc    - The resource file for the Event Consumer program.
produce.c     - The source file for the Event Producer program.
produce.h     - The header file for the Event Producer program.
produce.rc    - The resource file for the Event Producer program.
os2_32.mak    - Make file for OS/2 (32-bit).
readme.txt    - This file. Specifies what is needed to use this example.


RUNNING produce and consume
-----------------------------
1) Make sure the Domino data directory on the Lotus Domino Server contains 
the server log file (log.nsf).  Start the Lotus Domino Server.

2) Copy the executable file for the add-in task to the Domino program
directory. 

3) Wait until all server tasks have started - about 30 seconds - then
press ENTER to get the server console prompt, >.

4) Load the add-in tasks by typing

        load produce
        load consume

5) Confirm that the add-in task is running by typing "show tasks" at the 
server console.

Note: These programs should only be started from a Lotus Domino Server. 


CHECKING THE RESULTS
--------------------
There are two ways to check that produce is producing events, and that
consume is consuming them. 
     
     1) Watch the server console screen for a couple of minutes while
        the two programs are running.  Each minute, the produce program
        should log a message such as:

            "Producer Test:  Produced an event!",
         
        along with the date and time.  Soon after this message is logged,
        the consume program will display a message such as:
     
            "CONSUME: Consumed an event at 02/12/92  11:15:01!"
            
        as a result of consuming an event.
         

     2) Using the Notes Workstation software, display the latest entry
        in the Domino Server Log database, and check that the above messages 
        appear.
