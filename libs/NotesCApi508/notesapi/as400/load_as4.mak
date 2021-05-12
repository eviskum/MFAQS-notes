# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#		Makefile to load the C API and header files to the AS/400.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

!include "setup.mak"

main:  
  !echo .
  !echo Starting to load the AS/400 library and header files.
  !echo .

  !cttconn /h$(HOST) /ASn$(CONNAME)
  !ctttime sync

#  if exist $(AS400DIR)\qsys.lib\$(TEMP).lib\LNCAPI50.FILE 

  ctthcmd CRTLIB $(TEMP)
  ctthcmd DLTF FILE($(TEMP)/$(NOTESAPI))
  ctthcmd DLTF FILE($(TEMP)/RUNDOMCMD)
  ctthcmd CRTSAVF FILE($(TEMP)/$(NOTESAPI)) TEXT('C Api Rel $(REV): Save File')
  ctthcmd CRTSAVF FILE($(TEMP)/RUNDOMCMD) TEXT('RUNDOMCMD: Save File')

  ctthcmd CRTLIB $(NOTESSDK)

  ftp -s:mv2as400.ftp $(HOST)

# Only load the service program if it doesn't exist.
  if not exist $(AS400DIR)\qsys.lib\rundomcmd.lib\rundomcmd.pgm ctthcmd RSTLIB SAVLIB(RUNDOMCMD) DEV(*SAVF) SAVF($(TEMP)/RUNDOMCMD)
  if not exist $(AS400DIR)\qsys.lib\$(NOTESAPILIB).lib\NOTES0.MODULE ctthcmd RSTLIB SAVLIB($(NOTESAPILIB)) DEV(*SAVF) SAVF($(TEMP)/$(NOTESAPI))

  ctthcmd DLTLIB $(TEMP)
  ctthcmd CHGCURLIB $(NOTESAPILIB)

  mkdir ..\include
  cd ..\include
  ftp -s:..\as400\ftpapifl.ftp $(HOST)
  cd ..

  cttdis

  @echo .
  @echo The AS/400 library and headers have been loaded.
  @echo .

