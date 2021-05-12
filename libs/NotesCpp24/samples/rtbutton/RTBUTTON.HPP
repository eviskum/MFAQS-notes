//===========================================================================
//
// Module:              RTBUTTON.HPP
//
// Description: 
//              Definitions for RTBUTTON sample application.
//===========================================================================

#ifndef RTBUTTON_HPP
#define RTBUTTON_HPP

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

void AppendCDButton(const LNString &ButtonTitle, const LNString &FormulaString, 
					LNDocument *CurDoc,  LNRichText *RT );

void AppendButton(const LNString &ButtonTitle, const LNString &FormulaString,  
				  LNDocument *CurDoc, LNButton *lnbutton );

void EditCDButtonLabel(LNString NewLabel, LNRichText *RT);

void DeleteButton(LNDocument *CurDoc, LNButton *Lnbutton);

void DeleteCDButton (LNRichText *RT);


void ProcessArguments ( int                     argc,
						char            *argv[],
						LNString        *DatabasePath,
						LNString        *ServerPath,
						LNString        *ButtonTitle );

void InitDefaultParams(void);
void GetArguments(void);
void QueryArguments(void);
void PrintArguments(void);

//
//      Class definition of IOParameter, a string class for console I/O.
//

class IOParameter 
{

int     Size;
char    *BufferPointer;

public:

	// Constructors, etc.
	IOParameter();                                                          // Default
	IOParameter( const char *Str );                         // string x = "abc"
	IOParameter( const int Number );                        // Constructs a string rep for an int.
	IOParameter( const IOParameter &Other );        // Copy constructor
	IOParameter( const IOParameter& Prefix, const IOParameter& Postfix);

	~IOParameter() { delete [] BufferPointer; }                      // Destructor

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
	friend IOParameter operator + ( char *Str, const IOParameter &Other );  // Concat a string with a IOParameter

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

#endif // RTBUTTON_HPP

