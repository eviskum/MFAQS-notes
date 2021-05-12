//===========================================================================
//
//      Module: MAIL_DOC.CPP
//
//      Syntax:	mail_doc [<dbname> <server> <"search string"> <user name>]
//				Note: all arguments are optional, you will be prompted and
//					  provided with working defaults (except for user name).
//
//      Description:
//              Sample C++ API program that searches the documents in a Notes
//              database for a specified string and, once found, sends the 
//				document as a mail message to a specified user.
//		Note:
//				This program is coded to search for must the specified string
//				which must be contained in a rich text 'Body' item of a 
//				document. 
//
//===========================================================================
//
// Copyright (c) 1997,1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef MAIL_DOC_HPP
#include "mail_doc.hpp"
#endif

// Input parameter strings.
IOParameter             CommandBuf;
IOParameter             PromptString1;
IOParameter             ParamString1;
IOParameter             PromptString2;
IOParameter             ParamString2;
IOParameter             PromptString3;
IOParameter             ParamString3;
IOParameter             PromptString4;
IOParameter             ParamString4;

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main( int argc, char *argv[] )
{
	int				ProgramStatus = 0;
	LNNotesSession	Session;

#if defined(MAC)
// Initialize things for the Macintosh.
	InitGraf(&thePort); 
	InitFonts();
	InitWindows(); 
	InitDialogs(0);
	SetApplLimit(GetApplLimit()-8192); 
	MaxApplZone();
	MoreMasters(); 
	MoreMasters(); 
	MoreMasters();
#endif

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	LNSetThrowAllErrors (TRUE);

	try
	{
		LNDatabase		DocDB;
		LNDocumentArray	DocArray;
		LNString		DatabasePath;
		LNString		ServerPath;
		LNString		SearchStr;
		LNString		UserName;
		LNString		SearchFormula;
		LNINT			Index;
		LNINT			Count;

		// Initialize the API.
		Session.Init (argc, argv);

		// Parse the argument list.              
		ProcessArguments (argc, argv, &DatabasePath, &ServerPath, &SearchStr, &UserName);

		// Get the specified Notes database.
		Session.GetDatabase(DatabasePath, &DocDB, ServerPath);

		// Open the database.
		DocDB.Open();

		cout << "Scanning database:  " << DatabasePath << endl;

		// Get an array of all the docs in the database.
		DocDB.GetDocuments( &DocArray );

		LNBOOL  isDocFound = FALSE;
		Count = DocArray.GetCount();
		for (Index=0; Index<Count; Index++)
		{
			LNDocument	CurDoc;

			// Get the next document in the array.
			CurDoc = DocArray[Index];
			// Open it.
			CurDoc.Open( LNNOTEOPENFLAGS_DEFAULT );

			if ( CurDoc.HasItem("Body") )
			{
				// This Document has a Body field, so search for the string in it.
				if ( SearchDocument( CurDoc, "Body", SearchStr ) )
				{
					// String was found; e-mail the current document to username.
					CurDoc.SendTo( UserName, TRUE );

					cout << "Sent Document to:  " << UserName << endl;
					isDocFound = TRUE;
				}
			}

			CurDoc.Close();
		}

		if ( !isDocFound )
			cout << "Search String was not found" << endl;

		// Close the database.
		DocDB.Close();

		ProgramStatus = 0;

	} // END try block.

	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(lnerror, ErrorBuf);
		cout << "\nError:  " << ErrorBuf << endl;
		ProgramStatus = 2;
	}

	catch (const char *pErrorMessage)
	{
		cout << "\nError: " << pErrorMessage << endl;
		ProgramStatus = 1;
	}

	cout << endl;
	cout << "Hit Return To Exit: ";
	cin >> CommandBuf;

	// Terminate the API
	Session.Term();

	return (ProgramStatus);

} // END MAIN

//---------------------------------------------------------------------------
//
// Name:
//              SearchDocument
//
// Description:
//              Searches stylized text elements in a document's rich text fields
//              for the presence of a search string and returns TRUE if found.
//---------------------------------------------------------------------------
LNBOOL SearchDocument( const LNDocument &Doc, 
					   const LNString &FieldName, 
					   const LNString &SearchStr  )
{
	LNRichText	RT;
	LNRTCursor	Cursor;

	// Get the document's Body field as a rich text item.
	Doc.GetItem( FieldName, &RT );

	// Get the position of the very beginning of the RT field.
	RT.GetCursor( &Cursor );

	// Find the first stylized text in the rich text.
	if ( Cursor.GotoFirst(SearchStr) == LNWARN_NOT_FOUND )
		return FALSE;

	return TRUE;

} // END SearchDocument()

//---------------------------------------------------------------------------
//
// Name:
//              ProcessArguments
//
// Description:
//      Scan the input command line and sort out the input strings.
//      If no arguments were supplied, prompt for them.
//
//      Throws exceptions:
//              char *          Argument error description
//
//---------------------------------------------------------------------------
void ProcessArguments ( int			argc,
						char		*argv[],
						LNString	*DatabasePath,
						LNString	*ServerPath,
						LNString	*SearchStr,
						LNString	*UserName )
{
	LNBOOL Prompt = FALSE;

// Macintosh cannot process (argc, argv).
#if defined(MAC)
	Prompt = TRUE;
#else
	if (argc != 5)
		Prompt = TRUE;  
#endif

	// Set up the default parameters first.
	InitDefaultParams();

	*DatabasePath = ParamString1;
	*ServerPath = ParamString2;
	*SearchStr = ParamString3;
	*UserName = ParamString4;       
	
	// Check the command line.
	if (Prompt)
	{
		// Get user input data.
		GetArguments();
		*DatabasePath = ParamString1;
		*ServerPath = ParamString2;
		*SearchStr = ParamString3;
		*UserName = ParamString4;
	}
	else
	{
		// Get info from command line.
		*DatabasePath = argv[1];
		*ServerPath = argv[2];
		*SearchStr = argv[3];
		*UserName = argv[4];
	}

} // END ProcessArguments()

//---------------------------------------------------------------------------
//
// Name:
//              InitDefaultParams
//
// Description:
//              Set up all the default parameter strings and numbers for user
//              input.  Called by ProcessArguments() if no user input params
//              were provided.
//
//              NOTE:
//
//              You only need to edit this function and ProcessArguments() 
//              when creating a new sample.  The rest of the user interface 
//              functions below are called by ProcessArguments() and are 
//              generic, which means that they can stay the same unless
//              you modify the number of parameters to use. If you do modify
//              the number of parameters used, you will need to modify the 
//              switch statements.
//---------------------------------------------------------------------------
void InitDefaultParams()
{
	// Initialize default parameter strings.

	PromptString1   = "NSF file path name : [";
	ParamString1    = "dumpme.nsf";
	PromptString2   = "Server path name   : [";
	ParamString2    = "";
	PromptString3   = "Search string      : [";
	ParamString3    = "I think";
	PromptString4   = "User name          : [";
	ParamString4    = "UserName@SomeDomain";

} // END InitDefaultParams()

//---------------------------------------------------------------------------
//
// Name:
//              GetArguments
//
// Description:
//              Allows the user to change any or all of the input parameter 
//              strings.  The inputs can also be left as they are if desired.
//---------------------------------------------------------------------------
void GetArguments()
{
	BOOL IsCorrectData = FALSE;

	QueryArguments();

	while( !IsCorrectData )
	{
		PrintArguments();

		cout << "Are these current data settings correct? [Y] ";
		cin >> CommandBuf;

		switch( CommandBuf[0] )
		{
			case 'Y':
			case 'y':

			IsCorrectData = TRUE;   // All done, get out now!
			break;

			default:

			// Prompt again for anything other than a "Y" or carriage return.
			if( (CommandBuf) != (const char *)"" )
				QueryArguments();
			else
				IsCorrectData = TRUE;  // All done, get out now!

		} // END switch

	} // END while

} // END GetArguments()

//---------------------------------------------------------------------------
//
// Name:
//              PrintArguments
//
// Description:
//              Prints out all of the current input parameters to use.
//---------------------------------------------------------------------------
void PrintArguments()
{
	cout << endl;
	cout << "The current default data settings are: " << endl;
	cout << endl;
	cout << "     " << PromptString1 << ParamString1 << "]" << endl;
	cout << "     " << PromptString2 << ParamString2 << "]" << endl;
	cout << "     " << PromptString3 << ParamString3 << "]" << endl;
	cout << "     " << PromptString4 << ParamString4 << "]" << endl;
	cout << endl;

} // END PrintArguments()

//---------------------------------------------------------------------------
//
// Name:
//              QueryArguments
//
// Description:
//              Queries the user to change any of the input parameters.
//              A carriage return on any of the prompts leaves it alone.
//---------------------------------------------------------------------------
void QueryArguments()
{
	cout << endl;

	cout << "Enter " << PromptString1 << ParamString1 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString1 = CommandBuf;

	cout << "Enter " << PromptString2 << ParamString2 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString2 = CommandBuf;

	cout << "Enter " << PromptString3 << ParamString3 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString3 = CommandBuf;

	cout << "Enter " << PromptString4 << ParamString4 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString4 = CommandBuf;

} // END QueryArguments()



//===========================================================================
//
// IOPARAMETER Class Implementation
//
// Description: 
//              Implementation for a simple generic string buffer class
//              to hold user input and output prompts.
//===========================================================================

//===========================================================================
// Constructors
//===========================================================================
IOParameter::IOParameter() // Default constructor.
{
	size =1; // Null terminator.
	
	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	pBuf[0] = '\0';
}

//===========================================================================
IOParameter::IOParameter( const char *str ) // Init with const string.
{
	size = strlen(str) + 1;		// size of string + null term.

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, str);
}


//===========================================================================
// Constructs a decimal radix string representation of an integer.
IOParameter::IOParameter( const int number )
{
	char buf[16];				// Temporary buffer for characters.

	sprintf(buf, "%d", number);

	size = strlen(buf) + 1;		// size of string + null term.

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, buf);
}


//===========================================================================
IOParameter::IOParameter( const IOParameter &Other ) // Copy constructor.
{
	size = Other.size;

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, Other.pBuf);
}

//===========================================================================
// Constructor using 2 IOParameter objects as input.
IOParameter::IOParameter( const IOParameter& Prefix, const IOParameter& Postfix)
{
	size = Prefix.size + Postfix.size - 1;

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, Prefix.pBuf);
	strcat(pBuf, Postfix.pBuf);
}

//===========================================================================
// Subscript, etc.
//===========================================================================
char IOParameter::operator [] (int Index)
{
	char c;

	if (Index > size)
		c = '\0';
	else
		c = pBuf[Index];

	return c;
}

//===========================================================================
// Assignment.
//===========================================================================
IOParameter IOParameter::operator = ( const IOParameter &Other )
{
	if(pBuf)
		delete [] pBuf;

	size = Other.size;
	
	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, Other.pBuf);

	return *this;
}

//===========================================================================
IOParameter IOParameter::operator = ( const char *str )
{
	size = strlen(str) +1;

	if (pBuf)
		delete [] pBuf;
	
	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, str);
	return *this;
}

//===========================================================================
// I/O operators.
//===========================================================================
ostream &operator << ( ostream &Stream, const IOParameter &Other )
{
	Stream << Other.pBuf;
	return Stream;
}

//===========================================================================
istream &operator >> ( istream &Stream, IOParameter &Other )
{
	const int 	buflen = 255;		// Arbitrary size, change if needed.
	char		t[buflen];                                                                                         // temp string... 
	int 		len;

	for (len=0; len<buflen; len++)
	{
		Stream.get(t[len]);
		if (t[len] == '\n')		// Newline character
			break;
		if (t[len] == '\b')		// Backspace character
		{
			if(len)
			{
				len--;
			}
		}
	}

	t[len] = '\0';
	len++;

	if(Other.pBuf)
		delete [] Other.pBuf;

	if (! (Other.pBuf = new char[len]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	Other.size = len;

	strcpy(Other.pBuf, t);
	return Stream;

} // END istream &operator >>

//===========================================================================
// Concatenate.
//===========================================================================
IOParameter IOParameter::operator + ( const IOParameter &Other ) // Cat 2 IOParameter objects.
{
	return IOParameter( *this, Other );
}

//===========================================================================
IOParameter IOParameter::operator + ( const char *str ) // Cat IOParameter and string.
{
	return IOParameter( *this, IOParameter(str) );
}

//===========================================================================
IOParameter operator + ( char *str, const IOParameter &Other ) // Cat string with IOParameter.
{
	return IOParameter( IOParameter(str), Other );
}

//===========================================================================
IOParameter& IOParameter::operator << ( const IOParameter &Other ) // Cat 2 IOParameter objects.
{
	IOParameter TempString(*this);

	size = TempString.size + Other.size - 1;

	if (pBuf)
		delete [] pBuf;

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, TempString.pBuf);
	strcat(pBuf, Other.pBuf);

	return *this;
}

//===========================================================================
IOParameter& IOParameter::operator << ( const char *str ) // Cat IOParameter and string.
{
	IOParameter TempString(*this);
	IOParameter Other(str);

	size = TempString.size + Other.size - 1;

	if (pBuf)
		delete [] pBuf;

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, TempString.pBuf);
	strcat(pBuf, Other.pBuf);

	return *this;   
}


