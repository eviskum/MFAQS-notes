#
#  makefile for Notes API sample program extunix
#                  Solaris 2 SPARC Edition
#
#

# set TARGET to the name of the executable to create
TARGET = libextpsw.so

# set SOURCES to the list of C source files in this program
SOURCES = extunix.c

# set HEADERS to the list of C include files in this program
HEADERS =

# set OBJECTS to the list of object files that must be linked
OBJECTS = extunix.o

# CC defines the compiler. 
CC = cc

# Set CCOPTS - the compiler options.
CCOPTS = -c
# You may use -g flag for debugging:
#CCOPTS = -c -g

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = -o $(TARGET) -G

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DSOLARIS

# set INCDIR to specify where to search for include files
INCDIR = $(LOTUS)/notesapi/include

# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -L/usr/dt/lib -L/usr/openwin/lib

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CC) $(LINKOPTS) $(OBJECTS) -L$(NOTESDIR) $(LIBS)

# the object files depend on the corresponding source files
.c.o:
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES)

clean :
	rm -rf libextpsw.so extunix.o
