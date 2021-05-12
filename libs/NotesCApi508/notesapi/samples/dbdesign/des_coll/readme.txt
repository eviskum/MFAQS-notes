(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
des_coll - Example Program: Read the design collection for the database
           and print the type and title of each design note found.


PURPOSE      
-------
This program demonstrates the use of the design collection. It uses 
class NOTE_CLASS_DESIGN to open the design collection then reads all 
the entries in it.  The design collection is a collection that contains 
entries for every form, view, macro, and replication formula in the 
database. This reads through the design collection and for each design 
note prints the note class (Form, View, etc.) and the title, of each.

NOTE:  This sample does not open the private design collection.  Therefore,
       design notes that are private will not be included in the output.
              

ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

des_coll.c   - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.


RUNNING des_coll:
-----------------

- Under OS/2, Windows, or UNIX (AIX, HP-UX, Linux or Solaris),
  type the following at the system command prompt:

  des_coll <database>

           or

  des_coll

where:

  <database> is the full pathname of a Domino database.
  If no command line argument is provided, the program will prompt for it.


EXAMPLE
-------

  des_coll des_coll


If the program runs correctly, it should display:

Printing design collection for 'Design Collection Test'
Found 5 design notes in 'Design Collection Test'.
        Design Note 1 : Class = Field   Title = 'ColorField'
        Design Note 2 : Class = replication formula     Title = 'Martin Cox'
        Design Note 3 : Class = Form    Title = 'SimpleDataForm'
        Design Note 4 : Class = View    Title = 'SimpleDataView'
        Design Note 5 : Class = Macro   Title = 'Status Update'
