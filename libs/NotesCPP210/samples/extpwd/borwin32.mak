# 
# makefile for Notes C++ API sample program "extpwd"
# Windows NT and Windows 95 version
#
# This makefile is designed for use on Win32 systems with the
# Borland C++ (version 5) 32-bit compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# The name of the project
PROJNAME = nextpwd

!ifdef DEBUG
CCDEBUG=-k -y
LDEBUG=-v
MAPFILE=$&
!else
LDEBUG=-x
!endif

CCWARN=-w-pck -w-inl -w-pia -w-aus -w-sig -w-rch -w-hid -w-use
CCOPTS=-Oi -AT -a1 -wii -DNT -DW32 -DBCC -b -c -i64 -tWDE $(CCDEBUG)
LOPTS=-c -Tpd -ap -w-inq $(LDEBUG) -L$(LIB)

# Dependencies
$(PROJNAME).dll: extpwd.obj extman.obj
extman.obj: extman.c
extpwd.obj: extpwd.c


# Compilation command.  
.c.obj:       
 bcc32 @&&!
$(CCOPTS) \
$(CCWARN) \
-I$(INCLUDE) \
$.
!

# Link command.
$(PROJNAME).dll:
  tlink32 @&&!
$(LOPTS) \
c0d32.obj extman.obj extpwd.obj,\
nextpwd.dll,\
$(MAPFILE),\
notes.lib import32.lib cw32mt.lib,mswin32.def
!
