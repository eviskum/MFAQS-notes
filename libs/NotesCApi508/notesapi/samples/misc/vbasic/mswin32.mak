#
# Makefile for Notes C API sample program api_wrap.dll.
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler
# and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.
#
# Standard Windows 32-bit make definitions
!include <ntwin32.mak>


cpuflags = -Zp
outfilename = api_wrap
defname = mswin32


all : $(outfilename).DLL

$(outfilename).DLL : API_WRAP.OBJ $(defname).DEF
    $(link) $(linkdebug) \
        -dll -def:$(defname).DEF \
        -out:$(outfilename).DLL \
        API_WRAP.OBJ \
        $(conlibsdll) notes.lib

 
API_WRAP.OBJ :  API_WRAP.C
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvarsdll) API_WRAP.C
