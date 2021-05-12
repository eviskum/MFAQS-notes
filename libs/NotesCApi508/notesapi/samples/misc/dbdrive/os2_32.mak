# 
# makefile for Notes API sample program DBDRIVE
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Master dependency

all: idbdbdrv.dll

# Compilation command. 

dbdrive.obj : dbdrive.c dbdrive.h
    icc /Ge- /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- dbdrive.c

# Link command.
 
idbdbdrv.dll : dbdrive.obj os2_32.def
    ILINK /NOFREEFORMAT /IGNORECASE /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK dbdrive.obj, idbdbdrv.dll, NUL, notes.lib, os2_32.def ;


