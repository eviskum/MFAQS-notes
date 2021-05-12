(c) 1997, 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
RTPGRAPH - Introductory Notes C++ API program that demonstrates the use
of the LNParagraphStyle and LNTabs classes. It loops through stylized
text found in the first document that contains a "Body" field and applies
a new paragraph style, tabs setting, and font style to each paragraph in 
the stylized text. You are prompted along the way to examine the document 
in Notes to see what has been changed. Before exiting, the program sets 
the font and paragraph style of all the modified paragraphs back to a normal 
(plain, monospaced, etc.) font.

NOTE: New paragraphs are marked by a CD record object that is created
and inserted whenever the user enters a carriage return into the text
of the body field of a note. In this sample, the Body field contains
text of a repeating sentence: "The dangerously erratic ..." and the 
phrase: "TAB1, TAB2, TAB3, ..."  The paragraph breaks are not after
each sentence but wherever a carriage return was entered in the text.
As you run the program, you will notice the paragraph breaks when they
are modified by seeing the font, paragraph, and tab styles change.


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
rtpgraph.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and
               Windows 95 (32-bit) using Microsoft Visual C++.

rtpgraph.def - Module definition (.def) file for 16-bit Borland C++ for 
               Windows.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ 5.0 for Windows.

os2_32.mak   - Make file OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

sol_x86.mak  - Make file for Sun Solaris Intel Edition platform.

aix.mak      - Make file for IBM AIX.

readme.txt   - This file.

rtsample.nsf - Sample Notes database (in NOTEDATA directory).


RUNNING RTPGRAPH
----------------
This sample program runs against a supplied Notes database, RTSAMPLE.NSF.
This database should be copied to your Notes data directory. The program
prompts the user along the way to continue after pauses, but does
not take any input parameters. It depends on finding a document with a 
'body' item which must contain a paragraph that starts with the string 
"The dangerously erratic".  

 
Command Line Syntax:	RTPGRAPH

- Under Windows 16-bit, choose File - Run from the Program Manager menu, 
  type the full program path and filename, and press Enter.

- Under OS/2, Windows NT, Windows 95, and UNIX (Solaris, AIX, OS/390 or HP-UX), 
  type 'RTPGRAPH' at the system command prompt.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
In Notes, open RTSAMPLE.NSF when prompted during program execution to examine 
the results of paragraph, tabs, and font style changes in the rich text. 
Be sure to close the document after each examination before continuing 
program execution. If you do not do so, you will not see the changes made to 
the document, since you have the document in its old state still open. 

When the program completes, it sets the text in the affected portion of the 
document to plain, typewriter-style text and normal paragraph and tab 
settings so that you can run the program again without having to
edit the document.
