(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
fontbl  - Create a Font Table used by rich text.


ENVIRONMENTS
------------
Windows 95/98 (32-bit)
Windows NT (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
IBM AS/400
Linux RedHat


FILES
-----
readme.txt    - This file. Specifies what is needed to use this example.

fontbl.c      - Main program.

mswin32.mak   - Make file for Windows (32-bit).

os2_32.mak    - Make file for OS/2 (32-bit).

aix.mak       - Make file for IBM AIX.

hp.mak        - Make file for HP HP-UX.

sol_2x.mak    - Make file for Solaris SPARC Edition.

sol_x86.mak   - Make file for Solaris Intel Edition.

as4ftbmk.bat  - Batch file for IBM AS/400 using Visual Age C++.

as400.mak     - Make file for IBM AS/400 using Visual Age C++.

mk_fontbl.clp - Make file for IBM AS/400 using the native C compiler.

linux.mak     - Make file for Linux RedHat.


RUNNING fontbl
--------------
- First copy the database richtext.nsf located in the Notedata directory
  to the Domino or Notes data directory.

- Under Windows (32-bit), OS/2 or UNIX (AIX, HP-UX, Linux and Solaris), 
  type the following at the system command prompt:

        fontbl <database filename>
            or
        fontbl

- Under AS/400, type:
    rundomcmd/rundomcmd server(<server name>) cmd(call pgm(qntcsdk/fontbl)
    parm( <database filename> )) batch(*no)

   where:

   <database filename>  is the filename of the Domino database.
   If no command line argument is provided, the program will prompt
   for it.
  

EXAMPLE
-------

        fontbl  richtext


CHECKING THE RESULTS
--------------------
FONTBL  will create a document in the database richtext.nsf.  The
document's RICH_TEXT field will contain three lines of richtext, 
each line in a different font.

After running the FONTBL program, open the database and display the
document that was just created.  The RICH_TEXT field will contain the
strings: 

"This is an example of System Monospaced font."
"This is an example of System Proportional font."
"This is an example of TYPEWRITER font."

The first line will be displayed in blue System Monospaced font.
The second line will be displayed in magenta System Proportional font.
The third line will be displayed in black TYPEWRITER (Courier) font.

Note that the TYPEWRITER font is not defined in the font table.  It is
one of the three hard coded fonts supported.                 
