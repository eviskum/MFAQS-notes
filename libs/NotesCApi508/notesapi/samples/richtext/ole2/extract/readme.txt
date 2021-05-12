(c) 1997-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
EXTRACT -  Sample Lotus C API for Domino and Notes Program: 
           Extract OLE 2 object(s) to structured storage file(s).


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha) 
Windows 95/98 (32-bit)


FILES
-----
extract.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING extract
---------------
This program shows how to extract OLE 2 object(s) embedded in documents in
the Domino database "embedole.nsf" to structured storage file(s).

Make sure the Domino database "embedole.nsf" resides in the Domino or
Notes data directory.

Through the Notes User Interface, create a document in this database and
insert an OLE 2 object.

EXTRACT will create structured storage files whose name corresponds
to the name extendable $FILE object of embedded OLE 2 objects (e.g.
EXT12345.OLE) in the database embedole.nsf.

- Under Windows 32-bit
  type:
       extract
  at the system command prompt.


CHECKING THE RESULTS
--------------------
Open the structured storage file(s) with the DocFile Viewer application
that ships with the Microsoft Developer Tools.  The extracted object will
be in a substorage named for the ProgID of the extracted object.
