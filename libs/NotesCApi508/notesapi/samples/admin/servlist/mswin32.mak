#
# makefile for Notes API sample program SERVLIST
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler 
# and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

proj = SERVLIST

#
# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
!ELSE
cpuflags = /Zp
!ENDIF

all: $(proj).exe

# Update the resource file if necessary.
$(proj).res : mswin32.rc $(proj).h
	rc -r -fo $(proj).res $(cvars) /DNT mswin32.rc

# Update the object file if necessary.
$(proj).obj : $(proj).c $(proj).h
	$(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) $(proj).c

# Update the executable file if necessary, and if so, add the resource
# back in.
$(proj).exe: $(proj).obj $(proj).res mswin32.def
	$(link) $(linkdebug) $(guiflags) $(proj).obj $(proj).res \
		$(guilibs) notes.lib -out:$(proj).exe
