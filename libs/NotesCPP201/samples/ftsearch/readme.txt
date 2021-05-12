(c) 1997, 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
FTSEARCH - Introductory Notes C++ API program that opens a Notes database
and performs a search based on a Search Set created from user input 
parameters.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC
	Sun Solaris Intel Edition


The following environments rely on the Integrated Development Environment
(IDE) and do not require makefiles:

	Windows (16-bit) using Borland C++

This sample does not currently support the Macintosh.


FILES
-----
ftsearch.cpp - Main program

ftsearch.hpp - Include file for main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and
               Windows 95 (32-bit) using Microsoft Visual C++

ftsearch.def - Module definition (.def) file for 16-bit Borland C++ for 
               Windows

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
		       Borland C++ (version 5) 32-bit compiler and tools. 

os2_32.mak   - Make file OS/2 (32-bit)

os390.mak    - Make file for OS/390

hp.mak       - Make file for HP-UX

sol_2x.mak   - Make file for SUN Solaris SPARC platform

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform

aix.mak      - Make file for IBM AIX

readme.txt   - This file

ftsearch.nsf - Sample Notes database (in NOTEDATA directory).


RUNNING FTSEARCH
----------------
- Under Windows 16-bit, choose File - Run from the Program Manager menu, 
  type the full program path and file name, add command line arguments
  if desired, and press Enter.

- Under OS/2, Windows NT, Windows 95, and UNIX (Solaris, AIX, OS/390 or HP-UX), 
  type 'ftsearch' at the system command prompt and add command line
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

    FTSEARCH ftsearch.nsf wtsd25

    The default number is 100.
o - Sort option to use. This parameter must be followed by a number between 
    1 and 3:
	1 = Sort by relevance (default setting)
	2 = Sort by date (newest first)
	3 = Sort by date (oldest first)
    Do not insert a space between the option letter and the number. For
    example:

    FTSEARCH ftsearch.nsf wtsd25o3

v - Type of view to use in the search. This parameter must be followed by a
    number between 1 and 4:
	1 = By Author
	2 = Categorize
	3 = By Main Topics Only
	4 = By Main View (default setting)

    Do not insert a space between the option letter and the number. For 
    example:

    FTSEARCH ftsearch.nsf wtsd25o3v2


CHECKING THE OUTPUT
-------------------
To verify that this sample executes correctly, use the following command 
line to run it:

ftsearch ftsearch.nsf wtsd25o3

You should see output similar to the following:

Creating a Full Text Index for the database:

New documents added to the index: 0
Revise documents re-indexed:      0
Documents deleted from index:     0
Total bytes indexed:              0

The Last Index Time Was: 11/02/98 10:50:31 AM

The Search Options: Sort Order is: By Date, oldest first.
Database search follows:
This search uses Search Options
and/or Search Set chosen from above.
11 document(s) found on query: "document"
Document   FTScore 
2136	   0
2132	   0
212a	   0
2126	   0
211e	   0
211a	   0
2112	   0
210a	   0
2106	   0
2102	   0
20fa	   0

ViewFolder search by chosen View follows:
This search only searches the selected
view for the string: "document".
11 document(s) found on query: "document"
Document   FTScore 
2136	   93
2132	   90
210a	   89
20fa	   83
211e	   81
211a	   81
212a	   80
2126	   78
2112	   78
2106	   78
2102	   78

All Done. Hit return to exit:  
