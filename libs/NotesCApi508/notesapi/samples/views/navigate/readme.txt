(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM:      
-------
navigate - Navigate a Two-Level Category View

PURPOSE    This program shows how to navigate within a collection.
-------    The program navigates to the 2nd major category, then 
	   into the 2nd subcategory within this category. The program then
	   displays the noteIDs of the main documents.


ENVIRONMENTS
------------
OS/2 (32-bit)

FILES 
-----
readme.txt   - This file. Specifies what is needed to use this example.

navigate.c   - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).

       
RUNNING navigate:
-----------------
Copy the sample database, "hierarch.nsf", to the Domino data directory on
your system.  From the Notes user interface, add the database's icon to your
Notes workspace.

- Under OS/2: type the following at the system command prompt:

    navigate <database> <view>

    where:
      <database> is the filename of the Domino database to operate on
      <view> is the name of the view to navigate


EXAMPLE:

      NAVIGATE  hierarch twolevels

If the program runs correctly, it should display

-------------------------------------------------------------------------------

Note ID number 1 is: 211A
Note ID number 2 is: 211E
Note ID number 3 is: 2122

-------------------------------------------------------------------------------


EXAMINING THE DOMINO DATABASE TO CHECK THE RESULT:
--------------------------------------------------

To see if NAVIGATE worked correctly:

Open HIERARCH.NSF.

Go to the documents in Main B, sequence 2. For each one, choose
File/Document Properties... item, select the Document IDs tab
(sixth tab from the left) of the document's properties InfoBox and
look at the last line of the ID value.  It should end with one
of the NoteIDs that were in the output.
 

