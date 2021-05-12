#
# makefile for Notes API sample program BIG_RICH
# Windows 32-bit version using Microsoft 32-bit Visual C++
# compiler and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
!ELSE
cpuflags = /Zp
!ENDIF


# Targets.

ALL: BIG_FILE.EXE BIG_RICH.EXE

# Dependencies.
           
BIG_FILE.EXE: BIG_FILE.OBJ
    $(link) $(linkdebug) $(conflags) -out:$@ big_file.obj $(conlibs) \
    	user32.lib

BIG_FILE.OBJ: BIG_FILE.C
    $(cc) $(cdebug) $(cflags) $(cpuflags) /DW32 $(cvars) $*.c

BIG_RICH.EXE: BIG_RICH.OBJ
    $(link) $(linkdebug) $(conflags) -out:$@ big_rich.obj notes0.obj $(conlibs) \
    	notes.lib user32.lib

BIG_RICH.OBJ: BIG_RICH.C
    $(cc) $(cdebug) $(cflags) $(cpuflags) /DW32 $(cvars) $*.c
