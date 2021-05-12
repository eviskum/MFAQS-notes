#
# makefile for Notes API sample program BIG_RICH
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Targets.

ALL: BIG_FILE.EXE BIG_RICH.EXE

# Dependencies.
           
BIG_FILE.EXE: BIG_FILE.OBJ
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK $*.OBJ, $*.EXE, NUL, , ;

BIG_FILE.OBJ: BIG_FILE.C
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

BIG_RICH.EXE: BIG_RICH.OBJ
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK $*.OBJ NOTES0, $*.EXE, NUL, NOTES.LIB, ;

BIG_RICH.OBJ: BIG_RICH.C
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C
