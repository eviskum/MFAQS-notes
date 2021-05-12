#
# makefile for Notes API sample program USER_DEF
# OS/2 32-bit version using IBM VisualAge C++ compiler and tools.
#
# This makefile assumes that the INCLUDE and LIB environment variables
# are set up to point at the Notes and C "include" and "lib" directories.

# Targets.

ALL: W_USRDEF.EXE R_USRDEF.EXE

# Dependencies.
           
W_USRDEF.EXE: W_USRDEF.OBJ PROC_ARG.OBJ
R_USRDEF.EXE: R_USRDEF.OBJ PROC_ARG.OBJ

W_USRDEF.OBJ: W_USRDEF.C USER_DEF.H
R_USRDEF.OBJ: R_USRDEF.C USER_DEF.H
PROC_ARG.OBJ: PROC_ARG.C USER_DEF.H

# Compilation command. 

.C.OBJ:
    icc /C+ /Ti+ /Sp1 /Gs+ /DOS2_2x /W3 /Wcnd- $*.C

# Link command.
 
.OBJ.EXE:
    ILINK /NOFREEFORMAT /CO /PMTYPE:VIO /ST:32768 /BASE:65536 /ALIGN:16 /EXEPACK PROC_ARG.OBJ $*.obj NOTES0, $*.EXE, NUL, NOTES.LIB, ;
