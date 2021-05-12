//===========================================================================
//
//      Module: ADMINP.CPP
//
//      Description:
//			This program requests that a user be renamed in the
//			Name & Address book on the specified server.
//
//      Syntax:
//			adminp	<server> <certifier name> <certifier password>
//					<oldname> <firstname> <middlename> <lastname>
//
//===========================================================================
#include <iostream.h>

// Notes C++ API headers.

#include "lncppapi.h"

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
int				ProgramStatus = 0;
LNNotesSession  Session;

	// Check the command line. All arguments are required.

	if (argc != 8)
	{
		cout << "\nUsage:\n\t" << argv[0]
			 << " <server> <certifier name>"
			 << " <certifier password> <oldname>"
			 << " <firstname> <middlename> <lastname>"
			 << endl;

		return(1);
	}

	// Throw all errors encountered during command execution.

	LNSetThrowAllErrors (TRUE);

	try
	{
	// Add all local variables inside try block.

	char *DbServerName;
	char *CertifierName;
	char *CertifierPass;
	char *OldName;
	char *FirstName;
	char *MiddleName;
	char *LastName;
	LNAdministrationProcess	adminp;
	LNCertifier		cert;
	LNDatetime		expdate;

		// Initialize the API.

		Session.Init (argc, argv);

		// Get info from command line.

		DbServerName = argv[1];
		CertifierName = argv[2];
		CertifierPass = argv[3];
		OldName = argv[4];
		FirstName = argv[5];
		MiddleName = argv[6];
		LastName = argv[7];

		// We meed this for the certifier

		expdate = Session.GetCurrentDatetime();
		expdate.AdjustDate( 0, 0, 2 );

		Session.GetCertifier(CertifierName, expdate, &cert, CertifierPass);

		// Create the administration process object

		Session.CreateAdministrationProcess(DbServerName, &adminp);

		// Submit a request to rename someone

		adminp.RequestRename(cert, OldName, FirstName, MiddleName, LastName, "");
		adminp.ProcessRequests();

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

// END AdminP.cpp


