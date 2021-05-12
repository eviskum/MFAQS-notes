/****************************************************************************

    PROGRAM: RAGENTS

    FILE:    ragents.cpp

    SYNTAX:  ragents 

    PURPOSE: Shows how to execute various V5 Agent notes via the Notes C++ API

    DESCRIPTION:
	 This sample executes the background and scheduled agents that 
	 were created with agents.exe and reads and displays the results.

	For the ragent.exe to execute successfully, you must use the sample
	database problems.nsf, which is supplied with the toolkit.

****************************************************************************/
#include <lncppapi.h>
#include <iostream.h>
#include <fstream.h>

#define ERR_BUF_SIZE 512

char CommandBuf[80];

// Progam constants - names of the agents
#define AGENT_BACKGROUND    "Assign Support Rep"
#define AGENT_SCHEDULED     "Decrease Priority"

// log file and file pointer
#define AGENTS_LOG   "agents.log" 

ofstream fout(AGENTS_LOG); 

// LotusScript agent "Parameter Document" variables
// Notice that manual or 'on schedule' run of this agent sets the default "Isabel Stilton" 
// name to all unassigned problems. Here we are going to pass parameters to the 
// scheduled LotusScript agent.

#define     PARM_FIELD  "NewRep"
#define     PARM_VALUE  "Sandy Block"

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

	// Check the command line.
	if ( argc > 2) 
	{
		cout << "Incorrect number of arguments." << endl;
		cout << "Usage:\t" << "ragents" << " [server]" << endl;
		goto Term; 
	}

	// Get info from command line.
	DbFilename = "problems.nsf";
	
	if (argc == 2) DbServer = argv[1];

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
		// assigned to unassigned problem reports, ie. "Sandy Block".
		// Basically we don't need to save this document.
		Db.CreateDocument(&parmDocument);
		LNText Value;
		Value << PARM_VALUE;
		parmDocument.CreateItem( PARM_FIELD, Value);

		// Run agent, redirecting output into memory
		agent.Execute(parmDocument, 
			LNAGENTEXECUTEFLAGS_DEFAULT, LNAGENTOUTPUTOPTION_MEMORY);
		
		cout << "Successfully ran agent " << "\"" << AGENT_BACKGROUND << "\"" << endl;
		fout << "Successfully ran agent " << "\"" << AGENT_BACKGROUND << "\"" << endl;

		// Retrieve the run data results from memory...
		LNText Output = agent.GetAgentOutputFromMemory ();

		fout << endl << "Output from memory (Lotus script agents only):" << endl << endl;

		// and save them in the log file
		for(i = 0; i < Output.GetCount(); i++)
			fout << LNString(Output[ i ]) << endl;

		// retrieve run data from the run data object
		LNAgentRunData RunData = agent.GetAgentRunData();

		//  save them in the log file
		fout << endl << "Output from Run Data:" << endl << endl;

		LNString RunDatetimeString;
		RunData.GetRunDatetime().GetText(&RunDatetimeString);

		fout << "Time of the last run: " << RunDatetimeString << endl;
		fout << "Number of processed documents: " << RunData.GetProcessedDocumentsCount() << endl;
        fout << "Exit status code: " << RunData.GetRunExitCode() << endl;			
		fout << endl << "Run log:" << endl << endl;
		fout << RunData.GetRunLog() << endl;
		
		agent.Close();

		// Run the scheduled agent 
		if(Db.AgentExists(AGENT_SCHEDULED))
			Db.GetAgent(AGENT_SCHEDULED, &agent);

		agent.Open();

		agent.Execute();

		cout << "Successfully ran agent " << "\"" << AGENT_SCHEDULED << "\"" << endl;
		fout << endl << "Successfully ran agent " << "\"" << AGENT_SCHEDULED << "\"" << endl;
	
		// retrieve run data from the run data object
		RunData = agent.GetAgentRunData();

		//  save them in the log file
		fout << endl << "Output from Run Data:" << endl << endl;

		RunDatetimeString;
		RunData.GetRunDatetime().GetText(&RunDatetimeString);

		fout << "Time of the last run: " << RunDatetimeString << endl;
		fout << "Number of processed documents: " << RunData.GetProcessedDocumentsCount() << endl;
        fout << "Exit status code: " << RunData.GetRunExitCode() << endl;			
		fout << endl << "Run log:" << endl << endl;
		fout << RunData.GetRunLog() << endl;

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


