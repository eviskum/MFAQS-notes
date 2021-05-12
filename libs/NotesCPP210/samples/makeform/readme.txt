(c) 1998-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
makeform - Sample Notes C++ API program that opens a Notes database,
creates a form that is a copy of a default form created by the Notes UI,
and modifies and saves the copied form. It then creates a new form
from scratch and saves this in the database as well. 

This sample demonstrates how to use the LNForm class to:

* Create new forms
* Copy existing forms
* Get and set attributes for forms
* Create a simple form field and insert it into a form
* Get and set auto launch attributes
* Change background colors
* Import background graphics
* Remove static text from a form and insert it
* Get and set font styles
* Create and set an action bar for the form using the LNActions 
  and LNAction classes


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
makeform.cpp - Main program.

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

fdesign.ntf  - The source database template file (in NOTEDATA directory).

bkground.bmp - A background graphic (in NOTEDATA directory) that is
               imported and used in the form.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING makeform
---------------
This sample does not take any arguments. Copy the fdesign.ntf
and bkground.bmp files from the NOTEDATA directory into your 
Notes data directory.

The sample is self-explanatory and tells you what is happening as it runs.
After the program terminates, you can use Domino Designer to open 
fdesign.ntf and examine the new forms that were created.

Create a document using the "Brand New Form" that was created by the sample.
You will see an action bar at the top of your new document with the buttons
"Formula Action," "Approve Request," and "Deny Request."

NOTE: The 'import background' feature that uses bkground.bmp does
not apply to either OS/2 or UNIX but works on all other platforms.

To run this program, type 'makeform' at the system command prompt.

Note that you can only examine the forms in fdesign.ntf on platforms that
support a full Notes client. The Domino administration client on server-
only platforms -- for example, Notes 4.6x for OS/2 -- cannot be used to examine
forms in a database. However, you can run the sample program on any of the
platforms listed in the ENVIRONMENTS section above.


