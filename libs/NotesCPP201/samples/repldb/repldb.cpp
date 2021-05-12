//===========================================================================
//
//      Module: REPLDB.CPP
//
//      Description:
//              Sample C++ API program that creates a replica database 
//				(replica.nsf) and replicates the new document added to the 
//				source database.
//
//      Syntax: REPLDB [<sourcedbname>] [server]
//
//              Where sourcedbname = file path name for the source database 
//				for replication. If the user does not supply this parameter, 
//				the default source database (repldb.nsf) will be used.
//
//===========================================================================
//
// Copyright (c) 1997,1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef REPLDB_HPP
#include "repldb.hpp"
#endif

// Parameter strings.
IOParameter             CommandBuf;
IOParameter             PromptString1;
IOParameter             ParamString1;
IOParameter             PromptString2;
IOParameter             ParamString2;

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int				ProgramStatus = 0;
	LNNotesSession	Session;
	LNSTATUS		Status;

#if defined (MAC)
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

	LNSetThrowAllErrors(TRUE);

	// Initialize the Notes session.
	Status = Session.Init(argc, argv);
	if (Status)
	{
		cout << "\nUnable to initialize the API" << endl;
		return(1);
	}

	LNDatabase	SourceDb;

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try
	{
		LNString	SourceDbPath;
		LNString	SourceDbServer;
		LNDatabase	ReplicaDb;

		//Parse the argument list.       
		ProcessArguments ( argc, argv, &SourceDbPath, &SourceDbServer);

		//Get the specified database.
		Session.GetDatabase(SourceDbPath, &SourceDb, SourceDbServer);

		LNString	ReplicaDbName = "replica.nsf";
		LNString	ReplicaServer = "";

		//Now, create a database replica!
		Session.CreateDatabaseReplica(SourceDbPath, SourceDbServer, 
									  ReplicaDbName, ReplicaServer, &ReplicaDb);

		SourceDb.Open();

		LNDocumentArray SourceDbDocs;
		SourceDb.GetDocuments(&SourceDbDocs);

		//Let's create a new document by copying an existing document 
		//in the source database, and replicate the changes made to the 
		//source database to the replica database.
		if (SourceDbDocs.GetCount() != 0)
		{
			LNDocument SourceDoc = SourceDbDocs[0];
			LNDocument NewDoc;
			SourceDb.CreateDocument(SourceDoc, &NewDoc);
			NewDoc.Save();
		}

		LNReplicationOptions RepOpt;
		LNReplicationStatistics Stats;

		//Set the replication options first.
		RepOpt.SetCloseSession(TRUE);
		RepOpt.SetDirection(LNREPLICATIONDIRECTION_RECEIVE);

		//Set the replica file name in the replication option settings.
		LNText  FileList;
		FileList.Append(ReplicaDbName);
		RepOpt.SetFileList(FileList);

		//Replicate this specific file.
		RepOpt.SetFileType(LNREPLICATIONFILETYPE_SPECIFIC);

		//Now replicate the changes.
		Session.Replicate(SourceDbServer, RepOpt, &Stats);

		//Get the replication result.
		LNINT  DocAdded = (Stats.GetReceivedStatistics()).GetNotesAdded();

		//Output the replication statistics.
		cout << "Replication Statistics - Document(s) Added: " << DocAdded << endl;

	} // END try

	//Error handler.  If an error occurred, get the text of
	//the error message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(lnerror, ErrorBuf);
		cout << "\nError:  " << ErrorBuf << endl;
		ProgramStatus = 2;
	}

	catch (const char *ErrorMessage)
	{
		cout << "\nError: " << ErrorMessage << endl << endl;
		ProgramStatus = 1;
	}

	//Done, close the source database.
	if (SourceDb.IsOpen())
		SourceDb.Close();

	//Terminate the API.
	Session.Term();

	cout << endl;
	cout << "Hit Return To Exit: ";
	cin >> CommandBuf;

	//All done.
	return (ProgramStatus);

} // END MAIN


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
void ProcessArguments ( int			argc,
						char		*argv[],
						LNString	*SourceDbPath,
						LNString	*SourceDbServer )
{
	LNBOOL Prompt = FALSE;

// Macintosh cannot process (argc, argv).
#if defined(MAC)
	Prompt = TRUE;
#else
	if (argc < 2)
		Prompt = TRUE;  
#endif

	// Set up the default parameters first.
	InitDefaultParams();
	*SourceDbPath = ParamString1;
	*SourceDbServer = ParamString2;

	if (Prompt)
	{
		// Get user input data by Prompting.
		GetArguments();
		*SourceDbPath = ParamString1;
		*SourceDbServer = ParamString2;
	}
	else
	{
		// Parse the command line.
		*SourceDbPath = argv[1];
		*SourceDbServer = argv[2];
	} // END if (argc < 1) ELSE

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
//              You only need to edit this function and ProcessArguments() 
//              when creating a new sample.  The rest of the user interface 
//              functions below are called by ProcessArguments() and are 
//              generic, which means that they can stay the same unless
//              you modify the number of parameters to use.
//              Then you only need to cut or paste in one more or one less
//              block of the switch statements in the functions below.
//---------------------------------------------------------------------------
void InitDefaultParams()
{
	//Initialize default parameter strings.

	PromptString1 =  "File path name for the database to replicate: [";
	ParamString1 = "repldb.nsf";

	PromptString2 =  "Server name for the database: [";
	ParamString2 = "";

} // END InitDefaultParams()

//---------------------------------------------------------------------------
//
// Name:
//              GetArguments
//
// Description:
//              Allows The user to change any or all of the input parameter 
//              IOParameter.  The inputs can also be left as they are if desired.
//---------------------------------------------------------------------------
void GetArguments()
{
	BOOL IsCorrectData = FALSE;

	QueryArguments();

	while(! IsCorrectData)
	{
		PrintArguments();

		cout <<  "Are these current data settings correct? : [Y] ";
		cin >> CommandBuf;

		switch( CommandBuf[0] )
		{
			case 'Y':
			case 'y':

				IsCorrectData = TRUE;			// All done; get out now!
				break;

			default:

				// Prompt again for anything other than a "Y" or carriage return.
				if( (CommandBuf) != (const char *)"" )
					QueryArguments();
				else
					IsCorrectData = TRUE;		// All done; get out now!

		} // END switch

	} // END while

} // END GetArguments()

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
	cout << "Enter the following parameters (Enter by itself takes the default):" << endl;
	cout << endl;

	// Prompt for strings.
	cout << PromptString1 << ParamString1 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString1 = CommandBuf;

	cout << PromptString2 << ParamString2 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString2 = CommandBuf;

} // END QueryArguments()


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

	// Print out current parameter strings.
	cout << PromptString1 << ParamString1 << "]" << endl;
	cout << PromptString2 << ParamString2 << "]" << endl;

} // END PrintArguments()




//===========================================================================
//
// IOPARAMETER Class implementation
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
	size = strlen(Str) + 1;                                 // Size of string + null term.

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, Str);
}


//===========================================================================
// Constructs a decimal radix string representation of an integer.
IOParameter::IOParameter( const int number )
{
	char	Buf[16];	// Temporary buffer for characters.

	sprintf(Buf, "%d", number);

	size = strlen(Buf) + 1;    // Size of string + null term.

	if(! (pBuf = new char[size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(pBuf, Buf);
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

	if( !(pBuf = new char[size]) )
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
	const int	buflen = 255; // Arbitrary size; change if needed.
	char 		t[buflen];                                                                                         // temp string... 
	int 		len;

	for (len=0; len<buflen; len++)
	{
		Stream.get(t[len]);
		if (t[len] == '\n')  // New-line character.
			break;
		if (t[len] == '\b')  // Backspace character.
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
IOParameter IOParameter::operator + ( const char *Str ) // Cat IOParameter and string.
{
	return IOParameter( *this, IOParameter(Str) );
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


