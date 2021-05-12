//===========================================================================
//
//	Module:	    DBTITLE
//
//	Description:
//				This program displays the title of the specified database.
//
//	Syntax:     dbtitle <dbname> [<server>]
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

#define ERR_BUF_SIZE 512

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

int main(int argc, char *argv[])
{
	char *                  DbFilename;
	char *                  DbServer=NULL;
	LNNotesSession			Session;
	LNDatabase              Db;
	LNString                DbTitle;

#if defined MAC
	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line.

	char		FileBuffer[MAXPATH];
	char		ServerBuffer[MAXPATH];
	
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
    
	// Prompt for file and server names.
    DbFilename = FileBuffer;
	DbServer = ServerBuffer;
	
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
		cout << "\nUsage:\n\t" << argv[0] << " <filename> [<server>] \n" << endl;
		return (1);
	}

	// Get info from command line.
	DbFilename = argv[1];

	if (argc == 3)
		DbServer = argv[2];

#endif


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
