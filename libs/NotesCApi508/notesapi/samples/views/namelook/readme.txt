(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
namelook   - Look up names in Address book(s)


ENVIRONMENTS
------------
Windows NT (32-bit) (not including DEC Alpha) 
Windows 95/98 (32-bit)


PURPOSE
-------
Test the Name Lookup C API functions including the associated buffer access 
functions.


FILES
-----
readme.txt  - This file. Documents this sample program and provides examples.

namelook.c  - Main C source file for the program

mswin32.mak - Make file for Windows 32-bit.


RUNNING namelook
----------------
- Under Windows 32-bit type:

      namelook

  If no command line arguments are provided, the program will prompt
  for them.   

  You may also include the view names, the names, the items and optionally
  the server name as arguments:  

         namelook  <ViewNames> <Names> <Items> [ServerName]

All arguments given on the command line must be surrounded by double quotes 
if they contain spaces or symbols such as '|' that require double quotes.  
If entering arguments at the prompts instead of at the command line, do not 
enclose your responses in quotation marks. All required arguments may have 
multiple values separated by semicolons. The server name is optional. No 
server name causes namelook to search only local Address books.

Example:     namelook  "Contacts|People"  "boyle , robert"  jobtitle

Output:
    Looking up 1 item(s) for 1 name(s) in 1 view(s).
    Found 1 match(es) in record for name 'boyle , robert' in view 
    'Contacts|People'.
    Item(s) in match # 1:
    item 1: Name   = 'jobtitle'
        Length = 16
        Type   = TYPE_TEXT
        Value  = 'Physical Chemist'

    Program completed successfully.


TESTING namelook
----------------

1) NAMELOOK will work with the Address book(s) in your environment.

To reproduce the test cases listed below, you must use the
Address book "namelook.nsf" included with the Lotus C API 
for Domino and Notes Toolkit.  

From your Domino or Notes data directory, copy your personal Address 
book to a file name other than "names.nsf" (for example, names.sav).

2) After making a copy of your personal Address book, copy the 
example Address book included with the C API toolkit,
"namelook.nsf" to "names.nsf" in the Domino or Notes data directory.

3) From the Notes user interface, add this example Address book 
to your Notes workspace if necessary.

4) From Notes, open the test Address book database and familiarize 
yourself with the documents and information in the database. 

5) Then, perform the following tests with the example Address 
book provided:

TEST #1 (one view, one name, one text item):

  namelook  "Contacts|People"  "boyle , robert"  jobtitle


TEST #2 (one view, one name, several text items):

  namelook  "Contacts|People"  "boyle , robert"  "jobtitle;companyname;maildomain" 


TEST #3 (one view, two names, one text item)

  namelook  "Contacts|People"  "boyle , robert;sibert , willa"  jobtitle


TEST #4 (one view, two names, several text items)

  namelook  "Contacts|People"  "boyle , robert;sibert , willa"  "jobtitle;companyname;maildomain"


TEST #5 (one view, one name, one text list item):

  namelook  groups  chemists  members


TEST #6 (one view, one name, one number item)

  namelook  $Connections  bernard-1  destination

  Note that you might need to add the escape character ("\") before the
  dollar sign ("$").


TEST #7 (one view, one name matching several documents in the view)

        namelook  $users  robert  lastname

  Note that you might need to add the escape character ("\") before the
  dollar sign ("$").

