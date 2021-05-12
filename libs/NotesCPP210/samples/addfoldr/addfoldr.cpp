//===========================================================================
//
//      Module: ADDFOLDR.CPP
//
//      Description:
//              This program illustrates how to create new folders and move
//              existing documents in the database into the new folders.
//
//      Syntax: ADDFOLDR <dbname> [server]
//                      dbname = VIEW.NSF
//
//===========================================================================

#include <iostream.h>
#include <lncppapi.h>

#define ERR_BUF_SIZE 512

enum Quarter 
{
	FirstQuarter    = 1,
	SecondQuarter   = 2,
	ThirdQuarter    = 3,
	FourthQuarter   = 4,
	UnknownQuarter  = 5
};

static Quarter GetQuarter(const LNString& MonthString);

int main(int argc, char *argv[])
{
	char			*DbFilename;
	char			*DbServer = NULL;
	LNNotesSession	Session;
	LNSTATUS		Lnstatus = LNNOERROR;

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

	// Initialize the C++ API.
	if (Session.Init(argc, argv))
	{
		cout << "\nUnable to initialize the API" << endl;
		return(2);
	}

	LNSetThrowAllErrors(TRUE);

	// Begin TRY Block. 
	// Throw all errors encountered during command execution.
	try 
	{
		LNINT Count;
		LNDatabase Db;
		LNDocumentArray DocArray;
		LNViewFolder Folder1, Folder2, Folder3, Folder4, TempFolder;

		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open it.
		Db.Open();

		Db.GetViewFolder("NewFolder", &TempFolder);

		// Create new folders for each quarter and save them.
		
		Db.CreateFolder("1stQuarter",LNVFSHARING_SHARED,TempFolder,&Folder1);
		Folder1.Save();

		Db.CreateFolder("2ndQuarter",LNVFSHARING_SHARED,TempFolder,&Folder2);
		Folder2.Save();

		Db.CreateFolder("3rdQuarter",LNVFSHARING_SHARED,TempFolder,&Folder3);
		Folder3.Save();

		Db.CreateFolder("4thQuarter",LNVFSHARING_SHARED,TempFolder,&Folder4);
		Folder4.Save();

		// Get all the documents in the database.
		Db.GetDocuments(&DocArray);

		// How many documents do we have?
		Count = DocArray.GetCount();

		// Loop through each document in the array.
		for (LNINT Index = 0; Index < Count; Index++) 
		{
			LNDocument Doc; 

			// Get the current document.
			Doc = DocArray[Index];

			// Open the document.
			Doc.Open();

			// Make sure the document is a parent document!
			if (!Doc.IsResponse())
			{
				LNText Item;

				if (Doc.HasItem("Subject"))
				{
					// Get the Subject item contents first.
					Doc.GetItem("Subject", &Item);
					LNString MonthString = Item[0];
				
					// Return the category based on the Subject item contents.
					Quarter CurQuarter = GetQuarter(MonthString);

					// Adding the parent documents; the responses go along
					// for the ride.
					switch (CurQuarter)                                
					{
					case FirstQuarter:
						Folder1.FolderAddDocument(Doc);
						break;                          
					case SecondQuarter:
						Folder2.FolderAddDocument(Doc);
						break;                          
					case ThirdQuarter:
						Folder3.FolderAddDocument(Doc);
						break;                          
					case FourthQuarter:
						Folder4.FolderAddDocument(Doc);
						break;                          
					case UnknownQuarter:
						break;
					}

					cout << "Subject: " << MonthString << endl;    
				}

			} // END if (parent doc)

			// Close the document, free item memory.
			Doc.Close();

		} // END for (doc array loop)

		// Close the database.
		Db.Close();

	} // END try

	//Error handler.  If an error occurred, get the text of the error
	//message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}

	//Terminate the API.
	Session.Term();

	//All done.
	return(0);
}


static Quarter GetQuarter(const LNString& MonthString)
{
	if (LNStringCompare("January Event", MonthString) == 0 ||
		LNStringCompare("February Event", MonthString) == 0 ||
		LNStringCompare("March Event", MonthString) == 0)
	{
		return FirstQuarter;
	}
	else if (LNStringCompare("April Event", MonthString) == 0 ||
		LNStringCompare("May Event", MonthString) == 0 ||
		LNStringCompare("June Event", MonthString) == 0)
	{
		return SecondQuarter;
	}
	else if (LNStringCompare("July Event", MonthString) == 0 ||
		LNStringCompare("August Event", MonthString) == 0 ||
		LNStringCompare("September Event", MonthString) == 0)
	{
		return ThirdQuarter;
	}
	else if (LNStringCompare("October Event", MonthString) == 0 ||
		LNStringCompare("November Event", MonthString) == 0 ||
		LNStringCompare("December Event", MonthString) == 0)
	{
		return FourthQuarter;
	}
	else
		return UnknownQuarter;
}


