#
# makefile for Notes API sample program ATTACH
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler 
# and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

# The name of the program.

PROGNAME = ATTACH

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

attach.EXE:   attach.OBJ cdrecord.obj
attach.OBJ:   attach.C
cdrecord.OBJ: cdrecord.C

# Compilation command.  

.C.OBJ:
    $(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) $*.c

# Link command.
           
.OBJ.EXE:
attach.exe: attach.obj cdrecord.obj
    $(link) $(linkdebug) $(conflags) attach.obj cdrecord.obj notes0.obj \
            $(conlibs) $(olelibs) user32.lib notes.lib -out:attach.exe
