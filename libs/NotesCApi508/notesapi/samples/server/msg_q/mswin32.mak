#
# makefile for Notes API sample program MSG_Q
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
outfilename1 = amsg_q
outfilename2 = amsg_t
!ELSE
cpuflags = /Zp
outfilename1 = nmsg_q
outfilename2 = nmsg_t
!ENDIF

# targets
all: $(outfilename1).exe $(outfilename2).exe

# Update the executable file if necessary
$(outfilename1).exe: msg_q.obj
	$(link) $(linkdebug) $(conflags) msg_q.obj notes0.obj notesai0.obj \
		$(conlibs) notes.lib user32.lib -out:$(outfilename1).exe

# Update the object file if necessary.
msg_q.obj : msg_q.c
	$(cc) $(cdebug) $(cflags) $(cvars) $(cpuflags) /DNT msg_q.c

# Update the executable file if necessary
$(outfilename2).exe: msg_t.obj
	$(link) $(linkdebug) $(conflags) msg_t.obj notes0.obj notesai0.obj \
		$(conlibs) notes.lib user32.lib -out:$(outfilename2).exe

# Update the object file if necessary.
msg_t.obj : msg_t.c
	$(cc) $(cdebug) $(cflags) $(cvars) $(cpuflags) /DNT msg_t.c
