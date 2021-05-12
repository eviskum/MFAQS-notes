# 
#  makefile for Notes API sample program DBDRIVE
#  Windows 32-bit version using Microsoft 32-bit Visual C++
#  compiler and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>


#
# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
outfilename = adbdbdrv
defname = mswin32a
!ELSE
cpuflags = -Zp
outfilename = ndbdbdrv
defname = mswin32
!ENDIF

# Master dependency

all : $(outfilename).dll


# Link command.
	   
$(outfilename).dll : dbdrive.obj mswin32.def
    $(link) $(linkdebug) -base:0x1C000000 -stack:0 \
	-dll -entry:_DllMainCRTStartup$(DLLENTRY) -def:$(defname).def \
	-out:$(outfilename).dll \
	dbdrive.obj \
	$(conlibs) notes.lib


# Compilation command.  

dbdrive.obj : dbdrive.c dbdrive.h
	$(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) dbdrive.c
