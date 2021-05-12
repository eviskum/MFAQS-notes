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
Extension manager programs are applications that can register a callback
routine that will be called before and/or after Notes or Domino performs
selected operations. Extension manager programs are built as dynamic link
libraries (DLLs) on PC platforms or shared object libraries on UNIX
platforms.

EXTPWD is an extension manager program that intercepts the Notes password
prompt, and supplies the password to Notes by reading it from a text file.
This illustrates how to write an application that can run without user
intervention when Notes requires a password.

Notes:

1. This sample is meant to illustrate how you can write an application
   that provides a password programmatically. Under no circumstances should
   a real application store an unencrypted password in a disk file, as this
   bypasses Notes security features by making the password available to
   anyone with access to the file.

2. This sample program is a C API program. The C++ API does not currently
   support extension manager applications. For more information about
   extension manager programs, refer to the Notes C API User Guide.


ENVIRONMENTS
------------
32-bit Windows 
Solaris SPARC Edition

Note: This sample is supported only on the platforms listed above. However,
      Notes supports extension manager programs on all platforms.


FILES
-----
extpwd.c     - Extension manager entry point and callback.

extman.c     - DLL handler code.

extpwd.h     - Header file for sample program.

extenv.h     - Platform-dependent definitions.

mswin32.mak  - Make file for 32-bit Windows using Microsoft Visual 
               C++.

mswin32.def  - Module definition file for 32-bit Windows.

sol_2x.mak   - Make file for Solaris SPARC Edition.

readme.txt   - This file.


USING EXTPWD
------------
Before using EXTPWD, you should copy the EXTPWD program to the Notes
executable directory, which is the directory containing the Notes program
files and libraries. The name of the EXTPWD program DLL or shared library
depends on the platform, as follows:

        nextpwd.dll        32-bit Windows
	libextpsw.so       Solaris SPARC and Intel Editions

You also need to instruct Notes to load the EXTPWD program by adding one
of the following entries to notes.ini, the Notes environment file (do this
before starting Notes):

	PC platforms:      EXTMGR_ADDINS=extpwd
	Solaris:           EXTMGR_ADDINS=libextpsw.so 

When Notes requires a password, it will read the password from a text file
called password.txt in the Notes data directory.  Be sure to create this
file in the Notes data directory before using EXTPWD.

Note: The main entry point in the EXTPWD program is called by Notes when
      Notes starts, and should NOT be called from your own application code.

You can test that the EXTPWD is working correctly by starting Notes after
performing the steps described above.  You should find that you are not
prompted for your password in circumstances where you would have been
prompted without using EXTPWD, for example when first accessing a remote
database.

Once you establish that your Notes client no longer prompts you for a 
password, you should be able to run any Notes C or C++ API application
without being prompted for a password.

As mentioned above, keeping an unencrypted password in a text file is not
recommended for a real application, because it makes the password available
to anyone with access to the file.
