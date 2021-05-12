//===========================================================================
//
//
//
//	Program:        ITEMSAMP
//
//	File:           ITEMSAMP.CPP
//
//	Description:
//
//		This program displays the name and size of all the items
//		in all the notes in the specified database.
//
//	Syntax:         itemsamp <dbname> [<server>]
//
//	
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This	software is	subject	to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable	export regulations.
//
//===========================================================================


#include <iostream.h>

#include <lncppapi.h>

#if defined(MAC)

// These headers are only needed on the Macintosh.
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
	char *			DbFilename;
	char *			DbServer = NULL;
	LNNotesSession  Session;
	LNDatabase		Db;
	LNDocumentArray Docs;       
	LNDocument		Doc;
	LNItemArray		Items;
	LNItem			Item;
	LNINT			NumDocs, NumItems, i, j;


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

	if (argc == 3 )
		DbServer = argv[2];

#endif

		
	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);
	
	try
	{
		// Initialize the C++ API.
		if (Session.Init(argc, argv))
		{
			cout << "\nUnable to initialize the API" << endl;
			return(2);
		}

		// Get the database.
		Session.GetDatabase(DbFilename, &Db, DbServer);
		
		// Open it.
		Db.Open();
		
		// Get an array of all the documents in the database.
		Db.GetDocuments(&Docs);
		
		// Get the number of documents in the array.
		NumDocs = Docs.GetCount();
		
		// Loop over the documents.
		for (i=0; i<NumDocs; i++)
		{
			// Get a document.
			Doc = Docs[i];

			// Open it.
			Doc.Open();
						
			// Display its index in the document array.
			cout << "\n\nDocument Number = " << i << endl;

			// Get an array of items in the document; use default function args.
			Doc.GetItems(&Items);
			
			// Get the number of items in the document.
			NumItems = Items.GetCount();
			
			// Loop over the items.
			for (j=0; j<NumItems; j++)
			{
				// Get an item from the array.
				Item = Items[j];

				// Display its index in the item array.
				cout << "\nItem Number = " << j << "   " << endl;

				// Display its name.
				cout << "Name = " << Item.GetName() << "   " << endl;

				// Display its size.
				cout << "Size = " << Item.GetValueSize() << endl;
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
		ErrorBuf[0] = '\0';
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}
		
	// Close the database, free document memory.
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
		
