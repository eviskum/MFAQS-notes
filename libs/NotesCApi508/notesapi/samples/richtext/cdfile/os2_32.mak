# 
# makefile for Notes API sample program CDFREAD and CDFWRITE
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Dependencies

ALL: CDFREAD.EXE CDFWRITE.EXE

CDFREAD.EXE: CDFREAD.OBJ
CDFREAD.OBJ: CDFREAD.C CDFILE.H
CDFWRITE.EXE: CDFWRITE.OBJ
CDFWRITE.OBJ: CDFWRITE.C CDFILE.H

# Compilation command. 

.C.OBJ:
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Link command.
 
.OBJ.EXE:
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK $*.OBJ NOTES0, $*.EXE, NUL, NOTES.LIB, ;
