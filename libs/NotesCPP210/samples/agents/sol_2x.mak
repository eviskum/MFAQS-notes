#
#  makefile for Notes API sample program agents/ragents
#                 Solaris 2 version
#
#

# set TARGET to the name of the executable to create
TARGET1 = agents
TARGET2 = ragents
TARGET = $(TARGET1) $(TARGET2)

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET1).cpp $(TARGET2).cpp

# allow the rules to work with .cpp files
.SUFFIXES : .c .cpp .s .o

# set OBJECTS to the list of object files that must be linked
OBJECTS1 = $(TARGET1).o
OBJECTS2 = $(TARGET2).o
OBJECTS = $(OBJECTS1) $(OBJECTS2)

# CPP defines the compiler. Set to "CC" 
CPP = CC

# Set CPPOPTS - the compiler options.
CPPOPTS = -c -mt
# You may use -g flag for debugging:
#CPPOPTS = -c -mt -g

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# set NOTESCPP to specify where to find the toolkit
# set LNINCDIR to specify where to search for include files
# set LNLIBDIR to specify where to search for library files
NOTESCPP = $(LOTUS)/notescpp
LNINCDIR = $(NOTESCPP)/include
LNLIBDIR = $(NOTESCPP)/lib/sol_2x

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS1 = -mt -o $(TARGET1) -xcg92 -R $(NOTESDIR)
LINKOPTS2 = -mt -o $(TARGET2) -xcg92 -R $(NOTESDIR)

# Notes API header files require UNIX to be defined.
DEFINES =  -DSOLSPARC

LIBS = -lnotes -lcppsun$(CPPAPI_ID)

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CPP) $(LINKOPTS1) $(OBJECTS1) -L$(NOTESDIR) -L$(LNLIBDIR) $(LIBS)
	$(CPP) $(LINKOPTS2) $(OBJECTS2) -L$(NOTESDIR) -L$(LNLIBDIR) $(LIBS)

# the object files depend on the corresponding source files
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) -I$(LNINCDIR) $(SOURCES)

