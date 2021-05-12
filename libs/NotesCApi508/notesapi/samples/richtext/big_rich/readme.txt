(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
big_rich - Reads ASCII text files into a Domino database.


PURPOSE
-------
Big_rich shows how to create rich text fields from ASCII text
files using Compound Text functions.  It reads all the ASCII .txt
files in the source directory and stores them in the rich text fields
of consecutive documents created in the destination database.  The
text files may be of any size up to 5 Megabytes.  The utility program
big_file creates ASCII text files of any size to use when testing
big_rich.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

big_rich.c   - Main program.
big_file.c   - Utility program: creates ASCII text files of any size.

mswin32.mak  - Makefile for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).


RUNNING big_rich
----------------
The syntax for the utility program big_file is:

  big_file <file> <count>

where:

  <file> is the fully-qualified name of an output ASCII text file.
  <count> is the number of ASCII characters to be written to <file>.

The syntax for this big_rich is:

  big_rich <server> <database> <directory>

where:

  <server> is the Lotus Domino Server where the <database> resides.
  You may specify "" for <server> to indicate the database is in the
  local data directory.

  <database> is the filename of a Domino database with a design similar
  to the example database "big_rich.nsf" included with the C API toolkit.
  The database must exist and you must have at least author access.

  <directory> is a path specification to a directory containing any number
  of ASCII files with a file extension of ".txt".  These ASCII files may
  be of arbitrary length.

Create one or more example text files.  You may use any ASCII text files
to test big_rich but the file name extension must be ".txt".  You may also
use the utility program "big_file", included with this sample, to create
ASCII text files of any size for testing purposes.

For example, to create a file containing 50K bytes of text, type:

  big_file c:\temp\f50k.txt 51200

Then type:

  big_rich "" big_rich c:\temp

If successful, big_rich will print the following:

  big_rich: created note from file 'f50k.txt'.
  big_rich: successfully processed 1 files.
 

CHECKING THE RESULTS
--------------------
From Notes, open the target database and press <escape>, if necessary,
to see the main view.  Open the document with Subject = f50k.txt.

big_rich reads all the files ending in ".txt" found in the source
directory, and creates a document in the destination database
for each file.

The "From" field of each document gets the name of the user who
is running this program (obtained from the ID file).  The "Category"
field gets the directory name specified.  The "Body" field gets the
complete text from the file, converted to rich text format.  The
"Subject" field of each document gets the file name.

