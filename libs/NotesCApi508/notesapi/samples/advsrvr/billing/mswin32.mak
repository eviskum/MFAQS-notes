#
# makefile for Notes API sample program BILLING.
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
# NOTE:  This sample has not yet been ported to DEC Alpha.
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
outdllname = abillmgr
outexename = abillses
defname = mswin32a
!ELSE
cpuflags = -Zp
outdllname = nbillmgr
outexename = nbillses
defname = mswin32
!ENDIF

all : $(outdllname).DLL $(outexename).EXE

# BILLMNGR billing extension manager sample DLL
$(outdllname).DLL : billmngr.OBJ $(defname).DEF
    $(link) $(linkdebug) \
	/NODEFAULTLIB \
	-dll -def:$(defname).DEF \
	-entry:_DllMainCRTStartup$(DLLENTRY) \
	-out:$(outdllname).DLL \
	billmngr.OBJ \
	$(conlibsmt) notes.lib

billmngr.OBJ : billmngr.C
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) billmngr.C

# BILLSES session billing sample addin
$(outexename).exe: billses.obj
	$(link) $(linkdebug) $(conflags) billses.obj notes0.obj notesai0.obj \
		$(conlibs) notes.lib user32.lib -out:$(outexename).exe

billses.obj : billses.c
	$(cc) $(cdebug) $(cflags) $(cvars) $(cpuflags) -DNT billses.c


