//===========================================================================
//
//      Module: HOTSPOT.CPP
//
//      Description:
//              This program illustrates how to create and manipulate
//              different kind of hotspots.
//
//      Syntax: HOTSPOT <dbname> [server]
//                      dbname = SAMPLEDB.NSF
//
//===========================================================================

#include <fstream.h>
#include <lncppapi.h>

LNSTATUS  CreateActionHotspot(LNRichText *Rt, LNRTCursor *Cursor);
LNSTATUS  CreateButton(LNRichText *Rt, LNRTCursor *Cursor);
LNSTATUS  CreatePopups(LNRichText *Rt, LNRTCursor *Cursor);

#define ERR_BUF_SIZE   512
#define BUFFER_SIZE    1024
#define SCRIPT_SOURCE  "script.txt"

char            ScriptFilePath[MAXPATH];
LNNotesSession  Session;


int main(int argc, char *argv[])
{
	char *          DbFilename;
	char *          DbServer = NULL;	
	LNSTATUS        Status = LNNOERROR;

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

	LNSetThrowAllErrors(TRUE);

	LNDatabase   	Db;
		
	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try
	{
		Session.Init(argc, argv);

		LNDocumentArray DocArray;

		//  Construct default, import, and export file paths.

		char   FilePath[LNMAXPATH];
		char   ScriptFile[LNMAXPATH];

		//  Check the data path length first.

		LNString	DataDir = Session.GetDataDirectory();		
		LNINT		Len = DataDir.GetByteLength();

		if ( (Len+12) <= LNMAXPATH )
		{
			memcpy(FilePath,(const char *)DataDir, (size_t)Len+1);
		}
		else
		{
			cout << "Data Directory path too long." << endl;
			return (1);
		}


#if defined(DOS) || defined(OS2) || defined(NT)  
		strcat(FilePath, "\\");
#elif defined(UNIX)
		strcat(FilePath, "/");
#endif
		strcpy (ScriptFile, FilePath);
		strcat (ScriptFile, SCRIPT_SOURCE);
		strcpy (ScriptFilePath, ScriptFile);

		//  Get the specified database and open it to gets the documents.

		Session.GetDatabase(DbFilename, &Db, DbServer);

		Db.Open();

		Db.GetDocuments(&DocArray);

		LNDocument      Doc; 
		LNRichText      Rt;
		LNRTCursor      Cursor;		
		LNINT			i,Count;
		
		
		//  Get the number of documents from db
		
		Count = DocArray.GetCount();
		
		//  Look for the specific document for this hotspot sample
		for (i=0; i<Count; i++)
		{
			Doc = DocArray[i];
			Doc.Open();
			
			LNText		Item;
			LNString	Name;

			//  Look for target doc by subject title
			if (Doc.HasItem("Subject"))
			{
				Doc.GetItem("Subject", &Item);
				Name = Item[0];

				if (Name == "Hotspot Sample Document")
				{
					Doc.GetItem("Body", &Rt);
					break;
				}
			}
		}
		
		if ( !Rt.IsNull() )
		{
			Rt.GetCursor(&Cursor);

			CreateActionHotspot(&Rt, &Cursor);
			cout << "Action Hotspots created" << endl;

			CreateButton(&Rt, &Cursor);
			cout << "Buttons created" << endl;

			CreatePopups(&Rt, &Cursor);
			cout << "Popups created" << endl;
			
			// Save and close the document

			Doc.Save();
			Doc.Close();
		}
		else
		{
			Status = LNERR_OBJECT_NOT_INITIALIZED;
			throw (Status);
		}
	}

	//  Error handler.  If an error occurred, get the text of the error
	//  message and display it.
	
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}
  
	//Close the database, free document memory.
	if (Db.IsOpen())
		Db.Close(); 

	//Terminate the API.
	Session.Term();

	char    CommandBuf[10];

	cout << endl;   
	cout << "All Done. Hit return to exit: ";
	cin.getline(CommandBuf, 10);

	//All done.
	return(0);
}


//  This function construct three action hotspots and insert them into the
//  rich text.  The first, second, third action hotspot is of type
//  LNACTIONTYPE_LOTUSSCRIPT, LNACTIONTYPE_SIMPLEACTIONS, and
//  LNACTIONTYPE_LOTUSSCRIPT consecutively.

LNSTATUS  CreateActionHotspot(LNRichText *Rt, LNRTCursor *Cursor)
{
	LNSTATUS  Status;


	//  Action Hotspot One:
	//    Contains a lotus script object which it reads the script source
	//    from an existing text file.

	//  Retrieve the Lotus Script source from a file and store it toa Buffer

	ifstream InFile(ScriptFilePath, ios::in);

	if (!InFile)
	{
		cerr << "Can't open file contains the Lotus Script source." << endl;
		return (LNERR_FILE_OPEN);
	}

	char	Buf[BUFFER_SIZE];
	int		i = (int)EOF;

	if (InFile.getline(Buf, BUFFER_SIZE, (char)i) == NULL)
	{
		cout << "Can't read the Lotus Script source." << endl;
		return (LNERR_FILE_READ);
	}

	//  Construct a lotus script object with the retrieved source

	LNLotusScript	Script(Buf);
	LNString		Label ("Script ActionHotspot");

	//  Construct an action hotspot with the lotus script object

	LNActionHotspot	Hotspot(Script, Label);

	//  Put it into the rich text body

	Rt->Insert(Hotspot, Cursor);
	Rt->Insert("\n\n", Cursor);


	//  Action Hotspot Two:
	//    Contains two LNSimpleAction objects that one sends an email and 
	//    the other run a formula which display a notified dialog box.
	

	LNSimpleSendMailAction	EMail;
	LNString				Subject = "Test Email For Action Hotspot<EOM>";

	
	//  Get the user's email name and address

	if (Status = EMail.SetToString(Session.GetUserName()))
		return (Status);

	//  Set the test email subject
	
	if (Status =  EMail.SetSubjectString(Subject))
		return (Status);
	
	//  Construct a simple action that runs a formula which display a
	//  dialog box.

	LNSimpleRunFormulaAction  Dialog;
	LNFormula		Info("@Prompt([Ok];\"Hotspot Test\";\"An email has been sent!\")");
	
	if (Status = Dialog.SetFormula(Info))
		return (Status);

	//  Construct a LNSimpleActions and store the other to LNSimpleAction to
	//  it.  This way, the action hotspot will consecutively execute the two
	//  simple action (or more if constructed) in an orderly manner which they
	//  are store.

	LNSimpleActions	Actions;

	if (Status = Actions.Append(EMail))
		return (Status);

	if (Status = Actions.Append(Dialog))
		return (Status);
	
	//  Construct the action hotspot that contains a LNSimpleActions

	LNActionHotspot	Hotspot2(Actions, "SimpleActions ActionHotspot");

	//  Put it into the rich text body

	Rt->Insert(Hotspot2, Cursor);
	Rt->Insert("\n\n", Cursor);


	//  Action Hotspot Three:
	//    Is a modified version of hotspot2 which is changed from storing
	//    LNSimpleActions to LNFormula.

	LNFormula Form("@Prompt([Ok];\"New Hotspot\";\"Hello World!\")");

	//  Set the formula to the hotspot.  This would actually change the
	//  existing LNACTIONTYPE of the hotspot to LNACTIONTYPE_FORMULA.

	if (Status = Hotspot2.SetFormula(Form))
		return (Status);

	//  Change the label for the hotspot

	if (Status = Hotspot2.SetValue("It's now a formula hotspot"))
		return (Status);

	//  Put it into the rich text body

	Rt->Insert(Hotspot2, Cursor);
	Rt->Insert("\n\n<<<\n\n", Cursor);

	return LNNOERROR;
}


//  This function construct three button and insert them into the
//  rich text.  The first, second, third action hotspot is of type
//  LNACTIONTYPE_LOTUSSCRIPT, LNACTIONTYPE_SIMPLEACTIONS, and
//  LNACTIONTYPE_LOTUSSCRIPT consecutively.

LNSTATUS  CreateButton(LNRichText *Rt, LNRTCursor *Cursor)
{
	LNSTATUS    Status;
	LNRTCursor  TempCursor;

	
	if (Status = Rt->GetCursor(&TempCursor))
		return (Status);

	//  Button One:
	//    Contains a lotus script object which it reads the script object
	//    from an existing action hotspot.

	//  Retrieve the previously constructed action hotspot to recycle
	//  the lotus script.

	LNActionHotspot	Hotspot;
	LNLotusScript	Script;

	//  Goto the first action hotspot in the rich text body

	if (Status = TempCursor.GotoFirst(LNRTTYPE_ACTION_HOTSPOT, &Hotspot))
		return (Status);

	if (Status = Hotspot.GetLotusScript(&Script))
		return (Status);


	//  Construct a button with the retrieved Lotus Script

	LNButton	Button1("Script Button", Script);
	
	Rt->Insert(Button1, Cursor);
	Rt->Insert("\n", Cursor);


	//  Button Two:
	//    Contains an LNSimpleAction 

	//  Goto the second action hotspot in the rich text body

	if (Status = TempCursor.GotoNext(LNRTTYPE_ACTION_HOTSPOT, &Hotspot))
		return (Status);

	LNSimpleActions Actions;

	//  Retrieve an array of actions

	if (Status = Hotspot.GetSimpleActions(&Actions))
		return (Status);

	//  Get the first action from that retrieved array
	
	LNSimpleAction	Action = Actions[0];

	//  Construct a new button with the action

	LNButton	button2("Hit to send email", Action);

	Rt->Insert(button2, Cursor);
	Rt->Insert("\n", Cursor);

	
	//  Button Three:
	//    Is a modified version of button2 which is changed from storing
	//    LNSimpleActions to LNFormula.

	LNFormula Form("@Prompt([Ok];\"Hello\";\"Hello World!\")");
	
	//  Change button2 to store a formula instead of simple action and
	//  update its label as well.

	if (Status = button2.SetFormula(Form))
		return (Status);

	if (Status = button2.SetLabel("This button now contains a formula"))
		return (Status);

	//  Change button2 label's font style and set its text unwrapped.

	LNFontStyle Style;
	
	Style.SetAttributes(LNFONTATTRIBUTEFLAGS_UNDERLINE);
	Style.SetColor(LNCOLOR_DARK_GREEN);				
	
	if (Status = button2.SetLabelFontStyle(Style))
		return (Status);

	if (Status = button2.SetWrapText(FALSE))
		return (Status);

	Rt->Insert(button2, Cursor);
	Rt->Insert("\n\n<<<\n\n", Cursor);

	return LNNOERROR;
}


//  This function construct three more types of hotspot.  A text popup,
//  formula popup, and url link hotspots.

LNSTATUS  CreatePopups(LNRichText *Rt, LNRTCursor *Cursor)
{
	LNSTATUS  Status;

	
	//  Construct a text popup and insert it into the rich text
	
	LNTextPopup textPop("Now you've done it!", "Click to see text");

	Rt->Insert("Text Popup:\t", Cursor);
	Rt->Insert(textPop, Cursor);
	Rt->Insert("\t\t", Cursor);

	//  Change its label and insert it again

	if (Status = textPop.SetValue("Label is modified"))
		return (Status);

	Rt->Insert(textPop, Cursor);	
	Rt->Insert("\n\n", Cursor);
	
	//  Construct a formula popup

	LNFormula Formula("@Today");
	LNString  Label("Click to see today's date");

	LNFormulaPopup FormulaPop(Formula, Label);

	Rt->Insert("Formula Popup:\t\t", Cursor);
	Rt->Insert(FormulaPop, Cursor);	
	Rt->Insert("\n\n", Cursor);

	//  Construct a url link hotspot

	LNString Address = "www.lotus.com";
	Label = "IBM Lotus Software";
	
	LNURLLink	urlLink(Address, Label);

	Rt->Insert("URL Link:\t\t", Cursor);
	Rt->Insert(urlLink, Cursor);	
	Rt->Insert("\n\n", Cursor);

	return LNNOERROR;
}


