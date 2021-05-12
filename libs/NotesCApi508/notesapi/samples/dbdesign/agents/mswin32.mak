#
# makefile for Notes API sample program AGENTS
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler
# and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the NotesAPI and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

#
# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
!ELSE
cpuflags = /Zp
!ENDIF

#Master build target

all : agents.exe ragents.exe

# Dependencies

agents.exe  : agents.obj
agents.obj  : agents.c
ragents.exe : ragents.obj
ragents.obj : ragents.c


# Compilation command.  

.C.OBJ:
    $(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) $*.c

# Link command.
           
.OBJ.EXE:
    $(link) $(linkdebug) $(conflags) -out:$@ $** notes0.obj $(conlibs) \
    	notes.lib user32.lib
