//===========================================================================
//
//      Module: ADDINJOB.CPP
//
//      Description:
//
//          This program demonstrates how to use the LNServerAddin class
//          to create a server add-in task to periodically update a 
//          database. It creates a status line and sets its status.
//          Then it performs certain operations at specific time intervals. 
//          It ouputs the status line text and the add-in task name to
//          the server log.nsf file.  In addition to all this, the program
//          creates a message queue using the LNMessageQueue class and
//          uses the message queue to recieve commands from the server
//          console every 20 seconds which are echoed back to the console
//          using the the LNServerAddin::AppendLogMessage method.
//
//      SYNTAX: (at the Lotus server console) > load addinjob
//
//===========================================================================
#include <iostream.h>

// Notes C++ API headers.

#include "lncppapi.h"

// Forward declarations:

void OurAddInJob( LNDatabase &db, LNNotesSession &session );

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
int				ProgramStatus = 0;
LNNotesSession  session;
LNServerAddin   addin;

	// Throw all errors encountered during execution.

	LNSetThrowAllErrors(TRUE);

	try
	{
    LNDatabase      db;
	LNString        buffer;
    LNString        taskname;
    LNMessageQueue  mqueue;

		// Initialize the C++ API.

		session.Init(argc, argv);

		// First get our output database file.

		session.GetDatabase("addinjob.nsf", &db);

		// Create a server add-in task with default status line.

		session.GetServerAddin("ADDINJOB","CPP ADDIN SAMPLE", &addin);

		// Append the addin task Name to the log file.

        taskname = addin.GetDefaultStatusLineTaskName();
		buffer = "DefaultStatusLineTaskName = ";
		buffer.Append(taskname);
		addin.AppendLogMessage(buffer);

		// Append the status line text to the log file.

		buffer = "DefaultStatusLineText = ";
		buffer.Append(addin.GetDefaultStatusLineText());
		addin.AppendLogMessage(buffer);

        // Create a message queue for this addin task.

		buffer = TASK_QUEUE_PREFIX;
		buffer.Append(taskname);
        session.CreateMessageQueue( buffer, &mqueue);

		// Begin the addin task main processing loop.  The call to
        // addin.Idle() serves two functions.  First it relinquishes
        // processor control to Domino allowing other tasks to run.
        // Secondly, addin.Idle() will return TRUE, when it has recived
        // a quit command from Domino meaning a user has typed 
        // "tell myaddin quit" at the server console.
        // NOTE: the member function: ShouldAddinTerminate() could be
        // used to find this out as well without having to relinquish
        // processor control.

		while (!addin.Idle())
		{	
			// Do the operations that we do each day.

			if (addin.IsNewDay())
			{
				addin.SetDefaultStatusLineText("Doing daily job");

				// Append the status line text to the log file.

				addin.AppendLogMessage("CPP Add In Sample: Daily job complete.");
				addin.SetDefaultStatusLineText("Idle");
			}
 
			// Do the operations that we do every other minute.

			else if (addin.HaveMinutesElapsed(2))
			{
				addin.SetDefaultStatusLineText("Doing two-minute job");

				// Do our database update job in this add-in task.

				OurAddInJob(db,session);

				// Append the status line text to the log file.

				addin.AppendLogMessage("CPP Add In Sample: Two-minute job complete.");
				addin.SetDefaultStatusLineText("Idle");
			}

			// Do the operations that we do every 20 seconds. (check message queue)

			else if (addin.HaveSecondsElapsed(20))
			{
            LNString    message;
            LNINT       nRetLen;
            const LNINT nMaxMsgLen = MQ_MAX_MSGSIZE;
            char        buffer[nMaxMsgLen+1];

				addin.SetDefaultStatusLineText("Doing 20-second job");

				// Process messages if any are in the message queue.

                while (mqueue.GetMessageCount() > 0)
                {
                    // GetNextMessage automatically de-queues the message
                    // and decrements the current message count.

                    mqueue.GetNextMessage( nMaxMsgLen, buffer, &nRetLen);
                    
                    // Do stuff with the messages...

                    message = "CPP Add In Sample: Recieved console command: ";
                    message.Append( LNString((const char *)buffer, nRetLen) );

    				addin.AppendLogMessage(message);
                }

				// Append the status line text to the log file.

				addin.AppendLogMessage("CPP Add In Sample: 20-second job complete.");
				addin.SetDefaultStatusLineText("Idle");
			}

		} // End while (!addin.Idle())

        // Close the database.

        db.Close();

    } // END Try

    catch (LNSTATUS lnerror)
    {
    char ErrorBuf[LNERROR_MESSAGE_LENGTH];
    LNString errormessage;

        LNGetErrorMessage(lnerror, ErrorBuf, LNERROR_MESSAGE_LENGTH);

        errormessage = "AddInJob Sample: Exception thrown! Error: ";
		errormessage.Append(ErrorBuf);
        addin.AppendLogMessage(errormessage);

        ProgramStatus = 1;
    }

    catch (const char *pErrorMessage)
    {
    LNString errormessage;

        errormessage = "AddInJob Sample: Exception thrown! Error: ";
		errormessage.Append(pErrorMessage);
        addin.AppendLogMessage(errormessage);

        ProgramStatus = 2;
    }

    catch (...)
    {
    LNString errormessage;

        errormessage = "AddInJob Sample: Exception thrown! Error unknown!: ";
        addin.AppendLogMessage(errormessage);

        ProgramStatus = 3;
    }

	// Terminate the API

	session.Term();

	return(ProgramStatus);

} // END main()


//---------------------------------------------------------------------------
//
// Name:
//              OurAddInJob
//
// Description:
//              Local function called by the main add-in task loop.
//
// Inputs:
//              db - LNDatabase for the database to be updated
//              session - LNNotesSession for this Notes session
//
// Outputs:
//              If successful, the database is updated.
//
//---------------------------------------------------------------------------
void OurAddInJob ( LNDatabase &db, LNNotesSession &session )
{
LNDocument      Doc;
LNText          AddInTextFld;
LNDatetime      Dt;
LNDatetimes     TimeFld;

	try
	{
	    // Open the database, create a new doc, and set its form.

        db.Open();
        db.CreateDocument(&Doc);
        Doc.SetForm("AddInForm");

	    // Set the AddIn_Text field value.

        AddInTextFld.SetValue("This is a note written by the add-in task.");

	    // Create AddIn_Text text field item in the new document.

        Doc.CreateItem("AddIn_Text", AddInTextFld, LNITEMFLAGS_SUMMARY);

	    // Get a snapshot of the current date/time and use it to
        // create a new datetime field in the new document.

	    Dt = session.GetCurrentDatetime();
        TimeFld.SetValue(Dt);
        Doc.CreateItem("AddIn_Time", TimeFld, LNITEMFLAGS_SUMMARY);

	    // Save and close the new document and close the database.

        Doc.Save();
        Doc.Close();
        db.Close();

    } // END try

    catch (LNSTATUS lnerror)
    {
    char ErrorBuf[LNERROR_MESSAGE_LENGTH];

        LNGetErrorMessage(lnerror, ErrorBuf, LNERROR_MESSAGE_LENGTH);

        // Close everything that may be open at this point and then re-throw.
        Doc.Close();
        db.Close();

        throw lnerror;
    }

} // END OurAddInJob()

// END AddInJob.cpp


