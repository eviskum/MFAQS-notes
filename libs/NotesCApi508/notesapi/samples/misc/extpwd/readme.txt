(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
extpwd - Extension manager password dialog.


PURPOSE:       
--------      
The purpose of this sample is to illustrate the work of the Extension
Manager.  This sample generates a Dynamic Link Library (DLL), or, for the
UNIX platforms, a shared library, which will intercept the Domino request 
to obtain a password.

For the Window 32-bit platforms, the DLL uses an application dialog box 
to obtain the password.  The use of a dialog box is specific to this sample, 
and is not required by the Extension Manager;  all that is required is 
that a string be returned by the DLL. 

For the UNIX and OS/2 platforms, the sample does not provide Windows User 
Interface, and the password is intercepted at the Domino Server console.


ENVIRONMENTS
------------
Windows NT (32-bit) (not including DEC Alpha)
Windows 95/98 (32-bit)
OS/2 (32 bit)
HP HP-UX
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES:
------
extpwd.c     - Extension manager entry point and callback for Windows 32-bit.
               
extos2.c     - Extension manager entry point and callback for OS/2 (32-bit).

extunix.c    - Extension manager entry point and callback for UNIX.

extwin.c     - Windows DLL and dialog code.
extwin.rc    - Windows resource script.

extpwd.h     - Header file for sample program.
extenv.h     - Platform-dependent definitions.
extpwdrs.h   - Resource constant declarations.

mswin32.mak  - Make file for Windows 32-bit.

mswin32.def  - DLL module definition file for Windows NT and Windows 95/98.

os2_32.mak   - Make file for OS/2 (32-bit).
os2_32.def   - DLL module definition file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.
exports.aix  - specifies exported entry points for AIX.

hp.mak       - Make file for HP HP-UX.
exports.hpx  - specifies exported entry points for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.

readme.txt   - This file. Specifies what is needed to use this example.


RUNNING extpwd
--------------
- Copy the DLL, or in UNIX, the shared library, to the Domino or the Notes
  program directory.


- Modify notes.ini:


  This samples generates a platform-specific prefix to the name of the DLL, 
  or in UNIX, the shared library.

  The names used are:

        nextpwd.dll             Windows NT and Windows 95/98
        iextpwd.dll             OS/2 (32-bit)
        libextpsw.a             IBM AIX
        libextpwd.sl            HP HP-UX
        libextpsw.so            Solaris SPARC and Intel Editions
        libextpsw.so            Linux RedHat


  -- For Windows 32-bit platforms:

        Exit Notes client, add the following line to client's 
        notes.ini:

           EXTMGR_ADDINS=EXTPWD


  -- For OS/2 platforms:

        Shutdown Domino server, add the following line to server's 
        notes.ini:

           EXTMGR_ADDINS=EXTPWD


  -- For UNIX platforms:
  
        Shutdown Domino server, add the following line to server's 
        notes.ini:

           EXTMGR_ADDINS=shared-library-in-lower-case

           e.g. for AIX:

           EXTMGR_ADDINS=libextpsw.a 



VERIFYING extpwd
----------------
On Windows 32-bit platforms:
   Start Notes client.  The standard Notes password prompting dialog box is
   replaced.  The new Window prompt should have a line that says 
   "Let's have your password:".


On OS/2 platforms:
   Start the Domino server.  At the Domino server console, the standard
   password prompting line should be replaced with the following line:
   "Please enter your password (Extension Manager Notification):"
   

On UNIX platforms:
   Start the Domino server.  At the Domino server console, the standard
   password prompting line should be replaced with the following line:
   "Please enter your password:".

