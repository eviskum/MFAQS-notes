# 
#		Makefile for Notes C++ API sample program FTSEARCH
#		Builds the sample FTSEARCH for OS/2 32-bit platforms
#
# This makefile is designed for use under OS/2 3.x with the
# IBM VisualAge C++ 3.0 compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# The name of the program.
PROGNAME = FTSEARCH

# Dependencies
$(PROGNAME).EXE: $(PROGNAME).OBJ 
$(PROGNAME).OBJ: $(PROGNAME).CPP

# Compilation command. 
.CPP.OBJ:
    icc /C+ /Sp1 /Gm+ /DOS2_2x /W2 $*.CPP

# Link command.
 
.OBJ.EXE:
    ILINK /NOFREEFORMAT /DEBUG /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 \
		/EXEPACK $*.OBJ, $*.EXE, , notescpp.lib, ;
