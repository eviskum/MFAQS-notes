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
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#include <iostream.h>

#include <lncppapi.h>

#if defined(MAC)
	// These headers are only needed for Macintosh applications.
#include <Types.h>
#include <Quickdraw.h>
#define thePort qd.thePort
#include <Dialogs.h>
#include <Menus.h>
#include <Windows.h>
#include <Fonts.h>
#include <Memory.h>
#include <stdio.h>
#endif

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

#if defined MAC
		// On the Macintosh, we need to prompt for parameters
		// since they are not being passed in on the command line.

	char			sourceFile[MAXPATH];
	char			destFile[MAXPATH];
	char			begCut[MAXPATH];
	char			endCut[MAXPATH];
	
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
	
	SrcDbFilename = sourceFile;
	DestDbFilename = destFile;
	BeginCutoff = begCut;
	EndCutoff = endCut;
	
	// Prompt for parameters since they are not being passed in on the command line.
	cout << endl << "Enter source filename: " << flush;
	gets(SrcDbFilename);
	cout << "Enter destination filename:  " << flush;
	gets(DestDbFilename);
	cout << "Enter beginning cutoff:  " << flush;
	gets(BeginCutoff);
	cout << "Enter ending cutoff:  " << flush;
	gets(EndCutoff);
#else
		// On anything other than the Macintosh, the parameters
		// are entered on the command line.

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

#endif

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
