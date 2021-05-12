#
#		Makefile for Notes C++ API sample program COPYDB
#		Builds the sample COPYDB for AIX platforms
#
#

# set TARGET to the name of the executable to create
TARGET = copydb

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).cpp 

# allow the rules to work with .cpp files
.SUFFIXES : .c .cpp .s .o

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(SOURCES:.cpp=.o)

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
LINKOPTS = -o $(TARGET)

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DAIX

# set LIBS to list all the libraries ld should link with.
# ***  FOR NOTES R4.1+ AIX THE NOTES LIBRARY IS libnotes_r.a ***
LIBS = -lnotes_r -lm -lcppaix$(CPPAPI_ID)

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CPP) $(LINKOPTS) $(OBJECTS) -L$(NOTESDIR) -L$(LNLIBDIR) $(LIBS)

# the object files depend on the corresponding source files
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) -I$(LNINCDIR) $(SOURCES)

