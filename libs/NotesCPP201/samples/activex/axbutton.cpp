#include <stdafx.h>
#include <lncppapi.h>
#include "AXButton.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int LaunchSample(WORD wNotifyCode)
{
	LNNotesSession	Session;
	LNSTATUS		Lnstat = LNNOERROR;
	char *			DbFilename = "rtxtsamp.nsf";
	char *			DbServer = NULL;

	// We are only interested in the button click event.
	if(wNotifyCode != BN_CLICKED)
	{	
		return 0;
	}

	// Initialize the C++ API.
	if (Session.Init())
	{		
		AfxMessageBox("Unable to initialize Notes.", MB_OK | MB_ICONEXCLAMATION );
		return 1;
	}
	
	LNSetThrowAllErrors(TRUE);

	LNDatabase			Db;
		
	// Begin TRY Block. 
	// Throw all errors encountered during command execution.
	try 
	{	

		// Construct attachment file path.
		char    FullPathName[LNMAXPATH];

		// Check the data path length first.
		LNINT   Length = (Session.GetDataDirectory()).GetByteLength();

		if ( (Length+12) <= LNMAXPATH )
		{
			memcpy(FullPathName, Session.GetDataDirectory(), 
					(size_t)Length+1);
		}
		else
		{
			// Data directory path too long
			AfxMessageBox("Data directory path too long.", MB_OK | MB_ICONEXCLAMATION );	
			return 2;
		}


		#if defined(NT)  
			strcat(FullPathName, "\\");
		#endif
	
		strcat(FullPathName, ATTACH_FILE_NAME);

		// Get the specified database.
		Session.GetDatabase(DbFilename, &Db, DbServer);

		// Open it.
		Db.Open();
	
		LNDocument				NewDoc;
		LNString                AttachmentFile(FullPathName);
		LNString                AttachmentName("button.htm");
		LNAttachment            Attachment;
		LNRichText              RT;
		LNRTCursor     		BeginUrlCursor, EndUrlCursor;
		LNURLLink               NewLink;
		LNString                WebPage = "http://www.lotus.com";
		LNText					Subject, Author;
		
		// Create a new file in the database
		Lnstat = Db.CreateDocument(&NewDoc);
		
		// Open it
		NewDoc.Open();

		// Create the "Subject" and "From" fields.
		// Note!!! Make sure you pass in the LNITEMFLAGS_SUMMARY
		// when creating those items. Otherwise, the subject and the author
		// will not appear in the document listing.
		Subject.SetValue("ActiveX");
		Author.SetValue("Sam Sample");
		NewDoc.CreateItem("From", Author, LNITEMFLAGS_SUMMARY);
		NewDoc.CreateItem("Subject", Subject, LNITEMFLAGS_SUMMARY);

		// Let's create a compressed attachment in the document now.
		Lnstat = NewDoc.CreateAttachment(AttachmentFile, AttachmentName,
				                 TRUE, &Attachment);
		
		// Create a richtext item and turn it into a URL link to Lotus web page
		RT.Append("Take a look at Lotus web page: ");
		RT.GetEndCursor(&BeginUrlCursor);
		RT.Append("www.lotus.com");
		RT.GetEndCursor(&EndUrlCursor);
		RT.CreateURLLink(WebPage, &BeginUrlCursor, &EndUrlCursor);
		NewDoc.CreateItem("Body", RT);
		NewDoc.Save();

		// Close the document, free item memory.
		NewDoc.Close();
		
	}

	// Error handler.  If an error occurred, get the text of the error
	// message and display it.
	catch (LNSTATUS lnerror)
	{
		// If you wanted to display the error message, here's how you'd do it
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		AfxMessageBox(ErrorBuf, MB_OK | MB_ICONEXCLAMATION );
		return 1;
	}
	  
	// Close the database, free document memory.
	if (Db.IsOpen())
		Db.Close(); 		

	// Terminate the API.
	Session.Term();

	return 0;

} // END LaunchSample()

