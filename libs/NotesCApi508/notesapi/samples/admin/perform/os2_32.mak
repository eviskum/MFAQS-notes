#
# makefile for Notes API sample program PERFORM
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Targets.

ALL: ADDNAMES.EXE INDEX.EXE MIXED_1.EXE MIXED_2.EXE

# Dependencies.
           
ADDNAMES.EXE: ADDNAMES.OBJ
INDEX.EXE:    INDEX.OBJ
MIXED_1.EXE:  MIXED_1.OBJ
MIXED_2.EXE:  MIXED_2.OBJ

ADDNAMES.OBJ: ADDNAMES.C
INDEX.OBJ:    INDEX.C
MIXED_1.OBJ:  MIXED_1.C
MIXED_2.OBJ:  MIXED_2.C

# Compilation command. 

.C.OBJ:
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Link command.
 
.OBJ.EXE:
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK $*.OBJ NOTES0, $*.EXE, NUL, NOTES.LIB, ;
