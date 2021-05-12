(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
VBASIC - Sample Lotus C API for Domino and Notes Library called from a 
         Visual Basic program.


PURPOSE
-------
This sample demonstrates how to call the Lotus C API for Domino and Notes 
from a Visual Basic 4.0 32 Bit program.  The method used is to create "wrapper" functions around 
the API calls, then to call these wrappers from Visual Basic.  This method 
has the advantage that it uses the C language to manipulate the complex 
data structures used by the C API, while presenting a simpler interface to 
the Visual Basic program.


ENVIRONMENTS
------------
Windows (32-bit) (not including DEC Alpha)


FILES
-----
readme.txt     - This file. Specifies what is needed to use this example.

api_wrap.c     - Wrapper functions for Lotus C API for Domino and Notes.

mswin32.mak    - Make file for Windows (32-bit).
mswin32.def    - Module definition file for Windows (32-bit).

vb\
  gettitle.bas - Visual Basic Module (declaration file).
  gettitle.frm - Visual Basic Form (source file).
  gettitle.vbp - Visual Basic Project (make file).
  vbcode.txt   - Sample VBA Code in text format.


SAMPLE CODE STRUCTURE
---------------------
The sample code is contained in two directories: vbasic and vb. The vbasic 
directory contains code to create a Windows 32 Bit DLL with wrappers around 
Lotus C API for Domino and Notes functions. The vb subdirectory contains a 
complete Visual Basic program that calls the wrapper functions defined in 
the DLL. Notes or Domino must be installed, configured and in your path to 
run this sample.

The resulting program, with a Visual Basic interface and a Windows DLL
back end, retrieves the title of a Domino database.  While this application
is simple, it demonstrates all the techniques you need to create much 
larger programs.


RUNNING GETTITLE
----------------
(Note: The directory that holds the DLL at runtime as well as Notes or 
Domino must be in your path)

Build api_wrap.dll and copy it to a directory in your path.
 
Start Visual Basic. 

Open the project named gettitle.vbp found in the VB directory.

Run the Visual Basic program.

In the upper edit box, type "names" (or the name of any other
Domino database you have).

Click on the "Get the title..." button.
