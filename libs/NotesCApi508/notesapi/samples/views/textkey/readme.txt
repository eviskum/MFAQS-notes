(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM      
-------
textkey  - Find Documents with Text Keys


ENVIRONMENTS
------------
OS/2 (32-bit)

FILES 
-----
readme.txt   - This file. Specifies what is needed to use this example.

textkey.c    - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).

			  
RUNNING textkey:
----------------
Copy the sample database, "textkey.nsf", to the Domino data directory on
your system.  From the Notes user interface, add the database's icon to your
Notes workspace.

- Under OS/2: type the following at the system command prompt:

    textkey <database> <view> <string>

    where:
      <database> is the filename of the Domino database to operate on
      <view> is the name of the view to search
      <string> is the text to look for in the view


EXAMPLE:

      TEXTKEY  TEXTKEY PeopleView "Smith, Carl"

If the program runs correctly, it should display:

-------------------------------------------------------------------------------

Note count is 1.         Note ID is: 2112

-------------------------------------------------------------------------------


EXAMINING THE DOMINO DATABASE TO CHECK THE RESULT:
--------------------------------------------------

To see if TEXTKEY worked correctly:

Open TEXTKEY.NSF.

In the menu, for each document that have the name "Smith, Carl", choose
File/Document Properties... item, select the Info tab of the
document's properties InfoBox and look at the 3rd line of the ID value.
It should end with one of the NoteIDs that were in the output.
