//===========================================================================
//
//      Module: IEXPORT.CPP
//
//      Description:
//              This program illustrates how to import a Microsoft Rich Text
//              file to document in a database file.  It then exports all the
//              text from that document of the same database to a text file.
//
//      Syntax: IEXPORT <dbname> [server]
//
//		Note:
//				This sample program is designed to work with the sample 
//				database SAMPLEDB.NSF and the sample "impfile.rtf" file.
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
#define IMPORT_FILE_NAME        "impfile.rtf"
#define EXPORT_FILE_NAME        "expfile.txt"


int main(int argc, char *argv[])
{
	char *          DbFilename;
	char *          DbServer = NULL;
	LNNotesSession  Session;
	LNSTATUS        Status = LNNOERROR;

#if defined MAC
	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line.

	char   fileBuffer[MAXPATH];
	char   serverBuffer[MAXPATH];
	
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

		
	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try
	{
		LNDocumentArray	DocArray;
		LNDatabase		Db;

		// Initialize the C++ API.
		Session.Init(argc, argv);

		//  Construct default, import, and export file paths.
		char   FilePath[LNMAXPATH];
		char   FileImport[LNMAXPATH], FileExport[LNMAXPATH];

		//  Check the data path length first.

		LNINT   len = (Session.GetDataDirectory()).GetByteLength();


		if ( (len+12) <= LNMAXPATH )
		{
			memcpy(FilePath,
				   Session.GetDataDirectory(), (size_t)len+1);
		}
		else
		{
			cout << "Data Directory path too long." << endl;
			goto Term;
		}


#if defined(DOS) || defined(OS2) || defined(NT)  
		strcat(FilePath, "\\");
#elif defined(UNIX)
		strcat(FilePath, "/");
#endif
		strcpy (FileImport, FilePath);
		strcat (FileImport, IMPORT_FILE_NAME);
		strcpy (FileExport, FilePath);
		strcat (FileExport, EXPORT_FILE_NAME);


		//  Get the specified database and open it to gets the documents.

		Session.GetDatabase(DbFilename, &Db, DbServer);

		Db.Open();

		Db.GetDocuments(&DocArray);

		LNDocument      Doc; 
		LNRichText      Rt;
		LNRTCursor      Cursor, StartCursor, EndCursor;
		
		//  Get the first document in the database & open it.
		
		Doc = DocArray[0];
		Doc.Open();

		
		if ( Doc.HasItem("Body") )
		{
			//  Get the item named "Body" and a cursor pointing
			//  at the first element in the rich text.
			
			Doc.GetItem("Body",&Rt);

			Rt.GetCursor(&Cursor);

			//  Importing the provided file into rich text at the giving cursor
			//  position.

			Rt.Import(FileImport, &Cursor);
			cout << FileImport << " is imported to rich text" << endl;

			Doc.Save();

			
			//  Get two cursors from rich text, one points to the first element
			//  and the other points to the last element of this rich text.  Thus,
			//  everything in rich text will be exported to the file.

			Rt.GetCursor(&StartCursor);
			Rt.GetEndCursor(&EndCursor);

			Rt.Export(FileExport, StartCursor, EndCursor);
			cout << "Rich text is exported to " << FileExport << endl;
			
			
			// Close the document, free item memory.
			Doc.Close();
		}

		// Close the database, free document memory.
		if (Db.IsOpen())
			Db.Close(); 

	}

	//  Error handler.  If an error occurred, get the text of the error
	//  message and display it.
	
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}
  
Term:
	//Terminate the API.
	Session.Term();

	char    CommandBuf[10];

	cout << endl;   
	cout << "All Done. Hit return to exit: ";
	cin.getline(CommandBuf, 10);

	//All done.
	return(0);
}
