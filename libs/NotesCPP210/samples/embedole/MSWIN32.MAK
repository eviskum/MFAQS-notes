# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#		samples\embedole\mswin32.mak
#		Makefile for Notes C++ API sample program RTBUTTON
#		Builds the sample EMBEDOLE for Win32 platforms
#		(Windows 95, Windows NT, Windows NT for Alpha AXP)
#		This Makefile Builds the application to run with the DLL
#		form of the C++ API.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the correct Notes C and C++ "include" and 
# "lib" directories for your environment.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Standard Windows NT make definitions
!include <win32.mak>

#
# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string.
#
!IF "$(CPU)" == "i386"
lncpuflags = -D_X86_=1 -Zp1
!ELSE
!IF "$(CPU)" == "ALPHA"
lncpuflags = -D_ALPHA_=1
!ENDIF
!ENDIF

# The name of the program.
PROGNAME = EMBEDOLE

# Link command.
# Since this is a console application that makes OLE calls, the OLE libraries
# must be explicitly included.  Those libraries are included in the standard
# $(olelibsmt) macro when building Windows applications.
$(PROGNAME).EXE: $(PROGNAME).OBJ MSBITMAP.OBJ
    $(link) $(linkdebug) $(conflags) -out:$@ $** $(conlibsmt) gdi32.lib \
		ole32.lib uuid.lib notescpp.lib libcimt.lib

# Compilation commands.
$(PROGNAME).OBJ: $(PROGNAME).CPP
 $(cc) $(cdebug) -c -W3 -nologo -GX -MT -DCRTAPI1=_cdecl -DCRTAPI2=_cdecl -DW32 -DNODLL \
		$(lncpuflags) $(cvars) $*.cpp

MSBITMAP.OBJ : MSBITMAP.C
 $(cc) $(cdebug) -c -W3 -nologo -GX -MT -DCRTAPI1=_cdecl -DCRTAPI2=_cdecl -DW32 -DNODLL \
		$(lncpuflags) $(cvars) $*.c
