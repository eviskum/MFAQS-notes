//===========================================================================
//
//      Module: RTBUTTON.CPP
//
//      Syntax: RTBUTTON [<button title> [<database> [<Server>]]]
//				Note: All the arguments are optional, but must be in the
//					  order specified.
//
//      Description:
//              Sample C++ API program that creates, edits and deletes rich 
//				text buttons using the LNButton and LNCompositeData classes.
//
//
//
//===========================================================================

#include "rtbutton.hpp"

// Input parameter strings.
IOParameter     CommandBuf;
IOParameter     PromptString1;
IOParameter     ParamString1;
IOParameter     PromptString2;
IOParameter     ParamString2;
IOParameter     PromptString3;
IOParameter     ParamString3;

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int             ProgramStatus = 0;
	LNNotesSession	Session;

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	LNSetThrowAllErrors (TRUE);

	try
	{
		LNDatabase            DocDB;
		LNString              DatabasePath;
		LNString              ServerPath;
		LNString              ButtonTitle;
		LNDocumentArray		  DocArray;
		LNString              SearchFormula;

		// Initialize the API.
		Session.Init (argc, argv);

		// Parse the argument list.              
		ProcessArguments (argc, argv, &DatabasePath, &ServerPath, &ButtonTitle);

		// Get the specified Notes database.
		Session.GetDatabase(DatabasePath, &DocDB, ServerPath);

		// Open the database.
		DocDB.Open();

		// Get an array of all the docs in the database.
		DocDB.GetDocuments( &DocArray );

		LNINT		Index;
		LNBOOL		IsDocFound1 = FALSE;
		LNBOOL		IsDocFound2 = FALSE;
		LNINT		Count = DocArray.GetCount();
		LNString	FormulaString("@Prompt([Ok];\"Greeting\";\"Hi, how are you?!\")");
		LNDocument	CurDoc;	
		LNText		Subject;
		LNString	SubjectString;	
		LNButton	Button1, Button2, Button3;
		LNRichText	RT1, RT2, RT3;
		LNString	NewLabel("New Label");


		// Loop through the documents until we find the two documents 
		// that this sample is supposed to use
		
		for (Index=0; Index<Count; Index++)
		{
			// Get the next document in the array.
			CurDoc = DocArray[Index];

			// Open it.
			CurDoc.Open( LNNOTEOPENFLAGS_DEFAULT );
				
			// Check the subject of each document to find the two documents that we need
			if ( CurDoc.HasItem("Subject"))
			{
				CurDoc.GetItem("Subject", &Subject);
				Subject.GetText(&SubjectString);
				if (LNStringCompare(SubjectString, "Rtbutton using LNButton class") == 0)

				{
					//	Let's create 3 buttons using LNButton class
					AppendButton(ButtonTitle, FormulaString, &CurDoc, &Button1);
					AppendButton(ButtonTitle, FormulaString, &CurDoc, &Button2);
					AppendButton(ButtonTitle, FormulaString, &CurDoc, &Button3);

					
					// Save the note to disk, otherwise all the work is wasted.
					CurDoc.Save();

					// You can now check the document and make sure that it contains 3 buttons.

					// Now let's edit the second button that we just created.
					// We'll change its label to the NewLabel string, defined above.
					Button2.SetLabel(NewLabel);

					// And again, save the document.
					CurDoc.Save();

					cout << "Buttons created with LNButton class added and saved" << endl;
					cout << "Hit Return to continue: ";
					cin >> CommandBuf;


					// Now let's delete Button3 that we created earlier.
					DeleteButton(&CurDoc,  &Button3);

					// Save the document.
					CurDoc.Save();

					cout << "Button3 created with LNButton class deleted" << endl;

					IsDocFound1 = TRUE;
					if (IsDocFound2) // found both documents, don't need to iterate any more.
						break;

				}

				else if (LNStringCompare(SubjectString, "Rtbutton using CD Records") == 0)
				{

					// Here we'll create 3 buttons using CD records and  append them
					// to the document.
					AppendCDButton(ButtonTitle, FormulaString, &CurDoc, &RT1);
					AppendCDButton(ButtonTitle, FormulaString, &CurDoc, &RT2);
					AppendCDButton(ButtonTitle, FormulaString, &CurDoc, &RT3);

					
					// Save the note to disk, otherwise all the work is wasted.
					CurDoc.Save();					

					// You can now check the document and make sure that
					// it contains 3 buttons created with CD Records.
					

					// Now we'll show how to modify the button (change its label)
					// using CD records.
					EditCDButtonLabel(NewLabel, &RT2);
					CurDoc.Save();

					
					cout << "Buttons created with CD records added and saved" << endl;
					cout << "Hit Return to continue: ";
					cin >> CommandBuf;

					// You can now check the document and make sure that the second
					// button has a different label
				
					// Now we'll delete the third button we created using CD records

					DeleteCDButton(&RT3);
					CurDoc.Save();
					
					cout << "Button3 created with CD records deleted" << endl;

					IsDocFound2 = TRUE;
					if (IsDocFound1) // found both documents, don't need to iterate any more
						break;				
					
				}
			}

			CurDoc.Save();
			// Always close it, too! Conserve memory!
			CurDoc.Close();
		}

		if (!IsDocFound1)
		{
			cout << "This database contains no documents with \"Rtbutton using LNButton class\" subject." << endl;
			cout << "Unable to create buttons using LNButton class." << endl;
		}

		if (!IsDocFound2)
		{
			cout << "This database contains no documents with \"Rtbutton using CD records\" subject." << endl;
			cout << "Unable to create buttons using CD records." << endl;
		}

		// Close the database.
		DocDB.Close();

		ProgramStatus = 0;

	} // END try

	catch (LNSTATUS Lnerror)
	{
		char ErrorBuf[LNERROR_MESSAGE_LENGTH];

		LNGetErrorMessage(Lnerror, ErrorBuf);
		cout << "\nError:  " << ErrorBuf << endl;
		ProgramStatus = 2;
	}

	catch (const char *ErrorMessage)
	{
		cout << "\nError: " << ErrorMessage << endl << endl;
		ProgramStatus = 1;
	}

	cout << endl;
	cout << "Hit Return To Exit: ";
	cin >> CommandBuf;

	// Terminate the API.
	Session.Term();

	return (ProgramStatus);

} // END MAIN

//---------------------------------------------------------------------------
// Name: 
//				AppendButton														 
//																			 
// Description:																 
//              Creates a button using LNButton class, and appends it to the 
//              body of the document that is passed in.						 
//																			 
//																			 
//---------------------------------------------------------------------------

void AppendButton (const LNString &ButtonTitle, const LNString &FormulaString, 
				   LNDocument *CurDoc,  LNButton* Button)


{
	LNRichText		RT;
	LNRTCursor		Cursor;

	LNSetThrowAllErrors (TRUE);

	//Create a button in a document using LNButton class.
						
	CurDoc->GetItem("Body",&RT);

	RT.GetEndCursor(&Cursor);
				
	//  Create a formula
				
	LNFormula Formula(FormulaString);
			
	//  Construct a button that contains the above formula.  Then
	//  insert the button into the rich text item.	
			
	RT.Insert("\n\nThis button was made using LNButton class:  ", &Cursor);
	RT.CreateButton(ButtonTitle, Formula, &Cursor, Button);

	RT.Insert("\n\n", &Cursor);

}  // END AppendButton()

//---------------------------------------------------------------------------
//
// Name:
//              AppendCDButton
//
// Description:
//              Creates a button hotspot and appends this to the body field of the
//              LNDocument passed in.
//
//---------------------------------------------------------------------------
void AppendCDButton(const LNString &ButtonTitle, const LNString &FormulaString,  
					LNDocument *CurDoc, LNRichText *RT)
{

	LNSTATUS                Error;
	CDHOTSPOTBEGIN			Hotspotbegin;
	CDBUTTON                Button;
	CDHOTSPOTEND			Hotspotend;
	HANDLE                  FormulaHandle;
	void*                   FormulaBuf;
	WORD                    Wnop;
	STATUS                  Werr;
	LNString                Formula;
	LNCompositeData			CD;
	WORD                    Length;

	// Get the rich text "Body" field from the document.  We will append the button to it.
	CurDoc->GetItem("Body", RT);

	// Append a string to the end of the field where the button will follow.
	RT->Append( "\nThis button was made using CD records: ");

	// Specify a formula (in text format) for the button.
	Formula = FormulaString;
	//Formula = "@Prompt([OKCANCELEDIT];\"Search Criteria\";\"Please enter your name:\";\"\" )";
	// Assume no search formula.
	FormulaHandle = NULLHANDLE;

	// Compile the specified LNString text formula into the actual formula.
	// Note: The following call is not a C++ call so we need to handle the error return.
	if (Error = NSFFormulaCompile( NULL, 0, Formula.GetTextPtr(),
								   (WORD)Formula.GetByteCount(),
								   &FormulaHandle, &Wnop, &Werr,
								   &Wnop, &Wnop,&Wnop,&Wnop      ) )
		throw Error;

	// Get the length of the compiled formula for the button.
	// NOTE for C API programmers: The LNCompositeData class will make sure 
	// that the CD record is aligned on even byte boundaries for you.
	if ( Error = NSFFormulaGetSize(FormulaHandle, &Length) )
		throw Error;

	// Note!!!
	// A rich text button consists of 3 CD records:
	// - HotspotBegin record
	// - Button record
	// - HotspotEnd record.
	// In order to create a rich text button, we need to create each of those
	// records separately.

	// Let's start by setting up the CD Hot Spot Begin record.
	//

	Hotspotbegin.Header.Signature = SIG_CD_HOTSPOTBEGIN;
	Hotspotbegin.Header.Length = ( ODSLength(_CDHOTSPOTBEGIN) + Length );  // see: NOTE above.
	Hotspotbegin.Type = HOTSPOTREC_TYPE_BUTTON;
	Hotspotbegin.Flags = HOTSPOTREC_RUNFLAG_NOBORDER; // See: C API, HOTSPOTREC_RUNFLAG_xxx
	Hotspotbegin.DataLength = Length; // Length of the button's compiled formula.

	// Write the filled CDHOTSPOTBEGIN record into the LNCompositeData object.
	CD.WriteODS(_CDHOTSPOTBEGIN, &Hotspotbegin);

	//Get a pointer to the compiled formula's buffer.
	FormulaBuf = OSLock(char, FormulaHandle);

	// Write the compiled formula data to the CD object.
	CD.Write( Length,  FormulaBuf, ODSLength(_CDHOTSPOTBEGIN) );

	// Unlock it immediately after use.
	OSUnlock(FormulaHandle);

	// Get rid of the compiled formula, since we don't need it anymore.
	if (FormulaHandle)
		OSMemFree(FormulaHandle);

	// Append this composite data object to the end of the rich text field.
	RT->Append(CD);

	// Get the Length of the button's title string.
	// NOTE for C API programmers: The LNCompositeData class will make sure 
	// that the CD record is aligned on even byte boundaries for you.
	Length = (WORD)ButtonTitle.GetByteCount();

	//
	// Set up the CD Button data structure.
	//

	Button.Header.Signature = SIG_CD_BUTTON;
	Button.Header.Length = ( ODSLength(_CDBUTTON) + Length ); // see: NOTE above.
	Button.Flags = NULL;
	Button.Width = (ONEINCH * 2);
	Button.Height = NULL;
	Button.Lines = 5;
	Button.FontID = DEFAULT_FONT_ID; 

	// Write the filled CDButton record into the LNCompositeData object.
	CD.WriteODS(_CDBUTTON, &Button);

	// Write the button title text after the CDButton record info.
	CD.Write( Length,  ButtonTitle.GetTextPtr(), ODSLength(_CDBUTTON) );

	// Append this composite data object to the end of the rich text field.
	RT->Append (CD);

	//
	// Set up the CD Hotspot End data structure.
	//

	Hotspotend.Header.Signature = SIG_CD_HOTSPOTEND;
	Hotspotend.Header.Length = (BYTE)ODSLength(_CDHOTSPOTEND);

	// Write the filled CDHOTSPOTEND record into the LNCompositeData object.
	CD.WriteODS(_CDHOTSPOTEND, &Hotspotend);

	// Append this composite data object to the end of the rich text field.
	RT->Append (CD);

	RT->Append(" ");  // Add a space after the button records.

	RT->Append("\n\n");

} // END AppendCDButton()

//---------------------------------------------------------------------------
// Name:
//				EditCDButtonLabel
//
// Description:
//				Set the button label to the new label (passed in), using CD records.
//
//---------------------------------------------------------------------------

void EditCDButtonLabel (LNString NewLabel, LNRichText *RT)
{
	LNINT					NewLength;
	CDBUTTON				Button;
	LNINT					Counter;
	LNCompositeData			CD;
	LNRTCursor				Cursor;
	LNSTATUS				Lnstatus;
	WORD					CDSig;

	// Modify the second button stored as a CD record

	// Initialize the counter - we need the SECOND button to modify.
	Counter = 0;
	// Get a cursor at the start of all the rich text
	RT->GetCursor(&Cursor);

	// Find the first composite data object

	Lnstatus = Cursor.GotoFirst(LNRTTYPE_COMPOSITE_DATA, &CD);
	if (Lnstatus != LNWARN_NOT_FOUND)
	{
		while (Counter != 2) 
		{
			// Get the signature from the composite object

			CDSig = CD.GetCDSignature();

			if (CDSig == SIG_CD_BUTTON) // IF found a button...
				Counter++;
			if (Counter == 2) // ...and it's the second one

			{	 
				// In order to change the label of the button,
				// we need to first read the data structure, then modify it,
				// and finally write it back.
				
				CD.ReadODS(_CDBUTTON, &Button);
	
				// Calculate the length of the new label and adjust the header length
				// appropriately
				NewLength = (NewLabel.GetByteCount());
				Button.Header.Length = (WORD)( ODSLength(_CDBUTTON) + NewLength );

				// Write the CDButton record into the LNCompositeData object.
				CD.WriteODS(_CDBUTTON, &Button);
		
				// Write the button title text after the CDButton record info.
				CD.Write( NewLength,  NewLabel.GetTextPtr(), ODSLength(_CDBUTTON));
		
			}

			// Otherwise, we have to look for more composite data records

			Lnstatus = Cursor.GotoNext(LNRTTYPE_COMPOSITE_DATA, &CD);
			if (Lnstatus == LNWARN_NOT_FOUND) // There are no more composite data records left.
			{
				cout << "Error, button not found." << endl;
				break;
			}
		
		}
		
	}
	
	 else
		 cout << "Error, no Composite Data objects found." << endl;

} // END EditCDButtonLabel()

//---------------------------------------------------------------------------
// Name:
//				DeleteButton
//
// Description:
//				Removes the button from the document
//
//---------------------------------------------------------------------------

void DeleteButton (LNDocument *CurDoc, LNButton *Button)
{
	LNRichText		RT;

	CurDoc->GetItem("Body", &RT);
	RT.Delete(Button);

} // END DeleteButton()

//---------------------------------------------------------------------------
// Name:
//				DeleteCDButton
//
// Description:
//				Removes the button from the document using CD records.
//
//---------------------------------------------------------------------------
void DeleteCDButton(LNRichText *RT)
{
	LNRTCursor			Cursor;
	LNCompositeData 	CDHotspotBegin, CDButton, CDHotspotEnd;
	LNINT				HotspotBeginCounter=0;
	LNSTATUS			Lnstatus;
	WORD				CDSig;
	LNBOOL				NotFound=FALSE;

	// Note:
	// In order to delete the button using CD records, we need to delete the HotspotBegin
	// records that precedes the button record, the Button record itself, and the
	// HotspotEnd record that follows the button record.
	// We should delete each of those records separately as opposed to passing the cursors
	// to the RichText::Delete() method and expecting it to delete everything between the cursors.
	// The reason for this requirement lies in the fact that there might be other CD records in 
	// the rich text that we are not aware of (e.g. SectionBegin record). If, by passing 
	// the cursors, we delete SectionBegin record but leave the SectionEnd record, this 
	// may mess up the document.

	RT->GetCursor(&Cursor);

	// Since we know that we inserted 3 buttons into the document, 
	// we can search for the 3rd HotspotBegin structure in order to locate the
	// records to be deleted.

	while (HotspotBeginCounter < 3) 
	{
		if (HotspotBeginCounter == 0)
			Lnstatus = Cursor.GotoFirst(LNRTTYPE_COMPOSITE_DATA, &CDHotspotBegin);

		  else
			Lnstatus = Cursor.GotoNext(LNRTTYPE_COMPOSITE_DATA, &CDHotspotBegin);
	
		if (Lnstatus == LNWARN_NOT_FOUND)
		{
			cout << "Error. Button cannot be found. Unable to delete it."  << endl;
			NotFound = TRUE;
			break;
		}
				
		CDSig =CDHotspotBegin.GetCDSignature();
		if (CDSig ==  SIG_CD_HOTSPOTBEGIN)
			HotspotBeginCounter++;

	}

	// OK, found the third HotspotBegin CD record.
	// Now we need to get a hold of the Button CD record that follows the HotspotBegin
	// and of the HotspotEnd CD record that goes after the Button CD record.
	// Once we got a hold of those objects, we can delete them.


	// Note!!!
	// Do not delete each record as soon as you get a hold of it.
	// If you delete the record right away, the pointer that was originally pointing to it
	// will now point to nothing, and will throw an error when you will try to use it
	// to locate the next CD record that you want to get a hold of.

	Cursor.GotoNext(LNRTTYPE_COMPOSITE_DATA, &CDButton);
	CDSig =   CDButton.GetCDSignature();
	if (CDSig != SIG_CD_BUTTON)
		NotFound = TRUE;

	Cursor.GotoNext	(LNRTTYPE_COMPOSITE_DATA, &CDHotspotEnd);
	CDSig = CDHotspotEnd.GetCDSignature();
	if (CDSig != SIG_CD_HOTSPOTEND)
		NotFound = TRUE;
	
	if (NotFound)
		cout << "Error. Cannot locate the button." << endl;
	else
	{
		RT->Delete(&CDHotspotBegin);
		RT->Delete(&CDButton);
		RT->Delete(&CDHotspotEnd);
	}

} // END DeleteCDButton()

//---------------------------------------------------------------------------
//
// Name:
//              ProcessArguments
//
// Description:
//				Scan the input command line and sort out the input strings.
//				If no arguments were supplied, prompt for them.
//
//				Throws exceptions:
//					char *          Argument error description
//
//---------------------------------------------------------------------------
void ProcessArguments ( int             argc,
						char            *argv[],
						LNString        *DatabasePath,
						LNString        *ServerPath,
						LNString        *ButtonTitle   )
{
	LNBOOL prompt = FALSE;

	if (argc < 2)
		prompt = TRUE;

	// Set up the default parameters first.
	InitDefaultParams();
	*ButtonTitle = ParamString1;
	*DatabasePath = ParamString2;
	*ServerPath = ParamString3;

	if (prompt)
	{
		// Get user input data.
		GetArguments();
		*ButtonTitle = ParamString1;
		*DatabasePath = ParamString2;
		*ServerPath = ParamString3;
	}
	else
	{
		// Get info from command line.
		if(argc > 1)
			*ButtonTitle = argv[1];
		if(argc > 2)
			*DatabasePath = argv[2];
		if(argc > 3)
			*ServerPath = argv[3];
	}

} // END ProcessArguments()

//---------------------------------------------------------------------------
//
// Name:
//              InitDefaultParams
//
// Description:
//              Set up all the default parameter strings and numbers for user
//              input.  Called by ProcessArguments() if no user input params
//              were provided.
//
//              NOTE:
//                      You only need to edit this function and ProcessArguments() 
//                      when creating a new sample.  The rest of the user interface 
//                      functions below are called by ProcessArguments() and are 
//                      generic, which means that they can stay the same unless
//                      you modify the number of parameters to use.
//                      Then you only need to cut or paste in your changes to
//                      the switch statements in the functions below.
//---------------------------------------------------------------------------
void InitDefaultParams()
{
	// Initialize default parameter strings.

	PromptString1   = "Button Title       : [";
	ParamString1    = "My New Button";

	PromptString2   = "NSF File Path Name : [";
	ParamString2    = "rtxtsamp.nsf";

	PromptString3   = "Server Path Name   : [";
	ParamString3    = "";

} // END InitDefaultParams()

//---------------------------------------------------------------------------
//
// Name:
//              GetArguments
//
// Description:
//              Allows the user to change any or all of the input parameter 
//              IOParameter.  The inputs can also be left as they are if desired.
//---------------------------------------------------------------------------
void GetArguments()
{

	BOOL IsCorrectData = FALSE;

	QueryArguments();

    while(! IsCorrectData)
    {
		PrintArguments();

		cout << "Are these current data settings correct? [Y] ";
		cin >> CommandBuf;

		switch( CommandBuf[0] )
		{
		case 'Y':
		case 'y':

			IsCorrectData = TRUE;                           // All done; get out now!
			break;

		default:

			// Prompt again for anything other than a "Y" or carriage return.
			if( (CommandBuf) != (const char *)"" )
				QueryArguments();
			else
				IsCorrectData = TRUE;                   // All done; get out now!

		} // END switch

	} // END while

} // END GetArguments()

//---------------------------------------------------------------------------
//
// Name:
//              PrintArguments
//
// Description:
//              Prints out all of the current input parameters to use.
//---------------------------------------------------------------------------
void PrintArguments()
{
	cout << endl;
	cout << "The current default data settings are: " << endl;
	cout << endl;
	cout << "     " << PromptString1 << ParamString1 << "]" << endl;
	cout << "     " << PromptString2 << ParamString2 << "]" << endl;
	cout << "     " << PromptString3 << ParamString3 << "]" << endl;
	cout << endl;

} // END PrintArguments()

//---------------------------------------------------------------------------
//
// Name:
//              QueryArguments
//
// Description:
//              Queries the user to change any of the input parameters.
//              A carriage return on any of the prompts leaves it alone.
//---------------------------------------------------------------------------
void QueryArguments()
{
	cout << endl;

	cout << "Enter " << PromptString1 << ParamString1 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString1 = CommandBuf;

	cout << "Enter " << PromptString2 << ParamString2 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString2 = CommandBuf;

	cout << "Enter " << PromptString3 << ParamString3 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString3 = CommandBuf;

} // END QueryArguments()




//===========================================================================
//
// IOPARAMETER	Class implementation
//
// Description: 
//              Implementation for a simple generic string buffer class
//              to hold user input and output prompts.
//===========================================================================

//===========================================================================
// Constructors.
//===========================================================================
IOParameter::IOParameter() // Default constructor.
{
	Size =1; // null terminator.
	
	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	BufferPointer[0] = '\0';
}

//===========================================================================
IOParameter::IOParameter( const char *Str ) // Init with const string.
{
	Size = strlen(Str) + 1;                                 // Size of string + null term.

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Str);
}


//===========================================================================
// Constructs a decimal radix string representation of an integer.
IOParameter::IOParameter( const int Number )
{
	char    Buffer[16];     // Temporary buffer for characters.

	sprintf(Buffer, "%d", Number);

	Size = strlen(Buffer) + 1;                         // Size of string + null term.

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Buffer);
}


//===========================================================================
IOParameter::IOParameter( const IOParameter &Other ) // Copy constructor.
{
	Size = Other.Size;

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Other.BufferPointer);
}

//===========================================================================
// Constructor using 2 IOParameter objects as input.
IOParameter::IOParameter( const IOParameter& Prefix, const IOParameter& Postfix)
{
	Size = Prefix.Size + Postfix.Size - 1;

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Prefix.BufferPointer);
	strcat(BufferPointer, Postfix.BufferPointer);
}

//===========================================================================
// Subscript, etc.
//===========================================================================
char IOParameter::operator [] (int Index)
{
char Character;

	if (Index > Size)
		Character = '\0';
	else
		Character = BufferPointer[Index];

	return Character;
}

//===========================================================================
// Assignment.
//===========================================================================
IOParameter IOParameter::operator = ( const IOParameter &Other )
{
	if(BufferPointer)
		delete [] BufferPointer;

	Size = Other.Size;
	
	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Other.BufferPointer);

	return *this;
}

//===========================================================================
IOParameter IOParameter::operator = ( const char *Str )
{
	Size = strlen(Str) +1;

	if (BufferPointer)
		delete [] BufferPointer;
	
	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, Str);
	return *this;
}

//===========================================================================
// I/O operators.
//===========================================================================
ostream &operator << ( ostream &Stream, const IOParameter &Other )
{
	Stream << Other.BufferPointer;
	return Stream;
}

//===========================================================================
istream &operator >> ( istream &Stream, IOParameter &Other )
{
	const int BufferLength = 255;       // Arbitrary size; change if needed.
	char T[BufferLength];                                                                                         // temp string... 
	int Length;					   
	for (Length=0; Length<BufferLength; Length++)
	{
		Stream.get(T[Length]);
		if (T[Length] == '\n')  // New line character.
			break;
		if (T[Length] == '\b')  // Backspace character.
		{
			if(Length)
			{
				Length--;
				// cout << "'\b'";  // For debug only.
			}
		}
	}

	T[Length] = '\0';
	Length++;

	if(Other.BufferPointer)
		delete [] Other.BufferPointer;

	if (! (Other.BufferPointer = new char[Length]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	Other.Size = Length;

	strcpy(Other.BufferPointer, T);
	return Stream;

} // END istream &operator >>

//===========================================================================
// Concatenate.
//===========================================================================
IOParameter IOParameter::operator + ( const IOParameter &Other ) // Cat 2 IOParameter objects.
{
	return IOParameter( *this, Other );
}

//===========================================================================
IOParameter IOParameter::operator + ( const char *Str ) // Cat IOParameter and string.
{
	return IOParameter( *this, IOParameter(Str) );
}

//===========================================================================
IOParameter operator + ( char *Str, const IOParameter &Other ) // Cat string with IOParameter.
{
	return IOParameter( IOParameter(Str), Other );
}

//===========================================================================
IOParameter& IOParameter::operator << ( const IOParameter &Other ) // Cat 2 IOParameter objects.
{
	IOParameter TempString(*this);

	Size = TempString.Size + Other.Size - 1;

	if (BufferPointer)
		delete [] BufferPointer;

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, TempString.BufferPointer);
	strcat(BufferPointer, Other.BufferPointer);

	return *this;
}

//===========================================================================
IOParameter& IOParameter::operator << ( const char *Str ) // Cat IOParameter and string.
{
	IOParameter TempString(*this);
	IOParameter Other(Str);

	Size = TempString.Size + Other.Size - 1;

	if (BufferPointer)
		delete [] BufferPointer;

	if(! (BufferPointer = new char[Size]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	strcpy(BufferPointer, TempString.BufferPointer);
	strcat(BufferPointer, Other.BufferPointer);

	return *this;   
}


