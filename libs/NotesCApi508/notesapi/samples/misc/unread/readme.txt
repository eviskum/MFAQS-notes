(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
unread - Manipulate unread lists


PURPOSE:      
-------       
This program will display or modify a user's unread note list.

This program also demonstrates how to update a note and then change
its unread status back to what it was before the update occurred.  To
activate this demonstration, specify the simple.nsf sample database and 
specify a currently unread noteid to be deleted from the unread list.  
This note will be deleted from the unread list and then it will be modified 
and updated.  The update will cause the note to become unread.  It will 
then be converted back to read.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
HP HP-UX
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

unread.c     - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Makefile for IBM AIX.

hp.mak       - Makefile for HP HP-UX.

sol_2x.mak   - Makefile for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.


IDENTIFY A TEST DATABASE:
-------------------------
Determine the name of a Domino database file, such as simple.nsf, that
resides in the Domino or Notes data directory on your system. Unread will
work with any valid Domino database file.


RUNNING unread
--------------
The command line of unread is  -

  unread <database> [<username>] [+/-<NoteID>] ...

where:

  <database> is the filename of the Domino database to operate on
  <username> Optional user name.  This must be the complete user
             name, as it appears in the user's User ID.
             If no name is supplied, the name from the current
             User ID will be used.  If the name is hierarchical,
             the fully-qualified user name must be provided.
  <NoteID>   Optional Note ID to be added to (+) or removed
             from (-) the unread note list.


EXAMPLES
--------

To display the unread list for the current user, type:

  unread simple

To display the unread list for a specific user, say, Richard Roe, type:

  unread simple "Richard Roe"

To remove a Note from the unread list (so the document will appear as Read):

  unread simple -8FA
In the above example, the simple.nsf database is used, the sample removes
note 8FA from the unread list.  Then, it updates the "plain_text" field
in the note, this update forces the note to become unread again.  The 
unread mark is then reset to be what is was before the note was updated.

To add a Note to the unread list (so the document will appear as Unread):

  unread simple +8FA
