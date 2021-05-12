#
# Makefile for Notes API sample program SENDMAIL Windows 32-bit
# using Microsoft 32-bit Visual C++ compiler and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the NotesAPI and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

# The name of the program.

PROGNAME = sendmail

cpuflags = /Zp


# Dependencies

$(PROGNAME).EXE: $(PROGNAME).OBJ
$(PROGNAME).OBJ: $(PROGNAME).C $(PROGNAME).H

# Compilation command.

.C.OBJ:
    $(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) $*.c

# Link command.

.OBJ.EXE:
   $(link) $(linkdebug) $(conflags) -out:$@ $** notes0.obj $(conlibs) \
       notes.lib user32.lib

