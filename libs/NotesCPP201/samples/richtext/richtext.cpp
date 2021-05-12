
//===========================================================================
//
//      Module: RICHTEXT.CPP
//
//      Description:
//              Sample C++ API program that illustrates how to retrieve the 
//				contents of all different types of items stored in a note
//				and how to display them in rich text.
//
//      Syntax: RICHTEXT  <dbname> [<server>]
//
//		Note:
//				This sample program is designed to work with the sample 
//				database 'rtxtsamp.nsf' that is located in the 
//				notescpp\notedata directory. This database should be copied 
//				to your Notes data directory.  
//
//				You may copy the rtxtsamp.nsf database into another file and 
//				supply the new filename as the command-line argument. If you 
//				want to create another sample database to run against this
//				sample - be careful: the program looks for a specific document 
//				(called "Rich Text sample") that was created using a specific 
//				form (RichTextSample). You may encounter errors if your 
//				document is different. 
//			
//===========================================================================
//
// Copyright (c) 1997-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================


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
	char *				DbFilename;
	char *				DbServer = NULL;
	LNNotesSession		Session;
	LNDatabase			Db;
	LNDocument			CurDoc; 
	LNRichText			BodyItem; 
	LNRTCursor			Cursor;
	LNINT				Index, Count = 0;
	LNDocumentArray		DocArray;

#if defined MAC
	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line.

	char				fileBuffer[MAXPATH];
	char				serverBuffer[MAXPATH];
	
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
	
	// Prompt for parameters since they are not 
	// being passed in on the command line.
	cout << endl << "Enter database filename: " << flush;
    gets(DbFilename);
    cout << "Enter server name:  " << flush;
    gets(DbServer);
#else
	// On anything other than the Macintosh, the parameters
	// are entered on the command line.

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
#endif

	
	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try 
	{
		LNText				Subject;
		LNString			SubjectString;
		LNDatetimes			Datetime, Datetimes;
		LNDatetimeRanges	DatetimeRange, DatetimeRanges;
		LNString			TextString;
		LNRichText			RT, NewRT;
		LNDocument			NewDoc;
		LNText				NewSubject, NewAuthor;
		LNNumbers			Number, Numbers;
		LNText				Name, Names, TextItem, TextList;
		LNBOOL				IsDocFound = FALSE;
		
		/*
		Note!!!!

		You may wonder why we declared Name, Number, Datetime, DatetimeRange and 
		TextItem as lists of items. Here's the answer:

		In Notes, a text item can be stored in one of two forms: a single-valued 
		text string or a text list, which can contain multiple strings. The same 
		is true for Notes number, date/time, and date/time range items.

		The C++ API always presents these items in their list form 
		(as arrays of values). This allows C++ API programs to deal with these 
		items as if they are always lists, even if they're not actually stored 
		that way. A side effect of this feature is that the C++ API usually stores 
		items in their list form, even if they only consist of a single value.

		In most cases, Notes treats single-value items and single-entry lists as 
		the same thing. However, if you need to create a single-value item for any 
		reason, there's a way to do this: create the item outside of a note, set 
		its value, and then copy the item to the note using LNNote::CreateItem.

		*/


		// Initialize the C++ API.
		Session.Init(argc, argv);
	
		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open it.
		Db.Open();

		// Get all the documents in the database.
		Db.GetDocuments(&DocArray);

		// How many documents do we have?
		Count = DocArray.GetCount();

		// Loop through each document in the array until we find the document
		// that we want to use.
		for (Index=0; Index<Count; Index++) 
		{
			// Get the current document.
			CurDoc = DocArray[Index];

			// Open the document.
			CurDoc.Open();

			if ( CurDoc.HasItem("Subject"))
			{
				CurDoc.GetItem("Subject", &Subject);
				Subject.GetText(&SubjectString);

				if (LNStringCompare(SubjectString, "Rich Text sample") == 0)

				{	
					// Set the flag 
					IsDocFound = TRUE;

					// Create a new document in the database -
					// we'll write the output of the sample there

					// create a document that uses the 'MainTopic' as it's form
					Db.CreateDocument(&NewDoc, "MainTopic");
	
					// Open it.
					NewDoc.Open( LNNOTEOPENFLAGS_DEFAULT );

					// Create the "Subject" and "From" fields because they
					// are not created for you.
					// Note!!! Make sure you pass in the LNITEMFLAGS_SUMMARY
					// when creating those items. Otherwise, the subject 
					// and the author will not appear in the document listing
					// in the view.
					NewSubject.SetValue("Rich Text sample results");
					NewAuthor.SetValue("Sam Sample");
					NewDoc.CreateItem("From", NewAuthor, LNITEMFLAGS_SUMMARY);
					NewDoc.CreateItem("Subject", NewSubject, LNITEMFLAGS_SUMMARY);

					// Create the rich text Body field of the new document.
					NewDoc.CreateItem("Body", &NewRT);

					// Now we'll go through every item that is contained
					// in this document. For each item, we'll retrieve its
					// contents and display them in our new document that we
					// created earlier.

					// First let's retrieve the rich text from the original document
					// and append it to the new document (note that the original
					// document had the rich text at the end of the rich text body, 
					// we are inserting it in the begining of the rich text body)
					CurDoc.GetItem("Body", &RT);
					NewRT.Append("\nRichText: ");
					NewRT.Append(RT);

					NewRT.Append("\n\n");

					// Get and display the text stored in the Datetime item
					CurDoc.GetItem("Datetime", &Datetime);
					Datetime.GetText(&TextString);

					// note: we are using the default text style/font for our text 
					// string output to the document - which is different from the 
					// original style/font
					NewRT.Append("\nDatetime: ");
					NewRT.Append(TextString);

					// Repeat the same for Datetimes (a list of individual Datetime
					// items, which is treated in the same way as an individual Datetime)
					CurDoc.GetItem("Datetimes", &Datetimes);
					Datetimes.GetText(&TextString);

					NewRT.Append("\nDatetimes: ");
					NewRT.Append(TextString);

					// Retrieve and display the text stored in 
					// the DatetimeRange item
					CurDoc.GetItem("DatetimeRange", &DatetimeRange);
					DatetimeRange.GetText(&TextString);

					NewRT.Append("\nDatetime range:");
					NewRT.Append(TextString);

					// Repeat the same for DatetimeRanges (a list of 
					// individual DatetimeRange items)
					CurDoc.GetItem("DatetimeRanges", &DatetimeRanges);
					DatetimeRanges.GetText(&TextString);

					NewRT.Append("\nDatetime ranges:");
					NewRT.Append(TextString);

					// Now retrieve and display the contents of the Number item
					CurDoc.GetItem("Number", &Number);
					Number.GetText(&TextString);

					NewRT.Append("\nNumber: ");
					NewRT.Append(TextString);

					// And do the same for the list of numbers
					CurDoc.GetItem("Numbers", &Numbers);
					Numbers.GetText(&TextString);

					NewRT.Append("\nNumbers: ");
					NewRT.Append(TextString);

					// ...and the same for the Name item
					CurDoc.GetItem("Name", &Name);
					Name.GetText(&TextString);

					NewRT.Append("\nName: ");
					NewRT.Append(TextString);

					// ... and the list of names
					CurDoc.GetItem("Names", &Names);
					Names.GetText(&TextString);

					NewRT.Append("\nNames: ");
					NewRT.Append(TextString);

					// Now get the contents of the Text item 
					CurDoc.GetItem("Text", &TextItem);
					TextItem.GetText(&TextString);

					NewRT.Append("\nText: ");
					NewRT.Append(TextString);

					// And here we'll see what's stored in the TextList field
					CurDoc.GetItem("TextList", &TextList);
					TextList.GetText(&TextString);

					NewRT.Append("\nTextList: ");
					NewRT.Append(TextString);

					// Update the documents 
					CurDoc.Save();  
					NewDoc.Save();

					// Close the documents, free item memory.
					CurDoc.Close();       
					NewDoc.Close();
				}
			}
		}

		if (!IsDocFound)
		{
			cout << "Error. The document entitled \"Rich Text sample\" " << endl;
			cout << "was not found in the given database."	 << endl;
		}
	
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