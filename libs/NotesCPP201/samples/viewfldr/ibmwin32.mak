# 
# makefile for Notes C++ API sample program "viewfldr"
# Windows NT and Windows 95 version
#
# This makefile is designed for use on Win32 systems with the
# IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# The name of the program.
PROGNAME = VIEWFLDR

# Dependencies
$(PROGNAME).EXE: $(PROGNAME).OBJ
$(PROGNAME).OBJ: $(PROGNAME).CPP

# Compilation command. 
.CPP.OBJ:
    icc /C+ /Gm+ /Sp1 /DW32 /W3 $*.CPP

# Link command.
 
.OBJ.EXE:
    ILINK /OUT:$*.EXE $*.OBJ notescpp.lib
