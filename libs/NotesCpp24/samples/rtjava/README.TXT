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
rtjava - Notes C++ API sample program that embeds a Java applet in rich text.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	IBM AIX
        Sun Solaris SPARC platform
        Linux on Intel platforms

Notes:

   1. This sample is supported only on the platforms listed above.

   2. Notes platforms that do not support embedded Java applets will
      display an alternate text message when you open a document that
      contains an embedded Java applet.


FILES
-----
rtjava.cpp   - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

sol_2x.mak   - Make file for Sun Solaris SPARC Edition.

aix.mak      - Make file for IBM AIX.

linux.mak    - Make file for Linux on Intel platform.

SystemProperties.class - Sample Java applet.

PropertyWrapper.class  - Supporting Java class.

ButtonKeyDriver.class  - Supporting Java class.

PanelKeyDriver.class   - Supporting Java class.

SystemProperties.java  - Sample Java applet source code.

PropertyWrapper.java   - Supporting Java class source code.

ButtonKeyDriver.java   - Supporting Java class source code.

PanelKeyDriver.java    - Supporting Java class source code.

readme.txt   - This file.  Specifies what is needed to use this example.

rtsample.nsf - Sample Notes database (in notedata directory).



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
      does not support Java applets, an alternate text message should be
      displayed.)

