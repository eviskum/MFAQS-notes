(c) 1996-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
rtattach - Notes C++ API sample program that demonstrates the different
ways of creating and deleting the attachments: one using LNNote class, 
another using LNRichText class, and the third way using LNRTContainer
class. 


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Windows NT (32-bit)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	OS/390
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition
        Linux on Intel platforms


FILES
-----
rtattach.cpp - Main program.

mswin32.mak  - Make file for Windows NT (32-bit) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit) using
               Borland C++ for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

os390.mak    - Make file for OS/390.

hp.mak       - Make file for HP-UX.               

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

readme.txt   - This file.  Specifies what is needed to use this example.

rtxtsamp.nsf - Sample Notes database (in NOTEDATA directory).

image.tif    - Sample image file (in NOTEDATA directory).


RUNNING rtattach
----------------
This sample program is designed to work with the sample database 
RTXTSAMP.NSF and the sample TIFF image file IMAGE.TIF, in the 
NOTESCPP\NOTEDATA directory.  Copy these files to your Notes data directory.  

To run this program, type 'rtattach' at the system command prompt,
followed by the Notes pathname of the database, and (optionally) the name
of the server.

For example, assuming RTXTSAMP.NSF and IMAGE.TIF have been copied to your
Notes data directory, the command line for rtattach is:

	RTATTACH RTXTSAMP



EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if rtattach worked correctly:

Use Notes to open RTXTSAMP.NSF

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
same IMAGE.TIF) and a comment "This is a rich text attachment created
from LNAttachment by LNRTContainer." The cell in the lower right-hand corner
should also contain an attachment and a comment "This is a rich text attachment 
created from RTAttachment by LNRTContainer."

Down at the bottom of the document, there should be another IMAGE.TIF attachment.


