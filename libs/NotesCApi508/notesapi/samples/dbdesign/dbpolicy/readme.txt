(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
dbpolicy - Sample Notes API Program: Create a database policy document.


PURPOSE
-------
This sample creates a Help-About (policy) document in a database and
writes some text to the rich text field of this document.  It also creates
a Help-Using (help) document and writes some text to it.


ENVIRONMENTS
------------
OS/2 (32-bit)


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

dbpolicy.c   - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).


RUNNING dbpolicy:
-----------------

- Under OS/2:
  type the following at the system command prompt:

  dbpolicy <database>

where:

  <database> is the full pathname of the Domino database to be modified.


EXAMPLE
-------

  dbpolicy  dbpolicy

dbpolicy will create a database policy document (Help-About This Database
document) and a database help document (Help-Using This Database document)
in the database DBPOLICY.NSF.  Each document's $BODY field will contain a
couple of lines of richtext.

dbpolicy will also print out the text in the $BODY field of the database
policy document and the database help document.


CHECKING THE RESULTS
--------------------
After running the DBPOLICY program, open the database.  
To display the database policy document that was just created, choose the
Help/About DB Policy Doc menu item.  The database policy document will
contain the strings: 

                    "DATABASE POLICY STATEMENT"
"This is a sample policy document (Help-About Database document) for 
the API sample program, DBPOLICY."
 
displayed in rich text.

To display the database help document that was just created, choose the 
Help/Using DB Policy Doc menu item.  The database help document will
contain the strings:

                    "DATABASE HELP STATEMENT"
"This is a sample help document (Help-Using Database document) for 
the API sample program, DBPOLICY."

displayed in rich text.

