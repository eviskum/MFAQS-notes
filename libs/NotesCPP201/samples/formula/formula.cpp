//===========================================================================
//
//      Module: FORMULA.CPP
//
//      Description:
//              This program illustrates how to create a formula and 
//              run the formula against the documents in a database via 
//              the C++ LNFormula class.
//
//      Syntax: FORMULA <dbname> [server]
//                      dbname = VIEW.NSF
//
//===========================================================================
//
// Copyright (c) 1997, 1998 Lotus Development Corporation. All rights reserved.
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
	char *					DbFilename;
	char *                  DbServer = NULL;
	LNNotesSession			Session;
	LNSTATUS                Lnstat = LNNOERROR;

#if defined MAC
	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line.

	char			FileBuffer[MAXPATH];
	char			ServerBuffer[MAXPATH];
	
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
    
    DbFilename = FileBuffer;
	DbServer = ServerBuffer;
	
	// Prompt for parameters since they are not being passed in on the command line.
	cout << endl << "Enter database filename: " << flush;
    gets(DbFilename);
    cout << "Enter server name:  " << flush;
    gets(DbServer);
#else
	// On anything other than the Macintosh, the parameters
	// are entered on the command line.

	// Check the command line.
	if (argc < 2 || argc > 3) 
	{
		cout << "\nUsage:\n\t" << argv[0]
			<< " <filename> [<server>] \n"
			<< endl;
		return(1); 
	}

	// Get info from command line.
	DbFilename = argv[1];
	
	if (argc == 3)
		DbServer = argv[2];
#endif


	// Initialize the C++ API.
	if (Session.Init(argc, argv))
	{
		cout << "\nUnable to initialize the API" << endl;
		return(2);
	}
	
	LNSetThrowAllErrors(TRUE);
	
	LNDatabase      Db;

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try 
	{
		LNINT           Index, Count = 0;
		LNDocumentArray DocArray;

		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open it.
		Db.Open();
		Db.GetDocuments(&DocArray);

		// Create an LNFormula object.
		LNFormula formula;

		// The contents of the formula.
		const char *szFormula = 
			"FIELD Subject := @LeftBack(Subject; \"Event\") + \"Holiday\" + \
			@RightBack(Subject; \"Event\");SELECT @All";

		// Change the value of this LNFormula to the specified formula text.
		Lnstat = formula.SetText(szFormula);
		if (Lnstat)
			throw Lnstat;

		// Echo back the formula contents.
		cout << "Formula: " << formula.GetText() << endl;     

		// How many documents do we have?
		Count = DocArray.GetCount();

		// Loop through each document in the array.
		for (Index = 0; Index < Count; Index++)
		{
			LNDocument      Doc; 

			// Get the current document.
			Doc = DocArray[Index];

			// Open the document.
			Doc.Open();

			// We want to use the formula to replace the Subject item 
			// contents for the main topic documents.
			if (!Doc.IsResponse())
			{
				LNItem Result;

				// We don't care about the result, just compute 
				// the formula against the main topic document.
				Lnstat = formula.Evaluate(&Result, Doc);
				if (Lnstat)
					throw Lnstat;

				// Save the document changes.
				Doc.Save();
			}

			// Close the document, free item memory.
			Doc.Close();
		}

	}

	// Error handler.  If an error occurred, get the text of the error
	// message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}

	// Close the database, free document memory.
	if (Db.IsOpen())
		Db.Close(); 
	  
	// Terminate the API.
	Session.Term();

	char    CommandBuf[10];

	cout << endl;   
	cout << "All Done. Hit return to exit: ";
	cin.getline(CommandBuf, 10);

	// All done.
	return(0);
}


