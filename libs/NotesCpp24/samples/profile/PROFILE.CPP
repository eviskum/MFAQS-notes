/****************************************************************************

	Program:    PROFILE

	File:       PROFILE.CPP

	Syntax:     profile <dbname> [<server>]

	Description:
		This program loops through all the profile documents in a database 
		prints out their name and owner. If the profile document is a calendar
		profile it also tells you whether alarm notification is enabled.

****************************************************************************/

#include <iostream.h>

#include <lncppapi.h>

#define ERR_BUF_SIZE 512

char CommandBuf[80];

int main(int argc, char *argv[])
{
		char *          DbServerName=NULL;
		char *          DbFilename=NULL;
		LNNotesSession  Session;
		LNDatabase      Db;
		LNINT			Index, Count = 0;
		

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
		DbServerName = argv[2];


	// Initialize the C++ API.
	if (Session.Init(argc, argv))
	{
		cout << "\nUnable to initialize the API" << endl;
		return (2);
	}

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);
	
	try
	{
		LNProfileDocumentArray docs;
		LNCalendarProfileDocument calend;
		LNProfileDocument profile;



		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServerName);

		// Open the database
		Db.Open();

		// Get an array of all the profile documents in the database
		Db.GetProfileDocuments("", &docs);

		// Loop through all the profile documents in the database
		Count = docs.GetCount();
		for (Index = 0; Index < Count; Index++)
		{
			profile = docs[Index];

			// Print out the profile name
			cout << "\n\nThe name of profile number " << Index << " is " << profile.GetProfileName() << endl;
			// and the owner name
			cout << "The owner of this profile is " << profile.GetOwnerName() << endl;
			
			// If it is a calendar profile and alarms are enabled print that information
			if (profile.GetProfileName() == LNPROFILECALENDAR)
			{
				calend = profile;

				if (calend.GetEnableAlarmNotification())
					cout << "Alarms are enabled for this calendar profile" << endl;

			}

		}

	}


	// Error handler.  If an error occurred, get the text of
	// the error message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];	
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error:  " << ErrorBuf << endl;
	}
	catch(...)
	{	
		cout << "Unknown error in test" << endl;
	}	

	// Close the database
	Db.Close();

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);	

	Session.Term();
	return (0);
}


