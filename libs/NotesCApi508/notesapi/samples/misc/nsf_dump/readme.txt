(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software
Development Kit Agreement (in the apilicns.txt file in the notesapi directory
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
nsf_dump - Print the entire contents of a Domino database.


PURPOSE
-------
Nsf_dump prints out the entire contents of a Domino database (NSF file)
or a Compound Text (CD) file to the standard output using Lotus C API
for Domino and Notes functions. Nsf_dump recognizes almost every structure,
value, and flag exposed by the API and prints everything it recognizes.
Use this program to find out how Domino stores different kinds of data in
Domino databases. This example also shows how to enumerate the contents of a
Domino database, including database header data, note header data, all
classes of notes, and all types of data items.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
IBM S/390
Solaris SPARC Edition
Solaris Intel Edition
Power Macintosh
Linux RedHat


FILES
-----
nsf_dump.c   - Main program.
dumpitem.c   - Routines that print the contents of one item.
dumpcd.c     - Routines that print contents of one CD record.
cdfile.c     - Routines that process the contents of a CD file.
agents.c     - Routines that dump Agent records.
navigate.c   - Routines that dump Navigator records.
mime.c       - Routines that dump MIME records.

nsf_dump.h   - Constants and function prototypes.

mswin32.mak  - Make file for Windows (32-bit) (including DEC Alpha).

os2_32.mak   - Make file for OS/2 (32-bit).
os2_32.def   - Module definition file for OS/2 (32-bit).

aix.mak      - Make file for AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

os390.mak    - Make file for S/390.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file.


RUNNING nsf_dump
----------------
- Under OS/2, Windows 32-bit, or UNIX (AIX, HP-UX, Solaris, Linux and
  S/390) use the following syntax at the system command prompt:

  nsf_dump  <database name>  [options]

  where [options] =
                      not given    - dump everything, non-data
                                     notes first, then data notes.
                      -d           - dump just data notes.
                      -n           - dump just non-data notes.
                      -b           - dump binary data (like bitmaps).
                      -f <formula> - dump just data notes that match
                                     the specified formula.
                      -c           - file is a CD file, not NSF.
                      -s           - file is a CD storage file (not NSF)
                      -o <file>    - dump output to specified file.
                      -p           - dump profile information, (Environment
                                     variable, PROFILE, must be included
                                     in your makefile)
                      -e           - dump deletion stubs only
                      -m           - leave TYPE_MIME_PART and TYPE_RCF822_TEXT
                                     in native format
                      -l           - dump folder object items

The database name is required and the default path is the Domino or Notes
data directory.

All other switches are optional. If the -c option is specified the default
path for the CD file is the current directory.  If the -o option is not
specified, this program prints the entire contents of the specified
Domino database to the standard output.  It does not handle signals, which
means it does not stop on Ctl+C or Ctl+BREAK.  Therefore, run this program
on small databases or specify the -o option to send the output to a file.

nsf_dump will run against any Domino database.

- On the Macintosh, double click on the application in the Finder. You will
  be prompted for all the arguments.


EXAMPLE
-------
  nsf_dump simple
