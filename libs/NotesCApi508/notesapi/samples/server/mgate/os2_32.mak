#
# makefile for Notes API sample program MGATE
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Master dependency

all: imgate.exe

# Build the objects.

main.obj: main.c mgate.h mgateerr.h
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

inbound.obj: inbound.c mgate.h mgateerr.h
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

outbound.obj: outbound.c mgate.h mgateerr.h
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Build the resource file.

imgate.res: os2_32.rc mgateerr.h
    RC -R os2_32.rc
    copy os2_32.res imgate.res
    del  os2_32.res

# Link the executable.

imgate.exe: main.obj inbound.obj outbound.obj imgate.res
    ILINK /NOFREEFORMAT /PMTYPE:NOVIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK main.obj inbound.obj outbound.obj NOTES0 NOTESAI0, IMGATE.EXE, NUL, NOTES.LIB, ;
    RC imgate.res $@
