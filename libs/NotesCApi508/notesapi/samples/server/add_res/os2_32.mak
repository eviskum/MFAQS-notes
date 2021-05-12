#
# makefile for Notes API sample program ADD_RES
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.

# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Link the executable. Includes IBM's recommended link options.

IADD_RES.EXE: ADD_RES.OBJ ADD_RES.RES
    ILINK /NOFREEFORMAT /PMTYPE:NOVIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK ADD_RES.OBJ NOTES0 NOTESAI0, IADD_RES.EXE, NUL, NOTES.LIB, ;
    RC ADD_RES.RES $@

# Build the resource file.

ADD_RES.RES: ADD_RES.RC ADD_RES.H
    RC -R ADD_RES.RC

# Build the objects.

ADD_RES.OBJ: ADD_RES.C ADD_RES.H
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

