//===========================================================================
//
//      Module: RTPGRAPH.CPP
//
//      Description:
//              Sample C++ API program that creates rich text paragraphs.
//              
//      Syntax: RTPGRAPH
//
//		Note:	This sample program runs against a supplied Notes database, 
//				RTSAMPLE.NSF. It prompts the user along the way to continue 
//				after pauses, but does not take any input parameters.  It
//				depends on finding a document with a 'body' item which must
//				contain a paragraph that starts with the string "The 
//				dangerously erratic".  
//
//===========================================================================
//
// Copyright (c) 1997,1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#include <iostream.h>

// Notes C++ API headers.
#include "lncppapi.h"
#include "editdflt.h"

// For 16-bit Windows only, disable the warning about assignments in
// conditional expressions, because this sample uses many of them.
#if defined(W16)
#pragma option -w-pia
#endif

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
void EditParagraphs( LNDocument *CurDoc );
void SetUpStyles( LNParagraphStyle &PS, LNFontStyle &FS, LNTabs &Tabs, int index );

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int				ProgramStatus = 0;
	LNNotesSession	Session;
	LNDatabase		DocDB;

#if defined(MAC)
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
#endif

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	LNSetThrowAllErrors (TRUE);

	try
	{
		LNDocumentArray	DocArray;
		LNINT			i;

		// Initialize the API.
		Session.Init (argc, argv);

		// Get the specified Notes database.
		Session.GetDatabase( "rtsample.nsf", &DocDB );

		// Open the database.
		DocDB.Open();

		// Get an array of all the docs in the database.
		DocDB.GetDocuments( &DocArray );

		LNBOOL  IsDocFound = FALSE;
		for (i = 0; i < DocArray.GetCount (); i++)
		{
			LNDocument	CurDoc;

			// Get the next document in the array.
			CurDoc = DocArray[i];

			// Open it.
			CurDoc.Open( LNNOTEOPENFLAGS_DEFAULT );

			if ( CurDoc.HasItem("Body") )
			{
				// Change 10 paragraphs of rich text to different font styles and paragraph styles. 
				EditParagraphs( &CurDoc );

				IsDocFound = TRUE;
				break;
			}
			// Always close it too! Conserve memory!
			CurDoc.Close();
		}

		if (!IsDocFound)
			cout << "This database contains no documents with a \"Body\" field!" << endl;

		ProgramStatus = 0;

	} // END try

	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(lnerror, ErrorBuf, LNERROR_MESSAGE_LENGTH);
		cout << "\nError:  " << ErrorBuf << endl;
		ProgramStatus = 2;
	}

	// Close the database.
	DocDB.Close();

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);

	// Terminate the API.
	Session.Term();

	return (ProgramStatus);

} // END MAIN

//---------------------------------------------------------------------------
//
// Name:
//              EditParagraphs
//
// Description:
//              Changes paragraphs in a rich text field of the current doc.
//              Applies different paragraph styles, tab settings, and font styles
//              to the paragraphs. Stops along the way to give the user a chance to
//              examine what has happened at each step.
//
//---------------------------------------------------------------------------
void EditParagraphs( LNDocument *CurDoc )
{
	LNRichText			RT;
	LNRTCursor			StartCursor;
	LNRTCursor			EndCursor;
	LNParagraphStyle	PS;
	LNFontStyle			FS;
	LNTabs				Tabs;
	int					i;

	// Get the rich text "Body" field from the document.
	CurDoc->GetItem("Body", &RT);

	// Get a start cursor for this RT object.
	RT.GetCursor( &StartCursor );

	// Position the start cursor at the first occurrence of the search string.
	StartCursor.GotoFirst( "The dangerously erratic" );

	// Make the end cursor a copy of the start cursor.  We will use the end cursor
	// to advance and leave the start cursor at the beginning of each paragraph.
	EndCursor.Copy( StartCursor );

	// Loop through the text, aligning the cursors at the beginning and end of each new paragraph.
	// Change each paragraph encountered to have a different paragraph and font style.
	for (i=0; i<10; i++)
	{
		// Move the end cursor ahead to the beginning of the next 
		// paragraph (after the next carriage return).
		EndCursor.GotoNext( LNRTTYPE_NEW_PARAGRAPH );

		// Modify the paragraph style and font style based on the loop index.
		SetUpStyles( PS, FS, Tabs, i );

		// Set the paragraph style for the paragraph at the start cursor.
		RT.SetParagraphStyle( StartCursor, PS );

		// Set the font style for the paragraph at the cursor.              
		RT.SetFontStyle( StartCursor, EndCursor, FS );

		// Save the note to disk so we can go look and see what happened at this point.
		CurDoc->Save();

		cout << "Paragraph [" << i << "] has just been modified in the Current Document.";
		if ( i == 0 )
		{
			cout << endl << "The color was changed to red and all text has been underlined." << endl
				 << endl 
				 << "This sample demonstrates how to change styles in another " << endl
				 << "nine paragraphs. For each of these paragraph style changes, " << endl 
				 << "if you want to examine the newly changed paragraph, use the" << endl
				 << "Notes UI to open the first document in rtsample.nsf." << endl
				 << "Be sure to close the document before continuing here" << endl
				 << "or else you will not be able to see more changes. " << endl
				 << "Hit return to continue: ";
		}

		cin.getline(CommandBuf, 50);

		// Line up the start cursor with the end cursor so it will be the start 
		// of the next paragraph.
		StartCursor.GotoNext( LNRTTYPE_NEW_PARAGRAPH );
	}

	// Now demonstrate paragraph merges and splits. This will be performed on the first two
	// paragraphs that were processed above.

	// Position the start cursor back to the first occurrence of the search string.
	StartCursor.GotoFirst( "The dangerously erratic" );

	// Get the end cursor back to the starting paragraph, too.
	EndCursor.Copy( StartCursor );

	// Modify the paragraph style, tabs, and font style.
	SetUpStyles( PS, FS, Tabs, 8 );

	// Merge the paragraph at the cursor with the next one after it. 
	RT.MergeNextParagraph( &StartCursor );

	// Move the end cursor ahead to the end of the merged paragraph.
	EndCursor.GotoNext( LNRTTYPE_NEW_PARAGRAPH );

	// Apply the newly changed paragraph style to the merged paragraph.
	RT.SetParagraphStyle( StartCursor, PS );

	// Apply the newly changed font style to the merged paragraph.
	RT.SetFontStyle( StartCursor, EndCursor, FS );

	// Save the note to disk so we can go look and see what happened at this point.
	CurDoc->Save();

	cout << endl << "The first paragraph has just been merged with the second." << endl
		 << "new font and paragraph styles were applied to the merged paragraph." << endl
		 << "You may go and examine the changes just as before." << endl
		 << "Don't forget to close the document before continuing." << endl
		 << "Hit return to continue: ";

	cin.getline(CommandBuf, 50);

	// Now split the paragraph apart into two different paragraphs and
	// modify the second one with different syles, fonts, and tabs.

	// Position the start cursor at the word Tab1 in the middle of the merged paragraph.
	StartCursor.GotoFirst( "Tab1" );

	// Split the paragraph in two at the cursor (adds a carrage return at cursor position).
	RT.StartNewParagraph( &StartCursor );

	// Modify the paragraph style, tabs, and font style.
	SetUpStyles( PS, FS, Tabs, 6 );

	// Apply the newly changed paragraph style to the new split-off paragraph.
	RT.SetParagraphStyle( StartCursor, PS );

	// Apply the newly changed font style to the new split-off paragraph.
	RT.SetFontStyle( StartCursor, EndCursor, FS );

	// Save the note to disk so we can go look and see what happened at this point.
	CurDoc->Save();

	cout << endl << "The first paragraph has just been split in two." << endl
		 << "New font and paragraph styles were applied to the new paragraph." << endl
		 << "You may go and examine the changes just as before." << endl
		 << "Don't forget to close the document before continuing." << endl
		 << "Hit return to continue: ";

	cin.getline(CommandBuf, 50);

	// Finally, set the cursors to contain all the paragraphs changed and
	// reset the font style and paragraph style of all of it back to plain 
	// old typwriter text, plain old paragraph style, .5 inch tabs.

	// Position the start cursor at the first occurrence of the search string.
	StartCursor.GotoFirst( "The dangerously erratic" );

	// Position the end cursor at the very end of the rich text field. 
	RT.GetEndCursor( &EndCursor);

	// Modify the paragraph style, tabs, and font style.
	SetUpStyles( PS, FS, Tabs, 4 );

	// Apply the newly changed paragraph style back to the new split-off paragraph.
	RT.SetParagraphStyle( StartCursor, EndCursor, PS );

	// Apply the newly changed font style back to the merged paragraph.
	RT.SetFontStyle( StartCursor, EndCursor, FS );

	// Save the note to disk so we can go look and see what happened at this point.
	CurDoc->Save();

	cout << endl << "All of the paragraphs have been changed back to a plain" << endl
		 << "mono-spaced font style and a non-indented paragraph style." << endl
		 << "You may go and examine the changes just as before." << endl
		 << "Don't forget to close the document before continuing." << endl
		 << "Hit return to continue: ";

	cin.getline(CommandBuf, 50);

} // END EditParagraphs()

//---------------------------------------------------------------------------
//
// Name:
//              SetUpStyles
//
// Description:
//              Sets an LNParagraphStyle LNFontStyle to
//              specified settings based on the input index value.
//
// Font style constants available for use:
//
//      Font attributes flags:
//
//              LNFONTATTRIBUTEFLAGS_PLAIN
//              LNFONTATTRIBUTEFLAGS_BOLD
//              LNFONTATTRIBUTEFLAGS_ITALIC
//              LNFONTATTRIBUTEFLAGS_UNDERLINE
//              LNFONTATTRIBUTEFLAGS_STRIKETHROUGH
//              LNFONTATTRIBUTEFLAGS_SUPERSCRIPT
//              LNFONTATTRIBUTEFLAGS_SUBSCRIPT
//
//      FACE IDs defined for use in LNFontStyle:
//
//              LNFACEID_ROMAN
//              LNFACEID_HELVETICA
//              LNFACEID_COURIER
//
//      LNCOLOR constants defined:
//
//              LNCOLOR_BLACK
//              LNCOLOR_WHITE
//              LNCOLOR_RED
//              LNCOLOR_GREEN
//              LNCOLOR_BLUE    
//              LNCOLOR_MAGENTA
//              LNCOLOR_YELLOW  
//              LNCOLOR_CYAN
//              LNCOLOR_DARK_RED        
//              LNCOLOR_DARK_GREEN
//              LNCOLOR_DARK_BLUE
//              LNCOLOR_DARK_MAGENTA
//              LNCOLOR_DARK_YELLOW     
//              LNCOLOR_DARK_CYAN
//              LNCOLOR_GRAY
//              LNCOLOR_LIGHT_GRAY      
//
// Paragraph style constants used below:
//
//      UNIT constants available:
//
//              LNUNITS_INCHES
//              LNUNITS_CENTIMETERS
//              LNUNITS_TWIPS
//              LNUNITS_DEFAULT
//
//      LIST STYLE constants available:
//
//              LNLISTSTYLE_NONE
//              LNLISTSTYLE_BULLET
//              LNLISTSTYLE_NUMBERED
//
//      LINE SPACING constants available:
//
//              LNLINESPACING_SINGLE
//              LNLINESPACING_1_5
//              LNLINESPACING_DOUBLE
//
//      ALIGNMENT constants available:
//
//              LNALIGNMENT_LEFT                        // flush left, ragged right
//              LNALIGNMENT_CENTER                      // centered
//              LNALIGNMENT_RIGHT                       // flush right, ragged left
//              LNALIGNMENT_FULL                        // full block justification
//              LNALIGNMENT_NONE                        // no line wrapping AT ALL (except hard CRs (carriage returns))
//
//      INDENTATION constants available:
// 
//              LNINDENTATION_NONE
//              LNINDENTATION_INDENT
//              LNINDENTATION_OUTDENT
//---------------------------------------------------------------------------
void SetUpStyles( LNParagraphStyle &PS, LNFontStyle &FS, LNTabs &Tabs, int i )
{       
	LNSTATUS	error;

	// Set the paragraph style to defaults for starters.
	if ( error =  PS.SetDefaults() )
		throw error;

	// Set the font style to defaults for starters.
	if ( error =  FS.SetDefaults() )
		throw error;

	// Get a new tab array for this paragraph style.
	if ( error =  PS.GetTabs( &Tabs ) )
		throw error;

	switch ( i )
	{
	case 0:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 1.0 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 1.0 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_LEFT ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_INDENT ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_1_5 ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_BULLET ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_DOUBLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  Tabs.SetInterval( 1.0 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_ITALIC | LNFONTATTRIBUTEFLAGS_UNDERLINE ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_COURIER ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_RED ) )
			throw error;
		if ( error =  FS.SetPointSize( 10 ) )
			throw error;

		break;

	case 1:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 1.0 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 1.0 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_RIGHT ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_NONE ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_SINGLE ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_NONE ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_DOUBLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  Tabs.SetInterval( 3.0 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_PLAIN ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_HELVETICA ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_BLUE ) )
			throw error;
		if ( error =  FS.SetPointSize( 18 ) )
			throw error;

		break;

	case 2:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 2.5 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 2.5 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_FULL ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_NONE ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_SINGLE ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_NONE ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_DOUBLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_CENTIMETERS ) )
			throw error;
		if ( error =  Tabs.SetInterval( 2.0 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_STRIKETHROUGH ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_ROMAN ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_MAGENTA ) )
			throw error;
		if ( error =  FS.SetPointSize( 12 ) )
			throw error;

		break;

	case 3:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 0.5 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 0.5 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_CENTER ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_NONE ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_SINGLE ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_NONE ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_DOUBLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  Tabs.SetInterval( 1.0 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_UNDERLINE ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_COURIER ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_GREEN ) )
			throw error;
		if ( error =  FS.SetPointSize( 24 ) )
			throw error;

		break;

	case 4: // Use this one for setting back to plain styles.

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 1.0 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 1.0 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_LEFT ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_INDENT ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_SINGLE ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_NONE ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_SINGLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_SINGLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  Tabs.SetInterval( 0.5 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_PLAIN ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_COURIER ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_BLACK ) )
			throw error;
		if ( error =  FS.SetPointSize( 9 ) )
			throw error;

		break;

	case 5:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 3.0 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 1.0 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_LEFT ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_NONE ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_1_5 ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_NUMBERED ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_1_5 ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_1_5 ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_CENTIMETERS ) )
			throw error;
		if ( error =  Tabs.SetInterval( 1.0 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_PLAIN | LNFONTATTRIBUTEFLAGS_UNDERLINE ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_HELVETICA ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_DARK_BLUE ) )
			throw error;
		if ( error =  FS.SetPointSize( 18 ) )
			throw error;

		break;

	case 6:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 0.5 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 4.0 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_RIGHT ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_NONE ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_SINGLE ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_BULLET ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_DOUBLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  Tabs.SetInterval( 0.5 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_PLAIN ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_ROMAN ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_DARK_CYAN ) )
			throw error;
		if ( error =  FS.SetPointSize( 10 ) )
			throw error;

		break;

	case 7:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 0.5 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 0.5 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_CENTER ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_NONE ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_SINGLE ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_NUMBERED ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_DOUBLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  Tabs.SetInterval( 1.0 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_PLAIN ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_ROMAN ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_GRAY ) )
			throw error;
		if ( error =  FS.SetPointSize( 10 ) )
			throw error;

		break;

	case 8:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 1.5 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 1.5 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_FULL ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_NONE ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_NONE ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_DOUBLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_CENTIMETERS ) )
			throw error;
		if ( error =  Tabs.SetInterval( 3.0 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_STRIKETHROUGH ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_HELVETICA ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_DARK_MAGENTA ) )
			throw error;
		if ( error =  FS.SetPointSize( 14 ) )
			throw error;

		break;

	case 9:

		// Set specific things in the paragraph style.
		if ( error =  PS.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  PS.SetLeftMargin( 3.0 ) )
			throw error;
		if ( error =  PS.SetRightMargin( 0.5 ) )
			throw error;
		if ( error =  PS.SetAlignment( LNALIGNMENT_RIGHT ) )
			throw error;
		if ( error =  PS.SetFirstLineIndentation( LNINDENTATION_NONE ) )
			throw error;
		if ( error =  PS.SetLineSpacing( LNLINESPACING_SINGLE ) )
			throw error;
		if ( error =  PS.SetListStyle( LNLISTSTYLE_NONE ) )
			throw error;
		if ( error =  PS.SetSpacingAbove( LNLINESPACING_DOUBLE ) )
			throw error;
		if ( error =  PS.SetSpacingBelow( LNLINESPACING_DOUBLE ) )
			throw error;

		// Set up the tabs for this current paragraph style.
		if ( error =  Tabs.SetUnits( LNUNITS_INCHES ) )
			throw error;
		if ( error =  Tabs.SetInterval( 3.0 ) )
			throw error;
		
		// Set specific things in the font style.
		if ( error =  FS.SetAttributes( LNFONTATTRIBUTEFLAGS_PLAIN | LNFONTATTRIBUTEFLAGS_ITALIC ) )
			throw error;
		if ( error =  FS.SetFaceID( LNFACEID_COURIER ) )
			throw error;
		if ( error =  FS.SetColor( LNCOLOR_BLUE ) )
			throw error;
		if ( error =  FS.SetPointSize( 12 ) )
			throw error;

		break;
	}

} // END SetUpStyles()

