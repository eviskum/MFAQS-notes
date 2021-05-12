@echo off

set HOST=
set DIR=c:\notesapi
set AS400DIR=f:

set REV="5.0"
set DEBUG=1
set CONNAME=con1

set NOTESSDK=qntcsdk
set NOTESAPILIB=qnotesapi
set NOTESAPI=lncapi50
set QLIBASCII=qlibascii
set LIBASCII=libascii
set QNOTES=qnotes
set LIBNOTES=libnotes
set NOTES0=notes0

set TEMP=TEMP0423
set BACKUP=SDKBACKUP

if "%DEBUG%" == "0" goto nodebug
set ICCAS_ARGS=/Til /W2 /AScp850 /qnoro /ASl%NOTESSDK% /DUNIX /DEBCDIC_RTL /DOS400 /DHANDLE_IS_32BITS /D_ALL_SOURCE /D__STRING_CODE_SET__ /D_IFS_IO__ /Li+ /Ls+ /Lj+ /Fl+ /ASi+ /I%DIR%\include
goto continue
:nodebug
set ICCAS_ARGS=/W2 /AScp850 /qnoro /ASl%NOTESSDK% /DUNIX /DEBCDIC_RTL /DOS400 /DHANDLE_IS_32BITS /D_ALL_SOURCE /D__STRING_CODE_SET__ /D__IFS_IO__ /O+ /ASi+ /I%DIR%\include
:continue
:done