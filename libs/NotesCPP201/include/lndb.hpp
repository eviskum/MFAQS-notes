//===========================================================================
//
// Module:		LNDB.HPP
//
// Description:
//
//		Class library definition for LNDatabase and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNDB_HPP
#define LNDB_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif


class LNSelectiveReplication {};
class LNSubformArray;

//
//	Class definition for LNSearchOptions.
//
class LNIMPEXPCL LNSearchOptions : public LNNotesClass
{

public:
	LNSearchOptions();

	LNSearchOptions( const LNSearchOptions &other );

	~LNSearchOptions();

	LNSearchOptions & operator=( const LNSearchOptions &other );

	LNDatetime GetBeginDate() const;

	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNSEARCHOPTIONS;}

	LNDatetime GetCompletedDate() const;

	LNDatetime GetEndDate() const;

	LNINT GetMaxNotes() const;

	LNNOTETYPE GetNoteType() const;

	LNSTATUS SetBeginDate( const LNString &begindate );
	LNSTATUS SetBeginDate( const LNDatetime &begindate );

	LNSTATUS SetEndDate( const LNString &enddate );
	LNSTATUS SetEndDate( const LNDatetime &enddate );

	LNSTATUS SetMaxNotes( LNINT maxnotes );

	LNSTATUS SetNoteType( LNNOTETYPE notetype );

private:
	LNSTATUS SetCompletedDate( TIMEDATE *completeddate );

	TIMEDATE BeginDate;
	TIMEDATE CompletedDate;
	TIMEDATE EndDate;
	LNINT MaxNotes;
	LNNOTETYPE NoteType;
};

//
//	Class definition for LNFTIndexStatistics.
//
class LNIMPEXPCL LNFTIndexStatistics : public LNNotesClass
{

public:
	LNFTIndexStatistics();

	LNFTIndexStatistics( const LNFTIndexStatistics &other );

	~LNFTIndexStatistics();

	LNFTIndexStatistics & operator=( const LNFTIndexStatistics &other );

	LNCLASSID GetClassID() const {return LNCLASSID_LNFTINDEXSTATISTICS;}

	LNINT GetNumberOfBytesIndexed() const;

	LNINT GetNumberOfDocsAdded() const;

	LNINT GetNumberOfDocsDeleted() const;

	LNINT GetNumberOfDocsUpdated() const;

private:
	void Assign( FT_INDEX_STATS stats );

	FT_INDEX_STATS Statistics;
};

//
//	Class definition for LNFTSearchOptions.
//
class LNIMPEXPCL LNFTSearchOptions : public LNNotesClass
{

public:
	LNFTSearchOptions();

	LNFTSearchOptions( const LNFTSearchOptions &other );

	~LNFTSearchOptions();

	LNFTSearchOptions & operator=( const LNFTSearchOptions &other );

	LNCLASSID GetClassID() const {return LNCLASSID_LNFTSEARCHOPTIONS;}

	LNINT GetMaxDocuments() const;

	LNFTSEARCHORDER GetSortOrder() const;

	LNBOOL GetStemWords() const;

	LNBOOL GetThesaurusWords() const;

	LNSTATUS SetMaxDocuments( LNINT maxdocuments );

	LNSTATUS SetSortOrder( LNFTSEARCHORDER sortorder );

	void SetStemWords( LNBOOL stemwords );

	void SetThesaurusWords( LNBOOL theswords );

private:
	DWORD GetOptions() const {return Options;}

	WORD MaxDocuments;
	DWORD Options;
};

#ifndef LNRTTYPE_HPP
#include "lnrttype.hpp"
#endif

//
//	Class definition for LNDatabase.
//
class LNIMPEXPCL LNDatabase : public LNSmartPtr
{
friend class LNCalendar;
friend class LNCalendarEntryArray;
friend class LNNote;
friend class LNNoteArray;
friend class LNNotesSession;

public:
	LNDatabase() : LNSmartPtr() {}
	LNDatabase( const LNDatabase &other ) : LNSmartPtr(other) {}

	~LNDatabase() {}
	
	LNDatabase & operator=( const LNDatabase &other );

	LNBOOL AgentExists( const LNString &agentname ) const;

	LNSTATUS CreateAgent( const LNString &agentname, LNBOOL shared, LNAgent *newagent );
	LNSTATUS CreateAgent( LNAgent &agent, LNAgent *newagent);

	LNSTATUS DeleteAgent( const LNString &agentname );
	LNSTATUS DeleteAgent( LNAgent *agent );

	LNSTATUS GetAgent( const LNString &agentname, LNAgent *agent );
	LNSTATUS GetAgent( const char *agentname, LNAgent *agent )
		{ return GetAgent(LNString(agentname), agent); }
	LNSTATUS GetAgent( const NOTEID idnote, LNAgent *agent );
	LNSTATUS GetAgent( const UNID *unidnote, LNAgent *agent );
	LNSTATUS GetAgent( NOTEHANDLE handle, LNAgent *agent )
		{ return GetNote(handle, (LNNote *) agent); }
	
	LNSTATUS GetAgents( LNAgentArray *agents );
	
	LNSTATUS CreateDocument( LNDocument *newdoc );
	LNSTATUS CreateDocument( LNDocument *newdoc, const LNString &form );
	LNSTATUS CreateDocument( LNDocument &document, LNDocument *newdoc = 0 );

	LNSTATUS DeleteDocument( LNDocument *document );
	
	LNSTATUS GetDocument( const NOTEID idnote, LNDocument *doc );
	LNSTATUS GetDocument( const UNID *unidnote, LNDocument *doc );
	LNSTATUS GetDocument( NOTEHANDLE handle, LNDocument *doc )
		{ return GetNote(handle, (LNNote *) doc); }

	LNSTATUS GetDocuments( LNDocumentArray *docs );

	LNSTATUS CreateForm( const LNString &formname, LNForm *newform );
	LNSTATUS CreateForm( LNForm &form, LNForm *newform );

	LNSTATUS DeleteForm( const LNString &formname )
		{ return DeleteFormXYZ(formname); }
	LNSTATUS DeleteForm( LNForm *form )
		{ return DeleteFormXYZ(form); }

	LNSTATUS DeleteSubform( const LNString &subformname);
	LNSTATUS DeleteSubform( LNSubform *subform);
	LNSTATUS DeleteSharedField( const LNString &sharedfieldname);
	LNSTATUS DeleteSharedField( LNSharedField *sharedfield);

	
	LNBOOL FormExists( const LNString &formname ) const;
	
	LNSTATUS GetDefaultForm( LNForm *form ) const;

	LNSTATUS GetForm( const LNString &formname, LNForm *form )
		{ return GetFormXYZ(formname,form); }
	LNSTATUS GetForm( const char *formname, LNForm *form )
		{ return GetFormXYZ(LNString(formname), form); }
	LNSTATUS GetForm( const NOTEID idnote, LNForm *form )
		{ return GetFormXYZ(idnote,form); }
	LNSTATUS GetForm( const UNID *unidnote, LNForm *form )
		{ return GetFormXYZ(unidnote,form); }
	LNSTATUS GetForm( NOTEHANDLE handle, LNForm *form )
		{ return GetNote(handle, (LNNote *) form); }
	
	LNSTATUS GetForms( LNFormArray *forms );

	LNBOOL SharedFieldExists( const LNString &sharedfieldname ) const;

	LNSTATUS CreateSharedField( const LNFormField &field, LNSharedField *sharedfield = 0);
	LNSTATUS CreateSharedField( const LNString &name, LNRTTYPE fieldtype, LNSharedField *sharedfield = 0);
	LNSTATUS CreateSharedField( LNSharedField &sharedfield, LNSharedField *newsharedfield = 0);

	LNSTATUS GetSharedField( const LNString &sharedfieldname, LNSharedField *sharedfield); 
	LNSTATUS GetSharedFields( LNSharedFieldArray *array );

	LNBOOL SubformExists( const LNString &subformname ) const;

	LNSTATUS CreateSubform( const LNString &subformname, LNSubform *subform = 0);
	LNSTATUS CreateSubform( LNSubform &subform, LNSubform *newSubform = 0);

	LNSTATUS GetSubform( const LNString &subformname, LNSubform *subform);
	LNSTATUS GetSubforms( LNSubformArray *array );
	
	LNSTATUS CreateNote( LNNOTETYPE notetype, LNNote *newnote );
	LNSTATUS CreateNote( LNNote &note, LNNote *newnote = 0 );
	
	LNSTATUS CreateEncryptedNote	// here for backwards compatiblity
		( LNNote &note, LNNote *newnote, LNENCRYPTOPTION option )
		{ return CreateEncryptedNote(note, option, newnote); }	
	LNSTATUS CreateEncryptedNote( LNNote &note, LNNote *newnote = 0 )
		{ return CreateEncryptedNote(note, LNENCRYPTOPTION_PUBLIC, newnote); }	
	LNSTATUS CreateEncryptedNote
		( LNNote &note, LNENCRYPTOPTION option, LNNote *newnote = 0 );
	LNSTATUS CreateEncryptedNote
		( LNNote &note, const LNString &keyname, LNNote *newnote = 0);
	LNSTATUS CreateEncryptedNote
		( LNNote &note, const LNText &keynames, LNNote *newnote = 0);

	LNSTATUS DeleteNote( LNNote *note );

	LNSTATUS DeleteNotes( const LNNoteArray &notes );

	LNSTATUS GetNote( const NOTEID idnote, LNNote *note );
	LNSTATUS GetNote( const UNID *unidnote, LNNote *note );
	LNSTATUS GetNote( NOTEHANDLE handle, LNNote *note );

	LNSTATUS GetNotes( LNNoteArray *notes );
	
	LNSTATUS CreateFolder( const LNString &name, LNViewFolder *newfolder = 0 );
	LNSTATUS CreateFolder
		( const LNString &name, LNVFSHARINGOPTION sharing,
		  LNViewFolder *newfolder = 0 );
	LNSTATUS CreateFolder
		( const LNString &name, LNVFSHARINGOPTION sharing,
		  const LNViewFolder &templt, LNViewFolder *newfolder = 0 );

	LNSTATUS CreateView( const LNString &name, LNViewFolder *newview = 0 );
	LNSTATUS CreateView
		( const LNString &name, LNVFSHARINGOPTION sharing,
		  LNViewFolder *newview = 0 );
	LNSTATUS CreateView
		( const LNString &name, LNVFSHARINGOPTION sharing,
		  const LNViewFolder &templt, LNViewFolder *newview = 0 );

	LNSTATUS CreateViewFolder
		( const LNString &name, LNViewFolder &oldviewfolder,
		  LNViewFolder *newviewfolder = 0 );

	LNSTATUS DeleteViewFolder( const LNString &viewname );
	LNSTATUS DeleteViewFolder( LNViewFolder *view );
	
	LNSTATUS GetDefaultViewFolder( LNViewFolder *view ) const;

	LNSTATUS GetViewFolder( const LNString &viewname, LNViewFolder *view );
	LNSTATUS GetViewFolder( const char *viewname, LNViewFolder *view )
		{ return GetViewFolder(LNString(viewname), view); }
	LNSTATUS GetViewFolder( const NOTEID idnote, LNViewFolder *view );
	LNSTATUS GetViewFolder( const UNID *unidnote, LNViewFolder *view );
	LNSTATUS GetViewFolder( NOTEHANDLE handle, LNViewFolder *view )
		{ return GetNote(handle, (LNNote *) view); }
	
	LNSTATUS GetFolders( LNViewFolderArray *folders );
	LNSTATUS GetViews( LNViewFolderArray *views );
	LNSTATUS GetViewFolders( LNViewFolderArray *viewfolders );
	
	LNSTATUS MoveFolder( const LNString &source, const LNString &dest ) const;
	LNSTATUS MoveFolder
		( const LNViewFolder &source, const LNViewFolder &dest ) const;
	
	LNBOOL ViewFolderExists( const LNString &viewname ) const;
	
	LNSTATUS CreateFTIndex( LNFTINDEXFLAGS options = LNFTINDEXFLAGS_DEFAULT,
		const LNString &stopfile = "", LNFTIndexStatistics *stats = 0 );
		
	LNSTATUS DeleteFTIndex();
	
	LNSTATUS GetFTIndexFlags( LNFTINDEXFLAGS *options );
	
	LNSTATUS GetLastFTIndexed( LNDatetime *lastindex );
	
	LNBOOL IsFTIndexed();
	
	LNSTATUS FTSearch( const LNString &query, LNDocumentArray *results ) const;

	LNSTATUS FTSearch
		( const LNString &query, LNDocumentArray *results,
		  const LNFTSearchOptions &options ) const;

	LNSTATUS FTSearch
		( const LNString &query, LNDocumentArray *results,
		  const LNFTSearchOptions &options, const LNNoteArray &input ) const;
	
	LNSTATUS GetModifiedNotes
		( const LNString &start, LNNoteArray *notes, LNDatetime *end = 0 ) const
		{
			return GetModifiedNotes(LNDatetime(start), notes,
									LNNOTETYPE_DOCUMENT, end);
		}

	LNSTATUS GetModifiedNotes
		( const LNDatetime &start, LNNoteArray *notes, LNDatetime *end = 0 ) const
		{ return GetModifiedNotes(start, notes, LNNOTETYPE_DOCUMENT, end); }

	LNSTATUS GetModifiedNotes
		( const LNString &start, LNNoteArray *notes, LNNOTETYPE type,
		  LNDatetime *end = 0 ) const
		{ return GetModifiedNotes(LNDatetime(start), notes, type, end); }

	LNSTATUS GetModifiedNotes
		( const LNDatetime &start, LNNoteArray *notes, LNNOTETYPE type,
		  LNDatetime *end = 0 ) const;
	  
	LNSTATUS Search( const LNFormula &formula, LNNoteArray *results,
		LNSearchOptions *options=0 );
		
	LNSTATUS UpdateFTIndex( LNFTIndexStatistics *stats = 0 );
	
	LNSTATUS GetUnreadList( LNNoteArray *unread, LNBOOL create = FALSE ) const;
	LNSTATUS GetUnreadList
		( LNNoteArray *unread, const LNString &username,
		  LNBOOL create = FALSE ) const;

	LNSTATUS SetUnreadList
		( LNNoteArray *unread, LNNoteArray *oldunread = 0,
		  LNBOOL flush = FALSE ) const;
	LNSTATUS SetUnreadList
		( LNNoteArray *unread, LNNoteArray *oldunread, const LNString &username,
		  LNBOOL flush = FALSE ) const;
	
	LNSTATUS UpdateUnreadList( LNNoteArray *unread ) const;

	LNSTATUS Close();
	
	LNSTATUS CreateAboutDatabaseDocument( LNDocument *newdoc );
	LNSTATUS CreateAboutDatabaseDocument( LNDocument &policydoc,
		LNDocument *newdoc = 0 );
	
	LNSTATUS CreateIcon( LNNote *newicon );
	LNSTATUS CreateIcon( LNNote &icon, LNNote *newicon = 0 );
	
	LNSTATUS CreateUsingDatabaseDocument( LNDocument *newdoc );
	LNSTATUS CreateUsingDatabaseDocument( LNDocument &helpdoc,
		LNDocument *newdoc = 0 );
	
	LNSTATUS GetAboutDatabaseDocument( LNDocument *policy );
	
	LNSTATUS GetACL( LNACL *acl );
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNDATABASE;}
	
	LNDatetime GetCreated();

	LNText GetDatabaseCatalogCategories();
	
	DBHANDLE GetDatabaseHandle( LNBOOL keep_object = FALSE );
	
	TIMEDATE * GetDatabaseID();
	
	LNDBOPENFLAGS GetDatabaseOpenFlags() const;
	
	LNDatetime GetDataLastModified();
	
	LNDatetime GetDesignLastModified();
	
	LNBOOL GetDisableBackgroundAgents();
	
	LNBOOL GetDisableReplication();
	
	LNBOOL GetNeverReplicate();

	LNString GetFilename() const;
	
	LNString GetFilepath() const;
	
	LNBOOL GetHideDesign();
	
	LNSTATUS GetIcon( LNNote *icon );
	
	LNString GetInheritsFromTemplateName();
	
	LNDatetime GetLastModified();
	
	LNBOOL GetListInDatabaseCatalog();
	
	LNString GetOwnerName() const;

	LNNUMBER GetPercentageUsed();
	
	LNString GetPort() const;
	
	LNINT GetRemoveOldDocumentsDays();
	
	LNBOOL GetRemoveOldDocuments();
	
	TIMEDATE * GetReplicaID();
	
	LNBOOL GetReplicateReceiveSummaries();
	
	LNBOOL GetReplicateSendDeletions();
	
	LNBOOL GetReplicateSendTitleAndCatalogInfo();
	
	LNREPLICATIONPRIORITY GetReplicationPriority();
	
	LNString GetServer() const;

	LNBOOL GetShowInOpenDatabaseDialog();
	
	LNINT GetSize();
	
	LNString GetTemplateName();
	
	LNString GetTitle();
	
	LNDBTYPE GetType();
	
	LNSTATUS GetUsingDatabaseDocument( LNDocument *helpdoc );
	
	LNBOOL IsLocal() const { return !IsRemote(); }

	LNBOOL IsOpen() const;
	
	LNBOOL IsRemote() const;

	LNSTATUS Open();
	
	LNSTATUS Open( LNDBOPENFLAGS flags );
	
	LNSTATUS SetDatabaseCatalogCategories( const LNText &txtcategories );
	
	LNSTATUS SetDisableBackgroundAgents( LNBOOL flag );
	
	LNSTATUS SetDisableReplication( LNBOOL flag );
	
	LNSTATUS SetNeverReplicate( LNBOOL flag );

	LNSTATUS SetHideDesign( LNBOOL flag );
	
	LNSTATUS SetInheritsFromTemplateName( const LNString &name );
	
	LNSTATUS SetListInDatabaseCatalog( LNBOOL flag );
		
	LNSTATUS SetOwnerName(const LNString &name);

	LNSTATUS SetRemoveOldDocumentsDays( LNINT olddocdays );
	
	LNSTATUS SetRemoveOldDocuments( LNBOOL flag );
	
	LNSTATUS SetReplicateReceiveSummaries( LNBOOL flag );
	
	LNSTATUS SetReplicateSendDeletions( LNBOOL flag );
	
	LNSTATUS SetReplicateSendTitleAndCatalogInfo( LNBOOL flag );
	
	LNSTATUS SetReplicationPriority( LNREPLICATIONPRIORITY reppriority );
	
	LNSTATUS SetShowInOpenDatabaseDialog( LNBOOL flag );
	
	LNSTATUS SetTemplateName( const LNString &name );

	LNSTATUS SetTitle( const LNString &title );
	
private:
	LNDatabase & operator=( LNDatabaseBody *datab );

	LNSTATUS CreateDatabaseBody( LNNotesSession *session,
		const LNString &filename, const LNString &server );
	
	LNSTATUS DeleteFormXYZ( const LNString &formname );
	LNSTATUS DeleteFormXYZ( LNForm *form );

	LNDatabaseBody * GetDatabaseBody() const {return (LNDatabaseBody *)Body;}
	
	LNSTATUS GetFormXYZ( const LNString &formname, LNForm *form );
	LNSTATUS GetFormXYZ( const NOTEID idnote, LNForm *form );
	LNSTATUS GetFormXYZ( const UNID *unidnote, LNForm *form );
};	


#ifndef LNNOTE_HPP
#include "lnnote.hpp"
#endif

	
#endif	//LNDB_HPP

