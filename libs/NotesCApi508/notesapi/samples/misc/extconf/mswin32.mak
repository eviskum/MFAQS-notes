# Standard Windows NT make definitions
!include <ntwin32.mak>

#
# DEC Alpha doesn't want the structures to be packed so we use the CPU
# type to conditionally add it as part of compile string
#
!IF "$(CPU)" == "ALPHA"
cpuflags = 
outfilename = aextconf
defname = mswin32a
!ELSE
cpuflags = -Zp
outfilename = nextconf
defname = mswin32
!ENDIF

all : $(outfilename).dll

.c.obj :
    $(cc) $(cdebug) $(cflags) $(cpuflags) -Ow -DNT $(cvars) $*.c


$(outfilename).dll : extconf.obj extcwin.obj $(defname).def
    $(link) $(linkdebug) \
        -dll -def:$(defname).def \
         -entry:_DllMainCRTStartup$(DLLENTRY) \
         -out:$(outfilename).dll \
        extconf.obj extcwin.obj \
        $(guilibs) notes.lib

extconf.obj : extconf.c

extcwin.obj : extcwin.c
