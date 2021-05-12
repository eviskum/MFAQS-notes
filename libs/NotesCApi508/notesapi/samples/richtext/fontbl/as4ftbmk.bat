: **************************************************************/
:
:       Notes C API Sample Program "make" file for:
:                      richtext/fontbl
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
set ICCAS=%ICCAS_ARGS%

: Build it, place on the AS400 machine, and finish building **/
: on the AS400 ***********************************************/
iccas /B"CRTPGM PGM(%NOTESSDK%/fontbl) BNDSRVPGM(%QNOTES%/%LIBNOTES% %QLIBASCII%/%LIBASCII%) ENTMOD(%NOTESAPILIB%/%NOTES0%) DETAIL(*BASIC)"  fontbl.c

CALL ..\..\..\as400\disconn.bat