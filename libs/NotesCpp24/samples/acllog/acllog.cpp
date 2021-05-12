//===========================================================================
//
//      Module: ACLLOG.CPP
//
//      Description:
//              Sample C++ API program that creates an access control entry 
//              list log file.
//
//      Syntax:         ACLLOG  <dbname> [server]
//
//              Where dbname = file path name for the database to add the ACL
//              information. If you do not supply this parameter you will be  
//              prompted for arguments at run time.
//
//===========================================================================

#ifndef ACLLOG_HPP
#include "acllog.hpp"
#endif

// Parameter Strings
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
	LNNotesSession  Session;
	LNSTATUS        Stat;

	LNSetThrowAllErrors(TRUE);

	LNDatabase		ACLDb;
    ACLLog			Log;

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try
	{
		LNString                ACLDbTitle;
		LNDocument              Doc;
		LNString                DatabasePath;
		LNString                ServerName;

		// Initialize the Notes session.
		Session.Init(argc, argv);

		// Parse the argument list.      
		ProcessArguments( argc, argv, &DatabasePath, &ServerName);

		LNString                AclLogFile = "acllog.nsf";
		LNString                AclLogServer = "";

		// Get the specified database.
		Session.GetDatabase(DatabasePath, &ACLDb, ServerName);

		// Open the log database.
		Stat = Log.OpenAclDB( &Session, AclLogFile, AclLogServer );
		if (Stat)
			throw Stat;

		LNACL                   Acl;
		LNACLEntryArray			Entries;
		LNACLEntry              Entry;
		LNACLRoleArray			EntryRoles;
		LNINT                   EntryCount,EntryRoleCount; 
		LNINT                   Index1, Index2;

		ACLDb.Open();
		ACLDbTitle = ACLDb.GetTitle();

		// Get the database's ACL.
		Stat = ACLDb.GetACL(&Acl);
		Stat = Acl.GetEntries(&Entries);
		EntryCount = Entries.GetCount();

		for (Index1 = 0; Index1 < EntryCount; Index1 ++)
		{
			// Create a New log document to log all of the ACL entry list
			// data to. Log the db data to the top of the new log.
			Stat = Log.CreateLogEntry( ServerName, DatabasePath, ACLDbTitle );
			if (Stat)
				throw Stat;

			// Then output all the ACL entry info in the ACL.
			Entry = Entries[Index1];
			Stat = Log.AddACLEntry( Entry );
			if (Stat)
				throw Stat;

			cout << "Entry Name: " << Entry.GetName() << endl;

			// Output all the roles for each ACL entry.
			Entry.GetRoles(&EntryRoles);

			EntryRoleCount = EntryRoles.GetCount();
			for (Index2 = 0; Index2 < EntryRoleCount; Index2 ++)
			{
				cout << "   Entry Role Name: " << EntryRoles[Index2] << endl;
			}
	
			// All done; close the ACL log document.
			Stat = Log.CloseLogEntry();
			if (Stat)
				throw Stat;
		}   

	}// try

	// Error handler.  If an error occurred, get the text of
	// the error message and display it.
	catch (LNSTATUS lnerror)
	{
	char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(lnerror, ErrorBuf);
		cout << "\nError:  " << ErrorBuf << endl;
		ProgramStatus = 2;
	}

	catch (const char *pErrorMessage)
	{
		cout << "\nError: " << pErrorMessage << endl << endl;
		ProgramStatus = 1;
	}

	// Close the log database.
	if (Log.IsDbOpen())
		Log.CloseAclDB();

	// Close the source database. 
	if (ACLDb.IsOpen())
		ACLDb.Close();

	// Terminate the API.
	Session.Term();

	cout << endl;
	cout << "Hit Return To Exit: ";
	cin >> CommandBuf;

	return (ProgramStatus);

} // END MAIN


//===========================================================================
//
// ACLLog Class Implementation
//
// Description: 
//              Implementation of an Abstract Logging ACL object which can be 
//              used to store and keep track of ACL entry list information 
//              from a user-specified .NSF file.
//===========================================================================

//---------------------------------------------------------------------------
//
// Name:
//              Default constructor
//
//---------------------------------------------------------------------------
ACLLog::ACLLog()
{ 
	LogSession              = 0; 
	IsDBOpen                = FALSE;
	IsDocOpen               = FALSE;
}

//---------------------------------------------------------------------------
//
// Name:
//              Destructor
//
//---------------------------------------------------------------------------
ACLLog::~ACLLog( )
{
}

//---------------------------------------------------------------------------
//
// Name:
//              ACLLog::OpenAclDB
//
// Description:
//              Opens the ACL log database for ACL info.  This version takes 
//				a pointer to an initialized LNNotesSession object.
//
// Inputs:
//              session         Pointer to an initialized Notes session object
//              path:           Database pathname
//              server:         Server name (null string for local database)
//
// Outputs:
//              If successful, the database is opened and ready for log entries.
//
// Returns:
//              0 if successful, error code otherwise.
//
//---------------------------------------------------------------------------
LNSTATUS ACLLog::OpenAclDB( LNNotesSession *Session, const LNString &Path, 
							const LNString &Server)
{
	LNSTATUS        Error;

	if (! LNIsNotesInitialized() )
		return LNERR_SESSION_NOT_INITIALIZED;

	if (!Session)
		return LNERR_NULL_POINTER_PARAMETER;

	LogSession = Session;

	// Get the specified Log database.
	Error = LogSession->GetDatabase(Path, &ACLLogDb, Server);
	if (Error)
		return Error;
	
	// Open it.
	Error = ACLLogDb.Open();
	if (Error)
		return Error;

	IsDBOpen = TRUE;

	return LNNOERROR;

} // END ACLLog::OpenAclDB

//---------------------------------------------------------------------------
//
// Name:
//              ACLLog::CloseAclDB
//
// Description:
//              Closes the ACL log database for ACL Log.
//
//---------------------------------------------------------------------------
LNSTATUS ACLLog::CloseAclDB()
{
	LNSTATUS        Error;

	if (! IsDBOpen )
		return LNWARN_NOT_OPEN;

	// Close the database.
	Error = ACLLogDb.Close();
	IsDBOpen = FALSE;

	return Error;

} // END ACLLog::CloseAclDB

//---------------------------------------------------------------------------
//
// Name:
//              ACLLog::CreateLogEntry
//
// Description:
//              A new document is created in the log database and the main
//              heading is recorded in it. All of the db info about the 
//              specified .NSF file being logged is added to the header area.
//
// Inputs:
//              The file name of the .NSF file to iterate the ACL entries.
//              The title of the database for which the ACL entries are being 
//              iterated.
//
// Outputs:
//              A new ACL log document is created in the log database.
//
// Returns:
//              Success or error code
//
//---------------------------------------------------------------------------
LNSTATUS ACLLog::CreateLogEntry(const LNString &ServerName, const LNString &NSFName, 
								const LNString &DBTitle)
{
	LNSTATUS        Error;
	LNDatetime      Dt;
	LNDatetimes     TimeFld;
	LNText          ServerNameFld;
	LNText          NSFNameFld;
	LNText          DBTitleFld;

	if (! IsDBOpen )
		return LNERR_DATABASE_CLOSED;

	// Create a new document log Entry.
	Error = ACLLogDb.CreateDocument(&AclEntryDoc);
	if (Error)
		return Error;

	// Attach the document to the "U&G".
	Error = AclEntryDoc.SetForm("U&G");
	if (Error)
		return Error;

	// Set up some flags for this log doc that are needed later. 
	IsDocOpen = TRUE;

	// Get a snapshot of the current date/time. 
	Dt = LogSession->GetCurrentDatetime();

	// Set the current datetime into the TimeField LNItem.
	Error = TimeFld.SetValue(Dt);
	if (Error)
		return Error;

	// Create the new time field item in the new document.
	Error = AclEntryDoc.CreateItem("ModTime", TimeFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	// Set the new server name field to the supplied server name.
	if (ServerName.IsNull())
	{
		Error = ServerNameFld.SetValue("Local");
		if(Error)
			return Error;
	}
	else
	{
		Error = ServerNameFld.SetValue(ServerName);
		if (Error)
			return Error;
	}

	// Create the new server name field item in the new document.
	Error = AclEntryDoc.CreateItem("Server", ServerNameFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	// Set the new NSF name field to the supplied NSF file name.
	Error = NSFNameFld.SetValue(NSFName);
	if (Error)
		return Error;

	// Create the new NSF name field item in the new document.
	Error = AclEntryDoc.CreateItem("DBFile", NSFNameFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	// Set the database title field.  
	Error = DBTitleFld.SetValue(DBTitle);
	if (Error)
		return Error;

	// Create the database title field item in the new document.
	Error = AclEntryDoc.CreateItem( "DBTitle", DBTitleFld, LNITEMFLAGS_SUMMARY );
	if (Error)
		return Error;

	// Save the newly created document to disk but leave it open 
	// for appends to the log Entry field.
	Error = AclEntryDoc.Save();
	if (Error)
		return Error;

	return LNNOERROR;

} // END ACLLog::CreateLogEntry

//---------------------------------------------------------------------------
//
// Name:
//              ACLLog::AddACLEntry()
//
// Description:
//              A new document is created in the log database and the main
//              heading is recorded in it. All of the ACL entry info about 
//              the specified .NSF file is being logged to the document.
//
// Inputs:
//              LNACLEntry for the ACL entry information.
//
// Outputs:
//              None
//
// Returns:
//              Success or error code
//
//---------------------------------------------------------------------------
LNSTATUS ACLLog::AddACLEntry(LNACLEntry &Entry)
{
	LNSTATUS Error;

	if (! IsDBOpen )
		return LNERR_DATABASE_CLOSED;

	if (! IsDocOpen )
		return LNNOERROR;

	LNText  EntryNameFld;
	Error = EntryNameFld.SetValue(Entry.GetName());
	if (Error)
		return Error;
	Error = AclEntryDoc.CreateItem("Name", EntryNameFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNString Roles;
	LNACLRoleArray ARoles;
	LNText  RoleNameFld;

	Entry.GetRoles(&ARoles);
	LNINT Count = ARoles.GetCount();
	for (LNINT Index = 0; Index < Count; Index++)
	{
		Roles << ARoles[Index];
		if (Index < Count - 1)
			Roles << ", "; // a separator
	}

	// Set the new entry name field to the supplied entry name.
	if (Count == 0)
	{
		Error = RoleNameFld.SetValue("None");
		if (Error)
			return Error;
	}
	else 
	{
		Error = RoleNameFld.SetValue(Roles);
		if (Error)
			return Error;
	}

	// Create the new NSF name field item in the new document.
	Error = AclEntryDoc.CreateItem("Roles", RoleNameFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText TypeFld;
	switch(Entry.GetUserType())
	{
		case  LNACLUSERTYPE_PERSON:
		{
			Error = TypeFld.SetValue("Person");
			if (Error)
				return Error;
			break;
		}       
		case LNACLUSERTYPE_SERVER:
		{
			Error = TypeFld.SetValue("Server");
			if (Error)
				return Error;
			break;
		}       
		case LNACLUSERTYPE_GROUP:
		{
			Error = TypeFld.SetValue("Group");
			if (Error)
				return Error;
			break;
		}       
		case LNACLUSERTYPE_PERSONGROUP:
		{
			Error = TypeFld.SetValue("Person Group");
			if (Error)
				return Error;
			break;
		}       
		case    LNACLUSERTYPE_SERVERGROUP:
		{
			Error = TypeFld.SetValue("Server Group");
			if (Error)
				return Error;
			break;
		}       
		case LNACLUSERTYPE_UNKNOWN:
		{
			Error = TypeFld.SetValue("Unknown");
			if (Error)
				return Error;
			break;
		}       
	}

	Error = AclEntryDoc.CreateItem("Type", TypeFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText   LevelFld;
	switch(Entry.GetAccessLevel())
	{
		case  LNACLLEVEL_NO_ACCESS:
		{
			Error = LevelFld.SetValue("No Access");
			if (Error)
				return Error;
			break;
		}       
		case LNACLLEVEL_DEPOSITOR:
		{
			Error = LevelFld.SetValue("Depositor");
			if (Error)
				return Error;
			break;
		}       
		case LNACLLEVEL_READER:
		{
			Error = LevelFld.SetValue("Reader");
			if (Error)
				return Error;
			break;
		}       
		case LNACLLEVEL_AUTHOR:
		{
			Error = LevelFld.SetValue("Author");
			if (Error)
				return Error;
			break;
		}       
		case    LNACLLEVEL_EDITOR:
		{
			Error = LevelFld.SetValue("Editor");
			if (Error)
				return Error;
			break;
		}       
		case LNACLLEVEL_DESIGNER:
		{
			Error = LevelFld.SetValue("Designer");
			if (Error)
				return Error;
			break;
		}       
		case LNACLLEVEL_MANAGER:
		{
			Error = LevelFld.SetValue("Manager");
			if (Error)
				return Error;
			break;
		}       
	}

	Error = AclEntryDoc.CreateItem("Level", LevelFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText CreDocFld;
	if (Entry.GetCanCreateDocuments())
	{
		Error = CreDocFld.SetValue("Yes");
		if (Error)
			return Error;
	}
	else 
	{
		Error = CreDocFld.SetValue("No");
		if (Error)
		return Error;
	}

	Error = AclEntryDoc.CreateItem("CreDoc", CreDocFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText DelDocFld;
	if (Entry.GetCanDeleteDocuments())
	{
		Error = DelDocFld.SetValue("Yes");
		if (Error)
			return Error;
	}
	else 
	{
		Error = DelDocFld.SetValue("No");
		if (Error)
			return Error;
	}

	Error = AclEntryDoc.CreateItem("DelDoc", DelDocFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText CrePAgFld;
	if (Entry.GetCanCreatePersonalAgents())
	{
		Error = CrePAgFld.SetValue("Yes");
		if (Error)
			return Error;
	}
	else
	{
		Error = CrePAgFld.SetValue("No");
		if (Error)
			return Error;
	}

	Error = AclEntryDoc.CreateItem("CrePAg", CrePAgFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText CrePFVFld;
	if (Entry.GetCanCreatePersonalFolders())
	{
		Error = CrePFVFld.SetValue("Yes");
		if (Error)
			return Error;
	}
	else
	{       
		Error = CrePFVFld.SetValue("No");
		if (Error)
		return Error;
	}

	Error = AclEntryDoc.CreateItem("CrePFV", CrePFVFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText CreSFVFld;
	if (Entry.GetCanCreateSharedFolders())
	{
		Error = CreSFVFld.SetValue("Yes");
		if (Error)
			return Error;
	}
	else
	{
		Error = CreSFVFld.SetValue("No");
		if (Error)
			return Error;
	}

	Error = AclEntryDoc.CreateItem("CreSFV", CreSFVFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText CreLSAFld;
	if (Entry.GetCanCreateLotusScript())
	{
		Error = CreLSAFld.SetValue("Yes");
		if (Error)
			return Error;
	}
	else
	{
		Error = CreLSAFld.SetValue("No");
		if (Error)
			return Error;
	}

	Error = AclEntryDoc.CreateItem("CreLSA", CreLSAFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText ReadDocFld;
	if (Entry.GetCanReadPublicDocuments())
	{
		Error = ReadDocFld.SetValue("Yes");
		if (Error)
			return Error;
	}
	else 
	{
		Error = ReadDocFld.SetValue("No");
		if (Error)
			return Error;
	}

	Error = AclEntryDoc.CreateItem("ReadDoc", ReadDocFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	LNText WriteDocFld;
	if (Entry.GetCanWritePublicDocuments())
	{
		Error = WriteDocFld.SetValue("Yes");
		if (Error)
			return Error;
	}
	else 
	{
		Error = WriteDocFld.SetValue("No");
		if (Error)
			return Error;
	}

	Error = AclEntryDoc.CreateItem("WriteDoc", WriteDocFld, LNITEMFLAGS_SUMMARY);
	if (Error)
		return Error;

	// Save the newly created document to disk but leave it open 
	// for appends to the log entry field.
	Error = AclEntryDoc.Save();
	if (Error)
		return Error;

	return LNNOERROR;
} // END ACLLog::AddACLEntry

//---------------------------------------------------------------------------
//
// Name:
//              ACLLog::CloseLogEntry
//
// Description:
//              Closes the current ACL LogEntry note.
//---------------------------------------------------------------------------
LNSTATUS ACLLog::CloseLogEntry()
{
	LNSTATUS        Error;

	if (! IsDocOpen )
		return LNNOERROR;

	// Close the new document.
	Error = AclEntryDoc.Close();
	if (Error)
		return Error;

	// Reset those flags!
	IsDocOpen = FALSE;

	return LNNOERROR;

} // END ACLLog::CloseLogEntry

//
// END ACLLog class implementation.
//


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
void ProcessArguments ( 
	int				argc,
	char            *argv[],
	LNString        *DatabasePath,
	LNString        *ServerName)
{
	LNBOOL Prompt = FALSE;

	if (argc < 2)
		Prompt = TRUE;  

	// Set up the default parameters first.
	InitDefaultParams();
	*DatabasePath = ParamString1;
	*ServerName = ParamString2;

	if (Prompt)
	{
		// Get user input data by prompting.
		GetArguments();
		*DatabasePath = ParamString1;
		*ServerName = ParamString2;
	}
	else
	{
		// Parse the command line.
		*DatabasePath = argv[1];
		*ServerName = argv[2];
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
//                      You only need to edit this function and ProcessArguments() 
//                      when creating a new sample.  The rest of the user interface 
//                      functions below are called by ProcessArguments() and are 
//                      generic and can stay the same unless you modify the number of
//                      parameters.
//                      
//---------------------------------------------------------------------------
void InitDefaultParams()
{

	// Initialize default parameter strings.
	PromptString1 =  "File path name for the database to iterate ACL Entries: [";
	ParamString1 = "names.nsf";

	PromptString2 =  "Server name for the database: [";
	ParamString2 = "";

} // END InitDefaultParams()

//---------------------------------------------------------------------------
//
// Name:
//              GetArguments
//
// Description:
//              Allows the user to change any or all of the input parameter 
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

			IsCorrectData = TRUE;     // All Done, Get out now!
			break;

		default:

			// Prompt again for anything other than a "Y" or "CARRIAGE RETURN".
			if( (CommandBuf) != (const char *)"" )
				QueryArguments();
			else
				IsCorrectData = TRUE;    // All Done, Get out now!

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

