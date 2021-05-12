#ifndef _EXTMNGRH
#define _EXTMNGRH

#define USE_NOTESINIT_NOTESTERM
#undef DEBUG
/*
	extmngr.H
*/

/*
	REQUIRED WHEN COMPILING SAMPLE FOR WINDOWS
*/
#if defined(DOSW16) || defined(NT)
#include <windows.h>
#include <string.h>
#elif  defined(MAC)
#include <files.h>
#include <string.h>
#elif defined(OS2_2x)
#include <os2.h>
#include <string.h>
#include <malloc.h>
#endif

#include <stdio.h>


/*
	LOTUS C API FOR DOMINO AND NOTES HEADER FILES
*/

#include <global.h>
#include <event.h>
#include <kfm.h>
#include <nsfnote.h>
#include <nsferr.h>
#include <nsfdb.h>
#include <nsfdata.h>
#include <nsfnote.h>
#include <osmisc.h>
#include <misc.h>
#include <ostime.h>
#include <extmgr.h>
#include <OSfile.h>

/*===== GLOBAL DEFININITIONS =========================*/

#define MAX_NAME   128
#define DB_NAME    "ANIMALS.DB"
#define ERR_FILE_OPEN   PKG_OS + 230  /* can't open file */
#define ERR_MEMORY      PKG_OS + 231  /* can't allocate memory */

/* 
	Static table for holding information pertaining to
	the functions that I am placing hooks into.
*/
typedef struct {
	EID 	m_Identifier;			/* identifier for which call to trap on */
	WORD	m_Notification;			/* EM_REG_BEFORE, EM_REG_AFTER */
	HEMREGISTRATION	m_RegistrationHandle; /* reg handle from EMRegister */
	BOOL	m_WasRegistered; 		/* Indicates if reg was successfully. */
	char    *m_Name;      		    /* Name of Identifier  */
} TExtensionInfo, *pExtensionInfo;


/* record definition in the animals database */
typedef struct _dbrecord_tag
{
	char  CommonName[MAX_NAME];
	char  LatinName[MAX_NAME];
	char  Range[MAX_NAME];
    char  Status[MAX_NAME];
	struct _dbrecord_tag *Next;
} DBRECORD;


#if defined(DOSW16)

/* Log file containing output from sample */
#define LOG_FILE_NAME   "\\OUTPUT.LOG"

#define DLL_EXPORT	_export
#define UNREFERENCED_PARAMETER(x) {x=x;}
#define WRITE_PERMISSION			"w+"
#define APPEND_PERMISSION			"a+"
#define READ_PERMISSION		        "r"

#elif defined(NT)


/* Log file containing output from sample */

#define LOG_FILE_NAME "\\OUTPUT.LOG"

/* #define DLL_EXPORT	__declspec( dllexport ) */
#define WRITE_PERMISSION			"w+"
#define APPEND_PERMISSION			"a+"
#define READ_PERMISSION		        "r"
#define DLL_EXPORT

#elif defined(OS2_2x)

/* Log file containing output from sample */
#define LOG_FILE_NAME   "\\OUTPUT.LOG"
#define WRITE_PERMISSION			"w+"
#define APPEND_PERMISSION			"a+"
#define READ_PERMISSION		        "r"
#define DLL_EXPORT
#define UNREFERENCED_PARAMETER(x) {x=x;}

#elif defined(MAC)

/* Log file containing output from sample */
#define LOG_FILE_NAME   "OUTPUT.LOG"

#define WRITE_PERMISSION			fsWrPerm
#define APPEND_PERMISSION			fsWrPerm
#define READ_PERMISSION		        fsRdPerm
#define DLL_EXPORT	
#define UNREFERENCED_PARAMETER(x) {x=x;}
#endif
                           
/*---------------------------------------------------------
	PLATFORM SPECIFIC MACROS FOR FILE AND MEMORY FUNCTIONS
-----------------------------------------------------------*/

#if defined(MAC)
typedef IOParam *	FILEPointer;

/* Memory Allocation */
#define __AllocateMemory(__sz)			NewPtrClear(__sz)
#define __FreeMemory(__ptr)				DisposePtr((Ptr)__ptr)
#define __sprintf						SLMsprintf

/* File Managment */
#define EOL                             13   /* line delimiter is CR (ASCII 13)   */
#define __FILE 							short 
#define __CloseFile( _file )			FSClose(*_file);*_file=0;_file=0L
#define __FileError(_file)				gFileError
__FILE * __OpenFile ( char * fileName, int permission );
static int __WriteLine( char *lineBuf, __FILE *  file );
int __ReadLine( char *lineBuf, long maxLen, __FILE * pbp);
#define __FileSeek( _file, _offset, _whence ) SetFPos(*_file, _whence, _offset)
#else
/* Memory Allocation */
#define __AllocateMemory(__sz)			malloc( __sz )
#define __FreeMemory(__ptr)				free( __ptr )

#define __sprintf						sprintf


/* File Managment */
#define __FILE 							        FILE
#define __OpenFile( _fn, _perm )		        fopen(_fn, _perm )
#define __CloseFile( _file )			        fclose( _file )
#define __WriteLine( _buf, _file )		        fwrite( _buf, strlen(_buf), 1, _file )
#define __FileError(_file)				        ferror(_file)
#define __ReadLine( _buf, _len, _f )			fgets( _buf, _len, _f )
#define __FileSeek( _file, _offset, _whence )	fseek( _file, _offset, _whence )


#endif


#if defined(NT)
#define DLL_IMPORT_PREFIX  __declspec (dllimport)
#define DLL_EXPORT_PREFIX  __declspec (dllexport)
#define DLL_IMPORT_INFIX   
#define DLL_EXPORT_INFIX
#elif defined(DOSW16)
#define DLL_IMPORT_PREFIX
#define DLL_EXPORT_PREFIX
#define DLL_IMPORT_INFIX
#define DLL_EXPORT_INFIX   __export
#else
#define DLL_IMPORT_PREFIX
#define DLL_EXPORT_PREFIX
#define DLL_IMPORT_INFIX
#define DLL_EXPORT_INFIX
#endif

/*---------------------------------------------------------
	Function Declarations for Creating the Database
-----------------------------------------------------------*/

STATUS LNPUBLIC ReadDataBase(DBRECORD **);
STATUS LNPUBLIC CreateDBForm(DBRECORD *pDBHead);
STATUS LNPUBLIC CreateDBNotes(DBRECORD *pDBRec);
STATUS LNPUBLIC CreateDBView(void);

/*---------------------------------------------------------
	Function Declarations for CD manipulation functions
-----------------------------------------------------------*/

BOOL LNPUBLIC PutPara (char far * far *ppBuf,
                         WORD wLength);
                               
BOOL LNPUBLIC PutPabDef(char far * far *ppBuf,
                         WORD wPabDefNumber,
                         WORD wLength);
                                
BOOL LNPUBLIC PutPabRef(char far * far *ppBuf,
                          WORD wPabDefNumber,
                          WORD wLength);
                                
BOOL LNPUBLIC PutText(char far * far *ppBuf,
                        char far * pText,
                        WORD wLength);

#endif

