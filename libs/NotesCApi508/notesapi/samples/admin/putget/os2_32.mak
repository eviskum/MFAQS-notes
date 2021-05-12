#
# makefile for Notes API sample program PUTGET
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Targets

ALL: IPUTNOTE.EXE IGETNOTE.EXE

# Dependencies

GET_UI.OBJ:  os2_32\GET_UI.C CONSTANT.H PUTGET.H
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- os2_32\$*.C

PUT_UI.OBJ:  os2_32\PUT_UI.C CONSTANT.H PUTGET.H
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- os2_32\$*.C

PUTNOTE.OBJ: PUTNOTE.C CONSTANT.H FILE_IO.H MISC.H FIELDS.H
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

GETNOTE.OBJ: GETNOTE.C CONSTANT.H FILE_IO.H MISC.H FIELDS.H
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

FIELDS.OBJ:  FIELDS.C  CONSTANT.H FILE_IO.H MISC.H
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

FILE_IO.OBJ: FILE_IO.C CONSTANT.H
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

MISC.OBJ:    MISC.C CONSTANT.H
    icc /C+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

IPUTNOTE.EXE: PUT_UI.OBJ PUTNOTE.OBJ FIELDS.OBJ FILE_IO.OBJ MISC.OBJ
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK PUT_UI.OBJ PUTNOTE.OBJ FIELDS.OBJ FILE_IO.OBJ MISC.OBJ, $*.EXE, , NOTES.LIB, ;

IGETNOTE.EXE: GET_UI.OBJ GETNOTE.OBJ FIELDS.OBJ FILE_IO.OBJ MISC.OBJ
    ILINK /NOFREEFORMAT /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK GET_UI.OBJ GETNOTE.OBJ FIELDS.OBJ FILE_IO.OBJ MISC.OBJ, $*.EXE, , NOTES.LIB, ;
