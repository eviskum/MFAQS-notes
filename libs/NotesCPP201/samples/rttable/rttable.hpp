//===========================================================================
//
// Module:		RTTABLE.HPP
//
// Description:	
//              Definitions for RTTABLE sample application.
//===========================================================================
//
// Copyright (c) 1997-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef RTTABLE_HPP
#define RTTABLE_HPP

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#ifdef _X86_
#include <conio.h>
#endif

#include <stdio.h>

// Notes C++ API headers.
#include "lncppapi.h"
#include "editdflt.h"

// These headers are only needed on the Macintosh.
#if defined(MAC)
#include <Types.h>
#include <Quickdraw.h>
#define thePort qd.thePort
#include <Dialogs.h>
#include <Menus.h>
#include <Windows.h>
#include <Fonts.h>
#include <Memory.h>
#include <stdio.h>
#endif  // defined(MAC)

// Forward declarations.
void ProcessArguments ( int			argc,
						char		*argv[],
						LNString 	*DatabasePath,
						LNINT		*Rows, 
						LNINT		*Cols   );

void InitDefaultParams();
void GetArguments(void);
void QueryArguments(void);
void PrintArguments(void);

void AppendRTTable( LNDocument *CurDoc, LNINT Rows, LNINT Cols );

//
//      Class definition of IOParameter, a string class for console I/O.
//

class IOParameter 
{

	int		Size;
	char	*BufferPointer;

	public:

		// Constructors, etc.
		IOParameter();								// Default.
		IOParameter( const char *Str );				// String x = "abc".
		IOParameter( const int Number );			// Constructs a string rep for an int.
		IOParameter( const IOParameter &Other );	// Copy constructor.
		IOParameter( const IOParameter& Prefix, const IOParameter& Postfix);

		~IOParameter() { delete [] BufferPointer; }	// Destructor.

		// Conversion methods.
		operator char *() { return BufferPointer; }
		int GetSize() const { return (Size -1); }
		void MakeString(char *Str) { strcpy(Str, BufferPointer); }
		int StringToInteger() { return atoi(BufferPointer); }

		// Subscript, etc.
		char operator [] (int Index);

		// Assignment.
		IOParameter operator = ( const IOParameter &Other );
		IOParameter operator = ( const char *Str );
	
		// Concatenate.
		IOParameter operator + ( const IOParameter &Other );
		IOParameter operator + ( const char *Str );
	
		// Concat a string with an IOParameter.
		friend IOParameter operator + ( char *Str, const IOParameter &Other );  

		IOParameter& operator << ( const IOParameter &Other );
		IOParameter& operator << ( const char *Str );

		// I/O operators.
		friend ostream &operator << ( ostream &Stream, const IOParameter &Other );
		friend istream &operator >> ( istream &Stream, IOParameter &Other );

		// Relational operators.
		int operator == ( const IOParameter &Other ) { return !strcmp(BufferPointer, Other.BufferPointer ); }
		int operator == ( const char *Str ) { return !strcmp(BufferPointer, Str ); }
		int operator != ( const IOParameter &Other ) { return strcmp(BufferPointer, Other.BufferPointer ); }
		int operator != ( const char *Str ) { return strcmp(BufferPointer, Str ); }
		int operator < ( const IOParameter &Other ) { return strcmp(BufferPointer, Other.BufferPointer ) <0; }
		int operator < ( const char *Str ) { return strcmp(BufferPointer, Str ) <0; }
		int operator <= ( const IOParameter &Other ) { return strcmp(BufferPointer, Other.BufferPointer ) <=0; }
		int operator <= ( const char *Str ) { return strcmp(BufferPointer, Str ) <=0; }
		int operator > ( const IOParameter &Other ) { return strcmp(BufferPointer, Other.BufferPointer ) >0; }
		int operator > ( const char *Str ) { return strcmp(BufferPointer, Str ) >0; }
		int operator >= ( const IOParameter &Other ) { return strcmp(BufferPointer, Other.BufferPointer ) >=0; }
		int operator >= ( const char *Str ) { return strcmp(BufferPointer, Str ) >=0; }

}; // END class IOParameter

#endif // RTTABLE_HPP

