(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
readview   -  Read the specified view note, display some information about 
          the view.

ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
IBM AS/400
Linux RedHat

FILES
-----
readview.c     - Main program.
readview.h     - Symbolic constants used by the main program.
               
mswin32.mak    - Make file for Windows 32-bit.

os2_32.mak     - Make file for OS/2 (32-bit).

aix.mak        - Make file for IBM AIX.

hp.mak         - Make file for HP HP-UX.

sol_2x.mak     - Make file for Solaris SPARC Edition.

sol_x86.mak    - Make file for Solaris Intel Edition.

as4rvwmk.bat   - Batch file for IBM AS/400 using Visual Age C++.

as400.mak      - Make file for IBM AS/400 using Visual Age C++.

mk_readvie.clp - Make file for IBM AS/400 using the native C compiler.

linux.mak      - Make file for Linux RedHat.

readme.txt     - This file.


RUNNING readview
----------------
This program opens the Domino database readview.nsf. The API kit provides
this database in the notedata directory. You must copy this file to the 
Domino or Notes data directory before running readview.

- Under OS/2, Windows NT, Windows 95/98, or UNIX (AIX, HP-UX, Linux and 
  Solaris), type the following at the system command prompt:

       readview

- Under AS/400
  type:
    rundomcmd/rundomcmd server(<server name>) cmd(call pgm(qntcsdk/readview))
    batch(*no)
  
The program takes no arguments.


OUTPUT
------
The output of this program will look like the following (some details
may vary from one system to another):

View Title:  View A
Date/Time of last modification:  10/25/1999 04:20:49 PM
Time relative formulae DO NOT exist in this view.

Column 1 of 3
        Item Name:                  $0
        Title:                      "#"
        Formula:                    @DocNumber
        Sort Key:                   NO
        Category:                   NO
        Sort Order:                 Ascending
        Hidden:                     NO
        Response Column:            NO
        Hide Detail if Subtotaled:  NO
        Display Icon:               NO
        Resizable at Runtime:       resizable
        Resortable at Runtime:      NOT resortable

Column 2 of 3
        Item Name:                  Number
        Title:                      "Number Column"
        Sort Key:                   YES
        Category:                   NO
        Sort Order:                 Ascending
        Hidden:                     NO
        Response Column:            NO
        Hide Detail if Subtotaled:  NO
        Display Icon:               NO
        Resizable at Runtime:       resizable
        Resortable at Runtime:      NOT resortable

Column 3 of 3
        Item Name:                  Text
        Title:                      "Text Column"
        Sort Key:                   NO
        Category:                   NO
        Sort Order:                 Ascending
        Hidden:                     NO
        Response Column:            NO
        Hide Detail if Subtotaled:  NO
        Display Icon:               NO
        Resizable at Runtime:       resizable
        Resortable at Runtime:      NOT resortable


Selection View Formula: "SELECT @All"

Program completed successfully.
