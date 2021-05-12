//===========================================================================
//
// Module:		COPYDB.HPP
//
// Description: 
//              Definitions for COPYDB sample application.
//===========================================================================

#ifndef COPYDB_HPP
#define COPYDB_HPP

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#ifdef _X86_
#include <conio.h>
#endif

#if defined(MAC)
	// These headers are only needed for Macintosh applications.
#include <Types.h>
#include <Quickdraw.h>
#define thePort qd.thePort
#include <Dialogs.h>
#include <Menus.h>
#include <Windows.h>
#include <Fonts.h>
#include <Memory.h>
#include <stdio.h>
#endif

#include <stdio.h>

#include <lncppapi.h>

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

// Prototypes:
void ProcessArguments ( LNString        &SrcPath,
						LNString        &SrcServer,
						LNString        &DestPath,
						LNString        &DestServer,
						LNString        &Title);

void SetUpNames();
void QueryNames();
void PrintNames();

//
// Class definition of IOParameter, a generic string buffer for console I/O.
//
class IOParameter 
{

int		Size;
char	*BufferPointer;

public:

	// Constructors, etc.
	IOParameter();							// Default
	IOParameter( const char *Str );			// String x = "abc"
	IOParameter( const int number );		// Constructs a string rep for an int.
	IOParameter( const IOParameter &Other );// Copy constructor
	IOParameter( const IOParameter& Prefix, const IOParameter& Postfix);

	~IOParameter() { delete [] BufferPointer; }		// Destructor

	// Conversion methods.
	operator char *() { return BufferPointer; }
	int GetSize() const { return (Size -1); }
	void MakeString(char *Str) { strcpy(Str, BufferPointer); }
	int StringToInteger() { return atoi(BufferPointer); }

	// Subscript, etc.
	char operator [] (int index);

	// Assignment.
	IOParameter operator = ( const IOParameter &Other );
	IOParameter operator = ( const char *Str );

	// Concatenate.
	IOParameter operator + ( const IOParameter &Other );
	IOParameter operator + ( const char *Str );
	// Concat a string with a IOParameter
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

#endif // COPYDB_HPP

