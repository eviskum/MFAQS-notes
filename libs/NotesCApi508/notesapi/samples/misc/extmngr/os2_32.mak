# 
# makefile for Notes API sample program EXTMNGR
# OS/2 32-bit version using OS/2 IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Master dependency

all: iextmngr.dll

# Compilation command. 

extmngr.obj : extmngr.c extmngr.h
    icc /Ge- /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- extmngr.c

cdrecord.obj : cdrecord.c extmngr.h
    icc /Ge- /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- cdrecord.c

createdb.obj : createdb.c extmngr.h
    icc /Ge- /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- createdb.c

# Link command.
 
iextmngr.dll : extmngr.obj cdrecord.obj createdb.obj os2_32.def
    ILINK /NOFREEFORMAT /IGNORECASE /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK extmngr.obj cdrecord.obj createdb.obj, iextmngr.dll, NUL, NOTES.LIB, os2_32.def ;
