#
#  makefile for Notes API sample program nsf_dump
#                 HP/UX version
#
#

# set TARGET to the name of the executable to create
TARGET = nsf_dump

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).c dumpitem.c dumpcd.c cdfile.c agents.c navigate.c mime.c

# set HEADERS to the list of C include files in this program
HEADERS = $(TARGET).h

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(TARGET).o dumpitem.o dumpcd.o cdfile.o agents.o navigate.o mime.o

# set BOOTOBJS to the list of bootstrap files that must be linked
BOOTOBJS = $(LOTUS)/notesapi/lib/hp/notes0.o

# CC defines the compiler. Set to "aCC" for HP C++ compiler.
CC = aCC

# Set CCOPTS - the compiler options.
CCOPTS = -c +W829
# You may use -g1 flag for debugging:
#CCOPTS = -c +W829 -g1

# Set LINKOPTS - the linker options passed to aCC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = -o $(TARGET)

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DHPUX

# set INCDIR to specify where to search for include files
INCDIR = $(LOTUS)/notesapi/include


# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)


# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -lm

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CC) $(LINKOPTS) $(OBJECTS) $(BOOTOBJS) -L$(NOTESDIR) $(LIBS)

# the object files depend on the corresponding source files
.c.o:
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES)


