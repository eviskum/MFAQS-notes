(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
summary - Find and print all summary data of each data note in a database
          without opening the notes. Works on any database.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32-bit)
IBM AIX
HP HP-UX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
summary.c    - Main program.

mswin32.mak  - Make file for Windows 32-bit.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING summary
---------------
You may run this program against any Domino database.

- Under OS/2, Windows 32-bit or UNIX (AIX, HP-UX, Linux and Solaris),
  type the following at the system command prompt:
  
        summary <database filename>
                 or
        summary

  where:

  <database filename> is the filename of the Domino database to operate on.

  If the database filename is not specified, the program will prompt for it.



EXAMPLE
-------

        summary    summary.nsf

The program should print output that is similar to:

Note ID is: 0x000020fa.
        Item Name = Form
        Data Type = TYPE_TEXT
        Item Value = "SimpleDataForm"

        Item Name = plain_text
        Data Type = TYPE_TEXT
        Item Value = "This is a line of simple text."

        Item Name = number
        Data Type = TYPE_NUMBER
        Item Value = "0.000987"

        Item Name = time_date
        Data Type = TYPE_TIME
        Item Value = "01/15/1988"

        Item Name = text_list
        Data Type = TYPE_TEXT_LIST
        Item Value = "one,two,three,four"



Note ID is: 0x000020fe.
        Item Name = Form
        Data Type = TYPE_TEXT
        Item Value = "SimpleDataForm"

        Item Name = plain_text
        Data Type = TYPE_TEXT
        Item Value = "This is a sentence"

        Item Name = number
        Data Type = TYPE_NUMBER
        Item Value = "836.000000"

        Item Name = time_date
        Data Type = TYPE_TIME
        Item Value = "04/20/1986"

        Item Name = text_list
        Data Type = TYPE_TEXT_LIST
        Item Value = "a,b,c,d,e,f,g"



Note ID is: 0x00002102.
        Item Name = Form
        Data Type = TYPE_TEXT
        Item Value = "SimpleDataForm"

        Item Name = plain_text
        Data Type = TYPE_TEXT
        Item Value = "This is another line of simple text."

        Item Name = number
        Data Type = TYPE_NUMBER
        Item Value = "836.000000"

        Item Name = time_date
        Data Type = TYPE_TIME
        Item Value = "07/04/1953 07:12:00 AM"

        Item Name = text_list
        Data Type = TYPE_TEXT_LIST
        Item Value = "a,b,c,d,e"



Note ID is: 0x00002106.
        Item Name = Form
        Data Type = TYPE_TEXT
        Item Value = "SimpleDataForm"

        Item Name = plain_text
        Data Type = TYPE_TEXT
        Item Value = "This is a line of plain text."

        Item Name = number
        Data Type = TYPE_NUMBER
        Item Value = "836.000000"

        Item Name = time_date
        Data Type = TYPE_TIME
        Item Value = "07/09/1988"

        Item Name = text_list
        Data Type = TYPE_TEXT_LIST
        Item Value = "xxx,yyy,zzz"



Program completed successfully.

