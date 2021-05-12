//===========================================================================
//
//      Module: VIEWNAV.CPP
//
//      Description:
//              This program illustrates how to navigate a view.
//
//      Syntax: VIEWNAV <dbname> [server]
//                      dbname = VIEW.NSF
//
//===========================================================================

#include <iostream.h>
#include <lncppapi.h>

#define ERR_BUF_SIZE 512

int main(int argc, char *argv[])
{
	char *			DbFilename;
	char *			DbServer = NULL;
	LNNotesSession	Session;
	LNSTATUS		Status = LNNOERROR;

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

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	
	LNDatabase	Db;

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try 
	{
		LNINT			i, Count = 0;
		LNDocumentArray	DocArray;
		LNViewFolder	View;

		// Initialize the C++ API.
		Session.Init(argc, argv);

		//Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		//Open the database.
		Db.Open();

		//Get the AllDocuments view.
		Db.GetViewFolder("($All)", &View);

		//Open the view.
		View.Open();

		//Find the entry count in the view.
		LNINT Entries = View.GetEntryCount();

		//Let's loop through all the documents in this view.
		for (i = 0; i < Entries; i++)
		{
			LNDocument      Doc;
			LNINT           IndentLevels = 0;

			//Navigate through view using subscript operator in LNViewFolder.
			LNVFEntry       Entry = View[i];

			//Get the LNDocument associated with the view entry.
			Entry.GetDocument(&Doc);

			//Open the document.
			Doc.Open();

			LNText Item;
			if (Doc.HasItem("Subject"))
			{
				Doc.GetItem("Subject", &Item);
				LNString Name = Item[0];

				//Get the indent level of each document.
				IndentLevels = Entry.GetIndentLevels();

				//Output the Subject item contents and tab the 
				//output based on the indent level. We know that
				//the deepest indent level in our database is no
				//more than three.
				switch (IndentLevels)
				{
				case 0:
					cout << "Subject: " << Name << endl;    
					break;
				case 1:
					cout << "	Subject: " << Name << endl;   
					break;
				case 2:
					cout << "		Subject: " << Name << endl;  
					break;
				case 3:
					cout << "			Subject: " << Name << endl; 
					break;
				default:
					break;
				}
			}

			// Close the document, free item memory.
			Doc.Close();
		}

		//Close the view.
		View.Close();
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

	//Terminate the API.
	Session.Term();
	
	char    CommandBuf[10];

	cout << endl;
	cout << "Hit Return To Exit: ";
	cin.getline(CommandBuf, 10);

	//All done.
	return(0);
}


