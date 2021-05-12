#
#               Makefile for Notes C++ API sample program REPLDB
#               Builds the sample REPLDB for HP/UX platforms
#
#

# set TARGET to the name of the executable to create
TARGET = repldb

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).cpp

# allow the rules to work with .cpp files
.SUFFIXES : .c .cpp .s .o

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(TARGET).o

# CPP defines the compiler. Set to "aCC" for native HP C++ compiler.
CPP = aCC

# Set CPPOPTS - the compiler options passed to aCC when compiling.
CPPOPTS = -c +W740,741,749
# You may use -g flag for debugging:
#CPPOPTS = -c +W740,741,749 -g

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# set NOTESCPP to specify where to find the toolkit
# set LNINCDIR to specify where to search for include files
# set LNLIBDIR to specify where to search for library files
NOTESCPP = $(LOTUS)/notescpp
LNINCDIR = $(NOTESCPP)/include
LNLIBDIR = $(NOTESCPP)/lib/hp

DEFINES = -DHPUX -D_REENTRANT -D_THREAD_SAFE -DRWSTD_MULTI_THREAD -DRW_MULTI_THREAD -D_IOSTREAM_INIT_NOT_NEEDED

# Set LINKOPTS - the linker options passed to aCC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = $(DEFINES) -Wl,+s -o $(TARGET)

# set LIBS to list all the libraries ld should link with.
LIBS = -L$(NOTESDIR) -lnotes -L$(LNLIBDIR) -lcpphpx$(CPPAPI_ID)

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CPP) $(LINKOPTS) $(OBJECTS)  $(LIBS)

# the object files depend on the corresponding source files
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) -I$(LNINCDIR) $(SOURCES)
