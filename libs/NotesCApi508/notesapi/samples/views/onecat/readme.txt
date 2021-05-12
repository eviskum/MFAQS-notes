(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM      
-------                   
onecat  - Display noteIDs of documents in a category.


ENVIRONMENTS
------------
OS/2 (32-bit)

FILES 
-----
readme.txt   - This file. Specifies what is needed to use this example.

onecat.c     - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).



RUNNING onecat:
---------------
Copy the sample database, "onecat.nsf", to the Domino data directory on
your system.  From the Notes user interface, add the database's icon to your
Notes workspace.

- Under OS/2: type the following at the system command prompt:

    onecat <db filename> <view name> <category text>

    where:
      <db filename>   is the filename of the Domino database to operate on
      <view name>     is the view to use
      <category text> is the specific category to select


COMMAND LINE EXAMPLE:

      onecat onecat.nsf SimpleCategory "Category 1"


CHECKING THE RESULT
-------------------

If the program runs correctly, it should display something that looks like:
-----------------------------------------------------------------------------

Main topic count is: 1.         Note ID is: 20FA.
Main topic count is: 2.         Note ID is: 2106.
Main topic count is: 3.         Note ID is: 210A.
Main topic count is: 4.         Note ID is: 210E.

-----------------------------------------------------------------------------

To see if onecat worked correctly: 

Open onecat.nsf.

In the menu, for each document in the category "Category 1", choose
File/Document Properties... item, select the Info tab of the
document's properties InfoBox and look at the 3rd line of the ID value.
It should end with one of the NoteIDs that were in the output.
