# 
# makefile for Notes C++ API sample program "adminp"
# Windows NT and Windows 95 version
#
# This makefile is designed for use on Win32 systems with the
# Borland C++ (version 5) 32-bit compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# The name of the program.
PROGNAME = adminp

!ifdef DEBUG
CCDEBUG=-k -y
LDEBUG=-v
MAPFILE=$&
!else
LDEBUG=-x
!endif

CCWARN=-w-pck -w-inl -w-pia -w-aus -w-sig -w-rch -w-hid -w-use
CCOPTS=-Oi -AT -a1 -w -DW32 -DBCC -b -c -i64 -tWDE $(CCDEBUG)
LOPTS=-c -Tpe -ap -w-inq $(LDEBUG) -L$(LIB)

# Dependencies
$(PROGNAME).EXE: $(PROGNAME).OBJ
$(PROGNAME).OBJ: $(PROGNAME).CPP

# Compilation command.  
.cpp.OBJ:       
 bcc32 @&&!
$(CCOPTS) \
$(CCWARN) \
-I$(INCLUDE) \
$.
!

# Link command.
.obj.exe: 
  tlink32 @&&!
$(LOPTS) \
c0x32.obj *.obj,\
$&,\
$(MAPFILE),\
notescpp.lib import32.lib cw32mt.lib
!
