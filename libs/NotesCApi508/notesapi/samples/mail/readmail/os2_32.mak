#
# makefile for Notes API sample programs READMAIL
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# The name of the program.

PROGNAME = READMAIL

# Dependencies

$(PROGNAME).EXE: $(PROGNAME).OBJ
$(PROGNAME).OBJ: $(PROGNAME).C

# Compilation command. 

.C.OBJ:
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Link command.
 
.OBJ.EXE:
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK $*.OBJ NOTES0, $*.EXE, NUL, NOTES.LIB, ;
