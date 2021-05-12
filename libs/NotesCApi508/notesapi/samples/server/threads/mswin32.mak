#
# makefile for Notes API sample program THREADS
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
outfilename = athreads
!ELSE
cpuflags = /Zp
outfilename = nthreads
!ENDIF

# Update the executable file if necessary
$(outfilename).exe: threads.obj
	$(link) $(linkdebug) $(conflags) threads.obj notes0.obj notesai0.obj \
		$(conlibsmt) notes.lib user32.lib -out:$(outfilename).exe

# Update the object file if necessary.
threads.obj : threads.c
	$(cc) $(cdebug) $(cflags) $(cvarsmt) $(cpuflags) /DNT threads.c
