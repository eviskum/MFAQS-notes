/****************************************************************************

	Copyright (c) 1998 Lotus Development Corporation

	Program:    FDESIGN

	File:       FDESIGN.CPP

	Syntax:     fdesign [fdesign.ntf [<server>]]

	Comment:    Note that the sample works with *.ntf (not *.nsf) file.

	Description:
		This program illustrates how to manipulate and change the design of
		a form in a specified template database.  It makes an exact copy of 
		the "master" form, and then makes changes to the copy, inserting new
		fields and subforms and adjusting properties of the existing design 
		elements of the copy.

****************************************************************************/


#include <iostream.h>
#include <lncppapi.h>

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

int main(int argc, char *argv[])
{
	char *                          DbFilename;
	char *                          DbServer = NULL;
	LNNotesSession                  Session;

#if defined MAC

	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line.

	char                    fileBuffer[MAXPATH];
	char                    serverBuffer[MAXPATH];
	
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
   
	DbFilename = fileBuffer;
	DbServer = serverBuffer;
	
	// Prompt for parameters since they are not being passed in on the command line.
	cout << endl << "Enter database filename: " << flush;
	gets(DbFilename);
	cout << "Enter server name:  " << flush;
	gets(DbServer);
#else
	// On anything other than the Macintosh, the parameters
	// are entered on the command line.

	// Check the command line.
	if ( argc > 3) 
	{
		cout << "\nUsage:\t" << "fdesign"
		<< " [fdesign.ntf [<server>]] \n"
		<< endl;
		return(1); 
	}

	// Get info from command line.
	if ( argc == 1 ) 
		DbFilename = (char *) "fdesign.ntf";
	else 
		DbFilename = argv[1];
	
	if (argc == 3)
		DbServer = argv[2];
#endif

	cout << "\nRunning FDESIGN..." << endl;

	// Initialize the C++ API.
	if (Session.Init(argc, argv))
	{
		cout << "\nUnable to initialize the API" << endl;
		return(2);
	}

	LNDatabase                      Db;

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try 
	{
		LNForm                          form, createdForm;
		LNRTSubform                     rtSubform;

		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open it.
		Db.Open();

		// Get and open the master form. 
		// We can use alias instead of the name here
		Db.GetForm("$MasterFieldsForm", &form);
		form.Open();

		// Create a copy of this form with the name "Created Form"
		// First clean up.
		if(Db.FormExists("Created Form with Fields and a Subform"))
			Db.DeleteForm("Created Form with Fields and a Subform");

		Db.CreateForm(form, &createdForm);

		// We don't need Master Form any more...
		form.Close();

		// createdForm is the exact in-memory copy of the original form
		// including its name and aliases.
		// We want to set new name and alias.
		createdForm.Open();

		createdForm.SetName("Created Form with Fields and a Subform");
		createdForm.SetAlias("$CreatedForm");

	// Now we are going to change some existing design elements
	// of the form, and add some new ones. 

	// I. Adjust a regular field

		// Find the regular keywords field by name:
		LNKeywordsField kwField;
		LNRichText      createdFormBodyItem;
		createdForm.GetFormBody(&createdFormBodyItem);

		createdFormBodyItem.GetFormField("keywordsField", &kwField);

		// Change some properties, say the list of choices and the name:
		LNText list;
		list << "Boston" << "Cambridge" << "Beverly";
		kwField.SetChoicesList(list);
		kwField.SetChoicesOption(LNKWCHOICES_LIST);
		kwField.SetName("ModifiedKeywordsField");
		kwField.SetDontDisplayHelperButton(FALSE);

	// II. Modify the first shared field in the form

		// Find the first shared field of a particular type in the form 
		LNRTCursor cursor;
		LNBOOL bFound = FALSE;
		LNSharedField sharedfield;

		createdFormBodyItem.GetCursor(&cursor);
		LNFormField field; 

		while(LNWARN_NOT_FOUND != cursor.GotoFirst(LNRTTYPE_TIME_FIELD, &field))
		{
			if(field.IsShared())
			{
				bFound = TRUE;
				break;
			}
		}

		if(bFound)
		{
		// We are going to change some propertries of this shared field and save
		// it under a different name.
		// Clean up first...
			if(Db.SharedFieldExists("ModifiedTimeSharedField"))
				Db.DeleteSharedField("ModifiedTimeSharedField");

			// Create new shared field based on the form field
			LNSharedField newSharedField;
			Db.CreateSharedField(field, &newSharedField); 

			// Change name
			newSharedField.SetName("ModifiedTimeSharedField");

			// Now we want to substitute the original field in the form with this one
			createdFormBodyItem.Delete(&cursor,1);
			createdFormBodyItem.InsertSharedField(newSharedField, &cursor, &field);

			// Now field points to the new shared field. Let us use it
			// to change some other property. The property will be changed
			// both in shared field note, and in the form containing the shared field.
			field.SetValueFormula("@Modified");
		}

	// III. Substitute first subform in the form with the new one, based on
	//      the original, but with additional field in it.
		
		// Get the first subform in the form
		cursor.GotoFirst(LNRTTYPE_SUBFORM, &rtSubform);

		// We don't want to change original subform, so let's create a new one
		// based on the content of the original.
		LNSubform subform, createdSubform;
		rtSubform.GetSubform(&subform);
		Db.CreateSubform(subform, &createdSubform);

		// First clean up
		if(Db.SubformExists("Created Yellow Gradient"))
			Db.DeleteSubform("Created Yellow Gradient");

		// Set the new name and alias.
		createdSubform.SetName("Created Yellow Gradient");
		createdSubform.SetAlias("&YellowMemoAddress");

		LNRichText subformBodyItem;
		createdSubform.GetSubformBody(&subformBodyItem);

		// Insert new field in the created subform as the very first
		// rich text element
		LNFormField subformField;

		LNRTCursor subformCursor;
		subformBodyItem.GetCursor(&subformCursor);
		subformBodyItem.CreateFormField("CreatedSubformField", 
			LNRTTYPE_TEXT_FIELD, &subformCursor, &subformField);

		// Make it computed and add some help description
		subformField.SetComputeOption(LNCOMPUTEOPTION_COMPUTED);
		subformField.SetValueFormula("\"Time and Date :  \"");
		subformField.SetHelpDescription("This is a title field");

		// Now we want to substitute the original subform in the form with this one
		createdFormBodyItem.Delete(&cursor,1);
		createdFormBodyItem.InsertSubform(createdSubform, &cursor, &rtSubform);

		// Save and close
		createdForm.Save();
		createdForm.Close();
	}

	// Error handler.  If an error occurred, get the text of the error
	// message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}
		
	// Close the database, free document memory.
	Db.Close(); 

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);    

	// Terminate the API.
	Session.Term();
	
	// All done.
	return(0);
}

