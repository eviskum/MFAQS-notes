#
#  makefile for Notes C++ API sample program agents/ragents
#                 AIX version
#
#

# set TARGET to the name of the executable to create
TARGET1 = agents
TARGET2 = ragents
TARGET = $(TARGET1) $(TARGET2)

# set SOURCES to the list of CPP source files in this program
SOURCES = $(TARGET1).cpp $(TARGET2).cpp

# allow the rules to work with .cpp files
.SUFFIXES : .c .cpp .s .o

# set OBJECTS to the list of object files that must be linked
OBJECTS1 = $(TARGET1).o
OBJECTS2 = $(TARGET2).o
OBJECTS = $(OBJECTS1) $(OBJECTS2)

# CPP defines the compiler. 
# ***  FOR NOTES R4.1+ USE xlC_r ***
CPP = xlC_r

# Set CPPOPTS - the compiler options.
CPPOPTS = -c
# You may use -g flag for debugging:
#CPPOPTS = -c -g

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# set NOTESCPP to specify where to find the toolkit
# set LNINCDIR to specify where to search for include files
# set LNLIBDIR to specify where to search for library files
NOTESCPP = $(LOTUS)/notescpp
LNINCDIR = $(NOTESCPP)/include
LNLIBDIR = $(NOTESCPP)/lib/aix

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS1 = -o $(TARGET1)
LINKOPTS2 = -o $(TARGET2)

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DAIX

# set LIBS to list all the libraries ld should link with.
# ***  FOR NOTES R4.1+ AIX THE NOTES LIBRARY IS libnotes_r.a ***
LIBS = -lnotes_r -lm -lcppaix$(CPPAPI_ID)

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CPP) $(LINKOPTS1) $(OBJECTS1) -L$(NOTESDIR) -L$(LNLIBDIR) $(LIBS)
	$(CPP) $(LINKOPTS2) $(OBJECTS2) -L$(NOTESDIR) -L$(LNLIBDIR) $(LIBS)
# the object files depend on the corresponding source files
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) -I$(LNINCDIR) $(SOURCES)

