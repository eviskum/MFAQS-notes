# 
# Makefile for Notes API sample program uiaddin2
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler 
# and linker.
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
!ELSE
cpuflags = -Zp
!ENDIF

# Master dependency

all : uiaddin2.dll


# Link command.
           
uiaddin2.dll : uiaddin2.obj mswin32.def
    $(link) $(linkdebug) -base:0x1C000000 \
    	-dll -entry:_DllMainCRTStartup$(DLLENTRY) -def:mswin32.def \
    	-out:uiaddin2.dll \
    	uiaddin2.obj \
                $(guilibs) notes.lib


# Compilation command.  

uiaddin2.obj: uiaddin2.c 
	$(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) uiaddin2.c
