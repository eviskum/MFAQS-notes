//===========================================================================
//
//      Module: ADDINJOB.CPP
//
//      Description:
//              This program demonstrates how to use the LNServerAddin class
//              to create a server add-in task to periodically update a 
//              database. It creates a status line and sets its status, 
//              then performs certain operations at specific time intervals. 
//              It also ouputs the status line text and the add-in task name 
//              to the server log.nsf file.
//
//      SYNTAX: (at the Lotus server console) > load addinjob
//
//===========================================================================
//
// Copyright (c) 1997-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================


#include <lncppapi.h>
#include <iostream.h>

#ifndef LNSERVERADDIN_HPP
#define LNSERVERADDIN_HPP
#include <lnsaddin.hpp>
#endif

// The database that we will update via this add-in task.
#define DATABASE_NAME "addinjob"

#define ERR_BUF_SIZE 512

// Function prototype:
static LNSTATUS OurAddInJob( LNDatabase &Db, LNNotesSession &Sess );

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{

	LNNotesSession  Session;
	LNSTATUS                Lnstat = LNNOERROR;
	LNDatabase              TestDb;

	LNSetThrowAllErrors(TRUE);
	
	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try
	{
		LNServerAddin   Addin;
		LNString                Buffer;

		// Initialize the C++ API.
		Session.Init(argc, argv);

		// First get our output database file.
		Session.GetDatabase(DATABASE_NAME, &TestDb);

		// Create a server add-in task with default status line.
		Buffer = "DefaultStatusLineTaskName = ";
		Session.GetServerAddin("ADDINJOB","CPP ADDIN TEST", &Addin);

		// Append the task Name to the log file.
		Buffer.Append(Addin.GetDefaultStatusLineTaskName());
		Addin.AppendLogMessage(Buffer);

		// Append the status line text to the log file.
		Buffer = "DefaultStatusLineText = ";
		Buffer.Append(Addin.GetDefaultStatusLineText());
		Addin.AppendLogMessage(Buffer);

		// Begin the main loop. When Addin.Idle() returns TRUE, 
		// it is time to shut down this task.
		while (!Addin.Idle())
		{               
	
			// Do the operations that we do each day. 
			if (Addin.IsNewDay())
			{
				Addin.SetDefaultStatusLineText("Doing daily job");

				// Append the status line text to the log file.
				Addin.AppendLogMessage("Addin Test: Daily job complete.");

				Addin.SetDefaultStatusLineText("Idle");
			}
 
			// Do the operations that we do every other minute.
			else if (Addin.HaveMinutesElapsed(2))
			{
				Addin.SetDefaultStatusLineText("Doing two-minute job");

				// Append the status line text to the log file.
				Addin.AppendLogMessage("Addin Test: Two-minute job complete.");

				Addin.SetDefaultStatusLineText("Idle");
			}

			// Do the operations that we do every 20 seconds. 
			else if (Addin.HaveSecondsElapsed(20))
			{        
				Addin.SetDefaultStatusLineText("Doing 20-second job");

				// Do our database update job in this add-in task.
				Lnstat = OurAddInJob(TestDb,Session);
				if (Lnstat)
					throw Lnstat;

				// Append the status line text to the log file.
				Addin.AppendLogMessage("Add-in Test: 20-second job complete.");

				Addin.SetDefaultStatusLineText("Idle");
			}

		} // End of main task loop.
	}


	// Error handler.  If an error occurred, get the text of the error
	// message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}
	
	// Just in case the test database is still opened
	if (TestDb.IsOpen())
		TestDb.Close();

	// Terminate the API.
	Session.Term();

	//All done.
	return(0);
}


//---------------------------------------------------------------------------
//
// Name:
//              OurAddInJob
//
// Description:
//              Local function called by the main add-in task loop.
//
// Inputs:
//              Db - LNDatabase for the database to be updated
//              Sess - LNNotesSession for this Notes session
//
// Outputs:
//              If successful, the database is updated.
//
// Returns:
//              0 if successful, error code otherwise.
//
//---------------------------------------------------------------------------
static LNSTATUS OurAddInJob ( LNDatabase &Db, LNNotesSession &Sess )
{
	// Local data declarations.
    LNSTATUS            Stat = LNNOERROR;
	LNDocument      Doc;
	LNText          AddInTextFld;
	LNDatetime      Dt;
	LNDatetimes     TimeFld;


	// Open the database.
	Stat = Db.Open();
	if (Stat)
		goto cleanup;

	// Create a new document in the database.
	Stat = Db.CreateDocument(&Doc);
	if (Stat)
		goto cleanup;

	// Set document form name.
	Stat = Doc.SetForm("AddInForm");
	if (Stat)
		goto cleanup;
    
	// Set the AddIn_Text field value.
	Stat = AddInTextFld.SetValue("This is a note written by the add-in task.");
	if (Stat)
		goto cleanup;

	// Create AddIn_Text text field item in the new document.
	Stat = Doc.CreateItem("AddIn_Text", AddInTextFld, LNITEMFLAGS_SUMMARY);
	if (Stat)
		goto cleanup;

	// Get a snapshot of the current date/time 
	Dt = Sess.GetCurrentDatetime();

	// Set the current date/time into the TimeField LNItem.
	Stat = TimeFld.SetValue(Dt);
	if (Stat)
		goto cleanup;

	// Create the AddIn_Time field item in the new document.
	Stat = Doc.CreateItem("AddIn_Time", TimeFld, LNITEMFLAGS_SUMMARY);
	if (Stat)
		goto cleanup;

	// Save the newly created document to the database.
	Stat = Doc.Save();

cleanup:

	// Check to see if the document is opened; close it if opened.
	if (Doc.IsOpen())
		Doc.Close();

	// Check to see if the database is opened; close it if opened.
	if (Db.IsOpen())
		Db.Close();

	return Stat;
}
