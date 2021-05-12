#
#  makefile for Notes API test program NTRACKER.DLL
#  Windows 32-bit version using Visual C++ compiler and linker.
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
outfilename = atracker
defname = mswin32a
!ELSE
cpuflags = -Zp
outfilename = ntracker
defname = mswin32
!ENDIF

all : $(outfilename).DLL reqnum.exe

$(outfilename).DLL : tracker.OBJ $(defname).DEF
    $(link) $(linkdebug) \
        -dll -def:$(defname).DEF \
         -entry:_DllMainCRTStartup$(DLLENTRY) \
         -out:$(outfilename).DLL \
        tracker.OBJ \
        $(guilibs) notes.lib


tracker.OBJ : tracker.H
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) tracker.C


reqnum.exe : reqnum.obj
   $(link) $(linkdebug) $(conflags) -out:reqnum.exe reqnum.obj notes0.obj $(conlibs) \
        notes.lib user32.lib

reqnum.obj : reqnum.c
    $(cc) $(cdebug) $(cflags) $(cpuflags) /DNT $(cvars) $*.c
