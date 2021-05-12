(c) 1999, 2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
mthread - Sample program that shows the structure of a multi-threaded
          C++ API program.

          This program spawns five threads that send mail to each other.
          Each thread exists until a call to LNDatabase::Search finds a
          message for the thread.


ENVIRONMENTS
------------
This program runs on the 32-bit Windows environment for Microsoft
Visual C++, and Borland C++ compilers only, but can be easily extended
to run on other platforms.  There are some preprocessor #ifdef sections
already set up for you at the top of the source file which contain an
incomplete set of macros for Unix environments.


FILES
-----
mthread.cpp  - Main program.

mswin32.mak  - Make file for Win 32 platform using Microsoft Visual C++.

borwin32.mak - Make file for Win 32 platform using Borland C++.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING mthread
---------------
This sample program runs against the current user's mail database. Type 
'mthread' at the system command prompt.

The console window should display output similar to the following:

Starting thread: 0
Starting thread: 1
Starting thread: 2
Thread: Michael thread started.
Thread: Michael thread sending message.
Starting thread: 3
Thread: Dave thread started.
Thread: Serge thread started.
Thread: Dan thread started.
Starting thread: 4
Thread: Dave thread sending message.
Thread: Serge thread sending message.
Thread: Dan thread sending message.
Thread: Police thread started.
Thread: Police thread sending message.
Thread: Serge thread found message.
Thread: Serge thread shutting down
Thread: Dan thread found message.
Thread: Dan thread shutting down
Thread: Dave thread found message.
Thread: Michael thread found message.
Thread: Dave thread shutting down
Thread: Michael thread shutting down
Thread: Police thread found message.
Thread: Police thread shutting down

Execution successful
All Done.  Hit return to exit:

Note that the order of the progress messages may not be the same as in
the example output above.


CHECKING THE RESULT
-------------------
To see if mthread worked correctly:

1. Use Notes to open your mail database.
2. The Drafts folder should contain five new messages in no particular
   order, authored by the current user and with the following subject 
   lines:

   Oh, no! Here come the Cops!
   Hey, Dave!
   Hey, Dan!
   Hey, Serge!
   All right, guys, let's stop the spam mail now!

