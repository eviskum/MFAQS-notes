//===========================================================================
//
//	Module: LINKDEMO.CPP
//
//	Description:
//		Sample C++ API program that demonstrates the use of the
//		rich text classes:
//
//			LNLinkHotspot
//			LNDatabaseLink
//			LNViewLink
//			LNDocumentLink
//
//	Syntax:	LINKDEMO
//
//===========================================================================
#include <iostream.h>
#include <stdio.h>

// Notes C++ API headers.
#include "lncppapi.h"
#include "editdflt.h"

#include "lnlinks.hpp"

char CommandBuf[80];

void ProcessLinks( LNDocument *SrcDoc, LNDocument *DestDoc,  
				   LNDatabaseLink *SrcDBLink, LNDatabaseLink *DestDBLink );

LNBOOL SearchDocument( const LNDocument &Doc, 
					   const LNString &FieldName, 
					   const LNString &SearchStr  );

void PrintTimeDate( TIMEDATE *td );
void PrintUNID( UNID *unid );

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main( int argc, char *argv[] )
{
int				ProgramStatus = 0;
LNNotesSession	Session;

	// Throw all errors encountered during command execution.
	LNSetThrowAllErrors (TRUE);

	try
	{
	LNDatabase		SrcDB;
	LNDatabase		DestDB;
	LNDocumentArray DocArray;
	LNDocument		SrcDoc;
	LNDocument		DestDoc;
	LNINT			Index;
	LNINT			Count;
	LNBOOL			IsDocFound;

		// Initialize the API.
		Session.Init (argc, argv);

		// Get the source Notes database.
		Session.GetDatabase( "linkdemo.nsf", &SrcDB );

		// Get the destination Notes database.
		Session.GetDatabase( "rtsample.nsf", &DestDB );

		// Open the source database.
		SrcDB.Open();

		// Get an array of all the docs in the database.
		SrcDB.GetDocuments( &DocArray );

		// Search all the documents in the array for the 
		// source document we are to test against.
		IsDocFound = FALSE;
		Count = DocArray.GetCount();
		for (Index = 0; Index<Count; Index++)
		{
			// Get the next document in the array.
			SrcDoc = DocArray[Index];

			// Open it.
			SrcDoc.Open( LNNOTEOPENFLAGS_DEFAULT );

			if ( SrcDoc.HasItem("Body") )
			{
				// This document has a body field, so search for the string in it.
				if ( SearchDocument( SrcDoc, "Body", "*Here are some links for testing*" ) )
				{
					// Document was found; leave the loop now without closing the doc.
					IsDocFound = TRUE;
					break;
				}
			}
		
			SrcDoc.Close();
		}

		if (!IsDocFound)
			throw ("Could not find the source document needed for this demo!");

		// Open the destination database.
		DestDB.Open();

		// Get an array of all the docs in the database.
		DestDB.GetDocuments( &DocArray );

		// Search all the documents in the array for the 
		// destination document we are to test against.
		IsDocFound = FALSE;
		Count = DocArray.GetCount();
		for (Index = 0; Index<Count; Index++)
		{
			// Get the next document in the array.
			DestDoc = DocArray[Index];

			// Open it.
			DestDoc.Open( LNNOTEOPENFLAGS_DEFAULT );

			if ( DestDoc.HasItem("Body") )
			{
				// This document has a body field, so search for the string in it.
				if ( SearchDocument( DestDoc, "Body", "   *END LINKDEMO*" ) )
				{
					// Document was found; leave the loop now without closing the doc.
					IsDocFound = TRUE;
					break;
				}
			}
		
			DestDoc.Close();
		}

		if (!IsDocFound)
			throw ("Could not find the Destination document needed for this demo!");

		// Make links to both the source and dest databases.
		LNDatabaseLink  SrcDBLink( SrcDB );
		LNDatabaseLink  DestDBLink( DestDB );

		// String was found; now process all the links you can find 
		// or create (the meat of this sample).
		ProcessLinks( &SrcDoc, &DestDoc, &SrcDBLink, &DestDBLink );

		// Close the documents and databases.
		SrcDoc.Close();
		DestDoc.Close();
		SrcDB.Close();
		DestDB.Close();

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

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);

	// Terminate the API.
	Session.Term();

	return (ProgramStatus);

} // END MAIN

//---------------------------------------------------------------------------
//
// Name:
//              SearchDocument
//
// Description:
//              Searches stylized text elements in a document's rich text field
//              for the presence of a search string and returns TRUE if found.
//---------------------------------------------------------------------------
LNBOOL SearchDocument( const LNDocument &Doc, 
					   const LNString &FieldName, 
					   const LNString &SearchStr  )
{
LNRichText	RT;
LNRTCursor	Cursor;

	// Get the document's body field as a rich text item.
	Doc.GetItem( FieldName, &RT );

	// Get the position of the very beginning of the RT field.
	RT.GetCursor( &Cursor );

	// Find the first stylized text in the richtext.
	if ( Cursor.GotoFirst(SearchStr) == LNWARN_NOT_FOUND )
		return FALSE;

	return TRUE;

} // END SearchDocument()

//---------------------------------------------------------------------------
//
// Name:
//              ProcessLinks
//
// Description:
//
//---------------------------------------------------------------------------
void ProcessLinks( LNDocument *SrcDoc, LNDocument *DestDoc,  
				   LNDatabaseLink *SrcDBLink, LNDatabaseLink *DestDBLink )
{
LNSTATUS		error;
LNRichText		SrcRT;
LNRichText		DestRT;
LNRTCursor		SrcCursor;
LNRTCursor		DestCursor;
LNLinkHotspot	linkhotspot;
LNDatabaseLink  DBLink;
LNDocumentLink  DocLink;
LNViewLink		ViewLink;
LNFontStyle		fontstyle;
TIMEDATE		*TimeDate;
UNID			*Unid;
LNBOOL			IsLink = FALSE;

	// Get the rich text "Body" field from the source document.
	cout << endl << "Getting the \"Body\" rich text field from the source document." << endl;
	SrcDoc->GetItem("Body", &SrcRT);

	// Get a start cursor for this RT object.
	SrcRT.GetCursor( &SrcCursor );

	// Get and set stuff in our newly created link to the destination database.
	DestDBLink->SetDescription( "LINKDEMO Destination Database Link");
	TimeDate = DestDBLink->GetLinkedDatabaseReplicaID();

	// Find the first hotspot in the richtext.  This should be the place
	// In the document where the word: "Habenero" appears.
	error = SrcCursor.GotoFirst(LNRTTYPE_LINK_HOTSPOT, &linkhotspot);

	// throw any warnings here too. (i.e. LNWARN_NOT_FOUND) to test for SPR remove this later ***dhs
	if (error)
		throw error;

	// Get an end cursor for the hot spot.  Both cursors will be used
	// to modify the font style of the text in the hot spot.
	DestCursor.GotoEnd( linkhotspot );

	// Set the Destination database link for the hot spot.
	linkhotspot.SetLink( *DestDBLink );

	// Get the font style at the beginning of the hot spot.
	SrcCursor.GetFontStyle( &fontstyle );

	// Change font color to red.
	fontstyle.SetColor( LNCOLOR_RED );

	// Assign this modified font style back to the hotspot.
	linkhotspot.SetFontStyle( SrcCursor, DestCursor, fontstyle );

	// Position the source cursor at the beginning of the next line
	// after the hot spot link.
	SrcCursor.GotoNext( LNRTTYPE_NEW_PARAGRAPH );

	// Insert text on the next line about what just happened and insert a paragraph break after it.
	SrcRT.Insert( "The Habenero hot spot now points to the LINKDEMO destination database.", &SrcCursor );
	SrcRT.StartNewParagraph( &SrcCursor );

	// Save the note to disk so we can go look and see what happened at this point.
	SrcDoc->Save();

	// Print out the info about what we have just done.
	cout << "A link to the destination database was created" << endl;
	cout << "Its description is: [" << (const char *)DestDBLink->GetDescription() << "]" << endl;
	cout << "Here is a Hex printout of its Linked Database Replica ID" << endl;
	PrintTimeDate( TimeDate );
	cout << "It has been inserted into the \"Habenero\" hot spot in the Source document in linkdemo.nsf" << endl;
	cout << "Hit return to continue: ";
	cin.getline(CommandBuf, 50);

	// Get the rich text "Body" field from the destination document.
	cout << endl << "Getting the \"Body\" Rich Text field from the Destination Document." << endl;
	DestDoc->GetItem("Body", &DestRT);

	// Get a cursor for this RT object.
	DestRT.GetCursor( &DestCursor );

	// Position the destination cursor where the links from the source doc will be inserted.
	cout << "Setting the cursor position where the links from " << endl 
		 << "the source doc will be inserted in the dest doc." << endl;

	DestCursor.GotoFirst( "   *END LINKDEMO*" );

	// Get and set stuff in our newly created link to the source database.
	SrcDBLink->SetDescription( "LINKDEMO Source Database Link");
	TimeDate = SrcDBLink->GetLinkedDatabaseReplicaID();

	// Insert the new source database link into the
	// rich text field of the destination document.
	DestRT.Insert( " Here is a link[ ",  &DestCursor );
	DestRT.Insert( *SrcDBLink, &DestCursor );
	DestRT.Insert( " ] to the LINKDEMO source database. ", &DestCursor );

	// Save the note to disk so we can go look and see what happened at this point.
	DestDoc->Save();

	// Print out the info about what we have just done.
	cout << "A link to the source database was created" << endl;
	cout << "Its description is: [" << (const char *)SrcDBLink->GetDescription() << "]" << endl;
	cout << "Here is a Hex printout of its Linked Database Replica ID" << endl;
	PrintTimeDate( TimeDate );
	cout << "It has been inserted into the destination document in rtsample.nsf" << endl;
	cout << "Hit return to continue: ";
	cin.getline(CommandBuf, 50);

	//
	// Now get all of the existing database links in the source document
	// and copy these into the destination document at the cursor position.
	//

	cout << endl << "Looking for top level database links in the source document rich text field." << endl << endl;

	DestRT.Insert( " Any Top Level Database Links from the Source Doc will be inserted here -> ",  &DestCursor );

	while ( SrcCursor.GotoNext( LNRTTYPE_DATABASE_LINK, &DBLink ) != LNWARN_NOT_FOUND )
	{
	LNString	Description;

		// Do not process if this is also a view link (includes doclinks).
		if ( DBLink.IsType(LNRTTYPE_VIEW_LINK) )
			continue;

		// If we have at least one top-level database link in the source database, set the flag true.
		IsLink = TRUE;

		// Get info about the current database link.
		cout << "Getting Info about the current database link found." << endl;
		TimeDate = DBLink.GetLinkedDatabaseReplicaID();
		Description = DBLink.GetDescription();
		cout << "Its description is: [" << (const char *)Description << "]" << endl;
		cout << "Here is a Hex printout of it's Linked Database Replica ID" << endl;
		PrintTimeDate( TimeDate );

		// Insert the current database link into the destination document.
		DestRT.Insert( "     Database Link:  ", &DestCursor );
		DestRT.Insert( Description, &DestCursor );
		DestRT.Insert( "[", &DestCursor );
		DestRT.Insert( DBLink, &DestCursor );
		DestRT.Insert( "]", &DestCursor );

		// Save the note to disk so we can go look and see what happened at this point.
		DestDoc->Save();

		cout << "It has been inserted into the destination database document" << endl;
		cout << "Hit return to continue: ";
		cin.getline(CommandBuf, 50);
	}

	if ( !IsLink )
	{
		DestRT.Insert( " There were no top level data base links in the rich text. ",  &DestCursor );

		cout << endl << "Sorry, but no top level database links were found!" << endl;
		cout << "Hit return to continue: ";
		cin.getline(CommandBuf, 50);
	}

	//
	// Now get all of the existing view links in the source document
	// and copy these into the destination document at the cursor position.
	//

	IsLink = FALSE;

	cout << endl << "Looking for top level view links in the source document rich text field." << endl << endl;

	DestRT.Insert( " Any top level view links from the source doc will be inserted here -> ",  &DestCursor );

	// Position the start cursor back to the place before the links in the rich text field.
	SrcCursor.GotoFirst( "*Here are some links for testing*" );

	while ( SrcCursor.GotoNext( LNRTTYPE_VIEW_LINK, &ViewLink ) != LNWARN_NOT_FOUND )
	{
	LNString	Description;

		// Do not process if this is also a doc link.
		if ( ViewLink.IsType(LNRTTYPE_DOCUMENT_LINK) )
			continue;

		// If we have at least one top level view link in the source database, set the flag true.
		IsLink = TRUE;

		// Get info about the current view link.
		cout << "Getting Info about the current View link found." << endl;

		Unid = ViewLink.GetLinkedViewUniversalID();
		Description = ViewLink.GetDescription();
		cout << "Its description is: [" << (const char *)Description << "]" << endl;
		cout << "Here is a Hex printout of its linked universal view ID" << endl;               
		PrintUNID( Unid );

		// Insert the current view link into the destination document.
		DestRT.Insert( "     View Link:  ", &DestCursor );
		DestRT.Insert( Description, &DestCursor );
		DestRT.Insert( "[", &DestCursor );
		DestRT.Insert( ViewLink, &DestCursor );
		DestRT.Insert( "]", &DestCursor );

		// Save the note to disk so we can go look and see what happened at this point.
		DestDoc->Save();

		cout << "It has been inserted into the destination database document" << endl;
		cout << "Hit return to continue: ";
		cin.getline(CommandBuf, 50);
	}

	if ( !IsLink )
	{
		DestRT.Insert( " There were no top level view links in the rich text. ",  &DestCursor );

		cout << endl << "Sorry, but no top level view links were found!" << endl;
		cout << "Hit return to continue: ";
		cin.getline(CommandBuf, 50);
	}


	//
	// Now get all of the existing document links in the source document
	// and copy these into the destination document at the cursor position.
	//
	IsLink = FALSE;

	cout << endl << "Looking for document links in the source document rich text field." << endl << endl;

	DestRT.Insert( " Any document links from the source doc will be inserted here -> ",  &DestCursor );

	// Position the start cursor back to the place before the links in the rich text field.
	SrcCursor.GotoFirst( "*Here are some links for testing*" );

	while ( SrcCursor.GotoNext( LNRTTYPE_DOCUMENT_LINK, &DocLink ) != LNWARN_NOT_FOUND )
	{
	LNString	Description;

		// If we have at least one doc link in the source database, set the flag true.
		IsLink = TRUE;

		// Get info about the current document link.
		cout << "Getting Info about the current document link found." << endl;
		Unid = DocLink.GetLinkedDocumentUniversalID();
		Description = DocLink.GetDescription();
		cout << "Its description is: [" << (const char *)Description << "]" << endl;
		cout << "Here is a Hex printout of it's Linked Universal Note ID" << endl;              
		PrintUNID( Unid );

		// Insert the current document link into the destination document.
		DestRT.Insert( "     Document Link:  ", &DestCursor );
		DestRT.Insert( Description, &DestCursor );
		DestRT.Insert( "[", &DestCursor );
		DestRT.Insert( DocLink, &DestCursor );
		DestRT.Insert( "]", &DestCursor );

		// Save the note to disk so we can go look and see what happened at this point.
		DestDoc->Save();

		cout << "It has been inserted into the destination database document" << endl;
		cout << "Hit return to continue: ";
		cin.getline(CommandBuf, 50);
	}

	if ( !IsLink )
	{
		DestRT.Insert( " There were no document links in the rich text. ",  &DestCursor );

		cout << endl << "Sorry, but no document links were found!" << endl;
		cout << "Hit return to continue: ";
		cin.getline(CommandBuf, 50);
	}

} // END ProcessLinks()

//---------------------------------------------------------------------------
//
// Name:
//              PrintTimeDate
//
// Description:
//              Prints out the hex values of a TIMEDATE to the screen.
//---------------------------------------------------------------------------
void PrintTimeDate( TIMEDATE *TimeDate )
{
char	buf[32];

	// Make up the timedate hex string from the timedate struct values.
	sprintf(buf, "0x%X - 0x%X", (int)TimeDate->Innards[1], (int)TimeDate->Innards[0] );         
	cout << "     Link ID: [" << buf << "]" << endl << endl;

} // END PrintTimeDate()

//---------------------------------------------------------------------------
//
// Name:
//              PrintUNID
//
// Description:
//              Prints out the hex values of a Universal Note ID to the screen.
//---------------------------------------------------------------------------
void PrintUNID( UNID *Unid )
{
char	buf[32];

	cout << "     UNID:" << endl;
	// Make up the timedate hex strings from the "File" element of the UNID.
	sprintf(buf, "0x%X - 0x%X", (int)Unid->File.Innards[1], (int)Unid->File.Innards[0] );           
	cout << "         Unid->File: [" << buf << "]" << endl;
	// Make up the timedate hex strings from the "Note" element of the UNID.
	sprintf(buf, "0x%X - 0x%X", (int)Unid->Note.Innards[1], (int)Unid->Note.Innards[0] );           
	cout << "         Unid->Note: [" << buf << "]" << endl << endl;

} // END PrintUNID()

// END linkdemo.cpp


