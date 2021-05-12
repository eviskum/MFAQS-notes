//===========================================================================
//
//    PROGRAM: AGENTS
//
//    FILE:    agents.cpp
//
//    SYNTAX:  agents appletpath [ server ]
//
//    PURPOSE: Shows how to create various V4 Agent notes via the 
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
//        a month.
//
//        4) A manual (menu command), shared, Java Agent run 
//        against all documents in the database.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#include <lncppapi.h>
#include <iostream.h>

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
void  AddJavaAgent( LNDatabase &Db, const LNString &JavaFilesPath );

// Progam constants - names of the agents
#define AGENT_MANUAL        "Send Reminder to Support Rep"
#define AGENT_BACKGROUND    "Assign Support Rep"
#define AGENT_SCHEDULED     "Escalate Priority"
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

#if defined MAC

	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line.
	char	appletPathBuffer[MAXPATH];
	char	serverBuffer[MAXPATH];

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
	cout << endl << "Enter applet directory name: " << flush;
	gets(appletPathBuffer);
	cout << "Enter server name:  " << flush;
	gets(serverBuffer);

	AppletPath = appletPathBuffer;
	DbServer = serverBuffer;
#else
	// On anything other than the Macintosh, the parameters
	// are entered on the command line.

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
#endif

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
		AddBackgroundAgent(Db);

		// Create and add scheduled Agent
		AddScheduleAgent(Db);

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
void AddBackgroundAgent( LNDatabase &Db )
{
	LNAgent 	Agent;
	LNString 	Title (AGENT_BACKGROUND);
	LNString 	Comment ("Assign all unassigned "
				"problems to Isabel Silton.");
	LNString 	Source ("Sub Initialize\n" 
				"  Dim updcount As Integer\n"
				"  Dim repname As String\n"
				"  Dim session As New NotesSession\n"
				"  Dim db As NotesDatabase\n"
				"  Dim dc As NotesDocumentCollection\n"
				"  Dim doc As NotesDocument\n"
				"  Dim parm As NotesDocument\n"
				"  Set db = session.CurrentDatabase\n"
				"  Set dc = db.AllDocuments\n"
				"  updcount = 0\n"
				"  Set parm = session.DocumentContext\n"
				" 'if running from UI, then hardcode new rep name\n"
				"  If parm IS NOTHING Then\n"
				"   repname = \"Isabel Silton\"\n"
				" 'else, use passed parameter document value\n"
				"  Else\n"
				"   repname = parm.NewRep(0)\n"
				"  End If\n"
				" 'assign passed name to all unassigned, open problems\n"
				"  For j = 1 To dc.Count\n"
				"   Set doc = dc.GetNthDocument(j)\n"
				"   If doc.SRep(0) = \"\" AND doc.Status(0) = \"Open\" Then\n"
				"	doc.SRep = repname\n"
				"	updcount = updcount+1\n"
				"   End If\n"
				"   Call doc.Save(True,False)\n"
				"  Next\n"
				"  Print \"Support Rep parameter = \"+repname\n"
				"  Print \"Updated documents = \"+STR$(updcount)\n"
				" End Sub\n");

	// Clean up
	if(Db.AgentExists(Title))
		Db.DeleteAgent(Title);

	// Create Agent note
	Db.CreateAgent(Title, TRUE, &Agent);

	// Set comment
	Agent.SetComment(Comment);

	// Set Lotus Script
	LNLotusScript LotusScript (Source);
	Agent.SetLotusScript(LotusScript);           

	// Disable
	Agent.SetIsEnabled(FALSE);

	// Set trigger                           
	Agent.SetAgentSchedule(LNAGENTSCHEDULE_IF_DOCUMENTS_CREATED_OR_MODIFIED);

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
//	On the first day of each month at 1AM, this Agent will increase the 
//	Priority of all open problems one level.  If the priority is already
//	High, then it is unchanged.  
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
void AddScheduleAgent( LNDatabase &Db )
{
	LNAgent		Agent;
	LNString	Title (AGENT_SCHEDULED);
	LNString	Comment ("Once per month, search for all open "
				"problems that are older than one month and escalate the priority "
				"one level.");
	LNFormula	Formula("FIELD Priority := " 
				"@If(Priority=\"Low\";\"Medium\";"
				"Priority=\"Medium\";\"High\";\"High\"); SELECT @All;");

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
	Agent.SetAgentSchedule(LNAGENTSCHEDULE_EVERY_MONTH);
	Agent.SetDayOfMonth ( 1 );
	Agent.SetStartHour ( 1 );

	// Set document selection criteria
	LNSearches searches;
	
	LNSearchByFormUsed ByForm;  // act on documents based on 
	LNText FormNames;			// on the form "Problem" only
	FormNames << "Problem";
	ByForm.SetFormNames(FormNames);
	searches.Append(ByForm);

	LNSearchByDate ByDate;          // act on documents which were not
	ByDate.SetIsDateCreated(FALSE); // acessed for more that 30 days
	ByDate.SetDateCondition(LNSEARCHDATECOND_OLDER_THAN);
	ByDate.SetNumberOfDays(30);
	searches.Append(ByDate);

	LNSearchByTextInField ByTextInField; // choose only those
	ByTextInField.SetFieldName("Status");// which has status 'Open'
	ByTextInField.SetSearchString("Open");
	searches.Append(ByTextInField);

	Agent.SetSearches(searches);

	// Set one of the two available documents option
	Agent.SetAgentDocumentsOption (LNAGENTDOCUMENTSOPTION_ALL_IN_DB);

	// Enable
	Agent.SetIsEnabled(TRUE);

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


