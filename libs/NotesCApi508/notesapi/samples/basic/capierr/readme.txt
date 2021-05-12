(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
CapiErr - C API functions called from a C++ module to retrieve C API error messages.


PURPOSE
-------
A Lotus C API for Domino and Notes sample program that retrieves C API error 
messages. 

This program demonstrates how to call C API functions from a module written 
in C++ using the Microsoft Foundation Classes (MFC).
     

ENVIRONMENTS
------------
Windows NT (32-bit) (not including DEC Alpha)
Windows 95/98 (32-bit)


FILES
-----
capierr.c    - Defines the class behaviors for the application.

capierr.h    - Main header file for the CapiErr application.

capierr.rc   - Resource compiler file for this example.

resource.h   - Resource compiler header file.

capierr.ico  - An icon file for this example.

capierrd.cpp - Implementation file containing C API function calls.

capierrd.h   - Header file.

stdafx.cpp   - Source file that includes just the standard include files.

stdafx.h     - Header file for standard system include files. 

capierr.dsp  - MSVC++ project file.

capierr.dsw  - MSVC++ workspace file.

mswin32.mak  - Make file for Windows 32-bit.

readme.txt   - This file. Specifies what is needed to use this example.


Compiling CapiErr:
------------------

There are two different ways to compile CapiErr:

1 - At the command prompt enter, nmake -f mswin32.mak.

2 - Launch the MSVC++ IDE, properly configured to compile C API 
    applications (please see Chapter 3-1 "Building 32-bit Windows
    Applications for details), and go to 'File - Open - Workspaces'
    and specify the file 'capierr.dsw'.  Then, from the 'Build' menu,
    choose 'Build CapiErr.exe'.   


RUNNING CapiErr:
-----------------

- Under Windows 32-bit type capierr at the command prompt in the 
  program's build directory.  When the CapiErr main window appears.  
  Choose Hex or Dec and enter a STATUS value - that may be retuned 
  from a C API function - in the Error Code window and click 
  the Error button.  The text associated with the status will appear 
  in the dialog box.
   
   For example:
   1) Choose Hex
   2) Enter 103
   3) "File does not exist" will appear in the dialog box.
