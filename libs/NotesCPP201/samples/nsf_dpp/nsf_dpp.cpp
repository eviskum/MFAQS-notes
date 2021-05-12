//===========================================================================
//
//	Program:    NSF_DPP
//
//	File:       NSF_DPP.CPP
//
//	Sytax:		NSFDPP [<dbname>]
//
//				Default dbname = dumpme.nsf
//
//	Description:
//
//		This program is the C++ API version of NSF_DUMP. Instead of
//		dumping the data to a file, a log document is created in a 
//		text file ('nsflog.txt' in your current working directory)
//		created to store the dump information as formatted Rich Text 
//		fields.  
//
//		NOTE: 
//			This program is not intended as a replacemet for the C API
//		    NSF_DUMP program. and should not be used as a tool for 
//			analyzing CD records etc in .NSF files. In fact,  only
//			the first 25 documents are of the .NSF file are dumped.
//			Instead, this program is intended to show just how much 
//			can be done using the C++ API without getting into the 
//			complexity and time consuming task of using the C API.
//          This will help Applications programmers get more done 
//          in less time while still providing many of the features
//			of the C API.
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef NSF_DPP_HPP
#include "nsf_dpp.hpp"
#endif

IOParameter			CommandBuf;
IOParameter			PromptString1;
IOParameter			ParamString1;
IOParameter			PromptString2;
IOParameter			ParamString2;
IOParameter			PromptString3;
IOParameter			ParamString3;
IOParameter			PromptString4;
IOParameter			ParamString4;

//---------------------------------------------------------------------------
//
//	MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	LNNotesSession		Session;

#if defined MAC
// Initializations for the Macintosh
	InitGraf(&thePort); 
	InitFonts();
	InitWindows(); 
	InitDialogs(0);
	SetApplLimit(GetApplLimit()-8192); 
	MaxApplZone();
	MoreMasters(); 
	MoreMasters(); 
	MoreMasters();    
#endif // defined(MAC)

	// Begin TRY Block. 
	// Throw all errors encountered during Command execution.
	LNSetThrowAllErrors(TRUE);
	try
	{
		LNINT			NumDocs, NumItems, i, j;
		LNString		NSFPath;
		LNString		NSFServerPath;
		LNString		LogFilePath;
		LNString		LogServerPath;
		LNString		DBTitle;
		LNDatabase		NSFDb;
		NSFLog			Log;
		LNDocumentArray	Docs;
		LNDocument		Doc;
		LNItemArray		Items;
		LNItem			Item;

		// Initialize a Notes Session first.
		Session.Init(argc, argv);

		// Parse the argument list	
		ProcessArguments( argc, argv, &NSFPath, &NSFServerPath, &LogFilePath, &LogServerPath );

		// Open the Log File.
		Log.Open( &Session, LogFilePath );

		// Get the (Source) NSF database.
		Session.GetDatabase(NSFPath, &NSFDb, NSFServerPath);

		// Open it.
		NSFDb.Open();

		// Get an array of all the documents in the (Source) NSF database.	
		NSFDb.GetDocuments( &Docs );

		DBTitle = NSFDb.GetTitle();
		NumDocs = Docs.GetCount();

		// Log the Database header data to the top of the Log.
		Log.CreateLogEntry( NSFPath, DBTitle, (LNNUMBER)NumDocs );

		// Iterate through the documents in the database.
		for (i=0; i<NumDocs; i++)
		{
			cout << "Dumping note number: " << i << " in "<< (const char *)NSFPath << endl;

			// Get a document.
			Doc = Docs[i];

			// Open it.
			Doc.Open();

			// Get an array of all items in the document.
			Doc.GetItems(&Items);

			// Get the number of items in the document.
			NumItems = Items.GetCount();

			// Start with 1 instead of 0 for the display in the Log.
			Log.AddNewDocHeader( Doc, i+1, NumItems );

			// Iterate through all of the items in the current document.
			for (j=0; j<NumItems; j++)
			{
				// Get an item from the array.
				Item = Items[j];

				// Dump item info to the Log Database.
				Log.AddNewItem( Item, j );
			}

			// Close the current document.
			Doc.Close();

		} // END for(i=0; i<NumDocs; i++)

		// All done. Close the Logfile.
		Log.Close();

		// Close the (Source) NSF database.
		NSFDb.Close();

		cout << endl;
		cout << "Source NSF File: [" << NSFPath << "] was successfully dumped." << endl;

	} // END TRY Block.

	// If an error occurred on any of the above commands get the text
	//  of the error message and display it.
	catch (LNSTATUS lnerror)
	{
	char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(lnerror, ErrorBuf, LNERROR_MESSAGE_LENGTH);
		cout << "\nError:  " << ErrorBuf << endl;
	}

	catch (const char *pErrorMessage)
	{
		cout << "\nError: " << pErrorMessage << endl;
	}

	// Terminate the Notes Session.
	Session.Term();

	cout << endl;
	cout << "Hit Return To Exit: ";
	cin >> CommandBuf;

	return (0);

} // END main()

//---------------------------------------------------------------------------
//
// Name:
//		ProcessArguments
//
// Description:
//      Scan the input command line and sort out the input strings.
//      If no arguments were supplied, prompt for them.
//
//      Throws exceptions:
//              char *          Argument error description
//---------------------------------------------------------------------------
void ProcessArguments ( int			argc,
						char		*argv[],
						LNString	*NSFPath,
						LNString	*NSFServerPath,
						LNString	*LogFilePath,
						LNString	*LogServerPath  )
{
LNBOOL prompt = FALSE;

// Macintosh cannot process (argc, argv)
#if defined(MAC)
	prompt = TRUE;
#else
	if (argc < 4)
		prompt = TRUE;	
#endif

	// Set up the default parameters first.
	InitDefaultParams();
	*NSFPath		= ParamString1;
	*NSFServerPath	= ParamString2;
	*LogFilePath	= ParamString3;
	*LogServerPath	= ParamString4;

	// Check the command line.
	if (prompt)
	{
		// Get User Input Data by prompting.
		GetArguments();
		*NSFPath		= ParamString1;
		*NSFServerPath	= ParamString2;
		*LogFilePath	= ParamString3;
		*LogServerPath	= ParamString4;
	}
	else
	{
		// parse the command line strings.
		*NSFPath 		= argv[1];
		*NSFServerPath	= argv[2];
		*LogFilePath	= argv[3];
		*LogServerPath	= argv[4];

	} // END if (argc < 2) ELSE

} // END ProcessArguments()

//---------------------------------------------------------------------------
//
// Name:
//		InitDefaultParams
//
// Description:
//		Set up all the default parameter strings and numbers for user
//		input.  Called by ProcessArguments() if no user input params
//		were provided.
//
//		NOTE:
//			You only need to Edit this function and ProcessArguments() 
//			when creating a new sample.  The rest of the user interface 
//			functions below are called by ProcessArguments() and are 
//			generic which means that they can stay the same unless
//			you modify the number of parameters to use.
//			Then you only need to cut or paste a block of 
//			the switch statements in the functions below.
//---------------------------------------------------------------------------
void InitDefaultParams()
{
	// Initialize default parameter strings...

	PromptString1	=  "File path name for the input database to dump : [";
	ParamString1	= "dumpme.nsf";

	PromptString2	=  "Path of the server for the input database     : [";
	ParamString2	= "";

	PromptString3	=  "File path name for the output log file    : [";
	ParamString3	= "nsflog.txt";

	PromptString4	=  "Path of the server for the output log         : [";
	ParamString4	= "";

} // END InitDefaultParams()

//---------------------------------------------------------------------------
//
// Name:
//		GetArguments
//
// Description:
//		Allows the user to change any or all of the input parameter 
//		IOParameter.  The inputs can also be left as is.
//---------------------------------------------------------------------------
void GetArguments()
{
	BOOL IsCorrectData = FALSE;

	QueryArguments();

	while(! IsCorrectData)
	{
		PrintArguments();

		cout << "Are these current data settings correct?      : [Y] ";
		cin >> CommandBuf;

		switch( CommandBuf[0] )
		{
			case 'Y':
			case 'y':

				IsCorrectData = TRUE;				// All Done, Get out now!
				break;

			default:

				// Prompt again for anything other than a "Y" or "CARRIAGE RETURN".
				if( (CommandBuf) != (const char *)"" )
					QueryArguments();
				else
					IsCorrectData = TRUE;			// All Done, Get out now!

		} // END switch

	} // END while

} // END GetArguments()

//---------------------------------------------------------------------------
//
// Name:
//		PrintArguments
//
// Description:
//		Prints out all of the current input Parameters to use.
//---------------------------------------------------------------------------
void PrintArguments()
{
	cout << endl;
	cout << "The current default data settings are: " << endl;
	cout << endl;

	// Print out current parameter strings...
	cout << PromptString1 << ParamString1 << "]" << endl;
	cout << PromptString2 << ParamString2 << "]" << endl;
	cout << PromptString3 << ParamString3 << "]" << endl;
	cout << PromptString4 << ParamString4 << "]" << endl;

	cout << endl;

} // END PrintArguments()

//---------------------------------------------------------------------------
//
// Name:
//		QueryArguments
//
// Description:
//		Querys the user to change any of the input parameters.
//		a carriage return on any of the prompts leaves it alone.
//---------------------------------------------------------------------------
void QueryArguments()
{
	cout << endl;
	cout << "Enter the following parameters (Enter by itself takes the default):" << endl;
	cout << endl;

	// Prompt for strings....
	cout << PromptString1 << ParamString1 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString1 = CommandBuf;

	cout << PromptString2 << ParamString2 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString2 = CommandBuf;

	cout << PromptString3 << ParamString3 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString3 = CommandBuf;

	cout << PromptString4 << ParamString4 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString4 = CommandBuf;

} // END QueryArguments()



//===========================================================================
//
// IOPARAMETER Class Implementation
//
// Description:	
//		Implementation for a simple generic string buffer class.
//		to hold user input and output prompts.
//===========================================================================

//===========================================================================
// Constructors
//===========================================================================
IOParameter::IOParameter() // Default Constructor.
{
	size =1; // Null Terminator.
	
	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	pBuf[0] = '\0';
}

//===========================================================================
IOParameter::IOParameter( const char *Str ) // Init with const string.
{
	size = strlen(Str) + 1;					// Size of string + null term.

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, Str);
}


//===========================================================================
// Constructs a decmal radix string representation in of an integer.
IOParameter::IOParameter( const int Number )
{
char	buf[16];						// Temporary Buffer for characters.

	sprintf(buf, "%d", Number);

	size = strlen(buf) + 1;				// Size of string + null term.

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, buf);
}


//===========================================================================
IOParameter::IOParameter( const IOParameter &Other ) // copy constructor
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
// Subscript etc...
//===========================================================================
char IOParameter::operator [] (int index)
{
char c;

	if (index > size)
		c = '\0';
	else
		c = pBuf[index];

	return c;
}

//===========================================================================
// Assignment...
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
IOParameter IOParameter::operator = ( const char *Str )
{
	size = strlen(Str) +1;

	if (pBuf)
		delete [] pBuf;
	
	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, Str);
	return *this;
}

//===========================================================================
// I/O operators...
//===========================================================================
ostream &operator << ( ostream &Stream, const IOParameter &Other )
{
	Stream << Other.pBuf;
	return Stream;
}

//===========================================================================
istream &operator >> ( istream &Stream, IOParameter &Other )
{
const int buflen = 255;					// Arbitrary size change if needed...
char t[buflen];						// temp string... 
int len;

	for (len=0; len<buflen; len++)
	{
		Stream.get(t[len]);
		if (t[len] == '\n')  // New line character
			break;
		if (t[len] == '\b')  // Backspace character
		{
			if(len)
			{
				len--;
				// cout << "'\b'";  // for debug only...
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
// Concatenate...
//===========================================================================
IOParameter IOParameter::operator + ( const IOParameter &Other ) // Cat 2 IOParameter objects
{
	return IOParameter( *this, Other );
}

//===========================================================================
IOParameter IOParameter::operator + ( const char *str ) // Cat IOParameter and String.
{
	return IOParameter( *this, IOParameter(str) );
}

//===========================================================================
IOParameter operator + ( char *str, const IOParameter &Other ) // Cat string with IOParameter
{
	return IOParameter( IOParameter(str), Other );
}

//===========================================================================
IOParameter& IOParameter::operator << ( const IOParameter &Other ) // Cat 2 IOParameter objects
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
IOParameter& IOParameter::operator << ( const char *str ) // Cat IOParameter and String.
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


