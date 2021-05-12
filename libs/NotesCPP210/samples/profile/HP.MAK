#
#               Makefile for Notes C++ API sample program PROFILE
#               Builds the sample PROFILE for HP/UX platforms
#
#

# set TARGET to the name of the executable to create
TARGET = profile

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).cpp

# allow the rules to work with .cpp files
.SUFFIXES : .c .cpp .s .o

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(SOURCES:.cpp=.o)

# CPP defines the compiler. Set to "CC" for native HP C++ compiler.
CPP = CC

# Link defines the linker
Link = CC

# Set CPPOPTS - the compiler options. Specify -Aa for ANSI compliance.
#
# The flag D_IOSTREAM_INIT_NOT_NEEDED is needed to prevent creating
# a global iostream_init object - which runs afoul of an HP-UX bug.
#
# NOTE: This has been changed 14Aug97 to accomodate changes to HPUX build of C++ API.
#
CPPOPTS = -c -Aa +eh +a1 -DHPUX -D_IOSTREAM_INIT_NOT_NEEDED -D_REENTRANT -D_THREAD_SAFE
# You may use -g flag for debugging:
#CPPOPTS = -c -Aa -g +eh +a1 -DHPUX -D_IOSTREAM_INIT_NOT_NEEDED -D_REENTRANT -D_THREAD_SAFE

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# set NOTESCPP to specify where to find the toolkit
# set LNINCDIR to specify where to search for include files
# set LNLIBDIR to specify where to search for library files
NOTESCPP = $(LOTUS)/notescpp
LNINCDIR = $(NOTESCPP)/include
LNLIBDIR = $(NOTESCPP)/lib/hp

# Set LINKOPTS - the linker options passed to CC when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
#
# NOTE: This has been changed 14Aug97 to accomodate changes to HPUX build of C++ API.
#
LINKOPTS =  -Wl,+s -o $(TARGET) +eh +a1

# Notes API header files require UNIX to be defined.
DEFINES =  -DUNIX -DHPUX

# set LIBS to list all the libraries ld should link with.
LIBS = -lnotes -lm -ldld -lnsl_s -lcpphpx$(CPPAPI_ID)

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CPP) $(LINKOPTS) $(OBJECTS) -L$(NOTESDIR) -L$(LNLIBDIR) $(LIBS)

# the object files depend on the corresponding source files
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) -I$(LNINCDIR) $(SOURCES)

