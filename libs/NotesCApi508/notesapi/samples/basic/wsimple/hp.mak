#
#  makefile for Notes API sample program wsimple
#                 HP/UX version
#
#

# set TARGET to the name of the executable to create
TARGET = wsimple

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).c

# set HEADERS to the list of C include files in this program
HEADERS =

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(TARGET).o

# set BOOTOBJS to the list of bootstrap files that must be linked
BOOTOBJS = $(LOTUS)/notesapi/lib/hp/notes0.o


# CC defines the compiler. Set to "aCC" for native HP C++ compiler.
CC = aCC

# Set CCOPTS - the compiler options. 
CCOPTS = -c 
# You may use -g1 flag for debugging:
#CCOPTS = -c  -g1

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
####
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
