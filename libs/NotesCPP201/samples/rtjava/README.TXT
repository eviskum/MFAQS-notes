(c) 1998-1999 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement (in the apilicns.txt file in the notescpp directory of
this toolkit), Restricted Rights for U.S. government users, and
applicable export regulations.


PROGRAM
-------
rtjava - Notes C++ API sample program that embeds a Java applet in rich text.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

	Windows NT (32-bit, including DEC Alpha)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	OS/2 (32-bit)
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition

Notes:

   1. This sample requires Notes 4.6 or later.

   2. This sample is supported only on the platforms listed above.

   3. Notes platforms that do not supported embedded Java applets will
      display an alternate text message when you open a document that
      contains an embedded Java applet.


FILES
-----
rtjava.cpp   - Main program.

mswin32.mak  - Make file for Windows NT (32-bit, including DEC Alpha) and 
               Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit)
               using IBM VisualAge C++ for Windows.

borwin32.mak - Make file for Windows NT (32-bit) and Windows 95 (32-bit)
               using Borland C++ 5.0 for Windows.

os2_32.mak   - Make file for OS/2 (32-bit).

hp.mak       - Make file for HP-UX.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

sol_x86.mak  - Make file for Sun Solaris Intel Edition.

aix.mak      - Make file for IBM AIX.

SystemProperties.class (sysprop.cls) - Sample Java applet.

PropertyWrapper.class (propwrap.cls) - Supporting Java class.

ButtonKeyDriver.class (keybtn.cls)   - Supporting Java class.

PanelKeyDriver.class (keypnl.cls)    - Supporting Java class.

SystemProperties.java (sysprop.jav)  - Sample Java applet source code.

PropertyWrapper.java (propwrap.jav)  - Supporting Java class source code.

ButtonKeyDriver.java (keybtn.jav)    - Supporting Java class source code.

PanelKeyDriver.java (keypan.jav)     - Supporting Java class source code.

readme.txt   - This file.  Specifies what is needed to use this example.

rtsample.nsf - Sample Notes database (in NOTEDATA directory).

longname.bat - Batch file to create Java files with long filenames.

longname.cmd - OS/2 version of longname.bat.


NOTE TO PC TOOLKIT USERS
------------------------
There are two sets of Java files included with this sample, one using long
filenames, the other using short (8.3) filenames. When you run the sample,
only the long filename versions are used.

If you installed the PC version of the toolkit using a version of PKUNZIP
that does not support long filenames, you'll need to run the longname batch
file in this directory (just type longname). The batch file will create
versions of the Java files with long filenames.

Note that for OS/2, this sample must be installed to a disk that supports
long filenames (for example, an HPFS volume).


RUNNING RTJAVA
--------------
This sample program is designed to work with the sample database 
rtsample.nsf file provided in the notescpp\notedata directory, and the 
Java applet (.class) files in this sample directory, although you can use a
different database and/or applet files if you wish. If you use rtsample.nsf,
copy the database file to your Notes data directory before running the sample.

The program requires one command line parameter, the name of the
directory containing the applet (.class) files, which is probably
the same directory containing this sample.

You can also specify the following optional parameters in the order shown:

	* Notes database file name
	* Optional server name, preceded by "-s "
	* The primary applet .class file
	* Any additional .class files required by the applet

If you do not specify a database, rtsample.nsf is used. If you do not
specify any applet .class files, the class files in this sample directory
are used (SystemProperties.class is the primary file). If you do specify
any applets, you must specify the database first, and the first applet you
specify must be the primary applet; note that all Java class file names are
case sensitive. 

To run the sample, type 'rtjava' followed by the applet directory name plus
any additional parameters you wish to specify. For example, on PC platforms,
if you installed the C++ API toolkit in c:\notescpp, you could run the sample
as follows:

      rtjava c:\notescpp\samples\rtjava


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if rtjava worked correctly:

      Use Notes to open rtsample.nsf

      Open the most recently-added document to the database. The title 
      should be "Java Applet Sample."  When the document is opened, the Java
      applet should be loaded and started. (If your Notes client platform
      does not support Java applets, the alternate text message should be
      displayed.)

