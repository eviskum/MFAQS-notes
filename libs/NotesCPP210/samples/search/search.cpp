//===========================================================================
//
//
//    Program:  SEARCH
//
//    File:		SEARCH.CPP
//
//    Syntax:	search <srcdb> <destdb> <cutoffbegin> <cutoffend>
//
//    Description:
//			  	This program copies all documents from the specified source 
//				database to the specified destination database that were 
//				created within the specified cutoff dates.
//
//				For example, the sample databases search1.nsf and search2.nsf 
//				may be copied to the user's Notes data directory.  The 
//				command line for search using these sample databases is:
//					search search1 search2 1/1/86 1/1/96
//
//===========================================================================

#include <iostream.h>

#include <lncppapi.h>

#define ERR_BUF_SIZE 512

int main(int argc, char *argv[])
{
	char *			SrcDbFilename;
	char *			DestDbFilename;
	char *			BeginCutoff;
	char *			EndCutoff;
	LNINT			Count;
	LNINT			i;
	LNNotesSession  Session;
	LNDatabase		SrcDb;
	LNDatabase		DestDb;
	LNDocumentArray Docs;
	LNDocument		Doc;
	LNDocument		NewDoc;
	LNString		SearchFormula;
	LNSearchOptions SearchOptions;

	// Check the command line.
	if (argc != 5)
	{
		cout << "\nUsage:\n\t" << argv[0]
		     << " <source database> <destination database> <begin date> <end date> \n"
			 << endl;
		return(1);
	}

	// Get info from command line.
	SrcDbFilename = argv[1];
	DestDbFilename = argv[2];
	BeginCutoff = argv[3];
	EndCutoff = argv[4];

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try
	{
		// Initialize the C++ API.
		Session.Init(argc, argv);

		// This sample assumes that both the source and destination databases
		// are on the local machine.  If the databases are on a remote server,
		// the server name should also be passed to Session.GetDatabase().

		cout << "Copying notes from " << SrcDbFilename << " to "
			<< DestDbFilename << endl;

		// Get the source database.
		Session.GetDatabase(SrcDbFilename, &SrcDb);

		// Get the destination database.
		Session.GetDatabase(DestDbFilename, &DestDb);

		// Open the source database.
		SrcDb.Open();

		// Open the destination database.
		DestDb.Open();

		// Set up the search formula.
		SearchFormula = "@All";

		// Set up the search options.
		SearchOptions.SetBeginDate(BeginCutoff);
		SearchOptions.SetEndDate(EndCutoff);
		SearchOptions.SetMaxNotes(100);
		
		// Get an array of all documents in the source database that
		// match the search formula and the search options.
		SrcDb.Search(SearchFormula, &Docs, &SearchOptions);

		// Iterate through the array copying each of the documents found
		// into the destination database.
		Count = Docs.GetCount();

		cout << "Number of documents found: " << Count << endl;

		for (i=0; i<Count; i++)
		{
			// Get the next document.
			Doc = Docs[i];

			// Open it.
			Doc.Open();

			// Make an in-memory copy of it in the destination database.
			DestDb.CreateDocument(Doc, &NewDoc);

			// Save the copy.
			NewDoc.Save();

			// Close the copy.
			NewDoc.Close();

			// Close the document.
			Doc.Close();
		}
	}

	// Error handler.  If an error occurred, get the text of
	// the error message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		ErrorBuf[0] = '\0';
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error:  " << ErrorBuf << endl;
	}
	
	// Close the destination database.
	DestDb.Close();

	// Close the source database.
	SrcDb.Close();

	// Clean up and exit because we're done.
	Session.Term();

	// Adios amigo!
	return(0);
}
