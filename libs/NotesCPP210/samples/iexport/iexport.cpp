//===========================================================================
//
//      Module: IEXPORT.CPP
//
//      Description:
//              This program illustrates how to import a CGM graph image
//              file to document in a database file.  It then exports all the
//              text from that document of the same database to a text file.
//
//      Syntax: IEXPORT <dbname> [server]
//
//		Note:
//				This sample program is designed to work with the sample 
//				database SAMPLEDB.NSF and the sample "graph.cgm" file.
//
//===========================================================================

#include <iostream.h>
#include <lncppapi.h>

#define IMPORT_FILE_NAME        "graph.cgm"
#define EXPORT_FILE_NAME        "expfile.txt"

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
int				ProgramStatus = 0;
LNNotesSession  Session;

	// Check the command line.

	if (argc < 2 || argc > 3) 
	{
		cout << "\nUsage:\n\t" << argv[0]
			 << " <filename> [<server>] " << endl
			 << endl;

		return(1);
	}

	// Throw all errors encountered during command execution.

	LNSetThrowAllErrors(TRUE);

	try
	{
	char *          DbFilename;
	char *          DbServer = NULL;
	LNDocumentArray	DocArray;
	LNDatabase		Db;

		// Get info from command line.

		DbFilename = argv[1];
		
		if (argc == 3)
			DbServer = argv[2];

		// Initialize the C++ API.

		Session.Init(argc, argv);

		//  Construct default, import, and export file paths.

		char   FilePath[LNMAXPATH];
		char   FileImport[LNMAXPATH], FileExport[LNMAXPATH];

		//  Check the data path length first.

		LNINT   len = (Session.GetDataDirectory()).GetByteLength();

		if ( (len+12) <= LNMAXPATH )
			memcpy(FilePath, Session.GetDataDirectory(), (size_t)len+1);
		else
			throw "Data Directory path too long.";

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

	} // END try

    catch (LNSTATUS lnerror)
    {
    char ErrorBuf[LNERROR_MESSAGE_LENGTH];

        LNGetErrorMessage(lnerror, ErrorBuf, LNERROR_MESSAGE_LENGTH);
        cout << "\nException thrown during execution of main process." << endl;
        cout << "\nError:  " << ErrorBuf << endl;
        ProgramStatus = 3;
    }

    catch (const char *pErrorMessage)
    {
        cout << "\nException thrown during execution of main process." << endl;
        cout << "\nError: " << pErrorMessage << endl << endl;
        ProgramStatus = 2;
    }

    catch (...)
    {
        cout << "\nException thrown during execution of main process." << endl;
        cout << "\nError unknown!" << endl;
        ProgramStatus = 1;
    }

    char CommandBuf[80];
    cout << "All Done.  Hit return to exit: ";
    cin.getline(CommandBuf, 80);

    // Terminate the API.

    Session.Term();

    return (ProgramStatus);

} // END MAIN

// END iexport.cpp


