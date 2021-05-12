#
#  makefile for Notes API sample program user_def.
#                 HP/UX version
#

# set TARGET to the name of the executable to create
TARGET1 = r_usrdef
TARGET2 = w_usrdef
TARGET = $(TARGET1) $(TARGET2)

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET1).c $(TARGET2).c proc_arg.c

# set HEADERS to the list of C include files in this program
HEADERS =

# set OBJECTS to the list of object files that must be linked
OBJECTS1 = r_usrdef.o proc_arg.o
OBJECTS2 = w_usrdef.o proc_arg.o

# Link this program with the bootstrap code notes0.o because
# this program is structured as a NotesMain.
BOOTOBJS = $(LOTUS)/notesapi/lib/hp/notes0.o

# CC defines the compiler. Set to "aCC" for HP C++ compiler.
CC = aCC
 
# Set CCOPTS - the compiler options.
CCOPTS = -c
# You may use -g1 flag for debugging:
#CCOPTS = -c -g1
 
# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS1 = -o $(TARGET1)
LINKOPTS2 = -o $(TARGET2)

# Notes API header files require UNIX to be defined.
DEFINES = -DUNIX -DHPUX

# set INCDIR to specify where to search for include files
INCDIR = $(LOTUS)/notesapi/include

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -lm

# the executable depends on the objects.
$(TARGET): $(OBJECTS1) $(OBJECTS2)
	$(CC) $(LINKOPTS1) $(OBJECTS1) $(BOOTOBJS) -L$(NOTESDIR) $(LIBS)
	$(CC) $(LINKOPTS2) $(OBJECTS2) $(BOOTOBJS) -L$(NOTESDIR) $(LIBS)

# the object files depend on the corresponding source files
.c.o:
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES)
