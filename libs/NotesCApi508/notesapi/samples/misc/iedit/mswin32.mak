# 
#  makefile for Notes API sample program IEDIT
#  Windows 32-bit version using Microsoft 32-bit Visual C++
#  compiler and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

cpuflags = -Zp
outfilename = niedit
defname = mswin32

# Master dependency

all : $(outfilename).dll


# Link command.
           
$(outfilename).dll : iedit.obj ieditwin.obj $(defname).def
    $(link) $(linkdebug) -base:0x1C000000 -stack:0 \
    -dll -entry:_DllMainCRTStartup$(DLLENTRY) \
    -def:$(defname).def \
    -out:$(outfilename).dll \
    iedit.obj \
    ieditwin.obj \
    $(conlibs) $(guilibs) notes.lib


# Compilation command.  

iedit.obj : iedit.c iedit.h
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) iedit.c

ieditwin.obj : ieditwin.c iedit.h
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) ieditwin.c

