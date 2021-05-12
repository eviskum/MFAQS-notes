//===========================================================================
//
//   Module: rtjava.cpp
//
//   Description:
//      This program illustrates how to embed a Java applet in rich text.
//
//   Syntax:
//      rtjava appletPath [ dbname [-s server] [ appletClass [ class ... ] ]
//
//      The only required parameter is appletPath, which is the location of
//      the .class files. If no dbname is specified, rtsample.nsf is used.
//      If no class files are specified, the files included with this sample
//      are used.  If class files are specified, the applet class must be listed
//      first.
//
//      This sample creates a document with a text field "Subject" and rich
//      text field "Body", which matches the forms and views in rtsample.nsf.
//
//===========================================================================

#include <fstream.h>
#include <lncppapi.h>

//
//		Subroutine declarations
//

int ProcessArguments (
	int			argc,
	char **		argv,
	LNString *	pAppletPath,
	LNString *	pDbName,
	LNString *	pServerName,
	LNString *	pAppletName,
	LNText *	pAppletFiles);

LNSTATUS  CreateJavaApplet(
	const LNString & AppletName,
	const LNString & FilePath,
	const LNText &   AdditionalFiles,
	LNRichText *     Rt);

#define ERR_BUF_SIZE   512
#define BUFFER_SIZE    1024

int main (
	int		argc,
	char *	argv []
) {
	LNSTATUS        Status = LNNOERROR;
	LNNotesSession  Session;
	LNDatabase   	Db;
	LNString		AppletPath;
	LNString		DbName;
	LNString		ServerName;
	LNString		AppletName;
	LNText			AdditionalFiles;

	LNSetThrowAllErrors(TRUE);
		
	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try
	{
		Session.Init(argc, argv);

			// Either parse the command line, or (on the Macintosh)
			// prompt for the arguments.  Since this uses LNString
			// and LNText, it must be done AFTER Session.Init ().
		ProcessArguments (
			argc,
			argv,
			&AppletPath,
			&DbName,
			&ServerName,
			&AppletName,
			&AdditionalFiles);

			//  Get the specified database and open it.
		Session.GetDatabase(DbName, &Db, ServerName);

		Db.Open();

		LNDocument      Doc; 
		LNText			Txt;
		LNRichText      Rt;

			// Create a new document
		Db.CreateDocument (&Doc, "Journal Entry");

			// Create the fields
		Doc.CreateItem ("Subject", &Txt);
		Txt.Append ("Java Applet Sample");

		Doc.CreateItem ("Body", &Rt);

			// Ensure the item is available
		if ( Rt.IsNull() )
		{
			Status = LNERR_OBJECT_NOT_INITIALIZED;
			throw (Status);
		}

			// Add some text
		Rt.Append ("Here is the Java applet:\n");

			// Add the Java applet
		CreateJavaApplet (AppletName, AppletPath, AdditionalFiles, &Rt);
		cout << "Applet created" << endl;

			// Add a bit more text
		Rt.Append ("\nThere's the applet!\n");

			// Save and close the document
		Doc.Save();
		Doc.Close();
	}

	//  Error handler.  If an error occurred, get the text of the error
	//  message and display it.
	
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}

	catch (char * pErrorMessage)
	{
		cout << "Error: " << pErrorMessage << endl;
		cout << "\nUsage:\n\trtjava " <<
			"appletPath [ dbname [-s server] [ appletClass [ class ... ] ] \n" <<
			endl;
	}
  
	//Close the database, free document memory.
	if (Db.IsOpen())
		Db.Close(); 

	//Terminate the API.
	Session.Term();

	cout << endl;   
	cout << "Program complete." << endl;

	//All done.
	return(0);
}

//	This function processes the command-line arguments (or, on the Macintosh,
//	does the promting and user input).


int ProcessArguments (
	int			argc,
	char **		argv,
	LNString *	pAppletPath,
	LNString *	pDbName,
	LNString *	pServerName,
	LNString *	pAppletName,
	LNText *	pAppletFiles
) {

	int		curArg = 1;		// Skip the program name!

		// Get the applet path
	if (curArg < argc)
	{
		*pAppletPath = argv[curArg];
		curArg++;
	}
	else
		throw "Missing applet path";	// Required argument

		// Get the database name
	if (curArg < argc)
	{
		*pDbName = argv[curArg];
		curArg++;

			// Any other parameters?
		if (curArg < argc)
		{
				// Yes - is the [-/][sS] flag present?
			if ((('-' == argv[curArg][0]) || ('/' == argv[curArg][0])) &&
				(('S' == argv[curArg][1]) || ('s' == argv[curArg][1])))
			{
				curArg++;		// Skip the flag

					// Yes - copy the server name
				if (curArg < argc)
				{
					*pServerName = argv[curArg];
					curArg++;
				}
				else
					throw "Missing server name";	// Server name required after -s!
			}
			else
				*pServerName = "";

				// Get the applet name and additional files, if present
			if (curArg < argc)
			{
				*pAppletName = argv[curArg];
				curArg++;
	
					// Append any additional arguments to the additional files list
				while (curArg < argc)
				{
						// Append the string
					*pAppletFiles << LNString (argv[curArg++]);
				}
			}
		}
	}
	else
		*pDbName = "rtsample.nsf";	// No database name, use default

		// If no applet name specified, use defaults
	if (pAppletName->IsNull())
	{
		*pAppletName = "SystemProperties.class";

		*pAppletFiles << "PropertyWrapper.class"
					  << "ButtonKeyDriver.class"
					  << "PanelKeyDriver.class";
	}

	return (0);
}


//  This function constructs the Java applet in the rich text item.

LNSTATUS  CreateJavaApplet (
	const LNString & AppletName,
	const LNString & FilePath,
	const LNText &   AdditionalFiles,
	LNRichText *     Rt
) {
	LNRTCursor  Cursor;

		// Get a cursor to the end of the rich text item.
	Rt->GetEndCursor(&Cursor);

		// Create the applet
	LNRTJavaApplet	Applet;

	Rt->CreateJavaApplet (AppletName, &Cursor, &Applet);

		// Make the display size a bit bigger
	Applet.SetWidth (400);

		// Import the applet file
	Applet.ImportFile (AppletName, FilePath);

		// Import any additional files
	if (0 != AdditionalFiles.GetCount ())
	{
		Applet.ImportFiles (AdditionalFiles, FilePath);
	}

	Applet.SetAlternateText ("The Java applet could not be loaded.");

		// That's all there is to it!
	return (LNNOERROR);
}


