CALL SETUP.BAT
CALL CONN.BAT

ctthcmd /ASn%CONNAME% /Q CRTLIB %NOTESSDK%
ctthcmd /ASn%CONNAME% /Q CRTLIB %TEMP%
ctthcmd /ASn%CONNAME% /Q DLTF FILE(%TEMP%/%NOTESAPI%)
ctthcmd /ASn%CONNAME% /Q DLTF FILE(%TEMP%/RUNDOMCMD)
ctthcmd /ASn%CONNAME% /Q CRTSAVF FILE(%TEMP%/%NOTESAPI%) TEXT('C Api Rel %REV%: Save File')
ctthcmd /ASn%CONNAME% /Q CRTSAVF FILE(%TEMP%/RUNDOMCMD) TEXT('RUNDOMCMD: Save File')
CALL ftp -s:mv2as400.ftp %HOST%
if exist %AS400DIR%\qsys.lib\rundomcmd.lib\rundomcmd.pgm goto do_rest
ctthcmd /ASn%CONNAME% /Q RSTLIB SAVLIB(RUNDOMCMD) DEV(*SAVF) SAVF(%TEMP%/RUNDOMCMD)
:do_rest
if exist %AS400DIR%\qsys.lib\%NOTESAPILIB%.lib\%NOTESAPI%.srvpgm goto do_rest2
ctthcmd /ASn%CONNAME% /Q CRTLIB %BACKUP%
ctthcmd /ASn%CONNAME% /Q DLTF FILE(%BACKUP%/%NOTESAPILIB%)
ctthcmd /ASn%CONNAME% /Q CRTSAVF %BACKUP%/%NOTESAPILIB%
ctthcmd /ASn%CONNAME% /Q SAVLIB LIB(%NOTESAPILIB%) DEV(*SAVF) SAVF(%BACKUP%/%NOTESAPILIB%)
ctthcmd /ASn%CONNAME% /Q DLTLIB %NOTESAPILIB%
ctthcmd /ASn%CONNAME% /Q RSTLIB SAVLIB(%NOTESAPILIB%) DEV(*SAVF) SAVF(%TEMP%/%NOTESAPI%)
:do_rest2
ctthcmd /ASn%CONNAME% /Q DLTLIB %TEMP%
ctthcmd /ASn%CONNAME% /Q CHGCURLIB %NOTESAPILIB%
mkdir ..\include
cd ..\include
ftp -s:..\as400\ftpapifl.ftp %HOST%
cd ..
cttdis