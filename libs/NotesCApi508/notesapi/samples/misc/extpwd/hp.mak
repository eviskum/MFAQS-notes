#
#  makefile for Notes API sample program extunix.
#                 HP/UX version
#

# set TARGET to the name of the executable to create
TARGET = libextpwd.sl

# set SOURCES to the list of C source files in this program
SOURCES = extunix.c

# set HEADERS to the list of C include files in this program
HEADERS =

# set OBJECTS to the list of object files that must be linked
OBJECTS = extunix.o

# CC defines the compiler. Set to "cc" for native HP C compiler.
CC = aCC

# Use "ld" to link 
LINK = ld

# Set CCOPTS - the compiler options. Specify -Aa for ANSI compliance.
CCOPTS = -c +z
# You may use -g1 flag for debugging:
#CCOPTS = -c +z -g1

# Set LINKOPTS - the linker options. Specify -o $(TARGET) to
# create TARGET rather than a.out.
LINKOPTS = -o $(TARGET) -n -b -c exports.hpx

# Notes API header files require UNIX to be defined.
DEFINES = -DUNIX -DHPUX -D_HPUX_SOURCE

# set INCDIR to specify where to search for include files
INCDIR = $(LOTUS)/notesapi/include

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)


# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -lm -ldld -lnsl_s -lc

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(LINK) $(LINKOPTS) $(OBJECTS) -L$(NOTESDIR) $(LIBS)

# the object files depend on the corresponding source files
.c.o:
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES)

clean :
	rm -rf extunix.o libextpwd.sl
