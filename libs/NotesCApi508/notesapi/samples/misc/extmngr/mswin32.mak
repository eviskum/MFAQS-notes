#
#  makefile for Notes API test program NEXTMNGR.DLL
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
outfilename = aextmngr
defname = mswin32a
!ELSE
cpuflags = -Zp
outfilename = nextmngr
defname = mswin32
!ENDIF

all : $(outfilename).DLL

$(outfilename).DLL : extmngr.OBJ createdb.OBJ cdrecord.OBJ $(defname).DEF
    $(link) $(linkdebug) \
        -dll -def:$(defname).DEF \
         -entry:_DllMainCRTStartup$(DLLENTRY) \
         -out:$(outfilename).DLL \
        extmngr.OBJ createdb.OBJ cdrecord.OBJ \
        $(guilibs) notes.lib


extmngr.OBJ : extmngr.H extmngr.C
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) extmngr.C

createdb.OBJ : createdb.C
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) createdb.C

cdrecord.OBJ : cdrecord.C
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) cdrecord.C
