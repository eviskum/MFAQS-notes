//===========================================================================
//
// Module:		NSF_DPP.HPP
//
// Description:	
//		Definitions for NSF_DPP Sample Application.
//===========================================================================

#ifndef NSF_DPP_HPP
#define NSF_DPP_HPP

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#ifdef _X86_
#include <conio.h>
#endif

#include <stdio.h>

#ifndef NSFLOG_HPP
#include "nsflog.hpp"
#endif

// Forward Declarations:

void ProcessArguments ( int			argc,
						char		*argv[],
						LNString	*NSFPath,
						LNString	*NSFServerPath,
						LNString	*LogDBPath,
						LNString	*LogServerPath,
						LNString	*Options       );

void InitDefaultParams();
void GetArguments();
void PrintArguments();
void QueryArguments();

//
//	Class Definition of IOParameter. A String Class for console IO.
//

class IOParameter 
{

	int		size;
	char	*pBuf;

public:

	// Constructors etc...
	IOParameter();								// default
	IOParameter( const char *str );				// string x = "abc"
	IOParameter( const int number );			// constructs a string rep for and int.
	IOParameter( const IOParameter &Other );	// copy constructor
	IOParameter( const IOParameter& Prefix, const IOParameter& Postfix);

	~IOParameter() { delete [] pBuf; }			// destructor

	// Conversion methods.
	operator char *() { return pBuf; }
	int GetSize() const { return (size -1); }
	void MakeString(char *str) { strcpy(str, pBuf); }
	int StringToInteger() { return atoi(pBuf); }

	// Subscript etc...
	char operator [] (int index);

	// Assignment...
	IOParameter operator = ( const IOParameter &Other );
	IOParameter operator = ( const char *str );

	// Concatenate...
	IOParameter operator + ( const IOParameter &Other );
	IOParameter operator + ( const char *str );
	friend IOParameter operator + ( char *str, const IOParameter &Other );  // Concat a string with a IOParameter

	IOParameter& operator << ( const IOParameter &Other );
	IOParameter& operator << ( const char *str );

	// I/O operators...
	friend ostream &operator << ( ostream &Stream, const IOParameter &Other );
	friend istream &operator >> ( istream &Stream, IOParameter &Other );

	// Relational operators
	int operator == ( const IOParameter &Other ) { return !strcmp(pBuf, Other.pBuf ); }
	int operator == ( const char *str ) { return !strcmp(pBuf, str ); }
	int operator != ( const IOParameter &Other ) { return strcmp(pBuf, Other.pBuf ); }
	int operator != ( const char *str ) { return strcmp(pBuf, str ); }
	int operator < ( const IOParameter &Other ) { return strcmp(pBuf, Other.pBuf ) <0; }
	int operator < ( const char *str ) { return strcmp(pBuf, str ) <0; }
	int operator <= ( const IOParameter &Other ) { return strcmp(pBuf, Other.pBuf ) <=0; }
	int operator <= ( const char *str ) { return strcmp(pBuf, str ) <=0; }
	int operator > ( const IOParameter &Other ) { return strcmp(pBuf, Other.pBuf ) >0; }
	int operator > ( const char *str ) { return strcmp(pBuf, str ) >0; }
	int operator >= ( const IOParameter &Other ) { return strcmp(pBuf, Other.pBuf ) >=0; }
	int operator >= ( const char *str ) { return strcmp(pBuf, str ) >=0; }

}; // END class IOParameter

#endif // NSF_DPP_HPP


