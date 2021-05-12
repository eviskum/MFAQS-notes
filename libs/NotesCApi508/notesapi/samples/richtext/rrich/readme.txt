(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
rrich - Lotus C API for Domino and Notes Sample Program: Read RichText Fields


PURPOSE
-------
This program shows how to read the text within a rich-text field.
       

ENVIRONMENTS
------------
OS/2 (32-bit)


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

rrich.c      - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).


RUNNING rrich
-------------
The command line of rrich is:

  rrich <database>  

where:

  <database> is the filename of the Domino database to operate on


EXAMPLE
-------

  rrich richtext


If the program runs correctly, it should display something that looks like:

-----------------------------------------------------------------------------

       ************* Note ID is: 212A. *************

RICH_TEXT field is:

This is some rich text.
This is a centered paragraph
It will be used  to demonstrate  the Lotus C API for Domino and Notes 
CompoundText Routines.

These lines use font faces that require a font table (a 
$Fonts item).
1234 asdfjkl;
(MS Sans Serf, Symbol, and System)

--------------------------------------------------------------------------------


CHECKING THE RESULTS
--------------------
To see if rrich worked correctly, open Rich Text Test database (richtext.nsf).
Open the documents. The text should be the same as displayed on the screen. 
It will have different colors, sizes, alignment, and styles, but it will 
be the same text as that displayed.
