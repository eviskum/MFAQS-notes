Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1996, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


PROGRAM
-------
rtattach - Notes C++ API sample program that demonstrates the different
ways of creating and deleting the attachments: one using LNNote class, 
another using LNRichText class, and the third way using LNRTContainer
class. 


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
	Sun Solaris SPARC Edition
        Linux on Intel platforms


FILES
-----
rtattach.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.

rtxtsamp.nsf - Sample Notes database (in notedata directory).

image.tif    - Sample image file (in notedata directory).


RUNNING rtattach
----------------
This sample program is designed to work with the sample database 
rtxtsamp.nsf and the sample TIFF image file image.tif, in the 
notescpp\notedata directory.  Copy these files to your Notes data
directory.

To run this program, type 'rtattach' at the system command prompt,
followed by the Notes pathname of the database, and (optionally) the name
of the server.

For example, assuming rtxtsamp.nsf and image.tif have been copied to your
Notes data directory, the command line for rtattach is:

        rtattach rtxtsamp



EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if rtattach worked correctly:

Use Notes to open rtxtsamp.nsf.

Open the note with the subject "Rtattach." You should see the text 
"Here are the attachments" followed by "RT Attachment goes here --->>",
followed by the attachment itself and the text
"<<--- End of RTAttachment".

On the next line there should be a comment
"RT named Attachment goes here --->>", followed by the attachment itself
and the text "<<--- End of RT named Attachment". 

On the next line there should be a comment
"RT named Attachment used to be here --->>", immediately followed by
"<<--- End of RT named Attachment", since the attachment itself was
deleted.

Further in the document there should be a table with 2 rows and 2 columns.
The cell in the upper left-hand corner should contain an attachment (the
same image.tif) and a comment "This is a rich text attachment created
from LNAttachment by LNRTContainer." The cell in the lower right-hand corner
should also contain an attachment and a comment "This is a rich text attachment 
created from RTAttachment by LNRTContainer."

Down at the bottom of the document, there should be another image.tif attachment.


