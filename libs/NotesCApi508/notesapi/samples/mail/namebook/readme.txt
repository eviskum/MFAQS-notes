(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
namebook  - List all Address books identified by the NAMES variable 
            in the notes.ini file.


ENVIRONMENTS
------------
OS/2 (32-bit)


PURPOSE
-------
This program demonstrates the Lotus C API for Domino and Notes function 
NAMEGetAddressBooks().


FILES
-----
namebook.c   - Main program.
os2_32.mak   - Make file for OS/2 (32-bit).
readme.txt   - This file. Specifies what is needed to use this example.


RUNNING namebook
----------------
- Under OS/2, the syntax for this sample is:

        namebook  <server name>  [options]


If options = TITLES, this sample prints the title of each database 
in addition to the file path.


EXAMPLE
-------
Note:  A Server's Address book is called the Domino Directory.

Print a list of the Address book databases identified by the
NAMES variable in the NOTES.INI file on your workstation by typing:

         namebook  ""

Print the same list also including the titles of the Address 
book by typing:

         namebook  ""  TITLES

Print the list of Address book and Domino Directory databases identified
by the NOTES.INI file on server ACME-1 (for example) by typing:

        namebook  ACME-1  TITLES

