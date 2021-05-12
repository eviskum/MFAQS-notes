(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
jvapplet - Sample Lotus C API for Domino and Notes Program. Shows how to 
embed a Java Applet in a rich text field in a document in the embedole.nsf
database.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt             - This file. Specifies what is needed to use 
                         this example.

jvapplet.c             - Main program.

mswin32.mak            - Makefile for Windows 32-bit.

sol_2x.mak             - Makefile for Solaris SPARC Edition.

sol_x86.mak            - Makefile for Solaris Intel Edition.

linux.mak              - Makefile for Linux RedHat.

IntroLocalApplet.java  - Java Applet source file.

IntroLocalApplet.class - Java Applet class file.



BEFORE RUNNING THIS SAMPLE:
---------------------------
1. Enable Java and back-end class accessing in your Notes client.  
From the Notes UI, choose File|Preferences|User Preferences; from 
the Basics click the Security Options... button.  Click Java applet 
security then -No Signature-, check the Access to Notes Java classes 
option.  Click OK button to save the change.


RUNNING jvapplet:
-----------------
- Before compiling the program, ensure the variable "CodeStringFullPath"
in the jvapplet.c program reflects the fully-qualified path for the
IntroLocalApplet.class file.

- Run this sample program with the embedole.nsf Domino database
provided with the API toolkit.  You must copy the embedole.nsf file
to the Domino or Notes data directory before running this program.

- After the program is successfully compiled, at the system prompt type:

        jvapplet embedole


CHECKING THE RESULT
-------------------
After running the jvapplet program, from Notes UI:

- Select File - Preferences - User Preferences, be sure the 
"Enable Java applets" option is checked.

- Open the database embedole.nsf and the document just created.  This
should trigger the execution of the Applet in the document, and it
should display information similar to the following:


Title of the current database is
   EMBEDOLE test database

(This Java Applet is inserted in this document by the jvapplet C API sample.)


