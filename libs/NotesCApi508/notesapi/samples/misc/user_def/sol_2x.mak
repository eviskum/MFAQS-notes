#
#  makefile for Notes API sample program user_def
#                 Solaris 2 SPARC Edition
#
#

# set TARGET to the name of the executable to create
TARGET1 = r_usrdef
TARGET2 = w_usrdef
TARGET = $(TARGET1) $(TARGET2)

# set SOURCES to the list of C source files in this program
SOURCES = r_usrdef.c w_usrdef.c proc_arg.c

# set HEADERS to the list of C include files in this program
HEADERS = $(TARGET).h

# set OBJECTS to the list of object files that must be linked
OBJECTS1 = r_usrdef.o proc_arg.o
OBJECTS2 = w_usrdef.o proc_arg.o

# Link this program with the bootstrap code notes0.o because
# this program is structured as a NotesMain.
BOOTOBJS = $(LOTUS)/notesapi/lib/sol_2x/notes0.o

# CC defines the compiler. Set to "cc" 
CC = cc

# Set CCOPTS - the compiler options.
CCOPTS = -c
# You may use -g flag for debugging:
#CCOPTS = -c -g

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS1 = -o $(TARGET1) -xcg92 -R $(NOTESDIR)
LINKOPTS2 = -o $(TARGET2) -xcg92 -R $(NOTESDIR)

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DSOLARIS

# set INCDIR to specify where to search for include files
INCDIR = $(LOTUS)/notesapi/include

# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -lm -lnsl -lsocket -lposix4

# the executable depends on the objects.
$(TARGET): $(OBJECTS1)  $(OBJECTS2)
	$(CC) $(LINKOPTS1) $(OBJECTS1) $(BOOTOBJS) -L$(NOTESDIR) $(LIBS)
	$(CC) $(LINKOPTS2) $(OBJECTS2) $(BOOTOBJS) -L$(NOTESDIR) $(LIBS)

# the object files depend on the corresponding source files
.c.o:
	$(CC) $(CCOPTS) $(DEFINES) -I$(INCDIR) $(SOURCES)
