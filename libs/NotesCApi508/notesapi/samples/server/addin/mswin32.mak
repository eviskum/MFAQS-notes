#
# makefile for Notes API sample program ADDIN
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
outfilename = aaddin
!ELSE
cpuflags = /Zp
outfilename = naddin
!ENDIF

# Update the executable file if necessary
$(outfilename).exe: addin.obj
	$(link) $(linkdebug) $(conflags) addin.obj notes0.obj notesai0.obj \
		$(conlibs) notes.lib user32.lib -out:$(outfilename).exe

# Update the object file if necessary.
addin.obj : addin.c
	$(cc) $(cdebug) $(cflags) $(cvars) $(cpuflags) /DNT addin.c
