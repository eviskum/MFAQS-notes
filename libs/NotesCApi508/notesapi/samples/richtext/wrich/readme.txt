(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
wrich    - Example Lotus C API for Domino and Notes Program: 
           Create a note and write text to a RichText field.


ENVIRONMENTS
------------
OS/2 (32-bit)


PURPOSE
-------
This program shows how to create a rich text field by dynamically 
allocating a buffer, filling the buffer with CD records converted to 
Domino and Notes canonical format, and appending the buffer to a note as a 
rich-text field.


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

wrich.c      - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).


OS/2 Operating Environment Requirements
---------------------------------------
The INCLUDE environment variable must specify both the directory containing 
the Lotus C API for Domino and Notes include files, and the directory
containing the C compiler include files.  The LIB environment variable must specify both the 
directory containing the Lotus C API for Domino and Notes library, and the
directory containing the C compiler libraries.

To build the 32-bit executable using Visual Age 3.0, open a full screen
session, change to the directory containing this sample program, and type
"nmake  -f  os2_32.mak".


RUNNING wrich
-------------
Type:

        wrich <database>

where:

<db filename> is the filename of the Domino database to operate on.  It is 
recommended to use the richtext.nsf database file supplied with the toolkit.

EXAMPLE:

      wrich richtext

When the program runs correctly it does not display anything.



EXAMINING THE NOTES DATABASE TO CHECK THE RESULT:
------------------------------------------------

To see if wrich worked correctly:

Open the target database using Notes.

Double-click on the newly created document in order to read it. 

The text should contain a left-justified and center-justified paragraph
containing the following text (and font details):

  "This is a left justified"(1) " paragraph"(2) 
          "This is a centered paragraph"(3)
 
(1) in bold, blue, 24pt Swiss
(2) in italic, red, 18pt Roman
(3) in bold italic, mangneta, 12pt Typewriter
