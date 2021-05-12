#
# makefile for Notes API sample program HISTORY
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler 
# and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <NTWIN32.MAK>

#
# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
!ELSE
cpuflags = /Zp
!ENDIF

all: history.exe

# Update the resource file if necessary.
histwin.res : histwin.rc histwin.dlg histwin.ico history.h
	rc -r -fo histwin.res $(cvars) /DNT histwin.rc

# Update the object file if necessary.
history.obj : history.c history.h histerr.h
	$(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) history.c

# Update the executable file if necessary, and if so, add the resource
# back in.
history.exe: history.obj histwin.res
	$(link) $(linkdebug) $(guiflags) history.obj histwin.res \
		$(guilibs) notes.lib -out:history.exe
