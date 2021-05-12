//===========================================================================
//
//
//	Program:    ViewFldr
//
//	File:       VIEWFLDR.CPP
//
//	Syntax:     ViewFldr <filename> [<servername>]
//				where <filename> is the name of the new database to be created
//
//	Description:
//				This program demonstrates new ViewFolder features.
//				
//				This sample program is designed to work with the sample 
//				source database 'view.nsf'. 
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#include <iostream.h>
#include <lncppapi.h>

#define ERR_BUF_SIZE 512


#if defined(MAC)
	// These headers are only needed for Macintosh applications
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


int main(int argc, char *argv[])
{
	LNNotesSession	Session;
	LNDatabase 		Db;
	char 			*DbFileName;
	char 			*ServerName = NULL;
	LNDocument 		MyDocument;
	char 			Response[10];
	LNSTATUS		Status;
	LNCreateDatabaseOptions Opts;

#if defined MAC
	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line
	char FileBuffer[MAXPATH];
	char ServerBuffer[MAXPATH];

	// Initialize the Macintosh toolbox
	InitGraf(&thePort); 
	InitFonts();
	InitWindows(); 
	InitDialogs(0);
	SetApplLimit(GetApplLimit()-8192); 
	MaxApplZone();
	MoreMasters(); 
	MoreMasters(); 
	MoreMasters();	
	DbFileName = FileBuffer;
	ServerName = ServerBuffer;
	
	// Prompt for parameters since they are not being passed in on the command line.
	cout << endl << "Enter new database filename: " << flush;
	gets(DbFileName);
	cout << "Enter server name:  " << flush;
	gets(ServerName);
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

	// Get info from the command line.
	DbFileName = argv[1];
	if (argc == 3)
		ServerName = argv[2];
	
#endif


	// Set the error handler to throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try
	{
		LNViewFolder Folder;

		// Initialize the C++ API.
		Session.Init(argc, argv);

		// We'll use a copy of the View.nsf database
		// without the documents
		Opts.SetCopyDesignOnly(TRUE);


		// Check if the specified db already exists by trying to open it
		Session.GetDatabase(DbFileName, &Db);

		LNSetThrowAllErrors(FALSE);	// Don't throw error from LNDatabase::Open
		Status = Db.Open();

		if (Status == 0)			// If no error, database already exists
		{
			Db.Close();
			cout << "Database '" << DbFileName << "' already exists, delete it? [Y]  ";
			cin.getline(Response, 10);
			if (Response[0] == 'Y' || Response[0] =='y' || Response[0] == 0)
			{
				// need to explicitly test for failure
				if (Session.DeleteDatabase(DbFileName))
				{
					cout << "Could not delete the database - ending program\n"<< endl;
					goto Term;
				}
			}
			else
			{
				cout << "Please re-start with a new target database name\n" << endl;
				goto Term;
			}
		}
		// re-set this now that we are done with testing for db existence
		LNSetThrowAllErrors(TRUE);

		// Now we know that database does not exist
		// Create a copy of the view.nsf database
		Session.CreateDatabaseCopy("view.nsf", "", DbFileName, ServerName,
									Opts, &Db);
 
		Db.CreateDocument(&MyDocument, "Main Topic");

		// Set the subject line, store as LNText for call to CreateItem
		LNString MySubjectString("This is the subject");
		LNText MySubjectText;
		MySubjectText << MySubjectString;

		MyDocument.CreateItem("Subject", MySubjectText, LNITEMFLAGS_SUMMARY, 
							  LNITEMOPTION_DELETE_APPEND);

		// Set the From information
		LNText FromText;
		FromText.SetValue("CPP API User"); // another way to create an LNText object

		MyDocument.CreateItem("From", FromText, LNITEMFLAGS_SUMMARY, LNITEMOPTION_DELETE_APPEND);
		MyDocument.Save();


		Db.CreateFolder("The Empty Folder", &Folder);

		// Rename the folder something more appropriate
		Folder.SetName("My New Folder");

		// Add the document to the newly created folder
		Folder.FolderAddDocument(MyDocument);

		// Color the background
		Folder.SetBackgroundColor(LNCOLOR_YELLOW);

		// Change the heading display
		Folder.SetHeadingDisplay(LNVFHEADINGDISPLAY_BEVELED);

		Folder.Save();
		Folder.Close();

		Db.Close();

		
	}

	// Error handler.  If an error occurred then get the text of
	// the error message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		// ErrorBuf[0] = '\0';
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error:  " << ErrorBuf << endl;
	}

	cout << "All done - press Enter to continue";
	cin.getline(Response,10);

Term:
	// Terminate the API.
	Session.Term();

	return (0);
}
