//===========================================================================
//	Module:	    COPYDB
//
//	Description:
//		This program copies the the source database to a new output
//		database.  The user is prompted for the source database and 
//		server pathnames, the destination database and server pathnames,
//		and whether to make a replicating or non-replicating copy.
//
//		Syntax:
//			COPYDB
//===========================================================================

#ifndef COPYDB_HPP
#include "copydb.hpp"
#endif

IOParameter			CommandBuf;
IOParameter			InDbFile;
IOParameter			InDbServer;
IOParameter			OutDbFile;
IOParameter			OutDbServer;
IOParameter			DBTitle;
BOOL				IsReplicaCopy = FALSE;

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
LNNotesSession	Session;

	// Throw all errors encountered during command execution.

	LNSetThrowAllErrors(TRUE);

	try
	{
	LNString					SrcPath;
	LNString					SrcServer;
	LNString					DestPath;
	LNString					DestServer;
	LNString					Title;
	LNDatabase					SrcDb;
	LNDatabase					DestDb;
	LNCreateDatabaseOptions		DBOptions;

		// Initialize a Notes session.

		Session.Init(argc, argv);
	
		// Parse the argument list.

		ProcessArguments( SrcPath, SrcServer, DestPath, DestServer, Title);

		// Set up the database copy options.

		DBOptions.SetCopyACL( FALSE );			// Don't copy the ACL.
		DBOptions.SetCreateFTIndex( TRUE );		// Create a full text index.
		DBOptions.SetCopyDesignOnly( FALSE );   // Copy design and documents.

		// Copy the source database to the destination database.

		if (IsReplicaCopy)
		{
			// Make a replica copy of the source database. 
			// This assumes you have an *OPEN* session object first!

			Session.CreateDatabaseReplica( SrcPath,   SrcServer, 
										   DestPath,  DestServer, 
										   DBOptions, &DestDb);
		}
		else
		{
			// Make a non-replica copy of the source database. 
			// This assumes you have an *OPEN* session object first!

			Session.CreateDatabaseCopy( SrcPath,   SrcServer, 
										DestPath,  DestServer, 
										DBOptions, &DestDb);
		}

		// Set the title of the new database.

		DestDb.SetTitle( Title );

		cout << endl << "Source Database: [" << InDbFile << "] was successfully copied."
		     << endl << "New Database Copy:     [" << OutDbFile << "]"
			 << endl << "New Database Title:    [" << DBTitle << "]" << endl;

		if(IsReplicaCopy)
			cout << "The New Database is a replica copy." << endl;
		else
			cout << "The New Database is a non-replica copy." << endl;

	} // END TRY block.

	// If an error occurred on any of the above commands, get the text
	//  of the error message and display it.

	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(lnerror, ErrorBuf);
		cout << "\nError:  " << ErrorBuf << endl;
	}

	catch (const char *pErrorMessage)
	{
		cout << "\nError: " << pErrorMessage << endl;
	}

	cout << endl;
	cout << "Hit Return To Exit: ";
	cin >> CommandBuf;

	// Terminate the API.
	Session.Term();

	return (0);

} // END main()

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
//---------------------------------------------------------------------------
void ProcessArguments ( LNString        &SrcPath,
						LNString        &SrcServer,
						LNString        &DestPath,
						LNString        &DestServer,
						LNString        &Title        )
{
	// Get user input data.
	SetUpNames();

	// Set up LNStrings from the IOParameter strings.
	SrcPath    = (char *)InDbFile;
	SrcServer  = (char *)InDbServer;
	DestPath   = (char *)OutDbFile;
	DestServer = (char *)OutDbServer;
	Title      = (char *)DBTitle;

} // END ProcessArguments()

//---------------------------------------------------------------------------
//
// Name:
//              SetUpNames
//
// Description:
//              Initializes all of the global strings with user input,
//              etc.
//
//---------------------------------------------------------------------------
void SetUpNames()
{
	BOOL IsCorrectData = FALSE;

    while(!IsCorrectData)
    {
		QueryNames();

		PrintNames();

		cout << "Are these current data settings correct? [Y] ";
		cin >> CommandBuf;

		switch(CommandBuf[0])
		{
			case 'Y':                                       
			case 'y':
				IsCorrectData = TRUE;
				break;

			default:
				if(CommandBuf == (const char *)"")
					IsCorrectData = TRUE;
		}
	}
}


//---------------------------------------------------------------------------
//
// Name:
//              PrintNames
//
// Description:
//              Prints out all of the current settings.
//
//---------------------------------------------------------------------------
void PrintNames()
{
	cout << endl;
	cout << "The Current Default Data Settings are: " << endl;
	cout << endl;
	cout << "     Source Database : [" << InDbFile << "]" << endl;
	cout << "     Source Server   : [" << InDbServer << "]" << endl;
	cout << "     Dest Database   : [" << OutDbFile << "]" << endl;
	cout << "     Dest Server     : [" << OutDbServer << "]" << endl;
	cout << "     Database Title  : [" << DBTitle << "]" << endl;
	cout << endl;

	if(IsReplicaCopy)
		cout << "     Destination database will be a replica copy" << endl;
	else
		cout << "     Destination database will NOT be a replica copy" << endl;

	cout << endl;

} // END PrintNames()


//---------------------------------------------------------------------------
//
// Name:
//              QueryNames
//
// Description:
//              Queries the user to change any of the current settings.  Based on
//              state of inames flags.
//
//---------------------------------------------------------------------------
void QueryNames()
{
	cout << endl;

	cout << "Enter Source Database: [" << InDbFile << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		InDbFile = CommandBuf;

	cout << "Enter Source Server: [" << InDbServer << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		InDbServer = CommandBuf;

	cout << "Enter Destination Database: [" << OutDbFile << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		OutDbFile = CommandBuf;

	cout << "Enter Destination Server: [" << OutDbServer << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		OutDbServer = CommandBuf;

	cout << "Enter a Title for the New Database: [" << DBTitle << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		DBTitle = CommandBuf;

	cout << "Do you want the new database to replicate?: [N]> ";
	cin >> CommandBuf;

	switch( CommandBuf[0] )
	{
		case 'Y':                                       
		case 'y':
			IsReplicaCopy = TRUE;
			break;

		default:
			IsReplicaCopy = FALSE;
	}

} // END QueryNames()



//===========================================================================
//
// IOPARAMETER	Class implementation
//
// Description: 
//              Implementation for a simple generic string buffer class
//              to hold user input and output prompts.
//===========================================================================

//===========================================================================
// Constructors.
//===========================================================================
IOParameter::IOParameter() // Default constructor.
{
	Size =1; // null terminator.
	
	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	BufferPointer[0] = '\0';
}

//===========================================================================
IOParameter::IOParameter( const char *Str ) // Init with const string.
{
	Size = strlen(Str) + 1;                                 // Size of string + null term.

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Str);
}


//===========================================================================
// Constructs a decimal radix string representation of an integer.
IOParameter::IOParameter( const int Number )
{
	char    Buffer[16];     // Temporary buffer for characters.

	sprintf(Buffer, "%d", Number);

	Size = strlen(Buffer) + 1;                         // Size of string + null term.

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Buffer);
}


//===========================================================================
IOParameter::IOParameter( const IOParameter &Other ) // Copy constructor.
{
	Size = Other.Size;

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Other.BufferPointer);
}

//===========================================================================
// Constructor using 2 IOParameter objects as input.
IOParameter::IOParameter( const IOParameter& Prefix, const IOParameter& Postfix)
{
	Size = Prefix.Size + Postfix.Size - 1;

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Prefix.BufferPointer);
	strcat(BufferPointer, Postfix.BufferPointer);
}

//===========================================================================
// Subscript, etc.
//===========================================================================
char IOParameter::operator [] (int Index)
{
char Character;

	if (Index > Size)
		Character = '\0';
	else
		Character = BufferPointer[Index];

	return Character;
}

//===========================================================================
// Assignment.
//===========================================================================
IOParameter IOParameter::operator = ( const IOParameter &Other )
{
	if(BufferPointer)
		delete [] BufferPointer;

	Size = Other.Size;
	
	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Other.BufferPointer);

	return *this;
}

//===========================================================================
IOParameter IOParameter::operator = ( const char *Str )
{
	Size = strlen(Str) +1;

	if (BufferPointer)
		delete [] BufferPointer;
	
	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Str);
	return *this;
}

//===========================================================================
// I/O operators.
//===========================================================================
ostream &operator << ( ostream &Stream, const IOParameter &Other )
{
	Stream << Other.BufferPointer;
	return Stream;
}

//===========================================================================
istream &operator >> ( istream &Stream, IOParameter &Other )
{
	const int BufferLength = 255;       // Arbitrary size; change if needed.
	char T[BufferLength];                                                                                         // temp string... 
	int Length;					   
	for (Length=0; Length<BufferLength; Length++)
	{
		Stream.get(T[Length]);
		if (T[Length] == '\n')  // New line character.
			break;
		if (T[Length] == '\b')  // Backspace character.
		{
			if(Length)
			{
				Length--;
				// cout << "'\b'";  // For debug only.
			}
		}
	}

	T[Length] = '\0';
	Length++;

	if(Other.BufferPointer)
		delete [] Other.BufferPointer;

	if (! (Other.BufferPointer = new char[Length]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	Other.Size = Length;

	strcpy(Other.BufferPointer, T);
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
IOParameter IOParameter::operator + ( const char *Str ) // Cat IOParameter and string.
{
	return IOParameter( *this, IOParameter(Str) );
}

//===========================================================================
IOParameter operator + ( char *Str, const IOParameter &Other ) // Cat string with IOParameter.
{
	return IOParameter( IOParameter(Str), Other );
}

//===========================================================================
IOParameter& IOParameter::operator << ( const IOParameter &Other ) // Cat 2 IOParameter objects.
{
	IOParameter TempString(*this);

	Size = TempString.Size + Other.Size - 1;

	if (BufferPointer)
		delete [] BufferPointer;

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, TempString.BufferPointer);
	strcat(BufferPointer, Other.BufferPointer);

	return *this;
}

//===========================================================================
IOParameter& IOParameter::operator << ( const char *Str ) // Cat IOParameter and string.
{
	IOParameter TempString(*this);
	IOParameter Other(Str);

	Size = TempString.Size + Other.Size - 1;

	if (BufferPointer)
		delete [] BufferPointer;

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, TempString.BufferPointer);
	strcat(BufferPointer, Other.BufferPointer);

	return *this;   
}



