//===========================================================================
//
//	Module:	    DBTITLE
//
//	Description:
//			This program displays the title of the specified database.
//
//	Syntax:	dbtitle <dbname> [<server>]
//
//===========================================================================

#include <iostream.h>
#include <lncppapi.h>

#define ERR_BUF_SIZE 512

int main(int argc, char *argv[])
{
	char *                  DbFilename;
	char *                  DbServer=NULL;
	LNNotesSession			Session;
	LNDatabase              Db;
	LNString                DbTitle;

	// Check the command line.
	if (argc < 2 || argc > 3)
	{
		cout << "\nUsage:\n\t" << argv[0] << " <filename> [<server>] \n" << endl;
		return (1);
	}

	// Get info from command line.
	DbFilename = argv[1];

	if (argc == 3)
		DbServer = argv[2];

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try
	{
		// Initialize the C++ API
		Session.Init(argc, argv);

		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open sesame.
		Db.Open();

		// Get the database's title.
		DbTitle = Db.GetTitle();

		// Display it.
		cout << "The database title is:  " << DbTitle << endl;
	}

	// Error handler.  If an error occurred, get the text of
	// the error message and display it.
	catch (LNSTATUS Lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(Lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error:  " << ErrorBuf << endl;
	}

	// Close sesame.
	Db.Close();

	// Terminate the API.
	Session.Term();

	// Ciao, baby!
	return (0);
}


