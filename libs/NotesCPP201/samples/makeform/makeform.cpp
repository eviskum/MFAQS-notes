//===========================================================================
//
//      Module: MAKEFORM.CPP
//
//      Description:
//			Sample C++ API program that demonstrates how to use LNForm
//			and it's related classes to create and modify forms.
//              
//      Syntax:		MAKEFORM
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#include <iostream.h>
#include <iomanip.h>
#include <stdio.h>

// Notes C++ API headers.

#include "lncppapi.h"
#include "editdflt.h"

// These headers are only needed on the Macintosh.

#if defined(MAC)
#include <Types.h>
#include <Quickdraw.h>
#define thePort qd.thePort
#include <Dialogs.h>
#include <Menus.h>
#include <Windows.h>
#include <Fonts.h>
#include <Memory.h>
#include <stdio.h>
#endif  // defined(MAC)

char CommandBuf[80];

// Prototype definitions for this sample.

void PrintProperties(LNForm &form );
void PrintAutoLaunchSettings(LNForm &form );
void SetProperties(LNForm &form );
void SetAutoLaunchProperties(LNForm &form );

void CreateActionBar ( LNForm & sampleForm,
					   const LNString & approvalAddress,
					   const LNString &	ccList );

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
int				ProgramStatus = 0;
LNNotesSession	Session;

#if defined(MAC)
	// Initialize things for the Macintosh.
	InitGraf(&thePort);     InitFonts();
    InitWindows(); 
    InitDialogs(0);
    SetApplLimit(GetApplLimit()-8192); 
    MaxApplZone();
    MoreMasters(); 
    MoreMasters(); 
    MoreMasters();
#endif

	// Begin TRY block. 
	// Throw all errors encountered during command execution.

	LNSetThrowAllErrors (TRUE);

	try
	{
	LNDatabase	Db;
	LNForm		newform;
	LNForm		referenceform;
	LNForm		newform2;

		// Initialize the API.

		Session.Init (argc, argv);

		// Get the user of this machine to use later in the Create Action
		// Bar Function. NOTE: you could provide your own approval name,
		// and cclist and initialize them here instead for your own purposes.

		LNString user1 = Session.GetUserName();
		LNString ccusers = user1;

		// Include the following Background Graphic code for all 
		// platforms except Mac and unix.

#if !defined(UNIX) && !defined(MAC) && !defined (OS2)
		// Get the file name and path for an import Bitmap
		// that will be added in a form background later.

		LNString	bitmapfilepath;

		bitmapfilepath = Session.GetDataDirectory();
		bitmapfilepath << "/bkground.bmp";

		//  Check the file path length.

		LNINT len = bitmapfilepath.GetByteLength();

		if ( len > LNMAXPATH )
			throw "Data Directory path too long.";
#endif

		// Get the Notes database.

		Session.GetDatabase( "fdesign.ntf", &Db );

		// Open the database.

		Db.Open();

		// If this sample has been previously run, delete the forms
		// that were created by it so it can run again...

		if ( Db.FormExists("New Default Form") )
			Db.DeleteForm("New Default Form");

		if ( Db.FormExists("Brand New Form") )
			Db.DeleteForm("Brand New Form");

		cout << "*****  Getting the Master Default Form from  ******" << endl << endl;

		// Get an existing form from the database.

		Db.GetForm( "Master Default Form", &referenceform );
		referenceform.Open();

		// Print out all of the current property settings on the form.
		// This function is just below this Main() function and
		// demonstrates most of LNForm's Get methods.

		PrintProperties(referenceform);
		PrintAutoLaunchSettings(referenceform);

		cout << "***** Copying the Master Form to a new form. ******" << endl
			 << "***** Changing the name of the new form.     ******" << endl
			 << "***** Adding alias names to the new form.    ******" << endl
			 << "***** Adding a new background graphic.       ******" << endl
			 << "***** Changing the RichTextField1 name.      ******" << endl
			 << "***** Saving, closing, re-opening New Form.  ******" << endl
			 << endl;

		// Use the copy constructor to copy the existing form to newform.

		Db.CreateForm(referenceform, &newform);						
		newform.Open();

		// Close the reference form.  We will use the newform as the 
		// copy of it from now on.

		referenceform.Close();

		// Set the name of this copied form. Add in alias names too...

		newform.SetName("New Default Form | $DForm1 | simpleform");

		// Include the following Background Graphic code for all 
		// platforms except Mac and unix.

#if !defined(UNIX) && !defined(MAC) && !defined (OS2)
		// Get a background graphic from the bitmap file we set above...

		LNRichText	rt;
		LNRTCursor	cursor;
		LNGraphic	graphic;

		rt.GetCursor( &cursor);
		rt.Import( bitmapfilepath, &cursor );
		cursor.GotoFirst( LNRTTYPE_GRAPHIC, &graphic );

		// Set the background graphic for this form.

		newform.SetBackgroundGraphic( graphic );
#endif

		// Change the static text heading for this copied form. 
		// Change the default color for the form's text to stand
		// out against the background etc.

		LNRichText	formbody1;
		LNRTCursor	cursor1;
		LNRTCursor	cursor2;
		LNFontStyle	fs1;

		// Get the Form $Body some cursors, and the fontstyle.

		newform.GetFormBody ( &formbody1 );
		formbody1.GetCursor( &cursor1 );
		formbody1.GetCursor( &cursor2 );
		formbody1.GetFontStyle( cursor1, &fs1 );
		fs1.SetColor( LNCOLOR_YELLOW );

		// Replace the string "Master Default Form"
		// With the string "New Default Form"

		cursor1.GotoFirst( "Master Default" );
		cursor2.GotoFirst( "Default Form" );
		formbody1.Delete( &cursor1, &cursor2 );
		formbody1.Insert( "New ", &cursor1 );

		// Replace the string "Basic Form created with UI"
		// With the string "Copy of Master Default Form"

		cursor1.GotoFirst( "Basic Form" );
		cursor2.GotoFirst( ")" );
		formbody1.Delete( &cursor1, &cursor2 );
		formbody1.Insert( "Copy of Master Default Form", &cursor1 );

		// Reset cursors to start and end of $Body item.
		// and set the over all font style.

		formbody1.GetCursor( &cursor1 );
		formbody1.GetEndCursor( &cursor2 );
		formbody1.SetFontStyle( cursor1, cursor2, fs1 );

		// Change font point size for the field headings.

		cursor1.GotoFirst( "Text Field 1" );
		fs1.SetPointSize( 12 );
		formbody1.SetFontStyle( cursor1, cursor2, fs1 );

		// Get the RichTextFeld1 and change it's name just for kicks.

		LNFormField		rtField;
		newform.GetFormField("RichTextField1", &rtField);
		rtField.SetName("NewRichTextField");
		
		// Save, Close and re-open the new form just for fun.

		newform.Save();
		newform.Close();
		newform.Open();

		// Print out the properties of this new form now that it has been
		// refreshed to disk.

		PrintProperties(newform);
		PrintAutoLaunchSettings(newform);

		//
		// **** The next section creates a brand new form from scratch ****
		//

		cout << endl << endl << "*****************************************************" << endl;
		cout << "***** Now Create a brand new form from scratch ******" << endl;
		cout << "*****************************************************" << endl << endl;

		// Now Create a brand new (default) form from scratch.

		Db.CreateForm( "Brand New Form", &newform2 );

		// Print out all of the current property settings on the form.

		PrintProperties(newform2);
		PrintAutoLaunchSettings(newform2);

		cout << "***** Changing some properties on this form. ******" << endl << endl;

		// make some changes (calls to Set functions)

		SetProperties(newform2);

		cout << "***** Creating a new rich text form field, ******" << endl
			 << "***** and inserting it into the form.      ******" << endl
			 << "***** Adding a static text heading above   ******" << endl
			 << "***** the rich text field.  Setting auto   ******" << endl
			 << "***** launch features for this form.       ******" << endl
			 << endl;

		// Create a new rich text form field and insert it
		// Into the form $Body item, with a static text
		// heading above it.  Use Cursors, Fontstyle etc...

		LNRichText	formbody;
		LNRTCursor	startcursor;
		LNRTCursor	endcursor;
		LNFontStyle	fs;

		newform2.GetFormBody ( &formbody );

		formbody.Append( "Here is a New Rich Text Field Created using the C++ API" );

		formbody.GetCursor( &startcursor );
		formbody.GetEndCursor( &endcursor );

		fs.SetColor( LNCOLOR_DARK_BLUE );
		fs.SetFaceID( LNFACEID_ROMAN );
		fs.SetPointSize( 24 );
		fs.SetAttributes( LNFONTATTRIBUTEFLAGS_BOLD );

		formbody.SetFontStyle( startcursor, endcursor, fs );
		formbody.StartNewParagraph( &endcursor );

		formbody.CreateFormField( "RichTextField1", LNRTTYPE_RICH_TEXT_FIELD, &endcursor );

		// Set up some of the Auto Launch features.  Use RichTextField1 as
		// The richtext field for the launch OLE object in field.

		SetAutoLaunchProperties(newform2);

		// Change the background color of this form.

		newform2.SetBackgroundColor(LNCOLOR_RED);

		cout << "***** Saving, closing, and re-opening it. ******" << endl << endl;

		// Create an Action Bar and insert it into the form.

		CreateActionBar ( newform2, user1, ccusers );

		// Save, Close and re-open the brand new form just for fun.

		newform2.Save();
		newform2.Close();
		newform2.Open();

		// Print out all the form property settings now...

		PrintProperties(newform2);
		PrintAutoLaunchSettings(newform2);

		// Close the Brand New form for the last time...

		newform2.Close();

		// Close the database, we are all done now...

		Db.Close();

		cout << "***** Notes Template file: Fdesign.ntf is  ******" << endl
			 << "***** modified and two new forms have been ******" << endl
			 << "***** added.  You can open it with Notes   ******" << endl
			 << "***** Designer for Domino to examine it.   ******" << endl
			 << endl << "All Done.  ";

		ProgramStatus = 0;

	} // END try

	catch (LNSTATUS lnerror)
	{
	char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(lnerror, ErrorBuf, LNERROR_MESSAGE_LENGTH);
		cout << "\nError:  " << ErrorBuf << endl;
		ProgramStatus = 2;
	}

	catch (const char *pErrorMessage)
	{
		cout << "\nError: " << pErrorMessage << endl << endl;
		ProgramStatus = 1;
	}

	cout << "Hit return to exit: ";
	cin.getline(CommandBuf, 50);

	// Terminate the API.
	Session.Term();

	return (ProgramStatus);

} // END MAIN

//---------------------------------------------------------------------------
//
// Name:
//		PrintProperties
//
// Description:
//		Prints out various LNForm Properties.
//
//---------------------------------------------------------------------------

void PrintProperties(LNForm &form )
{
LNFormula formula;

	cout << "***** Current Properties on Form: [" << form.GetName() << "] ******" << endl << endl;
	cout << "Form Alias names:               [" << form.GetAlias() << "]" << endl;

	form.GetWindowTitleFormula( &formula );
	LNString code = formula.GetText();
	cout << "Window Title Formula:           [" << code << "]" << endl;

	cout << hex;

	cout << "GetIncludeInMenuOption:         [" << (LNINT)form.GetIncludeInMenuOption() << "]" << endl;
	cout << "GetFormType:                    [" << (LNINT)form.GetFormType() << "]" << endl;
	cout << "GetIncludeInSearchBuilder:      [" << form.GetIncludeInSearchBuilder() << "]" << endl;
	cout << "GetIsAnonymousForm:             [" << form.GetIsAnonymousForm() << "]" << endl;
	cout << "GetMergeReplicationConflicts:   [" << form.GetMergeReplicationConflicts() << "]" << endl;
	cout << "GetCreateVersionsAutomatically: [" << form.GetCreateVersionsAutomatically() << "]" << endl;
	cout << "GetVersioningOption:            [" << (LNINT)form.GetVersioningOption() << "]" << endl;
	cout << "GetRefreshFieldsAutomatically:  [" << (LNINT)form.GetRefreshFieldsAutomatically() << "]" << endl;
	cout << "GetContextPaneOption:           [" << (LNINT)form.GetContextPaneOption() << "]" << endl;
	cout << "GetDisableFieldExchange:        [" << form.GetDisableFieldExchange() << "]" << endl;
	cout << "GetEditOnOpen:                  [" << form.GetEditOnOpen() << "]" << endl;
	cout << "GetInheritDocumentOption:       [" << (LNINT)form.GetInheritDocumentOption() << "]" << endl;
	cout << "GetInheritDocumentFieldName:    [" << form.GetInheritDocumentFieldName() << "]" << endl;
	cout << "GetInheritFormulaValues:        [" << form.GetInheritFormulaValues() << "]" << endl;
	cout << "GetIsDefaultForm:               [" << form.GetIsDefaultForm() << "]" << endl;
	cout << "GetShowMailSendOnClose:         [" << form.GetShowMailSendOnClose() << "]" << endl;
	cout << "GetStoreFormInDocument:         [" << form.GetStoreFormInDocument() << "]" << endl;
	cout << "GetTreatContentsAsHTML:         [" << form.GetTreatContentsAsHTML() << "]" << endl;
	cout << "GetAllowAllAuthors:             [" << form.GetAllowAllAuthors() << "]" << endl;
	cout << "GetAllowAllReaders:             [" << form.GetAllowAllReaders() << "]" << endl;
	cout << "GetAllowPublicAccessUsers:      [" << form.GetAllowPublicAccessUsers() << "]" << endl;

	cout << dec;

	// Get the default encryption keys. (there may not be any for this form so you have to check it!)
	LNText keys = form.GetDefaultEncryptionKeys();

	// Make sure this form contains encryption keys before trying to use or look at them.
	if (!keys.IsNull())
		cout << "GetDefaultEncryptionKeys:       [" << (LNString)keys[0] << "]" << endl;

	cout << "GetDisablePrintingAndCopying:   [" << form.GetDisablePrintingAndCopying() << "]" << endl;
	cout << endl << "The list of Authors follows:" << endl << endl;

	LNText authorslist = form.GetAuthors();
	LNINT count = authorslist.GetCount();
	LNINT i;

	for (i=0; i<count; i++)
		cout << "     Author:     [" << i << "] " << "= " << "[" << (LNString)authorslist[i] << "]" << endl;

	cout << endl << "The list of Readers follows:" << endl << endl;

	LNText readerslist =  form.GetReaders();
	count = readerslist.GetCount();
	for (i=0; i<count; i++)
		cout << "     Reader:     [" << i << "] " << "= " << "[" << (LNString)readerslist[i] << "]" << endl;

	cout << "Hit return to continue: ";
	cin.getline(CommandBuf, 50);
	cout << endl;

} // END PrintProperties()

//---------------------------------------------------------------------------
//
// Name:
//		PrintAutoLaunchSettings
//
// Description:
//		Prints out the Auto Launch Settings on the form.
//
//---------------------------------------------------------------------------

void PrintAutoLaunchSettings(LNForm &form )
{
LNFormula formula;
LNString code;

	cout << "***** Auto Launch Settings on Form: [" << form.GetName() << "] ******" << endl << endl;

	cout << hex;

	cout << "GetAutoLaunchObjectType:        [" << (LNINT)form.GetAutoLaunchObjectType() << "]" << endl;
	cout << "GetLaunchOLEObjectInPlace:      [" << form.GetLaunchOLEObjectInPlace() << "]" << endl;
	cout << "GetCreateObjectInFieldOption:   [" << (LNINT)form.GetCreateObjectInFieldOption() << "]" << endl;
	cout << "GetCreateObjectInFieldName:     [" << form.GetCreateObjectInFieldName() << "]" << endl;
	cout << "GetLaunchObjectWhenFlags:       [" << form.GetLaunchObjectWhenFlags() << "]" << endl;
	cout << "GetHideDocumentWhenFlags:       [" << form.GetHideDocumentWhenFlags() << "]" << endl;
	cout << "GetPresentDocumentAsDialog:     [" << form.GetPresentDocumentAsDialog() << "]" << endl;

	cout << dec;

	cout << "Hit return to continue: ";
	cin.getline(CommandBuf, 50);
	cout << endl;

} // END PrintAutoLaunchSettings()

//---------------------------------------------------------------------------
//
// Name:
//		SetProperties
//
// Description:
//		Sets various LNForm Properties.
//
//---------------------------------------------------------------------------

void SetProperties(LNForm &form )
{
	form.SetAlias("NewAlias1|NewAlias2|Newalias3");

	form.SetInheritDocumentOption( LNINHERITDOCOPTION_RICH_TEXT );

	form.SetInheritDocumentFieldName("RichTextField1");

	form.SetTreatContentsAsHTML(TRUE);

	form.SetWindowTitleFormula( "@Text(\"NewForm: The Window Title has been changed!\")" );

	LNText authorslist;
	
	authorslist << "John Steinbeck";
	authorslist << "Philip K. Dick";
	authorslist << "Max V. Mathews";
	authorslist << "T.S. Eliot";
	authorslist << "Issac Asamov";
	authorslist << "Mark Twain";
	authorslist << "Jonathan Swift";

	form.SetAuthors(authorslist);

	LNText readerslist;
	
	readerslist << "Evelyn Wood";
	readerslist << "James Cagney";
	readerslist << "Duke Ellington";
	readerslist << "Bela Bartok";
	readerslist << "Steve Jobs";
	readerslist << "John Kennedy";
	readerslist << "Lenard Nemoy";

	form.SetReaders(readerslist);

	cout << "Properties for [" << form.GetName() << "] have been modified..." << endl << endl;

	cout << "Hit return to continue: ";
	cin.getline(CommandBuf, 50);
	cout << endl;

} // END SetProperties()

//---------------------------------------------------------------------------
//
// Name:
//		SetAutoLaunchProperties
//
// Description:
//		Sets various LNForm Auto Launch Properties.
//
//---------------------------------------------------------------------------

void SetAutoLaunchProperties(LNForm &form )
{
	// Set object type to OLE

	form.SetAutoLaunchObjectType( LNAUTOLAUNCHOBJECTTYPE_OLE_OBJECT );

	form.SetLaunchOLEObjectInPlace( TRUE );

	form.SetLaunchObjectWhenFlags( LNLAUNCHOBJECTWHENFLAGS_CREATING | 
								   LNLAUNCHOBJECTWHENFLAGS_EDITING    );

	form.SetCreateObjectInFieldOption( LNCREATEOBJECTINFIELDOPTION_NAMED_RT_FIELD );

	form.SetCreateObjectInFieldName( "RichTextField1" );

	cout << "Auto Launch Properties for [" << form.GetName() << "] have been modified..." << endl << endl;
	cout << "Hit return to continue: ";
	cin.getline(CommandBuf, 50);
	cout << endl;

} // END SetAutoLaunchProperties()

//----------------------------------------------------------------------
//
//	Function:
//		CreateActionBar
//
//	Description:
//		Create the action bar for the sample formula and "Approve"/"Deny"
//		actions.
//
//	Inputs:
//		sampleForm - Form to which the actions will be added
//		approvalAddress - Mail address to which approvals should be sent
//		ccList - List of people who receive copies of approve/deny messages.
//
//	Outputs:
//		None.
//
//	Returns:
//		None.
//
//	Remarks:
//		None.
//
//----------------------------------------------------------------------

void CreateActionBar (
	LNForm & sampleForm,
	const LNString &	approvalAddress,
	const LNString &	ccList
) {
	LNActions		actionArray;

		// Get the current set of actions
	sampleForm.GetActions (&actionArray);

		// Create an action that runs a formula
	{
		LNFormula		sampleFormula ("@Prompt([OK];\"Sample formula\";\"Running formula\")");
		LNAction		formulaAction ("Formula Action", sampleFormula);

			// Set the display attributes for the action
		formulaAction.SetIconIndex (12);
		formulaAction.SetShowInButtonBar (TRUE);
		formulaAction.SetShowInMenu (TRUE);

			// Add the action to the actions array
		actionArray.Append (formulaAction);
	}

		// Create the "Approve" operations
	{
		LNSimpleActions	approveSteps;

			// First step - send "Approve" message
		{
			LNSimpleSendMailAction	sendApproveMail;

			sendApproveMail.SetToString (approvalAddress);
			sendApproveMail.SetCCString (ccList);
			sendApproveMail.SetSubjectString ("Request approved");
			sendApproveMail.SetMessageBody ("This request has been approved.");
			sendApproveMail.SetIncludeDocument (TRUE);
			sendApproveMail.SetSaveMessage (TRUE);

				// Add to the set of simple actions
			approveSteps.Append (sendApproveMail);
		}

			// Second step - send reply to requestor
		{
			LNSimpleSendReplyAction	sendApproveReply;

			sendApproveReply.SetMessageBody ("This request has been approved.");
			sendApproveReply.SetIncludeDocument (TRUE);
			sendApproveReply.SetSaveMessage (FALSE);

				// Add to the list of simple actions
			approveSteps.Append (sendApproveReply);
		}

			// Final step - file in the "Approved Requests" folder
		{
			LNSimpleFolderAction	fileApproval (LNSIMPLEACTIONTYPE_MOVE_TO_FOLDER);

			fileApproval.SetCreateNewFolder (TRUE);
			fileApproval.SetPrivateFolder (TRUE);
			fileApproval.SetFolderName ("Approved Requests");

				// Add to the set of simple actions
			approveSteps.Append (fileApproval);
		}

		// The approval steps are ready to add!
		LNAction	approveAction ("Approve Request", approveSteps);

			// Set the display attributes for the action
		approveAction.SetIconIndex (15);
		approveAction.SetShowInButtonBar (TRUE);
		approveAction.SetShowInMenu (TRUE);

			// Add the action to the actions array
		actionArray.Append (approveAction);
	}

		// Create the "Deny" operations
	{
		LNSimpleActions	denySteps;

			// First step - send reply to requestor
		{
			LNSimpleSendReplyAction	sendDenyReply;

			sendDenyReply.SetMessageBody (
				"This request has been DENIED.  Call me if you wish to discuss this.");
			sendDenyReply.SetIncludeDocument (TRUE);
			sendDenyReply.SetSaveMessage (TRUE);

				// Add to the list of simple actions
			denySteps.Append (sendDenyReply);
		}

			// Final step - file in the "Denied Requests" folder
		{
			LNSimpleFolderAction	fileDenial (LNSIMPLEACTIONTYPE_MOVE_TO_FOLDER);

			fileDenial.SetCreateNewFolder (TRUE);
			fileDenial.SetPrivateFolder (TRUE);
			fileDenial.SetFolderName ("Denied Requests");

				// Add to the set of simple actions
			denySteps.Append (fileDenial);
		}

		// The approval steps are ready to add!
		LNAction	denyAction ("Deny Request", denySteps);

			// Set the display attributes for the action
		denyAction.SetIconIndex (16);
		denyAction.SetShowInButtonBar (TRUE);
		denyAction.SetShowInMenu (TRUE);

			// Add the action to the actions array
		actionArray.Append (denyAction);
	}

		// Store the new set of actions
	sampleForm.SetActions (actionArray);

	cout << "A New Action Bar for [" << sampleForm.GetName() << "] has been created..." << endl << endl;
	cout << "Hit return to continue: ";
	cin.getline(CommandBuf, 50);
	cout << endl;

} // END CreateActionBar()

// END Makeform sample application.


