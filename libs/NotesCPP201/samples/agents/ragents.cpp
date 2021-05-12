/****************************************************************************

    PROGRAM: RAGENTS

    FILE:    ragents.cpp

    SYNTAX:  ragents 

    PURPOSE: Shows how to execute various V4 Agent notes via the Notes C++ API

    DESCRIPTION:
	 This sample executes the background and scheduled agents that 
	 were created with agents.exe and reads and displays the results.

	For the ragent.exe to execute successfully, you must use the sample
	database problems.nsf, which is supplied with the toolkit.

****************************************************************************/
#include <lncppapi.h>
#include <iostream.h>
#include <fstream.h>

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

char CommandBuf[80];

// Program function prototypes 
void  AddManualAgent( LNDatabase &Db );
void  AddBackgroundAgent( LNDatabase &Db );
void  AddScheduleAgent( LNDatabase &Db );
void  AddJavaAgent( LNDatabase &Db );

// Progam constants - names of the agents
#define AGENT_BACKGROUND    "Assign Support Rep"
#define AGENT_SCHEDULED     "Escalate Priority"
#define LOTUSSCRIPT_ACTION  0
#define FORMULA_ACTION      1

/*log file and file pointer */
#define AGENTS_LOG   "agents.log" 

ofstream fout(AGENTS_LOG); 

/*LotusScript agent "Parameter Document" variables */
#define     PARM_FIELD  "NewRep"
#define     PARM_VALUE  "Isabel Silton"

/* Function Prototypes */
STATUS  LNPUBLIC  RunTriggeredAgents ( DBHANDLE );
STATUS  LNPUBLIC  GetAgentRunInfo( DBHANDLE, char * );
STATUS  LNPUBLIC  OpenAgent ( DBHANDLE, char *, HAGENT * );
STATUS  LNPUBLIC  SetRunContext ( HAGENT, WORD, HAGENTCTX * );
STATUS  LNPUBLIC  ExecuteAgent( HAGENT, HAGENTCTX );
void    LNPUBLIC  GetScriptRunInfo( HAGENTCTX );
void    LNPUBLIC  CloseAgent ( HAGENT, HAGENTCTX );

int main(int argc, char *argv[])
{
	cout << "\nRunning RAGENTS..." << endl;

	// Initialize the C++ API.
	LNNotesSession                  Session;
	if (Session.Init(argc, argv))
	{
		cout << "\nUnable to initialize the API" << endl;
		return(2);
	}

	LNString        DbFilename;
	LNString        DbServer;
	LNDatabase      Db;

#if defined MAC

	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line.
	char            fileBuffer[MAXPATH];
	char            serverBuffer[MAXPATH];

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
	
	// Prompt for parameters since they are not being passed in on the command line.
	cout << endl << "Enter database filename: " << flush;
	gets(fileBuffer);
	cout << "Enter server name:  " << flush;
	gets(serverBuffer);

	DbFilename = fileBuffer;
	DbServer = serverBuffer;
#else
	// On anything other than the Macintosh, the parameters
	// are entered on the command line.

	// Check the command line.
	if ( argc > 3) 
	{
		cout << "\nUsage:\t" << "agents"
		<< " [database [server]]" << endl;
		return(1); 
	}

	// Get info from command line.
	if ( argc == 1 ) DbFilename = "problems.nsf";
	else DbFilename = argv[1];
	
	if (argc == 3) DbServer = argv[2];
#endif

	if(DbFilename != "problems.nsf")
	{
		cout << "This sample works with \"problems.nsf\" database only" << endl;
		goto Term;
	}

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try 
	{
		LNAgent agent;
		LNDocument parmDocument;
		LNINT i;

		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open it.
		Db.Open();

		// Get background agent
		if(Db.AgentExists(AGENT_BACKGROUND))
			Db.GetAgent(AGENT_BACKGROUND, &agent);

		// Open the agent's note
		agent.Open();

		// Create Parameter Document Note for Script agent action.  
		// This parameter specifies the Support Rep name that is to be
		// assigned to unassigned problem reports, ie. "Isabel Silton".
		Db.CreateDocument(&parmDocument);
		LNText Value;
		Value << PARM_VALUE;
		parmDocument.CreateItem( PARM_FIELD, Value); 

		// Run agent, redirecting output into memory
		agent.Execute(parmDocument, 
			LNAGENTEXECUTEFLAGS_DEFAULT, LNAGENTOUTPUTOPTION_MEMORY);
		
		cout << "Successfully ran agent " << AGENT_BACKGROUND << endl;
		fout << "Successfully ran agent " << AGENT_BACKGROUND << endl;

		// Retrieve the run data results from memory...
		LNText Output = agent.GetAgentOutputFromMemory ();

		// and save them in the log file
		for(i = 0; i < Output.GetCount(); i++)
			fout << LNString(Output[ i ]) << endl;

		// retrieve run data from the run data object
		LNAgentRunData RunData = agent.GetAgentRunData();

		//  save them in the log file
		fout << "Summary:" << endl;

		LNString RunDatetimeString;
		RunData.GetRunDatetime().GetText(&RunDatetimeString);

		fout << "Time of the last run: " << RunDatetimeString << endl;

		fout << "Number of processed documents: " << RunData.GetProcessedDocumentsCount() << endl;
		 
        fout << "Exit status code: " << RunData.GetRunExitCode() << endl;			
		
		fout << "Run log:" << endl;

		fout <<  RunData.GetRunLog() << endl;
		
		agent.Close();

		// Run the scheduled agent 
		if(Db.AgentExists(AGENT_SCHEDULED))
			Db.GetAgent(AGENT_SCHEDULED, &agent);

		agent.Open();

		agent.Execute();

		cout << "Successfully ran agent " << AGENT_SCHEDULED << endl;
		fout << "Successfully ran agent " << AGENT_SCHEDULED << endl;

	
		// retrieve run data from the run data object
		RunData = agent.GetAgentRunData();

		//  save them in the log file
		fout << "Summary:" << endl;

		RunDatetimeString;
		RunData.GetRunDatetime().GetText(&RunDatetimeString);

		fout << "Time of the last run: " << RunDatetimeString << endl;

		fout << "Number of processed documents: " << RunData.GetProcessedDocumentsCount() << endl;
		 
        fout << "Exit status code: " << RunData.GetRunExitCode() << endl;			
		
		fout << "Run log:" << endl;

		fout <<  RunData.GetRunLog() << endl;

		agent.Close();
	}

	// Error handler.  If an error occurred, get the text of 
	// the error message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		ErrorBuf[0] = '\0';
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}

	// Close the database, free memory.
	Db.Close();

	fout << "Program execution completed." << endl; 
	cout << "Program execution completed.  See logfile " 
		<< AGENTS_LOG << " for results." << endl
		<< "Hit return to exit..." ;

	cin.getline(CommandBuf, 50); 

Term:
	// Terminate the API.
	Session.Term();
	
	// All done.
	return(0);
}


