#
# makefile for Notes API sample program MSG_Q
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.

# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Master dependency

all: IMSG_Q.EXE IMSG_T.EXE

# Link the executables. Includes IBM's recommended link options.

IMSG_Q.EXE: MSG_Q.OBJ
    ILINK /NOFREEFORMAT /PMTYPE:NOVIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK MSG_Q.OBJ NOTES0 NOTESAI0, IMSG_Q.EXE, NUL, NOTES.LIB, ;

IMSG_T.EXE: MSG_T.OBJ
    ILINK /NOFREEFORMAT /PMTYPE:NOVIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK MSG_T.OBJ NOTES0 NOTESAI0, IMSG_T.EXE, NUL, NOTES.LIB, ;

# Build the objects.

MSG_Q.OBJ: MSG_Q.C
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

MSG_T.OBJ: MSG_T.C
    icc /C+ /Gt+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

