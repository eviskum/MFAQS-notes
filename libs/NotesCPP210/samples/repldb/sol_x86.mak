#
#		Makefile for Notes C++ API sample program REPLDB
#		Builds the sample REPLDB for Solaris X86 platforms
#
#

# set TARGET to the name of the executable to create
TARGET = repldb

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).cpp 

# allow the rules to work with .cpp files
.SUFFIXES : .c .cpp .s .o

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(SOURCES:.cpp=.o)

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
LNLIBDIR = $(NOTESCPP)/lib/sol_x86

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = -mt -o $(TARGET) -R $(NOTESDIR)

# Notes API header files require UNIX to be defined.
DEFINES = -DSOLX86

# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -lcppx86$(CPPAPI_ID)

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CPP) $(LINKOPTS) $(OBJECTS) -L$(NOTESDIR) -L$(LNLIBDIR) $(LIBS)

# the object files depend on the corresponding source files
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) -I$(LNINCDIR) $(SOURCES)
