//===========================================================================
//
// Module:	LNGLOSYM.H
//
// Description:
//
//		C++ API global typedefs and constant symbols (included by LNGLOBAL.H).
//
//===========================================================================
//
// Copyright (c) 1996-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNGLOSYM_H
#define LNGLOSYM_H

//-----	Check for a valid platform symbol, and define any missing symbols
//		required by the C API headers.
//
//		The C++ API platform symbols are:
//
//		W32:		Windows NT or Windows 95 (Intel)
//		W16:		Windows 3.x
//		ALPHA:		Windows NT (DEC Alpha)
//		OS2:		OS/2 Warp
//		AIX:		IBM AIX
//		SOLSPARC:	Solaris Sparc
//		SOLX86:		Solaris X86
//		HPUX:		HP-UX
//		MAC:		Macintosh PPC
//		OS390:		IBM OS/390
//		OS400:		IBM OS/400 on AS/400

#if defined W32 || defined ALPHA
	#if !defined _X86_ && !defined _ALPHA_ && !defined ALPHA
		#define _X86_		// assume Intel if no processor type specified
	#elif defined ALPHA && !defined _ALPHA_
		#define _ALPHA_
	#endif
	#ifndef W32
		#define W32
	#endif
	#ifndef NT
		#define NT
	#endif
#elif defined W16 || defined DOSW16
	#ifndef DOSW16
		#define DOSW16
	#endif
#elif defined OS2
	#ifndef OS2_2x
		#define OS2_2x
	#endif
#elif defined AIX || defined SOLSPARC || defined SOLX86 || defined HPUX || \
	defined OS390 || defined OS400
	#ifndef UNIX
		#define UNIX
	#endif
	#if (defined SOLSPARC || defined SOLX86) && !defined SOLARIS
		#define SOLARIS	
	#endif
#endif

#if !defined NT && !defined DOSW16 && !defined OS2_2x && !defined UNIX && \
	!defined MAC
	#error ERROR: No platform specified.
#endif


//-----	Define IOSTREAM_INIT_NOT_NEEDED for HPUX. This must be defined before
//		<iostream.h> is included.

#if defined HPUX && !defined _IOSTREAM_INIT_NOT_NEEDED
	#define _IOSTREAM_INIT_NOT_NEEDED
#endif

//-----	On OS/390, make sure the application is not being compiled using IEEE
//		floating point. This is an option of the newer OS/390 compiler that
//		isn't supported by the compiler used to build the C++ API library.

#if defined OS390 && defined __BFP__
	#error ERROR: IEEE floating point is not supported by this release of the C++ API.
#endif

//===========================================================================
//                       EXTERNAL HEADER FILES
//===========================================================================

//-----	Include Windows API header file (WINDOWS.H) if needed to support
//		exception handling on Windows 3.x. This file must be included before
//		GLOBAL.H in order to avoid symbol redefinition warnings.

#ifdef DOSW16
	#include <windows.h>
#endif

//-----	Other system header files.

#include <stddef.h>			// needed to define size_t for operator new
#include <string.h>			// needed for strlen etc.
#ifdef AIX
	#include <strings.h>	// AIX needs both STRING.H and STRINGS.H
#endif

//-----	C API header files.

#ifndef GLOBAL_DEFS
	#include <global.h>		// required for all C API programs
#endif

#ifndef NAME_DEFS
	#include <names.h>		// defines MAXPATH, needed below
#endif

//-----	Make sure the correct version of GLOBAL.H was included above.

#if (defined LNCPPAPI_HEADER_VERSION && LNCPPAPI_HEADER_VERSION != 451) || \
	(!defined LNCPPAPI_HEADER_VERSION && !defined LNDISABLE_HEADER_CHECK)
	#error ERROR: Incorrect version of GLOBAL.H. Check your INCLUDE path.
#endif

//===========================================================================
//                       PLATFORM-DEPENDENT SYMBOLS
//===========================================================================

//-----	Generate an error if not compiling on a supported platform. Currently,
//		the supported platforms are:
//
//		Borland C++ 4.5 on Windows 3.x
//		Microsoft Visual C++ on Windows NT and Windows 95
//		IBM VisualAge C++ on Windows NT and Windows 95
//		IBM VisualAge C++ on OS/2 Warp
//		Solaris Sparc and X86
//		AIX
//		HP-UX
//		Metrowerks on Mac PPC
//		IBM OS/390
//		IBM AS/400

#if defined DOSW16 && !defined _MSC_VER
	#define BCC
#endif

#if !(defined DOSW16 && defined BCC) && \
	!(defined NT && (defined MSC || defined IBM_C || defined __BORLANDC__)) && \
	!(defined OS2_2x && defined IBM_C) && \
	!defined SOLARIS && !defined AIX && !defined HPUX && \
	!(defined MAC && defined MWERKS_C) && !defined OS390 && !defined OS400
	#error ERROR: Unsupported platform.
#endif

//-----	Define LNGLOBALS_SUPPORTED if the platform allows each instance of
//		a shared library to have its own copy of global data, and define the
//		global data access macro accordingly. All globals are maintained in
//		a single structure to make it possible to support globals on all
//		platforms.

#if defined DOSW16 || defined NT || defined OS2_2x || defined SOLARIS || \
	defined MAC || defined AIX || defined HPUX || defined OS390 || defined OS400
	#define LNGLOBALS_SUPPORTED
#else
	#error ERROR: Unsupported platform for global data.
#endif

//-----	Define the DLL import/export macros for each platform that
//		supports dynamically linked libraries.

#if defined NODLL || !defined NOTSDK
	#define LNIMPEXPCL
	#define LNIMPEXPFN(rt) rt
#else
	#if defined W32 && !defined UNIX	// UNIX also defines W32
		#ifdef __BORLANDC__
			#define LNIMPEXPCL _export
			#define LNIMPEXPFN(rt) rt _export
		#else
			#define LNIMPEXPCL __declspec(dllexport)
			#define LNIMPEXPFN(rt) __declspec(dllexport) rt
		#endif
	#elif defined OS2
		#define LNIMPEXPCL _Export
		#define LNIMPEXPFN(rt) rt _Export
	#else
		#define LNIMPEXPCL
		#define LNIMPEXPFN(rt) rt
	#endif
#endif

//-----	For Win16, redefine LNCALLBACK (defined as FAR PASCAL in GLOBAL.H) to
//		add the __loadds keyword, which forces callback functions to reload the
//		DS register.

#ifdef DOSW16
	#undef LNCALLBACK
	#define LNCALLBACK FAR PASCAL __loadds
#endif

//-----	Define LNOLE_SUPPORTED if the platform includes support for OLE.

// #if defined DOSW16 || defined NT || defined MAC
#if defined NT
	#define LNOLE_SUPPORTED
#endif

//-----	On OS/390, define the symbol LNNO_TEXT_TRANSLATION if the code is being
//		compiled in ASCII, to suppress translation between EBCDIC and LMBCS.
//		Assume ASCII if either __STRING_CODE_SET__ or LNCPPAPI_ASCII is defined.
//		For ASCII, the value of __STRING_CODE_SET__ should be "ISO8859-1", but
//		no other values are currently defined.

#if defined OS390 || defined OS400
	#define EBCDIC_PLATFORM
	#if defined __STRING_CODE_SET__ || defined LNCPPAPI_ASCII
		#define LNNO_TEXT_TRANSLATION
		#ifndef LNCPPAPI_ASCII
			#define LNCPPAPI_ASCII
		#endif
	#else
		#define EBCDIC_TRANSLATION_REQUIRED
	#endif
#endif

//===========================================================================
//                       CONSTANTS AND TYPEDEFS
//===========================================================================

//-----	Fundamental numeric types.

typedef DWORD LNINT;			// unsigned 32-bit integer
typedef LONG LNSINT;			// signed 32-bit integer
typedef int LNBOOL;				// boolean, platform-dependent size
typedef double LNNUMBER;		// platform-dependent floating point number

//-----	C++ API error/status code, similar to the C API STATUS code. LNSTATUS
//		is a 32-bit value. where the low word contains the status code and the
//		high word contains flags; if the status code is zero, the high word is
//		zero also. If the status code is non-zero, the most significant 4 bits
//		of the high word are one following:
//
//			MSBs	                     Meaning
//			----	---------------------------------------------------------
//			0000	low word of LNSTATUS contains a Notes C API STATUS code
//			1100	low word of LNSTATUS contains a C++ API error code
//			1101	low word of LNSTATUS contains a C++ API warning code
//
//		Note that the other bits in the high word are reserved.

typedef DWORD LNSTATUS;

const LNSTATUS LNNOERROR = 0;
const WORD LNSTATUS_CSTATUS = 0;
const WORD LNSTATUS_ERROR = 0xC000;
const WORD LNSTATUS_WARNING = 0xD000;
const WORD LNSTATUS_FLAGS = 0xF000;


//-----	API version number and string. The build number (LNAPIBUILD) is defined
//		as a string constant in LNBUILD.H.

typedef LNINT LNVERSION;

const LNVERSION LNAPIVERSION = 201;

#define LNAPIVERSIONSTRING "Lotus C++ API Release 2.01 for Domino and Notes 4.5"

#include "lnbuild.h"


//-----	LNCHAR is used to identify character data that has already been
//		translated into LMBCS, and is meant to be used as a pointer type (i.e.,
//		LNCHAR *). LNCHAR is defined as int to distinguish LNCHAR * from char *
//		and LNString *; int is used rather than void to make sure the
//		compiler will never implicitly convert LNCHAR * to char *.

typedef int LNCHAR;


//----- LNUNITS is used to identify the units of user input and output values.
//		Generally, Notes data is stored in TWIPS.

enum LNUNITS
{
	LNUNITS_INCHES,
	LNUNITS_CENTIMETERS,
	LNUNITS_TWIPS,
	LNUNITS_DEFAULT
};


//-----	LNCOLOR is the representation of a color value. LNCOLOR_xxx values map
//		the first 0-15 Notes color values. Notes allows 240 total color values.

typedef WORD LNCOLOR;

#define LNCOLOR_BLACK 			NOTES_COLOR_BLACK
#define LNCOLOR_WHITE			NOTES_COLOR_WHITE
#define LNCOLOR_RED				NOTES_COLOR_RED
#define LNCOLOR_GREEN			NOTES_COLOR_GREEN
#define LNCOLOR_BLUE			NOTES_COLOR_BLUE
#define LNCOLOR_MAGENTA			NOTES_COLOR_MAGENTA
#define LNCOLOR_YELLOW			NOTES_COLOR_YELLOW
#define LNCOLOR_CYAN			NOTES_COLOR_CYAN
#define LNCOLOR_DARK_RED		NOTES_COLOR_DKRED
#define LNCOLOR_DARK_GREEN		NOTES_COLOR_DKGREEN
#define LNCOLOR_DARK_BLUE		NOTES_COLOR_DKBLUE
#define LNCOLOR_DARK_MAGENTA	NOTES_COLOR_DKMAGENTA
#define LNCOLOR_DARK_YELLOW		NOTES_COLOR_DKYELLOW
#define LNCOLOR_DARK_CYAN		NOTES_COLOR_DKCYAN
#define LNCOLOR_GRAY			NOTES_COLOR_GRAY
#define LNCOLOR_LIGHT_GRAY		NOTES_COLOR_LTGRAY


//-----	LNERROR_MESSAGE_LENGTH is a reasonable default (not maximum) length
//		for Notes error messages, and can be used to declare an error message
//		text buffer for the LNGetErrorMessage function.

const int LNERROR_MESSAGE_LENGTH = 512;


//-----	LNMAXPATH is the same as the Notes MAXPATH value, which is 100 on 16-bit
//		Windows and 256 everywhere else. Unfotunately, a Borland C++ header file
//		redefines MAXPATH to 80, so we use LNMAXPATH instead.

#ifdef BCC
	const int LNMAXPATH = 100;
#else
	#if MAXPATH != 256
		#error Error: Notes MAXPATH has been redefined.
	#endif
	const int LNMAXPATH = MAXPATH;
#endif

#endif	// LNGLOSYM_H

