#
# makefile for Notes API sample program EVENTS
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Master dependency

all: iconsume.exe iproduce.exe

# Build the objects.

consume.obj: consume.c
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

produce.obj: produce.c
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Build the resource files.

consume.res: consume.rc consume.h
    RC -R consume.rc

produce.res: produce.rc produce.h
    RC -R produce.rc

# Link the executables.

iconsume.exe: consume.obj consume.res
    ILINK /NOFREEFORMAT /PMTYPE:NOVIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK consume.obj NOTES0 NOTESAI0, ICONSUME.EXE, NUL, NOTES.LIB, ;
    RC consume.res $@

iproduce.exe: produce.obj produce.res
    ILINK /NOFREEFORMAT /PMTYPE:NOVIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK produce.obj NOTES0 NOTESAI0, IPRODUCE.EXE, NUL, NOTES.LIB, ;
    RC produce.res $@

