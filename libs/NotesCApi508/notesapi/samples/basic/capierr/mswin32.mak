#
# Makefile for Notes API sample program CapiErr.
# Windows 32-bit version using Microsoft 32-bit Visual C++ compiler
# and linker.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Standard Windows 32-bit make definitions
!include <ntwin32.mak>

# The name of the program.
PROGNAME = CapiErr

#
# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
!ELSE
cpuflags = -Zpl
!ENDIF

# Dependencies
$(PROGNAME).exe: $(PROGNAME).obj $(PROGNAME).res $(PROGNAME)D.obj StdAfx.obj 
$(PROGNAME).obj		: $(PROGNAME).cpp
$(PROGNAME).res		: $(PROGNAME).rc
	rc -fo $(PROGNAME).res /DNT /d_AFXDLL $(PROGNAME).rc
$(PROGNAME)Dlg.obj		: $(PROGNAME)D.cpp
StdAfx.obj		: StdAfx.cpp



# Compilation command.  
.cpp.obj:
   $(cc) -c -W3 -nologo -GX -MD -O2 -D_MBCS -FD -DW32 -DNODLL -D_AFXDLL -D_X86_=1 $(cpuflags) $*.cpp


# Link command.
.obj.exe:
    $(link) $(DEF_FILE) -NODEFAULTLIB:libcmt.lib notes.lib -subsystem:windows -out:$@ $** 
