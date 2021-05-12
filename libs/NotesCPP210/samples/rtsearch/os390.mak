#
#		Makefile for Notes C++ API sample program RTSEARCH
#		Builds the sample RTSEARCH for the OS/390 platform
#
#

# set TARGET to the name of the executable to create
TARGET = rtsearch

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).cpp

# allow the rules to work with .cpp files
.SUFFIXES : .c .cpp .s .o

# Set DEBUGGER to '-g' to produce output suitable for a source-level
# debugger.
#DEBUGGER = -g

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(SOURCES:.cpp=.o)

# NOTESCPP to specifies where to find the toolkit.
NOTESCPP = $(LOTUS)/notescpp

# CPP defines the compiler. 
CPP = unset _CXX_OSUFFIX; cxx

# CPPOPTS are the compiler options.
#       -c indicates a compile (only).
CPPOPTS = -c $(DEBUGGER)

# Standard DEFINE symbols:
#       OS390           - compile for OS390 Open Edition
#       UNIX            - Notes API header files require UNIX
DEFINES = -DOS390 -DUNIX

# LNINCDIR specifies where to search for include files.
LNINCDIR = -I$(NOTESCPP)/include

# LINKOPTS are the linker options passed to CC when linking.
# -o $TARGET causes compiler to create acllog rather than a.out.
LINKOPTS = $(DEBUGGER) -o $(TARGET)
# Here is how to produce a pre-linker and linker map.
#LINKOPTS = $(DEBUGGER) -Wl,p,map -o $(TARGET)

# LIBRARY specifies the location of external libraries needed for
# object resolution.
LIBRARY = $(NOTESCPP)/lib/os390/lcpps$(CPPAPI_ID).x $(Notes_ExecDirectory)/libnotes.x

# the executable depends on the objects.
$(TARGET): $(OBJECTS)
	$(CPP) $(LINKOPTS) $(OBJECTS) $(LIBRARY)

# the object files depend on the corresponding source files
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) $(LNINCDIR) $(SOURCES)

