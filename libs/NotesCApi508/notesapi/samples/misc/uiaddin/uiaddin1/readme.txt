(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
uiaddin1  - Sample Notes User Interface Menu Add-In Program.


ENVIRONMENT
-----------
Windows NT (32-bit) (not including DEC Alpha)
Windows 95/98 (32-bit)

              
PURPOSE
-------        
This sample demonstrates how to implement a simple Notes Menu Add-In.

This sample adds a menu item, "DOS Shell", to the Actions menu in the Notes
workstation. The program provides a procedure to handle the menu item.  
The procedure for "DOS Shell" executes the DOS command shell.


FILES
----- 
readme.txt   -  This file. Specifies what is needed to use this example.

uiaddin1.c   -  Main program.

mswin32.def  -  Module definition file for Windows 32-bit.
mswin32.mak  -  Makefile for Windows 32-bit.


RUNNING uiaddin1
----------------
The Add-In DLL must be specified in the NOTES.INI file, assigned to the
AddInMenus variable:

AddInMenus = UIADDIN1.DLL

In the above case, UIADDIN1.DLL must be copied to a directory in the path.
Alternatively, the full pathname of the DLL may be specified in the 
NOTES.INI file.

Start up Notes and pull down the Actions menu.  The menu items added by
the DLLs assigned to the AddInMenus variable of the NOTES.INI file will
be added to the end of the Actions menu.

EXAMPLE
-------
Start up Notes.  Pull down the Actions menu and choose DOS Shell.  The
DOS shell is executed.  Type exit to exit the DOS shell and return to 
Notes.

