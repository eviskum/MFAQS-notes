##
#  makefile for Notes API sample programs cdfwrite and cdfread. 
#                 HP/UX version
#
#

# set TARGET to the name of the executable to create
TARGET1 = cdfwrite
TARGET2 = cdfread

# build two executables, cdfwrite and cdfread
all: cdfwrite cdfread

# set SOURCES1 and 2 to the names of the source files for these programs
SOURCES1 = $(TARGET1).c
SOURCES2 = $(TARGET2).c

# set HEADERS to the list of C include files in this program
HEADERS = cdfile.h

# Set OBJECTS 1 and OBJECT2 to the list of object files created by this
# sample.
OBJECTS1 = $(TARGET1).o
OBJECTS2 = $(TARGET2).o

# set BOOTOBJS to the list of bootstrap files that must be linked
BOOTOBJS = $(LOTUS)/notesapi/lib/hp/notes0.o

# CC defines the compiler. Set to "aCC" for native HP C++ compiler.
CC = aCC
 
# Set CCOPTS - the compiler options. 
CCOPTS = -c +W829 
# You may use -g1 flag for debugging:
#CCOPTS = -c +W829 -g1

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
####
LINKOPTS1 = -o $(TARGET1)
LINKOPTS2 = -o $(TARGET2)

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DHPUX

# set INCDIR to specify where to search for include files
INCDIR = $(LOTUS)/notesapi/include


# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)


# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -lm

# the executables depend on the objects.
$(TARGET1): $(OBJECTS1)
	$(CC) $(LINKOPTS1) $(OBJECTS1) $(BOOTOBJS) -L$(NOTESDIR) $(LIBS)

$(TARGET2): $(OBJECTS2)
	$(CC) $(LINKOPTS2) $(OBJECTS2) $(BOOTOBJS) -L$(NOTESDIR) $(LIBS)

# the object files depend on the corresponding source files and header files.
$(OBJECTS1): $(SOURCES1) $(HEADERS)
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES1)
 
$(OBJECTS2): $(SOURCES2) $(HEADERS)
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES2)

