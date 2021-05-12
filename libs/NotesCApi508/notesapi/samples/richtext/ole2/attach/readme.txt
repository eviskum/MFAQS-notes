(c) 1997-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
ATTACH  -  Sample Lotus C API for Domino and Notes Program: 
           Embed an OLE 2 object in a note.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha) 
Windows 95/98 (32-bit)

FILES
-----
attach.c     - Main program.
cdrecord.c   - Contains several functions used by the main program.
cdrecord.h   - Function prototypes and symbolic constants.

mswin32.mak  - Make file for Windows 32-bit.

notes.bmp    - sample file used to create OLE 2 object.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING ATTACH
--------------
This program shows how to embed an OLE 2 object in the rich text field
of a note.  The OLE object to be embedded is created from the file 
"notes.bmp".

First, ensure the variable "szSrcFile" in the file attach.c specifies
the fully-qualified path to the input file "notes.bmp", which is
supplied with this sample. If "szSrcFile" does not correctly identify the
location of the file, either copy the file to the location specified
by szSrcFile, or edit szSrcFile appropriately and rebuild the program.

Make sure the Domino database "embedole.nsf" resides in the Domino or
Notes data directory.

ATTACH will create in the database EMBEDOLE.NSF a document
containing an embedded Windows Paintbrush object.

- Under Windows 32-bit
  type:
       attach
  at the system command prompt.


CHECKING THE RESULTS
--------------------
Open the database EMBEDOLE.NSF, then open the document that was just
created. Double click on the string contained in the document's rich
text field.  The program "Microsoft Paint" will be initiated,
displaying a small bitmap of a Notes icon.
