//===========================================================================
//
// Module:              ACLLOG.HPP
//
// Description:
//              Definitions for the C++ API sample application ACLLOG.
//      
//              This include file also contains the definition of the
//              class library for the ACLLog class, ehich defines an abstract 
//              logging ACL object that can be used to store and keep track of 
//              ACL entry list information from a user-specified .NSF file.
//
//              A class library for providing convenient console I/O
//              functions, IOParameter, is also defined at the bottom of the 
//              file.
//===========================================================================

#ifndef ACLLOG_HPP
#define ACLLOG_HPP

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#ifdef _X86_
#include <conio.h>
#endif

#include <stdio.h>

// Notes C++ API headers
#include "lncppapi.h"

// Forward declarations
void ProcessArguments (
	int                     argc,
	char            *argv[],
	LNString        *DatabasePath,
	LNString        *ServerName
);

void InitDefaultParams(void);
void GetArguments(void);
void QueryArguments(void);
void PrintArguments(void);


//
//      Class definition for ACLLog. The logging/journaling database. 
//

class ACLLog
{

public:
	ACLLog();
	~ACLLog();

	// Public Methods:
	LNSTATUS OpenAclDB( LNNotesSession *Session, 
					    const LNString &Path, 
						const LNString &Server = "" );

	LNSTATUS CloseAclDB();

	LNSTATUS CreateLogEntry( const LNString &ServerName,
						const LNString &NSFName, 
						const LNString &DBTitle);

	LNSTATUS AddACLEntry( LNACLEntry &Entry);

	LNSTATUS CloseLogEntry();

	LNBOOL   IsDbOpen() const { return IsDBOpen; }

private:

	// Private data
	LNNotesSession			*LogSession;
	LNDatabase              ACLLogDb;
	LNDocument              AclEntryDoc;
	LNBOOL                  IsDBOpen;
	LNBOOL                  IsDocOpen;

};  // END class ACLLog


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

