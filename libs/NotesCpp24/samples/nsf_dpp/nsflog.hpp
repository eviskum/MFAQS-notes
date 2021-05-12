//===========================================================================
//
// Module:		NSFLOG.HPP
//
// Description:	
//		Class library for the NSFLog class. Which defines an Abstract Loging 
//		DataBase object which can be used to store and keep track of data 
//		dumped from .NSF files.
//===========================================================================

#ifndef NSFLOG_HPP
#define NSFLOG_HPP

#include <fstream.h>
#include <lncppapi.h>
#include <stdio.h>

//
//	Class definition for NSFLog. The Logging/Journaling Database.
//
class NSFLog
{

public:
	NSFLog();
	~NSFLog();

	// Public Methods:

    void AddNewItem( LNItem &Item, LNINT CurrentItem );

	void AddNewNoteHeader( LNNote &Note,
						   LNINT CurrentNote,
						   LNINT NumItems    );


	LNSTATUS Close();

	void CreateLogEntry( const LNString &NSFName, 
						 const LNString &DBTitle,
						 const LNNUMBER &TotalNotes );

    LNString GetCDSignatureString( const WORD cdsignature );

	void LogLabel( const LNString &Label,
				   const LNString &StrValue );

	void LogLabel( const LNString &Label,
				   const LNINT Number,
				   const LNINT base       );

	void LogMainHeading( const LNString &Heading );
	void Open( LNNotesSession *session, const LNString &path );

private:

	// Private Methods:
	void LogOID( LNNote &Note );
	void LogString( const char *pString );

	void LogNumberData( const LNINT Number, const LNINT base );

	void LogItemFlags( LNITEMFLAGS ItemFlags );
	void LogTextItem( const LNItem &Item );
	void LogNumbersItem( const LNItem &Item );
	void LogDateTimesItem( const LNItem &Item );
	void LogUndefinedItem();
	void LogFontAttributes( const LNFONTATTRIBUTEFLAGS FontFlags );
	void LogLabelWithHexTimeDate( const char *pString, const TIMEDATE &Td );

	LNSTATUS LogFontColor( const LNCOLOR FontColor );
	LNSTATUS LogCDRecordHeading( const LNINT recordcount );
	LNSTATUS LogCDGraphic( const LNCompositeData &CD );
	LNSTATUS LogCDButton( const LNCompositeData &CD );
	
	void LogFontIDFields( const FONTID &FontID );

	LNSTATUS LogCDSignature( const LNString &Sig );
	LNSTATUS LogUnexposedCDRHeading( const LNINT recordcount );

	LNString GetFontColorString( const LNCOLOR FontColor );
	LNString GetNoteTypeString( const LNNOTETYPE NoteType );
	LNString GetFontFaceString( const LNFACEID FaceID );
	LNString GetItemTypeString( LNITEMTYPE ItemType );
	LNString GetItemClassString( WORD ItemClass );

	void ProcessItemType( LNItem &Item, LNITEMTYPE ItemType );
	void ProcessRichTextItem( const LNItem &Item );
	void ProcessStylizedText( const LNRTObject &Obj, const LNINT recordcount );
	void ProcessCompositeData( const LNRTObject &Obj, const LNINT recordcount );

	LNSTATUS ProcessFontTableItem( const LNItem &Item );

	// Private Data:
	LNNotesSession	*LogSession;
	ofstream		LogFile;
	LNBOOL			isLogOpen;

};  // END class NSFLog

#endif // NSFLOG_HPP


