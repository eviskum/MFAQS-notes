#
#               Makefile for Notes C++ API sample program AGENTS/RAGENTS
#               Builds the sample AGENTS/RAGENTS for HP/UX platforms
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

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS1 = $(DEFINES) -Wl,+s -o $(TARGET1)
LINKOPTS2 = $(DEFINES) -Wl,+s -o $(TARGET2)

# set LIBS to list all the libraries ld should link with.
LIBS = -L$(NOTESDIR) -lnotes -L$(LNLIBDIR) -lcpphpx$(CPPAPI_ID)

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CPP) $(LINKOPTS1) $(OBJECTS1) $(LIBS)
	$(CPP) $(LINKOPTS2) $(OBJECTS2) $(LIBS)

# the object files depend on the corresponding source files
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) -I$(LNINCDIR) $(SOURCES)
