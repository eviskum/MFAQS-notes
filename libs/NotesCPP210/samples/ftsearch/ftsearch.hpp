//===========================================================================
//
// Module:              FTSEARCH.HPP
//
// Description: 
//              Definitions for FTSEARCH sample application.
//===========================================================================

#ifndef FTSEARCH_HPP
#define FTSEARCH_HPP

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

// Forward declarations.
void InitDefaultParams(void);
void GetArguments(void);
void QueryArguments(void);
void PrintArguments(void);

void ProcessArguments ( int			argc,
						char		*argv[],
						LNString	*DatabasePath,
						LNBOOL		*isStemWords,      // Use stemming (partial-word matching)? TRUE or FALSE.
						LNBOOL		*isThesaurusWords, // Use thesaurus in search? TRUE or FALSE.
						LNBOOL		*isSearchSet,      // Whether to select docs from a particular author.
						LNINT		*MaxDocuments,     // Maximum number of documents in result collection.
						LNINT		*SortOption,       // The sorting order.
						LNINT		*ViewNumber  );    // The type of View to use in the search.

void CreateFTIndex(LNDatabase &Db);

void SetFTSearchOption( LNFTSearchOptions	*SearchOptions, 
						LNINT				MaxDocuments,
						LNINT				SortOption,
						LNBOOL				IsStemWords,
						LNBOOL				IsThesaurusWords );

void SetFTSearchSet( LNDatabase &Db, LNNoteArray *SearchSet );
void ViewFolderFTSearch( LNDatabase &Db, LNINT ViewNumber );
void PrintSearchResult( LNDocumentArray &SearchResult );
void PrintSearchResult( LNVFNavigator &SearchResult );

#define DATABASENAME    "ftsearch.nsf"
#define QUERYSTRING     "document"

//
//      Class definition of IOParameter, a string class for console I/O.
//
class IOParameter 
{
	int		size;
	char	*pBuf;

public:

	// Constructors etc...
	IOParameter();								// Default
	IOParameter( const char *str );				// String x = "abc"
	IOParameter( const int number );			// Constructs a string rep for and int.
	IOParameter( const IOParameter &Other );	// Copy constructor
	IOParameter( const IOParameter& Prefix, const IOParameter& Postfix);

	~IOParameter() { delete [] pBuf; }			// Destructor

	// Conversion methods.
	operator char *() { return pBuf; }
	int GetSize() const { return (size -1); }
	void MakeString(char *str) { strcpy(str, pBuf); }
	int StringToInteger() { return atoi(pBuf); }

	// Subscript, etc.
	char operator [] (int index);

	// Assignment.
	IOParameter operator = ( const IOParameter &Other );
	IOParameter operator = ( const char *str );

	// Concatenate.
	IOParameter operator + ( const IOParameter &Other );
	IOParameter operator + ( const char *str );
	friend IOParameter operator + ( char *str, const IOParameter &Other );  // Concat a string with a IOParameter

	IOParameter& operator << ( const IOParameter &Other );
	IOParameter& operator << ( const char *str );

	// I/O operators.
	friend ostream &operator << ( ostream &Stream, const IOParameter &Other );
	friend istream &operator >> ( istream &Stream, IOParameter &Other );

	// Relational operators.
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

#endif // FTSEARCH_HPP

