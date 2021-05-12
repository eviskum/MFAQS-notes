//===========================================================================
//
//    PROGRAM: AGENTS
//
//    FILE:    agents.cpp
//
//    SYNTAX:  agents appletpath [ server ]
//
//    PURPOSE: Shows how to create various V5 Agent notes via the 
//    Notes C++ API
//
//    DESCRIPTION:
//        This sample creates the following four Agent notes in the 
//        PROBLEMS.NSF database supplied with the toolkit. 
//
//        1) A manual (menu command), shared, Actions Agent run 
//        against the currently selected document.
//        
//        2) A disabled, shared, background LotusScript Agent
//        triggered and run against new and/or documents.
//
//        3) An enabled, shared, scheduled, Formula based Agent
//        run against selected by search criteria documents once 
//        a day.
//
//        4) A manual (menu command), shared, Java Agent run 
//        against all documents in the database.
//
//===========================================================================

#include <lncppapi.h>
#include <iostream.h>

#define ERR_BUF_SIZE 512

char CommandBuf[80];

// Program function prototypes 
void  AddManualAgent( LNDatabase &Db );
void  AddBackgroundAgent( LNDatabase &Db, LNString &ServerName );
void  AddScheduleAgent( LNDatabase &Db, LNString &ServerName );
void  AddJavaAgent( LNDatabase &Db, const LNString &JavaFilesPath );

// Progam constants - names of the agents
#define AGENT_MANUAL        "Send Reminder to Support Rep"
#define AGENT_BACKGROUND    "Assign Support Rep"
#define AGENT_SCHEDULED     "Decrease Priority"
#define AGENT_JAVA          "Assign Hot Problems"

int main(int argc, char *argv[])
{
	cout << "\nRunning AGENTS..." << endl;

	LNNotesSession  Session;
	LNString		AppletPath;
	LNString		DbFilename;
	LNString		DbServer;
	LNDatabase		Db;

	// Initialize the C++ API 
	// Note: We need to do this before we process input parameters
	//       because we are using the LNString class for inputs.

	if (Session.Init(argc, argv))
	{
		cout << "\nUnable to initialize the API" << endl;
		return(1);
	}

	// Check the command line.
	if ( argc < 2 || argc > 3) 
	{
		cout << "\nUsage:\t" << "agents"
		<< " appletpath [ server ]" << endl;
		Session.Term();
		return(2); 
	}

	// Get info from command line.
	AppletPath = argv[1];

	if (argc == 3) 
		DbServer = argv[2];

	DbFilename = "problems.nsf";	// sample only works with this database

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try 
	{
		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open it.
		Db.Open();

		// Create and add manual Agent
		AddManualAgent(Db);

		// Create and add background Agent
		AddBackgroundAgent(Db, DbServer);

		// Create and add scheduled Agent
		AddScheduleAgent(Db, DbServer);

		// Create and add Java Agent
		AddJavaAgent(Db, AppletPath);
		cout << "Successfully added 4 Agents to " << DbFilename << endl;
	}

	// Error handler.  If an error occurred, get the text of 
	// the error message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}

	// Close the database, free memory.
	Db.Close(); 

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);    

	// Terminate the API.
	Session.Term();
	
	// All done.
	return(0);
}

//======================================================================
//
//  FUNCTION:   AddManualAgent
//
//  PURPOSE:    Add a Manual (executed from menu) Agent to the database.
//
//  DESCRIPTION:
//	This function adds a manual Agent named "Send reminder to Support Rep"
//	to the open database.  
//	
//	This Agent will send a mail message, with doclink, to the support
//	reps of all the selected documents in the view.
//	
//	After creating this Agent, you can execute it 
//	by running the Notes worstation, opening the database, and selecting
//	this Agent from the "Actions" menu of the main view.  
//
//=======================================================================
void AddManualAgent( LNDatabase &Db )
{
	LNAgent		Agent;
	LNString	Title(AGENT_MANUAL);
	LNString	Comment("Send a reminder email to the appropriate "
				"support reps for the documents selected in the view.");

	// Clean up
	if(Db.AgentExists(Title))
		Db.DeleteAgent(Title);

	// Create shared Agent note
	Db.CreateAgent(Title, TRUE, &Agent);

	// Set comment
	Agent.SetComment(Comment);

	// Set 'Send Mail Message' action
	LNSimpleSendMailAction Mail;
	LNFormula Formula("SRep");
	Mail.SetToFormula(Formula);
	Formula = "\"Reminder: \" + CompanyName + \" problem still open\"";
	Mail.SetSubjectFormula(Formula);
	Mail.SetIncludeDoclink(TRUE);
	Mail.SetIncludeDocument(FALSE);

	LNSimpleActions Actions;
	Actions.Append(Mail);
	Agent.SetSimpleActions(Actions);

	// Enable
	Agent.SetIsEnabled(TRUE);

	// Set manual trigger                           
	Agent.SetAgentSchedule(LNAGENTSCHEDULE_MANUALLY_FROM_ACTIONS_MENU);

	// Save and close
	Agent.Save();
	Agent.Close();

}

//=========================================================================
//
//  FUNCTION:   AddBackgroundAgent
//
//  PURPOSE:    Add a background (event triggered) Agent to the database.
//
//  DESCRIPTION:
//	This function adds a shared, disabled, background Agent named 
//	"Assign Support Rep" to the open database.  
//	
//	This Agent is LotusScript based will assign "Isabel Silton" as the 
//	Support Rep for those documents that do not have one assigned.
//
//	After creating this Agent, you can force execution by running the
//	Notes worstation, opening the database, opening the Agents view, 
//	selecting this Agent from the list, and executing the Run command
//	from the Actions menu.
//
//	Alternatively, since this background Agent is triggered each time a
//	document is added or modified to the database, you can enable 
//	background execution of the Agent by creating or modifying a problem
//	report document in the database.  Note that you must first enable 
//	the Agent from the Agents view.
//					       
//========================================================================
void AddBackgroundAgent( LNDatabase &Db, LNString &ServerName )
{
	LNAgent 	Agent;
	LNString 	Title (AGENT_BACKGROUND);
	LNString 	Comment ("Assign all unassigned "
				"problems to Isabel Silton.");

	// The problem with Lotus Script agents is that you can not use "raw"
	// Lotus Script source code. The reason is that internally Lotus Script
	// code is stored "decorated" with special headers which Notes UI uses
	// to properly render it. This means that Lotus Script code should be first
	// saved through Notes UI, and then it may be extracted for use elsewhere.
	// We'll use default agent with Lotus Script here as a storage facility.
	// In R5 script libraries may also be used for this purpose.
	//
	// Note that the API which formats "raw" code for internal 
	// storage was finally exposed in Release 5.0.3 (look for AgentLSTextFormat)
	// but the current release of this toolkit is based on Release 5.0.0.


	// We give here the Lotus Script source that was entered and saved in 
	// "Default Agent With Lotus Script" agent note in problems.nsf database.
/*
	Sub Initialize 
		  Dim updcount As Integer
		  Dim repname As String
		  Dim session As New NotesSession
		  Dim db As NotesDatabase
		  Dim dc As NotesDocumentCollection
		  Dim doc As NotesDocument
		  Dim parm As NotesDocument
		  Set db = session.CurrentDatabase
		  Set dc = db.AllDocuments
		  updcount = 0
		  Set parm = session.DocumentContext
		 'if running from UI, then hardcode new rep name
		  If parm IS NOTHING Then
		   repname = "Isabel Silton"
		 'else, use passed parameter document value
		  Else
		   repname = parm.NewRep(0)
		  End If
		 'assign passed name to all unassigned, open problems
		  For j = 1 To dc.Count
		   Set doc = dc.GetNthDocument(j)
		   If doc.SRep(0) = "" AND doc.Status(0) = "Open" Then
			doc.SRep = repname
			updcount = updcount+1
		   End If
		   Call doc.Save(True,False)
		  Next
		  Print "Support Rep parameter = "+repname
		  Print "Updated documents = "+STR$(updcount)
	End Sub
*/

	// Clean up
	if(Db.AgentExists(Title))
		Db.DeleteAgent(Title);

	// Create Agent note
	Db.CreateAgent(Title, TRUE, &Agent);

	// Set comment
	Agent.SetComment(Comment);

	// Extract Lotus Script from Notes storage
	LNAgent sourceAgent;
	Db.GetAgent("Default Agent With Lotus Script", &sourceAgent);
	sourceAgent.Open();

	LNLotusScript LotusScript;
	sourceAgent.GetLotusScript(&LotusScript);

	//You may uncomment the following two lines to see
	//what the internal format of Lotus Script code looks like:

	//LNString internalSource = LotusScript.GetSource();
	//cout << internalSource << endl;

	// Set Lotus Script
	Agent.SetLotusScript(LotusScript);           

	// Make agent available for public access users
	Agent.SetAllowPublicAccessUsers(TRUE);

	// Disable
	Agent.SetIsEnabled(FALSE);

	// Set trigger                           
	Agent.SetAgentSchedule(LNAGENTSCHEDULE_IF_DOCUMENTS_CREATED_OR_MODIFIED);

	// Set server name
	Agent.SetServerName(ServerName);

	// Save and close
	Agent.Save();
	Agent.Close();

}
	  
//=======================================================================
//
//  FUNCTION:   AddScheduleAgent
//
//  PURPOSE:    Add a scheduled Agent to the database.
//
//  DESCRIPTION:
//	This function adds a shared scheduled Agent named "Escalate Priority"
//	to the open database.  
//	
//	Every day at 1AM, this Agent will decrease the Priority of all created 
//  during the previous 24 hours opened problems one level.  
//  If the priority is already Low, then it is unchanged.  
//
//	After creating this Agent, you can force execution by running the
//	Notes worstation, opening the database, opening the Agents view, 
//	selecting this Agent from the list, and executing the Run command
//	from the Actions menu.
//
//	Note that if you wish to allow the Agent to run "On schedule", you 
//	must enable scheduled local agents on the Notes workstation. 
//		
//==========================================================================
void AddScheduleAgent( LNDatabase &Db, LNString &ServerName )
{
	LNAgent		Agent;
	LNString	Title (AGENT_SCHEDULED);
	LNString	Comment ("Once a day, search for all open "
				"problems that were created less than 24 hours ago and decrease the priority "
				"one level.");
	LNFormula	Formula("FIELD Priority := " 
				"@If(Priority=\"High\";\"Medium\";"
				"Priority=\"Medium\";\"Low\";\"Low\"); SELECT @All;");

	// Clean up
	if(Db.AgentExists(Title))
		Db.DeleteAgent(Title);

	// Create Agent note
	Db.CreateAgent(Title, TRUE, &Agent);

	// Set comment
	Agent.SetComment(Comment);

	// Set formula
	Agent.SetFormula(Formula, LNAGENTFORMULATYPE_MODIFY);           

	// Disable
	Agent.SetIsEnabled(FALSE);

	// Set schedule and its parameters                               
	Agent.SetAgentSchedule(LNAGENTSCHEDULE_EVERY_DAY);
	Agent.SetStartHour ( 1 );

	// Set document selection criteria
	LNSearches searches;

	// 1. Act on documents based on on the form "Problem" only.
	// Notice that we specify the form name here, while the documents
	// in the database use alias "EditDocument" referring to the form.
	// (see "Form" field in the "Document Properties" dialog box.).
	// Notes C++ code takes care of that as long as it can find the form by the
	// specified name.

	LNSearchByFormUsed ByForm; 
	LNText FormNames;			
	FormNames << "Problem";
	ByForm.SetFormNames(FormNames);
	searches.Append(ByForm);

	// act on documents which were created in the last 24 hours.

	LNSearchByDate ByDate;          
	ByDate.SetIsDateCreated(TRUE); 
	ByDate.SetDateCondition(LNSEARCHDATECOND_IN_THE_LAST);
	ByDate.SetNumberOfDays(1);
	searches.Append(ByDate);

	// choose only those which has status 'Open'
	LNSearchByTextInField ByTextInField; 
	ByTextInField.SetFieldName("Status");
	ByTextInField.SetSearchString("Open");
	searches.Append(ByTextInField);

	Agent.SetSearches(searches);

	// Set one of the two available documents option
	Agent.SetAgentDocumentsOption (LNAGENTDOCUMENTSOPTION_ALL_IN_DB);

	// Enable
	Agent.SetIsEnabled(TRUE);

	// Set server name
	Agent.SetServerName(ServerName);

	// Save and close
	Agent.Save();
	Agent.Close();

}

//=======================================================================
//
//  FUNCTION:   AddJavaAgent
//
//  PURPOSE:    Add a Java Agent (executed from Menu) to the database.
//
//  DESCRIPTION:
//	This function adds a shared manual Agent named "Assign Hot Problems"
//	to the open database.  
//	
//	This Agent is Java based and will assign "Fire Fighters" as the 
//	Support Rep for those documents that have an "Open" Status and
//	"High" Priority. Java agents are supported for Notes Release 4.6
//	and later.
//
//	After creating this Agent, you can execute it 
//	by running the Notes workstation, opening the database, and selecting
//	this Agent from the "Actions" menu of the main view.  
//					       
//=========================================================================
void AddJavaAgent( LNDatabase &Db, const LNString &JavaFilesPath )
{
	LNAgent  Agent;
	LNString Title (AGENT_JAVA);
	LNString Comment ("Assign all hot problems (high priority) to Fire Fighters.");
	LNString Class ("HotAgent.class"); 
	LNString JavaFileName("HotAgent.class");

	// Clean up
	if(Db.AgentExists(Title))
		Db.DeleteAgent(Title);

	// Create Agent note
	Db.CreateAgent(Title, TRUE, &Agent);

	// Set comment
	Agent.SetComment(Comment);

	// Set Java Code
	LNText JavaFileNames;
	JavaFileNames << JavaFileName;
	Agent.CreateJavaCode(Class, JavaFilesPath, JavaFileNames);           

	// Enable
 	Agent.SetIsEnabled(TRUE);

	// Set schedule                          
	Agent.SetAgentSchedule(LNAGENTSCHEDULE_MANUALLY_FROM_ACTIONS_MENU);

	// Set documents option 
	Agent.SetAgentDocumentsOption (LNAGENTDOCUMENTSOPTION_ALL_IN_DB);

	// Enable
	Agent.SetIsEnabled(TRUE);

	// Save and close
	Agent.Save();
	Agent.Close();

}
