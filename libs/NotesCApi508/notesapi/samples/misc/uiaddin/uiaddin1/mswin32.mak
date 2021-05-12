# 
# makefile for Notes API sample program UIADDIN1
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler 
# and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

cpuflags = -Zp

# Master dependency

all : uiaddin1.dll


# Link command.
           
uiaddin1.dll : uiaddin1.obj mswin32.def
    $(link) $(linkdebug) -base:0x1C000000 \
    	-dll -entry:_DllMainCRTStartup$(DLLENTRY) -def:mswin32.def \
    	-out:uiaddin1.dll \
    	uiaddin1.obj \
                $(guilibs)


# Compilation command.  

uiaddin1.obj: uiaddin1.c 
	$(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) uiaddin1.c
