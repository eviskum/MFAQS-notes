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

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC
        Linux on Intel platforms


FILES
-----
rtpgraph.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC platform.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.

rtsample.nsf - Sample Notes database (in notedata directory).


RUNNING RTPGRAPH
----------------
This sample program runs against a supplied Notes database, rtsample.nsf.
This database should be copied to your Notes data directory. The program
prompts the user along the way to continue after pauses, but does
not take any input parameters. It depends on finding a document with a 
'body' item which must contain a paragraph that starts with the string 
"The dangerously erratic".  
 
Command Line Syntax:    rtpgraph


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
In Notes, open rtsample.nsf when prompted during program execution to examine 
the results of paragraph, tabs, and font style changes in the rich text. 
Be sure to close the document after each examination before continuing 
program execution. If you do not do so, you will not see the changes made to 
the document, since you have the document in its old state still open. 

When the program completes, it sets the text in the affected portion of the 
document to plain, typewriter-style text and normal paragraph and tab 
settings so that you can run the program again without having to
edit the document.
