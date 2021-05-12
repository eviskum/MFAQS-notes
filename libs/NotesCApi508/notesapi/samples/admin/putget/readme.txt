(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.

PROGRAM
-------
putget - Lotus C API for Domino and Notes Sample program


ENVIRONMENTS
------------
OS/2 (32-bit)


FILES
-----
readme.txt    - This file. Specifies what is needed to use this example.

putnote.txt   - Sample import data for PutNote program.
pg_doc.nsf    - User Guide for this sample.

fields.c      - Functions for reading/writing various types of Notes fields.
fields.h      - Prototypes for reading/writing various types of Notes fields.
file_io.c     - Functions for platform-dependent file I/O.
file_io.h     - Prototypes for platform-dependent file I/O functions.
misc.c        - Miscellaneous functions for PutNote & GetNote programs.
misc.h        - Miscellaneous prototypes for PutNote & GetNote programs.
putnote.c     - Source for main routine of PutNote program.
getnote.c     - Source for main routine of GetNote program.
putget.h      - Prototypes for main putnote & getnote routines.
constant.h    - Global constants for GetNote & PutNote programs.

os2_32.mak    - Makefile for OS/2 (32-bit).
os2_32\
  get_ui.c    - Front-end for GetNote program for OS/2 (32-bit).
  put_ui.c    - Front-end for PutNote program for OS/2 (32-bit).


RUNNING putget
--------------
All information about PutNote and GetNote is contained in the Domino database
PG_DOC.NSF.  This database is the User Guide for PutNote and GetNote.

Please add this database to your Notes workspace and refer to it for all
further information about this sample.
