//===========================================================================
//
// Module:		NSFLOG.CPP
//
// Description:	Implementation of the NSFlog class.
//
//===========================================================================

#ifndef NSFLOG_HPP
#include "nsflog.hpp"
#endif

//---------------------------------------------------------------------------
//
// Name:
//		Default Constructor
//
//---------------------------------------------------------------------------
NSFLog::NSFLog()
{ 
	LogSession		= 0; 
	isLogOpen		= FALSE;
}

//---------------------------------------------------------------------------
//
// Name:
//		Destructor
//
//---------------------------------------------------------------------------
NSFLog::~NSFLog( )
{
}

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::Open
//
// Description:
//		Opens the Log file for NSF Dump.  Also makes sure that the
//		Notes Session Object has been properly initialized and then
//		passes the pointer into this object for later use during the
//		Logging operations. 
//
// Inputs:
//		session		A pointer to an initialized Notes Session object
//		path:		Log file pathname
//
// Outputs:
//		If successful, The Log file is opened and ready for log entrys.
//		and the NSFLog object is now properly initialized for use.
//
// Returns:
//		Throws exception if there is an error.
//
//---------------------------------------------------------------------------
void NSFLog::Open( LNNotesSession *session, const LNString &path )
{
	// Open the log file
//	LogFile.open( (const char *)path, ios::out | ios::app );

//  LogFile.open( (const char *)path, ios::out, filebuf::sh_read );

    LogFile.open( (const char *)path, ios::out );

	if (!LogFile)
		throw "Cannot open log file";

	if (! LNIsNotesInitialized() )
		throw LNERR_SESSION_NOT_INITIALIZED;

	if (!session)
		throw LNERR_NULL_POINTER_PARAMETER;

	LogSession = session;

	isLogOpen = TRUE;

} // END NSFLog::Open

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::Close
//
// Description:
//		Closes the NFS Logfile for NSF Dump.
//
//---------------------------------------------------------------------------
LNSTATUS NSFLog::Close()
{
	if (! isLogOpen )
		return LNWARN_NOT_OPEN;

	// Close The Logfile.
	
	LogFile.close();
	isLogOpen = FALSE;

	return LNNOERROR;

} // END NSFLog::Close

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::CreateLogEntry
//
// Description:
//		All of the top level information about the 
//		.nsf file being dumped is added to the header area
//		of the Log file.
//
// Inputs:
//		The File Name of the .nsf file being dumped
//		The Title of the database that is being dumped.
//		The total number of documents contained in the .NSF file.
//
// Outputs:
//		The output Log file is updated.
//
//---------------------------------------------------------------------------
void NSFLog::CreateLogEntry( const LNString &NSFName, 
							 const LNString &DBTitle,
							 const LNNUMBER &TotalNotes )
{
	LNDatetime	Dt;
	LNString	TimeString;

	if (! isLogOpen )
		throw "Log file is not open!";

	// Get a Snapshot of the Current Date/Time 
	Dt = LogSession->GetCurrentDatetime();

	Dt.GetText(&TimeString);

	LogFile << "***************************************************************" << endl
			<< "***************************************************************" << endl
			<< "****************  Beginning Dump of NSF file  *****************" << endl
			<< "***************************************************************" << endl
			<< "***************************************************************" << endl
			<< endl
			<< "Current Date/Time                       " << TimeString 
			<< endl
			<< "Database Name:                          " << NSFName 
			<< endl
			<< "Database Title                          " << DBTitle 
			<< endl
			<< "Total Number of Notes                   " << TotalNotes 
			<< endl
			<< endl
			<< endl;

} // END NSFLog::CreateLogEntry

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::AddNewNoteHeader
//
// Description:
//		Creates A new Header in the Log File, for each Note found 
//		in the .nsf file being Dumped.
//
// Inputs:
//		Note        - The Current LNNote being dumped.
//		CurrentNote - A number that represents the current note's index
//					  position in the total number of notes in the 
//					  Database.
//		NumItems    - The total number of items contained in the note.
//
// Outputs:
//		A New Note header is added to the Log file.  It contains All
//		of the top level info about the new note being dumped.
//
// Remarks:
//		Of the Three NOTE FLAGS available in the NOTE Header you can
//		currently only get the state of one of them using the C++API.
//		this is NOTE_FLAG_ABSTRACTED and is retrieved using the 
//		LNDocument method: IsAbstracted() which returns an LNBOOL.
//		To get the others you must use the CAPI call:
//		NSFNoteGetInfo(hEditNOTE, _NOTE_FLAGS, &NoteFlags) See the
//		CAPI documentation under NOTE_FLAG_xxx for more info.
//---------------------------------------------------------------------------
void NSFLog::AddNewNoteHeader( LNNote &Note,
							   LNINT CurrentNote,
							   LNINT NumItems    )
{
	LNNOTETYPE	NoteType;
	LNString	TempString;

	// Append a new note Heading in the Log.
	LogMainHeading( "Beginning Dump Of The Next Note in the Database" );

	// Append the Note Number label to the Log.
	LogLabel( "Note Number          ", CurrentNote, 10 );

	// Append the number of fields to the Log.
	LogLabel( "Number of Fields     ", NumItems, 10 );

	// Get the Note's type or (Note Class).
	NoteType = Note.GetNoteType();

	// Append the next Label into the Log.
	LogLabel( "Current Note Type    ", GetNoteTypeString(NoteType) );

	// Append Notes's Originator ID data to the Log.
	LogOID(Note);
	
	//Append the Author Name to the log.
	LogLabel( "Note Author          ", Note.GetAuthor() );

	// Get the Created Date as an LNDatetime and convert to LNString.
	(Note.GetCreated()).GetText(&TempString);

	// Append the Note's creation time to the log.
	LogLabel( "Creation Date        ", TempString );

	// Get the Last Accessed time as an LNDatetime and convert to LNString.
	(Note.GetLastAccessed()).GetText(&TempString);

	// Append the Notes's Last Accessed time to the log.
	LogLabel( "Last Accessed time   ", TempString );

	// Get the Last Modified time as an LNDatetime and convert to LNString.
	(Note.GetLastModified()).GetText(&TempString);

	// Append the Note's Last Modified time to the log.
	LogLabel( "Last Modified time   ", TempString );

	// Append the Note's Note ID to the log.
	LogLabel( "Note ID              ", (LNINT)Note.GetNoteID(), 10 );

	// Append the Note size to the log.
	LogLabel( "Note size            ", (LNINT)Note.GetSize(), 10 );

} // END NSFLog::AddNewNoteHeader

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogMainHeading
//
// Description:
//		Appends a new peice of text to the Log. And formats it as
//		a Main Heading.
//
//---------------------------------------------------------------------------
void NSFLog::LogMainHeading( const LNString &Heading )
{
	LogFile << endl
            << "***************************************************************"
			<< endl
            << "***************************************************************"
			<< endl
			<< Heading
			<< endl
            << "***************************************************************"
			<< endl
			<< "***************************************************************"
			<< endl
			<< endl;

} // END NSFLog::LogMainHeading

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogNumberData
//
// Description:
//		Appends a new number value to the log file. 
//		The value is a number that gets converted to an ascii
//		string corresponding to the input base parameter (10 or hex)
//---------------------------------------------------------------------------
void NSFLog::LogNumberData( const LNINT Number, const LNINT base )
{	 
	// Append the Current Note Number value between the brackets.
	if (base == 10)
		LogFile	<< "[" << Number << "]";
	else 
	{
		LogFile.setf(ios::hex);
		LogFile	<< "[0x" << Number << "]";
		LogFile.unsetf(ios::hex);
	}

} // END NSFLog::LogNumberData

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogLabel
//
// Description:
//		Appends a new item label and it's value to the log. 
//		The value is a number that gets converted to an ascii
//		string corresponding to the input base parameter (10 or hex)
//---------------------------------------------------------------------------
void NSFLog::LogLabel( const LNString &Label,
					   const LNINT Number,
					   const LNINT base       )
{
	// Append the Current Note Number value between the brackets.
	if (base == 10)
		LogFile	<< Label << "[" << Number << "]" << endl; 
	else
	{
		LogFile.setf(ios::hex);
		LogFile	<< Label << "[0x" << Number << "]" << endl;
		LogFile.unsetf(ios::hex);
	}

} // END NSFLog::LogLabel

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogLabel
//
// Description:
//		Appends a new item label and it's value to the log. 
//		The value is also a string.
//---------------------------------------------------------------------------
void NSFLog::LogLabel( const LNString &Label, const LNString &StrValue)
{
	// Append the Current Note Number value between the brackets.

	LogFile	<< Label << "[" << StrValue << "]" << endl;

} // END NSFLog::LogLabel

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogLabelWithHexTimeDate
//
// Description:
//		Appends The Hex value of a TIMEDATE to the Log using a ostrstream 
//		object to convert it to text. The data is formatted as plain text.
//
//---------------------------------------------------------------------------
void NSFLog::LogLabelWithHexTimeDate( const char *pString, const TIMEDATE &Td )
{	 
	char	Buf[128];

	// Make up the timedate Hex string.
	sprintf(Buf, "%s[0x%X] - [0x%X]", pString, (int)Td.Innards[1], (int)Td.Innards[0] );

	// Append the Hex value for the Time Date to the Log.
	LogFile	<< Buf << endl;

} // END NSFLog::LogLabelWithHexTimeDate

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogOID
//
// Description:
//		Gets the Note's OID and appends it's timedate 
//		data to the Log File.
//
//---------------------------------------------------------------------------
void NSFLog::LogOID( LNNote &Note )
{	 
	OID		* poidNote;

	// Append the Note's OID Heading to the Log.

	LogFile	<< endl << "Note Origionator ID:" << endl;

	// Get the Note's OID. 
	if ( (poidNote = Note.GetOriginatorID()) == (OID*)NULL )
	{
		// Add a Note in the Log indicating the Note OID is not available.
		LogLabel( "   OID.File           ", "UNAVAILABLE" );

		return;
	}

	// Append the Hex value for the OID File member to the Log.
	LogLabelWithHexTimeDate( "   OID.File          ", poidNote->File );

	// Append the Hex value for the OID Note member to the Log.
	LogLabelWithHexTimeDate( "   OID.Note          ", poidNote->Note );

	// Append the Hex value for the OID Sequence member to the Log.
	LogLabel( "   OID.Sequence      ", poidNote->Sequence, 10 );

	// Append the Hex value for the OID SequenceTime member to the Log.
	LogLabelWithHexTimeDate( "   OID.SequenceTime  ", poidNote->SequenceTime );

	LogFile	<< endl;

} // END NSFLog::LogOID

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::AddNewItem
//
// Description:
//		Information about the current item in the current note being 
//		dumped is appended to the log file.
//
//		All of the top level info about the current item being dumped is
//		added first and then the ProcessItemType() method is called to do
//		field specific processing and logging as needed.
//
// Inputs:
//		Item		The current note item being processed.
//		CurrentItem	The current item's index position in it's
//					notes item array.
// Outputs:
//		All available information about the current field is logged.
//
//---------------------------------------------------------------------------
void NSFLog::AddNewItem( LNItem &Item, LNINT CurrentItem )
{
	LNString	LogEntryString;
	LNITEMTYPE	ItemType;
	WORD		ItemClass;

	// Append a heading to indicate this is a new item being dumped.
	LogFile << endl
			<< "*************************" << endl
			<< "Note Item: [" << CurrentItem << "]" << endl
			<< "*************************" << endl
			<< endl;

	// Append item's Name to the log.
	LogLabel( "Item Name        ", Item.GetName() );

	ItemType = Item.GetType();

	// Append the Item Type to the log.
	LogLabel( "Item Type        ", GetItemTypeString(ItemType) );

	ItemClass = ( (WORD)ItemType & CLASS_MASK );

	// Append the Item's Class to the log.
	LogLabel( "Item Class       ", GetItemClassString(ItemClass) );

	// Append the Item's Size to the log.
	LogLabel( "Field Size       ", Item.GetValueSize(), 10 );

	// Append the Field Flags Info to the Log.
	LogItemFlags( Item.GetFlags() );

	// This next method call Will do the rest of the processing
	// on the current Item and implements what is done under the 
	// switch (wDataType) statement in the DumpOneItem() function 
	// in NSF_DUMP.
	ProcessItemType(Item, ItemType);

} // END NSFLog::AddNewItem

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::ProcessItemType
//
// Description:
//		This method Logs the Non Header Information on the current Item 
//		and implements what is done in the switch (wDataType) statement 
//		in the DumpOneItem() function of the CAPI Sample app NSF_DUMP.
//
// Inputs:
//		ItemType
//
// Outputs:
//		All non header information about the current field is logged.
//
// Remarks:
//
// The following Item Data Types have been defined by version 4.01 of
// the C++ API.  NOTE: More, have been added since, and more will be
// added in the future.
//
// C++ API Symbol               C API Symbol(s) that map to it.
// -----------------------------------------------------------------------
// LNITEMTYPE_DATETIMES			TYPE_TIME_RANGE
// LNITEMTYPE_ERROR				TYPE_ERROR
// LNITEMTYPE_FONTTABLE			TYPE_COMPOSITE      
// LNITEMTYPE_FORMULA			TYPE_FORMULA
// LNITEMTYPE_ICON				TYPE_ICON
// LNITEMTYPE_NOTELINKS			TYPE_NOTELINK_LIST
// LNITEMTYPE_NOTEREFS			TYPE_NOTEREF_LIST
// LNITEMTYPE_NUMBERS			TYPE_NUMBER_RANGE (also) TYPE_NUMBER
// LNITEMTYPE_OBJECT			TYPE_OBJECT
// LNITEMTYPE_RICHTEXT			TYPE_COMPOSITE
// LNITEMTYPE_SIGNATURE			TYPE_SIGNATURE
// LNITEMTYPE_TEXT				TYPE_TEXT_LIST  (also) TYPE_TEXT    
// LNITEMTYPE_UNAVAILABLE		TYPE_UNAVAILABLE
// LNITEMTYPE_UNSUPPORTED		TYPE_INVALID_OR_UNKNOWN
// LNITEMTYPE_USERDATA			TYPE_USERDATA
//
// New Item types that have been implemented in the 2.1 release of
// the C++ API Toolkit:  (Need to implement these here... ***dhs)
//
// LNITEMTYPE_ACTION            TYPE_ACTION
// LNITEMTYPE_ASSISTANT_INFO    TYPE_ASSISTANT_INFO
// LNITEMTYPE_CALENDAR_FORMAT   TYPE_CALENDAR_FORMAT
// LNITEMTYPE_COLLATION         TYPE_COLLATION
// LNITEMTYPE_FORM_VIEW_ACTION	(TYPE_COMPOSITE | LNITEMTYPE_SPECIAL | LNITEMTYPE_COMPOSITE_ACTION_FLAG)
// LNITEMTYPE_HIGHLIGHTS		TYPE_HIGHLIGHTS
// LNITEMTYPE_HTML				TYPE_HTML
// LNITEMTYPE_LSOBJECT			TYPE_LSOBJECT
// LNITEMTYPE_OLE_OBJECT		(TYPE_COMPOSITE | LNITEMTYPE_SPECIAL | LNITEMTYPE_COMPOSITE_OLE_FLAG)
// LNITEMTYPE_QUERY             TYPE_QUERY
// LNITEMTYPE_SCHED_LIST        TYPE_SCHED_LIST
// LNITEMTYPE_SEAL				TYPE_SEAL
// LNITEMTYPE_SEALDATA			TYPE_SEALDATA
// LNITEMTYPE_SEAL_LIST		    TYPE_SEAL_LIST
// LNITEMTYPE_USERID			TYPE_USERID
// LNITEMTYPE_VIEW_FORMAT		TYPE_VIEW_FORMAT
// LNITEMTYPE_VIEWMAP_DATASET	TYPE_VIEWMAP_DATASET
// LNITEMTYPE_VIEWMAP_LAYOUT	TYPE_VIEWMAP_LAYOUT
// LNITEMTYPE_WORKSHEET_DATA	TYPE_WORKSHEET_DATA
//
//---------------------------------------------------------------------------
void NSFLog::ProcessItemType( LNItem &Item, LNITEMTYPE ItemType )
{
	switch (ItemType)
	{
		case LNITEMTYPE_ERROR :
		case LNITEMTYPE_UNAVAILABLE :
		case LNITEMTYPE_UNSUPPORTED :
			break;

		case LNITEMTYPE_TEXT :
			LogTextItem( Item );
			break;

		case LNITEMTYPE_NUMBERS :
			LogNumbersItem( Item );
			break;

		case LNITEMTYPE_DATETIMES :
			LogDateTimesItem( Item );
			break;

		case LNITEMTYPE_FORMULA :
			LogUndefinedItem( );
			break;

		case LNITEMTYPE_RICHTEXT :
			ProcessRichTextItem( Item );
			break;

		case LNITEMTYPE_FONTTABLE :
			ProcessFontTableItem( Item );
			break;

		case LNITEMTYPE_ICON :
			LogUndefinedItem( );
			break;

	    case LNITEMTYPE_NOTEREFS :
			LogUndefinedItem( );
	        break;

	    case LNITEMTYPE_SIGNATURE :
			LogUndefinedItem( );
	        break;

	    case LNITEMTYPE_NOTELINKS :
			LogUndefinedItem( );
			break;

	    case LNITEMTYPE_OBJECT :
			LogUndefinedItem( );
	        break;

	    case LNITEMTYPE_USERDATA :
			LogUndefinedItem( );
	        break;

	//	case TYPE_USERID :
			// Type USERID is not supported by the C++ API
			// and is obsolete In Notes Version 3.0 or later.
	//		break;

		case TYPE_SEAL:
			LogUndefinedItem( );
			break;

	    case TYPE_SEALDATA:
			LogUndefinedItem( );
			break;

	    case TYPE_SEAL_LIST:
			LogUndefinedItem( );
			break;

	    case TYPE_HIGHLIGHTS:
			LogUndefinedItem( );
			break;

	    case TYPE_WORKSHEET_DATA:
			LogUndefinedItem( );
			break;

	    case TYPE_COLLATION:
			LogUndefinedItem( );
			break;

		default:
			// Item Type Unknown or Unexposed.
			break;

	} // END switch (ItemType)

} // END NSFLog::ProcessItemType

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogTextItem
//
// Description:
//		Extracts all of the Text elements from the LNText object.
//		Converts each element to an LNString and Appends it
//		to the Log file.
//---------------------------------------------------------------------------
void NSFLog::LogTextItem( const LNItem &Item )
{	
	LNINT	Count, i; 
	LNText	TempText;

	TempText = Item;
	Count = TempText.GetCount();

	LogFile << endl << "Dump Of Text Data Follows:" << endl;

	for (i = 0; i<Count; i++)
	{
		LogFile << "     [" << (LNString)TempText[i] << "]" << endl;
	}

} // END NSFLog::LogTextItem

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogNumbersItem
//
// Description:
//		Extracts all of the Number elements from the LNNumbers object.
//		Converts each element to an LNString and Appends it to the
//		Log file.
//---------------------------------------------------------------------------
void NSFLog::LogNumbersItem( const LNItem &Item )
{
	LNINT		Count, i; 
	LNNumbers	TempNumber;
	LNNumber	Number;
	LNString	TempString;

	TempNumber = Item;
	Count = TempNumber.GetCount();

	LogFile << "     Dump Of Number Data Follows:" << endl << endl;

	for (i = 0; i<Count; i++)
	{
		Number = (LNNUMBER)TempNumber[i];
		Number.GetText( &TempString );

		LogFile << "          [" << TempString << "]" << endl;
	}

	LogFile << endl;

} // END NSFLog::LogNumbersItem

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogDateTimesItem
//
// Description:
//		Extracts all of the Date Time elements from the LNDatetimes object.
//		Converts each element to an LNString and Appends it to the
//		Log file.
//---------------------------------------------------------------------------
void NSFLog::LogDateTimesItem( const LNItem &Item )
{	
	LNINT		Count, i; 
	LNDatetimes	TempDates;
	LNDatetime	Date;
	LNString	TempString;

	TempDates = Item;
	Count = TempDates.GetCount();

	LogFile << "     Dump Of Date Data Follows:" << endl << endl;

	for (i = 0; i<Count; i++)
	{
		Date = (LNDatetime)TempDates[i];
        if (!Date.IsSpecialCase())
            Date.GetText( &TempString );
        else
            TempString = "Date Time is Special Case";

		LogFile << "          [" << TempString << "]" << endl;
	}

	LogFile << endl;

} // END NSFLog::LogDateTimesItem

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogUndefinedItem
//
// Description:
//		This funciton is just a placeholder function for Items that
//		have not been defined as Classes in C++ API.
//		To further process these items you must use CAPI functions.
//		It Appends to the log file a message that the item is not defined 
//		as a C++ API class.
//
//---------------------------------------------------------------------------
void NSFLog::LogUndefinedItem()
{
	LogFile << endl 
			<< "This Item has not been defined as a C++ API Class." << endl
			<< "Use NSF calls to further process and display it." << endl
			<< endl;

} // END NSFLog::LogUndefinedItem

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::ProcessRichTextItem
//
// Description:
//		This method processes any Items that are abstracted by the C++
//		API as Rich Text, which includes all Composite Data Records,
//		Stylized Text, Font Styles, Icons, etc...  Because Rich Text can
//		contain sub objects, such as in the case of Stylized Text 
//		(i.e. Font Styles etc.) this method contains a loop which itterates 
//		through the rich text field looking for sub items and calls methods 
//		that process those objects even further.
//
//---------------------------------------------------------------------------
void NSFLog::ProcessRichTextItem( const LNItem &Item )
{
	LNRichText		Rt;
	LNRTCursor		Curser;
	LNRTObject		Obj;
	LNRTContainer	Container;
	LNBOOL			isObjFound;
	LNINT			i;

	// Get The Item as a Rich Text Object.
	Rt = Item;

	// Get a Curser object which will be pointing
	// to the left of the first element in the RT field.
	Rt.GetCursor( &Curser );

	// Begin processing all objects contained in this RT Field.
	isObjFound = TRUE;
	for (i=1; isObjFound; i++)
	{
		// Get The Object to the Right of the Curser Position.
		if ( Curser.GetObject( &Obj ) == LNWARN_NOT_FOUND )
		{
			isObjFound = FALSE;
		}
		// Find out what type of Rich Text Type this Object is and process it.
		else if ( Obj.IsType( LNRTTYPE_STYLIZED_TEXT ) )
		{
			// Process and Append info about the Stylized text to the Log.
			ProcessStylizedText( Obj, i );

			// Position the Curser to the right of the last element
			// in this Stylized Text Object. (Must use as Contaier Object)
			Container = Obj;
			Curser.GotoEnd( Container );
		}
		else if ( Obj.IsType( LNRTTYPE_COMPOSITE_DATA ) )
		{
			// Process and Append info about the CD Record to the Log.
			ProcessCompositeData( Obj, i );

			// Put the curser on the next element in the RT field.
			// This will not error if it is the last element.  It
			// just stays where it is and the above GetObject call will
			// return NOT FOUND to terminate the loop.
			Curser++;
		}
		else
		{
			// Add a heading for the UN-EXPOSED OR UNKNOWN record to be logged.
			LogUnexposedCDRHeading( i );

			// Put the curser on the next element in the RT field.
			Curser++;
		}

	} // END for (i=1; isObjFound; i++)

} // END NSFLog::ProcessRichTextItem

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogUnexposedCDRHeading
//
// Description:
//		Appends a heading to record the encounter with an unknown or 
//		un-exposed CD record in the C++ API.  These records have to
//		be processed using CAPI calls, (i.e. NSF_DUMP) to be logged.
//
//---------------------------------------------------------------------------
LNSTATUS NSFLog::LogUnexposedCDRHeading( const LNINT recordcount )
{
	LogFile << "     Un-Exposed or Unknown CD Record [";
	LogNumberData( recordcount, 10 );
	LogFile << "]" << endl;

	return LNNOERROR;

} // END NSFLog::LogUnexposedCDRHeading

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::ProcessStylizedText
//
// Description:
//		Processes and Logs data about the current Rich Text Object
//		which has been determined to be a Stylized Text Object. 
//
// Remarks:	
//		LNFontStyle::GetCDFace and LNFontStyle::GetFontID 
//		could have been called here to get the
//		lower level font records needed for doing things 
//		in combination with C API calls.  However, calling it
//		here is not necessary since higher level objects have
//		taken care of all that detail for us.
//---------------------------------------------------------------------------
void NSFLog::ProcessStylizedText( const LNRTObject &Obj, const LNINT recordcount )
{	
	LNStylizedText	StyleText;
	LNFontStyle		FontStyle;
	LNString		TextBuf;

	StyleText = Obj;

	LogFile << endl;

	// Add a heading for the record to be logged.
	LogLabel( "     CD Record", recordcount, 10);

	// Get the Font Style of the Stylized text.
	StyleText.GetFontStyle( &FontStyle );

	// Append the font style attribues flags info to the Log.
	LogFontAttributes( FontStyle.GetAttributes() );

	// Append the font's Color to the Log. Expressed as an 
	// integer from 0-239. Colors 0-15 have symbolic names 
	// (e.g., LNCOLOR_BLACK)
	LogLabel( "          Font Color: ", GetFontColorString( FontStyle.GetColor() ) );

	// Append the font Face ID to the Log.
	LogLabel( "          Font Face ID: ", GetFontFaceString( FontStyle.GetFaceID() ) );

	// Append the font point size to the Log.
	LogLabel( "          Font Point Size: ", FontStyle.GetPointSize(), 10 );

	// Append the Text String of this segment of stylized text to the Log.
	StyleText.GetText( &TextBuf );
	LogLabel("          Dump Of Stylized Text Data Follows:\n               ", TextBuf );

} // END NSFLog::ProcessStylizedText

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogFontAttributes
//
// Description:
//		Logs data about the current Font Styles Font Attribute flags
//		by checking each bit in the bitfield and loging it if set. 
//
//---------------------------------------------------------------------------
void NSFLog::LogFontAttributes( const LNFONTATTRIBUTEFLAGS FontFlags )
{
	// Append a heading to indicate the following are Font Attribute Flags.
	LogFile << "          Font Attribute Flags That Are Set:" << endl;

	// Log all the flags that are set.
	if ( FontFlags & LNFONTATTRIBUTEFLAGS_BOLD )
		LogFile << "               LNFONTATTRIBUTEFLAGS_BOLD" << endl;

	if ( FontFlags & LNFONTATTRIBUTEFLAGS_ITALIC )
		LogFile << "               LNFONTATTRIBUTEFLAGS_ITALIC" << endl;

	if ( FontFlags & LNFONTATTRIBUTEFLAGS_UNDERLINE )
		LogFile << "               LNFONTATTRIBUTEFLAGS_UNDERLINE" << endl;

	if (FontFlags & LNFONTATTRIBUTEFLAGS_STRIKETHROUGH )
		LogFile << "               LNFONTATTRIBUTEFLAGS_STRIKETHROUGH" << endl;

	if (FontFlags & LNFONTATTRIBUTEFLAGS_SUPERSCRIPT )
		LogFile << "               LNFONTATTRIBUTEFLAGS_SUPERSCRIPT" << endl;

	if (FontFlags & LNFONTATTRIBUTEFLAGS_SUBSCRIPT )
		LogFile << "               LNFONTATTRIBUTEFLAGS_SUBSCRIPT" << endl;

	if ( FontFlags == LNFONTATTRIBUTEFLAGS_PLAIN )
		LogFile << "               LNFONTATTRIBUTEFLAGS_PLAIN" << endl;

} // END NSFLog::LogFontAttributes

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::GetFontColorString
//
// Description:
//		Translates the Font Color Symbol value into a string or an 
//		string value representing any integers passed in greater than 15.
//
//---------------------------------------------------------------------------
LNString NSFLog::GetFontColorString( const LNCOLOR FontColor )
{	
	char	Buf[20];

	switch (FontColor)
	{
		case LNCOLOR_BLACK :	
			return "LNCOLOR_BLACK";

		case LNCOLOR_WHITE :	
			return "LNCOLOR_WHITE";

		case LNCOLOR_RED :	
			return "LNCOLOR_RED";

		case LNCOLOR_GREEN :	
			return "LNCOLOR_GREEN";

		case LNCOLOR_BLUE :	
			return "LNCOLOR_BLUE";

		case LNCOLOR_MAGENTA :	
			return "LNCOLOR_MAGENTA";

		case LNCOLOR_YELLOW :	
			return "LNCOLOR_YELLOW";

		case LNCOLOR_CYAN :	
			return "LNCOLOR_CYAN";

		case LNCOLOR_DARK_RED :	
			return "LNCOLOR_DARK_RED";

		case LNCOLOR_DARK_GREEN :	
			return "LNCOLOR_DARK_GREEN";

		case LNCOLOR_DARK_BLUE :	
			return "LNCOLOR_DARK_BLUE";

		case LNCOLOR_DARK_MAGENTA :	
			return "LNCOLOR_DARK_MAGENTA";

		case LNCOLOR_DARK_YELLOW :	
			return "LNCOLOR_DARK_YELLOW";

		case LNCOLOR_DARK_CYAN :	
			return "LNCOLOR_DARK_CYAN";

		case LNCOLOR_GRAY :	
			return "LNCOLOR_GRAY";

		case LNCOLOR_LIGHT_GRAY :	
			return "LNCOLOR_LIGHT_GRAY";

		default :

			sprintf(Buf, "%d", (int)FontColor);
			return (LNString)Buf;

	} // END switch (FontColor);

} // END NSFLog::GetFontColorString

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::GetFontFaceString
//
// Description:
//		Translates the Font Face ID Symbol value into a string 
//		representing the symbol that it represents.
//
//---------------------------------------------------------------------------
LNString NSFLog::GetFontFaceString( const LNFACEID FaceID )
{	
	switch (FaceID)
	{
		case LNFACEID_ROMAN :	
			return "LNFACEID_ROMAN";

		case LNFACEID_HELVETICA :	
			return "LNFACEID_HELVETICA";

		case LNFACEID_COURIER :	
			return "LNFACEID_COURIER";

		default:
			return "UNKNOWN OR UNEXPOSED";

	} // END switch (FaceID);

} // END NSFLog::GetFontFaceString

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::ProcessCompositeData
//
// Description:
//		Processes and Logs data about the current Rich Text Object which 
//		has been determined to be a Composite Data Record. 
//
// Remarks:
//
// The following is a Reference of Signatures for Composite Records 
// in items of data type COMPOSITE from ODS.H
// The ones with an asterisk ("*") are logged here.  
// SIG_CD_GRAPHIC and SIG_CD_BUTTON are fully processed.  
// The rest would be processed the same way and are left as a user exersize.
// (I dont have time to implement or maintain all of them!)
//
// * SIG_CD_PARAGRAPH
// * SIG_CD_PABDEFINITION
// * SIG_CD_PABREFERENCE
// * SIG_CD_TEXT
// * SIG_CD_HEADER
// * SIG_CD_LINKEXPORT2
// * SIG_CD_BITMAPHEADER
// * SIG_CD_BITMAPSEGMENT
// * SIG_CD_COLORTABLE
// * SIG_CD_GRAPHIC
// * SIG_CD_PMMETASEG
// * SIG_CD_WINMETASEG
// * SIG_CD_MACMETASEG
// * SIG_CD_CGMMETA
// * SIG_CD_PMMETAHEADER
// * SIG_CD_WINMETAHEADER
// * SIG_CD_MACMETAHEADER
// * SIG_CD_TABLEBEGIN
// * SIG_CD_TABLECELL
// * SIG_CD_TABLEEND
// * SIG_CD_STYLENAME
//
// Signatures for Composite Records that are reserved internal
// records, as of API release 4.1 Their format may change between releases.
//
// SIG_CD_DOCUMENT_PRE_26
// SIG_CD_FIELD_PRE_36
// SIG_CD_FIELD
// SIG_CD_DOCUMENT
// SIG_CD_METAFILE
// SIG_CD_BITMAP
// SIG_CD_FONTTABLE
// SIG_CD_LINK
// SIG_CD_LINKEXPORT
// SIG_CD_KEYWORD
// SIG_CD_LINK2
// SIG_CD_CGM
// SIG_CD_TIFF
// SIG_CD_PATTERNTABLE
// SIG_CD_DDEBEGIN
// SIG_CD_DDEEND
// SIG_CD_OLEBEGIN
// SIG_CD_OLEEND
// SIG_CD_HOTSPOTBEGIN
// SIG_CD_HOTSPOTEND
// * SIG_CD_BUTTON
// SIG_CD_BAR
// SIG_CD_V4HOTSPOTBEGIN
// SIG_CD_V4HOTSPOTEND
// SIG_CD_EXT_FIELD
// SIG_CD_LAYOUT
// SIG_CD_LAYOUTTEXT
// SIG_CD_LAYOUTEND
// SIG_CD_LAYOUTFIELD
// SIG_CD_PABHIDE
// SIG_CD_PABFORMREF
// SIG_CD_ACTIONBAR
// SIG_CD_ACTION
// SIG_CD_DOCAUTOLAUNCH
// SIG_CD_LAYOUTGRAPHIC
// SIG_CD_LAYOUTBUTTON
//
//	Saved Query records for items of type TYPE_QUERY
//
// SIG_QUERY_HEADER
// SIG_QUERY_TEXTTERM
// SIG_QUERY_BYFIELD
// SIG_QUERY_BYDATE
// SIG_QUERY_BYAUTHOR
// SIG_QUERY_FORMULA
// SIG_QUERY_BYFORM
// SIG_QUERY_BYFOLDER
// SIG_QUERY_USESFORM
// SIG_QUERY_TOPIC
//
//	Save Action records for items of type TYPE_ACTION
//
// SIG_ACTION_HEADER
// SIG_ACTION_MODIFYFIELD
// SIG_ACTION_REPLY
// SIG_ACTION_FORMULA
// SIG_ACTION_LOTUSSCRIPT
// SIG_ACTION_SENDMAIL
// SIG_ACTION_DBCOPY
// SIG_ACTION_DELETE
// SIG_ACTION_BYFORM
// SIG_ACTION_MARKREAD
// SIG_ACTION_MARKUNREAD
// SIG_ACTION_MOVETOFOLDER
// SIG_ACTION_COPYTOFOLDER
// SIG_ACTION_REMOVEFROMFOLDER
// SIG_ACTION_NEWSLETTER
// SIG_ACTION_RUNAGENT
// SIG_ACTION_SENDDOCUMENT
// SIG_ACTION_FORMULAONLY
//
// Signatures for items of type TYPE_VIEWMAP_DATASET
//
// SIG_VIEWMAP_DATASET
//
// Signatures for items of type TYPE_VIEWMAP
//
// SIG_CD_VMHEADER
// SIG_CD_VMBITMAP
// SIG_CD_VMRECT
// SIG_CD_VMPOLYGON
// SIG_CD_VMPOLYLINE
// SIG_CD_VMREGION
// SIG_CD_VMACTION
// SIG_CD_VMELLIPSE
// SIG_CD_VMRNDRECT
// SIG_CD_VMBUTTON
// SIG_CD_VMTEXTBOX
//
// 188-191 available for more TYPE_VIEWMAP records.
//
// SIG_CD_VMPOLYRGN
//
//---------------------------------------------------------------------------
void NSFLog::ProcessCompositeData( const LNRTObject &Obj, const LNINT recordcount )
{
	LNCompositeData	CD;
	WORD			cdsignature;

	CD = Obj;

	LogFile << endl;

	// Add a heading for the record to be logged.

	LogLabel( "     CD Record ", recordcount, 10);

	cdsignature = CD.GetCDSignature();

	switch ( cdsignature )
	{
		case SIG_CD_GRAPHIC :
			LogCDGraphic( CD );
			break;

		case SIG_CD_BUTTON :
			LogCDButton( CD );
			break;

		// The Rest of the CD Signatures just print out the type
		// First two were expanded as an example for the user
		// The rest of them will process the same way...

		case SIG_CD_PARAGRAPH :
			LogCDSignature( "SIG_CD_PARAGRAPH" );
			break;

		case SIG_CD_PABDEFINITION :
			LogCDSignature( "SIG_CD_PABDEFINITION" );
			break;

		case SIG_CD_PABREFERENCE :
			LogCDSignature( "SIG_CD_PABREFERENCE" );
			break;

		case SIG_CD_TEXT :
			LogCDSignature( "SIG_CD_TEXT" );
			break;

		case SIG_CD_HEADER :
			LogCDSignature( "SIG_CD_HEADER" );
			break;

		case SIG_CD_LINKEXPORT2 :
			LogCDSignature( "SIG_CD_LINKEXPORT2" );
			break;

		case SIG_CD_BITMAPHEADER :
			LogCDSignature( "SIG_CD_BITMAPHEADER" );
			break;

		case SIG_CD_BITMAPSEGMENT :
			LogCDSignature( "SIG_CD_BITMAPSEGMENT" );
			break;

		case SIG_CD_COLORTABLE :
			LogCDSignature( "SIG_CD_COLORTABLE" );
			break;

		case SIG_CD_PMMETASEG :
			LogCDSignature( "SIG_CD_PMMETASEG" );
			break;

		case SIG_CD_WINMETASEG :
			LogCDSignature( "SIG_CD_WINMETASEG" );
			break;

		case SIG_CD_MACMETASEG :
			LogCDSignature( "SIG_CD_MACMETASEG" );
			break;

		case SIG_CD_CGMMETA :
			LogCDSignature( "SIG_CD_CGMMETA" );
			break;

		case SIG_CD_PMMETAHEADER :
			LogCDSignature( "SIG_CD_PMMETAHEADER" );
			break;

		case SIG_CD_WINMETAHEADER :
			LogCDSignature( "SIG_CD_WINMETAHEADER" );
			break;

		case SIG_CD_MACMETAHEADER :
			LogCDSignature( "SIG_CD_MACMETAHEADER" );
			break;

		case SIG_CD_TABLEBEGIN :
			LogCDSignature( "SIG_CD_TABLEBEGIN" );
			break;

		case SIG_CD_TABLECELL :
			LogCDSignature( "SIG_CD_TABLECELL" );
			break;

		case SIG_CD_TABLEEND :
			LogCDSignature( "SIG_CD_TABLEEND" );
			break;

		case SIG_CD_STYLENAME :
			LogCDSignature( "SIG_CD_STYLENAME" );
			break;

		// The Rest of these Signatures for Composite Records are reserved
		// internal records, Enough of these have been processed to demonstrate
		// logging of Composite Data Records.

		default :
			LogCDSignature( "DEFAULT CD SIGNATURE" );
			break;

	} // END switch ( cdsignature ) 

} // END NSFLog::ProcessCompositeData

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogCDGraphic
//
// Description:
//		Logs Information about this CD record which has a signature of type
//		SIG_CD_GRAPHIC. 
//
// Remarks:
//		The CD Record Data is read from On Disk, using the 
//		following CDGRAPHIC Structure defination from EDITODS.H:
//		NOTE: This is only an example, refer to the source for latest version.
//
//	typedef struct
//	{
//		LSIG	Header;		 // Signature and Length of this record.
//		RECTSIZE DestSize;	 // Destination Display size in twips (1/1440 inch)
//		RECTSIZE CropSize;	 // Width and Height of crop rect in twips. Currently unused
//		CROPRECT CropOffset; // Crop rectangle offset from bottom left of Dest (in twips).Currently unused
//		WORD	fResize;	 // Set to true if object has been resized by user
//		BYTE    Version;	 // CDGRAPHIC_VERSION
//		BYTE	bReserved;   // NOTE: This gets changed after version 4 !!!
//		WORD	wReserved;   // NOTE: This gets changed after version 4 !!!
//	} CDGRAPHIC;
//
//	_CDGRAPHIC Is an odsmacro from ODSTYPES.H. To process other CD Records
//  in a similar way as this method does you must substitute the CD Record
//  structure type and macro name to the LNCompositeData::ReadODS method.
//---------------------------------------------------------------------------
LNSTATUS NSFLog::LogCDGraphic( const LNCompositeData &CD )
{	
	LNSTATUS	Error;
	CDGRAPHIC	CdGraph;

	// Read into memory the On Disk Structure CD Record.
	if ( Error = CD.ReadODS(_CDGRAPHIC, &CdGraph) )
		return Error;

	// Append all of the fields from the CDGRAPHIC struct to the Log.
	LogFile << "               Type                 [CDGRAPHIC]" << endl
			<< "               DestSize:   Width    [";	
	LogNumberData( CdGraph.DestSize.width, 10 );
	LogFile << "]" << endl;

	LogFile << "                           Height   [";
	LogNumberData( CdGraph.DestSize.height, 10 );
	LogFile << "]" << endl;

	LogFile << "               CropSize:   Width    [";
	LogNumberData( CdGraph.CropSize.width, 10 );
	LogFile << "]" << endl;

	LogFile << "                           Height   [";
	LogNumberData( CdGraph.CropSize.height, 10 );
	LogFile << "]" << endl;

	LogFile << "               CropOffset: Left     ["; 
	LogNumberData( CdGraph.CropOffset.left, 10 );
	LogFile << "]" << endl;

	LogFile << "                           Top      [";
	LogNumberData( CdGraph.CropOffset.top, 10 );
	LogFile << "]" << endl;

	LogFile << "                           Right    [";
	LogNumberData( CdGraph.CropOffset.right, 10 );
	LogFile << "]" << endl;

	LogFile << "                           Bottom   [";
	LogNumberData( CdGraph.CropOffset.bottom, 10 );
	LogFile << "]" << endl;

	LogFile << "               fResize:             [";
	if(CdGraph.fResize)
		LogFile << "TRUE";
	else
		LogFile << "FALSE";
	LogFile << "]" << endl;

	LogFile << "               Version:             [";
	LogNumberData( CdGraph.Version + 1, 10 );
	LogFile << "]" << endl;
	
	LogFile << "               wReserved:           [";
	LogNumberData( CdGraph.wReserved, 16 );
	LogFile << "]" << endl;

	return LNNOERROR;

} // END NSFLog::LogCDGraphic

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogCDButton
//
// Description:
//		Logs Information about this CD record which has a signature of type
//		SIG_CD_BUTTON.
//
// Remarks:
//		The CD Record Data is read from On Disk, using the 
//		following CDBUTTON Structure defination from EDITODS.H:
//		NOTE: This is only an example, refer to the source for latest version.
//
//	typedef struct
//	{
//		WSIG 	Header;		// Signature and length of this record.
//		WORD 	Flags;	
//		WORD 	Width;
//		WORD 	Height;
//		WORD	Lines;
//		FONTID 	FontID;
//		// Button Text Follows:
//	} CDBUTTON;
//
//	_CDBUTTON Is an odsmacro from ODSTYPES.H. To process other CD Records
//  in a similar way as this method does you must substitute the CD Record
//  structure type and macro name to the LNCompositeData::ReadODS method.
//---------------------------------------------------------------------------
LNSTATUS NSFLog::LogCDButton( const LNCompositeData &CD )
{	
	LNSTATUS	Error;
	CDBUTTON	CdButton;
	WORD		Flags;
	LNINT		Length;
	char		*TxtBuf;
	LNString	ButtonStr;

	if ( Error = CD.ReadODS(_CDBUTTON, &CdButton) )
		return Error;

	Flags = CdButton.Flags;

	// Append all of the fields from the CDBUTTON struct to the Log.
	LogFile << "               Type:                [CDBUTTON]" << endl;

	LogFile << "               Flags:               [";
	LogNumberData( Flags, 16 );
	LogFile << "]" << endl;

	if (Flags & BUTTONREC_IS_DOWN)  
		LogFile << "                    BUTTONREC_IS_DOWN" << endl;

	if (Flags & BUTTONREC_IS_EDITABLE)  
		LogFile << "                    BUTTONREC_IS_EDITABLE" << endl;

	if (Flags & BUTTONREC_FLAG_CARET_ON)  
		LogFile << "                    BUTTONREC_FLAG_CARET_ON" << endl;

	if (Flags & BUTTONREC_FLAG_RESIZE_ON) 
		LogFile << "                    BUTTONREC_FLAG_RESIZE_ON" << endl;

	if (Flags & BUTTONREC_FLAG_DISABLED)  
		LogFile << "                    BUTTONREC_FLAG_DISABLED" << endl;

	LogFile << "               Width:               [";
	LogNumberData( CdButton.Width, 10 );
	LogFile << "]" << endl;

	LogFile << "               Height:              [";
	LogNumberData( CdButton.Height, 10 );
	LogFile << "]" << endl;

	LogFile << "               Lines:              [";
	LogNumberData( CdButton.Lines, 10 );
	LogFile << "]" << endl;

	// Append The FontID fields to the log.
	LogFontIDFields( CdButton.FontID );

	// Button Text Follows: Get Length using the ODSLength macro.
	Length = CdButton.Header.Length - ODSLength(_CDBUTTON);

	// Allocate memory for the Button text.
	TxtBuf = new char[Length];

	// Read the Buton text into the buffer.
	if ( Error = CD.Read( Length, TxtBuf, ODSLength(_CDBUTTON) ) )
		return Error;

	// Append the Text from the Button text to the Log make sure it is in LIMBCS!.
	ButtonStr = LNString((LNCHAR *) TxtBuf, Length);

	LogFile << "               Button Text Follows:" << endl << endl;
	LogFile << "[" << ButtonStr << "]" << endl << endl;

	// Free the text buffer!
	delete [] TxtBuf;

	return LNNOERROR;

} // END NSFLog::LogCDButton

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogFontIDFields
//
// Description:
//		Appends the FontID Fields from a FontID to the Log.
//
// Remarks:
//		See FONTID.H for macro definitions and FONTID and FONTIDFIELDS 
//		    data structure definitions.
//---------------------------------------------------------------------------
void NSFLog::LogFontIDFields( const FONTID &FontID )
{
	LogFile << "               Font ID Fields: Face     [";
	LogNumberData( FontGetFaceID(FontID), 10 );
	LogFile << endl;

	LogFile << "                               Attrib   [";
	LogNumberData( FontGetStyle(FontID), 10 );
	LogFile << endl;

	LogFile << "                               Color    [";
	LogNumberData( FontGetColor(FontID), 10 );
	LogFile << endl;

	LogFile << "                               Size     [";
	LogNumberData( FontGetSize(FontID), 10 );
	LogFile << endl;

} // END NSFLog::LogFontIDFields

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogCDSignature
//
// Description:
//		Appends the CD Signature type of a Composit Data Item to the Log.
//
//---------------------------------------------------------------------------
LNSTATUS NSFLog::LogCDSignature( const LNString &Sig )
{
	LogFile << "          CD Signature: [" << Sig << "]" << endl;

	return LNNOERROR;

} // END NSFLog::LogCDSignature

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::ProcessFontTableItem
//
// Description:
//		TBD
// Remarks:
//		A Font Table Item Class has not been implemented in the C++API at
//		this time.  This is a placeholder stub just in case the class gets
//		implemented in the future.
//---------------------------------------------------------------------------
LNSTATUS NSFLog::ProcessFontTableItem( const LNItem &Item )
{
	LNCLASSID id;
	
	id = Item.GetClassID();
 
	LogFile << "     The Font Table Class is used indirectly in the C++ API" << endl;
	LogFile << "     Use the LNFonStyle class to process Font Tables." << endl;

	return LNNOERROR;

} // END NSFLog::ProcessFontTableItem

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::GetNoteTypeString
//
// Description:
//		TBD
//
//---------------------------------------------------------------------------
LNString NSFLog::GetNoteTypeString( const LNNOTETYPE NoteType )
{	
	switch (NoteType)
	{
		case LNNOTETYPE_ACL :	
			return "ACL";

		case LNNOTETYPE_AGENT :	
			return "AGENT";

		case LNNOTETYPE_DEFAULT_FORM :		
			return "DEFAULT FORM";

		case LNNOTETYPE_DEFAULT_VIEW_FOLDER :		
			return "DEFAULT VIEW FOLDER";

		case LNNOTETYPE_DESIGN :	
			return "DESIGN";

		case LNNOTETYPE_DOCUMENT :		
			return "DOCUMENT";

		case LNNOTETYPE_FIELD :	
			return "FIELD";

		case LNNOTETYPE_FORM :		
			return "FORM";

		case LNNOTETYPE_HELP_ABOUT :	
			return "HELP ABOUT";

		case LNNOTETYPE_HELP_INDEX :	
			return "HELP INDEX";

		case LNNOTETYPE_HELP_USING :	
			return "HELP USING";

		case LNNOTETYPE_ICON :		
			return "ICON";

		case LNNOTETYPE_NOTIFY_DELETION :		
			return "NOTIFY_DELETION";

		case LNNOTETYPE_REPLICATION_FORMULA	:	
			return "REPLICATION_FORMULA";

		case LNNOTETYPE_PRIVATE	:	
			return "PRIVATE";

		case LNNOTETYPE_VIEW_FOLDER	:	
			return "VIEW_FOLDER";

		default :
			return "UNKNOWN Or UN-EXPOSED Note Type";

	} // END switch (NoteType)";

} // END NSFLog::GetNoteTypeString

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::GetItemTypeString
//
// Description:
//		translates the Item Type symbol into text.
//
// Inputs:
//		LNITEMTYPE The Item Type to be translated.
//
// Returns:
//		LNString representation of the Item Type Symbol.
//
// Remarks:
//
// The following Item Data Types are currently defined in the C++ API
// (updated for 2.1. ***dhs)
//
// C++ API Symbol               C API Symbol(s) that map to it.
// -----------------------------------------------------------------------
// LNITEMTYPE_DATETIMES			TYPE_TIME_RANGE     
// LNITEMTYPE_ERROR				TYPE_ERROR
// LNITEMTYPE_FONTTABLE			TYPE_COMPOSITE      
// LNITEMTYPE_FORMULA			TYPE_FORMULA
// LNITEMTYPE_ICON				TYPE_ICON
// LNITEMTYPE_NOTELINKS			TYPE_NOTELINK_LIST
// LNITEMTYPE_NOTEREFS			TYPE_NOTEREF_LIST
// LNITEMTYPE_NUMBERS			TYPE_NUMBER_RANGE (also) TYPE_NUMBER
// LNITEMTYPE_OBJECT			TYPE_OBJECT
// LNITEMTYPE_RICHTEXT			TYPE_COMPOSITE
// LNITEMTYPE_SIGNATURE			TYPE_SIGNATURE
// LNITEMTYPE_TEXT				TYPE_TEXT_LIST  (also) TYPE_TEXT    
// LNITEMTYPE_UNAVAILABLE		TYPE_UNAVAILABLE
// LNITEMTYPE_UNSUPPORTED		TYPE_INVALID_OR_UNKNOWN
// LNITEMTYPE_USERDATA			TYPE_USERDATA
//
// LNITEMTYPE_ACTION            TYPE_ACTION
// LNITEMTYPE_ASSISTANT_INFO    TYPE_ASSISTANT_INFO
// LNITEMTYPE_CALENDAR_FORMAT   TYPE_CALENDAR_FORMAT
// LNITEMTYPE_COLLATION         TYPE_COLLATION
// LNITEMTYPE_FORM_VIEW_ACTION	(TYPE_COMPOSITE | LNITEMTYPE_SPECIAL | LNITEMTYPE_COMPOSITE_ACTION_FLAG)
// LNITEMTYPE_HIGHLIGHTS		TYPE_HIGHLIGHTS
// LNITEMTYPE_HTML				TYPE_HTML
// LNITEMTYPE_LSOBJECT			TYPE_LSOBJECT
// LNITEMTYPE_OLE_OBJECT		(TYPE_COMPOSITE | LNITEMTYPE_SPECIAL | LNITEMTYPE_COMPOSITE_OLE_FLAG)
// LNITEMTYPE_QUERY             TYPE_QUERY
// LNITEMTYPE_SCHED_LIST        TYPE_SCHED_LIST
// LNITEMTYPE_SEAL				TYPE_SEAL
// LNITEMTYPE_SEALDATA			TYPE_SEALDATA
// LNITEMTYPE_SEAL_LIST		    TYPE_SEAL_LIST
// LNITEMTYPE_USERID			TYPE_USERID
// LNITEMTYPE_VIEW_FORMAT		TYPE_VIEW_FORMAT
// LNITEMTYPE_VIEWMAP_DATASET	TYPE_VIEWMAP_DATASET
// LNITEMTYPE_VIEWMAP_LAYOUT	TYPE_VIEWMAP_LAYOUT
// LNITEMTYPE_WORKSHEET_DATA	TYPE_WORKSHEET_DATA
//
//---------------------------------------------------------------------------
LNString NSFLog::GetItemTypeString( LNITEMTYPE ItemType )
{	
	switch (ItemType)
	{
		case LNITEMTYPE_DATETIMES :
			return "LNITEMTYPE_DATETIMES";

		case LNITEMTYPE_ERROR :	
			return "LNITEMTYPE_ERROR";

		case LNITEMTYPE_FONTTABLE :	
			return "LNITEMTYPE_FONTTABLE";

		case LNITEMTYPE_FORMULA :	
			return "LNITEMTYPE_FORMULA";

		case LNITEMTYPE_ICON :	
			return "LNITEMTYPE_ICON";

		case LNITEMTYPE_NOTELINKS :	
			return "LNITEMTYPE_NOTELINKS";

		case LNITEMTYPE_NOTEREFS :	
			return "LNITEMTYPE_NOTEREFS";

		case LNITEMTYPE_NUMBERS :	
			return "LNITEMTYPE_NUMBERS";

		case LNITEMTYPE_OBJECT :	
			return "LNITEMTYPE_OBJECT";

		case LNITEMTYPE_RICHTEXT :	
			return "LNITEMTYPE_RICHTEXT";

		case LNITEMTYPE_SIGNATURE :	
			return "LNITEMTYPE_SIGNATURE";

		case LNITEMTYPE_TEXT :	
			return "LNITEMTYPE_TEXT";

		case LNITEMTYPE_UNAVAILABLE :	
			return "LNITEMTYPE_UNAVAILABLE";

		case LNITEMTYPE_UNSUPPORTED :	
			return "LNITEMTYPE_UNSUPPORTED";

		case LNITEMTYPE_USERDATA :	
			return "LNITEMTYPE_USERDATA";

		case LNITEMTYPE_ACTION :	
			return "LNITEMTYPE_ACTION";

		case LNITEMTYPE_ASSISTANT_INFO :	
			return "LNITEMTYPE_ASSISTANT_INFO";

		case LNITEMTYPE_CALENDAR_FORMAT :	
			return "LNITEMTYPE_CALENDAR_FORMAT";

		case LNITEMTYPE_COLLATION :	
			return "LNITEMTYPE_COLLATION";

		case LNITEMTYPE_FORM_VIEW_ACTION :	
			return "LNITEMTYPE_FORM_VIEW_ACTION";

		case LNITEMTYPE_HIGHLIGHTS :	
			return "LNITEMTYPE_HIGHLIGHTS";

		case LNITEMTYPE_HTML :	
			return "LNITEMTYPE_HTML";

		case LNITEMTYPE_LSOBJECT :	
			return "LNITEMTYPE_LSOBJECT";

		case LNITEMTYPE_OLE_OBJECT :	
			return "LNITEMTYPE_OLE_OBJECT";

		case LNITEMTYPE_QUERY :	
			return "LNITEMTYPE_QUERY";

		case LNITEMTYPE_SCHED_LIST :	
			return "LNITEMTYPE_SCHED_LIST";

		case LNITEMTYPE_SEAL :	
			return "LNITEMTYPE_SEAL";

		case LNITEMTYPE_SEALDATA :	
			return "LNITEMTYPE_SEALDATA";

		case LNITEMTYPE_SEAL_LIST :	
			return "LNITEMTYPE_SEAL_LIST";

		case LNITEMTYPE_USERID :	
			return "LNITEMTYPE_USERID";

		case LNITEMTYPE_VIEW_FORMAT :	
			return "LNITEMTYPE_VIEW_FORMAT";

		case LNITEMTYPE_VIEWMAP_DATASET :	
			return "LNITEMTYPE_VIEWMAP_DATASET";

		case LNITEMTYPE_VIEWMAP_LAYOUT :	
			return "LNITEMTYPE_VIEWMAP_LAYOUT";

		case LNITEMTYPE_WORKSHEET_DATA :	
			return "LNITEMTYPE_WORKSHEET_DATA";

		default :
			return "UNKNOWN or UN-SUPPORTED Item Type";

	} // END switch (ItemType)";

} // END NSFLog::GetItemTypeString

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::GetCDSignatureString
//
// Description:
//		Translates SIG_CD_xxx to an LNString.
//
// Remarks:
//      The following is a list of all of the possible
//      CD Signatures current up to Notes 5.02 10/14/1999
//      NOTE: Some of these signatures share the same value
//      but are used in different contexts, (i.e. Layouts, Navigators
//      Querys, Actions, and Rich Text)  This function returns only the
//      ones that apply to Rich Text.
//
//          SIG_CD_TARGET_DBLCLK
//          SIG_CD_CAPTION
//          SIG_CD_LINKCOLORS
//          SIG_CD_TABLECELL_HREF
//          SIG_CD_ACTIONBAREXT
//          SIG_CD_IDNAME
//          SIG_CD_TABLECELL_IDNAME
//          SIG_CD_IMAGESEGMENT
//          SIG_CD_IMAGEHEADER
//          SIG_CD_V5HOTSPOTBEGIN
//          SIG_CD_V5HOTSPOTEND
//          SIG_CD_PARAGRAPH
//          SIG_CD_PABDEFINITION
//          SIG_CD_PABREFERENCE
//          SIG_CD_TEXT
//          SIG_CD_HEADER
//          SIG_CD_LINKEXPORT2
//          SIG_CD_BITMAPHEADER
//          SIG_CD_BITMAPSEGMENT
//          SIG_CD_COLORTABLE
//          SIG_CD_GRAPHIC
//          SIG_CD_PMMETASEG
//          SIG_CD_WINMETASEG
//          SIG_CD_MACMETASEG
//          SIG_CD_CGMMETA
//          SIG_CD_PMMETAHEADER
//          SIG_CD_WINMETAHEADER
//          SIG_CD_MACMETAHEADER
//          SIG_CD_TABLEBEGIN
//          SIG_CD_TABLECELL
//          SIG_CD_TABLEEND
//          SIG_CD_STYLENAME
//          SIG_CD_STORAGELINK
//          SIG_CD_TRANSPARENTTABLE
//          SIG_CD_HORIZONTALRULE
//          SIG_CD_ALTTEXT
//          SIG_CD_ANCHOR
//          SIG_CD_HTMLBEGIN
//          SIG_CD_HTMLEND
//          SIG_CD_HTMLFORMULA
//          SIG_CD_NESTEDTABLEBEGIN
//          SIG_CD_NESTEDTABLECELL
//          SIG_CD_NESTEDTABLEEND
//          SIG_CD_COLOR
//          SIG_CD_TABLECELL_COLOR
//          SIG_CD_BLOBPART
//          SIG_CD_BEGIN
//          SIG_CD_END
//          SIG_CD_VERTICALALIGN
//          SIG_CD_FLOATPOSITION
//          SIG_CD_TIMERINFO
//          SIG_CD_TABLEROWHEIGHT
//          SIG_CD_TABLELABEL
//          SIG_CD_BIDI_TEXT
//          SIG_CD_BIDI_TEXTEFFECT
//          SIG_CD_REGIONBEGIN
//          SIG_CD_REGIONEND
//          SIG_CD_TRANSITION
//          SIG_CD_PLACEHOLDER
//          SIG_CD_HTMLNAME
//          SIG_CD_EMBEDDEDOUTLINE
//          SIG_CD_EMBEDDEDVIEW
//          SIG_CD_CELLBACKGROUNDDATA
//          SIG_CD_FRAMESETHEADER
//          SIG_CD_FRAMESET
//          SIG_CD_FRAME
//          SIG_CD_TARGET
//          SIG_CD_NATIVEIMAGE
//          SIG_CD_MAPELEMENT
//          SIG_CD_AREAELEMENT
//          SIG_CD_HREF
//          SIG_CD_EMBEDDEDCTL
//          SIG_CD_HTML_ALTTEXT
//          SIG_CD_EVENT
//          SIG_CD_IMPORTHTML
//          SIG_CD_PRETABLEBEGIN
//          SIG_CD_BORDERINFO
//          SIG_CD_EMBEDDEDSCHEDCTL
//          SIG_CD_EXT2_FIELD
//          SIG_CD_DOCUMENT_PRE_26
//          SIG_CD_FIELD_PRE_36
//          SIG_CD_FIELD
//          SIG_CD_DOCUMENT
//          SIG_CD_METAFILE
//          SIG_CD_BITMAP
//          SIG_CD_FONTTABLE
//          SIG_CD_LINK
//          SIG_CD_LINKEXPORT
//          SIG_CD_KEYWORD
//          SIG_CD_LINK2
//          SIG_CD_CGM
//          SIG_CD_TIFF
//          SIG_CD_PATTERNTABLE
//          SIG_CD_DDEBEGIN
//          SIG_CD_DDEEND
//          SIG_CD_OLEBEGIN
//          SIG_CD_OLEEND
//          SIG_CD_HOTSPOTBEGIN
//          SIG_CD_HOTSPOTEND
//          SIG_CD_BUTTON
//          SIG_CD_BAR
//          SIG_CD_V4HOTSPOTBEGIN
//          SIG_CD_V4HOTSPOTEND
//          SIG_CD_OBSOLETE_FIELD2
//          SIG_CD_EXT_FIELD
//          SIG_CD_LSOBJECT
//          SIG_CD_HTMLHEADER
//          SIG_CD_HTMLSEGMENT
//          SIG_CD_OLEOBJPH
//          SIG_CD_MAPIBINARY
//          SIG_CD_OBSOLETE_FIELD
//          SIG_CD_PABHIDE
//          SIG_CD_PABFORMREF
//          SIG_CD_ACTIONBAR
//          SIG_CD_ACTION
//          SIG_CD_DOCAUTOLAUNCH
//          SIG_CD_OLEOBJINFO
//          SIG_CD_TEXTEFFECT
//          SIG_CD_ALTERNATEBEGIN
//          SIG_CD_ALTERNATEEND
//          SIG_CD_OLERTMARKER

// Signatures for items of type TYPE_VIEWMAP
//
//          SIG_CD_VMHEADER
//          SIG_CD_VMBITMAP
//          SIG_CD_VMRECT
//          SIG_CD_VMPOLYGON_BYTE
//          SIG_CD_VMPOLYLINE_BYTE
//          SIG_CD_VMREGION
//          SIG_CD_VMACTION
//          SIG_CD_VMELLIPSE
//          SIG_CD_VMSMALLTEXTBOX
//          SIG_CD_VMRNDRECT
//          SIG_CD_VMBUTTON
//          SIG_CD_VMACTION_2
//          SIG_CD_VMTEXTBOX
//          SIG_CD_VMPOLYGON
//          SIG_CD_VMPOLYLINE
//          SIG_CD_VMPOLYRGN
//          SIG_CD_VMCIRCLE
//          SIG_CD_VMPOLYRGN_BYTE
//
// Signatures for CD Layout
//
//          SIG_CD_LAYOUT
//          SIG_CD_LAYOUTTEXT
//          SIG_CD_LAYOUTEND
//          SIG_CD_LAYOUTFIELD
//          SIG_CD_LAYOUTGRAPHIC
//          SIG_CD_LAYOUTBUTTON
//
//---------------------------------------------------------------------------
LNString NSFLog::GetCDSignatureString( const WORD cdsignature )
{
	switch (cdsignature)
	{
//    case SIG_CD_TARGET_DBLCLK :
//		return "SIG_CD_TARGET_DBLCLK";

    case SIG_CD_CAPTION :
		return "SIG_CD_CAPTION";

    case SIG_CD_LINKCOLORS :
		return "SIG_CD_LINKCOLORS";

    case SIG_CD_TABLECELL_HREF :
		return "SIG_CD_TABLECELL_HREF";

    case SIG_CD_ACTIONBAREXT :
		return "SIG_CD_ACTIONBAREXT";

    case SIG_CD_IDNAME :
		return "SIG_CD_IDNAME";

    case SIG_CD_TABLECELL_IDNAME :
		return "SIG_CD_TABLECELL_IDNAME";

    case SIG_CD_IMAGESEGMENT :
		return "SIG_CD_IMAGESEGMENT";

    case SIG_CD_IMAGEHEADER :
		return "SIG_CD_IMAGEHEADER";

    case SIG_CD_V5HOTSPOTBEGIN :
		return "SIG_CD_V5HOTSPOTBEGIN";

    case SIG_CD_V5HOTSPOTEND :
		return "SIG_CD_V5HOTSPOTEND";

    case SIG_CD_PARAGRAPH :
		return "SIG_CD_PARAGRAPH";

    case SIG_CD_PABDEFINITION :
		return "SIG_CD_PABDEFINITION";

    case SIG_CD_PABREFERENCE :
		return "SIG_CD_PABREFERENCE";

    case SIG_CD_TEXT :
		return "SIG_CD_TEXT";

    case SIG_CD_HEADER :
		return "SIG_CD_HEADER";

    case SIG_CD_LINKEXPORT2 :
		return "SIG_CD_LINKEXPORT2";

    case SIG_CD_BITMAPHEADER :
		return "SIG_CD_BITMAPHEADER";

    case SIG_CD_BITMAPSEGMENT :
		return "SIG_CD_BITMAPSEGMENT";

    case SIG_CD_COLORTABLE :
		return "SIG_CD_COLORTABLE";

    case SIG_CD_GRAPHIC :
		return "SIG_CD_GRAPHIC";

    case SIG_CD_PMMETASEG :
		return "SIG_CD_PMMETASEG";

    case SIG_CD_WINMETASEG :
		return "SIG_CD_WINMETASEG";

    case SIG_CD_MACMETASEG :
		return "SIG_CD_MACMETASEG";

    case SIG_CD_CGMMETA :
		return "SIG_CD_CGMMETA";

    case SIG_CD_PMMETAHEADER :
		return "SIG_CD_PMMETAHEADER";

    case SIG_CD_WINMETAHEADER :
		return "SIG_CD_WINMETAHEADER";

    case SIG_CD_MACMETAHEADER :
		return "SIG_CD_MACMETAHEADER";

    case SIG_CD_TABLEBEGIN :
		return "SIG_CD_TABLEBEGIN";

    case SIG_CD_TABLECELL :
		return "SIG_CD_TABLECELL";

    case SIG_CD_TABLEEND :
	    return "SIG_CD_TABLEEND";

    case SIG_CD_STYLENAME :
		return "SIG_CD_STYLENAME";

    case SIG_CD_STORAGELINK :
		return "SIG_CD_STORAGELINK";

    case SIG_CD_TRANSPARENTTABLE :
		return "SIG_CD_TRANSPARENTTABLE";

    case SIG_CD_HORIZONTALRULE :
		return "SIG_CD_HORIZONTALRULE";

    case SIG_CD_ALTTEXT :
		return "SIG_CD_ALTTEXT";

    case SIG_CD_ANCHOR :
		return "SIG_CD_ANCHOR";

    case SIG_CD_HTMLBEGIN :
		return "SIG_CD_HTMLBEGIN";

    case SIG_CD_HTMLEND :
		return "SIG_CD_HTMLEND";

    case SIG_CD_HTMLFORMULA :
		return "SIG_CD_HTMLFORMULA";

    case SIG_CD_NESTEDTABLEBEGIN :
		return "SIG_CD_NESTEDTABLEBEGIN";

    case SIG_CD_NESTEDTABLECELL :
		return "SIG_CD_NESTEDTABLECELL";

    case SIG_CD_NESTEDTABLEEND :
		return "SIG_CD_NESTEDTABLEEND";

    case SIG_CD_COLOR :
		return "SIG_CD_COLOR";

    case SIG_CD_TABLECELL_COLOR :
		return "SIG_CD_TABLECELL_COLOR";

    case SIG_CD_BLOBPART :
		return "SIG_CD_BLOBPART";

    case SIG_CD_BEGIN :
		return "SIG_CD_BEGIN";

    case SIG_CD_END :
		return "SIG_CD_END";

    case SIG_CD_VERTICALALIGN :
		return "SIG_CD_VERTICALALIGN";

    case SIG_CD_FLOATPOSITION :
		return "SIG_CD_FLOATPOSITION";

    case SIG_CD_TIMERINFO :
		return "SIG_CD_TIMERINFO";

    case SIG_CD_TABLEROWHEIGHT :
		return "SIG_CD_TABLEROWHEIGHT";

    case SIG_CD_TABLELABEL :
		return "SIG_CD_TABLELABEL";

    case SIG_CD_BIDI_TEXT :
		return "SIG_CD_BIDI_TEXT";

    case SIG_CD_BIDI_TEXTEFFECT :
		return "SIG_CD_BIDI_TEXTEFFECT";

    case SIG_CD_REGIONBEGIN :
		return "SIG_CD_REGIONBEGIN";

    case SIG_CD_REGIONEND :
		return "SIG_CD_REGIONEND";

    case SIG_CD_TRANSITION :
		return "SIG_CD_TRANSITION";

    case SIG_CD_PLACEHOLDER :
		return "SIG_CD_PLACEHOLDER";

//    case SIG_CD_HTMLNAME :
//		return "SIG_CD_HTMLNAME";

    case SIG_CD_EMBEDDEDOUTLINE :
		return "SIG_CD_EMBEDDEDOUTLINE";

    case SIG_CD_EMBEDDEDVIEW :
		return "SIG_CD_EMBEDDEDVIEW";

    case SIG_CD_CELLBACKGROUNDDATA :
		return "SIG_CD_CELLBACKGROUNDDATA";

    case SIG_CD_FRAMESETHEADER :
		return "SIG_CD_FRAMESETHEADER";

    case SIG_CD_FRAMESET :
		return "SIG_CD_FRAMESET";

    case SIG_CD_FRAME :
		return "SIG_CD_FRAME";

    case SIG_CD_TARGET :
		return "SIG_CD_TARGET";

    case SIG_CD_NATIVEIMAGE :
		return "SIG_CD_NATIVEIMAGE";

    case SIG_CD_MAPELEMENT :
		return "SIG_CD_MAPELEMENT";

    case SIG_CD_AREAELEMENT :
		return "SIG_CD_AREAELEMENT";

    case SIG_CD_HREF :
		return "SIG_CD_HREF";

    case SIG_CD_EMBEDDEDCTL :
		return "SIG_CD_EMBEDDEDCTL";

    case SIG_CD_HTML_ALTTEXT :
		return "SIG_CD_HTML_ALTTEXT";

    case SIG_CD_EVENT :
		return "SIG_CD_EVENT";

//    case SIG_CD_IMPORTHTML :
//		return "SIG_CD_IMPORTHTML";

    case SIG_CD_PRETABLEBEGIN :
		return "SIG_CD_PRETABLEBEGIN";

    case SIG_CD_BORDERINFO :
		return "SIG_CD_BORDERINFO";

    case SIG_CD_EMBEDDEDSCHEDCTL :
		return "SIG_CD_EMBEDDEDSCHEDCTL";

    case SIG_CD_EXT2_FIELD :
		return "SIG_CD_EXT2_FIELD";

    case SIG_CD_DOCUMENT_PRE_26 :
		return "SIG_CD_DOCUMENT_PRE_26";

    case SIG_CD_FIELD_PRE_36 :
		return "SIG_CD_FIELD_PRE_36";

    case SIG_CD_FIELD :
		return "SIG_CD_FIELD";

    case SIG_CD_DOCUMENT :
		return "SIG_CD_DOCUMENT";

    case SIG_CD_METAFILE :
		return "SIG_CD_METAFILE";

    case SIG_CD_BITMAP :
		return "SIG_CD_BITMAP";

    case SIG_CD_FONTTABLE :
		return "SIG_CD_FONTTABLE";

    case SIG_CD_LINK :
		return "SIG_CD_LINK";

    case SIG_CD_LINKEXPORT :
		return "SIG_CD_LINKEXPORT";

    case SIG_CD_KEYWORD :
		return "SIG_CD_KEYWORD";

    case SIG_CD_LINK2 :
		return "SIG_CD_LINK2";

    case SIG_CD_CGM :
		return "SIG_CD_CGM";

    case SIG_CD_TIFF :
		return "SIG_CD_TIFF";

    case SIG_CD_PATTERNTABLE :
		return "SIG_CD_PATTERNTABLE";

    case SIG_CD_DDEBEGIN :
		return "SIG_CD_DDEBEGIN";

    case SIG_CD_DDEEND :
		return "SIG_CD_DDEEND";

    case SIG_CD_OLEBEGIN :
		return "SIG_CD_OLEBEGIN";

    case SIG_CD_OLEEND :
		return "SIG_CD_OLEEND";

    case SIG_CD_HOTSPOTBEGIN :
		return "SIG_CD_HOTSPOTBEGIN";

    case SIG_CD_HOTSPOTEND :
		return "SIG_CD_HOTSPOTEND";

    case SIG_CD_BUTTON :
		return "SIG_CD_BUTTON";

    case SIG_CD_BAR :
		return "SIG_CD_BAR";

    case SIG_CD_V4HOTSPOTBEGIN :
		return "SIG_CD_V4HOTSPOTBEGIN";

    case SIG_CD_V4HOTSPOTEND :
		return "SIG_CD_V4HOTSPOTEND";

//    case SIG_CD_OBSOLETE_FIELD2 :
//		return "SIG_CD_OBSOLETE_FIELD2";

    case SIG_CD_EXT_FIELD :
		return "SIG_CD_EXT_FIELD";

    case SIG_CD_LSOBJECT :
		return "SIG_CD_LSOBJECT";

    case SIG_CD_HTMLHEADER :
		return "SIG_CD_HTMLHEADER";

    case SIG_CD_HTMLSEGMENT :
		return "SIG_CD_HTMLSEGMENT";

//    case SIG_CD_OLEOBJPH :
//        return "SIG_CD_OLEOBJPH";

//    case SIG_CD_MAPIBINARY :
//		return "SIG_CD_MAPIBINARY";

//    case SIG_CD_OBSOLETE_FIELD :
//		return "SIG_CD_OBSOLETE_FIELD";

    case SIG_CD_PABHIDE :
		return "SIG_CD_PABHIDE";

    case SIG_CD_PABFORMREF :
		return "SIG_CD_PABFORMREF";

    case SIG_CD_ACTIONBAR :
		return "SIG_CD_ACTIONBAR";

    case SIG_CD_ACTION :
		return "SIG_CD_ACTION";

    case SIG_CD_DOCAUTOLAUNCH :
		return "SIG_CD_DOCAUTOLAUNCH";


    case SIG_CD_OLEOBJINFO :
		return "SIG_CD_OLEOBJINFO";


    case SIG_CD_TEXTEFFECT :
		return "SIG_CD_TEXTEFFECT";



    case SIG_CD_ALTERNATEBEGIN :
		return "SIG_CD_ALTERNATEBEGIN";

    case SIG_CD_ALTERNATEEND :
		return "SIG_CD_ALTERNATEEND";

    case SIG_CD_OLERTMARKER :
        return "SIG_CD_OLERTMARKER";

// CD View Map signatures.

    case SIG_CD_VMHEADER :
		return "SIG_CD_VMHEADER";

    case SIG_CD_VMBITMAP :
		return "SIG_CD_VMBITMAP";

    case SIG_CD_VMRECT :
		return "SIG_CD_VMRECT";

    case SIG_CD_VMPOLYGON_BYTE :
		return "SIG_CD_VMPOLYGON_BYTE";

    case SIG_CD_VMPOLYLINE_BYTE :
		return "SIG_CD_VMPOLYLINE_BYTE";

    case SIG_CD_VMREGION :
		return "SIG_CD_VMREGION";

    case SIG_CD_VMACTION :
		return "SIG_CD_VMACTION";

    case SIG_CD_VMELLIPSE :
		return "SIG_CD_VMELLIPSE";

//    case SIG_CD_VMSMALLTEXTBOX :
//		return "SIG_CD_VMSMALLTEXTBOX";

    case SIG_CD_VMRNDRECT :
		return "SIG_CD_VMRNDRECT";

    case SIG_CD_VMBUTTON :
		return "SIG_CD_VMBUTTON";

    case SIG_CD_VMACTION_2 :
		return "SIG_CD_VMACTION_2";

//    case SIG_CD_VMTEXTBOX :
//		return "SIG_CD_VMTEXTBOX";

    case SIG_CD_VMPOLYGON :
		return "SIG_CD_VMPOLYGON";

    case SIG_CD_VMPOLYLINE :
		return "SIG_CD_VMPOLYLINE";

//    case SIG_CD_VMPOLYRGN :
//		return "SIG_CD_VMPOLYRGN";

    case SIG_CD_VMCIRCLE :
		return "SIG_CD_VMCIRCLE";

    case SIG_CD_VMPOLYRGN_BYTE :
		return "SIG_CD_VMPOLYRGN_BYTE";

// CD Layout signatures.

    case SIG_CD_LAYOUT :
		return "SIG_CD_LAYOUT";

//    case SIG_CD_LAYOUTTEXT :
//		return "SIG_CD_LAYOUTTEXT";

//    case SIG_CD_LAYOUTEND :
//		return "SIG_CD_LAYOUTEND";

    case SIG_CD_LAYOUTFIELD :
		return "SIG_CD_LAYOUTFIELD";

//    case SIG_CD_LAYOUTGRAPHIC :
//		return "SIG_CD_LAYOUTGRAPHIC";

    case SIG_CD_LAYOUTBUTTON :
		return "SIG_CD_LAYOUTBUTTON";

    default :
		return "UNKNOWN or UN-SUPPORTED CD Signature.";

	} // END switch (cdsignature)

} // END NSFLog::GetCDSignatureString

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::GetItemClassString
//
// Description:
//		Translates the Item Class symbol into text.
//
// Inputs:
//		WORD The Item Class to be translated.
//
// Returns:
//		LNString representation of the Item Class Symbol.
//
//---------------------------------------------------------------------------
LNString NSFLog::GetItemClassString( WORD ItemClass )
{	
	switch (ItemClass)
	{
		case CLASS_NOCOMPUTE :	
			return "CLASS_NOCOMPUTE";

		case CLASS_ERROR :	
			return "CLASS_ERROR";

		case CLASS_UNAVAILABLE :	
			return "CLASS_UNAVAILABLE";

		case CLASS_NUMBER :	
			return "CLASS_NUMBER";

		case CLASS_TIME :	
			return "CLASS_TIME";

		case CLASS_TEXT :	
			return "CLASS_TEXT";

		case CLASS_FORMULA :	
			return "CLASS_FORMULA";

		case CLASS_USERID :	
			return "CLASS_USERID";

		default :
			return "ITEM CLASS UNKNOWN";

	} // END switch (ItemClass)";

} // END NSFLog::GetItemClassString

//---------------------------------------------------------------------------
//
// Name:
//		NSFLog::LogItemFlags
//
// Description:
//		Translates the Item Flags into a text and appends them to
//		the Log file under the sub heading labeled "Item Flags:"
//
// Inputs:
//		WORD The Item Flag to be translated.
//
// Remarks:
//
//		Item Flags Supported By the 4.01 release of the C++ API:
//
//		C++ API symbol			C API equivalent
//		-----------------------------------------
//		LNITEMFLAGS_AUTHORS		ITEM_READWRITERS
//		LNITEMFLAGS_ENCRYPT		ITEM_SEAL
//		LNITEMFLAGS_NAMES		ITEM_NAMES
//		LNITEMFLAGS_PROTECTED	ITEM_PROTECTED
//		LNITEMFLAGS_READERS		ITEM_READERS
//		LNITEMFLAGS_SIGN		ITEM_SIGN
//		LNITEMFLAGS_SUMMARY		ITEM_SUMMARY
//		LNITEMFLAGS_PLACEHOLDER	ITEM_PLACEHOLDER
//
//		NOTE: More may have been added since the 4.01 release.
//---------------------------------------------------------------------------
void NSFLog::LogItemFlags( LNITEMFLAGS ItemFlags )
{
	LNBOOL	NoFlagsSet = TRUE;

	// Append a heading to indicate the following are Field Flags.
	LogFile << endl << "Field Flags That Are Set:" << endl;

	// Log all the flags that are set.
	if (ItemFlags & LNITEMFLAGS_AUTHORS )
	{
		LogFile << "     LNITEMFLAGS_AUTHORS" << endl;

		NoFlagsSet = FALSE;
	}
	if (ItemFlags & LNITEMFLAGS_ENCRYPT )
	{
		LogFile << "     LNITEMFLAGS_ENCRYPT" << endl;

		NoFlagsSet = FALSE;
	}
	if (ItemFlags & LNITEMFLAGS_NAMES )
	{
		LogFile << "     LNITEMFLAGS_NAMES" << endl;

		NoFlagsSet = FALSE;
	}
	if (ItemFlags & LNITEMFLAGS_PROTECTED )
	{
		LogFile << "     LNITEMFLAGS_PROTECTED" << endl;

		NoFlagsSet = FALSE;
	}
	if (ItemFlags & LNITEMFLAGS_READERS )
	{
		LogFile << "     LNITEMFLAGS_READERS" << endl;

		NoFlagsSet = FALSE;
	}
	if (ItemFlags & LNITEMFLAGS_SIGN )
	{
		LogFile << "     LNITEMFLAGS_SIGN" << endl;

		NoFlagsSet = FALSE;
	}
	if (ItemFlags & LNITEMFLAGS_SUMMARY )
	{
		LogFile << "     LNITEMFLAGS_SUMMARY" << endl;

		NoFlagsSet = FALSE;
	}
	if (ItemFlags & LNITEMFLAGS_PLACEHOLDER )
	{
		LogFile << "     LNITEMFLAGS_PLACEHOLDER" << endl;

		NoFlagsSet = FALSE;
	}
	if ( NoFlagsSet )
	{
		LogFile << "     NO FIELD FLAGS ARE SET" << endl;
	}

} // END NSFLog::LogItemFlags


