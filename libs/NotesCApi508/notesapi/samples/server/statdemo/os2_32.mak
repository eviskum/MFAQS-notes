#
# makefile for Notes API sample program STATDEMO
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Link the executable.

istatdem.exe: statdemo.obj statdemo.res
    ILINK /NOFREEFORMAT /PMTYPE:NOVIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK statdemo.obj NOTES0 NOTESAI0, istatdem.exe, NUL, NOTES.LIB, ;
    RC statdemo.res $@

# Build the resource file.

statdemo.res: statdemo.rc statdemo.h
    RC -R statdemo.rc

# Build the objects.

statdemo.obj: statdemo.c statdemo.h
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

