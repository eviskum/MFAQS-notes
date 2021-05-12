# 
# makefile for Notes API sample program EXTPWD
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Master dependency

all: iextpwd.dll

# Compilation command. 
.c.obj:
    icc /Ge- /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.c

# Dependencies
extos2.obj : extos2.c

# Link command.
iextpwd.dll : extos2.obj os2_32.def
    ILINK /NOFREEFORMAT /IGNORECASE /NOEXTDICTIONARY /ST:32768 /BASE:65536 /ALIGN:16 extos2.obj, iextpwd.dll, NUL, NOTES.LIB, os2_32.def ;

