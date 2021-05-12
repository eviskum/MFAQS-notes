# 
# makefile for Notes API sample program XEDIT
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
outfilename = axedit
defname = mswin32a
!ELSE
cpuflags = -Zp
outfilename = nxedit
defname = mswin32
!ENDIF

# Master dependency

all : $(outfilename).dll

# Link command.
           
$(outfilename).dll : nxedit.obj nxedit.res $(defname).def
    $(link) $(linkdebug) -base:0x1C000000 \
    	-dll -entry:_DllMainCRTStartup$(DLLENTRY) \
      -def:$(defname).def \
    	-out:$(outfilename).dll \
    	nxedit.obj \
    	nxedit.res \
		$(conlibs) $(guilibs) notes.lib

# Update the resource if necessary

nxedit.res: mswin32.rc xedit.h
    rc -v -r -fo nxedit.res mswin32.rc

# Compilation command.  

nxedit.obj : xedit.c xedit.h
	$(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DW32 $(cvars) -Fonxedit.obj xedit.c
