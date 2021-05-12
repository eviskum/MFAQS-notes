#
#  makefile for Notes API sample program nsf_dump
#                 Solaris 2 SPARC Edition
#
#

# set TARGET to the name of the executable to create
TARGET = nsf_dump

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).c dumpitem.c dumpcd.c cdfile.c agents.c navigate.c mime.c

# set HEADERS to the list of C include files in this program
HEADERS = nsf_dump.h

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(TARGET).o dumpitem.o dumpcd.o cdfile.o agents.o navigate.o mime.o

# Link this program with the bootstrap code notes0.o because
# this program is structured as a NotesMain.
BOOTOBJS = $(LOTUS)/notesapi/lib/sol_2x/notes0.o

# CC defines the compiler. Set to "cc"
CC = cc

# Set CCOPTS - the compiler options.
CCOPTS = -c
#You may use -g flag for debugging:
#CCOPTS = -c -g

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = -o $(TARGET) -xcg92 -R $(NOTESDIR)

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DSOLARIS

# set INCDIR to specify where to search for include files
INCDIR = $(LOTUS)/notesapi/include

# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -lm -lnsl -lsocket -lposix4

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CC) $(LINKOPTS) $(OBJECTS) $(BOOTOBJS) -L$(NOTESDIR) $(LIBS)

# the object files depend on the corresponding source files
.c.o:
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES)

