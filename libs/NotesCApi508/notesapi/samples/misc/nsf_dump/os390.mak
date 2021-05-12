#
#  makefile for Notes API sample program nsf_dump
#                 OS390 version
#
#

# Set TARGET to the name of the executable to create.
TARGET = nsf_dump

# SOURCES is the list of C source files in this program.
SOURCES = $(TARGET).c dumpitem.c dumpcd.c cdfile.c agents.c navigate.c mime.c

# HEADERS is the list of local C include files in this program.
HEADERS = nsf_dump.h

# OBJECTS is the list of object files that must be linked.
OBJECTS = $(TARGET).o dumpitem.o dumpcd.o cdfile.o agents.o navigate.o mime.o

# CC is the compiler.
CC = unset _C89_OSUFFIX; c89

# Set DEBUG to '-g' to produce output suitable for a source-level
# debugger.
#DEBUG = -g

# Standard DEFINE symbols:
#       OS390           - compile for OS390 Open Edition
#       UNIX            - Notes API header files require UNIX
#       __STRING_CODE_SET="ISO8859-1" - compile with ascii code set.
DEFINES = -DOS390 -DUNIX -D__STRING_CODE_SET__="ISO8859-1"

# CCOPTS are the compiler options.
CCOPTS = -c $(DEBUG) -W0,DLL

# INCDIR specifies where to search for include files.
INCDIR = -I$(LOTUS)/notesapi/include -I$(LIBASCII_PATH)

# Link this program with the bootstrap code notes0.o because
# this program is structured as a NotesMain.
BOOTOBJS = $(LOTUS)/notesapi/lib/os390/notes0.o

# NOTESDIR specifies where to search for the Notes library file.
NOTESDIR = $(Notes_ExecDirectory)

# LINKOPTS are the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = $(DEBUG) -o $(TARGET)
# Here is how to produce a pre-linker and linker map.
#LINKOPTS = $(DEBUG) -Wl,p,map -o $(TARGET)

# LIBRARY specifies the location of external libraries needed for
# object resolution.
LIBRARY = $(LIBASCII_PATH)/libascii.a $(NOTESDIR)/libnotes.x

# The executable depends on the objects.
$(TARGET): $(OBJECTS)
        $(CC) $(LINKOPTS) $(OBJECTS) $(BOOTOBJS) $(LIBRARY)

# The object files depend on the corresponding source files.
.c.o:
        $(CC) $(CCOPTS) $(DEFINES) $(INCDIR) $(SOURCES)

