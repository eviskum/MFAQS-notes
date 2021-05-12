//===========================================================================
//
//      Module: MAILSCAN.CPP
//
//      Description:
//              This program scans the mail database for messages with the 
//				specified subject line.  The "From:", "To:", "cc:", and 
//				"Subject:" lines from the message are copied to the file 
//				'mailscan.log', along with the date the message was sent.
//
//      Syntax:     mailscan <subject> [<dbname> [<server>] ]
//
//		Note:
//				The 'mailscan.log' file is created in your current working
//				directory.
//
//===========================================================================

// C++ library headers
#include "iostream.h"
#include "fstream.h"

// Notes C++ API headers
#include "lncppapi.h"

//
// Program constants
//

// Output log file name
char LogFileName [] = "mailscan.log";
#define ERR_BUF_SIZE 512                // Error message string buffer size

//
// Forward declarations
//

// Process the argument list.
void ProcessArguments (
	int		argc,
	char	**argv,
	char 	**NumDocsSubject,
	char 	**NumDocsDatabasePath,
	char 	**NumDocsServerName
);

// Print program usage instructions.
void PrintUsage (void);

// Write a mail message to the log file.
void WriteToLog (
	ofstream 		&LogFile,
	LNMailMessage	*pCurDoc
);


int main ( int argc, char ** argv) 
{
int				ProgramStatus = 0;
char			*Subject;
char			*DatabasePath;
char			*ServerName;
LNNotesSession  Session;
LNDatabase		Db;

	// Parse the argument list.
	try
	{
		ProcessArguments (argc, argv, &Subject, &DatabasePath, &ServerName);
	}
	catch (const char *pErrorMessage)
	{
		cout << "\nError: " << pErrorMessage << endl << endl;
		PrintUsage ();
		return (1);
	}

	// Now for the main processing.
	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors (TRUE);

	try
	{
	LNDocumentArray DocArray;
	LNString		SearchFormula;
	ofstream		LogFile (LogFileName, ios::out | ios::app);	// Create,open log file.
	LNINT			Index;
	LNINT			NumDocs;

		if (!LogFile)
			throw "Cannot open log file";

		// Initialize the API.
		if (Session.Init (argc, argv))
			throw "Unable to initialize the API";

		if (((char *) NULL) == DatabasePath)
		{
			// No database specified; get user's mail database.
			Session.GetMailDatabase (&Db);
		}
		else
		{
			// Get the specified database.
			Session.GetDatabase(DatabasePath, &Db, ServerName);
		}

		// Open the database.
		Db.Open();

		// Put a header in the log file.
		LogFile << "------------------------" << endl;
		LogFile << "------------------------" << endl;
		LogFile << "    MailScan Log" << endl;
		if (((char *) NULL) == DatabasePath)
		{
			cout << "Scanning mail file for "
				<< ((const char *) Session.GetUserName ()) << endl;
			LogFile << "Scanning mail file for "
				<< ((const char *) Session.GetUserName ()) << endl;
		}
		else
		{
			cout << "Scanning database:  " << DatabasePath << endl;
			LogFile << "Scanning database:  " << DatabasePath << endl;
		}

		//
		//      Search for documents with "Subject" or "Re: Subject".
		//

		// Build the search formula.
		SearchFormula = "(Subject = \"";
		SearchFormula += Subject;
		SearchFormula += "\") | (Subject = \"Re: ";
		SearchFormula += Subject;
		SearchFormula += "\")";

		LogFile << "Search Formula:  "
			<< ((const char *) SearchFormula) << endl;
		Db.Search (SearchFormula, &DocArray);

		NumDocs = DocArray.GetCount ();
		cout << "Document Count:  " << NumDocs << endl;
		LogFile << "Document Count:  " << NumDocs << endl;
		LogFile << "------------------------" << endl;

		for (Index = 0; Index < DocArray.GetCount (); Index++)
		{
		LNMailMessage   CurDoc;
		LNMailMessage   ReplyDoc;

			// Get the next message in the search result.
			CurDoc = DocArray[Index];

			// Write the mail message to the log file.
			WriteToLog (LogFile, &CurDoc);
		}

		LogFile << "------------------------" << endl;
		LogFile << "    End of Mail Scan" << endl;
		LogFile << "------------------------" << endl << endl;

		cout<< endl << "End of Mail Scan. Data has been entered in mailscan.log" << endl;

		ProgramStatus = 0;
	}
	catch (LNSTATUS lnerror)
	{
	char ErrorBuf[ERR_BUF_SIZE];

		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "\nError:  " << ErrorBuf << endl;
		ProgramStatus = 2;
	}
	catch (const char *ErrorMessage)
	{
		cout << "\nError: " << ErrorMessage << endl << endl;
		ProgramStatus = 1;
	}

	// Close the mail database.
	Db.Close();

	// Terminate the API.
	Session.Term();

	return (ProgramStatus);
}


//---------------------------------------------------------------------------
//
//      WriteToLog
//
//      Write a mail message header to the log file.
//
//---------------------------------------------------------------------------

void WriteToLog (ofstream &LogFile,	LNMailMessage *pCurDoc) 
{
LNString	Data;
LNText		TextData;
LNDatetime	Sent;
LNINT		Count;
LNINT		Index;

	pCurDoc->Open (LNNOTEOPENFLAGS_MARK_READ);

	LogFile << "--------" << endl;

	// Read and print the message header information.
	pCurDoc->GetSender (&Data);
	LogFile << "From:    " << ((const char *) Data) << endl;

	pCurDoc->GetRecipients (&TextData);
	Count = TextData.GetCount ();
	LogFile << "To:      ";
	for (Index = 0; Index < Count; Index++)
	{
		Data = (LNString) TextData[Index];
		if (Index > 0)
			LogFile << ", ";
		LogFile << ((const char *) Data);
	}
	LogFile << endl;

	pCurDoc->GetCC (&TextData);
	Count = TextData.GetCount ();
	LogFile << "cc:      ";
	for (Index = 0; Index < Count; Index++)
	{
		Data = (LNString) TextData[Index];
		if (Index > 0)
			LogFile << ", ";
		LogFile << ((const char *) Data);
	}
	LogFile << endl;

	pCurDoc->GetSubject (&TextData);
	Count = TextData.GetCount ();
	LogFile << "Subject: ";
	for (Index = 0; Index < Count; Index++)
	{
		Data = (LNString) TextData[Index];
		if (Index > 0)
			LogFile << ", ";
		LogFile << ((const char *) Data);
	}
	LogFile << endl;

	// Make sure this message is sent first (i.e., not a draft).
	// Then log the date sent info.
	if ( pCurDoc->GetDateSent (&Sent) == LNWARN_NOT_FOUND )
		LogFile << "Date:    Message not sent yet. (i.e. a draft) " << endl << endl;
	else
		LogFile << "Date:    "
				<< Sent.GetMonth () 
				<< "/" << Sent.GetDay ()
				<< "/" << Sent.GetYear ()
				<< " "
				<< Sent.GetHour ()
				<< ":" << Sent.GetMinute()
				<< ":" << Sent.GetSecond ()
				<< endl << endl;

	pCurDoc->Close ();
}

//---------------------------------------------------------------------------
//
//       ProcessArguments
//
//      Scan the input command line and sort out the input strings.
//      If no arguments were supplied, prompt for them.
//
//      Throws exceptions:
//              char *          Argument error description
//
//---------------------------------------------------------------------------

void ProcessArguments (
	int		argc,
	char	**argv,
	char	**Subject,
	char	**DatabasePath,
	char	**ServerName ) 
{
int	curParam = 0;
int index;

	// Set the default values for the arguments (that is, NULL!).
	*Subject = NULL;              // The logic of the main program depends
	*DatabasePath = NULL;         // on these pointers being set to NULL if
	*ServerName = NULL;           // no user input is supplied!

	// Check argument count
	if (argc < 2)
		throw "No subject provided";
	if (argc > 4)
		throw "Too many arguments";

		// Scan the argument list, item by item.
	for (index = 1; index < argc; index++)
	{
		// Check for option switches.
		if (('-' == ((argv[index])[0])) || ('/' == ((argv[index])[0])))
		{
			throw "Unknown switch";
		}
		else
		{
			// String argument - assign to 
			switch (curParam)
			{
				case 0:
					*Subject = argv[index];
					break;

				case 1:
					*DatabasePath = argv[index];
					break;

				case 2:
					*ServerName = argv[index];
					break;

				default:
					throw "More than 3 arguments";
			}
			curParam++;
		}
	}

	if (((char *) NULL) == (*Subject))
		throw "No subject provided";

	return;
}

//---------------------------------------------------------------------------
//
//      PrintUsage
//
//      Print program usage instructions.
//---------------------------------------------------------------------------

void PrintUsage (void)
{
	cout << "Usage:" << endl;
	cout << "\tmailscan subject [database [server]] "
		<< endl << endl;
	cout << "where:" << endl;
	cout << "\tsubject   Message subject to search for" << endl;
	cout << "\tdatabase  Optional pathname of database" << endl;
	cout << "\tserver    Optional server name" << endl;
}


