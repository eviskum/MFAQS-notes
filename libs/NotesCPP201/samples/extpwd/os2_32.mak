# 
# makefile for Notes API sample program "extpwd"
# OS/2 32-bit version
#
# This makefile is designed for use under OS/2 3.x with the
# IBM VisualAge C++ 3.0 compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Master dependency

all: iextpwd.dll

# Compilation command. 
.c.obj:
    icc /Ge- /C+ /Ss+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.c

# Dependencies
extpwd.obj : extpwd.c extpwd.h
extman.obj : extman.c extpwd.h extenv.h

# Link command.
iextpwd.dll : extpwd.obj extman.obj os2_32.def
    ILINK /NOFREEFORMAT /IGNORECASE /NOEXTDICTIONARY /ST:32768 /BASE:65536 /ALIGN:16 extpwd.obj extman.obj, iextpwd.dll, NUL, NOTES.LIB, os2_32.def ;
	
