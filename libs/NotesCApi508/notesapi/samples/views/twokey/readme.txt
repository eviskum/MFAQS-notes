(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
twokey.c - Example Lotus C API for Domino and Notes Program: 
           Use a Two-Part Key to Find Documents


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


PURPOSE
-------
This program illustrates how to find documents in a view that contains
multiple sort columns.


FILES
-----
twokey.c      - Main program.

mswin32.mak   - Make file for Windows 32-bit.

os2_32.mak    - Make file for OS/2 (32-bit).

aix.mak       - Make file for IBM AIX.

hp.mak        - Make file for HP HP-UX.

sol_2x.mak    - Make file for Solaris SPARC Edition.

sol_x86.mak   - Make file for Solaris Intel Edition.

as4twomk.bat  - Batch file for IBM AS/400 using Visual Age C++.

as400.mak     - Make file for IBM AS/400 using Visual Age C++.

mk_twokey.clp - Make file for IBM AS/400 using the native C compiler.

linux.mak     - Make file for Linux RedHat.

readme.txt    - This file. Specifies what is needed to use this example.


RUNNING twokey
--------------
This sample program runs against Domino database twokey.nsf, provided with
the Lotus C API for Domino and Notes toolkit. Copy twokey.nsf to the 
Domino or Notes data directory before running this program.
twokey will always assume that the database to be opened is twokey.nsf
and the collection to be searched is the collection of the view KEYVIEW.

- Under OS/2, Windows NT, Windows 95, or UNIX (AIX, HP-UX, Linux or 
  Solaris): type the following at the system command prompt:
 
        twokey <primary key> <secondary key>
                 or
        twokey
 
  where:
 
  <primary key> and <secondary key> are the search strings that Domino and 
  Notes will match in the primary and secondary sort columns of the collection.
  If no command line arguments are provided, the program will prompt for them.
 

EXAMPLE:

      twokey Elvis 99

  Under AS/400 type,
      rundomcmd/rundomcmd server(<server name>) cmd(call pgm(qntcsdk/twokey)
      parm(Elvis '99')) batch(*no)


Here is what twokey will display:
--------------------------------

Note count is 1.         NoteID is: 210A
Note count is 2.         NoteID is: 210E


EXAMINING THE DOMINO DATABASE TO CHECK THE RESULT:
--------------------------------------------------

In Notes, open the twokey Domino database.
In the menu, for each document with the sort string "Elvis" and the
number "99", choose File/Document Properties... item, select the 
Document IDs tab (sixth tab from the left) of the document's properties 
InfoBox and look at the last line of the ID value.  It should end with one 
of the NoteIDs that were in the output.
