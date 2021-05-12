#
# makefile for Notes API sample program CLUMON.
#		Windows 32-bit version 
#
# This makefile is designed for use under Windows NT and Windows 95
#		using Microsoft 32-bit Visual C++ compiler and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows NT make definitions
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

proj = CLUMON

.c.obj :
	$(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) $*.c

all: $(proj).exe

# Update the resource file if necessary.
$(proj).res : $(proj).rc resource.h $(proj).ico
	rc -r -fo $(proj).res $(cvars) /DNT $(proj).rc

# Update the object file if necessary.
clumon.obj : clumon.c clumon.h clfunc.h resource.h
clfunc.obj : clfunc.c

# Update the executable file if necessary, and if so, add the resource
# back in.
$(proj).exe: clumon.obj clfunc.obj clumon.res mswin32.def
	$(link) $(linkdebug) $(guiflags) clumon.obj clfunc.obj $(proj).res \
		$(guilibs) notes.lib -out:$(proj).exe
