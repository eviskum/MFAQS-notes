#===========================================================================
# makefile for Notes C++ API sample linux version
# TARGET = name of src, obj, and exe files
TARGET = rtsearch
#===========================================================================

# set SOURCES to the list of C source files in this program
SOURCES = $(TARGET).cpp

# allow the rules to work with .cpp files
.SUFFIXES: .c .cpp .s .o

# set OBJECTS to the list of object files that must be linked
OBJECTS = $(SOURCES:.cpp=.o)

# CPP defines the compiler. Set to "g++"
CPP = g++

# LINK defines the linker. This is also set to "g++"
LINK = $(CPP)

# Set CPPOPTS - the compiler options.
CPPOPTS = -c -m486 -w -Os
# You may use -g flag for debugging. (Optimization is off too)
#CPPOPTS = -c -m486 -w -g

# set NOTESDIR to specify where to search for the Notes library file
NOTESDIR = $(Notes_ExecDirectory)

# set NOTESCPP to specify where to find the toolkit
# set LNINCDIR to specify where to search for include files
# set LNLIBDIR to specify where to search for library files
NOTESCPP = $(LOTUS)/notescpp
LNINCDIR = $(NOTESCPP)/include
LNLIBDIR = $(NOTESCPP)/lib/linux

# Set LINKOPTS - the linker options passed when linking.
# -o $(TARGET) causes compiler to create target rather than a.out
LINKOPTS = -L$(LNLIBDIR) -o $(TARGET)

# Notes API header files require UNIX to be defined.
DEFINES = -DUNIX -DLINUX -DLINUX20 -DPTHREAD_KERNEL -D_REENTRANT \
          -DUSE_THREADSAFE_INTERFACES -D_POSIX_THREAD_SAFE_FUNCTIONS \
          -DHANDLE_IS_32BITS -DHAS_BOOL -DHAS_DLOPEN -DFUTUREUNIX1 \
          -DUSE_PTHREAD_INTERFACES -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE

# Set name of the current release of the C++ API library
LNLIBCPP = $(LNLIBDIR)/libcpplin.so.$(CPPAPI_ID)

# set LIBS to list all the libraries we should link with.
LIBS = -lnotes -lm -lnsl -lposix -lpthread -lc -ldl -lresolv

#... Build the executable, which depends on the objects.
$(TARGET): $(OBJECTS)
	$(LINK) $(LINKOPTS) $(OBJECTS) -L$(NOTESDIR) \
    $(LNLIBCPP) $(LIBS)

#... Compile the objects, which depend on the source.
.cpp.o:
	$(CPP) $(CPPOPTS) $(DEFINES) -I$(LNINCDIR) $(SOURCES)


