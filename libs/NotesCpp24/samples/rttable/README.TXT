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
RTTABLE - Sample Notes C++ API program that demonstrates the use of two
rich text classes, LNTable and LNTableCell. It creates a new document in a
given database (default is rtxtsamp.nsf) and adds two tables to it. 
The program then demonstrates how to modify table borders, background color, and 
how to set, modify, and delete the contents of each cell in a table.

ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
rttable.cpp  - Main program

rttable.hpp  - Include file for the main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.

rtxtsamp.nsf - Notes database file to be used with this sample
               (in notedata directory).


RUNNING RTTABLE
----------------
This sample program is designed to work with rtxtsamp.nsf, but can be used
with any database that contains a form with the name or alias "MainTopic."
The sample prompts you for the source database (.nsf) file and the number
of rows and columns for the new table. 

Type 'rttable' at the system command prompt, and add command line arguments
(see below) if desired.

You can also specify these parameters as command line arguments.

Syntax:

     rttable [ dbname [ options ] ]

"dbname" is the file path name for the database to which you want to add the 
table. If you don't specify any parameters, you will be prompted for a
database path name when you run the sample. If you specify a database other
than rtxtsamp.nsf, make sure it contains a form with the name or alias
"MainTopic." If you don't specify a complete path, the path name is relative
to the Notes data directory, so you might need to copy the database from the
toolkit notedata directory to your local Notes data directory.

"options" are one or both of the following in any order:
						
r - Number of rows in the table. There cannot be a space between the option 
    letter and the number (i.e., "rttable rtxtsamp.nsf r10"). (Default = 3)

c - Number of columns in the table. There cannot be a space between the 
    option letter and the number (i.e., "rttable rtxtsamp.nsf r10c15").
    (Default = 5).

If you omit the "options" parameter, the defaults are used.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------

In Notes, open the database file you specified. Open the document with
the topic "Rttable" (created by Sam Sample.) Check to see that it
contains two tables. The number of rows and columns of the first table
should match your inputs. The second table should have 2 rows and 2
columns, and have a cyan background color. The upper left-hand corner
cell should contain the comment "The button used to be here." The
lower right-hand corner cell should contain a comment "The button goes
here:" followed by a button. If you click the button, a window will
appear with the greeting "Hi, how are you?!" Click OK. The button
doesn't actually do anything.
