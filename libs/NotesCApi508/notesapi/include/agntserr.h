
#ifndef AGENTS_ERR_DEFS
#define AGENTS_ERR_DEFS

#define ERR_QUERY_BADDATATYPE	PKG_AGENTS+1
	errortext(ERR_QUERY_BADDATATYPE,	"Unable to load saved search; search is corrupt.")
#define ERR_QUERY_BADDATA		PKG_AGENTS+2
	errortext(ERR_QUERY_BADDATA,	"Unable to load saved search; data is corrupt.")
#define ERR_QUERY_UNKNOWNTERM	PKG_AGENTS+3
	errortext(ERR_QUERY_UNKNOWNTERM,	"This search cannot be recognized by this version of Lotus Notes.")
#define ERR_ACTION_UNKNOWNTERM	PKG_AGENTS+4
	errortext(ERR_ACTION_UNKNOWNTERM,	"This action cannot be recognized by this version of Lotus Notes.")
#define ERR_ACTION_BADDATA		PKG_AGENTS+5
	errortext(ERR_ACTION_BADDATA,	"Unable to load saved action; action is corrupt.")
#define ERR_ASSISTANT_BADDATA	PKG_AGENTS+6
	errortext(ERR_ASSISTANT_BADDATA,	"Unable to load agent; data is corrupt.")
#define STR_QUERY_KEYWORDS		PKG_AGENTS+7
	stringtext(STR_QUERY_KEYWORDS,		"AND OR ACCRUE CONTAINS FIELD NEAR NOT PARAGRAPH SENTENCE TOPIC TERMWEIGHT EXACTCASE VERITYQUERY")
#define STR_ACTION_REPLYTEXT	PKG_AGENTS+8
	stringtext(STR_ACTION_REPLYTEXT,	"Reply to sender")
#define STR_ACTION_MODIFYFIELD	PKG_AGENTS+9
	stringtext(STR_ACTION_MODIFYFIELD,	"Modify field '%s': Set to '%s'")
#define ERR_ACTION_NONAMETOREPLYTO	PKG_AGENTS+10
	errortext(ERR_ACTION_NONAMETOREPLYTO,	"The agent could not reply to the document because the author of the document is unknown.")
#define STR_ACTION_RE			PKG_AGENTS+11
	stringtext(STR_ACTION_RE,	"Re: ")
#define ERR_ACTION_NO_MATCH		PKG_AGENTS+12
	errortext(ERR_ACTION_NO_MATCH,	"Unable to send mail to %s, no match found in Name & Address Book(s)")
#define ERR_ACTION_AMBIG_MATCH	PKG_AGENTS+13
	errortext(ERR_ACTION_AMBIG_MATCH,	"Unable to send mail to %s, multiple matches found in Name & Address Book(s)")
#define STR_ACTION_REPLYFORWARD	PKG_AGENTS+14
	stringtext(STR_ACTION_REPLYFORWARD,	"In response to:")
#define STR_ACTION_FORMULA		PKG_AGENTS+15
	stringtext(STR_ACTION_FORMULA,	"Run @function formula")
#define STR_ACTION_LOTUSSCRIPT	PKG_AGENTS+16
	stringtext(STR_ACTION_LOTUSSCRIPT,	"Run LotusScript")
#define STR_ACTION_SENDMAIL	PKG_AGENTS+17
	stringtext(STR_ACTION_SENDMAIL,	"Send Mail")
#define ERR_QUERY_INVALIDSETTINGS	PKG_AGENTS+18
	errortext(ERR_QUERY_INVALIDSETTINGS,	"Saved search is invalid.")
#define ERR_ACTION_BADDATATYPE		PKG_AGENTS+19
	errortext(ERR_ACTION_BADDATATYPE,	"Unable to load saved action; action is corrupt.")
#define STR_ACTION_COPYDBLOCAL		PKG_AGENTS+20
	stringtext(STR_ACTION_COPYDBLOCAL,	"Copy document to %s")
#define STR_ACTION_COPYDBREMOTE		PKG_AGENTS+21
	stringtext(STR_ACTION_COPYDBREMOTE,	"Copy document to %s on %s")
#define STR_ACTION_MOVEDBLOCAL		PKG_AGENTS+22
	stringtext(STR_ACTION_MOVEDBLOCAL,	"Move document to %s")
#define STR_ACTION_MOVEDBREMOTE		PKG_AGENTS+23
	stringtext(STR_ACTION_MOVEDBREMOTE,	"Move document to %s on %s")
#define STR_ACTION_DELETE			PKG_AGENTS+24
	stringtext(STR_ACTION_DELETE,	"Delete document")
#define STR_LOG_STARTAGENT			PKG_AGENTS+25
	stringtext(STR_LOG_STARTAGENT,	"Started running agent '%s' on %z")
#define STR_LOG_STOPAGENT			PKG_AGENTS+26
	stringtext(STR_LOG_STOPAGENT,	"Done running agent '%s' on %z")
#define STR_LOG_RUNON_ALL			PKG_AGENTS+27
	stringtext(STR_LOG_RUNON_ALL,	"Running on all documents in database: %ld total")
#define STR_LOG_RUNON_NEWMAIL		PKG_AGENTS+28
	stringtext(STR_LOG_RUNON_NEWMAIL,	"Running on new mail messages: %ld total")
#define STR_LOG_RUNON_MODIFIED		PKG_AGENTS+29
	stringtext(STR_LOG_RUNON_MODIFIED,	"Running on new or modified documents: %ld total")
#define STR_LOG_RUNON_NONE			PKG_AGENTS+30
	stringtext(STR_LOG_RUNON_NONE,	"Running with no context")
#define STR_LOG_FTRESULT			PKG_AGENTS+31
	stringtext(STR_LOG_FTRESULT,	"Found %ld document(s) that match search criteria")
#define STR_LOG_REPLY				PKG_AGENTS+32
	stringtext(STR_LOG_REPLY,		"Replied to %ld document(s)")
#define STR_LOG_FORMULA				PKG_AGENTS+33
	stringtext(STR_LOG_FORMULA,		"%ld document(s) were modified by formula")
#define STR_LOG_SENDMAIL			PKG_AGENTS+34
	stringtext(STR_LOG_SENDMAIL,	"Sent mail for %ld document(s)")
#define STR_LOG_DBCOPY				PKG_AGENTS+35
	stringtext(STR_LOG_DBCOPY,		"Copied %ld document(s)")
#define STR_LOG_DELETED				PKG_AGENTS+36
	stringtext(STR_LOG_DELETED,		"Deleted %ld document(s)")
#define STR_LOG_GENERALERROR		PKG_AGENTS+37
	stringtext(STR_LOG_GENERALERROR,	"ERROR: %e")
#define STR_LOG_MODIFYFIELD			PKG_AGENTS+38
	stringtext(STR_LOG_MODIFYFIELD,	"Modified field in %ld document(s)")
#define STR_ACTION_BYFORM			PKG_AGENTS+39
	stringtext(STR_ACTION_BYFORM,	"Modify fields by form")
#define STR_ACTION_MARKREAD			(PKG_AGENTS+40)
	stringtext(STR_ACTION_MARKREAD,	"Mark document read")
#define STR_ACTION_MARKUNREAD		(PKG_AGENTS+41)
	stringtext(STR_ACTION_MARKUNREAD,	"Mark document unread")
#define ERR_UNKNOWN_SEARCHTYPE		(PKG_AGENTS+42)
	errortext(ERR_UNKNOWN_SEARCHTYPE,	"Unknown trigger and search type; agent may be corrupt")
#define STR_QUERY_ETC				(PKG_AGENTS+43)
	stringtext(STR_QUERY_ETC,		"etc...")
#define STR_QUERY_INVALID			(PKG_AGENTS+44)
	stringtext(STR_QUERY_INVALID,	"(Invalid Query)")
#define ERR_INVALID_RUNNOW			(PKG_AGENTS+45)
	errortext(ERR_INVALID_RUNNOW,	"This agent cannot be run manually.  It will only be run when documents are pasted into the database.")
#define STR_LOG_MODIFYBYFORM		(PKG_AGENTS+46)
	stringtext(STR_LOG_MODIFYBYFORM,"Modified fields by form in %ld document(s)")
#define STR_ACTION_MOVETOFOLDER		(PKG_AGENTS+47)
	stringtext(STR_ACTION_MOVETOFOLDER,	"Move document to folder '%s'")
#define STR_ACTION_COPYTOFOLDER		(PKG_AGENTS+48)
	stringtext(STR_ACTION_COPYTOFOLDER,	"Copy document to folder '%s'")
#define STR_ACTION_REMOVEFROMFOLDER	(PKG_AGENTS+49)
	stringtext(STR_ACTION_REMOVEFROMFOLDER,	"Remove document from folder '%s'")
#define STR_ACTION_NEWSLETTER		(PKG_AGENTS+50)
	stringtext(STR_ACTION_NEWSLETTER,	"Send newsletter summary")
#define STR_ACTION_RUNAGENT			(PKG_AGENTS+51)
	stringtext(STR_ACTION_RUNAGENT,	"Run '%s' agent")
#define STR_ACTION_SENDDOCUMENT		(PKG_AGENTS+52)
	stringtext(STR_ACTION_SENDDOCUMENT,	"Send document")
#define STR_QUERY_BYFIELD			(PKG_AGENTS+53)
	stringtext(STR_QUERY_BYFIELD,	"field %s ")
/* 54 Unused, Available */

#define STR_QUERY_MISC1				(PKG_AGENTS+55)
	stringtext(STR_QUERY_MISC1,		"date created |date modified |contains any of |contains |does not contain ")
#define IDX_QUERY_BYDATECREATED		1
#define IDX_QUERY_BYDATEMODIFIED	2
#define IDX_QUERY_CONTAINSANY		3
#define IDX_QUERY_CONTAINSALL		4
#define IDX_QUERY_DOESNOTCONTAIN	5

#define STR_LOG_STARTTESTING		(PKG_AGENTS+56)
	stringtext(STR_LOG_STARTTESTING,"The following will occur when this agent is run:")
#define STR_LOG_TESTINGPREFIX		(PKG_AGENTS+57)
	stringtext(STR_LOG_TESTINGPREFIX,	"Testing:  ")
#define ERR_ASSIST_NO_USER			(PKG_AGENTS+58)
	errortext(ERR_ASSIST_NO_USER,	"(must have a user name to open db with access control)")
#define ERR_LOG_NODELETEACCESS		(PKG_AGENTS+59)
	errortext(ERR_LOG_NODELETEACCESS,	"%a is not authorized to delete document %lx")
#define ERR_LOG_NOMODIFYACCESS		(PKG_AGENTS+60)
	errortext(ERR_LOG_NOMODIFYACCESS,	"%a is not authorized to modify document %lx")
#define ERR_BAD_LS_AGENT            (PKG_AGENTS+61)
    errortext(ERR_BAD_LS_AGENT,     "Unable to edit LotusScript agent; action list is corrupt")
#define STR_QUERY_BYAUTHOR			(PKG_AGENTS+62)
	stringtext(STR_QUERY_BYAUTHOR,	"Author ")
#define STR_QUERY_BYFORM			(PKG_AGENTS+63)
	stringtext(STR_QUERY_BYFORM,	"matches example form")
#define STR_LOG_COPYTOFOLDER		(PKG_AGENTS+64)
	stringtext(STR_LOG_COPYTOFOLDER,	"Placed %ld document(s) in folder")
#define STR_LOG_REMOVEFROMFOLDER	(PKG_AGENTS+65)
	stringtext(STR_LOG_REMOVEFROMFOLDER,	"Removed %ld document(s) from folder")
#define STR_LOG_FOLDERNOTFOUND		(PKG_AGENTS+66)
	stringtext(STR_LOG_FOLDERNOTFOUND,	"Folder '%s' could not be found")
#define STR_LOG_AGENTNOTFOUND		(PKG_AGENTS+67)
	stringtext(STR_LOG_AGENTNOTFOUND,	"Agent '%s' could not be found")
#define ERR_ASSIST_NORUNOBJECT		(PKG_AGENTS+68)
	errortext(ERR_ASSIST_NORUNOBJECT,	"Could not find agent run data object")
#define STR_LOG_SENDDOCUMENT		(PKG_AGENTS+69)
	stringtext(STR_LOG_SENDDOCUMENT,	"Sent %ld document(s)")
#define ERR_ASSIST_NOSAMPLENOTE		(PKG_AGENTS+70)
	errortext(ERR_ASSIST_NOSAMPLENOTE,	"Could not execute formula when composing mail: no document found")
#define STR_LOG_BELOWGATHERLIMIT	(PKG_AGENTS+71)
	stringtext(STR_LOG_BELOWGATHERLIMIT,	"Less than %ld document(s) found; not enough to send mail")
#define STR_LOG_VIEWNOTFOUND		(PKG_AGENTS+72)
	stringtext(STR_LOG_VIEWNOTFOUND,	"View '%s' could not be found")
#define ERR_ASSIST_TOOMANYCOLUMNS	(PKG_AGENTS+73)
	stringtext(ERR_ASSIST_TOOMANYCOLUMNS,	"View has too many columns")
#define ERR_ASSIST_BADVIEWFORMAT	(PKG_AGENTS+74)
	stringtext(ERR_ASSIST_BADVIEWFORMAT,	"Bad view format")
#define STR_LOG_SENDNEWSLETTER		(PKG_AGENTS+75)
	stringtext(STR_LOG_SENDNEWSLETTER,	"Sent %ld newsletter(s)")
#define STR_LOG_MAILERROR		(PKG_AGENTS+76)
	stringtext(STR_LOG_MAILERROR,	"Unable to send mail to '%s'")
#define STR_LOG_MARKREAD			(PKG_AGENTS+77)
	stringtext(STR_LOG_MARKREAD,	"Marked %ld document(s) read")
#define STR_LOG_MARKUNREAD			(PKG_AGENTS+78)
	stringtext(STR_LOG_MARKUNREAD,	"Marked %ld document(s) unread")
#define STR_LOG_RUNAGENT			(PKG_AGENTS+79)
	stringtext(STR_LOG_RUNAGENT,	"Ran agent on %ld document(s)")
#define STR_LOG_LOTUSSCRIPT			(PKG_AGENTS+80)
	stringtext(STR_LOG_LOTUSSCRIPT,	"Ran LotusScript code")
#define STR_LOG_FORMNOTFOUND		(PKG_AGENTS+81)
	stringtext(STR_LOG_FORMNOTFOUND,	"Unable to find form for document")
#define STR_LOG_AGENTRUNNING		(PKG_AGENTS+82)
	stringtext(STR_LOG_AGENTRUNNING,	"Unable to run agent '%s'. This agent is already running")
#define ERR_ACCESS_OLDVERSION		(PKG_AGENTS+83)
	errortext(ERR_ACCESS_OLDVERSION,	"The server is running a previous version of Lotus Notes that does not support private agents")
#define STR_LOG_FORMULAERROR		(PKG_AGENTS+84)
	stringtext(STR_LOG_FORMULAERROR,	"Formula error: %e")
#define STR_QUERY_BYFOLDER			(PKG_AGENTS+85)
	stringtext(STR_QUERY_BYFOLDER,	"In folder '%s'")
#define ERR_CANNOT_QUERY_RICHTEXT	(PKG_AGENTS+86)
	errortext(ERR_CANNOT_QUERY_RICHTEXT,	"Cannot create a formula which references a rich text field")
#define ERR_DOCUMENT_NOT_SAVED		(PKG_AGENTS+87)
	errortext(ERR_DOCUMENT_NOT_SAVED,	"You must save the document before this action can be performed")
#define STR_QUERY_USESFORM			(PKG_AGENTS+88)
	stringtext(STR_QUERY_USESFORM,	"uses '%s' form")
#define STR_ACTION_MODIFYFIELDAPPEND (PKG_AGENTS+89)
	stringtext(STR_ACTION_MODIFYFIELDAPPEND,"Modify field '%s': Append '%s'")
#define ERR_MODIFYFIELD_APPEND		(PKG_AGENTS+90)
	errortext(ERR_MODIFYFIELD_APPEND,	"Append is only valid for text fields.")
#define ERR_ASSISTANT_TIMEOUT			(PKG_AGENTS+91)
	errortext(ERR_ASSISTANT_TIMEOUT,		"Agent did not complete within the time limit.")
#define ERR_AGENTS_NODOCUMENT			(PKG_AGENTS+92)
	errortext(ERR_AGENTS_NODOCUMENT,		"No document has been selected.")
#define STR_QUERY_TOPIC				(PKG_AGENTS+93)
	stringtext(STR_QUERY_TOPIC,		"Verity Topic Query")
#define STR_LOG_RUNON_PASTED			PKG_AGENTS+94
	stringtext(STR_LOG_RUNON_PASTED,	"Running on documents pasted into database: %ld total")
#define STR_LOG_RUNON_SELECTED			PKG_AGENTS+95
	stringtext(STR_LOG_RUNON_SELECTED,	"Running on selected documents: %ld total")
#define STR_LOG_RUNON_VIEW				PKG_AGENTS+96
	stringtext(STR_LOG_RUNON_VIEW,		"Running on all documents in view: %ld total")
#define STR_LOG_RUNON_UNREAD			PKG_AGENTS+97
	stringtext(STR_LOG_RUNON_UNREAD,	"Running on unread documents in view: %ld total")
#define STR_LOG_AGENT_PRINT_MSG            PKG_AGENTS+98
	stringtext(STR_LOG_AGENT_PRINT_MSG,    "Addin: Agent printing: %s")
#define STR_LOG_AGENT_ERROR_MSG            PKG_AGENTS+99
	stringtext(STR_LOG_AGENT_ERROR_MSG,    "Addin: Agent %s error message: %s")
#define STR_LOG_AGENT_MSGBOX_MSG           PKG_AGENTS+100
	stringtext(STR_LOG_AGENT_MSGBOX_MSG,   "Addin: Agent message box: %s")
#define STR_AGENTS_V3COMMENT			PKG_AGENTS+101
	stringtext(STR_AGENTS_V3COMMENT,	"This is an agent created in Release 4. Please do not run it or modify it using Release 3.")
#define ERR_ACTION_TEXTNOTSUPPORTED		PKG_AGENTS+102
	errortext(ERR_ACTION_TEXTNOTSUPPORTED,	"Plain text cannot be entered into a simple actions field.")
#define ERR_AGENT_AGENTRUNNING			(PKG_AGENTS+103)
	stringtext(ERR_AGENT_AGENTRUNNING,	"Unable to run agent because the agent is already running")
#define ERR_AGENT_MAILERROR				(PKG_AGENTS+104)
	stringtext(ERR_AGENT_MAILERROR,		"Unable to send mail")
#define ERR_AGENT_NOUICOMMANDS			(PKG_AGENTS+105)
	errortext(ERR_AGENT_NOUICOMMANDS,	"@Command and other UI functions are not allowed with this search type; please select 'Run once (@Commands may be used)'")
#define ERR_QUERY_FOLDERNOTFOUND		(PKG_AGENTS+106)
	errortext(ERR_QUERY_FOLDERNOTFOUND,	"Unable to find folder or view")
#define STR_AGENT_ATALL					(PKG_AGENTS+107)
	stringtext(STR_AGENT_ATALL,			";SELECT @All")
#define STR_AGENT_ATALL2	   			(PKG_AGENTS+108)
	stringtext(STR_AGENT_ATALL2,		"SELECT @All")
#define STR_AGENT_NEWSLETTER_ORPHAN		(PKG_AGENTS+109)
	stringtext(STR_AGENT_NEWSLETTER_ORPHAN,	"(This document was not found in the view specified by the agent)")
#define STR_LOG_NONEWSLETTERGATHER		(PKG_AGENTS+110)
	stringtext(STR_LOG_NONEWSLETTERGATHER,	"No newsletter was sent because less than %d documents were found")
#define STR_AGENT_SENTMAIL				(PKG_AGENTS+111)
	stringtext(STR_AGENT_SENTMAIL,		"Mail submitted for delivery.  (1 Person/Group)")
#define STR_AGENT_SENTMAIL2				(PKG_AGENTS+112)
	stringtext(STR_AGENT_SENTMAIL2,		"Mail submitted for delivery.  (%ld People/Groups)")
#define STR_AGENT_RUN_CORRUPT			(PKG_AGENTS+113)
	stringtext(STR_AGENT_RUN_CORRUPT,	"Unable to run this agent; Agent is corrupt - please edit and resave agent")
#define STR_LOG_MOVETOFOLDER			(PKG_AGENTS+114)
	stringtext(STR_LOG_MOVETOFOLDER,	"Moved %ld document(s) to folder")
#define ERR_MAIL_NO_MATCH				(PKG_AGENTS+115)
	errortext(ERR_MAIL_NO_MATCH,		"Unable to send mail; no match found in Name & Address Book(s)")
#define ERR_MAIL_AMBIGUOUS_MATCH		(PKG_AGENTS+116)
	errortext(ERR_MAIL_AMBIGUOUS_MATCH,	"Unable to send mail; multiple matches found in Name & Address Book(s)")
#define ERR_AGENT_RUNCTX_EXTENDED	(PKG_AGENTS+117)
	errortext(ERR_AGENT_RUNCTX_EXTENDED,	"Agent run context must be of extended type to use this call")
#define ERR_AGENT_NOMULT_AGENTRUN	(PKG_AGENTS+118)
	errortext(ERR_AGENT_NOMULT_AGENTRUN,	"Run context cannot be used with more than one agent at the same time")
#define ERR_AGENT_UNKNOWN_REDIR		(PKG_AGENTS+119)
	errortext(ERR_AGENT_UNKNOWN_REDIR,		"Unknown redirection type")
#define ERR_AGENT_UI_TRIGGER		(PKG_AGENTS+120)
	errortext(ERR_AGENT_UI_TRIGGER,			"Unsupported trigger and search in the background or embedded agent")
#define ERR_AMGR_RUN_ACCESS_ERROR           (PKG_AGENTS+121)
	errortext(ERR_AMGR_RUN_ACCESS_ERROR,    "Error validating user's agent execution access")
#define ERR_AMGR_RUN_ACCESS_LOSTDATA_ERROR  (PKG_AGENTS+122)
	errortext (ERR_AMGR_RUN_ACCESS_LOSTDATA_ERROR, "Error validating user's agent execution access. Restrictions field is longer than 256 characters. Use groups.")
#define ERR_AMGR_ACL_LOSTDATA_WARN	(PKG_AGENTS+123)
	errortext (ERR_AMGR_ACL_LOSTDATA_WARN, "AMgr: Agent execution restriction is longer than 256 characters. Use groups.")
#define STR_ACTION_JAVAAGENT			(PKG_AGENTS+124)
	stringtext(STR_ACTION_JAVAAGENT,	"Run Java Agent")
#define STR_LOG_JAVAAGENT			(PKG_AGENTS+125)
	stringtext(STR_LOG_JAVAAGENT,	"Ran Java Agent Class")
#define ERR_AMGR_DBOPEN_NOTLOCAL		(PKG_AGENT1+14)
	stringtext(ERR_AMGR_DBOPEN_NOTLOCAL	,"Cannot open databases on machines other than the server running your program")
#define ERR_AMGR_SERVERACCESS_LOSTDATA_WARN	 (PKG_AGENTS+126)
  errortext (ERR_AMGR_SERVERACCESS_LOSTDATA_WARN, "AMgr: Access/Not Access Server Restriction is longer than 256 characters.")
#define ERR_AMGR_NEWDB_LOSTDATA_WARN	 (PKG_AGENTS+127)
  errortext (ERR_AMGR_NEWDB_LOSTDATA_WARN, "AMgr: Create New Database Restriction is longer than 256 characters.")

/* NOTE: Since the AGENTS PKG codes are shared with ASSISTSANT2, 
		we are limited to strings 0 - 127 */ 

/* extended codes to AGENTS2 PKG limited to strings PKG_AGENTS2+0 through PKG_AGENTS2+31 */
#define STR_LOG_SYNCH_NO_EMBED			(PKG_AGENTS2+0)
	stringtext(STR_LOG_SYNCH_NO_EMBED,	"'Before mail arrives' agents cannot run other agents")

#define STR_WRONG_SERVER				(PKG_AGENTS2+1) /* inserted into ERR_AMGR_WRONG_SERVER (second param)*/
	stringtext(STR_WRONG_SERVER,	"'%a' not '%a'")
#define ERR_AMGR_WRONG_SERVER			(PKG_AGENTS2+2)
	errortext(ERR_AMGR_WRONG_SERVER,	"AMgr: Agent '%s' will not run. It is intended to run on %s")
#define ERR_AMGR_REPLICADB_LOSTDATA_WARN   (PKG_AGENTS2+3)
	errortext(ERR_AMGR_REPLICADB_LOSTDATA_WARN, "AMgr: Create Replica Restriction is longer than 256 characters.")
#define ERR_AMGR_NOPUBKEY   (PKG_AGENTS2+4)
	errortext(ERR_AMGR_NOPUBKEY, "Document set for JIT encryption and no public key available.")
#define ERR_AMGR_NOMIMESENT   (PKG_AGENTS2+5)
	errortext(ERR_AMGR_NOMIMESENT, "Document set for MIME format and an error occurred during sending or conversion.")
#define STR_LOG_SYNCH_INVALIDOP			(PKG_AGENTS2+6)
	stringtext(STR_LOG_SYNCH_INVALIDOP,	"Invalid operation on folder '%s' in 'Before mail delivery' agent. Invalid operation(s) ignored.")
#define ERR_AGENT_TEST_NO_BGAGENT			(PKG_AGENTS2+7)
	stringtext(ERR_AGENT_TEST_NO_BGAGENT,	"All background agents are disabled for this database.")
#define ERR_AGENT_WRONGVERSION_GENERIC		(PKG_AGENTS2+8)
	errortext(ERR_AGENT_WRONGVERSION_GENERIC,"The agent version is incompatible with this release")
#endif



