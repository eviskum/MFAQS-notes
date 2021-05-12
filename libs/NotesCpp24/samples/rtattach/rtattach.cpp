//===========================================================================
//
//      Module: RTATTACH.CPP
//
//      Description:
//              This program illustrates how to insert attachments in the
//              rich text item of a document in a database file.
//
//      Syntax: RTATTACH <dbname> [server]
//              example: RTATTACH RTXTSAMP.NSF
//
//		Note:
//				This sample program is designed to work with the sample 
//				database RTXTSAMP.NSF and the sample TIFF image file 
//				IMAGE.TIF, in the notescpp/notedata directory.  Copy these 
//				files to your Notes data directory.  
//
//===========================================================================

#include <iostream.h>
#include <lncppapi.h>

#define ERR_BUF_SIZE			512
#define ATTACH_FILE_NAME        "image.tif"


int main(int argc, char *argv[])
{
	char *				DbFilename;
	char *				DbServer = NULL;
	LNNotesSession		Session;
	LNDatabase			Db;

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
	
	// Throw all errors encountered during command execution.
	LNSetThrowAllErrors (TRUE);
		
	// Begin TRY block. 

	try 
	{	
		LNDocument      NewDoc; 
		LNRichText      RT;
		LNRTCursor      Cursor;
		LNRTAttachment	RTAttachment, RTNamedAttachment;
		LNAttachment	Attachment;
		LNString		SubjectString;
		LNTable			Table;
		LNTableCell		Cell;
		LNText			Author, Subject;
		
		
		// Construct Attachment file path.
		char	FullPathName[LNMAXPATH];

		// Initialize the C++ API.
		Session.Init(argc, argv);

		// Check the data path length first.
		LNINT   Length = (Session.GetDataDirectory()).GetByteLength();

		if ( (Length+12) <= LNMAXPATH )
		{
			memcpy(FullPathName, Session.GetDataDirectory(), (size_t)Length+1);
		}
		else
		{
			cout << "Data Directory path too long." << endl;
			return (1);
		}


		#if defined(DOS) || defined(OS2) || defined(NT)  
		strcat(FullPathName, "\\");
		#elif defined(MAC)
		//  strcat(FullPathName, ":");  
		//  not needed, colon included in string already.
		#elif defined(UNIX)
		strcat(FullPathName, "/");
		#endif
		strcat(FullPathName, ATTACH_FILE_NAME);

		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open it.
		Db.Open();
		
		// Create a new document in the database, make it a MainTopic form
		Db.CreateDocument(&NewDoc, "MainTopic");

		// Create the "Subject" and "From" fields.
		// Note!!! Make sure you pass in the LNITEMFLAGS_SUMMARY
		// when creating those items. Otherwise, the subject and the author
		// will not appear in the document listing.
		Subject.SetValue("Rtattach");
		Author.SetValue("Sam Sample");
		NewDoc.CreateItem("From", Author, LNITEMFLAGS_SUMMARY);
		NewDoc.CreateItem("Subject", Subject, LNITEMFLAGS_SUMMARY);
	
		NewDoc.CreateItem("Body", &RT);
		RT.Append("Here are the attachments: \n\n");
		NewDoc.Save();		
						

		// First we'll demonstrate how to use LNNote class to create LNAttachment.
		// We will need this attachment for later examples of RTAttachment.		
		
		NewDoc.CreateAttachment(FullPathName, &Attachment); 

		// You can now save the document to take a look at it 
		// to make sure that the attachment is there.
		// In general, however, you don't need a Save here.
		// Save is a costly operation, and it needs to be done only 
		// once before you close the document.
		NewDoc.Save();
		
		cout << " Created LNAttachment in the note !! " << endl;

		// Now we'll demonstrate how to work with RichText Attachments.
		// LNRichText::CreateAttachment() has 4 overloaded versions, and they are
		// analogous to LNRTContainer::CreateAttachment(). So we'll give 2 examples
		// from LNRichText and 2 examples from LNRTContainer

		// We'll start with creating a regular attachment using LNRichText class.

		// Has the rich text item been closed?
		try
		{
			// Get a cursor pointing at the end of the rich text.
			RT.GetEndCursor(&Cursor);
		}
		catch (LNSTATUS error)
		{
			if (LNERR_OBJECT_CLOSED != error)
				throw (error);
			else
			{
				// The rich text item has been updated;  get the new item
				NewDoc.GetItem("Body", &RT);
				RT.GetEndCursor(&Cursor);
			}
		}

		// Insert comments to specify which attachment it is.
		RT.Insert("  RT Attachment goes here --->> ", &Cursor);
		
		// Insert an attachment in the rich text item.
		RT.CreateAttachment(FullPathName, &Cursor, &RTAttachment);
				
		cout << " Created the attachment in the rich text item !! " << endl;

		// Insert some text after the attachment in the rich text item.
		RT.Insert(" <<---  End of RT Attachment.\n\n", &Cursor);


		// Let's check the file name of the RT attachment being created.
		LNString AttachmentFileName = RTAttachment.GetFilepath();
		cout << " Attachment File Name Is: "  << AttachmentFileName << endl;

		// Now we'll show how to use another version of the 
		// LNRichText::CreateAttachment() method to create a named attachment

		// Let's create 2 attachments and give them names

		RT.Append("  RT named Attachment goes here --->> ");
		RT.GetEndCursor(&Cursor);
		RT.CreateAttachment(FullPathName, &Cursor, "Flowers1", TRUE, &RTNamedAttachment);
		RT.Append(" <<---  End of RT named Attachment.\n\n");

		RT.Append("  RT named Attachment used to be here --->> ");
		RT.GetEndCursor(&Cursor);
		RT.CreateAttachment(FullPathName, &Cursor, "Flowers2", TRUE, &RTNamedAttachment);
		RT.Append(" <<---  End of RT named Attachment.\n\n");

		// Now let's delete one of the named attachments.

		RT.DeleteAttachment("Flowers2");


		// Now we'll shift to LNRTContainer. 
		// Let's create a table and insert the attachments into some of the cells

		// Get the cursor pointing at the end of the rich text item.
		RT.GetEndCursor(&Cursor);

		// Create a table.
		// Note!!! You should use LNRichText::CreateTable() method here, as opposed to
		// simply calling a constructor on LNTable class and then inserting the table
		// into the rich text because LNRichText::CreateTable() method is more 
		// efficient.
		RT.CreateTable(2, 2, &Cursor, &Table);
		
		// Choose a cell
		Cell = Table(0, 0);

		// Get a cursor pointint at the beginning of the cell
		Cell.GetCursor(&Cursor);
		
		// Use a copy constructor to create an attachment from the LNAttachment
		// that we created earlier.
		Cell.CreateAttachment(FullPathName, &Cursor);

		cout << " Created a rich text attachment from LNAttachment!!" << endl;

		// Append a comment
		Cell.Append("\nThis is a rich text attachment created\n from LNAttachment by LNRTContainer\n"); 


		// Now we'll demonstrate another version of LNRTContainer::CreateAttachment().
		// It will be a copy constructor that constructs a rich text attachment from
		// another rich text attachment.

		// Choose another cell.
		Cell = Table(1, 1);

		// Get a cursor pointing at the beginning of the cell.
		Cell.GetCursor(&Cursor);

		// Create the attachment
		Cell.CreateAttachment(FullPathName, &Cursor);

		cout << " Created a rich text attachment from another rich text attachment!!" << endl;

		// Append a comment
		Cell.Append("\nThis is a rich text attachment created\n from RTAttachment by LNRTContainer\n"); 

		// And save the document.
		NewDoc.Save();
			
		// Close the document, free item memory.
		NewDoc.Close();
		
	} // END try	
		

	// Error handler.  If an error occurred, get the text of the error
	// message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}
	  
	// Close the database, free document memory.
	if (Db.IsOpen())
		Db.Close(); 

	// Terminate the API.
	Session.Term();

	char    CommandBuf[10];

	cout << endl;   
	cout << "All Done. Hit return to exit: ";
	cin.getline(CommandBuf, 10);

	// All done.
	return(0);

  }	// END main