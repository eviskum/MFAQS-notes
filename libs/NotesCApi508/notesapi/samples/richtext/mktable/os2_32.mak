#
# makefile for Notes API sample program mktable
# OS/2 32-bit version
#
# This makefile is designed for use under OS/2 3.x with the
# IBM VisualAge C++ 3.0 compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# program name

PROGNAME = MKTABLE

# Dependencies

$(PROGNAME).EXE: $(PROGNAME).OBJ cdrecord.OBJ cdtable.OBJ
$(PROGNAME).OBJ: $(PROGNAME).C $(PROGNAME).H
cdrecord.OBJ:    cdrecord.C $(PROGNAME).H
cdtable.OBJ:     cdtable.C $(PROGNAME).H


# Compilation command.

.C.OBJ:
   icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Link command.

.OBJ.EXE:
   ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK $*.OBJ CDRECORD CDTABLE NOTES0, $*.EXE, NUL, NOTES.LIB, ;
