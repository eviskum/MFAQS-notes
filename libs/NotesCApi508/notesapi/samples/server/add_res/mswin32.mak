#
# makefile for Notes API sample program ADD_RES
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
outfilename = aadd_res
!ELSE
cpuflags = /Zp
outfilename = nadd_res
!ENDIF

# Update the executable file if necessary, and if so, add the resource
# back in.
$(outfilename).exe: add_res.obj add_res.res
	$(link) $(linkdebug) $(conflags) add_res.obj notes0.obj notesai0.obj \
		add_res.res $(conlibs) notes.lib user32.lib -out:$(outfilename).exe

# Update the resource file if necessary.
add_res.res : add_res.rc add_res.h
	rc -r -fo add_res.res $(cvars) /DNT add_res.rc

# Update the object file if necessary.
add_res.obj : add_res.c add_res.h
	$(cc) $(cdebug) $(cflags) $(cpuflags) $(cvars) /DNT add_res.c
