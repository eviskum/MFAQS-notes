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

#include <iostream.h>

#include <lncppapi.h>

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


