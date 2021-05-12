#
# makefile for Notes API sample program NSF_DUMP.
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the NotesAPI and C "include" and "lib" directories.

# Standard Windows NT make definitions
!include <ntwin32.mak>

# The name of the program.

PROGNAME = NSF_DUMP

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

nsf_dump.exe : nsf_dump.obj dumpitem.obj dumpcd.obj cdfile.obj agents.obj navigate.obj mime.obj

nsf_dump.obj : nsf_dump.c nsf_dump.h

dumpitem.obj : dumpitem.c nsf_dump.h

dumpcd.obj : dumpcd.c nsf_dump.h

cdfile.obj : cdfile.c nsf_dump.h

agents.obj : agents.c nsf_dump.h

navigate.obj : navigate.c nsf_dump.h

mime.obj : mime.c nsf_dump.h

# Compilation command.

.C.OBJ:
    $(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) $*.c

# Link command.
        
.OBJ.EXE:
    $(link) $(linkdebug) $(conflags) -out:$@ $** notes0.obj \
      $(conlibs) notes.lib user32.lib
