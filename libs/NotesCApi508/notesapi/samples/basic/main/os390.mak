#
#  makefile for Notes API sample program main
#                 OS390 version
#
#

# Set TARGET to the name of the executable to create.
TARGET = main

# SOURCES is the list of C source files in this program.
SOURCES = $(TARGET).c

# HEADERS is the list of local C include files in this program.
HEADERS =

# OBJECTS is the list of object files that must be linked.
OBJECTS = $(TARGET).o

# CC is the compiler.
CC = unset _C89_OSUFFIX; c89

# Set CODE_SET to 'ascii' to compile with ascii format data.  Any
# other value (such as 'ebcdic') will compile with the OS/390 native
# ebcdic format.  This sample program supports either code set.
CODE_SET = ascii
#CODE_SET = ebcdic

# Set DEBUG to '-g' to produce output suitable for a source-level 
# debugger.
#DEBUG = -g

# Standard DEFINE symbols:
#       OS390           - compile for OS390 Open Edition
#       UNIX            - Notes API header files require UNIX
#       __STRING_CODE_SET="ISO8859-1" - compile with ascii code set.
#                         This example may be compiled as either "ascii"
#                         or "ebcdic", based on the CODE_SET setting.
.IF $(CODE_SET) == ascii
DEFINES = -DOS390 -DUNIX -D__STRING_CODE_SET__="ISO8859-1"
.ELSE
DEFINES = -DOS390 -DUNIX 
.END

# CCOPTS are the compiler options.
CCOPTS = -c $(DEBUG) -W0,DLL

# INCDIR specifies where to search for include files.  If compiling
# in ascii format, then the LIBASCII headers are required.
.IF $(CODE_SET) == ascii
INCDIR = -I$(LOTUS)/notesapi/include -I$(LIBASCII_PATH)
.ELSE
INCDIR = -I$(LOTUS)/notesapi/include
.END

# NOTESDIR specifies where to search for the Notes library file.
NOTESDIR = $(Notes_ExecDirectory)

# LINKOPTS are the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = $(DEBUG) -o $(TARGET)
# Here is how to produce a pre-linker and linker map.    
#LINKOPTS = $(DEBUG) -Wl,p,map -o $(TARGET)

# LIBRARY specifies the location of external libraries needed for
# object resolution.
.IF $(CODE_SET) == ascii
LIBRARY = $(LIBASCII_PATH)/libascii.a $(NOTESDIR)/libnotes.x
.ELSE
LIBRARY = $(NOTESDIR)/libnotes.x
.END

# The executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CC) $(LINKOPTS) $(OBJECTS) $(BOOTOBJS) $(LIBRARY)

# The object files depend on the corresponding source files.
.c.o:
	$(CC) $(CCOPTS) $(DEFINES) $(INCDIR) $(SOURCES)

