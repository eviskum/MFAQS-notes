
/* Extension Manager for Notes */

#ifndef EXMGR_DEFS
#define EXMGR_DEFS

#ifndef NSF_DATA_DEFS
#include "nsfdata.h"					/* We need DBHANDLE */
#endif

#ifndef NIF_DEFS
#include "nif.h"						/* We need HCOLLECTION */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Extension identifier */

typedef WORD EID;

/* handle passed back to identify registration */

typedef DWORD HEMREGISTRATION;

/* extension record; this data structure is passed to the callback routine */

typedef struct
	{
	EID			EId;					/* identifier */
	WORD		NotificationType;		/* EM_BEFORE or EM_AFTER */
	STATUS		Status;					/* core error code */
	VARARG_PTR	Ap;						/* ptr to args */
	} EMRECORD; 

/* the callback; takes one argument */

typedef STATUS (LNCALLBACKPTR EMHANDLER)(EMRECORD far *);

/*	Constants used in NotificationType */

#define EM_BEFORE	0
#define EM_AFTER	1

/*	Flags which can be passed to EMRegister */

#define EM_REG_BEFORE		0x0001
#define EM_REG_AFTER		0x0002

/* prototypes */

STATUS LNPUBLIC	EMRegister(EID EmID, DWORD Flags, EMHANDLER Proc, WORD RecursionID, HEMREGISTRATION far *rethRegistration);
STATUS LNPUBLIC	EMDeregister(HEMREGISTRATION hRegistration);
STATUS LNPUBLIC	EMCreateRecursionID(WORD far *retRecursionID);


/*	Types of extension callbacks */

#define EM_NSFDBCLOSESESSION				1
#define EM_NSFDBCLOSE						2
#define EM_NSFDBCREATE						3
#define EM_NSFDBDELETE						4
#define EM_NSFNOTEOPEN						5
#define EM_NSFNOTECLOSE						6
#define EM_NSFNOTECREATE					7
#define EM_NSFNOTEDELETE					8
#define EM_NSFNOTEOPENBYUNID				10
#define EM_FTGETLASTINDEXTIME				11
#define EM_FTINDEX							12
#define EM_FTSEARCH							13
#define EM_NIFFINDBYKEY						14
#define EM_NIFFINDBYNAME					15
#define EM_NIFOPENNOTE						17
#define EM_NIFREADENTRIES					18
#define EM_NIFUPDATECOLLECTION				20
#define EM_NSFDBALLOCOBJECT					22
#define EM_NSFDBCOMPACT						23
#define EM_NSFDBDELETENOTES					24
#define EM_NSFDBFREEOBJECT					25
#define EM_NSFDBGETMODIFIEDNOTETABLE		26
#define EM_NSFDBGETNOTEINFO					29
#define EM_NSFDBGETNOTEINFOBYUNID			30
#define EM_NSFDBGETOBJECTSIZE				31
#define EM_NSFDBGETSPECIALNOTEID			32
#define EM_NSFDBINFOGET						33
#define EM_NSFDBINFOSET						34
#define EM_NSFDBLOCATEBYREPLICAID			35
#define EM_NSFDBMODIFIEDTIME				36
#define EM_NSFDBREADOBJECT					37
#define EM_NSFDBREALLOCOBJECT				39
#define EM_NSFDBREPLICAINFOGET				40
#define EM_NSFDBREPLICAINFOSET				41
#define EM_NSFDBSPACEUSAGE					42
#define EM_NSFDBSTAMPNOTES					43
#define EM_NSFDBWRITEOBJECT					45
#define EM_NSFNOTEUPDATE					47
#define EM_NIFOPENCOLLECTION				50
#define EM_NIFCLOSECOLLECTION				51
#define EM_NSFDBGETBUILDVERSION				52
#define EM_NSFDBITEMDEFTABLE				56
#define EM_NSFDBREOPEN						59
#define EM_NSFDBOPENEXTENDED				63	
#define EM_NSFNOTEOPENEXTENDED				64
#define EM_TERMINATENSF						69
#define EM_NSFNOTEDECRYPT					70
#define EM_GETPASSWORD						73
#define EM_SETPASSWORD						74
#define EM_NSFCONFLICTHANDLER				75	
#define EM_MAILSENDNOTE						83
#define EM_CLEARPASSWORD					90
#define EM_NSFNOTEUPDATEXTENDED				102
#define EM_SCHFREETIMESEARCH				105
#define EM_SCHRETRIEVE						106
#define EM_SCHSRVRETRIEVE					107
#define EM_ADMINPPROCESSREQUEST				124
#define EM_NIFGETCOLLECTIONDATA				126
#define EM_NSFDBCOPYNOTE					127
#define EM_NSFNOTECOPY						128
#define EM_NSFNOTEATTACHFILE				129
#define EM_NSFNOTEDETACHFILE				130
#define EM_NSFNOTEEXTRACTFILE				131
#define EM_NSFNOTEATTACHOLE2OBJECT			132
#define EM_NSFNOTEDELETEOLE2OBJECT			133
#define EM_NSFNOTEEXTRACTOLE2OBJECT			134
#define EM_NSGETSERVERLIST					135
#define EM_NSFDBCOPY						136
#define EM_NSFDBCREATEANDCOPY				137
#define EM_NSFDBCOPYACL						138
#define EM_NSFDBCOPYTEMPLATEACL				139
#define EM_NSFDBCREATEACLFROMTEMPLATE		140
#define EM_NSFDBREADACL						141
#define EM_NSFDBSTOREACL					142
#define EM_NSFDBFILTER						143
#define EM_FTDELETEINDEX					144
#define EM_NSFNOTEGETINFO					145
#define EM_NSFNOTESETINFO					146
#define EM_NSFNOTECOMPUTEWITHFORM			147
#define EM_NIFFINDDESIGNNOTE				148
#define EM_NIFFINDPRIVATEDESIGNNOTE			149
#define EM_NIFGETLASTMODIFIEDTIME			150
#define EM_FTSEARCHEXT						160
#define EM_NAMELOOKUP						161
#define EM_NSFNOTEUPDATEMAILBOX				164
#define EM_NIFFINDDESIGNNOTEEXT         167
#define EM_AGENTOPEN                    170
#define EM_AGENTRUN                     171
#define EM_AGENTCLOSE                   172
#define EM_AGENTISENABLED               173
#define EM_AGENTCREATERUNCONTEXT        175
#define EM_AGENTDESTROYRUNCONTEXT       176
#define EM_AGENTSETDOCUMENTCONTEXT      177
#define EM_AGENTSETTIMEEXECUTIONLIMIT   178
#define EM_AGENTQUERYSTDOUTBUFFER       179
#define EM_AGENTREDIRECTSTDOUT          180
#define EM_SECAUTHENTICATION				184
#define EM_NAMELOOKUP2						185
#define EM_NSFMARKREAD						208
#define EM_NSFADDTOFOLDER					209
#define	EM_NSFDBSPACEUSAGESCALED			210		/* V5.04 */

/*	These functions are not actually defined (thus their declarations are only
	in comments) but illustrate the arguments for the corresponding extension
	manager callouts.

	EM_SETPASSWORD occurs when an ID file password is being set, either by
	a user or by administrator action.

	STATUS LNPUBLIC SetPassword (
						DWORD MaxPwdLen,	 Longest password you may supply 
						DWORD far *retLength, Return the length of the password
						char far *retPassword, Return the password here 

						char far *FileName,	 The name of the ID file 
						char far *OwnerName, The name of the owner of the ID file 

						DWORD DataLen,		 The old length of the extra ID info 
						BYTE far *Data,		 The old value of the extra ID info 

						DWORD MaxNewData,	 The max amount of extra ID info you may supply 
						DWORD far *retNewDataLen, Return the length of the new ID info 
						BYTE far *retNewData); Return the new ID info 

	EM_GETPASSWORD occurs when a user is about to be prompted for a password
	to decrypt and ID file.

	STATUS LNPUBLIC GetPassword (
						DWORD MaxPwdLen,	 Longest password you may supply 
						DWORD far *retLength, Return the length of the password here 
						char far *retPassword, Return the password here 

						char far *FileName,	 The name of the ID file 
						char far *OwnerName, The name of the owner of the ID file 

						DWORD DataLen,		 The length of the extra ID info 
						BYTE far *Data);	 The extra ID info 

	EM_CLEARPASSWORD occurs when a password is to be "cleared" either due to
	a timeout or because the user has pressed F5.

	STATUS LNPUBLIC ClearPassword ();


	STATUS LNPUBLIC ConflictHandler ( 
						HANDLE hDb,			Database Handle
						HANDLE hOldNote,	Original Note Handle
						HANDLE hNewNote,	New Note Handle
						DWORD  *pAction);	Conflict Action to take	

			*pAction returns:
				CONFLICT_ACTION_MERGE	- Have Notes try to merge
				CONFLICT_ACTION_HANDLE	- User handled the conflict	
				(zero)					- Proceed with Conflict in normal manner


	EM_ADMINPPROCESSREQUEST occurs prior to and after the Administration Process has
	processed a request on a server.

	STATUS LNPUBLIC ProcessRequest (
						NOTEHANDLE nhRequest, The handle of the Admin Request note 
						NOTEHANDLE nhResponse); The handle of the Admin Log note  


	EM_TERMINATENSF occurs when NSF service terminates for the process.

	void LNPUBLIC TerminateNSF (void *unused_params);


	EM_NSFNOTEUPDATEMAILBOX occurs when a NSFNoteUpdate is performed on 
	any and all mailbox databases (e.g. mail.box).  This is true even if
	multiple mailboxes are enabled in the server configuration document.
	The arguments are identical to those used for EM_NSFNOTEUPDATE.
	

	EM_NIFOPENNOTE opens a note by index position and optionally navigates.
	It is used by the Notes Editor.

	STATUS LNPUBLIC NIFOpenNote (
						HCOLLECTION hCollection,
						COLLECTIONPOSITION far *IndexPos,
						WORD Navigator,
						WORD FallbackNavigator,
						NOTEID NoteID,
						DWORD OpenFlags,
						INDEXSPECIALINFO far *retIndexInfo,
						HANDLE far *rethNote);


	EM_NSFNOTEOPENEXTENDED is a Notes internal, extended form of NSFNoteOpen.

	STATUS LNPUBLIC NSFNoteOpenExtended (
						DBHANDLE hDB,
						NOTEID NoteID,
						DWORD flags, 
						DWORD SinceSeqNum,
						BYTE *pKey,
						HANDLE *rtn);


	EM_MAILSENDNOTE is called when the Mailer sends an open note to recipients
	listed in the note's header items.

	STATUS LNPUBLIC MailSendNote (
						HANDLE			hNote,
						void			*internalViewDesc, 
						WORD			Flags, 
						BOOL			*Modified,
						void			*SendNoteCtx);


	EM_NSFMARKREAD is called when a note is opened by the Notes client and marked READ.
	Note that this does not include other mechanisms that could result in a note being
	marked read, such as being read by the client on another replica.

	STATUS LNPUBLIC NSFMarkRead(
							DBHANDLE	hDB,			- Handle of database containing note being marked
							HANDLE		hNote,			- Handle to note being marked read
							NOTEID		NoteID);		- NoteID of the note being marked read


	EM_NSFADDTOFOLDER is called when a note is being added or removed 
	from a folder.  The IsAddOperation flag should be checked to determine
	if this note is being added or removed from the folder.

	STATUS LNPUBLIC NSFAddToFolder( 
							DBHANDLE	hViewDB,		- Handle of database containing folder
							DBHANDLE	hDataDB,		- Handle of database containing notes being added to folder
							NOTEID		FolderNoteID,	- NoteID of the folder note
							NOTEID		NoteID,			- NoteID of the note being added to (removed from) the folder
							UNID		*NoteUNID,		- UNID of the note being added to (removed from) the folder
							BOOL		IsAddOperation,	- TRUE if note being added to the folder, FALSE if note being removed
							TIMEDATE	*RevisionTime);	- Time of original folder addition (OPTIONAL - may be NULL)


	The following functions ARE defined, but their extension manager callouts
	have slightly different signatures than the standard mechanism because of
	the fact that the function returns something other than STATUS.  The
	extension manager callout has an added argument which allows the callout
	to write the return value of the API routine.  For purposes of the callout,
	it is as if the function signatures were as follows.

	STATUS LNPUBLIC AgentIsEnabled(HAGENT hAgent, BOOL *return_value);

	EM_SECAUTHENTICATION is called on the server after the Notes Authentication
	succeeds but before the session is opened. 

	STATUS LNPUBLIC Authentication  (WORD		wEvent
									,SESSIONID	SessionId
									,char		far * pRemoteName
									,DWORD		dwFlags
									,WORD		wNetProtocol
									,char		far * NetAddress
									,void 		far * vpNull
									)


*/
/* Authentication Extension Manager flags
*/
#define fAuthRoleServer					((DWORD) 0x00000001)
#define fAuthRolePassthruServer			((DWORD) 0x00000002)
#define fAuthClientViaPassthruServer	((DWORD) 0x00000004)

/* Authentication Extension Manager events
*/
#define AUTHEM_StartAuthentication		((WORD) 0x0000)
#define AUTHEM_Poll					((WORD) 0x0001)
#define AUTHEM_Identify				((WORD) 0x0002)
#define AUTHEM_Terminate				((WORD) 0x0003)

#define MAXAUTHEMNAMELENGTH	1024

#ifdef __cplusplus
}
#endif

#endif /* EXMGR_DEFS */

