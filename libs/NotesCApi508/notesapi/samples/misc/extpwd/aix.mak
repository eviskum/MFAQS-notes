#
#  makefile for Notes API sample program extunix
#                 AIX version
#
#

# set TARGET to the name of the executable to create
TARGET = libextpsw.a

# set SOURCES to the list of C source files in this program
SOURCES = extunix.c

# set HEADERS to the list of C include files in this program
HEADERS =

# set OBJECTS to the list of object files that must be linked
OBJECTS = extunix.o

# CC defines the compiler. 
# ***  FOR NOTES R4.1+ USE xlC_r ***
CC = xlC_r

# Set CCOPTS - the compiler options.
CCOPTS = -c
# You may use -g flag for debugging:
#CCOPTS = -c -g

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = -o $(TARGET) -bE:exports.aix -bM:SRE -bnoentry

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DAIX

# set INCDIR to specify where to search for include files
INCDIR = $(LOTUS)/notesapi/include

# set LIBS to list all the libraries ld should link with.
# ***  FOR NOTES R4.1+ AIX THE NOTES LIBRARY IS libnotes_r.a ***
LIBS = -lnotes_r -lm -lc_r

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	ld $(LINKOPTS) $(OBJECTS) -L$(NOTESDIR) $(LIBS)

# the object files depend on the corresponding source files
.c.o:
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES)

clean :
	rm -rf libextpsw.a extunix.o
