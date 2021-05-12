(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
viewsumm - Print the summary information of each note in a view.

PURPOSE       
-------       
This program opens the View Note for the specified view, creates a 
collection containing the note ID's and summary information of all 
the notes in the view, and then prints the summary information.


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


FILES NEEDED:
------------
viewsumm.c  - Main program.

mswin32.mak - Make file for Windows 32-bit.

os2_32.mak  - Make file for OS/2 (32-bit).

aix.mak     - Make file for IBM AIX.

hp.mak      - Make file for HP HP-UX.

sol_2x.mak  - Make file for Solaris SPARC Edition.

sol_x86.mak - Make file for Solaris Intel Edition.

linux.mak   - Make file for Linux RedHat.

readme.txt  - This file. Specifies what is needed to use this example.

          
RUNNING viewsumm
----------------
This sample program can be run against the Domino database summary.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  Copy this file 
to the Domino or Notes data directory before running this program.

- Under OS/2, Windows 32-bit or UNIX (AIX, HP-UX, Linux or Solaris):
  type the following at the system command prompt:

        viewsumm <database filename> <view name in quotes>
                 or
        viewsumm

  where:

  <database filename> is the filename of the Domino database.
  <view name> is the name of the view.  If no command line arguments 
  are provided, the program will prompt for them.

If entering arguments at the prompts instead of at the command line, 
  do not enclose your responses in quotation marks.


EXAMPLE:

      viewsumm  summary  "FlatView"

Upon executing this command, viewsumm will print out the summary
information for each note in the view, FlatView. If an item in the 
summary information is an "empty" item, then a "*" will be printed for 
that item.  An "empty" item is an item that has zero length.  

