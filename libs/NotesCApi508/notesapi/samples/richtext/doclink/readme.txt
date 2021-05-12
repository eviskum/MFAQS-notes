(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
doclink  - Sample Lotus C API for Domino and Notes Program: 
           shows how to create a Doc Link, a View Link a Database Link and 
           an Anchor Link.
       

ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)

FILES
-----
readme.txt   - This file.
doclink.c    - Main C program.
mswin32.mak  - Makefile for Windows 32-bit.


RUNNING doclink
---------------
This sample program uses two Domino databases, doclink1.nsf and doclink2.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  You must copy 
these files to the Domino or Notes data directory before running this program.

- Under Windows 32-bit,
  type: doclink
  at the system prompt. The program takes no arguments.


CHECKING THE RESULTS
--------------------
This will create one note in each of the two databases doclink1.nsf
and doclink2.nsf.  The note in doclink2.nsf will contain a Doc Link, 
a View Link, a Database Link and an Anchor link to the note in doclink1.nsf.
