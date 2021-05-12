# 
# makefile for Notes API sample program EXTPWD.DLL
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
!ELSE
cpuflags = -Zp
outfilename = nextpwd
defname = mswin32
!ENDIF

.c.obj :
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) $*.c

all : $(outfilename).dll

$(outfilename).dll : extwin.obj extpwd.obj extwin.res $(defname).def
    $(link) $(linkdebug) -base:0x1c000000 \
        -dll -def:$(defname).def \
         -entry:LibMain \
         -out:$(outfilename).dll \
        extwin.obj extpwd.obj extwin.res \
        $(guilibs) notes.lib

extpwd.obj : extpwd.h extpwdrs.h extpwd.c

extwin.obj : extpwd.h extpwdrs.h extwin.c

# Update the resource file if necessary.
extwin.res : extwin.rc extpwd.h
	rc -r -fo extwin.res $(cvars) /DNT extwin.rc
