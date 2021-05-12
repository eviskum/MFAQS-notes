Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1997, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
MAIL_DOC - Introductory Notes C++ API program that opens Notes documents
containing a rich text "Body" field and searches for a text string 
in each Body field. If the text string is found, the program mails the 
document to a recipient specified by the user.

This program shows how to use an LNRTCursor object to search stylized text 
in a rich text field. It also shows how to use LNDocument::MailTo to mail 
a Notes document.


ENVIRONMENTS
------------
We provide sample makefiles for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
mail_doc.cpp  - Main program.

mail_doc.cpp  - Include file for main program.

dumpme.nsf    - Notes database file that contains the documents to search
                (in notedata directory).

mswin32.mak   - Make file for 32-bit Windows using Microsoft Visual 
                C++.

sol_2x.mak    - Make file for SUN Solaris SPARC platform.

aix.mak       - Make file for IBM AIX.

linux.mak     - Make file for Linux on Intel platform.

readme.txt    - This file.


RUNNING MAIL_DOC
----------------
This sample program can run against any Notes database. For your
convenience, we have provided a sample source database, dumpme.nsf.
If you place this file in your Notes data directory, you can accept 
all defaults, other than User-Name, when the program prompts you.

At the system command prompt, type 'mail_doc' and, optionally, the
following command arguments. (If you provide command line arguments,
enclose any input strings containing spaces in quotes. If you provide
no arguments or incomplete arguments, the program prompts you for
them.)

Source Database [dumpme.nsf]      
Must have at least one document that contains a rich text "Body" field.

Source Server Path
To use the local server, specify a null string ("").

Search String
A string contained in at least one rich text "Body" field of at least one
document in the database.

User-Name
The e-mail address of a recipient for the found documents.
This must be a valid user name in order for the mail router to find the
recipient.


CHECKING THE RESULTS
--------------------
To see if the program worked, have the User-Name recipient you specified 
check his/her incoming e-mail for any documents found by the program.

