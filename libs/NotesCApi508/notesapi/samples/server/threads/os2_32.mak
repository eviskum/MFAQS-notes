#
# makefile for Notes API sample program THREADS
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.

# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Link the executable. Includes IBM's recommended link options.

ITHREADS.EXE: THREADS.OBJ
    ILINK /NOFREEFORMAT /PMTYPE:NOVIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK THREADS.OBJ NOTES0 NOTESAI0, ITHREADS.EXE, NUL, NOTES.LIB, ;

# Build the objects.

THREADS.OBJ: THREADS.C
    icc /C+ /Gt+ /Sp1 /Gm+ /DOS2_2x /W3 /Wcnd- $*.C

