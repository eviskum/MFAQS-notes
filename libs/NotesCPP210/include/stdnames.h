#ifdef __cplusplus
extern "C" {
#endif


#ifndef STD_NAME_DEFS
#define STD_NAME_DEFS

/*	Standard NSF Field Name/Value Definitions for the Notes product */

/* Very global field names */

#define	FIELD_TITLE "$TITLE"
#define	FIELD_FORM	"Form"
#define FIELD_TYPE_TYPE	"Type"
#define	FIELD_LINK	"$REF"
#define	FIELD_UPDATED_BY "$UpdatedBy"
#define FIELD_NAMELIST "$NameList"
#define FIELD_NAMED 	"$Name"
#define	FIELD_URL		"URL"				/* used when copying link to clipboard */
#define	FIELD_UNAME		"$UName"			/* Universal UNID/Name */
#define	FIELD_CREATED	"$Created"			/* Created date, if specified overrides UNID created date for @Created */
#define FIELD_NAVIGATE_URL	"$NavigateToURL"/* used to pass a URL to an embedded web browser control */ 
#define FIELD_RELOAD_REFRESH "$ReloadRefresh"/* used to pass reload/refresh info to embedded web browser control */ 
#define	DESIGN_CLASS "$Class"
#define	DESIGN_MODIFIED "$Modified"
#define	DESIGN_COMMENT FILTER_COMMENT_ITEM
#define	DESIGN_READERS "$Readers"			/* Text list of users allowed to read note */
#define FIELD_ANONYMOUS "$Anonymous"		/* Indicates an anonymous document. */
#define	DESIGN_UPDATERS "$Updaters"			/* Text list of users allowed to update the folder note */
#define FIELD_NOPURGE 	"$NoPurge"			/* Note should never be purged. */
#define	DESIGN_RETAIN_FIELDS "$RetainFields"	/* Text list of fields to retain in a
													design refresh */
#define FIELD_ORIG_SIZE	"$OrigSize"			/* Size of entire note.  Set for
												abstracted note to give user
												info on whether they want to
												download the whole message or
												not. */
#define	FIELD_LANGUAGE "$LANGUAGE"			/* Used to specify the language of the note */
#define FIELD_VIEWLOCALE "$VIEWCOLLATION"

/* Public Access definitions */
#define FIELD_PUBLICROLE 	"$P"			/* Reader List role name for public users */
#define FIELD_PUBLICACCESS 	"$PublicAccess"	/* Note has public access if ACL_FLAG_PUBLICREADER is set. */
#define FORM_FIELD_PUBLICACCESS 	"$FormPublicAccess"	/* Form Note has public access if ACL_FLAG_PUBLICREADER is set. */
#define	FIELD_PUBLICACCESS_ENABLED	'1'

#define ITEM_NOTEID			"$$NoteID"			/* a NAMELookup item to be returned */
#define ITEM_DBNAME			"$$DBName"			/* address book this entry was found in */
#define ITEM_DBINDEX		"$$DBIndex"			/* 1-based db index upon primary NAB and ABs listed in MAB */
#define ITEM_MODIFIEDTIME	"$$ModifiedTime"	/* TIMEDATE this entry was last modified */
#define ITEM_DOMAINTYPE		"$$DomainType"		/* either NOTES or LDAP */

/*	Define Private note field name, and define the known types */

#define FIELD_PRIVATE_TYPE 	"$Private"

#define	FIELD_PRIVATE_TYPE_QUERY	'q'
#define	FIELD_PRIVATE_TYPE_AGENT	'a'
#define	FIELD_PRIVATE_TYPE_VIEW		'v'
#define	FIELD_PRIVATE_TYPE_FOLDER	'f'

/*	The following items are inserted into a note which cannot be saved to its
	Some special named notes. These values are stored in the FIELD_NAMED item to
	identify a named note. */

#define NAMEDNOTE_PRIVATEDESIGN		"$PrivateDesign"
#define NAMEDNOTE_PROFILE			"$Profile"
#define NAMEDNOTE_IMAP_DELETED_ENTRY "$IMAPResyncDE"


/* 	The following definitions of for the public directory profile note */
#define NAMEDNOTE_PUBLICDIRECTORYPROFILE	"directoryprofile"
#define LEDNAME_ITEM						"LedName"
#define DIRECTORY_DOMAIN_ITEM				"Domain" 

/*	The following items are inserted into a note which cannot be saved to its
	original database due to network failure.  When the failure can be
	remedied, the note is read back into memory and fixed up to point
	to correct database.  At that point the items are removed. */

#define PENDINGNAME					"NOTEPEND"
#define PENDINGSAVE_LINK_ITEM		"$ORIGLINK"
#define PENDINGSAVE_FILENAME_ITEM	"$ORIGFILE"

/*	Design flags */

#define	DESIGN_FLAGS "$Flags"

/*	Please keep these flags in alphabetic order (based on the flag itself) so that
	we can easily tell which flags to use next. Note that some of these flags apply
	to a particular NOTE_CLASS; others apply to all design elements. The comments
	indicate which is which. In theory, flags that apply to two different NOTE_CLASSes
	could overlap, but for now, try to make each flag unique. */

#define DESIGN_FLAG_ADD					'A'	/*	FORM: Indicates that a subform is in the add subform list */
#define DESIGN_FLAG_ANTIFOLDER			'a'	/*	VIEW: Indicates that a view is an antifolder view */
#define	DESIGN_FLAG_BACKGROUND_FILTER 	'B'	/*	FILTER: Indicates FILTER_TYPE_BACKGROUND is asserted */
#define	DESIGN_FLAG_INITBYDESIGNONLY	'b'	/*	VIEW: Indicates view can be initially built only by designer and above */
#define DESIGN_FLAG_NO_COMPOSE 			'C'	/*	FORM: Indicates a form that is used only for */
											/*		query by form (not on compose menu). */
#define DESIGN_FLAG_CALENDAR_VIEW		'c'	/*	VIEW: Indicates a form is a calendar style view. */
#define DESIGN_FLAG_NO_QUERY 			'D'	/* 	FORM: Indicates a form that should not be used in query by form */
#define DESIGN_FLAG_DEFAULT_DESIGN 		'd'	/* 	ALL: Indicates the default design note for it's class (used for VIEW) */
#define	DESIGN_FLAG_MAIL_FILTER 		'E'	/*	FILTER: Indicates FILTER_TYPE_MAIL is asserted */
#define DESIGN_FLAG_PUBLICANTIFOLDER	'e'	/*	VIEW: Indicates that a view is a public antifolder view */
#define DESIGN_FLAG_FOLDER_VIEW			'F'	/*	VIEW: This is a V4 folder view. */
#define DESIGN_FLAG_V4AGENT 			'f'	/*	FILTER: This is a V4 agent */
#define DESIGN_FLAG_VIEWMAP 			'G'	/*	VIEW: This is ViewMap/GraphicView/Navigator */
#define DESIGN_FLAG_OTHER_DLG			'H'	/*	ALL: Indicates a form that is placed in Other... dialog */
#define DESIGN_FLAG_V4PASTE_AGENT		'I'	/*	FILTER: This is a V4 paste agent */
#define DESIGN_FLAG_IMAGE_RESOURCE		'i'	/*	FORM: Note is a shared image resource */
#define DESIGN_FLAG_JAVA_AGENT   		'J' /*  FILTER: If its Java */
#define DESIGN_FLAG_JAVA_AGENT_WITH_SOURCE 'j' /* FILTER: If it is a java agent with java source code. */
#define DESIGN_FLAG_LOTUSSCRIPT_AGENT   'L' /*  FILTER: If its LOTUSSCRIPT */
#define DESIGN_FLAG_DELETED_DOCS		'l' /*  VIEW: Indicates that a view is a deleted documents view */
#define	DESIGN_FLAG_QUERY_MACRO_FILTER	'M'	/*	FILTER: Stored FT query AND macro */
#define DESIGN_FLAG_SITEMAP				'm' /*  FILTER: This is a site(m)ap. */
#define DESIGN_FLAG_NEW					'N'	/*  FORM: Indicates that a subform is listed when making a new form.*/
#define DESIGN_FLAG_HIDE_FROM_NOTES		'n' /*  ALL: notes stamped with this flag 
													will be hidden from Notes clients 
													We need a separate value here 
													because it is possible to be
													hidden from V4 AND to be hidden
													from Notes, and clearing one 
													should not clear the other */
#define	DESIGN_FLAG_QUERY_V4_OBJECT 	'O'	/*	FILTER: Indicates V4 search bar query object - used in addition to 'Q' */
#define DESIGN_FLAG_PRIVATE_STOREDESK   'o' /*  VIEW: If Private_1stUse, store the private view in desktop */
#define	DESIGN_FLAG_PRESERVE 			'P'	/*	ALL: related to data dictionary */
#define DESIGN_FLAG_PRIVATE_1STUSE 		'p'	/* 	VIEW: This is a private copy of a private on first use view. */
#define	DESIGN_FLAG_QUERY_FILTER 		'Q'	/*	FILTER: Indicates full text query ONLY, no filter macro */
#define DESIGN_FLAG_AGENT_SHOWINSEARCH	'q'	/*	FILTER: Search part of this agent should be shown in search bar */
#define DESIGN_FLAG_REPLACE_SPECIAL		'R'	/*	SPECIAL: this flag is the opposite of DESIGN_FLAG_PRESERVE, used
												only for the 'About' and 'Using' notes + the icon bitmap in the icon note */
#define DESIGN_FLAG_PROPAGATE_NOCHANGE  'r' /*  DESIGN: this flag is used to propagate the prohibition of design change */
#define DESIGN_FLAG_V4BACKGROUND_MACRO 	'S'	/*	FILTER: This is a V4 background agent */
#define DESIGN_FLAG_SCRIPTLIB			's'	/*	FILTER: A database global script library note */
#define DESIGN_FLAG_VIEW_CATEGORIZED 	'T'	/* 	VIEW: Indicates a view that is categorized on the categories field */
#define DESIGN_FLAG_DATABASESCRIPT		't'	/*	FILTER: A database script note */
#define DESIGN_FLAG_SUBFORM 			'U'	/*	FORM: Indicates that a form is a subform.*/
#define	DESIGN_FLAG_AGENT_RUNASWEBUSER	'u'	/*	FILTER: Indicates agent should run as effective user on web */
#define DESIGN_FLAG_PRIVATE_IN_DB 		'V'	/* 	ALL: This is a private element stored in the database */
#define DESIGN_FLAG_WEBPAGE				'W'	/*	FORM: Note is a WEBPAGE	*/
#define DESIGN_FLAG_HIDE_FROM_WEB		'w' /*  ALL: notes stamped with this flag 
													will be hidden from WEB clients */
/* WARNING: A formula that build Design Collecion relies on the fact that Agent Data's
			$Flags is the only Desing Collection element whose $Flags="X" */
#define DESIGN_FLAG_V4AGENT_DATA		'X' /*  FILTER: This is a V4 agent data note */
#define DESIGN_FLAG_SUBFORM_NORENDER	'x'	/*	SUBFORM: indicates whether
												we should render a subform in
												the parent form					*/
#define DESIGN_FLAG_NO_MENU 			'Y'	/*	ALL: Indicates that folder/view/etc. should be hidden from menu. */
#define DESIGN_FLAG_SACTIONS			'y'	/*	Shared actions note	*/
#define DESIGN_FLAG_MULTILINGUAL_PRESERVE_HIDDEN 'Z' /* ALL: Used to indicate design element was hidden */
											/*	before the 'Notes Global Designer' modified it. */
											/*	(used with the "!" flag) */
#define DESIGN_FLAG_FRAMESET			'#'	/*	FORM: Indicates that this is a frameset note */ 
#define DESIGN_FLAG_MULTILINGUAL_ELEMENT '!'/*	ALL: Indicates this design element supports the */
											/*	'Notes Global Designer' multilingual addin */
#define DESIGN_FLAG_JAVA_RESOURCE		'@'	/*	FORM: Note is a shared Java resource */
#define DESIGN_FLAG_HIDE_FROM_V3		'3'	/*	ALL: notes stamped with this flag 
													will be hidden from V3 client */
#define DESIGN_FLAG_HIDE_FROM_V4		'4'	/*	ALL: notes stamped with this flag 
													will be hidden from V4 client */
#define DESIGN_FLAG_HIDE_FROM_V5		'5'	/* 	FILTER: 'Q5'= hide from V4.5 search list */
											/*	ALL OTHER: notes stamped with this flag 
													will be hidden from V5 client */
#define DESIGN_FLAG_HIDE_FROM_V6		'6'	/*	ALL: notes stamped with this flag 
													will be hidden from V6 client */
#define DESIGN_FLAG_HIDE_FROM_V7		'7'	/*	ALL: notes stamped with this flag 
													will be hidden from V7 client */
#define DESIGN_FLAG_HIDE_FROM_V8		'8'	/*	ALL: notes stamped with this flag 
													will be hidden from V8 client */
#define DESIGN_FLAG_HIDE_FROM_V9		'9'	/*	ALL: notes stamped with this flag 
													will be hidden from V9 client */
#define DESIGN_FLAG_MUTILINGUAL_HIDE	'0'	/*	ALL: notes stamped with this flag 
													will be hidden from the client 
													usage is for different language
													versions of the design list to be
													hidden completely				*/


/*	These are the flags that help determine the type of a design element.
	These flags are used to sub-class the note classes, and cannot be
	changed once they are created (for example, there is no way to change
	a form into a subform). */

#define DESIGN_FLAGS_SUBCLASS		"UW#yi@GFXstm"

/*	These are the flags that can be used to distinguish between two
	design elements that have the same class, subclass (see DESIGN_FLAGS_SUBCLASS),
	and name. */

#define DESIGN_FLAGS_DISTINGUISH	"nw3456789"

/* '+' = ANY of the flags, '-' = NONE of the flags, '*' = ALL of the flags 	*/
/* '(+-*' = a combination of the above.										*/
/*	 Example:  "(+AB-C*DE" = (A OR B) AND (NOT C) AND (D AND E)				*/
/* 		Note: be sure to have +-* placeholders even if no flags for some.	*/
/* 			  ie: "(+-C*DE"   = (NOT C) AND (D AND E).						*/
/*	 Note: "(+-Q*" is equivalent to "-Q" 									*/

#define	DFLAGPAT_V4SEARCHBAR "(+Qq-Bst5nm*"	/* display things editable at V4 search bar; version filtering */
#define	DFLAGPAT_SEARCHBAR "(+QM-st5nm*" 	/* display things editable at search bar; version filtering */

#define DFLAGPAT_VIEWFORM "-FQMUGXWy#i@0n"	/* display things editable with dialog box; version filtering */
#define DFLAGPAT_VIEWFORM_MENUABLE "-FQMUGXWy#i@40n"	/* display things showable on the menu */
#define DFLAGPAT_VIEWFORM_ALL_VERSIONS "-FQMUGXWy#i@" /* display things editable with dialog box; no version filtering (for design) */

#define	DFLAGPAT_TOOLSRUNMACRO "-QXMBESIst5nm"/* display things that are runnable; version filtering */
#define DFLAGPAT_AGENTSLIST	"-QXstm"		/* display things that show up in agents list. No version filtering (for design) */
#define DFLAGPAT_PASTEAGENTS	"+I"		/* select only paste agents */
#define DFLAGPAT_SCRIPTLIB		 "+s"		/* display only database global script libraries */
#define DFLAGPAT_SCRIPTLIB_LS	 "(+s-j*"	/* display only database global LotusScript script libraries */
#define DFLAGPAT_SCRIPTLIB_JAVA	 "*sj"		/* display only database global Java script libraries */
#define DFLAGPAT_DATABASESCRIPT "+t"		/* display only database level script */

#define DFLAGPAT_SUBFORM "(+U-40n*"		 	/* display only subforms; version filtering	*/
#define DFLAGPAT_SUBFORM_DESIGN "(+U-40*"	/* display only subforms; for design mode, version filtering	*/
#define DFLAGPAT_SUBFORM_ALL_VERSIONS "+U"	/* only subforms; no version filtering */
#define	DFLAGPAT_DBRUNMACRO "+BS"			/* run all background filters */
#define DFLAGPAT_COMPOSE "-C40n"			/* display forms that belong in compose menu; version filtering */
#define DFLAGPAT_NOHIDDENNOTES "-n"			/* select elements not hidden from notes */
#define DFLAGPAT_NOHIDDENWEB "-w"			/* select elements not hidden from web */
#define DFLAGPAT_QUERYBYFORM "-D40ny"		/* display forms that appear in query by form; version filtering */
#define	DFLAGPAT_PRESERVE "+P"				/* related to data dictionary; no version filtering */
#define DFLAGPAT_SUBADD	"(+-40*UA"			/* subforms in the add subform list; no version filtering */
#define DFLAGPAT_SUBNEW "(+-40*UN"			/* subforms that are listed when making a new form.*/
#define DFLAGPAT_VIEW "-FG40n"				/* display only views */
#define DFLAGPAT_VIEW_DESIGN "-FG40"		/* display only views, ignore hidden from notes */
#define DFLAGPAT_NOTHIDDEN "-40n"			/* design element is not hidden*/
#define DFLAGPAT_FOLDER "(+-04n*F"			/* display only folders; version filtering */
#define DFLAGPAT_FOLDER_DESIGN "(+-04*F"	/* display only folders; version filtering, ignore hidden notes */
#define DFLAGPAT_FOLDER_ALL_VERSIONS "*F"/* display only folders; no version filtering (for design) */
#define DFLAGPAT_CALENDAR "*c"				/* display only calendar-style views */
#define DFLAGPAT_SHAREDVIEWS "-FGV40n"		/* display only shared views */
#define DFLAGPAT_SHAREDVIEWSFOLDERS "-GV40p"	/* display only shared views and folder; all notes & web */
#define DFLAGPAT_SHAREDWEBVIEWS "-FGV40wp"	/* display only shared views not hidden from web */
#define DFLAGPAT_SHAREDWEBVIEWSFOLDERS "-GV40wp" /* display only shared views and folders not hidden from web */
#define DFLAGPAT_VIEWS_AND_FOLDERS "-G40n"	/* display only views and folder; version filtering */
#define DFLAGPAT_VIEWS_AND_FOLDERS_DESIGN "-G40"	/* display only views and folder; all notes & web */

#define DFLAGPAT_VIEWMAP "(+-04n*G"			/* display only GraphicViews; version filtering */
#define DFLAGPAT_VIEWMAP_ALL_VERSIONS "*G"	/* display only GraphicViews; no version filtering (for design) */
#define DFLAGPAT_VIEWMAPWEB "(+-04w*G"		/* display only GraphicViews available to web; version filtering */
#define DFLAGPAT_VIEWMAP_DESIGN "(+-04*G" 	/* display only GraphicViews; all notes & web navs */

#define DFLAGPAT_WEBPAGE "(+-*W"			/* display WebPages	*/
#define DFLAGPAT_WEBPAGE_NOTES "(+W-n*"		/* display WebPages	available to notes client */
#define DFLAGPAT_WEBPAGE_WEB "(+W-w*"		/* display WebPages	available to web client */
#define DFLAGPAT_OTHER_DLG "(+-04n*H"			/* display forms that belong in compose menu */
#define DFLAGPAT_CATEGORIZED_VIEW "(+-04n*T"	/* display only categorized views */

#define DFLAGPAT_DEFAULT_DESIGN "+d"		/* detect default design note for it's class (used for VIEW) */
#define DFLAGPAT_FRAMESET "(+-*#"			/* display only Frameset notes */
#define DFLAGPAT_FRAMESET_NOTES "(+#-n*"  	/* Frameset notes available to notes client */
#define DFLAGPAT_FRAMESET_WEB "(+#-w*"  	/* Frameset notes available to web client */
#define DFLAGPAT_SITEMAP	"+m"			/* SiteMap notes (actually, "mQ345") */
#define DFLAGPAT_SITEMAP_NOTES "(+m-n*"		/* sitemap notes available to notes client */
#define DFLAGPAT_SITEMAP_WEB "(+m-w*"		/* sitemap notes available to web client */
#define DFLAGPAT_IMAGE_RESOURCE "+i"		/* display only shared image resources */
#define DFLAGPAT_JAVA_RESOURCE "+@"			/* display only shared Java resources */

/* Shared actions must be visible to both Notes and the Web since there is
	only one of these puppies - there is no list in the designer to get at
	more than one.  However, for completeness, I'll make the appropriate
	patterns for the day we may want to have separateness. */

#define DFLAGPAT_SACTIONS_DESIGN "+y"
#define DFLAGPAT_SACTIONS_WEB 	 "(+-0*y"
#define DFLAGPAT_SACTIONS_NOTES	 "(+-0*y"


/* Web server patterns */
#define DFLAGPAT_NONWEB "+w50stVXp"			/* elements that are never used on the web */
#define DFLAGPAT_NONWEB_EXCLUDE "-w50stVXp"	/* same flags as DFLAGPAT_NONWEB */
/* For the rest, no need to include flags from DFLAGPAT_NONWEB, since
   these flags are excluded in an initial pass. (see insrv\inotes\ndesdict.cpp) */
#define DFLAGPAT_AGENTSWEB "(+-QXstm*"		/* agents that can be run from the web */
#define DFLAGPAT_FORMSWEB "-U#Wi@y"			/* forms usable from the web */
#define DFLAGPAT_SUBFORMSWEB "+U"			/* subforms usable from the web */
#define DFLAGPAT_FRAMESETSWEB "+#"			/* frameset from the web */
#define DFLAGPAT_PAGESWEB "+W"				/* web pages from the web */
#define DFLAGPAT_VIEWSWEB "-G"				/* views usable from the web */
#define DFLAGPAT_NAVIGATORSWEB "+G"			/* navigators usable from the web */
#define DFLAGPAT_SHAREDFIELDSWEB "*"		/* shared fields usable from the web */
#define DFLAGPAT_ALLWEB "*"					/* all design elements */
#define DFLAGPAT_FIRSTPATTERNCHAR "(+-*"	/* patterns start with one of these */


/* Compute-defined item names that are actually pseudo-items, requested
   by NIF, that cause Compute to return some info.  These are not actually
   in any document, and if they are, will probably not work properly. */

#define	FIELD_COMPUTE_READERS "$C1$"

/* Mail note item names */

#define MAIL_MESSAGETYPE_ITEM "MessageType"		/* Message type. */
#define MAIL_MESSAGE_TYPE_ITEM "$MessageType"	/* $MessageType item name */
#define MAIL_SENDTO_ITEM "SendTo"				/* SendTo item name */
#define MAIL_COPYTO_ITEM "CopyTo"				/* CopyTo item name */
#define MAIL_REPLYTO_ITEM		"ReplyTo"		/* ReplyTo, used for agents */
#define MAIL_RESPONSETO_ITEM	"ResponseTo"	/* ResponseTo, used for agents */
#define MAIL_FROM_ITEM "From"					/* From item name */
#define MAIL_FROMDOMAIN_ITEM "FromDomain"		/* From domain item name */
#define MAIL_SUBJECT_ITEM "Subject"				/* Subject item name */
#define MAIL_DISPLAY_SUBJECT_ITEM "DisplaySubject"	/* Used by reply form */
#define MAIL_COMPOSEDDATE_ITEM "ComposedDate"	/* Composed date item name */
#define MAIL_POSTEDDATE_ITEM "PostedDate"		/* Posted date item name */
#define MAIL_BODY_ITEM "Body"					/* Body item name */
#define MAIL_INTENDEDRECIPIENT_ITEM "IntendedRecipient" /* Intended recipient item */
#define MAIL_FAILUREREASON_ITEM "FailureReason"		/* Failure reason item */
#define MAIL_DEADFAILUREREASON_ITEM "DeadFailureReason"		/* DEAD Failure reason item */
#define MAIL_RECIPIENTS_ITEM "Recipients"		/* Recipients list item */
#define MAIL_ROUTINGSTATE_ITEM "RoutingState"	/* Routing state */
#define MAIL_SAVED_FORM_ITEM "MailSavedForm"	/* Delivery report saved form name item */
#define MAIL_BLINDCOPYTO_ITEM "BlindCopyTo"		/* Blind copy to item name */
#define MAIL_DELIVERYPRIORITY_ITEM "DeliveryPriority" /* Delivery priority item name */
#define MAIL_DELIVERYREPORT_ITEM "DeliveryReport"	/* Delivery report request item name */
#define MAIL_DELIVEREDDATE_ITEM "DeliveredDate"	/* Delivered date item name */
#define MAIL_DELIVERYDATE_ITEM "DeliveryDate"	/* Delivery date item name (Confirmation Reports only) */
#define MAIL_FORM_ITEM FIELD_FORM				/* Form name item */
#define MAIL_REPLY_FORM_ITEM	"ReplyForm"		/* Reply form, used for agents */
#define MAIL_CATEGORIES_ITEM "Categories"		/* Categories field */
#define MAIL_FROM_CATEGORIES_ITEM "FromCategories"	/* Sender's Categories field */
#define MAIL_ROUTE_SERVERS_ITEM "RouteServers"	/* List of servers routed thru */
#define MAIL_ROUTE_TIME_ITEM "RouteTimes"		/* List of TIMEDATE_PAIRS describing holding times */
#define MAIL_RECIP_GROUPS_EXP_ITEM "RecipientGroupsExpanded" /* List of recipient group names that have been expanded */
#define MAIL_RETURNRECEIPT_ITEM "ReturnReceipt"	/* Return receipt requested? */
#define MAIL_NAMED_ENCKEY_ITEM "NamedEncryptionKey" /* Named encryption key. */
#define MAIL_ROUTE_HOPS_ITEM "$Hops" 			/* Number of routing hops still allowed. */
#define MAIL_CORRELATION_ITEM "$Correlation" 	/* Arbitrary delivery report correlation value. */
#define MAIL_FORMAT_ITEM "MailFormat"			/* (E)ncapsulated */
												/* (T)ext */
												/* (B)oth */
#define MAIL_IMPORTANCE_ITEM "Importance"		/* Send Priority/Importance item */
#define MAIL_QUALRECIPIENTS_ITEM "QualRecipients"	/* Fully qualified Recipients list item */
#define MAIL_ORIGNALPATH_ITEM "OriginalPath"	/* Original routing path (copy of original message's FromDomain) */
#define MAIL_TRACE_ITEM "$Trace"				/* Identifies message as a trace file */
#define MAIL_ORIG_ITEM	"$Orig"					/* Global Id used for Billing */
#define MAIL_DELIVER_LOOPS_ITEM "$Loops" 		/* Number of forwarding loops still allowed. */
#define MAIL_CLUSTERFAILOVER_ITEM "$MailClusterFailover" /* Server name mail was delivered to after cluster failover */
#define MAIL_UIDL_ITEM	"MailPop3UIDL"
#define MAIL_ENTERSENDTO_ITEM "EnterSendTo"		/* Enter SendTo item name */
#define MAIL_ENTERCOPYTO_ITEM "EnterCopyTo"		/* Enter CopyTo item name */
#define MAIL_ENTERBLINDCOPYTO_ITEM "EnterBlindCopyTo" /* Enter Blind copy to item name */
#define MAIL_INETSENDTO_ITEM "INetSendTo"	  	/* Internet SendTo item name */
#define MAIL_INETCOPYTO_ITEM "INetCopyTo"		/* Internet CopyTo item name */
#define MAIL_INETBLINDCOPYTO_ITEM "INetBlindCopyTo" /* Internet Blind copy to item name */
#define MAIL_ALTSENDTO_ITEM "AltSendTo"	  		/* Alternate Name SendTo item name */
#define MAIL_ALTCOPYTO_ITEM "AltCopyTo"			/* Alternate Name CopyTo item name */
#define MAIL_ALTBLINDCOPYTO_ITEM "AltBlindCopyTo" /* Alternet Blind copy to item name */
#define MAIL_ALTREPLYTO_ITEM "$AltReplyTo"		/* Alternate Reply To item name */
#define MAIL_ALTPRINCIPAL_ITEM "$AltPrincipal"	/* Alternate Principal item name */
#define MAIL_INETFROM_ITEM "INetFrom"			/* Internet From item name */
#define MAIL_ALTFROM_ITEM "AltFrom"				/* Alternate Name From item name */
#define MAIL_LANGFROM_ITEM "$LangFrom"			/* Language Tag From item name */
#define MAIL_DONOTHOLD_ITEM "$DoNotHold"		/* To prevent holding non-deliverable mail */
#define MAIL_STORAGETO_ITEM "$StorageTo"		/* Storage type To */
#define MAIL_STORAGECC_ITEM "$StorageCc"		/* Storage type Cc */
#define MAIL_STORAGEBCC_ITEM "$StorageBcc"		/* Storage type Bcc */
#define MAIL_LANGTO_ITEM "$LangTo"				/* Language tag To */
#define MAIL_LANGCC_ITEM "$LangCc"				/* Language tag Cc */
#define MAIL_LANGBCC_ITEM "$LangBcc"			/* Language tag Bcc */
#define MAIL_VIEWICON_ITEM			"_ViewIcon"	/* Icon to display in view column */
#define MAIL_EXCLUDEFROMVIEW_ITEM	"ExcludeFromView" /* View(s) to exclude note from in mail file */
#define MAIL_PRINCIPAL_ITEM 		"Principal"	/* Mail file from which a note was sent */
#define MAIL_ALTNAMELANGUAGETAGS_ITEM	"$NameLanguageTags"	/* Language Tags item. Single list of Lang Tags for set of current recipients. No Dups. */
#define MAIL_INETREPLYTO_ITEM "$INetReplyTo"   	/* Internet ReplyTo item name */
#define MAIL_INETPRINCIPAL_ITEM "$INetPrincipal" /* Internet Principal item name */
#define MAIL_MAILER_ITEM "$Mailer"				/* Name and version number of the Mailer which sent the message */
#define MAIL_ID_ITEM "$MessageID"				/* Unique ID of this message */

#define MAIL_APPARENTLY_FROM_ITEM "Apparently_From"
#define MAIL_APPARENTLY_TO_ITEM "Apparently_To"
#define MAIL_DISPOSITION_NOTIFICATION_TO_ITEM "Disposition_Notification_To"
#define MAIL_ORIGINAL_BCC_ITEM "Originalbcc"
#define MAIL_ORIGINAL_CC_ITEM "Originalcc"
#define MAIL_ORIGINAL_FROM_ITEM "OriginalFrom"
#define MAIL_ORIGINAL_PRINCIPAL_ITEM "OriginalPrincipal"
#define MAIL_ORIGINAL_REPLY_TO_ITEM "OriginalReplyTo"
#define MAIL_ORIGINAL_TO_ITEM "OriginalTo"
#define MAIL_RECEIVED_ITEM "Received"
#define MAIL_RESENT_BCC_ITEM "Resent_bcc"
#define MAIL_RESENT_CC_ITEM "Resent_cc"
#define MAIL_RESENT_DATE_ITEM "Resent_Date"
#define MAIL_RESENT_FROM_ITEM "Resent_From"
#define MAIL_RESENT_MESSAGE_ID_ITEM "Resent_Message_ID"
#define MAIL_RESENT_REPLY_TO_ITEM "Resent_Reply_To"
#define MAIL_RESENT_SENDER_ITEM "Resent_Sender"
#define MAIL_RESENT_TO_ITEM "Resent_To"
#define MAIL_RETURN_RECEIPT_TO_ITEM "Return_Receipt_To"
#define MAIL_SENDER_ITEM "Sender"
#define MAIL_MIME_VERSION "MIME_Version"
#define MAIL_FIRST_PASS "MailFirstPass"

/* POP3 view names */
#define MAIL_POP3_UIDL_VIEW	"($POP3UIDL)"

/*	Appointment form item names */

#define MAIL_APPT_BUSYNAME_ITEM 	"$BusyName"		/* Person/resource the appointment is for */
#define MAIL_APPT_STARTTIME_ITEM	"StartDateTime"	/* Start time of appointment */
#define MAIL_APPT_ENDTIME_ITEM		"EndDateTime"	/* End time of appointment */
#define MAIL_APPT_SEQUENCE_ITEM		"$Sequence"		/* Sequence # of updates */
#define MAIL_APPT_BUSYPRIORITY_ITEM "$BusyPriority"  /* Busy/Penciled-in/etc. */
#define MAIL_APPT_ATTENDEE_ITEM				"Attendees"	/* List of people for which the following items apply */
#define MAIL_APPT_ATTENDEE_STATE_ITEM		"ORGState"	/* Chairman, attendee, resource */
#define MAIL_APPT_ATTENDEE_STATUS_ITEM		"ORGStatus"	/* Deleted, etc. */
#define MAIL_APPT_ATTENDEE_OPTIONAL_ITEM	"OPTIONAL"	/* If TRUE, attendee is optional */
#define MAIL_APPT_PREV_BUSYNAME_ITEM 		"$PrevBusyName"		/* Previous Person/resource(s) the appointment is for */
#define RESOURCE_NAMESPACE_RESOURCES		"($RLookup)"		/* View containing resources sorted by name */
#define RESOURCE_NAMESPACE_RESERVATIONS		"($FindReservation)"	/* View containing reservations by name and apptunid */
#define MAIL_REPEAT_LOOKUP_NAMESPACE		"($RepeatLookup)"	/* View containing repeat replies/updates */
#define MAIL_REPEAT_INSTANCE_LOOKUP_NAMESPACE		"($RepeatInstanceLookup)"	/* View containing repeat instances */



/*  Internet Message Note items and definitions (for Internet Mail and Internet News) */

#define IMSG_RFC822_FILENAME_ITEM 			"$IntMailMsgFileName" /*  Name of the attachment that contains the BLOB.    */
																  /*  This contains the string 'Mail' because of   	    */
																  /*  history and changing it now would affect existing */
																  /*  databases and code.								*/
#define MAIL_TMP_MESSAGE_ID_DOMAIN			"LocalDomain"			/* Used as a place holder on constructed MessageIDs */

#define MAIL_MIME_CHARSET					"MIMEMailCharset"	/* field with charset value */

/*
 *	Person documents contain an item (MessageStorage) which indicates each person's preference for how
 *	messages delivered to them will be stored. Definitions of the valid values for this item are named
 *	IMSG_PREFERENCE_XXX.
 *
 *	Mail messages contain an item ($MessageStorage) which indicates the actual storage format of the
 *	message if it has been converted. Definitions of the valid values for this item are named
 *	IMSG_STORAGE_XXX. This item is deleted from messages when they are delivered by the router.
 *
 *	Routines which store messages or convert messages accept arguments which specify the required
 *	storage format. These routines accept values named IMSG_STORAGE_XXX.
 *
 *	As a performance optimization for the router, there is another item which can exist on a note
 *	which indicates that the note is stored in native MIME. This item is $NoteHasNativeMIME.
 */

#define IMSG_STORAGE_ITEM 					"$MessageStorage"	/* Describes how mail is stored.  See IMSG_STORAGE_XXX */

#define IMSG_STORAGE_UNKNOWN				0xFF /* can't find storage type */
#define IMSG_STORAGE_CDRECORDS				0 	/* Store as cd records only */
#define IMSG_STORAGE_CDRECORDS_AND_RFC822	1 	/* Store as cd records & attachment of original message */
#define IMSG_STORAGE_RFC822					2 	/* Store original message as attachment (no cdrecords) */
#define IMSG_STORAGE_NATIVE_MIME			3	/* Store headers & parts as separate items (without conversion) or CD */
#define IMSG_STORAGE_HAIKU					4	/* Store for Haiku users only */
/* Be sure to update count (IMSG_STORAGE_FORMATS) if new formats are added */

#define IMSG_STORAGE_FORMATS				5	/* Count of known storage formats */

#define IMSG_PREFERENCE_UNKNOWN				0xFF /* can't find preference type */
#define IMSG_PREFERENCE_NOTES				0	/* V4->CD, V5->CD or MIME */
#define IMSG_PREFERENCE_NOTES_AND_MIME		1	/* V4->CD and MIME blob, V5->CD or MIME */
#define IMSG_PREFERENCE_MIME				2	/* V4->MIME blob only, V5->Native MIME */
#define IMSG_PREFERENCE_HAIKU				3	/* V4->N/A, V5->Native MIME+Haiku fields */

#define IMSG_PREFERENCE_FORMATS				4	/* Count of known preference formats */

#define IMSG_RFC822_MSG_SIZE_ITEM			"$RFC822MessageSize"	/* Message size field (used by POP3 client) */
#define IMSG_RFC822_MSG_FILE_NAME			"$RFC822.eml"			/* Attached "MIME BLOB" name */
#define IMSG_SMTP_ORIGINATOR_ITEM			"SMTPOriginator"		/* RFC821 message originator */
#define IMSG_SMTP_RET_HDRS_ITEM				"SMTPReturnHdrs"		/* If TRUE, return only headers with non DSN */
#define IMSG_SMTP_ENVID_ITEM				"SMTPEnvid"				/* If ESMTP DSN is supported, ENVID to relay */
#define IMSG_SMTP_DSN_RCPTS_ITEM			"SMTPDSNRecipients"		/* If ESMTP DSN is supported, per rcpt info */
#define IMSG_SMTP_DSN_DELIVERY_STATUS		"SMTPDSNDeliveryStatus"	/* RFC822 formatted delivery status */

#define ITEM_MIMEHEADERS					"$MIMEHeaders"
#define ITEM_MIMETRACK						"$MIMETrack"
#define ITEM_IS_NATIVE_MIME					"$NoteHasNativeMIME"
#define ITEM_NOT_FROM_NOTES					"$SMTPNotFromNotes"
#define ITEM_KEEP_NOTES_ITEMS				"$SMTPKeepNotesItems"

#define ITEM_HEADERS_CONVERTED				"$ExportHeadersConverted"

/*	Calendar profile form related */

/*	On a profile are eight fields that relate to when a users is available:

	The AvailableDays item corresponds to the checkboxes allowing the user
		to choose which days of the week they work.  The resulting item
		will be a textlist which contains the days of the week that they
		work.
	For the days of the week that the user does work, the time ranges are
		read and for each day and assimilated into one item in the busytime
		database that represents the days and time the user or resource
		is available for scheduling.
	The item is encoded as follows:
		DateTime.Lower.Date	- a day that corresponds to the day of the week
					  .Time - start time of an interval for that day the user works
				.Upper.Date - the same day as the Lower
					  .Time - end time of an interval for that day the user works

		These values will repeat for the various times during the day for
			every day of the week that the user works.

	(i.e.	The default configuration will be: (for Monday through Friday)

		A Monday,	9:00 AM - A Monday, 12:00 PM
		A Monday,	1:00 PM - A Monday, 5:00 PM)

	NOTE:	The encoding does not care which real date is used, it just
			determines what day of the week the date correspondes to..
*/

#define MAIL_CALENDAR_PROFILE_WORK_AVAILABLEDAYS_ITEM	"$AvailableDays"
#define MAIL_CALENDAR_PROFILE_OWNER_ITEM				"Owner"				/* Owner field in calendar profile form */
#define MAIL_CALENDAR_PROFILE_WORK_WEEKDAYPREFIX		"$Times"
#define MAIL_CALENDAR_PROFILE_WORK_WEEKDAYSUFFIX		""
#define MAIL_CALENDAR_PROFILE_WORK_SUNDAY_ITEM			"$Times1"
#define MAIL_CALENDAR_PROFILE_WORK_MONDAY_ITEM			"$Times2"
#define MAIL_CALENDAR_PROFILE_WORK_TUESDAY_ITEM			"$Times3"
#define MAIL_CALENDAR_PROFILE_WORK_WEDNESDAY_ITEM 		"$Times4"
#define MAIL_CALENDAR_PROFILE_WORK_THURSDAY_ITEM		"$Times5"	
#define MAIL_CALENDAR_PROFILE_WORK_FRIDAY_ITEM			"$Times6"
#define MAIL_CALENDAR_PROFILE_WORK_SATURDAY_ITEM		"$Times7"
#define MAIL_CALENDAR_PROFILE_ENABLE_ALARMS_ITEM		"EnableAlarms"
#define MAIL_CALENDAR_PROFILE_APPROVALLIST_ITEM			"$ApprovalList"
#define MAIL_CALENDAR_PROFILE_DEFAULTDURATION_ITEM		"DefaultDuration"
#define MAIL_CALENDAR_PROFILE_EXCLUDEFROMALL_ITEM	"ExcludeFromAll"
#define MAIL_CALENDAR_PROFILE_EXCLUDEFROMSENT_ITEM	"ExcludeFromSent"
#define MAIL_CALENDAR_PROFILE_AUTOPROCESSLIST_ITEM			"AutoprocessUserList"
#define MAIL_CALENDAR_PROFILE_AUTOPROCESSTYPE_ITEM			"AutoprocessType"
#define MAIL_CALENDAR_PROFILE_AUTOPROCESSFORWARDTO_ITEM		"AutoprocessForwardTo"
#define MAIL_CALENDAR_PROFILE_AUTOPROCESSMTGS_ITEM			"AutoprocessMeetings"
#define MAIL_CALENDAR_PROFILE_V45AUTOPROCESSLIST_ITEM		"MeetingsPeople"
#define MAIL_CALENDAR_PROFILE_AUTOREMOVEFROMINBOX_ITEM		"AutoRemoveFromInbox"
#define MAIL_CALENDAR_PROFILE_ALARMSENABLED_ITEM				"EnableAlarms"
#define MAIL_CALENDAR_PROFILE_ALARMAPPTLEAD_ITEM				"AppointmentLead"
#define MAIL_CALENDAR_PROFILE_ALARMANNLEAD_ITEM				"AnniversaryLead"
#define MAIL_CALENDAR_PROFILE_ALARMEVENTLEAD_ITEM			"EventLead"
#define MAIL_CALENDAR_PROFILE_ALARMREMINDERLEAD_ITEM			"ReminderLead"
#define MAIL_CALENDAR_PROFILE_ALARMTASKLEAD_ITEM				"TaskLead"
#define MAIL_CALENDAR_PROFILE_ALARMAPPTENABLED_ITEM			"SetAlarmAppointment"
#define MAIL_CALENDAR_PROFILE_ALARMANNENABLED_ITEM			"SetAlarmAnniversary"
#define MAIL_CALENDAR_PROFILE_ALARMEVENTENABLED_ITEM			"SetAlarmEvent"
#define MAIL_CALENDAR_PROFILE_ALARMREMINDERENABLED_ITEM		"SetAlarmReminder"
#define MAIL_CALENDAR_PROFILE_ALARMTASKENABLED_ITEM			"SetAlarmTask"
#define MAIL_CALENDAR_PROFILE_CONFLICT_APPOINTMENT_ITEM		"ConflictMeeting"
#define MAIL_CALENDAR_PROFILE_CONFLICT_ANNIVERSARY_ITEM		"ConflictAnniversary"
#define MAIL_CALENDAR_PROFILE_CONFLICT_EVENT_ITEM			"ConflictEvent"
#define MAIL_CALENDAR_PROFILE_PREVENTREPLIESINBOX_ITEM		"PreventRepliesFromInbox"


/*	Mail delegation profile form related */

#define MAIL_DELEGATION_PROFILE_OWNER_ITEM			"Owner"				
#define MAIL_DELEGATION_ALLOWBUSYACCESS_ITEM		"AllowBusyAccess"

#define MAIL_UIDL_ITEM	"MailPop3UIDL"

/* Calendaring & Scheduling related item names */

#define MAIL_CS_KEEPPOSTED_ITEM 				"KeepPosted"		/* Determines if participant wants to be kept notified of updates */
#define MAIL_CS_KEEPPOSTED_ENABLED		'1'
#define MAIL_CS_SEQUENCENUM_ITEM 				"SequenceNum"		/* Sequence # of event notice */
#define MAIL_CS_NOTICETYPE_ITEM 				"NoticeType"		/* Type of notice being sent */
#define MAIL_CS_ASSIGNSTATE_ITEM 				"AssignState"		/* Used by tasks for communicating status */
#define MAIL_CS_CSVERSION_ITEM					"$CSVersion"		
#define MAIL_CS_APPOINTMENTTYPE_ITEM	"AppointmentType"
#define MAIL_CS_TASKTYPE_ITEM			"TaskType"
#define	MAIL_CS_CHAIR_ITEM				"Chair"
#define MAIL_CS_CHAIRDOMAIN_ITEM		"ChairDomain"
#define MAIL_CS_DELEGATOR_ITEM			"Delegator"
#define MAIL_CS_DELEGATETO_ITEM		"Delegee"
#define MAIL_CS_REQUIREDATTENDEES_ITEM	"RequiredAttendees"
#define MAIL_CS_OPTIONALATTENDEES_ITEM	"OptionalAttendees"
#define MAIL_CS_FYIATTENDEES_ITEM		"FYIAttendees"
#define MAIL_CS_REQUIREDASSIGNEES_ITEM "AssignedTo"
#define MAIL_CS_OPTIONALASSIGNEES_ITEM "OptionalAssignedTo"
#define MAIL_CS_FYIASSIGNEES_ITEM		"FYIAssignedTo"
#define MAIL_CS_ROOMTORESERVE_ITEM		"RoomToReserve"
#define MAIL_CS_ROOM_ITEM				"Room"
#define MAIL_CS_RESOURCESTORESERVE_ITEM	"Resources"
#define MAIL_CS_RESOURCES_ITEM			"RequiredResources"
#define MAIL_CS_BOOKFREETIME_ITEM		"BookFreeTime"
#define MAIL_CS_REMOVEDNAMES_ITEM		"Uninvited"
#define MAIL_CS_TOREMOVENAMES_ITEM		"tmpRemoveNames"
#define MAIL_CS_TMPOWNER_ITEM			"tmpOwner"
#define MAIL_CS_TOPIC_ITEM				"Topic"
#define MAIL_CS_DUESTATE_ITEM			"DueState"
#define MAIL_CS_RESOURCENAME_ITEM		"ResourceName"
#define MAIL_CS_STATUS_ITEM			"Status"
#define MAIL_CS_STARTDATE_ITEM			"StartDate"
#define MAIL_CS_STARTTIME_ITEM			"StartTime"
#define MAIL_CS_ENDDATE_ITEM			"EndDate"
#define MAIL_CS_ENDTIME_ITEM			"EndTime"
#define MAIL_CS_DUEDATETIME_ITEM		"DueDateTime"
#define MAIL_CS_APPTUNID_ITEM					"ApptUNID"
#define MAIL_CS_CALENDARDATETIME_ITEM			"CalendarDateTime"
#define MAIL_CS_TIMERANGE_ITEM					"TimeRange"
#define MAIL_CS_NEWDATE_ITEM					"NewDate"
#define MAIL_CS_NEWTIMERANGE_ITEM				"NewTimeRange"
#define MAIL_CS_NEWROOM_ITEM				"NewRoom"
#define MAIL_CS_NEWSTARTDATE_ITEM				"NewStartDate"
#define MAIL_CS_NEWSTARTTIME_ITEM				"NewStartTime"
#define MAIL_CS_NEWENDDATE_ITEM				"NewEndDate"
#define MAIL_CS_NEWENDTIME_ITEM				"NewEndTime"
#define MAIL_CS_BROADCAST_ITEM				"Broadcast"
#define MAIL_CS_DUEDATE_ITEM				"DueDate"
#define MAIL_CS_FLAGS_ITEM					"$CSFlags"
#define MAIL_CS_MAILINDB_ITEM				"MailInDatabaseList"
#define MAIL_CS_GROUP_REFRESHMODE_ITEM		"$GroupScheduleRefreshMode"
#define MAIL_CS_REFRESH_OPTIMAL				 '0'
#define MAIL_CS_REFRESH_FULL		 		 '1'
#define MAIL_CS_LEGEND_ENABLED_ITEM 	 	 "$GroupScheduleShowLegend"
#define MAIL_CS_LEGEND_DISABLED				 '0'
#define MAIL_CS_LEGEND_ENABLED				 '1'
#define MAIL_CS_COMPLETEDDATETIME_ITEM			"CompletedDateTime"
#define MAIL_CS_PREVENTREPLIES_ITEM				"$PreventReplies"
#define MAIL_CS_RESERVATION_PURPOSE_ITEM		"Purpose"
#define MAIL_CS_PREVDELEGEE_ITEM				"PrevDelegee"
#define MAIL_CS_PREVENTDELEGATION_ITEM			"PreventDelegate"
#define MAIL_CS_PREVENTCOUNTER_ITEM				"PreventCounter"
#define MAIL_CS_RESOURCEOWNER_ITEM				"ResourceOwner"


/* C&S Repeating Entry item names */

#define MAIL_CS_ORGREPEAT_ITEM					"OrgRepeat"
#define MAIL_CS_ORGTABLE_ITEM					"OrgTable"
#define MAIL_CS_REPEAT_DATES_ITEM				"RepeatDates"
#define MAIL_CS_REPEAT_INSTANCE_DATES_ITEM		"RepeatInstanceDates"
#define MAIL_CS_REPEAT_BASE_DATE_ITEM			"OriginalStartDate"
#define MAIL_CS_REPEAT_START_DATE_ITEM			"RepeatStartDate"
#define MAIL_CS_REPEAT_FOR_ITEM				"RepeatFor"
#define MAIL_CS_REPEAT_FORUNIT_ITEM			"RepeatForUnit"
#define MAIL_CS_REPEAT_UNIT_ITEM				"RepeatUnit"
#define MAIL_CS_REPEAT_ADJUST_ITEM				"RepeatAdjust"
#define MAIL_CS_REPEAT_UNTIL_ITEM				"RepeatUntil"
#define MAIL_CS_REPEAT_INTERVAL_ITEM			"RepeatInterval"
#define MAIL_CS_REPEAT_CUSTOM_ITEM				"RepeatCustom"
#define MAIL_CS_REPEAT_WEEKENDS_ITEM			"RepeatWeekends"
#define MAIL_CS_REPEAT_HOW_ITEM				"RepeatHow"
#define MAIL_CS_REPEAT_STARTFROMEND_ITEM		"RepeatFromEnd"
#define MAIL_CS_REPEAT_IDS_ITEM		"RepeatIds"
#define MAIL_CS_REPEAT_LOOKUP_ITEM				"$RepeatLookup"
#define MAIL_CS_REPEAT_CHANGEWHICH_ITEM			"RescheduleWhich"
#define MAIL_CS_REPEAT_ORIGINALENDDATE_ITEM		"OriginalEndDate"
#define MAIL_CS_REPEAT_PARENTREPEATDATES_ITEM	"ParentRepeatDates"
#define MAIL_CS_REPEAT_PARENTREPEATINSTANCEDATES_ITEM	"ParentRepeatInstanceDates"
#define MAIL_CS_REPEAT_INSTANCE_LOOKUP_ITEM		"$RepeatInstanceLookup"
#define MAIL_CS_REPEAT_CACHEINSTANCE_ITEM		"$RepeatCacheInstanceDate"
#define MAIL_CS_REPEAT_CONFLICTDATES_ITEM		"tmpRepeatConflictDates"


/* C&S Alarm item names */

#define MAIL_CS_ALARMENABLED_ITEM				"$Alarm"
#define MAIL_CS_ALARMSOUND_ITEM				"$AlarmSound"
#define MAIL_CS_ALARMDESCRIPTION_ITEM			"$AlarmDescription"
#define MAIL_CS_ALARMSENDTO_ITEM				"$AlarmSendTo"
#define MAIL_CS_ALARMOFFSET_ITEM				"$AlarmOffset"
#define MAIL_CS_ALARMTIME_ITEM					"$AlarmTime"
#define MAIL_CS_ALARMDISABLED_ITEM				"$AlarmDisabled"
#define MAIL_CS_ALARMOFFSETUNIT_ITEM			"$AlarmUnit"
#define MAIL_CS_ALARMMAILOPTIONS_ITEM			"$AlarmMemoOptions"


/* POP3 view names */
#define MAIL_POP3_UIDL_VIEW	"($POP3UIDL)"
#define POP3_VIEW	"($POP3)"

/* Mail form names */

#define MAIL_MEMO_FORM "Memo"					/* Standard memo */
#define MAIL_REPLY_FORM "Reply"					/* Standard memo reply */
#define MAIL_REPLY_WITH_HISTORY_FORM "Reply With History"	/* Standard reply w/history memo */
#define MAIL_PHONEMESSAGE_FORM "Phone Message"	/* Phone message */
#define MAIL_DELIVERYREPORT_FORM "Delivery Report" /* Delivery report form name */
#define MAIL_NONDELIVERYREPORT_FORM "NonDelivery Report" /* Non-Delivery report form name */
#define MAIL_RETURNRECEIPT_FORM "Return Receipt" /* Return Receipt form name */
#define MAIL_DATABASEENTRY_FORM "Database Entry" /* mailin database entry form for libraries */
#define MAIL_TRACEREPORT_FORM "Trace Report"	 /* Trace report form name */
#define MAIL_CALENDAR_PROFILE_FORM "CalendarProfile"	/* Calendar profile form name */
#define MAIL_DELEGATION_PROFILE_FORM "DelegationProfile" /* Delegation profile form name */
#define MAIL_APPOINTMENT_FORM "Appointment"		/* C & S Appointment form name */
#define MAIL_NOTICE_FORM "Notice"				/* C & S Meeting Notice form name */
#define MAIL_RESOURCE_RESERVATION_FORM "Reservation" /* C & S Resource reservation form name */
#define MAIL_RESOURCE_PROFILE_FORM "Resource"	/* C & S Calendar resource profile form name */
#define MAIL_TASK_FORM				"Task"		/* C & S Task form name */
#define MAIL_REPEAT_CACHE_FORM		"RepeatCache"	/* C&S Repeat Cache profile note name */
#define MAIL_TASK_NOTICE_FORM		"TaskNotice"	/* C&S Task notice workflow form */

/* Address Book - "Person" form item names */

#define MAIL_PERSON_FORM "Person"				/* Form and type name */
#define MAIL_FORMTYPE_ITEM "Type"				/* Form type */
#define MAIL_FULLNAME_ITEM 	"FullName"			/* Full name  */
#define MAIL_FIRSTNAME_ITEM "FirstName"			/* First name */
#define MAIL_LASTNAME_ITEM 	"LastName"			/* Last name */
#define MAIL_MIDDLEINITIAL_ITEM "MiddleInitial"	/* Middle initial */
#define MAIL_SHORTNAME_ITEM "ShortName"			/* Short name (for mail gateways) */
#define MAIL_INTERNETADDRESS_ITEM "InternetAddress"		/* InternetAddress */
#define MAIL_OWNER_ITEM 	"Owner"				/* Entry owner name */
#define MAIL_MAILSYSTEM_ITEM "MailSystem"		/* Mail system item (keyword field: 1,2,3,4) */
#define MAIL_MAILSERVER_ITEM "MailServer"		/* Mail server name */
#define MAIL_MAILFILE_ITEM 	"MailFile"			/* Mail file name */
#define MAIL_MAILDOMAIN_ITEM "MailDomain"		/* Mail domain name */
#define MAIL_MAILADDRESS_ITEM "MailAddress"		/* Mail auto-forwarding address */
#define MAIL_PUBLICKEY_ITEM "PublicKey"			/* Public encryption key */
#define MAIL_CERTIFICATE_ITEM "Certificate"		/* Public encryption key */
#define MAIL_USERCERTIFICATE_ITEM "UserCertificate"		/* X.509 Public encryption key */
#define MAIL_LOCATION_ITEM "Location"			/* Location field */
#define MAIL_COMMENT_ITEM "Comment"				/* Comment field */
#define MAIL_USERID_ATTACHMENT "UserID"			/* User ID attachment file name */
#define MAIL_SERVERID_ATTACHMENT "ServerID"		/* Server ID attachment file name */
#define MAIL_CALENDARDOMAIN_ITEM "CalendarDomain" /* User's calendar domain override */
#define MAIL_NETUSERNAME_ITEM "NetUserName"		 /* Network Acct Name (for dir synching) */
#define MAIL_HTTPPASSWORD_ITEM "HTTPPassword"	 /* http password */
#define MAIL_HASHVERSION_ITEM	"$SecurePassword"	/* Flag that indicates NoteUpdate should hash HTTPPassword field */
#define MAIL_STORAGE_ITEM	"MessageStorage"		/* Specifies how user wants to store the mail.  See IMSG_PREFERENCE_XXX */
#define MAIL_OFFICEPHONE_ITEM "OfficePhoneNumber"   /* Office phone number */
#define MAIL_COMPANYNAME_ITEM "CompanyName"         /* Company name */
#define MAIL_COUNTRY_ITEM "Country"                 /* Country */
#define MAIL_DEPARTMENT_ITEM "Department"           /* Department */

#define MAIL_ALTFULLNAME_ITEM				"AltFullName"					/* Alternate FullName */
#define MAIL_ALTFULLNAMELANGUAGE_ITEM		"AltFullNameLanguage"			/* Language Tag. */
#define MAIL_PROPALTCOMMONNAME_ITEM 		"ProposedAltCommonName"			/* Proposed Alternate CommonName */
#define MAIL_PROPALTORGUNIT_ITEM 			"ProposedAltOrgUnit" 			/* Proposed Alternate OrgUnit */
#define MAIL_PROPALTFULLNAMELANGUAGE_ITEM	"ProposedAltFullNameLanguage"	/* Proposed Language Tag. */

/* Address Book - Mail-in "Database" form item names.  Uses Person form
	fields: FullName, MailServer, MailFile, and MailDomain" */

#define MAIL_MAILINDATABASE_FORM "Database"		/* Form and type name */
#define MAIL_DESCRIPTION_ITEM 	"Description"	/* Mail-in db description item */
#define MAIL_HAIKU_ITEM			"$QuickPlace"	/* QuickPlace mail database */

/* MAPI specific items */

#define MAIL_MAPI_MSGFLAGS_ITEM "$MapiMessageFlags" /* MAPI IMessage PR_MESSAGE_FLAGS Property */
#define MAIL_MAPI_MSGCLASS_ITEM "$MapiMessageClass" /* MAPI IMessage PR_MESSAGE_CLASS Property */
#define MAIL_MAPI_STATUS_ITEM "$MapiStatus" 		/* MAPI PR_MSG_STATUS, PR_STATUS Properties */
#define MAIL_MAPI_ACCESS_ITEM "$MapiAccess" 		/* MAPI PR_ACCESS, PR_ACCESS_LEVEL Properties */
#define MAIL_MAPI_TO_ADDRTYPE_ITEM "$MapiSendToAddrType"/* MAPI Recip PR_ADDRTYPE Property for To List */
#define MAIL_MAPI_CC_ADDRTYPE_ITEM "$MapiSendCcAddrType"/* MAPI Recip PR_ADDRTYPE Property for Cc List*/
#define MAIL_MAPI_BCC_ADDRTYPE_ITEM "$MapiSendBccAddrType"/* MAPI Recip PR_ADDRTYPE Property for Bcc List*/
#define MAIL_MAPI_TO_RESP_ITEM "$MapiSendToResponsibility"/* MAPI Recip PR_RESPONSIBILITY Property for To List */
#define MAIL_MAPI_CC_RESP_ITEM "$MapiSendCcResponsibility"/* MAPI Recip PR_RESPONSIBILITY Property for Cc List */
#define MAIL_MAPI_BCC_RESP_ITEM "$MapiSendBccResponsibility"/* MAPI Recip PR_RESPONSIBILITY Property for Bcc List */
#define MAIL_MAPI_TO_EID_ITEM "$MapiSendToEID"		/* MAPI Recip PR_ENTRYID Property for To List */
#define MAIL_MAPI_CC_EID_ITEM "$MapiSendCcEID"		/* MAPI Recip PR_ENTRYID Property for Cc List */
#define MAIL_MAPI_BCC_EID_ITEM "$MapiSendBccEID"	/* MAPI Recip PR_ENTRYID Property for Bcc List */
#define MAIL_MAPI_TO_OT_ITEM "$MapiSendToObjType"	/* MAPI Recip PR_OBJECT_TYPE Property for To List */
#define MAIL_MAPI_CC_OT_ITEM "$MapiSendCcObjType"	/* MAPI Recip PR_OBJECT_TYPE Property for Cc List */
#define MAIL_MAPI_BCC_OT_ITEM "$MapiSendBccObjType" /* MAPI Recip PR_OBJECT_TYPE Property for Bcc List */
#define MAIL_MAPI_TO_ADDR_ITEM "$MapiSendToAddr" 	/* MAPI Recip PR_EMAIL_ADDRESS Property for To List */
#define MAIL_MAPI_CC_ADDR_ITEM "$MapiSendCcAddr" 	/* MAPI Recip PR_EMAIL_ADDRESS Property for Cc List */
#define MAIL_MAPI_BCC_ADDR_ITEM "$MapiSendBccAddr" 	/* MAPI Recip PR_EMAIL_ADDRESS Property for Bcc List */
#define MAIL_MAPI_SENDER_EID_ITEM "$MapiSenderEID"	/* MAPI Sender PR_ENTRYID Property */
#define MAIL_MAPI_SENDER_ADDRTYPE_ITEM "$MapiSenderAddrType"   /* MAPI Sender PR_ADDRTYPE Property */
#define MAIL_MAPI_SENDER_ADDR_ITEM "$MapiSenderAddr"/* MAPI Sender PR_EMAIL_ADDR Property */
#define MAIL_MAPI_SENDER_SEARCHKEY_ITEM "$MapiSenderSearchKey" /* MAPI Sender PR_SEARCH_KEY Property */
#define MAIL_MAPI_SENDER_NAME_ITEM "$MapiSenderName"/* MAPI Sender PR_DISPLAY_NAME Property */


/*	Summary item names used to store NNTP information. */

#define NNTP_MESSAGE_ID_ITEM_NAME		"$UName"
#define NNTP_FROM_ITEM_NAME				"$8"
#define	NNTP_SUBJECT_ITEM_NAME			"$9"
#define NNTP_DATE_ITEM_NAME				"$10"
#define NNTP_REFERENCES_ITEM_NAME		"$11"
#define NNTP_PATH_ITEM_NAME				"Path"
#define NNTP_DISTRIBUTIONS_ITEM_NAME	"Distribution"
#define NNTP_SIZE_ITEM_NAME				"NNTP_Size"
#define NNTP_LINES_ITEM_NAME			"Lines"
#define NNTP_ISLMBCS_ITEM_NAME			"$18"

/*	NNTP Client item names */

#define NNTPCL_OUTGOING_ITEM			"Outgoing"
#define NNTPCL_NEWSREADER_ITEM			"$Newsreader"

/*	Client Type  */

#define FIELD_CLIENTTYPE "ClientType"			/* Client Type - Full or Limited Notes */

/*	Standard Subform Item Name.	*/

#define SUBFORM_ITEM_NAME "$SubForms"

/*	Define field name common to Server, Person, and Certifier forms */

#define KFM_ITEM_CHANGE_REQUEST	"ChangeRequest"	

/*	Certifier and Cross-certificate Address Book lookup definitions */


#define	KFM_FORM_CERTIFIER			"Certifier"
#define	KFM_FORM_CROSSCERTIFICATE	"CrossCertificate"

#define KFM_ITEM_NAMECOMBO		"NameCombo"
#define KFM_ITEM_ORGCOMBO		"OrgCombo"
#define KFM_ITEM_ISSUEDTO		"IssuedTo"
#define KFM_ITEM_ISSUEDBY		"IssuedBy"
#define KFM_ITEM_CERTIFICATE	"Certificate"
#define KFM_ITEM_USER_CERTIFICATE	"UserCertificate"
												/* Some additional items are */
												/* the same as those defined */
												/* for the "Person" form */

#define KFM_ITEM_CERT_NOENC		"Certificate_NoEnc"	/* Public encryption key */
													/* to be used for signature */
													/* checking only and not for */
													/* sending encrypted mail */

#define KFM_ITEM_PUBLICKEY	 "PublicKey"		/* Public encryption key 	*/
												/* for flat names.			*/

#define CERTIFIERNAMESSPACE         "$Certifiers"
#define LOCAL_CERTIFIERNAMESSPACE   "1\\$Certifiers"
#define CERTIFIERSNAMESSPACE		"$Certifiers"
#define CROSSCERTBYROOTNAMESSPACE	"$CrossCertByRoot"
#define CROSSCERTBYNAMENAMESSPACE	"$CrossCertByName"

#define	KFM_CROSSCERT_ITEM_ISSUEDTO		0
#define	KFM_CROSSCERT_ITEM_ISSUEDBY		1
#define	KFM_CROSSCERT_ITEM_CERTIFICATE	2
#define	KFM_CROSSCERT_ITEM_CERT_NOENC	3
#define KFM_CROSSCERT_ITEM_NOTEID		4
#define	KFM_CROSSCERT_LOOKUPITEMCOUNT	5
#define	KFM_CROSSCERT_LOOKUPITEMS "IssuedTo\0IssuedBy\0Certificate\0Certificate_NoEnc\0$$NoteID"

#define	KFM_CERTIFIER_ITEM_ISSUEDTO		0
#define	KFM_CERTIFIER_ITEM_ISSUEDBY		1
#define	KFM_CERTIFIER_ITEM_CERTIFICATE	2
#define	KFM_CERTIFIER_ITEM_CERT_NOENC	3
#define	KFM_CERTIFIER_LOOKUPITEMCOUNT	4
#define	KFM_CERTIFIER_LOOKUPITEMS "IssuedTo\0IssuedBy\0Certificate\0Certificate_NoEnc"

/*	Names for Wired In Cross Certificates
 */
#define NOTES_TEMPLATE_DEVELOPER_ID "CN=Lotus Notes Template Development/O=Lotus Notes"
#define NOTES_COMPANION_ID "O=Lotus Notes Companion Products"
#define NOTES_WHOSAYS_ID "Notes"


/*	Lookup items for Network Authentication check.
*/
#define	NETAUTH_ITEM_CERTIFICATE	0
#define	NETAUTH_ITEM_CERT_NOENC		1
#define	NETAUTH_ITEM_PUBLIC_KEY		2
#define	NETAUTH_ITEM_CHANGEREQUEST	3
#define	NETAUTH_ITEM_USERCERTIFICATE 4
#define	NETAUTH_LOOKUPITEMCOUNT		5
#define NETAUTH_LOOKUPITEMS			"Certificate\0Certificate_NoEnc\0PublicKey\0ChangeRequest\0UserCertificate"

#define NETAUTH_NAMESPACE_USERS			"($Users)"
#define	NETAUTH_NAMESPACE_SERVERS		"($Servers)"
#define	NETAUTH_NAMESPACE_CERTIFIERS	"($Certifiers)"
#define NETAUTH_NAMESPACE_XCERTBYROOT	"($CrossCertByRoot)"

/*  Lookup items for KFMGetPublicKey
*
*	NOTE: Code knows that the last view may not be present (in the case
*	of a Personal N&A book), so $Servers must be last and the code must
*	be changed if any others become optional.
*/

#define KFM_GETPUB_VIEWS		"($Users)\0($Certifiers)\0($Servers)"
#define KFM_GETPUB_NUMVIEWS		3
#define KFM_GETPUB_FIELDS		"Certificate\0Certificate_NoEnc\0PublicKey\0UserCertificate"
#define KFM_GETPUB_NUMFIELDS	4

#define FILE_ID_VIEW			"$FileIdentifications"

/*  Lookup items for Profiles */

#define PROFILENAMESSPACE	"$Profiles"
#define PROFILENAME     "ProfileName"
#define PROFILES_ITEM "Profiles"

/* dblink fields in the Setup Profile note */
#define PROFILE_DATABASELINK_ITEM	"DatabaseLinks"
#define PROFILE_REPLICALINK_ITEM	"ReplicaLinks"
#define PROFILE_LNABLINK_ITEM		"LNABLinks"

/* Address Book - "Server" form item names */

#define MAIL_SERVER_FORM "Server"				/* Form and type name */
#define MAIL_SERVERNAME_ITEM "ServerName"		/* Server name */
#define MAIL_DOMAINNAME_ITEM "Domain"			/* Domain server is in */
#define MAIL_NETWORKNAME_ITEM "Network"			/* Network server is on */
#define MAIL_ADMINNAME_ITEM "Administrator" 	/* Server's administrator(s) */
#define MAIL_SERVERTITLE_ITEM "ServerTitle"		/* Server title */
#define MAIL_SERVERPORTS_ITEM "Ports"			/* Enabled ports in server record */
#define MAIL_SMTPLISTENER_ITEM "SMTPListenerEnabled" /* Does this server run an SMTP listener? */
#define MAIL_FULLHOSTNAME_ITEM "SMTPFullHostDomain"	/*	Host name of the server */
#define MAIL_NETADDRESSES_ITEM "NetAddresses"	/* Network Addresses */

/* Address Book - "X400Server" form item names */

#define MAIL_X400_SERVER_FORM "Server"				/* Form and type name */
#define MAIL_X400_SERVERNAME_ITEM "X400ServerName"		/* X400 MTA server name */
#define MAIL_X400_MTANAME_ITEM "X400MTAName"			/* X400 MTA name */
#define MAIL_X400_GLOBAL_DOMAIN_ITEM "X400GlobalDomain" /* Global domain identifier */ 
#define MAIL_X400_COUNTRY_ITEM "X400Country"			/* Country name */
#define MAIL_X400_ADMD_ITEM "X400ADMD"					/* Administration Management Domain name*/
#define MAIL_X400_PRMD_ITEM "X400Domain"				/* Private Domain name */
#define MAIL_X400_CREDENTIALS_ITEM "X400Credentials"	/* MTA credentials */
#define MAIL_X400_SUPP_APP_CONTEXTS_ITEM "X400SupportedApplicationContexts"	/* Supported app. contexts */
#define MAIL_X400_DEL_CONTENT_LENGTH_ITEM "X400DeliverContentLength"	/* Delivery content length */
#define MAIL_X400_DEL_CONTENT_TYPE_ITEM "X400DeliverContentTypes"	 	/* Delivery content types */
#define MAIL_X400_PSEL_ITEM "X400PSEL"					/* Presentation selector */
#define MAIL_X400_SSEL_ITEM "X400SSEL"					/* Session selector */
#define MAIL_X400_TSEL_ITEM "X400TSEL"					/* Transport selector */
#define MAIL_X400_IPADDRESS_ITEM "X400IPAddress" 		/* Network IP address for the MTA */
#define MAIL_X400_X121ADDRESS_ITEM "X400X121Address" 	/* X.121 Network address for the MTA */

/* Address Book - "Domain" form item names */

#define MAIL_DOMAIN_FORM "Domain"							/* Form and type name */
#define MAIL_DOMAINTYPE_ITEM "DomainType"					/* Domain type */
#define MAIL_DOMAINADJDOMAINNAME_ITEM "AdjacentDomainName" 	/* Adjacent domain name */
#define MAIL_DOMAINDOMAINNAME_ITEM "DomainName"				/* Domain name */
#define MAIL_DOMAINNEXTDOMAIN_ITEM "NextDomain"				/* Next domain to domain */
#define MAIL_DOMAINMAILSERVER_ITEM "MailServer"				/* Server containing mailbox */
#define MAIL_DOMAINMAILFILE_ITEM "MailFile"					/* File name of mailbox */
#define	MAIL_DOMAINALLOW_ITEM "AllowFromDomains"			/* Allow list */
#define	MAIL_DOMAINDENY_ITEM "DenyFromDomains"				/* Deny list */
#define MAIL_DOMAINCALENDARSERVER_ITEM "CalendarServer"		/* Calendar gateway server */
#define MAIL_DOMAINCALENDARSYSTEM_ITEM "CalendarSystem"		/* Calendar gateway system */

/* Address Book - "Connection" form item names */

#define MAIL_LOCAL_CONNECTION_FORM "Local"		/* Local Connection form name */
#define MAIL_REMOTE_CONNECTION_FORM "Remote"	/* Remote Connection form name */
#define MAIL_CONNECTION_TYPE "Connection"		/* Connection entry type */
#define MAIL_CONNECTION_TYPE_ITEM "ConnectionType" /* Connection type item */
#define MAIL_SOURCE_ITEM "Source"				/* Source computer name */
#define MAIL_SOURCEDOMAIN_ITEM "SourceDomain"	/* Source domain name */
#define MAIL_DESTINATION_ITEM "Destination"		/* Destination computer name */
#define MAIL_DESTINATIONDOMAIN_ITEM "DestinationDomain"	/* Destination domain name */
#define MAIL_PORTNAME_ITEM "PortName"			/* Port name */
#define MAIL_PHONENUMBER_ITEM "PhoneNumber" 	/* Phone number */
#define MAIL_COUNTRYCODE_ITEM "Country"		 	/* Phone number */
#define MAIL_AREACODE_ITEM "AreaCode"		 	/* Phone number */
#define MAIL_ENABLED_ITEM "Enabled"				/* Enabled/disabled item */
#define MAIL_TASKS_ITEM "Tasks"					/* Tasks item */
#define MAIL_INTERVAL_ITEM "Interval"			/* Interval item */
#define MAIL_SCHEDULE_ITEM "Schedule"			/* Schedule item */
#define MAIL_COST_ITEM "Cost"					/* Routing cost item */
#define MAIL_REPLICATION_TYPE_ITEM "RepType"	/* Replication type, e.g. pull/pull */
#define MAIL_LINKINFO_ITEM "LinkInfo"			/* For X.25 conn recs */
#define MAIL_PASSTHRUSERVER_ITEM "PassthruServer" /* For passthru conn recs */

/* Address Book - "Group" form item names */

#define MAIL_GROUP_FORM "Group"					/* Form and type name */
#define MAIL_GROUP_TYPE "GroupType"					/* Form and type name */
#define MAIL_LISTNAME_ITEM "ListName"			/* Distribution list name */
#define MAIL_LISTDESCRIPTION_ITEM "ListDescription"	/* Distribution list name */
#define MAIL_MEMBERS_ITEM "Members"				/* Members names name */
#define MAIL_LISTADMINISTRATOR_ITEM "Administrator" /* Group administrator */

/* Address Book - "External Domain Network Information" form item names */

#define MAIL_EXTERNAL_DOMAIN_NETWORK_INFORMATION_FORM "ExternalDomainNetworkInformation"	/* Form and type name */

/* Address Book - "User Setup Profile" form item names */

#define PROFILE_FORM "Profile"				/* Form and type name */

/* Address Book - "Holiday" form item names */

#define HOLIDAY_FORM "Holiday"				/* Form and type name */

/* Address Book - "(Alternate Language Personal Information)" form item names */

#define LDAP_ALT_LANGUAGE_PERSONAL_INFO_FORM "AltLanguagePersonalInfo" /* Form and type name */

/* Address Book - "(FileProtection)" form item names */

#define FILE_PROTECTION_FORM "FileProtection" /* Form and type name */

/* Address Book - "(Mapping)" form item names */

#define MAPPING_FORM "Mapping" /* Form and type name */

/* Address Book - "(Virtual Server)" form item names */

#define VIRTUAL_SERVER_FORM "VirtualServer" /* Form and type name */

/* Address Book - "Users" name space, items, and names */
/* Address Book - local $Users namespace */
#define LOCAL_USERNAMESSPACE "1\\$Users"
#define USERNAMESSPACE "$Users"
#define USERNAMESSPACE_ALT "($Users)"

#define MAIL_NAMELOOKUPITEMCOUNT 14
#define MAIL_NAMELOOKUPSIMPLEITEMCOUNT 10		/* Excludes PublicKey */
#define MAIL_LOCALNAMELOOKUPSIMPLEITEMCOUNT 11 	/* Includes LNAB Entry */
#define MAIL_LOCALNAMELOOKUPITEMCOUNT 16		/* Includes LNAB fields */
#define MAIL_NAMELOOKUPITEMS "FullName\0MailDomain\0MailAddress\0Location\0ListName\0Members\0InternetAddress\0AltFullName\0MessageStorage\0AltFullNameLanguage\0$$LNAB\0PublicKey\0Certificate\0UserCertificate\0$$LNABHasCertificates\0$$LNABHasUserCertificates"
#define FULLNAMEITEM	0
#define DOMAINNAMEITEM	1
#define MAILADDRESSITEM	2
#define LOCATIONITEM	3
#define LISTNAMEITEM	4
#define MEMBERSITEM		5
#define INTERNETADDRESSITEM	6
#define	ALTFULLNAMEITEM 7
#define STORAGETYPEITEM	8
#define ALTFULLNAMELANGUAGEITEM	9
#define LNABENTRY	10
#define PUBLICKEYITEM	11
#define CERTIFICATEITEM	12
#define USERCERTIFICATEITEM	13
#define HASCERTIFICATEITEM	14
#define HASUSERCERTIFICATEITEM	15

/* Lightweight Address book definitions */
#define LNAB_ENTRY_Y					'Y'
#define LNAB_ENTRY_YES					"Y"
#define LNAB_ENTRY_NO					"N"
#define LNAB_ENTRY_ITEM					"$$LNAB"
#define LNAB_HASCERTIFICATES_ITEM		"$$LNABHasCertificates"
#define LNAB_HASUSERCERTIFICATES_ITEM 	"$$LNABHasUserCertificates"
#define FIELD_JIT_ITEM					"$$JIT"
#define FIELD_JITFAILED_ITEM			"$$JITFailed"


#define MAIL_DELIVERYLOOKUPITEMCOUNT 11
#define MAIL_DELIVERYSIMPLEITEMCOUNT 6			/* Excludes PublicKey */
#define MAIL_DELIVERYLOOKUPITEMS "FullName\0MailAddress\0MailServer\0MailFile\0ShortName\0ListName\0PublicKey\0EncryptIncomingMail\0MailDomain\0Certificate\0UserCertificate"
#define MAIL_DELIVERYFULLNAMEITEM	 0
#define MAIL_DELIVERYMAILADDRESSITEM 1
#define MAIL_DELIVERYMAILSERVERITEM	 2
#define MAIL_DELIVERYMAILFILEITEM	 3
#define MAIL_DELIVERYSHORTNAMEITEM	 4
#define MAIL_DELIVERYLISTNAMEITEM	 5
#define MAIL_DELIVERYPUBLICINFO		 6
#define MAIL_DELIVERYENCRYPTINCOMING 7
#define MAIL_DELIVERYMAILDOMAINITEM	 8
#define MAIL_DELIVERYCERTIFICATEITEM 9
#define MAIL_DELIVERYUSERCERTIFICATEITEM 10


/* Address Book - "Domains" name space, items, and names */

#define DOMAINNAMESSPACE "$Domains"
#define ALIASDOMAINNAMESSPACE "($Domains)"

#define MAIL_DOMAINLOOKUPITEMCOUNT 4
#define MAIL_DOMAINLOOKUPITEMS "DomainName\0NextDomain\0MailServer\0MailFile"
#define MAIL_DOMAINNAMEITEM 0
#define MAIL_DOMAINNEXTDOMAINITEM 1
#define MAIL_DOMAINMAILSERVERITEM 2
#define MAIL_DOMAINMAILFILEITEM 3
#define MAIL_DEFAULTGLOBALDOMAIN_ITEM "DefaultGlobalDomain"
#define MAIL_SMTPDOMAINSUFFIXES_ITEM "SMTPDomainSuffixes"
#define MAIL_GLOBALDOMAIN_ITEM "GlobalDomain"
#define MAIL_SMTPADDRESSFORMAT_ITEM "SMTP822Format"
#define MAIL_SMTPNOTESDOMAININCLUDED_ITEM "SMTPNotesDomainIncluded"
#define MAIL_SMTPNOTESDOMAINSEPCHAR_ITEM "SMTPNotesDomainSepChar"
#define MAIL_SMTPNOTESDOMAINPOS_ITEM "SMTPNotesDomainPos"
#define MAIL_SMTPADDRLOOKUP_ITEM "SMTPAddrLookup"
#define MAIL_SMTPLOCALPART_ITEM  "SMTPLocalPart"
#define MAIL_SMTPADDRFORMAT_ADDRONLY	'1'
#define MAIL_SMTPADDRFORMAT_NAMEANDADDR	'2'
#define MAIL_SMTPLOCALPART_FULL 		'0'
#define MAIL_SMTPLOCALDOMAINSINCLUDED_99 "99"
#define MAIL_SMTPLOCALDOMAINSINCLUDED_1 "1"
#define MAIL_SMTPLOCALDOMAINSINCLUDED_0 "0"
#define MAIL_SMTPLOCALPART_CN 			'1'
#define MAIL_SMTPLOCALPART_SHORTNAME 	'2'
#define MAIL_SMTPLOCALDOMAINPOS_LEFT 	'1'
#define MAIL_SMTPLOCALDOMAINPOS_RIGHT 	'2'
#define MAIL_SMTPLOCALDOMAINSEPCHAR 	'%'
#define MAIL_SMTPLOCALDOMAINS_NONE		0
#define MAIL_SMTPLOCALDOMAINS_ONE		1
#define MAIL_SMTPLOCALDOMAINS_ALL		127
#define MAIL_SMTPADDRLOOKUP_DISABLED	'0'
#define MAIL_SMTPADDRLOOKUP_ENABLED		'1'

#define SMTPMTA_SUBFORM		"$SMTPServerFormSubForm"  /* Used by setup */

/* Address Book - "Servers" name space, items, and names */

#define SERVERNAMESSPACE "$Servers"
#define SERVERNAMESSPACE_1 "1\\$Servers"

#define MAIL_SERVERLOOKUPITEMCOUNT 3
#define MAIL_SERVERLOOKUPITEMS "ServerName\0Domain\0Network"
#define MAIL_SERVERNAMEITEM 0
#define MAIL_SERVERDOMAINITEM 1
#define MAIL_SERVERNETWORKITEM 2

#define SERVERLOOKUPITEMS "EDFilenames\0Enabled\0Interval\0Schedule\0Weekdays\0CatalogEnabled\0CatalogInterval\0CatalogSchedule\0CatalogWeekdays"
#define LNAB_SERVERLOOKUP_ITEMCOUNT 9
#define LNAB_SERVERFILENAMES	0
#define LNAB_ENABLED			1
#define LNAB_INTERVAL			2
#define LNAB_SCHEDULE			3
#define LNAB_WEEKDAYS			4
#define DOMAIN_INDEXER_ENABLED	5
#define DOMAIN_INDEXER_INTERVAL	6
#define DOMAIN_INDEXER_SCHEDULE	7
#define DOMAIN_INDEXER_WEEKDAYS	8


/* Address Book - "$People" name space, items, and names */

#define MAIL_PEOPLENAMESPACE "$People"

#define MAIL_PEOPLELOOKUPITEMCOUNT 1
#define MAIL_PEOPLELOOKUPITEMS "FullName"
#define MAIL_PEOPLEFULLNAMEITEM 0

/* Address Book - "$Groups" name space, items, and names */

#define MAIL_GROUPSNAMESPACE "$Groups"
#define MAIL_GROUPSNAMESPACE_1 "1\\$Groups"

#define REGISTER_GROUPSNAMESPACE "($RegisterGroups)"


/* Group type definitions */
#define GROUP_TYPE_MULTIPURPOSE '0'
#define GROUP_TYPE_MAILONLY '1'
#define GROUP_TYPE_ACCESSCONTROL '2' 
#define GROUP_TYPE_DENYLIST '3'

#define MAIL_GROUPSLOOKUPITEMCOUNT 1
#define MAIL_GROUPSLOOKUPITEMS "ListName"
#define MAIL_GROUPSGROUPNAMEITEM 0

/* Address Book - "$NameFieldLookup" name space, items, and names (Typeahead) */
#define LOCAL_MAIL_NAMEFIELD_LOOKUP "1\\$NamesFieldLookup"
#define MAIL_NAMEFIELD_LOOKUP	"$NamesFieldLookup"
#define TYPEAHEAD_STATUS_ITEM "TypeaheadStatus"
#define DISABLE_TYPEAHEAD	"DISABLE_TYPEAHEAD"

/* Address Book - Name field composite lookup */

#define MAIL_NAMEFIELD_COMPOSITE_NAMESSPACE	"$Users\0$Groups\0$ServersLookup"
#define NAMEFIELDCOMPOSITENAMESPACES 3

/* Address Book - Server lookup */

#define MAIL_SERVERSLOOKUP_NAMESSPACE	"$ServersLookup"



/*  Address Book - public views displayed by the admin subprogram */

#define ADMIN_GROUPS_VIEW 			"Groups"
#define ADMIN_PEOPLE_VIEW 			"People"
#define ADMIN_SERVERS_VIEW			"Servers"
#define ADMIN_CONFIGURATIONS_VIEW 	"Configurations"
#define ADMIN_WEBCONFIGURATIONS_VIEW "WebConfigurations"
#define ADMIN_CONNECTIONS_VIEW 		"Connections"
#define ADMIN_PROGRAMS_VIEW 		"Programs"
#define ADMIN_DOMAINS_VIEW 			"Domains"
#define ADMIN_CLUSTERS_VIEW   		"Clusters"
#define ADMIN_CERTIFICATES_VIEW		"Certificates"
#define ADMIN_LICENSES_VIEW   		"Licenses"
#define ADMIN_HOLIDAYS_VIEW   		"Holidays"
#define HIDDEN_HOLIDAYS_VIEW   		"($Holidays)"
#define ADMIN_EXT_DOMAIN_NET_INFO_VIEW "ExternalDomainNetworkInformation"

/*	Address Book - Items and names used by Admin Panel */

#define ADMIN_SERVERTYPEITEM			0
#define ADMIN_SERVERNAMEITEM			1
#define ADMIN_SERVERTITLEITEM			2
#define ADMIN_SERVERDOMAINITEM			3
#define ADMIN_SERVERNETWORKITEM			4
#define ADMIN_SERVERCLUSTERNAMEITEM		5
#define ADMIN_SERVERADMINISTRATORITEM	6
#define ADMIN_SERVERVERSIONITEM			7
#define ADMIN_SERVEROSITEM				8
#define ADMIN_SERVERLOOKUPITEMCOUNT		9
#define ADMIN_SERVERLOOKUPITEMS "Type\0ServerName\0ServerTitle\0Domain\0Network\0ClusterName\0Administrator\0ServerBuildNumber\0ServerPlatform"

/* Databases opened and displayed by the admin subprogram */

#define ADMIN_LOG_FILE				"log.nsf"
#define ADMIN_CATALOG5_FILE			"catalog.nsf"
#define ADMIN_CATALOG_FILE			"catalog.nsf"
#define ADMIN_EVENTS_FILE			"statrep.nsf"
#define ADMIN_EVENT4_CONFIG_FILE	"events4.nsf"
#define ADMIN_EVENT4_SAV_FILE		"events4.sav"  /* In R5, we save off the users EVENTS4.NSF as EVENTS4.SAV */
#define ADMIN_EVENT_CONFIG_FILE		"events4.nsf"
#define ADMIN_CERT_LOG_FILE			"certlog.nsf"
#define ADMIN_WEB_LOG_FILE			"domlog.nsf"
#define ADMIN_WEBCONFIG_FILE		"domcfg.nsf"
#define ADMIN_CERT_CA_FILE			"certca.nsf"
#define ADMIN_CERT_SRV_FILE			"certsrv.nsf"
#define ADMIN_REPORTS				"reports.nsf"
#define ADMIN_DECS_CFG				"decsadm.nsf"

#define ADMIN_REPORT_FORM			"faReport"

/* SMTP MTA files */
#define ADMIN_SMTP_BOX				"smtp.box"
#define ADMIN_SMTP_IQ				"smtpibwq.box"
#define ADMIN_SMTP_OQ				"smtpobwq.box"

/* cc:Mail MTA files */
#define ADMIN_CCMTA_BOX				"ccmail.box"
#define ADMIN_CCMTA_WQ				"ccmcwq.box"

/* X.400 MTA files */
#define ADMIN_X400_BOX				"x400.box"
#define ADMIN_X400_DEAD				"dead.box"
#define ADMIN_X400_LOG				"x400log.nsf"
#define ADMIN_X400_MADMAN			"madman.nsf"
	
/* Softswitch files */
#define ADMIN_SSW					"ssw.nsf"

/* Defense Messaging System files */
#define ADMIN_DMS_BOX				"dms.box"
#define ADMIN_DMS_HOLD				"dmshold.box"

/* MTA Config dbs */
#define ADMIN_MTA_CFG				"mtatbls.nsf"  /* MTA configuration tables, used by smtp, ccmail and x400 mta */
#define ADMIN_MTA_FORMS				"mtaforms.nsf" /* MTA forms, also used by all mta's */

/* View in MAB used by admin */
#define ADMIN_DA_VIEW				"Directory Assistance"

/* View in events5 displayed by the monitor subprogram */

#define ADMIN_STATSEL_VIEW			"($StatSelection)"
#define ADMIN_STATNAME_ITEM			"StatName"
#define ADMIN_STATISTIC_VIEW		"($Statistics)"
#define ADMIN_NUMBER_TYPE			"Number"

/*	Database containing UNAME database directory */

#define	UNAME_FILE					"unames.nsf"
	
/*  Address Book - "ServerAccess" namespace, items, and names */

#define ACCESS_GROUPS_NAMESPACE		"$ServerAccess"
#define ACCESS_GROUPS_NAMESPACE_1	"1\\$ServerAccess"

#define MAIL_GROUPS_NAMESPACE		"$MailGroups"
#define MAIL_GROUPS_NAMESPACE_1		"1\\$MailGroups"

#define ACCESS_ITEM_LISTNAME				0
#define ACCESS_ITEM_DBINDEX					1
#define ACCESS_ITEM_DOMAINTYPE				2
#define ACCESS_GROUPEXP_LOOKUPITEMCOUNT		3
#define ACCESS_LISTNAME_ITEM				"ListName"
#define ACCESS_GROUPEXP_LOOKUPITEMS			"ListName\0$$DBIndex\0$$DomainType"


/*  Address Book - $Users name space, to look up server access */

#define ACCESS_ITEM_COUNT	1
#define ACCESS_LOOKUP_ITEMS	"FullName"
#define ACCESS_ITEM_FULLNAME	0

/*  Address Book -- $Adminp name space, for admin proxy agent */
#define ADMINP_NAMESPACE "$Adminp"

/*  Address Book configuration parameters for the administration process */
#define ADMINP_CONFIG_MAX_THREADS	"AdminPMaxThreads" /* number */
#define ADMINP_CONFIG_INTERVAL	 	"AdminPInterval"   /* number */
#define ADMINP_CONFIG_DAILY_TIME	"AdminPDailyTime"  /* time   */
#define ADMINP_CONFIG_WEEK_DAYS		"AdminPWeekDays"   /* text list */
#define ADMINP_CONFIG_DELAYED_TIME  "AdminPDelayedTime"/* time */
#define ADMINP_CONFIG_DEL_MAIL_FILE "AdminPMailFileDelInt" /* number */
#define ADMINP_CONFIG_SUSPEND_RANGE "AdminPSuspendRange" /* timedate range */
#define ADMINP_CONFIG_SAVE_NRESP	"AdminPLogSetting"
#define ADMINP_CONFIG_NAME_CHANGE_X	"AdminPNameChangeExpiration"

#define ADMINP_LOCAL_ADMIN			"LocalAdmin"
#define ADMINP_ALLOW_ACCESS			"AllowAccess"
#define ADMINP_DENY_ACCESS			"DenyAccess"
#define ADMINP_CREATE_ACCESS		"CreateAccess"
#define ADMINP_REPLICA_ACCESS		"ReplicaAccess"
#define ADMINP_PT_ACCESS			"PTAccess"
#define ADMINP_PT_CLIENTS			"PTClients"
#define ADMINP_PT_CALLERS			"PTCallers"
#define ADMINP_PT_TARGETS			"PTTargets"
#define ADMINP_LIST_OWNER			"ListOwner"
#define ADMINP_PASSTHRU_SERVER		"PassthruServer"
#define ADMINP_SMPT_ADMINISTRATOR	"SMPTAdministrator"
#define ADMINP_GROUP_TYPE			"GroupType"
#define ADMINP_PRIVATE_LIST     	"PrivateList"
#define ADMINP_RESTRICTED_LIST		"RestrictedList"
#define ADMINP_UNRESTRICTED_LIST	"UnrestrictedList"
#define ADMINP_SERVERS_CPU_COUNT	"ServerCPUCount"
#define ADMINP_X509_CERT_PRESENT	"$X509CertIsPresent"

#define ADMINP_STATS_CPU_COUNT		"CPU.Count"
#define ADMINP_SERVER_PLATFORM		"ServerPlatform"

#define ADMINP_PROFILE_NOTEID "%NoteID"
#define ADMINP_PROFILE_SIGNATURE_ITEM "$Sig_Signature"
#define ADMINP_XDOMAIN_TRUSTED_ADMINS_ITEM "CrossDomainTrustedAdmins"

/* values for resource database */
#define ADMINP_RESOURCE_DOCUMENT	"Resource"
#define ADMINP_RESOURCE_NAME_ITEM	"ResourceName"
#define ADMINP_PROGRAM_FORM			"Program"

/* known values of fields in the proxy database document form */
#define AdminpDelete 							"0"
#define AdminpRenameInTheACL					"1"
#define AdminpCopyPublicKey 					"2"
#define AdminpStoreServerVersion				"3"
#define AdminpRenameServerInNAB 				"4"
#define AdminpRenameUserInNAB 					"5"
#define AdminpMoveUserInHier 					"6"
#define AdminpDeleteStats						"7"
#define AdminpInitiateNABChange					"8"
#define AdminpRecertServerInNAB					"9"
#define AdminpRecertUserInNAB					"10"
#define AdminpServerClusterAdd					"11"
#define AdminpServerClusterRemove				"12"
#define AdminpCreateReplicas					"13"
#define AdminpMoveReplicas						"14"
#define AdminpPendedDeleteForMove				"15"
#define AdminpDeleteInPersonDocs				"16"
#define AdminpDeleteInTheACL					"17"
#define AdminpDeleteInReadersAuthors			"18"
#define AdminpRenameInPersonDocs				"19"
#define AdminpRenameInReadersAuthors			"20"
#define AdminpDeleteMailFile					"21"
#define AdminpApproveMailFileInfo				"22"
#define AdminpDeleteUnlinkedMailFile			"23"
#define AdminpCreateMailFile					"24"
#define AdminpMonitorMovedReplica				"25"
#define AdminpDeleteChangeRequests				"26"
#define AdminpGetMailFileInfo					"27"
#define AdminpRequestDeleteMailFile				"28"
#define AdminpResourceAdd						"29"
#define AdminpResourceDelete					"30"
#define AdminpApproveResourceDelete				"31"
#define AdminpCreateReplicasCheckAccess			"32"
#define AdminpMoveReplicasCheckAccess			"33"
#define AdminpSetPasswordFields					"34"
#define AdminpUpdateUserPW						"35"
#define AdminpUpdateServerPW					"36"
#define AdminpSetMABField						"37"
#define AdminpRenamePersonInFreeTime			"38"
#define AdminpRenamePersonInMailFile			"39"
#define AdminpRenameGroupInNAB					"40"
#define AdminpRenameGroupInPersonDocs			"41"
#define AdminpRenameGroupInTheACL				"42"
#define AdminpRenameGroupInReadersAuthors		"43"
#define AdminpAddPersonsX509Certificate			"44"
#define AdminpCheckMailServersAccess			"45"
#define AdminpUpgradeUser						"46"
#define AdminpCopyExternalDomainAddresses		"47"	
#define AdminpPromoteMailServersAccess			"48"
#define AdminpCreateNewMailFileReplica			"49"
#define AdminpAddNewMailFileFields				"50"
#define AdminpMonitorNewMailFileFields			"51"
#define AdminpReplaceMailFileFields				"52"
#define AdminpLastPushToNewMailServer			"53"
#define AdminpDeletePersonInNAB					"54"
#define AdminpDeleteServerInNAB      			"55"
#define AdminpDeleteGroupInNAB      			"56"
#define AdminpDelegateMailFile      			"57"
#define AdminpApproveDeletePersonInNAB      	"58"
#define AdminpApproveDeleteServerInNAB      	"59"
#define AdminpApproveRenamePersonInNAB      	"60"
#define AdminpApproveRenameServerInNAB      	"61"
#define AdminpResourceModify					"62"
#define AdminpUpdateNetworkTables				"63"
#define AdminpCreateISPYMailInDb				"64"
#define AdminpNCMoveReplicasCheckAccess			"65"
#define AdminpNCMoveReplicas					"66"
#define AdminpStoreServerCPUCount				"67"
#define AdminpRenamePersonInUnreadList			"68"
#define AdminpDeleteReplicaAfterMove			"69"
#define AdminpSetDNSFullHostName				"70"
#define AdminpStoreServerPlatform				"71"
#define AdminpApproveDeleteDesignElements		"72"
#define AdminpRequestDeleteDesignElements		"73"
#define AdminpDeleteDesignElements				"74"
#define AdminpApproveDeleteMovedReplica			"75"
#define AdminpRequestDeleteMovedReplica			"76"
#define AdminpSetDomainCatalog					"77"
#define AdminpWebDelegateMailFile				"78"
							
#define AdminpDeleteWord 			 			0
#define AdminpRenameInTheACLWord 	 			1
#define AdminpCopyPublicKeyWord 	 			2
#define AdminpStoreServerVersionWord 			3
#define AdminpRenameServerInNABWord  			4
#define AdminpRenameUserInNABWord	 			5
#define AdminpMoveUserInHierWord 	 			6
#define AdminpDeleteStatsWord		 			7
#define AdminpInitiateNABChangeWord	 			8
#define AdminpRecertServerInNABWord	 			9
#define AdminpRecertUserInNABWord	 			10
#define AdminpServerClusterAddWord				11
#define AdminpServerClusterRemoveWord			12
#define AdminpCreateReplicasWord				13
#define AdminpMoveReplicasWord					14
#define AdminpPendedDeleteForMoveWord			15
#define AdminpDeleteInPersonDocsWord			16
#define AdminpDeleteInTheACLWord				17
#define AdminpDeleteInReadersAuthorsWord		18
#define AdminpRenameInPersonDocsWord			19
#define AdminpRenameInReadersAuthorsWord		20
#define AdminpDeleteMailFileWord				21
#define AdminpApproveMailFileInfoWord			22
#define AdminpDeleteUnlinkedMailFileWord		23
#define AdminpCreateMailFileWord				24
#define AdminpMonitorMovedReplicaWord			25
#define AdminpDeleteChangeRequestsWord			26
#define AdminpGetMailFileInfoWord				27
#define AdminpRequestDeleteMailFileWord			28
#define AdminpResourceAddWord					29
#define AdminpResourceDeleteWord				30
#define AdminpApproveResourceDeleteWord			31
#define AdminpCreateReplicasCheckAccessWord		32
#define AdminpMoveReplicasCheckAccessWord		33
#define AdminpSetPasswordFieldsWord				34
#define AdminpUpdateUserPWWord					35
#define AdminpUpdateServerPWWord				36
#define AdminpSetMABFieldWord					37
#define AdminpRenamePersonInFreeTimeWord		38
#define AdminpRenamePersonInMailFileWord 		39
#define AdminpRenameGroupInNABWord	 			40
#define AdminpRenameGroupInPersonDocsWord		41
#define AdminpRenameGroupInTheACLWord			42
#define AdminpRenameGroupInReadersAuthorsWord	43
#define AdminpAddPersonsX509CertificateWord		44

#define AdminpNewAdminpRequestFormat 			45

#define AdminpCheckMailServersAccessWord 		45
#define AdminpUpgradeUserWord			 		46
#define AdminpCopyExternalDomainAddressesWord	47
#define AdminpPromoteMailServersAccessWord		48
#define AdminpCreateNewMailFileReplicaWord		49
#define AdminpAddNewMailFileFieldsWord			50
#define AdminpMonitorNewMailFileFieldsWord		51
#define AdminpReplaceMailFileFieldsWord			52
#define AdminpLastPushToNewMailServerWord		53
#define AdminpDeletePersonInNABWord				54
#define AdminpDeleteServerInNABWord				55
#define AdminpDeleteGroupInNABWord				56
#define AdminpDelegateMailFileWord      		57
#define AdminpApproveDeletePersonInNABWord      58
#define AdminpApproveDeleteServerInNABWord      59
#define AdminpApproveRenamePersonInNABWord      60
#define AdminpApproveRenameServerInNABWord      61
#define AdminpResourceModifyWord				62
#define AdminpUpdateNetworkTablesWord			63
#define AdminpCreateISPYMailInDbWord			64
#define AdminpNCMoveReplicasCheckAccessWord		65
#define AdminpNCMoveReplicasWord				66
#define AdminpStoreServerCPUCountWord			67
#define AdminpRenamePersonInUnreadListWord		68
#define AdminpDeleteReplicaAfterMoveWord		69
#define AdminpSetDNSFullHostNameWord			70
#define AdminpStoreServerPlatformWord			71
#define AdminpApproveDeleteDesignElementsWord	72
#define AdminpRequestDeleteDesignElementsWord	73
#define AdminpDeleteDesignElementsWord			74
#define AdminpApproveDeleteMovedReplicaWord		75
#define AdminpRequestDeleteMovedReplicaWord		76
#define AdminpSetDomainCatalogWord				77
#define AdminpWebDelegateMailFileWord			78
	
#define ADMINP 									"Adminp"
#define ADMINP_ALL_SERVERS						"*"
#define ADMINP_DELETE_MAIL_FILE_ON_HOME_SERVER  "1"
#define ADMINP_DELETE_MAIL_FILE_REPLICAS		"2"
#define ADMINP_DELETE_ONE_MAIL_FILE_REPLICA		"3"
#define ADMINP_DISABLED							"0"
#define ADMINP_ENABLED							"1"

/* the view we use from the proxy database */
#define ADMINP_MAIN_VIEW 						"All Requests by Action"
#define ADMINP_RESPONSES_VIEW					"($LoggedEvents)"
#define ADMINP_REQUESTS_VIEW					"($Requests)"
#define ADMINP_RENAME_IN_ACL_DELETE_VIEW		"($RenameInACLAndDeleteRequests)"
#define ADMINP_RECEIVED_REQUESTS_VIEW			"($ReceivedRequests)"
#define ADMINP_RECEIVE_CONFIG_VIEW				"($ReceiveCrossDomainRequests)"
#define ADMINP_SUBMIT_CONFIG_VIEW	   			"($SubmitCrossDomainRequests)"

/* fields in the proxy database document form */

#define ADMINP_PROXY_DOCUMENT 					"AdminRequest"
#define ADMINP_PROXY_XDOMAIN_DOCUMENT 			"CrossDomainAdminRequest"
#define ADMINP_DOC_SERVER_ITEM					"ProxyServer"
#define ADMINP_ACTION_ITEM						"ProxyAction"
#define ADMINP_DOC_SERVER_BUILD_NUMBER_ITEM		"ProxyServerBuildNumber"
#define ADMINP_DOC_SOURCE_SERVER_ITEM			"ProxySourceServer"
#define ADMINP_DOC_DEST_SERVER_ITEM				"ProxyDestinationServer"
#define ADMINP_DOC_CLUSTER_NAME_ITEM			"ProxyClusterName"
#define ADMINP_NAME_LIST_ITEM 					"ProxyNameList"
#define ADMINP_DOC_AUTHOR_ITEM 	  				"ProxyAuthor"
#define ADMINP_DOC_PROCESS_ITEM					"ProxyProcess"
#define ADMINP_DOC_TARGET_CERTIFIER_ITEM		"ProxyTargetCertifier"
#define ADMINP_DOC_CERTIFICATE_ITEM 			"ProxyCertificate"
#define ADMINP_DOC_CHANGE_REQUEST_ITEM			"ProxyChangeRequest"
#define ADMINP_DOC_CHANGE_SIGNATURE_ITEM		"ProxyChangeSignature"
#define ADMINP_DOC_REPLICA_ID_ITEM				"ProxyReplicaId"
#define ADMINP_DOC_DATABASE_PATH_ITEM			"ProxyDatabasePath"
#define ADMINP_DOC_DATABASE_SOURCE_PATH_ITEM	"ProxyDatabaseSourcePath"
#define ADMINP_DATABASE_DESTINATION_PATH_ITEM	"ProxyDestinationDatabasePath"
#define ADMINP_DOC_DATABASE_NAME_ITEM			"ProxyDatabaseName"
#define ADMINP_DOC_COMMENTS_ITEM				"ProxyRequestComments"
#define ADMINP_DOC_DELETE_MAIL_FILE_ITEM		"ProxyDeleteMailfile"
#define ADMINP_DOC_HOME_SERVER_ITEM				"ProxyHomeServer"
#define ADMINP_DOC_EXECUTION_TIME_ITEM			"ProxyExecutionTime"
#define ADMINP_DOC_MAIL_SERVER_ITEM				"ProxySourceServer"
#define ADMINP_DOC_DATABASE_ACL_ITEM			"ProxyDatabaseACL"
#define ADMINP_DOC_DATABASE_CLASS_ITEM			"ProxyDatabaseTemplateName"
#define ADMINP_DOC_RESOURCE_SITE_ITEM			"ProxyResourceSite"
#define ADMINP_DOC_RESOURCE_TYPE_ITEM			"ProxyResourceType"
#define ADMINP_DOC_RESOURCE_CAPACITY_ITEM		"ProxyResourceCapacity"
#define ADMINP_DOC_RESOURCE_DESCRIPTION_ITEM	"ProxyResourceDescription"
#define ADMINP_DOC_RESOURCE_DOMAIN_ITEM			"ProxyResourceDomain"
#define ADMINP_DOC_PASS_CHECK_PASSWORD_ITEM		"ProxyPasswordCheck"
#define ADMINP_DOC_PASS_GRACE_PERIOD_ITEM		"ProxyPasswordGracePeriod"
#define ADMINP_DOC_PASS_CHANGE_INTERVAL_ITEM	"ProxyPasswordChangeInterval"
#define ADMINP_DOC_APPROVAL_FLAG_ITEM			"ApprovalFlag"
#define ADMINP_DOC_IMMEDIATE_FLAG_ITEM			"ProxyImmediateFlag"
#define ADMINP_NEW_GROUP_NAME_ITEM 				"ProxyNewGroupName"
#define ADMINP_DOC_PERSONS_CERT_ITEM 			"ProxyUserCertificate"
#define ADMINP_NAME_IN_X509_CERT_ITEM			"ProxyNameInX509Certificate"
#define ADMINP_DOC_DISPLAY_DESIGN_ELEMENTS_ITEM	"ProxyDesignElementList"
#define ADMINP_DOC_PRIVATE_DESIGN_ELEMENTS_ITEM	"$ProxyPrivateDesignElements"
#define ADMINP_DOC_DELETED_OBJECT_ITEM			"$ProxyDeletedObject"
#define ADMINP_DOC_MOVE_MAIL_DELETE_ITEM		"$ProxyMoveMailDelete"
#define ADMINP_DOC_ACL_FLAG_ITEM				"ACLFlag"

/* fields in the proxy database log form */
#define ADMINP_PROXY_LOG 						"AdminLog"
#define ADMINP_LOG_ACTION_REQUESTOR_ITEM 		"ProxyActionRequestor"
#define ADMINP_LOG_SERVER_NAME_ITEM 			"ProxyServerName"	
#define ADMINP_LOG_ACTION_START_TIME_ITEM 		"ActionStartTime"
#define ADMINP_LOG_ACTION_END_TIME_ITEM			"ActionEndTime"
#define ADMINP_LOG_DB_LIST_ITEM					"ProxyDbList"
#define ADMINP_LOG_STATUS_ITEM					"ProxyStatus"
#define ADMINP_LOG_MODIFIED_RESPONSE_ITEM		"ModifiedFlag"
#define ADMINP_LOG_SHOW_MODIFIED_ITEM			"ShowModified"
#define ADMINP_LOG_OLD_NAME_ITEM				"OldName"
#define ADMINP_LOG_NEW_NAME_ITEM				"NewName"
#define ADMINP_LOG_ACTION_COMMENTS_ITEM			"ActionComments"
#define ADMINP_LOG_SHOW_ERROR					"ErrorFlag"
#define ADMINP_LOG_REPLICA_CREATION_TIME		"ReplicaCreationTime"
#define ADMINP_LOG_CREATED_DELETE_REQUEST		"DeleteRequestCreated"
#define ADMINP_LOG_SIGNED_NOTES					"ProxySignedDocs"
#define ADMINP_LOG_IN_PROGRESS					"AdminPInProgress"
#define ADMINP_LOG_SENT_TO_DOMAINS				"ProxySentToDomains"
#define ADMINP_LOG_ADD_IN_NAME					"ProxyAddInProcess"
#define ADMINP_LOG_ADD_IN_SIGNER				"ProxyAddInSigner"
#define ADMINP_LOG_PRIVATE_AGENTS				"ProxyPrivateAgents"
#define ADMINP_LOG_PRIVATE_FOLDERS				"ProxyPrivateFolders"
#define ADMINP_LOG_PRIVATE_VIEWS				"ProxyPrivateViews"
#define ADMINP_LOG_SHARED_AGENTS				"ProxySharedAgents"
#define ADMINP_LOG_ERROR_DBS					"$AdminpErrorDbs"
#define ADMINP_LOG_NO_ERROR_DBS					"$AdminpNoErrorDbs"

/* fields in the proxy database profiles */

#define ADMINP_PROFILE_TO_DOMAINS				"ToDomains"
#define ADMINP_PROFILE_FROM_DOMAINS				"FromDomains"
#define ADMINP_PROFILE_INBOUND_REP_SERVERS		"InboundReplicaServers"
#define ADMINP_PROFILE_OUTBOUND_REP_SERVERS		"OutboundReplicaServers"
#define ADMINP_PROFILE_OUTBOUND_REP_DOMAINS		"OutboundReplicaDomains"
#define ADMINP_INBOUND_APPROVED_SIGNERS			"InboundApprovedSigners"
#define ADMINP_OUTBOUND_APPROVED_SIGNERS		"OutboundApprovedSigners"

#define ADMINP_MAIL_FILE_TITLE_ITEM ADMINP_DOC_DATABASE_NAME_ITEM

/* generic admin4.nsf fields */
#define ADMINP_PROXY_TEXT_ITEM_1				"ProxyTextItem1"
#define ADMINP_PROXY_TEXT_ITEM_2				"ProxyTextItem2"
#define ADMINP_PROXY_TEXT_ITEM_3				"ProxyTextItem3"
#define ADMINP_PROXY_TEXT_ITEM_4				"ProxyTextItem4"
#define ADMINP_PROXY_TEXT_ITEM_5				"ProxyTextItem5"
#define ADMINP_PROXY_TEXT_ITEM_6				"ProxyTextItem6"
#define ADMINP_PROXY_TEXT_ITEM_7				"ProxyTextItem7"
#define ADMINP_PROXY_TEXT_ITEM_8				"ProxyTextItem8"
#define ADMINP_PROXY_TEXT_ITEM_9				"ProxyTextItem9"
#define ADMINP_PROXY_TEXT_ITEM_10				"ProxyTextItem10"

#define ADMINP_PROXY_DATE_ITEM_1				"ProxyDateItem1"
#define ADMINP_PROXY_DATE_ITEM_2				"ProxyDateItem2"
#define ADMINP_PROXY_DATE_ITEM_3				"ProxyDateItem3"

#define ADMINP_PROXY_NUM_ITEM_1					"ProxyNumItem1"
#define ADMINP_PROXY_NUM_ITEM_2					"ProxyNumItem2"

#define ADMINP_PROXY_CREATE_FT_INDEX			"ProxyCreateFullTextIndex"
#define ADMINP_PROXY_MAILFILE_ACCESS			"ProxyMailfileAccessLevel"

/* name and address book fields and field values adminp needs */ 
#define ADMINP_NAB_SERVER_BUILD_NUMBER 			"ServerBuildNumber"
#define ADMINP_NAB_DENY_ACCESS_GROUP 			"3"

#define ADMINP_NAB_PASS_CHECK_PASSWORD			"CheckPassword"
#define ADMINP_NAB_PASS_GRACE_PERIOD			"PasswordGracePeriod"
#define ADMINP_NAB_PASS_CHANGE_INTERVAL			"PasswordChangeInterval"

#define ADMINP_NAB_MASTER_ADDRESS_BOOK			"MasterAddressBook"

#define ADMINP_SERVER_CONNECTION_FORM			"Server\\Connection"
#define ADMINP_NETWORK_CONNECTION_FORM			"Network Connection"
#define ADMINP_REMOTE_CONNECTION_X25_FORM		"Remote Connection (X25)"
#define ADMINP_REMOTE_CONNECTION_ISDN_FORM		"Remote Connection (ISDN)"

/* address book stuff for resources used by adminp */
#define ADMINP_NAB_RESOURCE_FLAG_ITEM	"ResourceFlag"
#define ADMINP_NAB_DOCUMENT_ACCESS_ITEM "DocumentAccess"
#define ADMINP_NAB_RESOURCE_CAPACITY_ITEM	"ResourceCapacity"
#define ADMINP_NAB_RESOURCE_TYPE_ITEM	"ResourceType"
#define ADMINP_NAB_RESOURCE_DOMAIN_ITEM	"MailDomain"

#define RESOURCES_NAMESPACE 		"$Resources"
#define RESOURCES_VIEW		 		"($Resources)"
#define ROOMS_NAMESPACE				"$Rooms"
#define ROOMS_VIEW					"($Rooms)"
#define ROOMS_PICKLIST_COLUMN	  	1
#define RESOURCES_PICKLIST_COLUMN 	2

#define ADMINP_FLAG_SET				"1"
#define ADMINP_DOCUMENT_ACCESS_SET  "[NetModifier]"
#define ADMINP_ROOM					"1" 
#define ADMINP_RESOURCE				"2" 

/* address book stuff for move mail file */
#define ADMINP_NEW_MAILFILE_ITEM		"NewMailFile"
#define ADMINP_NEW_MAILSERVER_ITEM		"NewMailServer"
#define ADMINP_OLD_MAILFILE_ITEM		"OldMailFile"
#define ADMINP_OLD_MAILSERVER_ITEM		"OldMailServer"
#define ADMINP_NEW_MAIL_CLIENT_UPDATE_ITEM	"NewMailClientUpdateFlag"

/*	Address Book - local $Programs namespace */
#define LOCAL_PROGRAMS_NAMESPACE "1\\$Programs"
#define PROGRAMSNAMESPACE "$Programs"

/*	Address Book - local $Locations namespace */
#define LOCAL_LOCATIONS_NAMESPACE "1\\$Locations"
#define LOCATIONSNAMESPACE "$Locations"

/*	Address Book - local $Connections namespace */
#define LOCAL_CONNECTIONS_NAMESPACE "1\\$Connections"
#define CONNECTIONSNAMESPACE "$Connections"


/*	Address Book - "Connections" namespace */


#define SOURCE_WILDCARD "*"

#define NAME_CONNECTIONLOOKUPITEMCOUNT	9
#define NAME_CONNECTIONLOOKUPITEMS "Source\0SourceDomain\0Destination\0DestinationDomain\0PortName\0Tasks\0Enabled\0Cost\0ConnectionType"
#define NAME_CONNECTIONSRCITEM	0
#define NAME_CONNECTIONSRCDOMAINITEM 1
#define NAME_CONNECTIONDSTITEM	2
#define NAME_CONNECTIONDSTDOMAINITEM 3
#define NAME_CONNECTIONPORTITEM	4
#define NAME_CONNECTIONTASKSITEM 5
#define NAME_CONNECTIONENABLEDITEM 6
#define NAME_CONNECTIONCOSTITEM 7
#define NAME_CONNECTIONTYPEITEM 8

#define DIALNAMELOOKUPITEMCOUNT	5
#define DIALNAMELOOKUPITEMS "Destination\0PhoneNumber\0PortName\0LinkInfo\0LinkScriptInfo\0CreditCardPrefix\0CreditCardSuffix"
#define DESTINATIONNAMEITEM		0
#define PHONENUMBERITEM			1
#define	PORTNAMEITEM			2
#define	LINKINFOITEM			3
#define	LINKSCRIPTITEM			4
#define CARDPREFIXITEM			5
#define CARDSUFFIXITEM			6

#define PT_NAMELOOKUPITEMCOUNT	3	/*	For Passthru */
#define PT_NAMELOOKUPITEMS "Destination\0PassthruServer\0Source"
#define PT_NAMEITEM_DST			0
#define PT_NAMEITEM_VIA			1
#define PT_NAMEITEM_SRC			2

/*	Address Book - "Connections" Application field values */

#define ROUTER_APPNAME	"Mail Routing"		/* Router application name */
#define PULL_ROUTER_APPNAME	"Pull Routing"	/* Pull Routing application name */
#define X400_APPNAME	"X400 Mail Routing"	/* X.400 MTA application name */
#define CCMAIL_APPNAME	"ccMail Routing"	/* ccMail MTA application name */
#define SMTP_APPNAME	"SMTP Mail Routing"	/* SMTP MTA application name */
#define REPL_APPNAME 	"Replication"		/* Replicator application name */
#define RUNPGM_APPLNAME	"Run Program"		/* Run program application name */
#define WKSREP_APPNAME	"WksRep"			/* Workstation Rep/Briefcase application name */
#define WKSREPHI_APPNAME "WksRepHI"			/* High-priority Rep/Briefcase application name */
#define CLREPL_APPNAME	"Cluster Replication" /* Cluster Replicator application name */
#define NNTP_APPNAME	"NNTP Feed"			/* NNTP Feed application name */
#define DIRCAT_APPNAME	"Directory Cataloger"	/* DIrectory Catalog Aggregator */
#define DOMAIN_INDEXER_APPNAME	"Domain Indexer"	/* Domain Indexer */

/* Connection record items not defined above */

#define CONNREC_USAGE_PRIORITY_ITEM "ConnectionRecordFirst" /* "Normal" use connection record first */
#define CONNREC_LOCATION			"ConnectionLocation" /* only for locations */
#define CONNREC_OPTIONAL_NET_ADDRESS_ITEM "OptionalNetworkAddress" /* Optional network address field */
#define CONNREC_REMOTE_DTE_ADDRESS_ITEM "RemoteDTEAddress" /* DTE address for X.25 */
#define CONNREC_FCODE1_ITEM "fcode_1" /* X.25 facility code */
#define CONNREC_FCODE2_ITEM "fcode_2" /* X.25 facility code */
#define CONNREC_FCODE3_ITEM "fcode_3" /* X.25 facility code */
#define CONNREC_FCODE4_ITEM "fcode_4" /* X.25 facility code */
#define CONNREC_FVAL1_ITEM "fval_1" /* X.25 facility code value */
#define CONNREC_FVAL2_ITEM "fval_2" /* X.25 facility code value */
#define CONNREC_FVAL3_ITEM "fval_3" /* X.25 facility code value */
#define CONNREC_FVAL4_ITEM "fval_4" /* X.25 facility code value */
#define CONNREC_SCRIPTNAME_ITEM "ScriptName" /* Login script filename */
#define CONNREC_LINKSCRIPT_INFO_ITEM "LinkScriptInfo" /* Login script information */
#define CONNREC_SCRIPTARG1_ITEM "ScriptArg1" /* Login script argument */
#define CONNREC_SCRIPTARG2_ITEM "ScriptArg2" /* Login script argument */
#define CONNREC_SCRIPTARG3_ITEM "ScriptArg3" /* Login script argument */
#define CONNREC_SCRIPTARG4_ITEM "ScriptArg4" /* Login script argument */
#define CONNREC_WEEKDAYS_ITEM "WeekDays" /* Call schedule WeekDays item */
#define CONNREC_REP_PRIORITY_ITEM "RepPriority" /* Replication priority item */
#define CONNREC_REP_TYPE_ITEM "RepType" /* Replication type item */
#define CONNREC_REP_FILELIST_ITEM "Filenames" /* Replication filename list item */
#define CONNREC_REP_TIME_LIMIT_ITEM "TimeLimit" /* Replication time limit item */
#define CONNREC_NNTP_TYPE_ITEM "NNTPFeedType" 			/* NNTP Feed type item */
#define CONNREC_NNTP_AUTH_ITEM "NNTPAuthentication" 	/* NNTP Authentication item */
#define CONNREC_NNTP_ENCRYPT_ITEM "NNTPChannelEncrypt" 	/* NNTP channel encrypt item */
#define CONNREC_NNTP_CREATE_DBS_ITEM "NNTPCreateUsenetDBs" /* NNTP create db's item */
#define CONNREC_NNTP_NEWSGROUP_SUBDIR_ITEM "NNTPNewsgroupSubDir" /* NNTP newsgroup subdirectory item */
#define CONNREC_NNTP_NEWSGROUPS_ITEM "NNTPNewsgroups" 	/* NNTP newsgroups item */
#define CONNREC_NNTP_SITES_ITEM "NNTPSites" 			/* NNTP sites item */
#define CONNREC_NNTP_TIMELIMIT_ITEM "NNTPTimeLimit" 	/* NNTP Feed time limit item */
#define CONNREC_NNTP_USER_ITEM "NNTPUserName"			/* NNTP user name for feed */
#define CONNREC_NNTP_PASSWD_ITEM "NNTPPassword"			/* NNTP password for feed */
#define CONNREC_DIALUP_SERVER_NAME_ITEM "DialViaName"	/* Dial Up Server name item */
#define CONNREC_CONNECTION_MODE_ITEM	"ConnectionMode"  /* Direct or Dial-Up connection mode */
#define CONNREC_ROUTING_TYPE_ITEM		"RouterType"
#define CONNREC_ROUTING_SMTPPULL_ITEM	"SMTPPullRouting"	/* will be enabled if SMTP Push/Pull or Pull Only */
#define CONNREC_PULL_TIMEOUT_ITEM		"PullRoutingTimeout"	/* Time to wait for an acknowledgement of the pull request */
#define CONNREC_PULL_THIS_SERVER		"PullThisServer"	/* Include this server in pull request */
#define CONNREC_PULL_ALL_PRIMARY 		"PullAllPrimary"	/* Include all primary internet domains in pull request */
#define CONNREC_PULL_ALL_ALTERNATE 		"PullAllAlternates"	/* Include all alternate internet domains in pull request */
#define CONNREC_PULL_CHOOSE_SPECIFIC	"PullChooseSpecific"	/* Include list specified in PullSpecificList in pull request */
#define CONNREC_PULL_SPECIFIC_LIST		"PullSpecificList"	/* Include list of domains in pull request */


/* Connection record Mail Routing types */

#define CONNRECMAILTYPE_PUSHWAIT 0
#define CONNRECMAILTYPE_PULLPUSH 1
#define CONNRECMAILTYPE_PULL 2
#define CONNRECMAILTYPE_PUSH 3

/* Connection record types */

#define CONNRECTYPE_NETWORK '0'
#define CONNRECTYPE_REMOTE '1'
#define CONNRECTYPE_PASSTHRU '2'
#define CONNRECTYPE_REMOTE_LAN_SERVICE '5'
#define CONNRECTYPE_X25 '6'
#define CONNRECTYPE_ISDN '7'
#define CONNRECTYPE_HUNT_GROUP '9'
#define CONNRECTYPE_NNTP 'a'

/* Network connection record item names */

#define CONNREC_TYPE 		"ConnectionType"
#define CONNREC_SOURCE 		"Source"
#define CONNREC_DESTINATION "Destination"
#define CONNREC_PORT 		"PortName"
#define CONNREC_LANPORT		"LanPortName"
#define CONNREC_ADDRESS 	"OptionalNetworkAddress"
#define CONNREC_COMMENTS 	"Comments"
#define CONNREC_ENABLED 	"Enabled"

#define CONNREC_RLAN_SERVICE "RemoteLanService"
#define CONNREC_RLAN_DRIVERS "DisplayDriverList"
#define CONNREC_RLAN_STATIC	"StaticTag"
#define CONNREC_RLAN_ITEMS	"RLANItems"
#define	CONNREC_RLAN_NAME	"RLANTag"
#define CONNREC_RLAN_LOGIN	"RLAN1"
#define CONNREC_RLAN_PASSWORD	"RLAN2"
#define CONNREC_RLAN_NUMBER	"RLAN3"

#define CONNREC_RLAN_SERVICE_RAS_TEXT	"RAS"
#define CONNREC_RLAN_SERVICE_ARA_TEXT	"ARA"

/* Connection record precedence */
#define	CONNRECFIRST	'1'
#define	CONNRECLOW	'0'

/*  Connection modes */

#define CONNREC_MODE_DIALUP		1
#define CONNREC_MODE_DIRECT 	0

/*  Authentication types */

#define CONNREC_AUTH_NONE		0
#define CONNREC_AUTH_PASSWORD   1

#define CONNREC_RLAN_ITEMS_RAS	"6"

/*	Address Book - "Connections" (and other views) Enabled field values */

#define	KWD_DISABLED 	"Disabled"				/* Obsolete */
#define	KWD_NO 			"No"					/* Obsolete */
#define VALUE_NO		'0'
#define VALUE_DISABLED	'0'
#define VALUE_ENABLED	'1'
#define VALUE_STARTUP	'2'

/* Account form/view stuff in personal address book */

#define ACCOUNTSNAMESPACE "$Accounts"

/* fields in the form */
#define ACCOUNT_FORM		"Account"
#define ACCOUNT_NAME		"AccountName"
#define ACCOUNT_SERVERNAME	"AccountServer"
#define ACCOUNT_USERNAME	"AccountLoginName"
#define ACCOUNT_PASSWORD	"AccountPassword"
#define ACCOUNT_PROTOCOL	"AccountProtocol"
#define ACCOUNT_FILENAME	"AccountFilename"
#define ACCOUNT_SSL			"SSLStatus"
#define ACCOUNT_LOCATION	"AccountLocation"
#define ACCOUNT_CONNECTION	"ConnectionMode"
#define ACCOUNT_PORT		"AccountPortNumber"
#define ACCOUNT_POPDELMAIL	"PopDeleteMail"
#define ACCOUNT_SSLSITECERTS 	"SSLSiteCerts"
#define ACCOUNT_SSLEXPIREDCERTS	"SSLExpiredCerts"
#define ACCOUNT_SSLPROTOCOLVER	"SSLProtocolVersion"
#define ACCOUNT_SSLSENDCERTS	"SSLSendCertificates"
#define ACCOUNT_SSLSERVERAUTH	"SSLServerAuthenticate"
#define ACCOUNT_IMAPDRAFT		"IMAPDrafts"
#define ACCOUNT_IMAPSENT		"IMAPSent"
#define ACCOUNT_REPLHISTORY		"AccountReplicationHistory"
#define ACCOUNT_REPLICAS		"AccountReplicas"
#define ACCOUNT_IMAPFIRSTOPEN	"IMAPFirstOpen"

#define ACCOUNT_SSL_ON		"1"
#define	ACCOUNT_SSL_OFF		"0"

/* used to get appropriate accounts for NAMELookups */
#define ACCOUNT_LOOKUPITEMS	"AccountName\0AccountProtocol\0AccountLocation\0AccountFilename\0AccountServer\0IMAPMode\0%AccountFileList"
#define ACCOUNT_NAMEITEM			0
#define ACCOUNT_PROTOCOLITEM		1
#define ACCOUNT_LOCATIONITEM		2
#define ACCOUNT_DATABASEITEM		3		/*	This is the proxy file name only */
#define ACCOUNT_SERVERITEM			4
#define ACCOUNT_IMAPMODEITEM		5
#define ACCOUNT_FILELISTITEM		6		/*	This is a list including the proxy file name and all replicas */
#define ACCOUNT_LOOKUPITEMCOUNT		7

/*   Address Book views used by Mail Address in V3. */

#define PEOPLE_GROUPS_FLAT_VIEW      "($PeopleGroupsFlat)"

/*   Address Book view and column used by Mail Address in V4. */

#define PEOPLE_GROUPS_HIER_VIEW      	"($PeopleGroupsHier)"
#define MAIL_ADDRESS_VIEW				"($PeopleGroupsFlat)"
#define PEOPLE_GROUPS_CORP_HIER_VIEW	"($PeopleGroupsCorpHier)"
#define PEOPLE_GROUPS_BY_LANG_VIEW		"($PeopleGroupsByLang)"

#define MAIL_ADDRESS_PICKLIST_COLUMN	2
#define MAIL_NAME_PICKLIST_COLUMN		3

#define MAIL_ADDRESS_NAME_COLUMN		"NPName"
#define MAIL_ADDRESS_ADDRESS_COLUMN		"MAMailAddress"
#define MAIL_ADDRESS_ALT_NAME_COLUMN	"AltFullName"

/*  ($PeoplesGroupsHier) column position,  be careful with modifying these.
		LDAP server uses this view and assumes these positions */
#define MAIL_ADDRESS_HIER_COLUMN		3
#define MAIL_NAME_HIER_COLUMN			4
#define MAIL_NAME_HIER_TYPE				5
#define MAIL_NAME_HIER_PUBLICKEY		6
#define MAIL_HIER_MAILADDRESS			"$25"
#define MAIL_HIER_CN					"$11"
#define MAIL_HIER_DN					"$24" /* This name had changed to "NPName" in R5.0 
												but has changed back because of compatibility */
#define USERS_FULLNAME_COLUMN			"$23" /* Users Full Name column named */ 
/* #define MAIL_HIER_DN						"NPName" */
#define MAIL_HIER_TYPE					"Type"
#define MAIL_HIER_PUBLICKEY				"$20"

/* Person record field names */
#define PERSON_HOME_STREETADDRESS		"StreetAddress"
#define PERSON_HOME_CITY				"City"
#define PERSON_HOME_STATE				"State"
#define PERSON_HOME_ZIP					"Zip"
#define PERSON_HOME_COUNTRY				"Country"
#define PERSON_HOME_FAX					"HomeFAXPhoneNumber"
#define PERSON_SPOUSE					"Spouse"
#define PERSON_CHILDREN					"Children"
#define PERSON_OFFICE_STREETADDRESS		"OfficeStreetAddress"
#define PERSON_OFFICE_CITY				"OfficeCity"
#define PERSON_OFFICE_STATE				"OfficeState"
#define PERSON_OFFICE_ZIP				"OfficeZip"
#define PERSON_OFFICE_COUNTRY			"OfficeCountry"
#define	PERSON_OFFICE_FAX				"OfficeFAXPhoneNumber"
#define PERSON_OFFICE_NUMBER			"OfficeNumber"
#define PERSON_GENERATION_QUALIFIER		"Suffix"
#define PERSON_PERSONAL_TITLE			"Title"
#define PERSON_JOB_TITLE				"JobTitle"
#define PERSON_MANAGER					"Manager"
#define PERSON_CELL_PHONE			  	"CellPhoneNumber"
#define PERSON_PAGER					"PhoneNumber_6"
#define PERSON_ASSISTANT				"Assistant"
#define PERSON_ENCRYPT_INCOMING_MAIL	"EncryptIncomingMail"
#define PERSON_X400_ADDRESS				"x400Address"
#define PERSON_WEB_SITE					"WebSite"
#define PERSON_EMPLOYEE_ID				"EmployeeID"



/*	Address Book view used by ServerConfig (to refresh Notes.INI parameters). */

#define SERVER_CONFIG_NAMESPACE		"$ServerConfig"
#define SERVER_CONFIG_NAMESPACE_1	"1\\$ServerConfig"
#define SERVER_CONFIG_VIEW			"($ServerConfig)"
#define SERVER_ACCESS_VIEW			"($ServerAccess)"

/* Server Configuration form items */
#define SERVER_CONFIG_FORM			"ServerConfig"
#define CONFIG_SERVERNAME_ITEM 		"ServerName"		/* Server name */
#define CONFIG_MAILEXT_ITEM			"MailExternalSMTP"

/* LDAP related definitions */
#define LDAP_ACCESS_CONTROL_ITEM		"LDAPAccessControl"
#define LDAP_MAXENTRIES_ITEM			"LDAPMaxEntries"
#define LDAP_MINCHAR_ITEM				"LDAPMinChar"
#define LDAP_TIMEOUT_ITEM				"LDAPTimeout"
#define LDAP_PORT_ITEM					"LDAP_Port"
#define LDAP_PORTSTATUS_ITEM			"LDAP_PortStatus"
#define LDAP_SSLPORT_ITEM				"LDAP_SSLPort"
#define LDAP_SSLSTATUS_ITEM				"LDAP_SSLStatus"
#define LDAP_USESSL_ITEM				"LDAP_UseSSL"
#define LDAP_TCP_NAME_PASSWORD_ITEM		"LDAP_TCPNP"
#define LDAP_ALLOWANONYMOUS_ITEM		"LDAP_AllowAnonymous"
#define LDAP_SEARCH_ITEM				"LDAP_Search"
#define LDAP_AUTHENTICATION_TYPE_ITEM	"LDAP_AuthenticationType"
#define LDAP_GET_CLIENT_CERT_ITEM		"LDAP_SSLCert"
#define LDAP_SSL_NAME_PASSWORD_ITEM		"LDAP_SSLNP"
#define	LDAP_SSLANONYMOUS_ITEM			"LDAP_SSLAnonymous"
#define LDAP_CONFIG_FORM				"($LDAPSettings)"
#define LDAP_AMBIGUOUS_WRITE_ITEM		"LDAPAmbiguousWrite"
#define LDAP_CLIENT_ACCESS_ITEM			"LDAPAllowWriteAccess"
#define LDAP_OPTIMIZEVIEW_ITEM			"LDAPOptimizeSearch"
#define LDAP_QUERYEXTENDEDOBJECT_ITEM	"LDAPOptimizeSearch" /* "LDAPQueryExtendedObjects" - Post R5.0 */
#define LDAP_QUERYALTLANG_ITEM			"LDAPQueryAltLangInfo"
#define LDAP_VIEW_TYPE					"%LDAPType"
#define LDAP_EXTENDED_OBJECTCLASS_ITEM	"$objectclass"
#define LDAP_ENFORCE_SCHEMA_ITEM		"LDAPEnforceSchema"

/* LDAP View names */
#define LDAP_CN_VIEW	"($LDAPCN)"
#define LDAP_CN_VIEW_ALT "$LDAPCN"
#define LDAP_S_VIEW		"($LDAPS)"
#define LDAP_G_VIEW		"($LDAPG)"
#define LDAP_HIER_VIEW	"($LDAPHIER)"

/* Column names */
#define LDAP_DN_COLUMN "%DN"


#define MSG_CONFIG_FORM					"($MessagingSettings)"


/* Address Book - Items used for Message Tracking Configuration */

#define MT_ENABLED_ITEM					"MTEnabled"
#define MT_NOTRACKING_FOR_ITEM			"MTNoTrackingFor"
#define MT_ALLOWEDTO_TRACK_ITEM			"MTAllowTracking"
#define MT_SUBJECTS_ENABLED_ITEM		"MTLogSubjects"
#define MT_NOSUBJECTS_FOR_ITEM			"MTNoSubjectsFor"
#define MT_ALLOWEDTO_TRACKSUBJECTS_ITEM "MTAllowSubjects"
#define MT_ALLOWEDTO_CAUSEDIALING_ITEM	"MTCallers"
#define MT_COLLECTOR_INTERVAL_ITEM		"MTInterval"
#define MT_MAXRESPONSES					"MTMaxResponses"


/* Address Book & INI - Items used for Transactional Logging Configuration INI */

#define TRANSLOG_STATUS					"TRANSLOG_Status"
#define TRANSLOG_PATH  					"TRANSLOG_Path"
#define TRANSLOG_MAXSIZE				"TRANSLOG_MaxSize"
#define TRANSLOG_PERFORMANCE			"TRANSLOG_Performance"
#define TRANSLOG_STYLE					"TRANSLOG_Style"
#define TRANSLOG_USEALL					"TRANSLOG_UseAll"
#define TRANSLOG_AUTOFIXUP				"TRANSLOG_AutoFixup"


/*	Address Book - Items and names used by name server */

#define NS_SERVERNAMEITEM			0
#define NS_SERVERTITLEITEM			1
#define NS_SERVERNETWORKITEM		2
#define NS_SERVERNETADDRESSESITEM	3
#define NS_SERVERPORTSITEM			4
#define NS_SERVERLOOKUPITEMCOUNT	5
#define NS_SERVERLOOKUPITEMS "ServerName\0ServerTitle\0Network\0NetAddresses\0Ports"

/*	Address Book - Items and names used by DbQuotaSet to verify access */

#define DBQUOTA_SERVERADMINITEM			0
#define DBQUOTA_SERVERLOOKUPITEMCOUNT	1
#define DBQUOTA_SERVERLOOKUPITEMS      "Administrator"

/*	Address Book - Items and names used by server during initialization */

#define INIT_SERVERNAMEITEM			0
#define INIT_SERVERTITLEITEM		1
#define INIT_SERVERADMINITEM		2

#define	INIT_SERVERCERTIFICATE		3
#define	INIT_SERVERCHANGEREQUEST	4

#define INIT_SERVERALLOWITEM		5
#define INIT_SERVERDENYITEM			6
#define INIT_SERVERCREATEITEM		7
#define INIT_SERVERREPLICAITEM		8

#define INIT_SERVERPTTARGETITEM		9
#define INIT_SERVERPTCLIENTITEM		10
#define INIT_SERVERPTCALLERITEM		11
#define INIT_SERVERPTACCESSITEM		12

#define INIT_SERVER_WHITELIST		13
#define INIT_SERVER_ANONYMOUSACCESS	14

#define INIT_SERVER_BUILDNUMBER		15
#define INIT_SERVERRESTRICTEDLIST	16
#define INIT_SERVERUNRESTRICTEDLIST	17

#define INIT_SERVER_CHECK_CLIENT_PW 18
#define INIT_SERVER_CLUSTERNAME		19

#define INIT_SERVERMONITORALLOWLIST	20
#define INIT_SERVERMONITORDENYLIST	21

#define INIT_SERVERSMTPENABLED		22

#define INIT_TRANSLOG_STATUS		23 /* Items used for Transactional Logging Configuration */
#define INIT_TRANSLOG_PATH  		24
#define INIT_TRANSLOG_MAXSIZE		25
#define INIT_TRANSLOG_PERFORMANCE	26
#define INIT_TRANSLOG_STYLE			27
#define INIT_TRANSLOG_USEALL		28
#define INIT_TRANSLOG_AUTOFIXUP		29

#define INIT_SERVERLOOKUPITEMCOUNT	30
#define INIT_SERVERLOOKUPITEMS      \
"ServerName\0ServerTitle\0Administrator\0\
Certificate\0ChangeRequest\0\
AllowAccess\0DenyAccess\0CreateAccess\0ReplicaAccess\0\
PTTargets\0PTClients\0PTCallers\0PTAccess\0\
WhiteList\0AnonymousAccess\0\
ServerBuildNumber\0RestrictedList\0UnrestrictedList\0\
ServerCheckPasswords\0ClusterName\0AllowMonitors\0DenyMonitors\0SMTPListenerEnabled\0\
TRANSLOG_Status\0TRANSLOG_Path\0TRANSLOG_MaxSize\0TRANSLOG_Performance\0\
TRANSLOG_Style\0TRANSLOG_UseAll\0TRANSLOG_AutoFixup"

/*	Address Book - Items and names used by cconsole to verify access */

#define CCONSOLE_SERVERADMINITEM			0
#define CCONSOLE_SERVERLOOKUPITEMCOUNT	1
#define CCONSOLE_SERVERLOOKUPITEMS      "Administrator"

/* 
 * Address Book - Items and names used by Assist to verify agent execution 
 * access.
 */
                                        
#define ASSIST_PRIVATE_ITEM             0
#define ASSIST_RESTRICTED_ITEM          1
#define ASSIST_UNRESTRICTED_ITEM        2
#define ASSIST_START_ITEM               3
#define ASSIST_END_ITEM                 4
#define ASSIST_MAX_START_ITEM			5
#define ASSIST_MAX_END_ITEM				6

#define ASSIST_LOOKUP_AMGR_ITEM_COUNT   7
#define ASSIST_LOOKUP_AMGR_ITEMS        "PrivateList\0RestrictedList\0UnrestrictedList\0StartTime\0EndTime\0MaxStartTime\0MaxEndTime"

#define ASSIST_PRIVATE_LIST_NAME        "PRIVATE_LIST"
#define ASSIST_RESTRICTED_LIST_NAME     "RESTRICTED_LIST"
#define ASSIST_UNRESTRICTED_LIST_NAME   "UNRESTRICTED_LIST"

/* 
 * Address Book - Items and names used by Agent Manager to verify agent
 * execution access.
 */

#define AMGR_RELOAD_ITEM            		0
#define AMGR_NORMAL_START_ITEM             	1
#define AMGR_NORMAL_END_ITEM               	2
#define AMGR_NORMAL_CONCURRENT_TASKS_ITEM  	3
#define AMGR_NORMAL_MAX_EXECUTION_ITEM     	4
#define AMGR_NORMAL_PERCENT_TIME_ITEM      	5
#define AMGR_MAX_START_ITEM             	6
#define AMGR_MAX_END_ITEM               	7
#define AMGR_MAX_CONCURRENT_TASKS_ITEM  	8
#define AMGR_MAX_MAX_EXECUTION_ITEM     	9
#define AMGR_MAX_PERCENT_TIME_ITEM     		10
#define AMGR_CREATE_DB_ITEM         		11
#define AMGR_PRIVATE_ITEM           		12
#define AMGR_RESTRICTED_ITEM        		13
#define AMGR_UNRESTRICTED_ITEM      		14
#define AMGR_ALLOWACCESS_ITEM      			15
#define AMGR_DENYACCESS_ITEM      			16
#define AMGR_CREATEREPLICA_DB_ITEM         	17
#define AMGR_SERVERS_NOTEID_ITEM         	18 /* expanded lookup to include servers id note */
#define AMGR_SERVERS_NAPATH_ITEM         	19 /* expanded lookup to include N&A path */


#define AMGR_LOOKUP_ITEM_COUNT      18
#define AMGR_LOOKUP_ITEMS           \
"ReloadTime\0StartTime\0EndTime\0ConcurrentAgents\0MaxExecution\0\
PercentTime\0MaxStartTime\0MaxEndTime\0MaxConcurrentAgents\0\
MaxMaxExecution\0MaxPercentTime\0CreateAccess\0PrivateList\0\
RestrictedList\0UnrestrictedList\0AllowAccess\0DenyAccess\0\
ReplicaAccess"

/* extended lookup used for web agents and synch new mail agents, i.e. API based invocation */
#define AMGR_EXT_LOOKUP_ITEM_COUNT      20
#define AMGR_EXT_LOOKUP_ITEMS           \
"ReloadTime\0StartTime\0EndTime\0ConcurrentAgents\0MaxExecution\0\
PercentTime\0MaxStartTime\0MaxEndTime\0MaxConcurrentAgents\0\
MaxMaxExecution\0MaxPercentTime\0CreateAccess\0PrivateList\0\
RestrictedList\0UnrestrictedList\0AllowAccess\0DenyAccess\0\
ReplicaAccess\0$$NoteId\0$$DBName"

/* Address book - Items used by NOI for configuration and other ORB addins for 
   security
*/

/* First List contains security configuration information used by all ORB process
 * and stored in global static memory
 */
#define NOI_ALLOW_ACCESS_LIST  			0
#define NOI_DENY_ACCESS_LIST        	1
#define NOI_CREATE_DB_LIST          	2
#define NOI_CREATE_RP_LIST          	3
#define NOI_RESTRICTED_LIST			  	4
#define NOI_UNRESTRICTED_LIST		 	5

#define NOI_SECURITY_ITEM_COUNT			6
#define NOI_SECURITY_ITEMS				"AllowAccess\0DenyAccess\0CreateAccess\0\
ReplicaAccess\0NOIRestrictedList\0NOIUnrestrictedList"

/* Second list contains port configuration information used by 1 process.
 * The field names must be specified for each additional ORB process,
 * but the field order should be as specified below for common processing
 */
#define ORB_TCP_PORT					0	
#define ORB_TCP_PORT_STATUS    			1
#define ORB_TCP_NAME_AND_PASSWD			2
#define ORB_TCP_ANONYMOUS      			3
#define ORB_SSL_PORT        			4
#define ORB_SSL_PORT_STATUS    			5
#define ORB_SSL_NAME_AND_PASSWD			6
#define ORB_SSL_ANONYMOUS      			7
#define ORB_THREADPOOL_SIZE				8
#define ORB_HTTP_KEYRING_FILE			9

#define NOI_PORT_ITEM_COUNT	        	10
#define NOI_PORT_ITEMS              "IIOP_Port\0IIOP_PortStatus\0IIOP_TCPNP\0IIOP_AllowAnonymous\0\
IIOP_SSLPort\0IIOP_SSLStatus\0IIOP_SSLNP\0IIOP_SSLAnonymous\0IIOP_ThreadPoolSize\0HTTP_SSLKeyFile"


/*	Address book - Items used by Calendaring & Scheduling for user lookup
	and domain lookup. */

#define SCHED_USERLOOKUPITEMCOUNT			6
#define SCHED_USERLOOKUPITEMS "FullName\0ListName\0MailAddress\0MailDomain\0MailServer\0CalendarDomain"
#define SCHED_USERLOOKUPFULLNAMEITEM		0
#define SCHED_USERLOOKUPLISTNAMEITEM		1
#define SCHED_USERLOOKUPMAILADDRESSITEM		2
#define SCHED_USERLOOKUPMAILDOMAINITEM		3
#define SCHED_USERLOOKUPMAILSERVERITEM		4
#define SCHED_USERLOOKUPCALENDARDOMAINITEM	5

#define SCHED_DOMAINLOOKUPITEMCOUNT					3
#define SCHED_DOMAINLOOKUPITEMS "DomainType\0CalendarServer\0CalendarSystem"
#define SCHED_DOMAINLOOKUPDOMAINTYPEITEM			0
#define SCHED_DOMAINLOOKUPCALENDARSERVERITEM		1
#define SCHED_DOMAINLOOKUPCALENDARSYSTEMITEM		2

#define SCHEDULE_MGR_LOOKUP_ITEM_COUNT			7
#define SCHEDULE_MGR_LOOKUP_ITEMS				"FullName\0MailServer\0MailFile\0MailDomain\0CalendarDomain\0Type\0MailAddress"
#define SCHEDULE_MGR_LOOKUP_ITEM_MAILSERVER		1
#define SCHEDULE_MGR_LOOKUP_ITEM_MAILFILE		2
#define SCHEDULE_MGR_LOOKUP_ITEM_MAILDOMAIN     3
#define SCHEDULE_MGR_LOOKUP_ITEM_CALENDARDOMAIN 4
#define SCHEDULE_MGR_LOOKUP_ITEM_TYPE			5
#define SCHEDULE_MGR_LOOKUP_ITEM_MAILADDRESS    6

/*	View note item names */

#define VIEW_TITLE_ITEM 				FIELD_TITLE				/* Title */
#define VIEW_COLLECTION_ITEM			"$Collection"			/* Contains object ID */
#define VIEW_CONTAINER_ITEM				"$ViewContainer"		/* Contains storage object ID */
#define VIEW_FORMULA_ITEM				"$Formula"				/* Selection formula buffer */
#define VIEW_FORMULA_TIME_ITEM			"$FormulaTV"			/* If present, formula is "time-relative" (@NOW-based) */
#define VIEW_CLASSES_ITEM 				"$FormulaClass" 		/* Formula note classes */
#define VIEW_COLLATION_ITEM				"$Collation"			/* Collation buffer */
#define VIEW_TOTALS_ITEM				"$Totals"				/* Subtotalling specification */
#define VIEW_VIEW_FORMAT_ITEM 			"$ViewFormat" 			/* View table format item */
#define VIEW_INDEX_ITEM 				"$Index"				/* Index disposition options */
#define VIEW_DESIGN_VER_ITEM_V2			"$DesignVersion"		/* Design note version, for V2 backward compatibility */
#define VIEW_DESIGN_VER_ITEM			"$Version"				/* Design note version */
#define VIEW_NOTEREF_ITEM 				FIELD_LINK				/* Note Reference item */
#define VIEW_CONFLICT_ITEM				"$Conflict"				/* Replication update conflict */
#define VIEW_FORM_FORMULA_ITEM			"$FormFormula"			/* Form Formula */
#define VIEW_COMMENT_ITEM				"$Comment"				/* View comment. */
#define VIEW_SELQUERY_ITEM				"$SelQuery"				/* View selection query object */
#define VIEW_LASTSEENUID_ITEM			"$LastSeenUID"			/* Internet Replication Last Seen UID */
#define ITEM_NAME_REFOPT				"$RefOptions"			/* ALlow a ref to original 
																	note to be included.
																*/

/* Calendar style view items */

#define VIEW_CALENDAR_FORMAT_ITEM  		"$CalendarFormat"		/* Calendar View format item */


/* Folder-related view items */
/* Pre-build 126 items, can be removed before V4 ship - only exposed internally */
#define VIEW_UNID_SELECTION_ITEM		"$UNIDSelection"		/* List of UNID's which are in view. */
#define VIEW_USE_UNID_SELECTION_ITEM	"$UseUNIDSelection"		/* If present, uses UNID selection table. */

#define VIEW_FOLDER_OBJECT				"$FolderObject"			/*  If present, is ODS version of FOHEADER and 
																	set of entries, see dbfolder.h.  The view
																	may have additional items with suffixes
																	on this item name, e.g., $FolderObject1 */
#define VIEW_FOLDER_IDTABLE				"$FolderIDTable"		/*  If present, is ID table representing the
																	contents of the folder */
#define VIEW_ANTIFOLDER_IDTABLE			"$AntiFolderIDTable"	

/*	Hidden view name prefix/postfix strings. */

#define HIDDEN_VIEW_NAME_PREFIX		"("
#define HIDDEN_VIEW_NAME_POSTFIX	")"

/* ViewMap note item names */

#define VIEWMAP_DATASET_ITEM	"$ViewMapDataset"	/* Contains ViewMap dataset data */
#define VIEWMAP_LAYOUT_ITEM		"$ViewMapLayout"	/* Contains layout objects */
#define VIEWMAP_IMAGEMAP_ITEM	"$NavImagemap"		/* Contains the navigator's imagemap */

/*	UName special fields */

#define	UNAME_PATH_ITEM			"Path"
#define	UNAME_SERVER_ITEM		"Server"
#define	UNAME_DB_ITEM			"Database"

/*	Actions */

#define ACTION_ITEM "$ACTIONS"
#define V5ACTION_ITEM "$V5ACTIONS"

/* Filter note item names */

#define	FILTER_TYPE_ITEM		"$Type"
#define	FILTER_COMMENT_ITEM		"$Comment"
#define	FILTER_FORMULA_ITEM		"$Formula"		/*	Required */
#define	FILTER_FORMULA2_ITEM	"$Formula2"		/*	Second one, optional */
#define	FILTER_SCAN_ITEM		"$Scan"			/*	all in view, selected in view, all in db, unread in db	*/
#define	FILTER_HIGHLIGHT_ITEM	"$Highlight"	/*	'1' if hilites enabled, '0' to remove */
#define	FILTER_QUERY_ITEM		"$Query"		/*	Full text query string used to refine notes to do */
#define FILTER_OPERATION_ITEM	"$Operation"	/*	update, create new, select	*/
#define FILTER_PERIOD_ITEM		"$Period"		/*	hourly, daily, or weekly	*/
#define FILTER_LEFTTODO_ITEM	"$LeftToDo"		/*	Data structure describing what's left to do */
#define FILTER_MACHINE_ITEM		"$MachineName"	/*	name of machine on which this background filter may run */

/*	filter types	*/

#define FILTER_TYPE_MENU 		0
#define FILTER_TYPE_BACKGROUND	1
#define FILTER_TYPE_MAIL 		2
#define FILTER_TYPE_ONCE		3

/*	filter scan options	*/

#define FILTER_SCAN_ALL  		0
#define FILTER_SCAN_UNREAD 		1
#define FILTER_SCAN_VIEW 		2
#define FILTER_SCAN_SELECTED 	3
#define FILTER_SCAN_MAIL		4
#define FILTER_SCAN_NEW			5

#define FILTER_OP_UPDATE  	0
#define FILTER_OP_SELECT  	1
#define FILTER_OP_NEW_COPY	2

/*	filter periods	*/

#define	PERIOD_HOURLY	0
#define	PERIOD_DAILY	1
#define	PERIOD_WEEKLY	2
#define	PERIOD_DISABLED	3

/*	Query note item names. */

/*	If the user has typed in a query, it is stored in $SimpleQuery; If
	the user has created a query using the Query Builder, it is stored
	in the $Builder... fields. */

#define QUERY_SIMPLEQUERY_ITEM	"$SimpleQuery"	/*	simple query */
#define QUERY_BUILDERQUERY_ITEM	"$BuilderQuery"	/*	Query Builder: text list of */
												/*	different portions of query: */
												/*	any of these, all of these, */
												/*	none of these, author */

#define QUERY_BUILDERDATE_ITEM	"$BuilderDate"	/*	Date before or after */
#define QUERY_BUILDERFLAGS_ITEM	"$BuilderFlags"	/*	query builder flags */
#define QUERY_FIELDQUERY_ITEM	"$FieldQuery"	/*	query by form query */

#define QUERY_FIELDACTION_ITEM	"$FieldAction"	/*	action by form struct */
#define QUERY_FORMULAACTION_ITEM	"$FormulaAction"	/*	@function action formula */

#define QUERY_BUILDERFLAG_NEAR			'N'		/*	Apply near to 'all of these' */
#define QUERY_BUILDERFLAG_DATEBEFORE	'B'		/*	Before $BuilderDate (as opposed to after) */

/* 	V4 Search Bar queries */

#define QUERY_V4_OBJECTQUERY_ITEM	"$V4QueryObject" /* Query object built by the V4 Search Builder */
#define QUERY_V4_OPTIONS_ITEM		"$V4QueryOptions" /* Query options from the V4 Search Builder */

/*	V4 Assistants */

#define ASSIST_INFO_ITEM		"$AssistInfo"	/*	info (TYPE_ASSISTANT_INFO) */
#define ASSIST_TYPE_ITEM		"$AssistType"	/*	Type of assistant - related to action type */
#define ASSIST_QUERY_ITEM		"$AssistQuery"	/*	assistant query item */
#define ASSIST_ACTION_ITEM		"$AssistAction"	/*	assistant action item */
#define ASSIST_LASTRUN_ITEM		"$AssistLastRun"	/*	TimeDate of last run */
#define ASSIST_DOCCOUNT_ITEM	"$AssistDocCount"	/*	Number of docs run on last run */
#define ASSIST_RUNINFO_ITEM		"$AssistRunInfo"	/*	Run information object */
#define ASSIST_EXACTION_ITEM	"$AssistAction_Ex"	/*	assistant action item - extra data */
#define ASSIST_VERSION_ITEM		"$AssistVersion"	/*	TIMEDATE of when the agent design 
														(as opposed to enable/disable state)
														was changed */

/* Types for ASSIST_TYPE_ITEM - the following defines are used to determine
 * what type of assistant we are dealing with -- ie, what is the main
 * action type that the user has defined.  The formula ones are for
 * backwards compatability with V3.
 *  See ods.h for the SIG_ACTION_xxx values used for regular V4 generic agents.
 */

#define ASSIST_SIG_ACTION_NONE	 		   -1	/* No action defined */
/* formula, update only -FILTER_OP_UPDATE 	0 */
/* formula, select only -FILTER_OP_SELECT  	1 */
/* formula, new copy    -FILTER_OP_NEW_COPY 2 */

/*	The default search form and default action forms are used by query by form
	and action by form. */

#define DEFAULT_QUERY_BY_FORM		"$DefaultSearch"
#define DEFAULT_ACTION_BY_FORM		"$DefaultAction"

/* Misc Flags */

#define ASSIST_FLAG_ENABLED			'E'
#define ASSIST_FLAG_NEWCOPY			'N'
#define ASSIST_FLAG_HIDDEN			'H'
#define ASSIST_FLAG_PRIVATE			'P'
#define ASSIST_FLAGS_ITEM		"$AssistFlags"	/*	Misc flags */

#define ASSIST_MAIL_ITEM		"$AssistMail"	/*	If this field exists in a mail note, it means that */
												/*	mail message was created by an agent. */

#define ASSIST_TRIGGER_ITEM		"$AssistTrigger"	/*	(Read-only) Assistant's trigger type */
#define FORM_SCRIPT_OBJECT		"$$FormScript_O"	/* Script object code item */
#define SUBFORM_ITEM_NAME "$SubForms"

/* These were moved here from \edit\dmem.h */
#define FORM_SCRIPT_ITEM_NAME "$$FormScript"
#define	DOC_SCRIPT_ITEM		"$Script"
#define DOC_SCRIPT_ITEM_OBJECT "$$Script_O"
#define DOC_ACTION_ITEM		"$$FormAction"
#define DOC_SCRIPT_NAME		"$$ScriptName"

/* View Script items */
#define VIEW_SCRIPT_NAME		"$ViewScript"
#define VIEW_SCRIPT_OBJECT		"$ViewScript_O"
#define VIEW_GLOBAL_SCRIPT_NAME		"$ViewGlobalScript"
#define VIEW_GLOBAL_SCRIPT_OBJECT	"$ViewGlobalScript_O"
#define VIEW_ACTION_ITEM_NAME	"$ViewAction" 	/* Formula for view script event */
#define VIEW_ACTION_EVENT_COUNT	11	/* ie, $ViewAction0-$ViewAction10 - one per view script event that can contain formulas */

/* Database Script items */
#define DB_SCRIPT_DESIGN_NAME	"Database Script"
#define DB_SCRIPT_NAME		"$DBScript"
#define DB_SCRIPT_OBJECT	"$DBScript_O"
#define DB_ACTION_ITEM_NAME	"$DBAction"

/* Script Library items */
#define SCRIPTLIB_ITEM_NAME	"$ScriptLib"
#define SCRIPTLIB_OBJECT	"$ScriptLib_O"

/* Replication formula note item names */

#define REPLFORMULA_SERVER_ITEM		FIELD_TITLE
#define REPLFORMULA_VERSION_ITEM	"$ReplVersion"
#define REPLFORMULA_SOURCE_SERVERS	"$ReplSrcServers"
#define REPLFORMULA_NOTECLASS_ITEM	"$ReplClassMasks"
#define REPLFORMULA_FORMULA_ITEM 	"$ReplFormula"
#define REPLFORMULA_VIEW_ITEM		"$ReplView"	/* V4 feature; sel repl by view */
#define REPLFORMULA_PRIVATE_FOLDER_ITEM	"$ReplPrivateFolder" 	/* V4 feature; sel repl by private folder */
#define REPLFORMULA_FIELDS_ITEM		"$ReplFields"	/* V4.5 feature; sel repl by fields */

#define FIELD_NAME_DELIMITER ';'
#define VIEW_NAME_DELIMITER ';'
#define VIEW_NAME_DELIMETER VIEW_NAME_DELIMITER /* (misspelled!) */

/* Special replication flags */
 
#define REPLFLAGS_ITEM 	"$ReplFlags"
#define REPL_FLAG_NOREPL	'n'

/* Icon note item names */

#define DESK_ICON_ITEM "IconBitmap"
#define LSECFLAGS_ITEM 	"$LSECFlags"
#define DEFAULT_NAVIGATOR_ITEM "$DefaultNavigator"
#define DEFAULT_WEB_NAVIGATOR_ITEM "$DefaultWebNavigator"
#define DEFAULT_WEBPAGE_ITEM "$DefaultWebPage"
#define DEFAULT_OUTLINE_ITEM "$DefaultOutline"
#define DEFAULT_FRAMESET_ITEM "$DefaultFrameset"
#define DEFAULT_WEB_FRAMESET_ITEM "$DefaultWebFrameset"
#define DEFAULT_WEB_PAGE_ITEM "$DefaultWebLaunchPage"
#define ICON_TEMPLATEMODTIME_ITEM "$TemplateModTime"
#define ICON_TEMPLATESERVERNAME_ITEM "$TemplateServerName"
#define ICON_TEMPLATEFILENAME_ITEM "$TemplateFileName"
#define ICON_UPDATEDBYLIMIT	"$UpdatedByLimit"
#define ICON_REVISIONSLIMIT	"$RevisionsLimit"
#define ICON_SOFTDELETE_EXPIRE_HOURS "$SoftDeleteExpireHours"
#define LAUNCH_VIEWNAME_ITEM "$LaunchViewName"
#define LAUNCH_WEB_VIEWNAME_ITEM "$LaunchWebViewName"
#define LAUNCH_DOCLINK_ITEM "$LaunchDoclink"
#define LAUNCH_WEB_DOCLINK_ITEM "$LaunchWebDoclink"
#define LAUNCH_WEB_DOCLINK_ANCHOR_ITEM "$LaunchWebDoclinkAnchor"
#define DEFAULT_LANGUAGE	"$DefaultLanguage"
#define DEFAULT_COLLATION	"$DefaultCollation"
							 
/*	Character flags for replicated local security property ($LSECFlags field
	in the icon note */

#define CHFLAG_SET_LOCALSEC		's'			/* should set local access control */
#define CHFLAG_CLEAR_LOCALSEC	'c'			/* should clear local access control */
#define CHFLAG_COMPACT_LOCALSEC 'p'			/* compact should set local access control */

/* 	character flags for the "replicated file header" ($Flags field in the 
	icon note) */

/*	NOTE: These flags are not in alphabetical order. There are more of them than
	you think. Keep looking until you see a comment saying the set is over. */

/* ----< This is the beginning of the CHFLAGs >---- */

#define	ICON_FLAGS	DESIGN_FLAGS

/* icon flags */
#define CHFLAG_LAUNCH_APP			'a'
#define CHFLAG_MAILBOX_TYPE			'A'
#define CHFLAG_ADDRESS_BOOK_TYPE	'b'
#define CHFLAG_LIGHT_ADDRESS_BOOK_TYPE	'B'
#define CHFLAG_SHOW_CHANGED_POLICY	'c'
#define CHFLAG_LAUNCH_DOCLINK		'd'
#define CHFLAG_LAUNCH_FRAMESET		'F'
#define CHFLAG_RESTRICT_STORED_FORMS 'f'
#define CHFLAG_LIBRARY_TYPE			'g'
#define CHFLAG_DEFERRED_LOADED_IMAGES 'i'
#define CHFLAG_PERSONALJOURNAL_TYPE	'j'
#define CHFLAG_LAUNCH_NAVIGATOR		'l'
#define CHFLAG_SEARCH_SCOPE_TYPE	'm'
#define CHFLAG_NEVER_SHOW_POLICY	'n'
#define CHFLAG_LAUNCH_OUTLINE		'o'	/* Launch Outline as the navigator */
#define CHFLAG_ALWAYS_SHOW_POLICY	'p'
#define CHFLAG_SOLO_NAVIGATOR		's'
#define CHFLAG_OBSOLETE_DONTUSE		't'	
#define CHFLAG_SITEDB_TYPE			'u'
										/* 'refresh' flag from build 130-133 */
										/* has been superceded by a flag in */
										/* ICON_FLAGS_NOREFRESH, below.  */
										/* don't use this one anymore... */
#define CHFLAG_NO_SHOW_VIEW			'v'

#define CHFLAG_LAUNCH_WEBPAGE		'W'	/* Launch navigator of type Web Page */
#define CHFLAG_PANE_BIGFOLDER		'w'	/* preview pane orientation; mutually exclusive with below */
#define CHFLAG_PANE_SMALLVIEW		'x' /* preview pane orientation; mutually exclusive with above*/
#define CHFLAG_PANE_MAXIMIZED		'y'	/* preview pane size */

/* web-specific launch flags */
#define CHFLAG_WEB_LAUNCH_DOCLINK	'D'
#define CHFLAG_WEB_LAUNCH_NAVIGATOR	'L'
#define CHFLAG_WEB_ALWAYS_SHOW_POLICY 'P'
#define CHFLAG_WEB_LAUNCH_THISDOCLINK 'T'
#define CHFLAG_WEB_LAUNCH_VIEWNAME	'V'
#define CHFLAG_WEB_USEJAVASCRIPT    'J'
#define CHFLAG_WEB_USESSLCONN		'X'
#define CHFLAG_WEB_LAUNCH_PAGE		'E'
#define CHFLAG_WEB_LAUNCH_FRAMESET	'S'

#define CHFLAG_MULTILINGUAL_DB	'M'
										
#define CHFLAG_NOUNREAD_MARKS			'z'
#define CHFLAG_DISABLE_RESPONSE_INFO	'1'
#define CHFLAG_FORM_BUCKET_OPT			'2'
#define CHFLAG_MAINTAIN_LAST_ACCESSED	'3'
#define CHFLAG_DELETES_ARE_SOFT			'4'
		
#define CHFLAG_IS_LOCK_DB				'5'
#define CHFLAG_MUST_LOCK_DB				'6'		
#define CHFLAG_LARGE_UNKTABLE			'7'

/* ----< This is the end of the CHFLAGs >---- */

/* 	unlike the $Flags field, this field doesn't get
	refreshed/replaced on a design refresh/replace 
	and they don't inherit from parent templates
*/
#define ICON_FLAGS_NOREFRESH	"$FlagsNoRefresh"

#define CHFLAG_NR_ADV_TEMPLATE			't'

/* Special replication flags */
 
#define REPLFLAGS_ITEM 	"$ReplFlags"
#define REPL_FLAG_NOREPL	'n'

/* Auto-merge replication conflicts */

#define ITEM_CONFLICT_ACTION 	"$ConflictAction"	/* enable auto-merge conflicts if 1 */
#define 	CONFLICT_AUTOMERGE	'1'

/* Form note item names */

#define	ITEM_NAME_TEMPLATE "$Body"			/* form item to hold form CD */
#define	ITEM_NAME_DOCUMENT "$Info"			/* document header info */
#define	ITEM_NAME_TEMPLATE_NAME FIELD_TITLE	/* form title item */
#define	ITEM_NAME_FORMLINK "$FormLinks"		/* form link table */
#define	ITEM_NAME_FIELDS "$Fields"			/* field name table */
#define ITEM_NAME_FORMPRIVS "$FormPrivs"	/* form privileges */
#define ITEM_NAME_FORMUSERS "$FormUsers"	/* text list of users allowed to use the form */
#define ITEM_NAME_FRAMESET "$FrameSet"		/* form item to hold form Frameset definition */
#define ITEM_NAME_FRAMEINFO	"$FrameInfo"	/* frameset used to open form */

/* Special form flags */						
 
#define ITEM_NAME_KEEP_PRIVATE "$KeepPrivate"	
#define PRIVATE_FLAG_YES	'1'				/* $KeepPrivate = TRUE  force disabling of printing, mail forwarding and edit copy */
#define PRIVATE_FLAG_YES_RESEND	'2'			/* $KeepPrivate = TRUE  same as PRIVATE_FLAG_YES except allow resend */

#define ITEM_NAME_DATEPICKER_MONTH "$DatePickerMonth"	
#define ITEM_NAME_HEADERAREA "$HeaderArea"	
#define ITEM_NAME_FOOTERAREA "$FooterArea"	
#define ITEM_NAME_REGIONFRAMESET "$RegionFrameset"	
#define ITEM_NAME_BACKGROUNDGRAPHIC "$Background"	
#define ITEM_NAME_BACKGROUNDGRAPHICR5 "$BackgroundR5"	
#define ITEM_NAME_PAPERCOLOR "$PaperColor"	
#define ITEM_NAME_PAPERCOLOREX "$PaperColorEx"
#define ITEM_NAME_LAYER "$Layer"	
#define ITEM_NAME_LAYERTEXT "$LayerText"	
#define ITEM_NAME_RESTRICTBKOVERRIDE "$NoBackgroundOverride" 
#define RESTRICTBK_FLAG_NOOVERRIDE '1'		/* $NoBackgroundOverride = TRUE Don't allow user to override document background */
#define	ITEM_NAME_HTMLCODE "$HTMLCode"

#define ITEM_NAME_AUTO_EDIT_NOTE "$AutoEditMode"	
#define AUTO_EDIT_FLAG_YES	'1'				/* $AutoEditMode = TRUE  force edit mode on open regardless of Form flag */

#define ITEM_NAME_SHOW_NAVIGATIONBAR "$ShowNavigationBar"  /* Display the URL navigation Bar */
#define ITEM_NAME_HIDE_SCROLL_BARS 	"$HideScrollBars"
#define WINDOW_SCROLL_BARS_NONE 	'1'
#define WINDOW_SCROLL_BARS_HORZ 	'2'
#define WINDOW_SCROLL_BARS_VERT 	'3'

#define ITEM_NAME_BACKGROUNDGRAPHIC_REPEAT "$BackgroundRepeat"
#define BACKGROUNDGRAPHIC_REPEAT_ONCE	'1'



#define ITEM_NAME_VERSION_OPT "$VersionOpt"	/* Over-ride the Form flags for versioning. */
#define VERSION_FLAG_NONE	'0'				/* $Version = 0, None */
#define VERSION_FLAG_MURESP	'1'				/* $Version = 1, Manual - Update becomes response */
#define VERSION_FLAG_AURESP	'2'				/* $Version = 2, Auto   - Update becomes response */
#define VERSION_FLAG_MUPAR	'3'				/* $Version = 3, Manual - Update becomes parent */
#define VERSION_FLAG_AUPAR	'4'				/* $Version = 4, Auto   - Update becomes parent */
#define VERSION_FLAG_MUSIB	'5'				/* $Version = 5, Manual - Update becomes sibling */
#define VERSION_FLAG_AUSIB	'6'				/* $Version = 6, Auto   - Update becomes sibling */


/* Document note item names */

#define	ITEM_NAME_TEMPLATE_USED FIELD_FORM	/* form name used to create note, user-visible */
#define ITEM_NAME_NOTEREF FIELD_LINK		/* optional reference to another note */
#define ITEM_NAME_VERREF "$VERREF"			/* optional reference to master version note */
#define	ITEM_NAME_LINK "$Links"				/* note link table */
#define ITEM_NAME_REVISIONS "$Revisions"	/* Revision history */
#define ITEM_NAME_CONFLICT VIEW_CONFLICT_ITEM /* Replication update conflict */
#define ITEM_NAME_AUTHORS "$Authors"		/* text list of users allowed to modify document below editor access */
#define ITEM_NAME_WRITERS "$Writers"		/* text list of users allowed to modify document */

/* Document and form note item names, all items are optional */

#define	ITEM_NAME_FONTS "$Fonts"			/* font table */
#define ITEM_NAME_HEADER "$Header"			/* print page header */
#define ITEM_NAME_FOOTER "$Footer"			/* print page footer */
#define ITEM_NAME_HFFLAGS "$HFFlags"		/* header/footer flags */
	#define	HFFLAGS_NOPRINTONFIRSTPAGE	'1'		/* suppress printing header/footer on first page */
	#define	HFFLAGS_DIRECTION_RTL	'R'		/* header/footer is RTL */
#define ITEM_NAME_WINDOWTITLE "$WindowTitle"/* window title */
#define	ITEM_NAME_ATTACHMENT "$FILE" 		/* file attachment, MUST STAY UPPER-CASE BECAUSE IT'S SIGNED! */
#define ITEM_NAME_HTMLHEADTAG "$HTMLHeadTag"/* Override for HTML head tag */
#define ITEM_NAME_HTMLBODYTAG "$HTMLBodyTag"/* Override for HTML body tag */
#define	ITEM_NAME_WEBQUERYSAVE "$WEBQuerySave" /*WebQuerySave formula */
#define	ITEM_NAME_WEBQUERYOPEN "$WEBQueryOpen" /*WebQueryOpen formula */
#define ITEM_NAME_APPHELPFORMULA "$AppHelpFormula" /* Help doc to load */

#define ITEM_NAME_WEBFLAGS	"$WebFlags"		/* Web related flags for form or document */
#define WEBFLAG_NOTE_USEAPPLET_INBROWSER	'B'		/* use appropriate applet when serving to browser */
#define WEBFLAG_NOTE_IS_HTML		'H'		/* treat this document or form as plain HTML, do not convert styled text to HTML */
#define WEBFLAG_NOTE_CONTAINS_VIEW	'V'		/* optimization for web server: this note contains an embedded view */
#define WEBFLAG_NOTE_HTML_ALL_FLDS	'F'		/* gen'd HTML for all fields */
#define WEBFLAG_NOTE_CONTAINS_JSBUTTON	'J'	/* Generate <FORM> tag */
#define ITEM_NAME_WEBPUBLISHING	"$WebPublishing" 

/* Document note Sign/Seal item names */

#define	ITEM_NAME_NOTE_SIGNATURE "$Signature"
#define	ITEM_NAME_NOTE_SIG_PREFIX "$Sig_"	/*	Prefix for multiple signatures. */
#define	ITEM_NAME_NOTE_SEAL "$Seal"
#define	ITEM_NAME_NOTE_SEALDATA "$SealData"
#define ITEM_NAME_NOTE_SEALNAMES "SecretEncryptionKeys"
#define ITEM_NAME_NOTE_SEALUSERS "PublicEncryptionKeys"
#define	ITEM_NAME_NOTE_FORCESIGN "Sign"
#define	ITEM_NAME_NOTE_FORCESEAL "Encrypt"
#define	ITEM_NAME_NOTE_FORCEMAIL "MailOptions"
#define	ITEM_NAME_NOTE_FORCESAVE "SaveOptions"
#define	ITEM_NAME_NOTE_FORCESEALSAVED "EncryptSaved"
#define	ITEM_NAME_NOTE_MAILSAVE	"MailSaveOptions"
#define	ITEM_NAME_NOTE_FOLDERADD "FolderOptions"

/* Group expansion item and legal values */

#define	ITEM_NAME_NOTE_GROUPEXP	 "ExpandPersonalGroups"	/* For backward compatibility */
#define ITEM_NAME_NOTE_EXPANDGROUPS	 "$ExpandGroups"
#define MAIL_DONT_EXPAND_GROUPS			'0'
#define MAIL_EXPAND_LOCAL_GROUPS		'1'
#define MAIL_EXPAND_PUBLIC_GROUPS		'2'
#define MAIL_EXPAND_LOCAL_AND_PUBLIC_GROUPS	'3'

/* Search term highlights item name prefix.  An item name is 
	concatenated to this; e.g. $Highlights_Body.  */

#define ITEM_NAME_HIGHLIGHTS	"$Highlights_"

/* Import/Export document item names */

#define IMPORT_BODY_ITEM_NAME "Body"
#define IMPORT_FORM_ITEM_NAME FIELD_FORM
#define NEW_FORM_ITEM_NAME FIELD_FORM

/*	Help index note item names */

#define ITEM_OBJECT	"$Section"
#define	HELP_VIEW_NAME "(All)"
#define APP_HELP_DEFAULT_VIEW_NAME "(Help)"

/*	Help view names */

#define HELP_VIEW_TOC "Top10"		/*	Table of contents view */
#define HELP_VIEW_MSG "MSG"		/*	Messages view */
#define HELP_VIEW_ATFUNC "REF"	/*	@Functions view */
#define HELP_VIEW_INDEX "IDX"	/*	Index view */
#define HELP_VIEW_NEWS "NEWS" 	/* Release Notes view */
#define HELP_VIEW_V3CMD "CLASSIC" 	/* V3 Menu Command Equivalents */

/* Help navigator names */

#define HELP_NAV_HOW "Help Topics - How"
#define HELP_NAV_INDEX "Help Topics - Index"
#define HELP_NAV_MSG "Help Topics - Trouble"
#define HELP_NAV_ATFUNC "Help Topics - Tell Me"
#define HELP_NAV_KBD	"Help Topics - Tell Me"

/*	Notes Help Template String */
#define HELP_TEMPLATE_STRING	"NotesHelp"

/*	Catalog form names */

#define NOTEFILE_FORM_NAME			"Notefile"
#define CONNECTION_FORM_NAME		"Connection"

/*	Catalog view names */
#define	CATALOG_VIEW_REPLICA_ID "Databases by _Replica ID"
#define CATALOG_VIEW_CATEGORY	"Databases by _Category"
#define CATALOG_VIEW_MULTIDBBIT	"($MultiDbIndex)"

/*	Catalog document note item names */

#define CATALOG_ITEM_SERVER		 	"Server"
#define CATALOG_ITEM_REMOTE_SERVER 	"RemoteServer"
#define CATALOG_ITEM_PATHNAME 		"Pathname"
#define CATALOG_ITEM_TITLE  		"Title"
#define CATALOG_ITEM_REPLICAID  	"ReplicaID"
#define CATALOG_ITEM_POLICY_DATE 	"PolicyDate"
#define CATALOG_ITEM_LICENSEID		"LicenseID"
#define CATALOG_ITEM_MANAGERS		"Managers"
#define CATALOG_ITEM_BODY			"Body"
#define CATALOG_ITEM_VIEW_INDEX		"View"
#define CATALOG_ITEM_CATEGORY1		"Category1"
#define CATALOG_ITEM_CATEGORY2		"Category2"
#define CATALOG_ITEM_CATEGORY3		"Category3"
#define CATALOG_ITEM_CATEGORY4		"Category4"
#define CATALOG_ITEM_CATEGORY5		"Category5"
#define CATALOG_ITEM_CAT			MAIL_CATEGORIES_ITEM
#define CATALOG_ITEM_FULLNAME		"FullName"
#define CATALOG_ITEM_META_TITLE			"Title"
#define CATALOG_ITEM_META_CREATOR		"Creator"
#define CATALOG_ITEM_META_DESCRIPTION	"Description"
#define CATALOG_ITEM_META_TYPE			"MetaType"
#define CATALOG_ITEM_META_IDENTIFIER	"URL"
#define CATALOG_ITEM_META_CREATION_DATE	"CreationDate"
#define CATALOG_ITEM_META_CATEGORIES	"Categories"

/*	Multi DB searching document forms, item names, and item values */

#define MULTIDB_FORM_CONFIG			"ConfigurationForm"
#define MULTIDB_FORM_ENTRY			"Database"
#define MULTIDB_ITEM_ACL			"ACL"
#define MULTIDB_ITEM_CATEGORIES		"DatabaseCategories"
#define MULTIDB_ITEM_CONFIGLINK		"ConfigLink"
#define MULTIDB_ITEM_DOMAIN			"Domain"
#define MULTIDB_ITEM_INDEXOPTIONS	"IndexOptions"
#define MULTIDB_ITEM_PATHNAME		"Pathname"
#define MULTIDB_ITEM_REPLICAID		"ReplicaID"
#define MULTIDB_ITEM_SCOPE			"Scope"
#define MULTIDB_ITEM_SERVER			"Server"
#define MULTIDB_ITEM_TITLE			"Title"
#define MULTIDB_ITEM_VIEWCHOICE		"DbViews"
#define MULTIDB_ITEM_VIEWLIST		"DatabaseViews"
#define MULTIDB_INDEX_NONE			"0"
#define MULTIDB_INDEX_SUMMARY		"1"
#define MULTIDB_INDEX_FULLNOTE		"2"
#define MULTIDB_INDEX_ATTACHMENT	"3"
#define MULTIDB_SCOPE_DATABASE		"0"
#define MULTIDB_SCOPE_DIRECTORY		"1"
#define MULTIDB_SCOPE_SERVER		"2"
#define MULTIDB_SCOPE_DOMAIN		"3"
#define	MULTIDB_VIEW_REPLICAID 		"$ReplicaID"

/*	Library document note item names */

#define LIBRARY_ITEM_AUTHOR			"Author"
#define LIBRARY_ITEM_SERVER		 	"Server"
#define LIBRARY_ITEM_PATHNAME 		"Pathname"
#define LIBRARY_ITEM_TITLE  		"Title"
#define LIBRARY_ITEM_REPLICAID  	"ReplicaID"
#define LIBRARY_ITEM_ABSTRACT		"Abstract"
#define LIBRARY_PATHNAME			"LibraryPathName"
#define LIBRARY_TITLE				"LibraryTitle"
#define LIBRARY_SENDTO				"SendTo"
#define LIBRARY_LIBRARIAN			"Librarian"

/* Library Form Names */
#define LIBRARIAN_FORM_NAME			"Librarian"

/* Library View Names */
#define LIBRARY_REPID_VIEW		   	"($RepID)"	
#define LIBRARY_LIBRARIAN_VIEW		"($Librarians)"	

/* Disk directory search item names and values */

#define DBDIR_PATH_ITEM 		"$Path"		 		/* Path name */
#define DBDIR_TYPE_ITEM 		"$Type"				/* Type item */
#define DBDIR_TYPE_ITEM_DIRECTORY "$DIR"			/* Directory type name */
#define DBDIR_TYPE_ITEM_NOTEFILE "$NOTEFILE"		/* Notefile type name */
#define DBDIR_TYPE_ITEM_OLDNOTEFILE "$OLDNOTEFILE"
#define DBDIR_INFO_ITEM 		"$Info"				/* Info item */
#define DBDIR_LENGTH_ITEM		"$Length"
#define DBDIR_MODIFIED_ITEM		"$Modified"
#define DBDIR_PROPERTIES_ITEM 	"$Properties"
#define DBDIR_LINK_ITEM 		"$LinkInfo"
#define DBDIR_DIRECTORY_LINK 	"$DIRLINK"			/* Directory Link */
#define DBDIR_DATABASE_LINK 	"$DBLINK"			/* Database Link */
#define DBDIR_DBOPTIONS_ITEM 	"$DBOPTIONS"		/* Database Options */
#define DBDIR_DBVERSIONS_ITEM 	"$DBVERSIONS"		/* Database Major and Minor versions */
#define DBDIR_DBCREATED_ITEM 	"$DBCREATED"		/* Database Created date	*/
#define DBDIR_LASTFIXUP_ITEM	"$LASTFIXUP"		/* Last database fixup time	*/
#define DBDIR_QUOTALIMIT_ITEM	"$QUOTALIMIT"		/* Database quota limit	*/
#define DBDIR_QUOTAWARNING_ITEM	"$QUOTAWARNING"		/* Database quota warning	*/
#define DBDIR_MAXDBSIZE_ITEM	"$MAXDBSIZE"		/* Database MAximum Size - 1Gb, 2GB, 3GB, 4GB	*/
#define DBDIR_PHYSICALPATH_ITEM	"$PHYSICALPATH"		/* Physical file path (OS level path)	*/
#define DBDIR_ISLOGGED_ITEM		"$ISLOGGED"			/* Is the db logged? */
#define DBDIR_LENGTH2_ITEM		"$Length2"			/* File Size as NSFDISKPOS */

/* Form names for log database. */

#define	LOG_EVENT_FORM 		"Events"
#define	LOG_REPLICA_FORM 	"Replication"
#define	LOG_MAIL_FORM 		"Mail Routing"
#define	LOG_SESSION_FORM 	"Session"
#define LOG_USAGE_FORM		"Activity"
#define LOG_SIZE_FORM		"Size"
#define LOG_PHONE_FORM		"Phone Call"
#define LOG_PHONE_IN_FORM	"Phone Call - Incoming"
#define LOG_PHONE_OUT_FORM	"Phone Call - Outgoing"
#define	LOG_PT_FORM 		"Passthru Connection"
#define	LOG_OBJSTORE_USAGE_FORM 	"ObjStoreUsageForm"

/* View names for log database. */

#define	LOG_OBJSTORE_USAGE_VIEW 		"ObjStoreUsageView"
#define	LOG_MAIL_ROUTING_EVENTS_VIEW	"MailRoutingEvents"

/*	Item names used by the log facility itself or commonly used
	by different packages that call the log facility. */

#define LOG_ITEM_STARTTIME			"StartTime"
#define LOG_ITEM_ENDTIME			"FinishTime"
#define LOG_ITEM_BODY				"Body"
#define LOG_ITEM_SERVER 			"Server"
#define LOG_ITEM_PORT				"Port"
#define LOG_ITEM_EVENTS				"Events"
#define LOG_ITEM_PATHNAME			"Pathname"
#define LOG_ITEM_TITLE				"Title"
#define LOG_ITEM_CAT				MAIL_CATEGORIES_ITEM
#define LOG_ITEM_BYTESIN			"BytesIn"
#define LOG_ITEM_BYTESOUT			"BytesOut"

/* Item names for replicator notes in log file. */

#define REPLICA_ITEM_SOURCE_SERVER	"SourceServer"
#define REPLICA_ITEM_INITIATED_BY	"InitiatedBy"

/* Item names for session notes in log file. */

#define SESSION_ITEM_USERNAME		"UserName"
#define SESSION_ITEM_READS			"Reads"
#define SESSION_ITEM_WRITES			"Writes"
#define SESSION_ITEM_SENT_FROM		"SentFromServer"
#define SESSION_ITEM_SENT_TO		"SentToServer"
#define SESSION_ITEM_TRANSACTIONS	"Transactions"

/* Item names for escrow log */

#define	ESCROW_SENDTO				"Escrow Agent"

#define	ESCROW_USER					"User"
#define	ESCROW_SERVER				"Server"
#define	ESCROW_CERTIFIER			"Certifier"

#define	ESCROW_LOCATION_ITEM		"Location"
#define	ESCROW_COMMENT_ITEM			"Comment"
	
/* Item names for database activity note in log file */

#define ACTIVITY_ITEM_MANAGERS		"Managers"
#define ACTIVITY_ITEM_VIEWTITLES	"ViewTitles"
#define ACTIVITY_ITEM_VIEWSIZES		"ViewSizes"
#define ACTIVITY_ITEM_DISKSPACE		"DiskSpace"
#define ACTIVITY_ITEM_DISKUSAGE		"DiskUsage"
#define ACTIVITY_ITEM_PERIOD		"Period"
#define ACTIVITY_ITEM_PERIOD_USES	"PeriodUses"
#define ACTIVITY_ITEM_PERIOD_READS	"PeriodReads"
#define ACTIVITY_ITEM_PERIOD_WRITES	"PeriodWrites"
#define ACTIVITY_ITEM_DAY_USES		"DayUses"
#define ACTIVITY_ITEM_DAY_READS		"DayReads"
#define ACTIVITY_ITEM_DAY_WRITES	"DayWrites"
#define ACTIVITY_ITEM_WEEK_USES		"WeekUses"
#define ACTIVITY_ITEM_WEEK_READS	"WeekReads"
#define ACTIVITY_ITEM_WEEK_WRITES	"WeekWrites"
#define ACTIVITY_ITEM_MONTH_USES	"MonthUses"
#define ACTIVITY_ITEM_MONTH_READS	"MonthReads"
#define ACTIVITY_ITEM_MONTH_WRITES	"MonthWrites"

/* Item names for unet notes in log file. */
#define UNIXNET_ITEM_BODY	"UnixBody"

#if 0

/* Address Book - "X400Server" form item names */

#define MAIL_X400_SERVER_FORM "Server"				/* Form and type name */
#define MAIL_X400_SERVERNAME_ITEM "ServerName"		/* X400 MTA name */
#define MAIL_X400_GLOBAL_DOMAIN_ITEM "GlobalDomain" /* Global domain identifier */ 
#define MAIL_X400_COUNTRY_ITEM "Country"			/* Country name */
#define MAIL_X400_ADMD_ITEM "ADMD"					/* Administration Management Domain name*/
#define MAIL_X400_PRMD_ITEM "Domain"				/* Private Domain name */
#define MAIL_X400_CREDENTIALS_ITEM "Credentials"	/* MTA credentials */
#define MAIL_X400_SUPP_APP_CONTEXTS_ITEM "SupportedApplicationsContext"	/* Supported app. contexts */
#define MAIL_X400_DEL_CONTENT_LENGTH_ITEM "DeliveryContentLength" 	/* Delivery content length */
#define MAIL_X400_DEL_CONTENT_TYPE_ITEM "DeliveryContentTypes"	 	/* Delivery content types */
#define MAIL_X400_PSEL_ITEM "PSEL"					/* Presentation selector */
#define MAIL_X400_SSEL_ITEM "SSEL"					/* Session selector */
#define MAIL_X400_TSEL_ITEM "TSEL"					/* Transport selector */
#define MAIL_X400_NADDRESSES_ITEM "NAddresses"		/* Network addresses */

#endif



/*	Public Queue Names */

#define	TASK_QUEUE_PREFIX	"MQ$"			/* Prepended to "addin" task */
											/* name to form task's queue name */

#define SERVER_QUEUE_NAME	"_SERVER"						/* DB Server */
#define REPL_QUEUE_NAME		TASK_QUEUE_PREFIX"REPLICATOR"	/* Replicator */
#define ROUTER_QUEUE_NAME	TASK_QUEUE_PREFIX"ROUTER"		/* Mail Router */
#define UPDATE_QUEUE_NAME 	TASK_QUEUE_PREFIX"INDEXER"		/* Index views & full text process */
#define LOGIN_QUEUE_NAME 	TASK_QUEUE_PREFIX"LOGIN"		/* Login Process */
#define EVENT_QUEUE_NAME	TASK_QUEUE_PREFIX"EVENT"		/* Event process */
#define REPORT_QUEUE_NAME	TASK_QUEUE_PREFIX"REPORTER"		/* Report process */
#define CLREPL_QUEUE_NAME	TASK_QUEUE_PREFIX"CLREPL"		/* Cluster Replicator */
#define FIXUP_QUEUE_NAME	TASK_QUEUE_PREFIX"FIXUP"		/* Fixup */
#define COLLECT_QUEUE_NAME  TASK_QUEUE_PREFIX"COLLECTOR"	/* Collector*/
#define NOI_QUEUE_NAME		TASK_QUEUE_PREFIX"DIIOP"		/* NOI Process */
#define ALARM_QUEUE_NAME	TASK_QUEUE_PREFIX"ALARMS"		/* Alarms Cache daemon */
#define MONITOR_QUEUE_NAME	TASK_QUEUE_PREFIX"MONITOR"		/* Monitor */
#define MONALARM_QUEUE_NAME	TASK_QUEUE_PREFIX"MONITORALARM"		/* Monitor */
#define APDAEMON_REQ_QUEUE	TASK_QUEUE_PREFIX"APDAEMONREQ"				/* Admin Panel Daemon (Request Queue) */
#define APDAEMON_FILERES_QUEUE	TASK_QUEUE_PREFIX"APDAEMONFILERES"		/* Admin Panel Daemon (File Response Queue) */
#define APDAEMON_SERVRES_QUEUE	TASK_QUEUE_PREFIX"APDAEMONSERVRES"		/* Admin Panel Daemon (Server Response Queue) */



/*  Names for server access lists and other stuff from Name & address book*/

#define SERVER_TITLE_NAME			"SERVER_TITLE"
#define ALLOW_ACCESS_NAME			"ALLOW_ACCESS"
#define DENY_ACCESS_NAME		  	"DENY_ACCESS"
#define CREATE_FILE_ACCESS_NAME		"CREATE_FILE_ACCESS"
#define CREATE_REPLICA_ACCESS_NAME	"CREATE_REPLICA_ACCESS"
#define ADMIN_ACCESS_NAME			"ADMIN_ACCESS"
#define ALLOW_PASSTHRU_TARGET_NAME	"ALLOW_PASSTHRU_TARGETS"
#define ALLOW_PASSTHRU_CLIENT_NAME	"ALLOW_PASSTHRU_CLIENTS"
#define ALLOW_PASSTHRU_CALLER_NAME	"ALLOW_PASSTHRU_CALLERS"
#define ALLOW_PASSTHRU_ACCESS_NAME	"ALLOW_PASSTHRU_ACCESS"
#define ALLOW_RESTRICTED_LOTUSCRIPT_NAME	"ALLOW_RESTRICTED_LOTUSSCRIPT"
#define ALLOW_UNRESTRICTED_LOTUSCRIPT_NAME	"ALLOW_UNRESTRICTED_LOTUSSCRIPT"
#define ALLOW_MONITORS_NAME			"ALLOW_MONITORS"
#define DENY_MONITORS_NAME		  	"DENY_MONITORS"

/*	Names for folder pane. */

#define CATEGORIES_AS_FOLDERS		"CategoriesAsFolders"

/*	Location information */

#define LOCATION_DEFAULT	"Location"
#define LOCATION_TYPE		"LocationType"
#define LOCATION_TRAVELPROMPT "TravelPrompt"
#define LOCATION_FORMTYPE	"Location"
#define LOCATION_VIEW		"($Locations)"
#define LOCATION_NAME		"Name"
#define LOCATION_SOURCE		"Source"
#define LOCATION_USERID		"UserID"
#define LOCATION_TIMEZONE	"TimeZone"
#define LOCATION_R5TIMEZONE "R5TimeZone"
#define LOCATION_USEOSTZ	"UseOSTZ"
#define LOCATION_DST		"DST"
#define LOCATION_DOMAIN		"Domain"
#define LOCATION_MAILSERVER	"MailServer"
#define LOCATION_DIRSERVER	"DirectoryServer"
#define LOCATION_MAILFILE	"MailFile"
#define LOCATION_MAILFILE_LASTSEQ	"$MailFileSeq"
#define LOCATION_DEFPASSTHRU "DefaultPassthruServer"
#define LOCATION_OUTSIDELINE "OutsideLine"
#define LOCATION_CARDPREFIX	"CallPre"	/* Number to dial to get carriers dial tone (10ATT or 1800...) */
#define LOCATION_CARDSUFFIX	"Suffix"	/* Number to identify user;s account (i.e. User's Home Phone + PIN) */
#define LOCATION_INTERNATIONALPREFIX	"InternationalPrefix"
#define LOCATION_LONGDISTANCEPREFIX		"LongDistancePrefix"
#define LOCATION_COUNTRY	"Country"
#define LOCATION_AREACODE	"AreaCode"
#define LOCATION_MAILTYPE	"MailType"
#define LOCATION_MAILTHRESHOLD		"MailThreshold"
#define LOCATION_TCPNAMESERVER		"TcpNameServer"
#define LOCATION_TCPNAMESERVERHOST	"TcpNameServerHost"
#define LOCATION_SCHEDULE			"Enabled"
#define LOCATION_PRIORITYSCHEDULE	"Enabled_HI"
#define LOCATION_USESPRIORITYSCHEDULE	"HiPriorityReplication"
#define LOCATION_NDSNAMESERVER			"NDSNameServer"
#define LOCATION_NDSNAMESERVERADDRESS	"NDSNameServerAddress"
#define LOCATION_NETBIOSNAMESERVER		"NetBIOSNameServer"
#define LOCATION_SOCKSPROXY 			"Proxy_SOCKs"
#define LOCATION_SSLPROXY 				"Proxy_SSL"
#define LOCATION_NOTESHTTPPROXY			"Proxy_NotesHttp"
#define LOCATION_IMAGES		"Images"
#define LOCATION_USERNAME_FLAG 			"UserNameFlag"	/* Primary/Alternate UserName Mode. 0 = Primary, 1 = Alternate */

/*	The following field is only meaningful if the user has workstation based
	mail, if they do not, then it is assumed that server addressing (i.e.
	resolution of the names, and allowing the use of server N&A books when
	addressing mail, is always available).  If the user is using a local
	mail file, but has network connectivity, then they may want to allow
	the use of server addressing.  If the user has no connectivity, then'
	this should be assumed to be off - regardless of its setting.  DWC */

#define LOCATION_SERVERADDRESSING		"MailAddressing"

		/* InterNotes/Web Location Items */

#define LOCATION_INTERNOTES					"InterNotes"
#define LOCATION_WEBLOCALDB					"WebDbName"
#define LOCATION_WEBSERVERDB				"WebDbName"
#define LOCATION_WEBRETRIEVERLOCATION		"WebLocation"
#define LOCATION_WEBUPDATECACHE				"WebUpdateCache"
#define LOCATION_WEBRETRIEVERLOGGING		"WebLogLevel"
#define LOCATION_WEBRETRIEVER				"WebRetriever"
#define LOCATION_WEBRETRIEVERS				"WebRetrievers"
#define LOCATION_WEBRETRIEVERPATH			"WebRetrieverPath"
#define LOCATION_WEBHTTPPROXY				"Proxy_HTTP"
#define LOCATION_WEBFTPPROXY				"Proxy_FTP"
#define LOCATION_WEBGOPHERPROXY				"Proxy_Gopher"
#define LOCATION_WEBNOPROXY					"No_Proxy"

#define LOCATION_SSLSITECERT				"SSLSiteCerts"
#define LOCATION_SSLEXPIREDCERTS			"SSLExpiredCerts"
#define LOCATION_SSLPROTOCOLVER				"SSLProtocolVersion"
#define LOCATION_SSLSENDCERTS				"SSLSendCertificates"

		/* Java Location Items */

#define LOCATION_JAVASECUREDOMAINLIST		"JavaSecureDomain"
#define LOCATION_JAVAALLOWINSECURE			"JavaAllowInSecureDomain"
#define LOCATION_JAVAALLOWINOTHER			"JavaAllowInOtherDomains"
#define LOCATION_JAVATRUSTPROXY				"JavaTrustHTTPProxy"

		/* Internet Mail Location Items */

#define LOCATION_IMAIL_PROTOCOL				"MailServerProtocol"
#define LOCATION_IMAIL_USER					"ImailUsername"
#define LOCATION_IMAIL_PASSWORD				"ImailPassword"
#define LOCATION_IMAIL_SERVERLIST			"ImailServer"
#define LOCATION_IMAIL_SMTP_SERVER			"ImailSMTPServer"
#define LOCATION_IMAIL_PORT					"ImailPort"
#define LOCATION_IMAIL_USE_SSL				"ImailUseSSL"
#define LOCATION_IMAIL_ADDRESS				"ImailAddress"
#define LOCATION_IMAIL_POP_DEL_MAIL			"PopDeleteMail"
#define LOCATION_IMAIL_SMTP_ROUTE			"SMTPRoute"
#define LOCATION_IMAIL_INTERNET_DOMAIN		"InternetDomain"
#define LOCATION_IMAIL_ATTACH_ENCODE		"SMTPEncodingScheme"
#define LOCATION_IMAIL_MAC_ATTACH_ENCODE	"SMTPMacAttachConvertOption"
#define LOCATION_IMAIL_MSGFORMAT			"MessageFormat"

		/* Admin Client Location Items */

#define LOCATION_ADMIN_MONITOR_REMENABLE	"EnableRemoteMonitor"
#define LOCATION_ADMIN_MONITOR_REMSERVER	"RemoteMonitorServer"
#define LOCATION_ADMIN_MONITOR_COLLINTER	"DataCollectionInterval"
#define LOCATION_ADMIN_MONITOR_AUTOACTIVATE	"AutoActivateMonitor"
#define LOCATION_ADMIN_FAVORITE_SERVERS		"AdminFavoriteServers"


/*	Personal database names... */
#define LOCATION_BOOKMARK_DB		"BookmarkDb"
#define LOCATION_SUBSCRIPTION_DB	"HeadlineDb"


/* Prior to build 125, in the location record, the ports that were listed
	were those that were enabled.  Beginning in build 125, the ports that
	are listed (internally by a different item) are those that are disabled.
	The location form will however present the enabled ports by selecting the
	ports which are not specifed in the disabled item.  When saved, it is
	inverted back to mean the ports that are disabled.  In this manner,
	newly added ports will be enabled for all locations (by default). */

#define LOCATION_AUTONETCONFIG				"AutoNetConfig"
#define LOCATION_PORTS			"PortName"	  		/* Prior to 125 */
#define LOCATION_DISABLEDPORTS	"DisabledPorts"		/* 125 and later */
#define LOCATION_NAMELOOKUPPREF	"NameLookupPref"
#define LOCATION_EXHAUSTIVENAMELOOKUP	"ExhaustiveNameLookup"
#define LOCATION_MAIL_ADDR_FILE "MailAddressFile"	/* Last N&A Book used at this location */
#define LOCATION_VERSION	"$LocationVersion"
#define LOCATION_BCASELIST	"$BCaseList"
#define LOCATION_DIALING_SERVERS "$DialingServers"
#define LOCATION_DIALING_RULES   "$DialingRules"
#define LOCATION_STACKFILENAMES	"$StackFileNames"	/* Filename of topmost
														replica icon at this
														location for this
														'stack', */
/*	The V5 list is a parallel list of a database and the last replica.  It
	is independent of the V4 list to avoid differnces that may be necessary
	between the 2 lists. */

#define LOCATION_LASTFILENAMES	"$LastFileNames"	/* Filename of topmost
														replica icon at this
														location for this
														'stack', */
#define LOCATION_LASTREPLICAIDS "$LastReplicaIDs"	/* Replica ID of topmost
														replica icon at this
														location for this
														'stack', */
#define LOCATION_LASTACCESSED	"$LastAccessedDB"	/* Time/Date of last use
														of this DB. */

#define LOCATION_SAVED_SERVER	"$SavedServers"		/* Server name */
#define LOCATION_SAVED_PORT		"$SavedPorts"		/* Port server reached on */
#define LOCATION_SAVED_ADDRESS	"$SavedAddresses"	/* Server address on this port */
#define LOCATION_SAVED_DATE		"$SavedDate"		/* Julian Date */
#define LOCATION_SAVED_LAST_TRIED_DATE	"$SavedTriedDate"	/* Julian Date */
#define LOCATION_RLAN_IDLE_TIMEOUT	"RLANIdleTimeout"	/* timeout for RLAN hangup */

/* The following field was introduced in build 133 so that new icons added
	to the desktop get bubbled to the top of the stack if appropriate.  New
	icons should be at the top of the stack if:

	the DB icon is mew, is for a server DB, the location has a LAN port and
		the current top of the stack is a local database.
	the DB icon is mew, is for a local DB, the location has no LAN port and
		the current top of the stack is a server database.
*/
#define LOCATION_STACKCHECKED		"$StackChecked"		

/* If this field is set, this location can be changed for existing users
	with information from the person record and setup profile records for this
	user on their home server */

#define	LOCATION_ACCEPTUPDATES		"AcceptUpdates"

/*	Catalog server - used for Domain Search */

#define CATALOG_FILE_V5				"catalog.nsf"
#define LOCATION_CATALOGSERVER		"CatalogServer"
#define DOMAINQUERY_FORM_NAME		"DomainQuery"
#define LOCAL_DOMAIN_CATALOG_SERVERS "LocalDomainCatalogServers"
#define DOMAIN_INDEXER_SCOPE		"CatalogIndexerScope"
#define DOMAIN_CATALOG_FIELD		"CatalogType"
#define DOMAIN_CATALOG_NAME			"Domain Catalog"
#define CATALOG_SERVERLOOKUPITEMCOUNT	2
#define CATALOG_SERVERLOOKUPITEMS		"CatalogType\0Administrator\0"

#define BOOKMARK_DBNAME				"bookmark.nsf"
#define BOOKMARK_FINDDB_FORMNAME	"DatabaseSearch"

/*	Fields used to store the list of folders into which a document is to be
	saved.  Note that @Command([ChooseFolders]) reads and writes these fields,
	so you do not normally need to manipulate them in a document.

	Note also that to a user, there are only two sets of folders: Shared and
	Private, with the distinction that some Private folders are stored in the
	databse, and some on the workstation in the desktop file (when the user
	cannot store them in the database due to access restrictions). */

#define FOLDERS_SHARED			"$Folders"			  	/*	List of shared folders. */
#define FOLDERS_PRIVATE			"$PrivateFolders"	  	/*	List of private folders (in database). */
#define FOLDERS_PRIVATE_LOCAL	"$LocalPrivateFolders"	/*	List of private folders (in desktop). */

/* Item names of fields in Mail template: */

#define MAILREPORT_ITEM	"$DeliveryReport"		/* TBD */

/* Item Name of view format note item */

#define ITEM_NAME_VIEW_FORMATNOTE	"$FormatNote"	/* UNID of note views design was originally copied from */

/*	Standard folder names. */

#define FOLDER_INBOX			"($Inbox)"
#define FOLDER_DRAFTS			"($Drafts)"
#define FOLDER_SENT				"($Sent)"
#define FOLDER_ALL				"($All)"
#define FOLDER_CALENDAR			"($Calendar)"
#define FOLDER_TODO				"($ToDo)"
#define FOLDER_MEETINGS			"($Meetings)"
#define FOLDER_TRASH			"($Trash)"
#define FOLDER_PROFILE			"($Profiles)"
#define FOLDER_ALARMS			"($Alarms)"

#define FOLDER_INBOX_NAME		"$Inbox"
#define FOLDER_DRAFTS_NAME		"$Drafts"
#define FOLDER_SENT_NAME		"$Sent"
#define FOLDER_ALL_MAIL			"$All"
#define FOLDER_CALENDAR_NAME	"$Calendar"
#define FOLDER_TODO_NAME		"$ToDo"
#define FOLDER_MEETINGS_NAME	"$Meetings"
#define FOLDER_TRASH_NAME		"$Trash"
#define FOLDER_PROFILE_NAME		"$Profiles"

/*	Site database view name */

#define SITE_DBLOOKUP_VIEW		"($DbLookup)"

/*	Router Shared Mail Object Store names */

#define SHARED_MAIL_NAME			"SHARED_MAIL"				/* config variable for shared mail */
#define ROUTER_OBJECT_STORE_NAME	"mailobj.nsf"				/* object store link file used by the router */
#define ROUTER_OBJECT_STORE_DBNAME	"mailobj1.nsf"				/* object store database created by the router */



/* Cluster Name and Address Book lookup definitions */

#define CLUSTERS_CLUSTER_VIEW_1		"1\\$Clusters"
#define CLUSTERS_CLUSTER_VIEW		"$Clusters"
#define CLUSTERS_CLUSTER_ITEM_NAME	"ClusterName"	
#define CLUSTERS_CLUSTER_ITEM		0

#define CLUSTERS_SERVERS_VIEW_1		"1\\$Servers"
#define CLUSTERS_SERVERS_VIEW		"$Servers"
#define CLUSTERS_SERVER_ITEM_NAME	"ServerName"	
#define CLUSTERS_SERVER_ITEM		0

#define CLUSTERS_CLREPID_ITEM_NAME	"ClRepID"
#define CLUSTERS_CLREPID_ITEM		0

/* Cluster Database Directory definitions */

#define CLUSTERS_SERVER_VIEW		"$Server"
#define CLUSTERS_PATHNAME_VIEW		"$Pathname"
#define CLUSTERS_REPID_VIEW			"$ReplicaID"
#define CLUSTERS_DIRTITLE_VIEW      "$DirectoryTitle"

#define CLUSTERS_SERVER_FIELD		"Server"
#define CLUSTERS_REPID_FIELD		"ReplicaID"
#define CLUSTERS_PATHNAME_FIELD		"PathName"
#define CLUSTERS_TITLE_FIELD  		"Title"
#define CLUSTERS_OUTOFSERVICE_FIELD	"DatabaseOutOfService"
#define CLUSTERS_REPL_FIELD			"ClusterReplicate"
#define CLUSTERS_FAILBYPATH_FIELD	"OnlyFailoverbyPathname"
#define CLUSTERS_DELETE_FIELD		"MarkedForDelete"

#define CLUSTERS_DBDIR_NAME				"cldbdir.nsf"
#define CLUSTERS_DBDIR_TEMPLATE_NAME	"cldbdir4.ntf"

/* Values for CLUSTERS_OUTOFSERVICE_FIELD */
#define CLUSTERS_IN_SERVICE 		"0"
#define CLUSTERS_OUT_OF_SERVICE 	"1"

/* Values for CLUSTERS_CLREPL_FIELD */
#define CLUSTERS_CLUSTER_REPLICATE_ON	"1"
#define CLUSTERS_CLUSTER_REPLICATE_OFF	"0"


/* User registration document and DUS (Domino Upgrade Service) field definitions */

/* Fields related to the basics user registration dialog pane */
#define USERREG_FULLNAME_ITEM 			"FullName"
#define USERREG_FIRSTNAME_ITEM			"FirstName"
#define USERREG_LASTNAME_ITEM			"LastName"
#define USERREG_MIDDLEINITIAL_ITEM		"MiddleInitial"
#define USERREG_SHORTNAME_ITEM			"ShortName"
#define USERREG_PASSWORD_ITEM			"UserPassword"

/* Comment field in the 'Other' user registration dialog pane */
#define USERREG_COMMENT_ITEM  		"Comment"

/* DUS related fields */
#define USERREG_DUSUSERID_ITEM	 	  	"NUAUserID"
#define USERREG_DUSNAME_ITEM		  	"NUAName"
#define USERREG_DUSALIASNAMES_ITEM 	  	"DUSFullNameAliases"
#define USERREG_DUSMAILFILE_ITEM	   	"NUAMailFile"
#define USERREG_DUSGROUPID_ITEM		  	"GroupID"
#define USERREG_DUSPARENTGROUPS_ITEM  	"ParentGroups"		/* for groups with parent groups */
#define USERREG_PERSONNOTEHANDLE_ITEM 	"PersonNoteHandle"	/* note handle to new person note in NAB created by user reg */

/* Advance info item fields */
#define USERREG_DUSADVANCEDINFO_ITEM 	"NUAAdvancedInfo"	/*	The DUS must set the DUS_ADVANCEDINFO_ITEM below to "1" if
																 any of the USERREG_XXX fields below are set by the DUS */
#define USERREG_STORAGE_ITEM			"MessageStorage"	/* Specifies how user wants to store the mail.  See USERREG_STORAGE_XXX below */
#define USERREG_STORAGE_UNKNOWN					0xFF		/* can't find storage type */
#define USERREG_STORAGE_CDRECORDS				0 			/* Store as cd records only */
#define USERREG_STORAGE_CDRECORDS_AND_RFC822	1 			/* Store as cd records & attachment of original message */
#define USERREG_STORAGE_RFC822					2 			/* Store original message as attachment (no cdrecords) */
#define USERREG_STORAGE_NATIVE_MIME				3			/* Store headers & parts as separate items (without conversion) or CD */
#define USERREG_STORAGE_NATIVE_MIME_ONLY		4			/* Store headers & parts as separate items (without conversion) only */

#define USERREG_PERSONAL_TITLE			"Title"			/* keyword choices are Mr., Ms., Mrs., Miss, Dr. or Prof. */
#define USERREG_GENERATION_QUALIFIER	"Suffix"		/* keyword choices are I, II, III, Jr., or Sr. */

#define USERREG_HOME_STREETADDRESS		"StreetAddress"
#define USERREG_HOME_CITY				"City"
#define USERREG_HOME_STATE				"State"
#define USERREG_HOME_ZIP				"Zip"
#define USERREG_HOME_COUNTRY			"Country"
#define USERREG_PHONENUMBER_ITEM		"PhoneNumber"
#define USERREG_HOME_FAX				"HomeFAXPhoneNumber"
#define USERREG_SPOUSE					"Spouse"
#define USERREG_CHILDREN				"Children"

#define USERREG_COMPANYNAME_ITEM		"CompanyName"
#define USERREG_JOB_TITLE				"JobTitle"
#define USERREG_DEPARTMENT_ITEM			"Department"
#define USERREG_MANAGER					"Manager"
#define USERREG_OFFICEPHONE_ITEM		"OfficePhoneNumber"
#define USERREG_CELL_PHONE			  	"CellPhoneNumber"
#define USERREG_PAGER					"PhoneNumber_6"
#define	USERREG_OFFICE_FAX				"OfficeFAXPhoneNumber"
#define USERREG_ASSISTANT				"Assistant"
#define USERREG_OFFICE_STREETADDRESS	"OfficeStreetAddress"
#define USERREG_OFFICE_CITY				"OfficeCity"
#define USERREG_OFFICE_STATE			"OfficeState"
#define USERREG_OFFICE_ZIP				"OfficeZip"
#define USERREG_OFFICE_COUNTRY			"OfficeCountry"
#define USERREG_OFFICE_NUMBER			"OfficeNumber"
#define USERREG_EMPLOYEEID_ITEM			"EmployeeID"

#define USERREG_ENCRYPT_INCOMING_MAIL	"EncryptIncomingMail" /* keyword choices are "Yes" | "1" or "No" | "0" */
#define USERREG_X400_ADDRESS			"x400Address"
#define USERREG_WEB_SITE				"WebSite"
#define USERREG_CALENDARDOMAIN_ITEM		"CalendarDomain" /* User's calendar domain override */
/* END of User registration document and DUS field definitions */


/*	Last specified path and username for alternate mail logon dialog. */

#define ALT_MAIL_LAST_PATH			"AltMailLastPath"
#define ALT_MAIL_LAST_NAME			"AltMailLastName"

/*	Convert Utility Constants. */

#define ITEM_NAME_CONVERT_FORM	FIELD_FORM
#define ITEM_NAME_CONVERT_DATE	"ConvertedDate"
#define ITEM_NAME_HIDDEN_DOC	"HiddenDocument"

/*	Names stored as UNKs if a note has rarely used item names. */

#define	RARELY_USED_NAME		"$RarelyUsedName"
#define	RARELY_USED_TABLE		"$RarelyUsedTable"

#define AGENT_HSCRIPT_ITEM		"$AgentHScript"
#define AGENT_HSCRIPTOBJ_ITEM	"$AgentHScript_O"

/*	Local schedule retrieval defintions */

#define	LOCSCHED_FORM_NAME		"LocalSchedSettings"
#define LOCSCHED_PROFILE_NAME	"LocalSchedSettings"

/*	Fields in local schedule database (busytime) for local 
	schedule synchronization via replicator page. */


#define	ITEM_LOCSCHED_LIST			"LocalSchedList"
#define ITEM_LOCSCHED_DAYSTOFETCH	"LocalSchedDaysToFetch"
#define ITEM_LOCSCHED_SUPPRESS		"LocalSchedSuppressMinutes"

/* OLE "special" Items used for ActiveDoc/RichText rendering */

#define OLE_ITEM_OLEOBJFIELD			"$OLEObjField"
#define OLE_ITEM_OLEOBJPROGID			"$OLEObjProgID"
#define OLE_ITEM_OLEOBJRICHTEXTFIELD	"$OLEObjRichTextField"

/* Enables any OLE object to be in-place activated in preview pane mode.  Used
	to activate OLE controls like WEB Browser */
#define OLE_PREVIEW_ACTIVATE			"$OLEPreviewActivate"

/*Site Database design and item names*/
#define SITE_FORM_NAME "Database"
#define SITE_REPLICAID_VIEW_NAME 	"($ReplicaID)"
#define SITE_PROFILE_NAME 			"Site"

#define SITE_TITLE_ITEM_NAME "Title"
#define SITE_REALTITLE_ITEM_NAME "RealTitle"
#define SITE_DBICON_ITEM_NAME "dbicon"
#define SITE_SEQUENCE_ITEM_NAME "dbsequence"
#define SITE_REPLICAID_ITEM_NAME "replicaid"
#define SITE_SEQUENCE_ITEM_NAME 	"dbsequence"
#define SITE_SERVERHINT_ITEM_NAME "$ServerHint"

/* Web Browser control well known action name and form name */
#define OLE_URLNAVIGATE_ACTION		"$ControlURLNavigate"
#define OLE_WEBBROWSER_FORM			"WebBrowserForm"		/* Used if IE 3 is installed */
#define OLE_WEBBROWSER4_FORM		"WebBrowser4Form"		/* Used if IE 4 is installed */

/* Distinguished Field Names */
#define DN_COUNTRY	"C"
#define DN_ORGANIZATION "O"
#define DN_ORGANIZATIONAL_UNIT "OU"
#define DN_COMMON_NAME "CN"
#define DN_SURNAME "S"


/*	Items used to store folder references. */

#define	ITEM_FOLDER_REF				"$FolderRef"
#define	ITEM_FOLDER_REF_ID			"$FolderRefID"
#define	ITEM_FOLDER_REF_FLAGS		"$FolderRefFlags"

/*	Folder reference flag values. */

#define	FOLDER_REF_FLAG_SEEN		0x00000001
#define	FOLDER_REF_FLAG_ANSWERED	0x00000002
#define	FOLDER_REF_FLAG_FLAGGED		0x00000004
#define	FOLDER_REF_FLAG_DELETED		0x00000008
#define	FOLDER_REF_FLAG_DRAFT		0x00000010
#define	FOLDER_REF_FLAG_NOT_RECENT	0x00000020
#define	FOLDER_REF_FLAG_RECENT		0x00000040		//	Unique flag value that is not stored

/*	Name of the folder reference information collection. */

#define	FOLDER_REF_INFO_COLLECTION	"$FolderRefInfo"

/*	Collations in the folder reference information collection. */

#define	FOLDER_UNID_REF_ID_COLLATION_NUMBER		1
#define	FOLDER_UNID_REF_ID_COLLATION_LEVELS		2

#define FOLDER_UNID_NNTP_DATE_COLLATION_NUMBER	2
#define FOLDER_UNID_NNTP_DATE_COLLATION_LEVELS	2

/*	Summary item names used to store folder reference information. */

#define	FOLDER_REF_UNID_ITEM_NAME		"$105"
#define	FOLDER_REF_REF_ID_ITEM_NAME 	"$FolderRefID"
#define	FOLDER_REF_FLAGS_ITEM_NAME		"$FolderRefFlags"

/*  Summarty item names used to store NNTP folder reference information. */

#define FOLDER_REF_NNTP_SUBJECT_ITEM_NAME 		"$110"
#define FOLDER_REF_NNTP_FROM_ITEM_NAME			"$109"
#define FOLDER_REF_NNTP_DATE_ITEM_NAME			"$113"
#define FOLDER_REF_NNTP_MESSAGE_ID_ITEM_NAME	"$uname"
#define FOLDER_REF_NNTP_REFERENCES_ITEM_NAME	"$114"
#define FOLDER_REF_NNTP_SIZE_ITEM_NAME			"NNTP_Size"		
#define FOLDER_REF_NNTP_LINES_ITEM_NAME			"Lines"
#define FOLDER_REF_NNTP_ISLMBCS_ITEM_NAME		"$115"
#define FOLDER_REF_NNTP_DISTRIBUTION_ITEM_NAME	"Distribution"
#define FOLDER_REF_NNTP_PATH_ITEM_NAME			"Path"


/*	Folder flag values. */

#define	FOLDER_FLAG_NOINFERIORS		0x00000001
#define	FOLDER_FLAG_NOSELECT		0x00000002
#define	FOLDER_FLAG_MARKED			0x00000004
#define	FOLDER_FLAG_UNMARKED		0x00000008

#define	FOLDER_FLAG_SYSTEM			0x00000010	/*	Set if folder name starts with '$' */
#define	FOLDER_FLAG_HIDDEN			0x00000020	/*	Set if folder name starts with '(' */

#define FOLDER_FLAG_NNTP_NEWSGROUP	0x00000040

/*	A special, unique folder flag value, that is never stored, used to indicate
	that any value of folder flags are to be considered a match. */

#define	FOLDER_FLAG_ANY				0x80000000

/*	A mask of bits that are used to qualify a folder name. */

#define	FOLDER_FLAG_MATCH_MASK		(FOLDER_FLAG_SYSTEM | FOLDER_FLAG_HIDDEN)

/*	A bit that is used to indicate that any value of folder flags are to be
	considered a match.  */

#define	FOLDER_FLAG_MATCH_ANY		(FOLDER_FLAG_ANY)


/*	Name of the folder information collection. */

#define	FOLDER_INFO_COLLECTION		"$FolderInfo"

/*	Collations in the folder information collection. */

#define	FOLDER_NAME_COLLATION_NUMBER			1
#define	FOLDER_NAME_COLLATION_LEVELS			1

#define	FOLDER_UNID_COLLATION_NUMBER			2
#define	FOLDER_UNID_COLLATION_LEVELS			1

/*	Collations in the IMAIL resync information collection. */

#define	RESYNC_INFO_NOTEID_COLLATION_NUMBER		1
#define	RESYNC_INFO_NOTEID_COLLATION_LEVELS		1

#define	RESYNC_INFO_UID_COLLATION_NUMBER		2
#define	RESYNC_INFO_UID_COLLATION_LEVELS		1

/*	Summary item names used to store folder information. */

#define	FOLDER_NAME_ITEM_NAME			"$106"
#define	FOLDER_UNID_ITEM_NAME	 		"$103"
#define	FOLDER_FLAGS_ITEM_NAME			"$107"

/*	Items used to store folder information. */

#define	ITEM_FOLDER_FLAGS			"$FolderFlags"

/*	Length of the text representation of an UNID in hex format. */

#define	UNID_TEXT_LENGTH			(2 * sizeof(UNID))

/*  IMAP subscription list */

#define IMAP_PROFILE_SUBSCRIPTION	"IMAPProfileSubscription"
#define ITEM_IMAP_SUBSCRIPTION		"$IMAPSubscription"

/*	IMAP Replication Items */

#define IMAP_SEQNO_ITEM_NAME				"$IMAPSeqNo"
#define	IMAP_LASTFOLDERUNID_ITEM_NAME		"$IMAPLastFolderUNID"
#define	IMAP_UID_ITEM_NAME					"$IMAPUID"
#define IMAP_FLAGS_ITEM_NAME				"$IMAPFlags"
#define IMAP_DISCFLAGS_ITEM_NAME   			"$IMAPDiscFlags"
#define IMAP_MSGID_ITEM_NAME				"$IMAPMsgID"

/*	IMAP Replication $IMAPResyncInfo view column names */

#define IMAP_SEQNO_COLUMN					"IMAPSeqNo"
#define	IMAP_LASTFOLDERUNID_COLUMN			"IMAPLastFolderUNID"
#define	IMAP_UID_COLUMN						"IMAPUID"
#define IMAP_FLAGS_COLUMN					"IMAPFlags"
#define IMAP_DISCFLAGS_COLUMN				"IMAPDiscFlags"
#define IMAP_MSGID_COLUMN					"IMAPMsgID"

/*	NNTP Replication Items */

#define	NNTP_FOLDERUNID_ITEM_NAME			"$NNTPFolderUNID"
#define	NNTP_UID_ITEM_NAME					"$NNTPUID"
#define NNTP_FLAGS_ITEM_NAME				"$NNTPFlags"
#define NNTP_MSGID_ITEM_NAME				"$UName"
#define FIELD_PARENT_UNAME					"$ParentUName"

/*	NNTP Replication $NNTPResyncInfo view column names */

#define	NNTP_FOLDERUNID_COLUMN				"NNTPFolderUNID"
#define	NNTP_UID_COLUMN						"NNTPUID"
#define NNTP_FLAGS_COLUMN					"NNTPFlags"
#define NNTP_MSGID_COLUMN					"UName"

/*	Name of the IMAP Resync information collection. */

#define	IMAP_RESYNC_INFO_COLLECTION			"$IMAPResyncInfo"

/*	Name of the NNTP Resync information collection. */

#define	NNTP_RESYNC_INFO_COLLECTION			"$NNTPResyncInfo"

/*	components (java applets, etc. ) */

#define	COMPONENTS_LIST_ITEM	"$Components"

/* Setup */
#define SETUP_SERVERLOOKUP_VIEW	"($ServersLookup)"

#endif /* STD_NAME_DEFS */

/*	Admin Panel	*/

#define	NETWORKS_NAMESPACE				"$Networks"
#define INIT_NETWORKSLOOKUPITEMCOUNT	2
#define INIT_NETWORKSLOOKUPITEMS      	"Network\0ServerName"
#define INIT_NETWORKSITEM_NETWORK      	0
#define INIT_NETWORKSITEM_SERVER      	1

/* Domain Type */

#define NOTES_DOMAIN_TYPE 	"NOTES"
#define LDAP_DOMAIN_TYPE	"LDAP"



/* Headline Items */

#define HEADLINE_DEFAULTVIEW_ITEM		"($Headlines)"			/* Default view to use to create headlines views */

#define HEADLINE_VIEW_ITEM				"$HLView"				/* Headline marker item for headlines view */
#define HEADLINE_SUMMARY_ITEM			"$HLNoteSummary"		/* Headline summary item */
#define HEADLINE_MODIFIED_ITEM			"$HLNoteModified"		/* Headline last modified time (time) */
#define HEADLINE_UNID_ITEM				"$HLNoteUNID"			/* Headline UNID (text) */
#define HEADLINE_SEARCHMATCH_ITEM		"$HLNoteSearchMatch"	/* Headline search match item (text format below) */
#define HEADLINE_REF_ITEM				"$HLNoteREF"			/* Headline saved reference (no main topic found) */

/* Subscription Items */

#define SUBSCRIPTION_VIEW				"$Subscriptions"	/* Alias of subscriptions view */
#define	SUBSCRIPTION_FORM				"$Subscription"		/* Name of subscription form */
#define SUBSCRIPTION_HEADLINES_VIEW		"$HeadlinesView"	/* Designer specified view for headlines */
#define	FIELD_FORM_DBID					"$FormDatabaseID"

#define SUBSCRIPTION_VIEW_ITEM			"$HLSubscription"	/* Marker item for subscriptions */
#define SUBSCRIPTION_TITLE				"$HLTitle"			/* Title of subscription */

#define SUBSCRIPTION_DISABLED_ITEM		"$HLDisabled"		/* Disabled Flag, checked before enabled flag */
#define SUBSCRIPTION_ENABLED_ITEM		"$HLEnabled"		/* Enabled Flag, only checked if disabled flag not found */
#define SUBSCRIPTION_DISABLED			'0'					/* Enabled Flag - disabled */
#define SUBSCRIPTION_ENABLED			'1'					/* Enabled Flag - enabled */

#define SUBSCRIPTION_TYPE_ITEM			"$HLType"			/* Subscription Type */
#define SUBSCRIPTION_TYPE_DB			'1'					/* Subscription Type - DB monitoring */
#define SUBSCRIPTION_TYPE_VIEW			'2'					/* Subscription Type - view */
#define SUBSCRIPTION_TYPE_URL			'3'					/* Subscription Type - URL */
#define SUBSCRIPTION_KIND_DB			1					/* Subscription Kind - DB monitoring */
#define SUBSCRIPTION_KIND_VIEW			2					/* Subscription Kind - view */
#define SUBSCRIPTION_KIND_URL			3					/* Subscription Kind - URL */

#define SUBSCRIPTION_TARGETFRAME_ITEM	"$HLTargetFrame"	/* Frame to use for the subscription */
#define SUBSCRIPTION_FRAME_DB			"$HLMonitorFrame"	/* Default frame to use for monitor subscriptions */
#define SUBSCRIPTION_FRAME_VIEW			"$HLViewFrame"		/* Default frame to use for view subscriptions */
#define SUBSCRIPTION_FRAME_URL			"$HLURLFrame"		/* Default frame to use for URL subscriptions */

#define SUBSCRIPTION_URL_ITEM			"$HLURL"			/* URL for View and URL subscription types */

#define SUBSCRIPTION_FORMULA_ITEM		"$HLFormula"		/* Monitor Formula */
#define SUBSCRIPTION_FULLTEXT_ITEM		"$HLFulltext"		/* Monitor Full Text */

#define SUBSCRIPTION_OPTIONS_ITEM		"$HLOptions"		/* Monitor Options Flag */
#define SUBSCRIPTION_OPTIONS_NONE		'0'					/* Monitor Options Flag - none */
#define SUBSCRIPTION_OPTIONS_SUMMARY	'1'					/* Monitor Options Flag - summary */
#define SUBSCRIPTION_OPTIONS_LOCAL		'2'					/* Monitor Options Flag - local */
#define SUBSCRIPTION_OPTIONS_ALL		'3'					/* Monitor Options Flag - summary&local */


#define SUBSCRIPTION_MONITORTYPE_ITEM	"$HLMonitorType"	/* Monitor Type Flag */
#define SUBSCRIPTION_MONITORTYPE_FORMULA	'1'				/* Monitor Type Flag - formula */
#define SUBSCRIPTION_MONITORTYPE_FULLTEXT	'2'				/* Monitor Type Flag - full text */
#define SUBSCRIPTION_DB_ITEM			"$HLMonitorDB"		/* Database to Monitor */
#define SUBSCRIPTION_DB_VIEW_ITEM		"$HLHeadlineView"	/* User specified view for headlines */

#define SUBSCRIPTION_CREATE			"$HLCreateSubscription"	/* Flag to indicate a partial subscription that */
															/* needs more information to be created */
#define SUBSCRIPTION_CREATE_MAIL		"mail"				/* Creating a special mail file subscription */

#define SUBSCRIPTION_LASTCHECKED_ITEM	"$HLMLastChecked"	/* Last time the monitor DB was checked */
#define SUBSCRIPTION_CLIENTID_ITEM		"$HLMClientId"		/* Last ClientId used */
#define SUBSCRIPTION_SERVER_ITEM		"$HLMServer"		/* Original server to be monitored */
#define SUBSCRIPTION_LASTSERVER_ITEM	"$HLMLastServer"	/* Last server monitored */
#define SUBSCRIPTION_LASTPATH_ITEM		"$HLMLastPath"		/* Last path monitored */
#define SUBSCRIPTION_MONITORID_ITEM		"$HLMMonitorId"		/* Last MonitorId used */
#define SUBSCRIPTION_ERROR_ITEM			"$HLMError"			/* Last error encountered while initilaizing */
#define SUBSCRIPTION_SERVER_INFO		"$HLMServerInfo"	/* Information about last servers monitored */



/*	Framesets used in the client */
#define CLIENT_FRAMESET_LAYOUT		"ClientLayout"
#define CLIENT_FRAMESET_MORE		"ClientMore"
#define CLIENT_FRAMESET_BMPAGE		"BMPage"

/*	Frameset used in mail */
#define MAIL_FRAMESET_MAIL			"MailFS"


#define Bookmark_IntroPageName 		"Intro"	/* webpage name in bookmark to startup */
#define Bookmark_StartupFramesetName "Home"	/* frameset name in bookmark to startup */

/*	Special frame names used by the client */

#define NAVIGATOR_PANE				"NotesNavigator"
#define VIEW_PANE					"NotesView"
#define PREVIEW_PANE				"NotesPreview"
#define USE_DEFAULT_FRAME_TARGETING "UseNotesDefaultFrameTargeting"

/*	Names used for various client types which can exist */
#define DESIGNER_CLIENT				"Designer"
#define ADMIN_CLIENT				"Admin"
#define NOTES_CLIENT				"Notes"

/* For use in search results template forms */
#define SEARCH_QUERY "Query"
#define SEARCH_START "Start"
#define SEARCH_COUNT "Count"
#define SEARCH_HITS "Hits"
#define SEARCH_TOTAL_HITS "TotalHits"
#define SEARCH_RESULT_LIMIT "SearchMax"
#define SEARCH_WV "SearchWV"
#define SEARCH_THESAURUS "SearchThesaurus"
#define SEARCH_FUZZY "SearchFuzzy"
#define SEARCH_ORDER "SearchOrder"
#define SEARCH_SORT_OPTIONS "SortOptions"
#define SEARCH_OTHER_OPTIONS "OtherOptions"
#define SEARCH_BODY "Body"
#define SEARCH_ENTRYFORM_NAME "SearchEntry"
#define SEARCH_BODY_WEB ITEM_NAME_EMBEDDED_VIEW
#define SEARCH_VIEW "SearchView"
#define SEARCH_SCOPE "Scope"

/* Dublin Core Meta Data */
#define ITEM_META_TITLE					"$$Title"
#define ITEM_META_CREATOR				"$$Creator"
#define ITEM_META_DESCRIPTION			"$$Description"
#define ITEM_META_TYPE					"$$Type"
#define ITEM_META_CATEGORIES			"$$Categories"

/* Document Content view in the Domain Catalog */
#define CATALOG_VIEW_CONTENT_CATEGORY "$DocumentContent"

/*	Shared Resources */

#define ITEM_NAME_IMAGE_DATA			"$ImageData"
#define ITEM_NAME_IMAGE_NAMES			"$ImageNames"
#define ITEM_NAME_IMAGES_WIDE			"$ImagesWide"
#define ITEM_NAME_IMAGES_HIGH			"$ImagesHigh"
#define ITEM_NAME_IMAGES_COLORIZE		"$ImagesColorize"

#define ITEM_NAME_JAVA_FILES			"$JavaFiles"

/*	defadmin.ntf definitions. */

#define ITEM_TASK_LOAD_LOADCMD			"$Task_LoadCmd"
#define ITEM_TASK_TELLCMD				"$Task_TellCmd"
#define ITEM_TASK_LOAD_NAME				"Task_name"
#define ITEM_TASK_LOAD_FILENAME			"Task_filename"
#define ITEM_TASK_LOAD_DESCRIPTION		"Task_description"
#define ITEM_TASK_LOAD_HASUI			"Task_hasLoadUI"
#define ITEM_TASK_TELL_HASUI			"Task_hasTellUI"
#define ITEM_TASK_MONITOR_NAME			"Task_MonitorName"

/* Special image resource name which will use the Database's icon if the
		image does not exist. */

#define IMAGE_DBICON_NAME	"$Icon"

/* For reading International MIME settings in NAB */
#define MIMEI18N_FLD_CONFIG_ENABLED			"MIMEOptionsEnabled"
#define MIMEI18N_FLD_PRIMARY_GROUP			"CVS_PrimaryGroup"
#define MIMEI18N_FLD_SECONDARY_GROUPS		"CVS_SecondaryGroups"
#define MIMEI18N_FLD_INP_ALIAS_ALIAS  		"CVSI_CharsetAlias%d"
#define MIMEI18N_FLD_INP_ALIAS_ACTUAL 		"CVSI_CharsetActual%d"
#define MIMEI18N_FLD_EXP_ALIAS_ALIAS  		"CVSO_CharsetAlias%d"
#define MIMEI18N_FLD_EXP_ALIAS_ACTUAL 		"CVSO_CharsetActual%d"
#define MIMEI18N_FLD_8BIT_FALLBACK			"CVSI_NonMIMECharSet"
#define MIMEI18N_FLD_INP_GROUP_FONT_PROP 	"CVSI_%s_F_P"
#define MIMEI18N_FLD_INP_GROUP_FONT_MONO 	"CVSI_%s_F_M"
#define MIMEI18N_FLD_INP_GROUP_FONT_PLAIN 	"CVSI_%s_F_T"
#define MIMEI18N_FLD_INP_GROUP_FONT_PLAIN_SIZE "CVSI_%s_F_Size"
#define MIMEI18N_FLD_INP_GROUP_FONT_HTML_SIZE "CVSI_%s_F_HSize"
#define MIMEI18N_FLD_EXP_GROUP_CSET_HEAD 	"CVSO_%s_CS_H"
#define MIMEI18N_FLD_EXP_GROUP_CSET_BODY 	"CVSO_%s_CS_B"
#define MIMEI18N_FLD_EXP_GROUP_ENC_HEAD 	"CVSO_%s_ENC_H"
#define MIMEI18N_FLD_EXP_GROUP_ENC_BODY 	"CVSO_%s_ENC_B"
/* _FALLBACK_MODE is obsolete, now using _MULTILINGUAL_MODE */
#define MIMEI18N_FLD_EXP_FALLBACK_MODE		"CVS_MLMessageHandling"
#define MIMEI18N_FLD_EXP_MULTILINGUAL_MODE	"CVS_MultilingualMsgHandling"
#define MIMEI18N_LOCATION_I18N_VIEW 		"($InternationalMIMESettings)"

/* these are obsolete, now using _MULTILINGUAL_xxx */
#define MIMEI18N_FALLBACK_UTF8				1
#define MIMEI18N_FALLBACK_FALLBACK_CHAR		2
#define MIMEI18N_FALLBACK_UNICODE_ENTITIES	3
#define MIMEI18N_FALLBACK_REFUSE			4

#define MIMEI18N_MULTILINGUAL_UNICODE		1
#define MIMEI18N_MULTILINGUAL_BEST_MATCH	2

/* these are NOTES.INI variables used on the client only -- not server
 * which has this stuff in a config note
 */
#define MIME_MULTILINGUAL_MODE_VAR 	 "MIMEMultilingualMode"
#define MIME_PROMPT_MULTILINGUAL_VAR "MIMEPromptMultilingual"

/* see net/resolver.c for use of these */
#define HTTP_SERVER_LOOKUP_ITEMS "HTTP_HostName\0SMTPFullHostDomain\0HTTP_NormalMode\0HTTP_SSLMode\0HTTP_Port\0HTTP_SSLPort\0Enabled_0\0Protocol_0\0NetAddr_0\0Enabled_1\0Protocol_1\0NetAddr_1\0Enabled_2\0Protocol_2\0NetAddr_2\0Enabled_3\0Protocol_3\0NetAddr_3\0Enabled_4\0Protocol_4\0NetAddr_4\0Enabled_5\0Protocol_5\0NetAddr_5\0Enabled_6\0Protocol_6\0NetAddr_6\0Enabled_7\0Protocol_7\0NetAddr_7"
#define HTTP_SERVER_LOOKUP_ITEM_COUNT 30
#define HTTP_SERVER_LOOKUP_ITEM_HTTPHOSTNAME 0
#define HTTP_SERVER_LOOKUP_ITEM_FULLHOSTNAME 1
#define HTTP_SERVER_LOOKUP_ITEM_NORMALMODE 2
#define HTTP_SERVER_LOOKUP_ITEM_SSLMODE 3
#define HTTP_SERVER_LOOKUP_ITEM_PORT 4
#define HTTP_SERVER_LOOKUP_ITEM_SSLPORT 5
#define HTTP_SERVER_LOOKUP_ITEM_OFFS_START 6
#define HTTP_SERVER_LOOKUP_ITEM_OFFS_ENABLED 0
#define HTTP_SERVER_LOOKUP_ITEM_OFFS_PROTOCOL 1
#define HTTP_SERVER_LOOKUP_ITEM_OFFS_NETADDR 2
#define HTTP_SERVER_LOOKUP_ITEM_OFFS_MAX 3


#ifdef __cplusplus
}
#endif
