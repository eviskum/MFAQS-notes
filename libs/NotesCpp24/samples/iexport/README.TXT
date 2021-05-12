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
IEXPORT - Notes C++ API sample program that imports a CGM Image
file into a Lotus Notes document in the test database provided. Then
it exports all the rich text to a text file.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Microsoft Visual C++ for Win32
	
This sample supports Win32 platforms only.


FILES
-----
iexport.cpp  - Main program.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.
	       
readme.txt   - This file.  Specifies what is needed to use this example.

sampledb.nsf - Sample Notes database (in notedata directory).

graph.cgm    - A sample CGM Image file that gets imported. (in
               notedata directory).


RUNNING IEXPORT
---------------
This sample program is designed to work with the sample database
sampledb.nsf and the file graph.cgm, both provided in the toolkit
directory notedata. Before running the sample, copy these files to
your Notes data directory.

To run the sample, type 'iexport' at the system command prompt,
followed by the pathname of the database, and (optionally) the name
of the server. For example, assuming sampledb.nsf and graph.cgm have
been copied to your Notes data directory, run the sample by typing:

     iexport sampledb.nsf


EXAMINING THE NOTES DATABASE TO CHECK THE RESULT
------------------------------------------------
To see if IEXPORT worked correctly:

      Use Notes to open sampledb.nsf.

      Open the first note. The file graph.cgm should be imported
      in the rich text item of the first document. There should also
      be a new exported text file called expfile.txt.
