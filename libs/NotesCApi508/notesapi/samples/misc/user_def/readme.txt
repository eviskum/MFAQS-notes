(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
w_usrdef - Write a field of a user defined data type to a note
r_usrdef - Read a field of a user defined data type from a note


PURPOSE
-------
These programs illustrate how to create a field that has a user-defined
data type in a Domino document.  User-defined types are useful if you want
to store your own kind of object in a document.  Some examples of these
objects are: graphics formats that Domino and Notes do not understand, time
stamps of your own creation, encrypted data that uses your own encryption
scheme, etc.

The program W_USRDEF creates a Domino document with three fields.  Two
of the fields are standard types (text and time).  The third field contains
a user-defined data type.

The program R_USRDEF scans a Domino database to find documents that 
contain the special field created by W_USRDEF.  On finding such a field,
the program extracts the user-defined data and prints it out.


ENVIRONMENT
-----------  
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

w_usrdef.c   - The sample program that creates a user-defined field.

r_usrdef.c   - The sample program that reads a user-defined field.

proc_arg.c   - Function to process command line arguments.

user_def.h   - A local include file used by both sample programs.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.



RUNNING w_usrdef
----------------
Copy the Domino database file user_def.nsf (included with the toolkit) to
the the Domino Data directory.

- Under OS/2 or UNIX (AIX, HP-UX, Linux and Solaris),
  type the following at the system command prompt:

  w_usrdef user_def

  If no command line argument is provided, the program will prompt for it.


CHECKING THE RESULTS
--------------------
Using Notes, open the database user_def.nsf. Select the default view.

You will see a document with the current time in its "Time/Date" field.
Highlight this document.

From the File - Document Properties InfoBox, select the "Fields" tab.
You will see all of the fields in the document, including the field with
the user-defined data type.


RUNNING r_usrdef
----------------
- Under OS/2 or UNIX (AIX, HP-UX, Linux and Solaris),
  type the following at the system command prompt:

  r_usrdef user_def

  If no command line argument is provided, the program will prompt for it.
                     
CHECKING THE RESULTS
--------------------
The program will find all the documents that contain the user-defined
field, display the document's Node ID, and print out the contents of the
user-defined field.
