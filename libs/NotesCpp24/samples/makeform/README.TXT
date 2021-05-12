Licensed Materials - Property of IBM
C513MNA
C513NNA
C513PNA

(c) Copyright IBM Corporation 1998, 2003
All rights reserved.
IBM, Lotus, Lotus Notes, Notes, and Domino are trademarks or registered
trademarks of Lotus Development Corporation and/or IBM Corporation
in the United States, or other countries, or both.


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

    Microsoft Visual C++ for Win32
    IBM AIX
    Sun Solaris SPARC Edition
    Linux on Intel platforms


FILES
-----
makeform.cpp - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

fdesign.ntf  - The source database template file (in notedata directory).

bkground.bmp - A background graphic (in notedata directory) that is
               imported and used in the form.

readme.txt   - This file.  Specifies what is needed to use this example.


RUNNING makeform
---------------
This sample does not take any arguments. Copy the fdesign.ntf
and bkground.bmp files from the notedata directory into your 
Notes data directory.

To run this program, type 'makeform' at the system command prompt.

After the program terminates, you can use Domino Designer to open 
fdesign.ntf and examine the new forms that were created, "Brand
New Form" and "New Default Form."

NOTE: The 'import background' feature that uses bkground.bmp does
not apply to UNIX but works on all other platforms.

Note that you can only examine the forms in fdesign.ntf on platforms that
support Domino Designer. The Domino administration client on server-
only platforms cannot be used to examine forms in a database. However,
you can run the sample program on any of the platforms listed in the
ENVIRONMENTS section above.


