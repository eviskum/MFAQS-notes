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
Rtbutton is a sample Notes C++ API program that demonstrates and compares the two
ways to handle buttons - one using the rich text LNButton class,  
and another using LNCompositeData class. This sample is a good
example of how to use the LNCompositeData class to deal with raw CD records
that the C++ API may not address for you on the higher level yet.

The program opens a Notes database ('rtxtsamp.nsf'), finds the documents with the 
subject lines "Rtbutton using LNButton class" and "Rtbutton using CD records." 
It then checks that the messages contain the "Body" field, and appends to each of
them three buttons - created using LNButton class and CD records, respectively. 
After that, the program modifies the label of the second button in each of the two 
documents and deletes the third button in both documents.

ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        32-bit Windows 
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
rtbutton.cpp - Main program.

rtbutton.hpp - Include file for main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for SUN Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

rtxtsamp.nsf - Default Notes database file (in notedata directory) to be
	       used with this sample.

readme.txt   - This file.


RUNNING RTBUTTON
----------------
This sample program runs against any Notes database that contains two documents
that each contain a "Body" field and have the subjects "Rtsample using 
LNButton class" and "Rtsample using CD records", respectively. 
For convenience, copy rtxtsamp.nsf from the notedata directory into your 
Notes data directory (rtxtsamp.nsf already contains those documents.)

The sample prompts the user for the title of the new button, the source 
database (.nsf) file and server path names. You can also specify these
parameters as command line arguments.

To run this program, type 'rtbutton' at the system command prompt and
add command line arguments if desired.

The syntax for calling rtbutton is:

	rtbutton [ "button title" [ "database path name" [ "Server name" ]]]

for example:

	rtbutton MyButtonTitle

Note: All the command line arguments are optional.  However, if you need to 
specify the server name, you must specify the first two. Or, if you need to 
specify the database path name, you must specify the button title first.


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
In Notes, open the .nsf file you specified - if you did not specify a second
argument then the default becomes 'rtxtsamp.nsf'.  Open the first document 
that has a "Body" field and a subject "Rtbutton using LNButton class." 
It should contain 2 buttons - the first one with the label you specified, 
and the second one with the label "New Label." The last line should say 
"This button was created using LNButton class," but should have no button
following it.

Next, open the first document that has a "Body" field and a subject 
"Rtbutton using CD records." It should be identical to the previous document,
except that lines in front of each button should say "This button was
created using CD records."

If you click on any of the buttons, a prompt box appears. The box does nothing
and will disappear when you click OK.
