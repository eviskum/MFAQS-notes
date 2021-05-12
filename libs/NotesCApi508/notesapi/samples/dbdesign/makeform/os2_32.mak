# 
# Makefile for Notes API sample program MAKEFORM
# OS/2 32-bit version
#
# This makefile is designed for use under OS/2 with the
# IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Dependencies

MAKEFORM.EXE: MAKEFORM.OBJ CDRECORD.OBJ
MAKEFORM.OBJ: MAKEFORM.C MAKEFORM.H
CDRECORD.OBJ: CDRECORD.C

# Compilation command. 

.C.OBJ:
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Link command.
 
.OBJ.EXE:
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK MAKEFORM.OBJ CDRECORD.OBJ NOTES0.OBJ, MAKEFORM.EXE, NUL, NOTES.LIB, ;
