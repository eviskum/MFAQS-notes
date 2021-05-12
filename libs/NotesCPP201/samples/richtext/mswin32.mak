# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#		samples\richtext\mswin32.mak
#		Build the sample RICHTEXT for Win32 platforms
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
PROGNAME = RICHTEXT

# Dependencies
$(PROGNAME).EXE: $(PROGNAME).OBJ
$(PROGNAME).OBJ: $(PROGNAME).CPP

# Compilation command.  
.CPP.OBJ:
 $(cc) $(cdebug) -c -W3 -nologo -GX -MT -DCRTAPI1=_cdecl -DCRTAPI2=_cdecl -DW32 -DNODLL \
		$(lncpuflags) $(cvars) $*.cpp

# Link command.
.OBJ.EXE:
    $(link) $(linkdebug) $(conflags) -out:$@ $** $(conlibsmt) \
		notescpp.lib libcimt.lib
