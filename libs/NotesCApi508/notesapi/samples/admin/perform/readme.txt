(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory of
this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
addnames, index, mixed_1, mixed_2 - Notes Performance Test Suite


PURPOSE
-------
This directory contains a suite of programs that test the performance of 
Domino and Notes.  Some of the programs measure raw data I/O speed, while other 
programs test indexing performance.  By using these programs as a set, or 
individually, you can accurately test (and compare) the performance of 
Domino and Notes on various hardware and software platforms. 

All of the tests operate on a R5 Address book.  This convention was 
chosen because an Address book is a typical Domino database, and is familiar
to all users.


OVERVIEW OF THE TESTS
---------------------

ADDNAMES -- Adds unique names to a N&A book. You control how many 
names are added. This test measures the raw data I/O speed to Notes. 

INDEX -- Performs one update of a specified index in a specified
database. This test measures the raw indexing speed of Notes.

MIXED_1 -- Performs any number of "transactions" on a N&A book. For n 
transactions, the test performs 1/3 n additions of new records, 1/3 n 
modifications to existing records, and 1/3 n deletions of whole records.

The program uses optimal indexing -- the index is only updated twice in 
the entire test run. The test, therefore, measures a combination of 
data I/O, index usage and a few index updates. 

MIXED_2 -- Performs any number of transactions on a N&A book, just like 
the test above, but it uses "worst case" indexing. The index is updated 
before every transaction. The test, therefore, measures primarily the 
speed of many index updates, where each update has only one change.


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

addnames.c   - Main program.
index.c      - Main program.
mixed_1.c    - Main program.
mixed_2.c    - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).

perform.cmd  - Runtime command file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.

perform.sh   - Shell script for all UNIX platforms to run the test.


RUNNING THE TESTS
-----------------

- Under OS/2 or UNIX (AIX, HP-UX, Linux and Solaris):

  The best way to run the tests is to use the command file perform.cmd
  (perform.sh Shell script on UNIX), or a variation of it.  This command
  file always starts with a fresh N&A book, so test results are reproducible.
  It then runs all the tests in a coherent order and reports the time taken
  by each test.

  Note:  perform.cmd and perform.sh contain explicit paths for the target
         and destination locations of na_test.nsf.  If these locations are
         different on your system, you will need to modify these command 
         files accordingly.

  Under OS/2 type:

    perform

       or
    
    to save the results of a test run, redirect the output of PERFORM.CMD
    to a log file as follows:

    perform > perform.log

  Under UNIX type:

    sh perform.sh

      or

    to save the results of a test run, redirect the output of the perform.sh
    to a log file as follows:

    sh perform.sh > perform.log
