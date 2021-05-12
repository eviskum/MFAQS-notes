(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.

PROGRAM
-------
fileatt  -  Sample Lotus C API for Domino and Notes Program: 
            Attach a file to a note.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98
IBM AIX
HP HP-UX
Solaris Intel Edition
Solaris SPARC Edition
IBM AS/400
Linux RedHat


FILES
-----
readme.txt       -  This file. Specifies what is needed to use this example.

fileatt.c        -  Main program.

mswin32.mak      -  Makefile for Windows 32-bit.

aix.mak          -  Make file for IBM AIX

hp.mak           -  Make file for HP HP-UX

sol_2x.mak       -  Make file for SPARC Solaris.

sol_x86.mak      -  Make file for Solaris Intel Edition.

as4filmk.bat     - Batch file for IBM AS/400 using Visual Age C++.

as400.mak        - Make file for IBM AS/400 using Visual Age C++.

mk_fileatt.clp   - Make file for IBM AS/400 using the native C compiler.

linux.mak        - Make file for Linux RedHat.



RUNNING fileatt
---------------
First, ensure the global variable "szSourceFileName" in the file fileatt.c
specifies the fully-qualified path to the input file "readme.txt" (or some
other file valid file on your disk), which is supplied with this sample.
If "szSourceFileName" does not correctly identify the location of the file,
either copy the file to the location specified by szSourceFileName, or edit
szSourceFileName appropriately and rebuild the program.

Next, ensure that the database embedole.nsf resides in your Domino or Notes
data directory.

- Under Windows 32-bit or UNIX (Solaris, AIX, Linux and HP-UX) type 
  the following at the system prompt:

        fileatt

- Under AS/400, type 
    'rundomcmd/rundomcmd server(<servername>) cmd(call pgm(qntcsdk/fileatt))
     batch(*no)'



FILEATT will create in the database EMBEDOLE.NSF a document which contains
two file attachments.  The first is attached using NSFNoteAttachFile.
The second is attached using low-level, FILEOBJECT APIs.


CHECKING THE RESULTS
--------------------
Open the database EMBEDOLE.NSF, then open the documents that were just
created. Double-click either attached file.  The Notes "File Attachment
Information" dialog box will appear.  You may then detach, launch or view
the file attachment.

