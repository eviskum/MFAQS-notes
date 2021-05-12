: **************************************************************/
:
:       Notes C API Sample Program "make" file for:
:                      server/addin
:
:   Compile Platform: Win95/VisualAge For AS400
:    Target Platform: AS400;
:
: ************************************************************/

: Load the environment variables *****************************/
: change the HOST as needed **********************************/ 
CALL ..\..\..\as400\setup.bat
CALL ..\..\..\as400\conn.bat

: Set the env variable ICCAS, pretty much this compiles it. **/
set ICCAS=%ICCAS_ARGS% /C+ /Q+

: Build it, place on the AS400 machine, and finish building **/
: on the AS400 ***********************************************/
iccas /B"CRTPGM PGM(%NOTESSDK%/addin) BNDSRVPGM(%QNOTES%/%LIBNOTES%)  ENTMOD(%NOTESAPILIB%/%NOTES0%) DETAIL(*BASIC)"  addin.c
ctthcmd /ASn%CONNAME% /Q CRTPGM PGM(%NOTESSDK%/addin) BNDSRVPGM(%QNOTES%/%LIBNOTES%) MODULE(%NOTESSDK%/addin %NOTESAPILIB%/notesai0) ENTMOD(%NOTESAPILIB%/%NOTES0%) DETAIL(*BASIC)


CALL ..\..\..\as400\disconn.bat