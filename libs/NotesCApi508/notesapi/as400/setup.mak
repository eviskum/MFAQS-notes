CC = iccas

HOST = 
CONNAME = con1

NOTESSDK = qntcsdk
NOTESAPILIB = qnotesapi
NOTES0 = notes0
NOTESAPI = lncapi50
QNOTES = qnotes
LIBNOTES = libnotes
QLIBASCII = qlibascii
LIBASCII = libascii

DIR = c:\notesapi
TEMP = temp0423
AS400DIR = f:

#Debug Mode 
DEBUG_FLAGS = /Til /Fl+ /Fo+ 
#Optimized Mode 
# DEBUG_FLAGS = /O+ 
DECLARE = /DUNIX /DOS400 /D_ALL_SOURCE /D__IFS_IO__ /DEBCDIC_RTL /D__STRING_CODE_SET__

ICCAS_ARGS = $(DEBUG_FLAGS) /W2 /AScp850 /qnoro /ASl$(NOTESSDK) $(DECLARE) /ASi+ /I$(DIR)\include