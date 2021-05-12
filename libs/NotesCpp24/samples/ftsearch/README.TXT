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
FTSEARCH - Introductory Notes C++ API program that opens a Notes database
and performs a search based on a Search Set created from user input 
parameters.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
ftsearch.cpp - Main program

ftsearch.hpp - Include file for main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform

aix.mak      - Make file for IBM AIX

linux.mak    - Make file for Linux for Intel platform.

readme.txt   - This file.

ftsearch.nsf - Sample Notes database (in notedata directory).


RUNNING FTSEARCH
----------------
Type 'ftsearch' at the system command prompt and add command line
  arguments if desired.

Note: To run the sample you must copy the 'ftsearch' database
      to your Notes data directory and use 'ftsearch' as 
      the first command line argument.
	  
      If you do not supply any command line arguments 
      you will be prompted for arguments at run time and 
      the default arguments will be displayed.

      Supplying options without the dbname argument will
      generate an error. If you supply only the first argument,
      all the options will be set to their defaults.

      The sample is hard coded to search for QUERYSTRING which 
      is defined as 'documents' in the include file.


Command Line Syntax:  ftsearch <dbname> [options]

dbname is the file path and name for the database to search. If you do not 
supply this parameter, you are prompted for arguments at run time. 
Supplying options without this parameter will generate an error. If you 
supply just the file path and name, all the options are set to their defaults.

options are one or more of the following in any order:
						
w - Whole words only in the match. No stemming or partial words. (The default 
    is to match stemming or partial words.)
t - Thesaurus Words are included in match (similar word matches). (The 
    default is not to match on thesaurus words.)
s - Do not use a search set selected from a particular author. (The default 
    is to use a search set. You will be prompted for an author.)
d - Maximum number of documents to search. Do not insert a space between the 
    option letter and the number. For example:

    ftsearch ftsearch.nsf wtsd25

    The default number is 100.
o - Sort option to use. This parameter must be followed by a number between 
    1 and 3:
	1 = Sort by relevance (default setting)
	2 = Sort by date (newest first)
	3 = Sort by date (oldest first)
    Do not insert a space between the option letter and the number. For
    example:

    ftsearch ftsearch.nsf wtsd25o3

v - Type of view to use in the search. This parameter must be followed by a
    number between 1 and 4:
	1 = By Author
	2 = Categorize
	3 = By Main Topics Only
	4 = By Main View (default setting)

    Do not insert a space between the option letter and the number. For 
    example:

    ftsearch ftsearch.nsf wtsd25o3v2


CHECKING THE OUTPUT
-------------------
To verify that this sample executes correctly, use the following command 
line to run it:

ftsearch ftsearch.nsf wtsd25

You should see output similar to the following:

Creating a Full Text Index for the database:

New documents added to the index: 16
Revise documents re-indexed:      0
Documents deleted from index:     0
Total bytes indexed:              0

The Last Index Time Was: 04/13/2000 12:30:23 PM

The Search Options: Sort Order is: By Relevance.
Database search follows:
This search uses Search Options
and/or Search Set chosen from above.
7 document(s) found on query: "document"
Document   FTScore  
2136 	   78
2132	   78
2102 	   72
211a 	   71
211e 	   70
2112 	   69
20fa 	   68

ViewFolder search by chosen View follows:
This search only searches the selected
view for the string: "document".
11 document(s) found on query: "document"
Document   FTScore  
2136 	   76
2132 	   76
210a 	   76
211a 	   73
211e 	   73
20fa 	   73
212a 	   72
2102 	   70
2106 	   70
2126 	   68
2112 	   68

All Done. Hit return to exit: 
