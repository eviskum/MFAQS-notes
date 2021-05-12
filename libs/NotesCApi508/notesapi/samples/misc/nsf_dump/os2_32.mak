#
# makefile for Notes API sample program NSF_DUMP
# OS/2 32-bit version using the IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Dependencies

nsf_dump.exe : nsf_dump.obj dumpitem.obj dumpcd.obj cdfile.obj \
               agents.obj navigate.obj mime.obj

nsf_dump.obj : nsf_dump.c nsf_dump.h

dumpitem.obj : dumpitem.c nsf_dump.h

dumpcd.obj : dumpcd.c nsf_dump.h

cdfile.obj : cdfile.c nsf_dump.h

agents.obj : agents.c nsf_dump.h

navigate.obj : navigate.c nsf_dump.h

mime.obj : mime.c nsf_dump.h

# Compilation command.

.C.OBJ:
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Link command.

.OBJ.EXE:
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK $** NOTES0, $*.EXE, NUL, NOTES.LIB;
