//===========================================================================
//
//	Module:	RTTABLE.CPP
//
//	Description:
//              Sample C++ API program that creates and modifies 
//				two rich text tables using the LNTable class.
//
//	Syntax:		RTTABLE	<dbname> [options]
//
//              Where dbname = file path name for the database to which you 
//              want to add the table. If you do not supply this parameter, 
//              you will be prompted for arguments at run time.
//              Supplying options without this parameter will
//              generate an error. If you supply this parameter alone,
//              all of the options will be set to their defaults.
//
//              "options" are one or more of the following in any order:
//							
//              R - Number of rows in the table. There cannot be a space 
//                  between the option letter and the number
//                  (i.e., "RTTABLE rtxtsamp.nsf r10"). Default = 3.
//
//              C - Number of columns in the table. There cannot be a 
//                  space between the option letter and the number
//                  (i.e., "RTTABLE rtxtsamp.nsf r10c15"). Default = 5.
//
//===========================================================================

#include <stdlib.h>
#include "rttable.hpp"

// Input parameter strings.

IOParameter		CommandBuf;
IOParameter		PromptString1;
IOParameter		ParamString1;

// Input parameter numbers.

IOParameter		PromptNumber1;
LNINT			ParamNumber1;
IOParameter		PromptNumber2;
LNINT			ParamNumber2;

//---------------------------------------------------------------------------
//
//	MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
int				ProgramStatus = 0;
LNNotesSession  Session;

	// Throw all errors encountered during command execution.

	LNSetThrowAllErrors (TRUE);

	try
	{	
	LNString 		DatabasePath;
	LNDatabase		DocDB;
	LNDocument		NewDoc;
	LNINT			Rows;
	LNINT			Cols;
	LNRichText		RT;
	LNText			Subject, Author;

		// Initialize the API.

		Session.Init( argc, argv );

		// Parse the argument list.

		ProcessArguments ( argc, argv, &DatabasePath, &Rows, &Cols );

		// Get the specified Notes database and open it.

		Session.GetDatabase( DatabasePath, &DocDB );
		DocDB.Open();

		// Create a new document in the database and open it.
		DocDB.CreateDocument(&NewDoc, "MainTopic");

		// Create the "Subject" and "From" fields.
		// NOTE: Make sure you pass in the LNITEMFLAGS_SUMMARY
		// when creating those items. Otherwise, the subject and the author
		// will not appear in the document listing.

		Subject.SetValue("Rttable");
		Author.SetValue("Sam Sample");
		NewDoc.CreateItem("From", Author, LNITEMFLAGS_SUMMARY);
		NewDoc.CreateItem("Subject", Subject, LNITEMFLAGS_SUMMARY);

		// Create the rich text "Body" field in the note.

		NewDoc.CreateItem("Body", &RT);
	
		// Add the new table to the current doc.

		AppendRTTable( &NewDoc, Rows, Cols );
		
		// Save and close the document

		NewDoc.Save();
		NewDoc.Close();

		// Close the database and set execution status to successful.

		DocDB.Close();
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

	// Terminate the API.
	Session.Term();

	return (ProgramStatus);

} // END MAIN

//---------------------------------------------------------------------------
//
// Name:
//		AppendRTTable
//
// Description:
//              Creates a rich text table and appends it to the body field of
//              the LNDocument passed in.
//---------------------------------------------------------------------------
void AppendRTTable( LNDocument *NewDoc, LNINT Rows, LNINT Cols )
{
	LNSTATUS		lnstatus;
	LNRichText		RT;
	LNRTCursor		Cursor1, Cursor2, SectionBeginCursor, SectionEndCursor;
	LNRTCursor		TableCursor;
	LNTable			Table1, Table2;
	LNTableCell		ThisCell1, ThisCell2;
	LNString		CellText;
	char			Buffer[80];
	LNNUMBER		Row, Col;
	LNString		SectionTitle, ButtonTitle;
	LNFormula		Formula("@Prompt([Ok];\"Greeting\";\"Hi, how are you?!\")");
	LNButton		Button1, Button2;
	
	// Get the rich text "Body" field from the document.  
	// We will append the table to it later.

	NewDoc->GetItem("Body", &RT);

	// Create a section that contains this table.
	// So we need to get a cursor before the table.

	RT.GetCursor(&SectionBeginCursor);

	// Append a string to the end of the field where the table will follow.

	RT << "\nThe New TABLE Goes Between Here:\n\n";
	RT << "\n\nAnd Here:\n";

	// Get a cursor at the end of this RT object and move it back to the
	// point between the two strings above.

	RT.GetEndCursor(&Cursor1);
	Cursor1-=12;

	// Create a new table just after the end cursor position.
	// This is more efficient than constructing a table on the stack and
	// then inserting it into the rich text because we can avoid an extra copy.

	RT.CreateTable(Rows, Cols, &Cursor1, &Table1);

	// Get an end cursor again and create a string section between the two
	// cursor positions.

	RT.GetEndCursor(&SectionEndCursor);
	SectionTitle = "Here is the table:";
	RT.CreateStringSection(SectionTitle, &SectionBeginCursor, &SectionEndCursor);

	// Get a cursor for the table positioned at the first cell: [R0:C0].

	Table1.GetCursor(&TableCursor);

	// Iterate through each row.

	for (Row=0; Row<(int)Rows; Row++)
	{
		// Iterate through each column.

		for (Col=0; Col<(int)Cols; Col++)
		{			
			// Add text in each cell that identifies its
			// row/column position. (i.e., "Cell: [R3:C5]")

			sprintf(Buffer, "Cell: [R%d:C%d]", Row, Col );

			// Insert the text in the current cell

			Table1.Insert( Buffer, &TableCursor );

			// Get the cell object for the current cursor position.
			// We can determine if the cursor is in a table cell,
			// and get a smart pointer to the table cell.

			lnstatus = TableCursor.GetParentContainer( LNRTTYPE_TABLE_CELL, &ThisCell1 );

			// Since we know the cursor is inside a table, it must be inside a 
			// table cell.

			if (lnstatus == LNWARN_NOT_FOUND) 
				throw ("Object is not in table cell");

			// Confirm that the table cell's row and columns match what we think
			// the cursor's position is.

			if ((ThisCell1.GetRowIndex() != Row) ||
				(ThisCell1.GetColumnIndex() != Col))
				throw ("The cursor is not in the correct table cell");

			// Find out which row and column we are on and, if on
			// an outside cell, remove the outer borders to make 
			// a tic-tac-toe-like structure.

			if (Row==0) // first row.
			{
				if (Col==0) // Left top corner.
				{
					// Remove left border.
					ThisCell1.SetLeftBorderWidth( LNTABLEBORDERTYPE_NONE );

					// Remove top border.
					ThisCell1.SetTopBorderWidth( LNTABLEBORDERTYPE_NONE );
				}
								
				else if (Col==(int)Cols-1) // Right top corner.
				{
					// Remove top border.

					ThisCell1.SetTopBorderWidth( LNTABLEBORDERTYPE_NONE );

					// Remove right border.

					ThisCell1.SetRightBorderWidth( LNTABLEBORDERTYPE_NONE );
				}
				else // Somewhere in middle of top row.
				{
					// Remove top border only.

					ThisCell1.SetTopBorderWidth( LNTABLEBORDERTYPE_NONE );
				}
			}
						
			else if (Row==(int)Rows-1) // Last row.
			{
				if ( Col==0) // Left bottom corner.
				{
					// Remove left border.

					ThisCell1.SetLeftBorderWidth( LNTABLEBORDERTYPE_NONE );
					
					// Remove bottom border.

					ThisCell1.SetBottomBorderWidth( LNTABLEBORDERTYPE_NONE );
				}
				else if (Col==(int)Cols-1) // Right bottom corner border.
				{
					// Remove right border.

					ThisCell1.SetRightBorderWidth( LNTABLEBORDERTYPE_NONE );

					// Remove bottom border.

					ThisCell1.SetBottomBorderWidth( LNTABLEBORDERTYPE_NONE );
				}
				else // Somewhere in middle of bottom row.
				{
					// Remove bottom border only.

					ThisCell1.SetBottomBorderWidth( LNTABLEBORDERTYPE_NONE );
				}
			}
			else // Any row in between.
			{
				if (Col==0) // Somewhere in middle of first left column.
				{
					// Remove left border only.

					ThisCell1.SetLeftBorderWidth( LNTABLEBORDERTYPE_NONE );
				}
				if (Col==(int)Cols-1) // Somewhere in middle of last right column.
				{
					// Remove right border only.

					ThisCell1.SetRightBorderWidth( LNTABLEBORDERTYPE_NONE );
				}

			} // END if(Row)

			TableCursor++; // Curser increments through table like reading a book.

		} // END (iterate Columns loop) 

	} // END (iterate Rows loop)

	// Now let's create another table and demonstrate a few other methods of
	// LNTable class.

	RT.Append("\n\nAnother table goes here:\n");
	RT.GetEndCursor(&Cursor1);
	Rows = 1;
	Cols = 2;
	RT.CreateTable(Rows, Cols, &Cursor1, &Table2);

	// Now let's append another row to this table.

	Table2.AppendRows(1);

	// Change the border style.
	// For some reason, this erases the "inside" borders of the table.
	// Filed an SPR about it.
	// Table2.SetBorderStyle(LNTABLEBORDERSTYLE_EMBOSSED);

	// Change the background color of the table

	Table2.SetBackgroundColor(LNCOLOR_CYAN);
	
	// Now we'll show how to insert and delete rich text items for a table cell
	// Let's create two buttons and delete one of them:
	// First choose the cells where to place the buttons

	ThisCell1 = Table2(1,1);
	ThisCell2 = Table2(0, 0);

	// Append a comment

	ThisCell1.Append("The button goes here: ");
	ThisCell2.Append("The button goes here: ");

	// Get the end cursors to place the buttons 

	ThisCell1.GetEndCursor(&Cursor1);
	ThisCell2.GetEndCursor(&Cursor2);

	// Create the buttons

	ButtonTitle = "Click Me!";
	ThisCell1.CreateButton(ButtonTitle, Formula,  &Cursor1, &Button1);
	ThisCell2.CreateButton(ButtonTitle, Formula,  &Cursor2, &Button2);
	
	// Now let's delete one of the buttons and replace the comment in that cell

	ThisCell2.Delete(&Button2);
	ThisCell2.SetValue("The button used to be here");

	// Save the note to disk.
	NewDoc->Save();

} // END AppendRTTable()

//---------------------------------------------------------------------------
//
// Name:
//		ProcessArguments
//
// Description:
//      Scan the input command line and sort out the input strings.
//      If no arguments were supplied, prompt for them.
//
//      Throws exceptions:
//              char *          Argument error description.
//---------------------------------------------------------------------------
void ProcessArguments ( int			argc,
						char		*argv[],
						LNString 	*DatabasePath,
						LNINT		*Rows,
						LNINT		*Cols   )
{
	LNBOOL Prompt = FALSE;

	if (argc < 2)
		Prompt = TRUE;

	// Set up the default parameters first.
	InitDefaultParams();
	*DatabasePath	= ParamString1;
	*Rows			= ParamNumber1;
	*Cols			= ParamNumber2;

	// Check the command line.
	if (Prompt)
	{
		// Get user input data by prompting.
		GetArguments();

		*DatabasePath	= ParamString1;
		*Rows			= ParamNumber1;
		*Cols			= ParamNumber2;
	}
	else
	{
		int I, J, Number;

		// Parse the command line strings.
		*DatabasePath = argv[1];

		// Parse the command line options.
		for(I=2; I<argc; I++)
		{
			char *argstring = argv[I];
			int Count = strlen(argstring);

			for (J=0; J<Count; J++)
			{
				switch (argstring[J])
				{
					case 'r':
					case 'R':
						if ( (Number = (LNINT)atoi( &argstring[(J+1)] ) ) ) 
							*Rows = Number;
						break;

					case 'c':
					case 'C':
						if ( (Number = (LNINT)atoi( &argstring[(J+1)] ) ) ) 
							*Cols = Number;
						break;
				}

			} // END for (J=0; J<Count; J++)

		} // END for(I=2; I<argc; I++)

	} // END if (argc < 2) ELSE

} // END ProcessArguments()

//---------------------------------------------------------------------------
//
// Name:
//		InitDefaultParams
//
// Description:
//		Set up all the default parameter strings and numbers for user
//              input.  Called by ProcessArguments() if no user input params
//		were provided.
//
//		NOTE:
//                      You only need to edit this funciton and ProcessArguments() 
//			when creating a new sample.  The rest of the user interface 
//                      functions below are called by ProcessArguments() and are 
//                      generic, which means that they can stay the same unless
//			you modify the number of parameters to use.
//			Then you only need to modify the case statements in the functions below.
//---------------------------------------------------------------------------
void InitDefaultParams()
{
	// Initialize default parameter strings.

	PromptString1 =  "File path name for the database to search     : [";
	ParamString1 = "rtxtsamp.nsf";

	// Initialize default parameter numbers.

	PromptNumber1 =  "Number of rows in the new table               : [";
	ParamNumber1 = 3;

	PromptNumber2 =  "Number of columns in the new table            : [";
	ParamNumber2 = 5;

} // END InitDefaultParams()

//---------------------------------------------------------------------------
//
// Name:
//		GetArguments
//
// Description:
//              Allows the user to change any or all of the input parameter 
//		IOParameter.  The inputs can also be left as they are if desired.
//---------------------------------------------------------------------------
void GetArguments()
{
	BOOL IsCorrectData = FALSE;

	QueryArguments();

	while(! IsCorrectData)
	{
		PrintArguments();

		cout <<      "Are these current data settings correct?      : [Y] ";
		cin >> CommandBuf;

		switch( CommandBuf[0] )
		{
			case 'Y':
			case 'y':

				IsCorrectData = TRUE;				// All done, get out now!
				break;

			default:

				// Prompt again for anything other than a "Y" or carriage return.
				if( (CommandBuf) != (const char *)"" )
					QueryArguments();
				else
					IsCorrectData = TRUE;			// All done, get out now!

		} // END switch

	} // END while

} // END GetArguments()

//---------------------------------------------------------------------------
//
// Name:
//		PrintArguments
//
// Description:
//		Prints out all of the current input parameters to use.
//---------------------------------------------------------------------------
void PrintArguments()
{
	cout << endl;
	cout << "The Current Default Data Settings are: " << endl;
	cout << endl;

	// Print out current parameter strings.
	cout << PromptString1 << ParamString1 << "]" << endl;

	// Print out current parameter numbers.
	cout << PromptNumber1 << ParamNumber1 << "]" << endl;
	cout << PromptNumber2 << ParamNumber2 << "]" << endl;
	cout << endl;

} // END PrintArguments()

//---------------------------------------------------------------------------
//
// Name:
//		QueryArguments
//
// Description:
//		Queries the user to change any of the input parameters.
//              A carriage return on any of the prompts leaves it alone.
//---------------------------------------------------------------------------
void QueryArguments()
{
	cout << endl;
	cout << "Enter the following parameters (Enter by itself takes the default):" << endl;
	cout << endl;

	// Prompt for strings.
	cout << PromptString1 << ParamString1 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamString1 = CommandBuf;


	// Prompt for numbers.
	cout << PromptNumber1 << ParamNumber1 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamNumber1 = (LNINT)CommandBuf.StringToInteger();

	cout << PromptNumber2 << ParamNumber2 << "]> ";
	cin >> CommandBuf;
	if( (CommandBuf) != (const char *)"" )
		ParamNumber2 = (LNINT)CommandBuf.StringToInteger();

} // END QueryArguments()


//===========================================================================
//
// IOPARAMETER Class Implementation
//
// Description:	
//              Implementation for a simple generic string buffer class
//		to hold user input and output prompts.
//===========================================================================

//===========================================================================
// Constructors
//===========================================================================
IOParameter::IOParameter() // Default constructor.
{
	Size =1; // Null terminator.
	
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
	Size = strlen(Str) + 1;					// Size of string + null term.

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
	char	Buffer[16];						// Temporary buffer for characters.

	sprintf(Buffer, "%d", Number);

	Size = strlen(Buffer) + 1;				// Size of string + null term.

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
	char Ch;

	if (Index > Size)
		Ch = '\0';
	else
		Ch = BufferPointer[Index];

	return Ch;
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
	const int BufferLength = 255;	// Arbitrary size, change if needed.
	char Temp[BufferLength];		// temp string... 
	int Length;

	for (Length=0; Length<BufferLength; Length++)
	{
		Stream.get(Temp[Length]);
		if (Temp[Length] == '\n')	// New line character
			break;
		if (Temp[Length] == '\b')	// Backspace character
		{
			if(Length)
			{
				Length--;
									
			}
		}
	}

	Temp[Length] = '\0';
	Length++;

	if(Other.BufferPointer)
		delete [] Other.BufferPointer;

	if (! (Other.BufferPointer = new char[Length]) )
	{
		cout << "IOParameter:  Allocation Error!!!" << endl;
		exit(1);
	}

	Other.Size = Length;

	strcpy(Other.BufferPointer, Temp);
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
IOParameter& IOParameter::operator << ( const char *Str ) 
// Cat IOParameter and string.
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


