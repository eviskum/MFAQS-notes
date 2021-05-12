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
//      This is a Notes C++ API program that opens a Notes database and
//      dumps information about its contents, (Database Information,
//      Notes, Items, and Item records) to a plain text log file.
//
//      This program exercises many of the (read only) tasks you can
//      perform with the C++ API.  It is roughly a C++ counterpart to the
//      C API NSF_DUMP program.
//
//      NOTE: Code that takes advantage of newer features of the C++ API,
//      (i.e. Versions after the 2.1 release) May not yet be implemented
//      in this sample.
//
//===========================================================================

#ifndef NSF_DPP_HPP
#include "nsf_dpp.hpp"
#endif

// Global definitions

IOParameter			CommandBuf;
IOParameter			PromptString1;
IOParameter			ParamString1;
IOParameter			PromptString2;
IOParameter			ParamString2;
IOParameter			PromptString3;
IOParameter			ParamString3;
IOParameter			PromptString4;
IOParameter			ParamString4;

// Global and Forward Declarations for Rich Text Parser Error Handling.
// See "Example: Rich text parser error recovery" in Appendex A of 
// the C++ API User's Guide.

void ProcessError( LNSTATUS error );
LNSTATUS ProcessRichText( const LNRTPARSERERRORDATA &data );

// number of exceptions thrown by program

LNINT ErrorCount = 0;

// Save state when last error was found.

NOTEID   PrevID;
LNString PrevName;
DWORD    PrevOffset;
WORD     PrevCDSig;
DWORD    PrevCDSize;

// Pointer for NSFLog object.  Must be global so it can be used by the
// rich text error handler. (this is not the best way to do this!)

NSFLog * pLog = 0;

//---------------------------------------------------------------------------
//
//	MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
LNNotesSession  Session;
LNBOOL			printscreen = TRUE;

	// Begin TRY Block. 
	// Throw all errors encountered during Command execution.
	LNSetThrowAllErrors(TRUE);
	try
	{
		LNINT			NumNotes, NumItems, i, j;
		LNString		NSFPath;
		LNString		NSFServerPath;
		LNString		LogFilePath;
		LNString		LogServerPath;
		LNString		Options;
		LNString		DBTitle;
		LNDatabase		NSFDb;
        LNNoteArray     Notes;
        LNNote          Note;
		LNItemArray		Items;
		LNItem			Item;
		LNINT			pos;

		// Initialize a Notes Session first.
		Session.Init(argc, argv);

		// Parse the argument list	
		ProcessArguments( argc, argv, &NSFPath,
						  &NSFServerPath, &LogFilePath,
						  &LogServerPath, &Options );

		// Find out if there are any options.
		// (currently there is only one option "s" for Silent or Smoketest mode.
		if( Options.FindChar("s", 0, &pos) == LNNOERROR )
			printscreen = FALSE;

        // Instantiate an NSFLog obj.
        pLog = new NSFLog();

		// Open the Log File.
		pLog->Open( &Session, LogFilePath );

		// Get the (Source) NSF database.
		Session.GetDatabase(NSFPath, &NSFDb, NSFServerPath);

        // Set the rich text parser error handler which will print out information
        // when parser errors are encountered while initializing rich text.
        LNRTPARSERERRORHANDLER fn = Session.SetRTParserErrorHandler(&ProcessRichText);

		// Open it.
		NSFDb.Open();

		// Get an array of all the notes in the (Source) NSF database.
		NSFDb.GetNotes( &Notes );

		DBTitle = NSFDb.GetTitle();
		NumNotes = Notes.GetCount();

		// Log the Database header data to the top of the Log.
		pLog->CreateLogEntry( NSFPath, DBTitle, (LNNUMBER)NumNotes );

		// Iterate through the notes in the database.
		for (i=0; i<NumNotes; i++)
		{
			if (printscreen)
				cout << "Dumping note number: " << i << " in "<< (const char *)NSFPath << endl;

			// Get a note.
			Note = Notes[i];

			// Open it.
			Note.Open();

			// Get an array of all items in the note.
			Note.GetItems(&Items);

			// Get the number of items in the note.
			NumItems = Items.GetCount();

			// Start with 1 instead of 0 for the display in the Log.
			pLog->AddNewNoteHeader( Note, i+1, NumItems );

			// Iterate through all of the items in the current note.
			for (j=0; j<NumItems; j++)
			{
				// Get an item from the array.
				Item = Items[j];

				// Dump item info to the Log Database.
				pLog->AddNewItem( Item, j );
			}

			// Close the current note.
			Note.Close();

		} // END for(i=0; i<NumNotes; i++)

		// All done. Close the Logfile.
		pLog->Close();

		// Close the (Source) NSF database.
		NSFDb.Close();

		if (printscreen)
		{
			cout << endl;
			cout << "Source NSF File: [" << NSFPath << "] was successfully dumped." << endl;
		}

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

    // Destroy the NSFLog object.
    delete pLog;

	if (printscreen)
	{
		cout << endl;
		cout << "Hit Return To Exit: ";
		cin >> CommandBuf;
	}

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
						LNString	*LogServerPath,
						LNString	*Options  )
{
LNBOOL prompt = FALSE;

	if (argc < 2)
		prompt = TRUE;

	// Set up the default parameters first.

	InitDefaultParams();
	*NSFPath		= ParamString1;
	*NSFServerPath	= ParamString2;
	*LogFilePath	= ParamString3;
	*LogServerPath	= ParamString4;
	*Options		= "";

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

        switch (argc)
        {
        case 2:

		    *NSFPath 		= argv[1];
            break;

        case 3:

		    *NSFPath 		= argv[1];
		    *NSFServerPath	= argv[2];
            break;

        case 4:

		    *NSFPath 		= argv[1];
		    *NSFServerPath	= argv[2];
		    *LogFilePath	= argv[3];
            break;

        case 5:

		    *NSFPath 		= argv[1];
		    *NSFServerPath	= argv[2];
		    *LogFilePath	= argv[3];
		    *LogServerPath	= argv[4];
            break;

        case 6:

		    *NSFPath 		= argv[1];
		    *NSFServerPath	= argv[2];
		    *LogFilePath	= argv[3];
		    *LogServerPath	= argv[4];
		    *Options		= argv[5];
            break;
        }

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


//---------------------------------------------------------------------------
//
// Rich Text Parser Error Handling functions
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// Name:
//		ProcessError
//
// Description:
//		Prints out error status. Used by ProcessRichText
//---------------------------------------------------------------------------
void ProcessError( LNSTATUS error )
{
char        msgbuf[LNERROR_MESSAGE_LENGTH];
LNString    errormessage;

    // Display the error message and increment the error count.

    LNGetErrorMessage(error, msgbuf);

    errormessage = "Rich Text Parsor Error! Count: [";
    errormessage << ErrorCount;
    errormessage << "] Message: ";
    errormessage << msgbuf;

    if ( pLog != 0 )
        pLog->LogMainHeading(errormessage);
    else
        cout << endl << errormessage << endl;

    ErrorCount++;
}

//---------------------------------------------------------------------------
//
// Name:
//      ProcessRichText
//
// Description:
//      Error handler for Rich Text Parser hangups.
//
// Remarks:
//
//      Definition of the LNPARSERERRORDATA from lnrt.hpp
//
//      struct LNRTPARSERERRORDATA
//      {
//          const LNItem *Item; // Rich text item, not fully initialized
//          LNINT       Offset; // From the beginning of the rich text, excluding the initial type word
//          WORD        CDSig;  // The signature of the cd record at the given offset
//          LNINT       CDSize; // The size of the cd record at the given offset
//          LNSTATUS    Status; // Error status found
//     };
//
//      Global defs from above...
//
//          NOTEID   PrevID;
//          LNString PrevName;
//          DWORD    PrevOffset;
//          WORD     PrevCDSig;
//          DWORD    PrevCDSize;
//
//---------------------------------------------------------------------------
LNSTATUS ProcessRichText( const LNRTPARSERERRORDATA &data )
{
LNNote doc = data.Item->GetNote();
NOTEID id = doc.GetNoteID();

    // If we've seen this problem before - go on without printing more
    // info

    if ( (id != PrevID)                     ||
         (data.Item->GetName() != PrevName) ||
         (data.Offset != PrevOffset)        ||
         (data.CDSig != PrevCDSig)          ||
         (data.CDSize != PrevCDSize)  )
    {
    LNString tempstring;

        PrevID     = id;
        PrevName   = data.Item->GetName();
        PrevOffset = data.Offset;
        PrevCDSig  = data.CDSig;
        PrevCDSize = data.CDSize;

        ProcessError(data.Status);

        // Dont log if pointer is no longer valid.

        if ( pLog == 0 )
            return data.Status;

        // log information about the problem rich text item but don't allow 
        // the parser to continue.

	    // Append the current Note ID to the log.
	    pLog->LogLabel( "Note ID            ", PrevID, 10 );

	    // Append the current Item name to the log.
	    pLog->LogLabel( "Item Name          ", PrevName );

        tempstring = pLog->GetCDSignatureString ( PrevCDSig );

	    // Append the currnet CD Sig to the log.
	    pLog->LogLabel( "CD Signature       ", PrevName );
    }

    return data.Status;

}// END ProcessRichText()


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


