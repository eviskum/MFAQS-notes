//===========================================================================
//
//      Module: RTSEARCH.CPP
//
//      Description:
//              This program illustrates how to search for and replace a 
//              text string in a rich text item.
//
//      Syntax: RTSEARCH <dbname> [server]
//
//		Note: 
//				This sample program is designed to work with the sample 
//				database RTSEARCH.NSF in the notescpp\notedata directory.  
//
//===========================================================================
//
// Copyright (c) 1997,1998 Lotus Development Corporation. All rights reserved.
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

char CommandBuf[80];

int main(int argc, char *argv[])
{
	char *			DbFilename;
	char *			DbServer = NULL;
	LNNotesSession	Session;
	LNSTATUS		lnstatus = LNNOERROR;

#if defined MAC
	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line.

	char			fileBuffer[MAXPATH];
	char			serverBuffer[MAXPATH];
	
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
   
	DbFilename = fileBuffer;
	DbServer = serverBuffer;
	
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

	LNSetThrowAllErrors(TRUE);

	
	LNDatabase                      Db;

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try 
	{
		LNDocument		Doc; 
		LNRichText		BodyItem; 
		LNRTCursor		StartCursor;
		LNINT			i, Count = 0;
		LNDocumentArray DocArray;


		// Initialize the C++ API.
		Session.Init(argc, argv);
	
		//Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		//Open it.
		Db.Open();

		//Get all the documents in the database.
		Db.GetDocuments(&DocArray);

		//How many documents do we have?
		Count = DocArray.GetCount();

		//Loop through each document in the array.
		for (i=0; i<Count; i++) 
		{
			//Get the current document.
			Doc = DocArray[i];

			//Open the document.
			Doc.Open();

			//Get the rich text item named "Body".
			Doc.GetItem("Body", &BodyItem);   

			//Get a cursor pointing at the first element in the rich text.
			BodyItem.GetCursor(&StartCursor);

			//Find the first text in the rich text.
			lnstatus = StartCursor.GotoFirst("Cplusplus");
			if (lnstatus)
				throw lnstatus;

			//Loop through the end of the document.
			while (lnstatus != LNWARN_NOT_FOUND) 
			{
				//Delete the original text string.
				BodyItem.Delete( &StartCursor, 9);

				//Replace the text string with the new one.
				BodyItem.Insert("C++", &StartCursor);

				//Go find the next string occurrence.
				lnstatus = StartCursor.GotoNext("Cplusplus");
			}

			//Now update it.
			Doc.Save();

			// Close the document, free item memory.
			Doc.Close();                                     
		}
	}

	//Error handler.  If an error occurred, get the text of the error
	//message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		ErrorBuf[0] = '\0';
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}
		
	//Close the database, free document memory.
	if (Db.IsOpen())
		Db.Close(); 

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);
	
	//Terminate the API.
	Session.Term();
	
	//All done.
	return(0);
}
