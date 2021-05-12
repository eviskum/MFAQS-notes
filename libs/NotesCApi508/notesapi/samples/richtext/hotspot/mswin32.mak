# 
# makefile for Notes API sample program HOTSPOT
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler
# and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the NotesAPI and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

# The name of the program.

PROGNAME = hotspot

#
# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
!ELSE
cpuflags = /Zp
!ENDIF

# Dependencies

$(PROGNAME).EXE: $(PROGNAME).OBJ cdrecord.obj 
$(PROGNAME).OBJ: $(PROGNAME).C cdrecord.c

# Compilation command.  

.C.OBJ:
	$(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) $*.c

# Link command.
           
.OBJ.EXE:
   $(link) $(linkdebug) $(conflags) -out:$@ $** notes0.obj $(conlibs) \
		notes.lib user32.lib

