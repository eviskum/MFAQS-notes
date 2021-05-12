#ifndef REG_ERR_DEFS
#define REG_ERR_DEFS

/* 	Returned errors	------------------------------------------------------ */


#define	ERR_REG_INC_CONTEXT				PKG_REG + 1
	apitext(ERR_REG_INC_CONTEXT, "Insufficient information supplied for requested registration function.")

#define	ERR_REG_ADDRBOOK_ENTRY_EXISTS	PKG_REG + 2
	apitext(ERR_REG_ADDRBOOK_ENTRY_EXISTS, "No permission (flag) to modify existing Address Book entry")

#define ERR_REG_USERID_EXISTS 			PKG_REG + 3
	apitext(ERR_REG_USERID_EXISTS, "No permission (flag) to modify existing UserID File")

#define ERR_REG_BEGIN_CERTIFYING		PKG_REG + 4
	stringtext(ERR_REG_BEGIN_CERTIFYING, "Begin certifying %A...") 

#define ERR_REG_NO_MAILFILE_CREATED 	PKG_REG + 5
	errortext(ERR_REG_NO_MAILFILE_CREATED, "Mail file for %A could not be created")

#define ERR_REG_BEGIN_REGISTERING		PKG_REG + 6
	stringtext(ERR_REG_BEGIN_REGISTERING, "Begin registering %A...")

#define ERR_REG_CREATINGNEWMAIL			PKG_REG + 7
	stringtext(ERR_REG_CREATINGNEWMAIL, "Creating mail file for %A...")

#define ERR_REG_ADDIDTOBOOK				PKG_REG + 8
	stringtext(ERR_REG_ADDIDTOBOOK, "Adding %A to the Name and Address Book...")

#define ERR_REG_DONE_REGISTERING		PKG_REG + 9
	stringtext(ERR_REG_DONE_REGISTERING, "%A successfully registered.")

#define	ERR_REG_LOG_ADDRBOOK_EXISTS		PKG_REG + 10
	stringtext(ERR_REG_LOG_ADDRBOOK_EXISTS, "Address Book entry for %A already exists.")

#define ERR_REG_LOG_USERID_EXISTS 		PKG_REG + 11
	stringtext(ERR_REG_LOG_USERID_EXISTS, "UserID file %p already exists.")

#define ERR_REG_LOG_NO_PASSWORD 		PKG_REG + 12
	stringtext(ERR_REG_LOG_NO_PASSWORD, "No password supplied for %s.")

#define ERR_REG_BEGIN_IDFILE_CREATE		PKG_REG + 13
	stringtext(ERR_REG_BEGIN_IDFILE_CREATE, "Creating ID for %A.  This requires 1-3 minutes of computation...")

#define ERR_REG_TOO_MANY_ENTRIES		PKG_REG + 14
	errortext(ERR_REG_TOO_MANY_ENTRIES, "The name cannot be registered.  More than one entry was found in the Address Book with this name")

#define ERR_REG_DONE_CERTIFYING			PKG_REG + 15
	stringtext(ERR_REG_DONE_CERTIFYING, "Done certifying %A...") 

#define ERR_REG_NO_IDFILE_NAME			PKG_REG + 16
	stringtext(ERR_REG_NO_IDFILE_NAME,	"No ID file name specified") 

#define ERR_REG_NO_MAIL_INFO			PKG_REG + 17
	stringtext(ERR_REG_NO_MAIL_INFO,	"No mail server or mail database name specified") 

#define ERR_REG_NO_LASTNAME				PKG_REG + 18
	stringtext(ERR_REG_NO_LASTNAME,		"No last name specified") 

#define ERR_REG_NO_SERVER_NAME			PKG_REG + 19
	stringtext(ERR_REG_NO_SERVER_NAME,	"No server name specified") 

#define ERR_REG_NO_CERTIFIER			PKG_REG + 20
	stringtext(ERR_REG_NO_CERTIFIER,	"No certifier specified") 

#define ERR_REG_NO_PASSWORD				PKG_REG + 21
	stringtext(ERR_REG_NO_PASSWORD,		"No password specified") 

#define ERR_REG_OPEN_CERTLOG		 	PKG_REG + 22
	stringtext(ERR_REG_OPEN_CERTLOG,	"Could not open the certifier log") 

#define ERR_REG_ACCESS_CERTLOG			PKG_REG + 23
	stringtext(ERR_REG_ACCESS_CERTLOG,	"You are not allowed to update the certifier log") 

#define ERR_REG_UPDATE_CERTLOG		 	PKG_REG + 24
	stringtext(ERR_REG_UPDATE_CERTLOG,	"Error attempting to update the certifier log") 

#define ERR_REG_OURSERVERS				PKG_REG + 25
	stringtext(ERR_REG_OURSERVERS,		"LocalDomainServers")

#define STR_REG_UPDATING_CERTLOG		PKG_REG + 26
	stringtext(STR_REG_UPDATING_CERTLOG,"Updating Certification Log")

#define ERR_REG_USER_NOT_FOUND 			PKG_REG + 27
	errortext(ERR_REG_USER_NOT_FOUND,"User or server name not found in Name and Address Book")

#define ERR_REG_IDFILE_NOT_FOUND		PKG_REG + 28
	errortext(ERR_REG_IDFILE_NOT_FOUND,"ID file not found in Name and Address Book")

#define	ERR_REG_NOSUCHUSER				PKG_REG + 29
	errortext(ERR_REG_NOSUCHUSER,		"User name not found in Name and Address Book")

#define	ERR_REG_NOTUNIQUE				PKG_REG + 30
	errortext(ERR_REG_NOTUNIQUE,		"Multiple users with same name found in Name and Address Book")

#define	ERR_REG_NOSUCHSERVER	   		PKG_REG + 31
	errortext(ERR_REG_NOSUCHSERVER,		"Server name not found in Name and Address Book")

#define	ERR_REG_SERVERNOTUNIQUE			PKG_REG + 32
	errortext(ERR_REG_SERVERNOTUNIQUE,	"Multiple servers with same name found in Name and Address Book")

#define STR_REG_NETWARE_NAME			PKG_REG + 33
	internaltext(ERR_REG_NETWARE_NAME, "NetWare")

#define ERR_REG_NO_STORED_CERTKEY		PKG_REG + 34
	errortext(ERR_REG_NO_STORED_CERTKEY, "The Name and Address Book entry does not include a certified public key")

#define ERR_REG_NO_SRV_VIEW				PKG_REG + 35
	errortext(ERR_REG_NO_SRV_VIEW, "The Address Book you are registering the server to does not contain a $Servers view.  In order to register a server you must use a Public Address Book.  You can replace the design of the Address Book you are using with the Public Address Book template.")

#define ERR_REG_LOG_PASSWORD_ADDRESSBOOK	PKG_REG + 36
	stringtext(ERR_REG_LOG_PASSWORD_ADDRESSBOOK, "No password supplied for %s (required for ID files to be stored in the Name and Address Book).")

#define ERR_REG_LOG_MINPSWDCHARS		PKG_REG + 37
	stringtext(ERR_REG_LOG_MINPSWDCHARS, "You must supply the minimum number of characters required for a password for %s.")

#define ERR_REG_CREATING_ADMINREQTOCREATEMAIL	PKG_REG + 38
	stringtext(ERR_REG_CREATING_ADMINREQTOCREATEMAIL, "Creating administration request to create mail file for %A...")

#define ERR_REG_NO_ADMINREQTOCREATEMAIL 	PKG_REG + 39
	errortext(ERR_REG_NO_ADMINREQTOCREATEMAIL, "The administration request could not be created: %s")

#define ERR_REG_NO_ADMINPROCESS 	PKG_REG + 40
	errortext(ERR_REG_NO_ADMINPROCESS, "The administration process has not been initialized.")

#define ERR_REG_CREATEMAILSETUP			PKG_REG + 41
	stringtext(ERR_REG_CREATEMAILSETUP, "Mail file for %A will be created during user setup.")

#define ERR_REG_NT_PASSWORD_SIZE		PKG_REG + 42
	stringtext(ERR_REG_NT_PASSWORD_SIZE, "The NT user '%s' could not be added.  The Notes password violated the minimum or maximum NT password length.")

#define ERR_REG_NT_ACCESS_DENIED			PKG_REG + 43
	stringtext(ERR_REG_NT_ACCESS_DENIED, "You must be an NT Administrator or Account Operator to add NT users or groups.")

#define ERR_REG_NT_DC_NOT_FOUND			PKG_REG + 44
	stringtext(ERR_REG_NT_DC_NOT_FOUND, "The NT account(s) cannot be added.  A primary domain controller for the current NT domain cannot be found.")

#define ERR_REG_NT_DLL_NOT_FOUND		PKG_REG + 45
	stringtext(ERR_REG_NT_DLL_NOT_FOUND, "%s could not be found.  If available, place it in the Windows system directory (SYSTEM32).")

#define ERR_REG_NT_USER_GROUP_ABSENT		PKG_REG + 46
	stringtext(ERR_REG_NT_USER_GROUP_ABSENT, "The NT account for '%s' could not be added.  The NT user or group could not be found on the current NT domain.")

#define ERR_REG_NT_REG_FAILED		PKG_REG + 47
	stringtext(ERR_REG_NT_REG_FAILED, "The NT account for '%s' could not be added.")

#define ERR_REG_NT_USER_EXISTS		PKG_REG + 48
	stringtext(ERR_REG_NT_USER_EXISTS, "The NT account for '%s' could not be added; an NT user with the same Username already exists.")

#define ERR_REG_ADDCERTIFICATETOBOOK	PKG_REG + 49
	stringtext(ERR_REG_ADDCERTIFICATETOBOOK, "Adding the certificate to the Name and Address Book...")

#define STR_REG_SETUP_NETWORK_NAME		(PKG_REG+50)
	stringtext(STR_REG_SETUP_NETWORK_NAME, "Network1")

/*	NOTE:  PKG_REG+51 through PKG_REG+151 are used by the setup program
			to provide network choices.

	The format of the stringtext is five fields separated by | (vertical bar):
		(1) List of platform names on which support is provided separated by
			; (semi-colons) -- must match platform name in global.h EXACTLY
		(2) Flags defined below (WORKSTATION_SUPPORT, etc.)
		(3) PortName in Ports= or DisabledPorts= line in notes.ini
		(4) Notes.ini PortName variable, specifying DLL name, unit number,
			number of simultaneous sessions, and buffer size in bytes
		(5) Dialog box description in Setup (TRANSLATE THIS ONE ONLY!).

	The order of the list of choices during setup for a given platform is
	determined by the order they are in the strings.  
		
	Network support may also be added by having a similar string in a
	text file which is shipped with the given network driver (like SNA).
	These networks will be at the end of the list.

	DO NOT USE PKG_REG+51 through PKG_REG+151!

*/

/************************** SETUP Network resource strings *****************/

#define NUMNETWORKSADDED	50
#define MAXDLGSTRING		50
#define MAXDLLNAME			9

#define WORKSTATION_SUPPORT 	0x00000001
#define SERVER_SUPPORT			0x00000002
#define PHONENUMBER_SUPPORT		0x00000004	/* Used for SNA support */
#define MODEM_SUPPORT			0x00000008

#define	PKG_SETUP				PKG_REG+51

/*	The following template is used so we can dynamically add the port name, unit
	number and driver name after querying the system.
*/
#define SETUP_XPC_TEMPLATE	PKG_SETUP
	stringtext(SETUP_XPC_TEMPLATE, "Macintosh|13|%s|XPC,%s,15,0,%s!%s|%s")

/* 	Note the strings, AppleTalk and VINES, in the port name are checked in 
	net\netsetup.c to exclude them from Win95 server setup selection.  If 
	you change the name here, change it there in subroutine, PutEntryInTable.
*/


#define SETUP_NETWORK_FIRST		(PKG_SETUP+10)
#define SETUP_NETWORK_LAST		(PKG_SETUP+100)

	stringtext(SETUP_NETWORK_FIRST+0, "Windows/16|1|TCP|TCP, 0, 15, 0|TCP/IP")
	stringtext(SETUP_NETWORK_FIRST+1, "OS/2v2|3|TCPIP|TCP, 0, 15, 0|TCP/IP")
	stringtext(SETUP_NETWORK_FIRST+2, "Windows/32;UNIX;Netware|3|TCPIP|TCP, 0, 15, 0|TCP/IP")	
	stringtext(SETUP_NETWORK_FIRST+3, "Windows/16|1|VINES|VINES, 0, 15, 0|Banyan VINES")
	stringtext(SETUP_NETWORK_FIRST+4, "OS/2v2;Windows/32|3|VINES|VINES, 0, 15, 0|Banyan VINES")
	stringtext(SETUP_NETWORK_FIRST+5, "Macintosh|1|TCP/IP|TCP, 0, 15, 0|TCP/IP")
	stringtext(SETUP_NETWORK_FIRST+6, "Windows/32;OS/2v2;Netware|3|SPX|NWSPX, 0, 15, 0|NetWare SPX")
	stringtext(SETUP_NETWORK_FIRST+7, "Windows/16|1|SPX|NWSPX, 0, 15, 0|NetWare SPX")
	stringtext(SETUP_NETWORK_FIRST+8, "OS/2v2|3|IBM_LAN0|IBMEENB, 0, 50, 0|IBM EE LAN Requestor")
	stringtext(SETUP_NETWORK_FIRST+9, "OS/2v2|2|AppleTalk|ATALK, 0, 15, 0|AppleTalk")								
	stringtext(SETUP_NETWORK_FIRST+10, "Windows/32;Netware|2|AppleTalk|ATALK, 0, 15, 0|AppleTalk")								
	stringtext(SETUP_NETWORK_FIRST+11, "Macintosh|1|AppleTalk|ATALK, 0, 15, 0|Appletalk")	
	stringtext(SETUP_NETWORK_FIRST+12, "Windows/32;Windows/16;OS/2v2;Netware|15|COM1|XPC, 1, 15, 0|COM1")
	stringtext(SETUP_NETWORK_FIRST+13, "Windows/32;Windows/16;OS/2v2;Netware|15|COM2|XPC, 2, 15, 0|COM2")
	stringtext(SETUP_NETWORK_FIRST+14, "Windows/32;Windows/16;OS/2v2;Netware|15|COM3|XPC, 3, 15, 0|COM3")
	stringtext(SETUP_NETWORK_FIRST+15, "Windows/32;Windows/16;OS/2v2;Netware|15|COM4|XPC, 4, 15, 0|COM4")
	stringtext(SETUP_NETWORK_FIRST+16, "Windows/32;Windows/16;OS/2v2;Netware|15|COM5|XPC, 5, 15, 0|COM5")
	stringtext(SETUP_NETWORK_FIRST+17, "UNIX|15|Serial1|XPC, 1, 15, 0|Serial1")
	stringtext(SETUP_NETWORK_FIRST+18, "UNIX|15|Serial2|XPC, 2, 15, 0|Serial2")
	stringtext(SETUP_NETWORK_FIRST+19, "UNIX|3|SPX|SPX, 0, 15, 0|SPX")
	stringtext(SETUP_NETWORK_FIRST+20, "Windows/32;Windows/16;OS/2v2|3|LAN0|NETBIOS, 0, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	
	stringtext(SETUP_NETWORK_FIRST+21, "Windows/32;Windows/16;OS/2v2|3|LAN1|NETBIOS, 1, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	
	stringtext(SETUP_NETWORK_FIRST+22, "Windows/32;Windows/16;OS/2v2|3|LAN2|NETBIOS, 2, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	
	stringtext(SETUP_NETWORK_FIRST+23, "Windows/32;Windows/16;OS/2v2|3|LAN3|NETBIOS, 3, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	
	stringtext(SETUP_NETWORK_FIRST+24, "Windows/32;Windows/16;OS/2v2|3|LAN4|NETBIOS, 4, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	
	stringtext(SETUP_NETWORK_FIRST+25, "Windows/32;Windows/16;OS/2v2|3|LAN5|NETBIOS, 5, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	
	stringtext(SETUP_NETWORK_FIRST+26, "Windows/32;Windows/16;OS/2v2|3|LAN6|NETBIOS, 6, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	
	stringtext(SETUP_NETWORK_FIRST+27, "Windows/32;Windows/16;OS/2v2|3|LAN7|NETBIOS, 7, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	
	stringtext(SETUP_NETWORK_FIRST+28, "Windows/32;Windows/16;OS/2v2|3|LAN8|NETBIOS, 8, 15, 0|NetBIOS (NetWare, LAN Manager, etc.)")	

/*	NOTE:  PKG_REG+51 through PKG_REG+151 are used by the setup program
			to provide network choices.

	DO NOT USE PKG_REG+51 through PKG_REG+151!
*/

/* Minimal setup hardcodes network setup to TCP (first entry) */
#define SETUP_NETWORK_TCPIP	0

#define STR_REG_NEWSETUP_NETWORK_SUFFIX			(PKG_REG+152)
	stringtext(STR_REG_NEWSETUP_NETWORK_SUFFIX,		"Network")
#define	STR_REG_ADDRESSBOOK_TITLE_STRING		(PKG_REG+153)
	stringtext(STR_REG_ADDRESSBOOK_TITLE_STRING,	"%a's Address Book")
#define ERR_REG_OTHERSERVERS					(PKG_REG+154)
	stringtext(ERR_REG_OTHERSERVERS,			"OtherDomainServers")
#define STR_REG_LOG_TITLE						(PKG_REG+155)
	stringtext(STR_REG_LOG_TITLE,				"Notes Log (%A)")
#define STR_REG_SETUP_ADDSERVER					(PKG_REG+156)
	stringtext(STR_REG_SETUP_ADDSERVER, 		"Setting Up Additional Domino Server")
#define STR_REG_SETUP_FIRSTSERVER				(PKG_REG+157)
	stringtext(STR_REG_SETUP_FIRSTSERVER, 		"Setting Up First Domino Server")
#define	ERR_REG_NOMODEMFILES					(PKG_REG+158)
	errortext(ERR_REG_NOMODEMFILES,				"No modem files are available on your system.")
#define ERR_REG_CERT_NAME_TOO_SHORT				(PKG_REG+159)
	errortext(ERR_REG_CERT_NAME_TOO_SHORT, 		"Certifier names must be at least three characters long.")
#define ERR_REG_PHONEREQUIRED					(PKG_REG+160)
	stringtext(ERR_REG_PHONEREQUIRED, 			"You must enter a phone number.")
#define ERR_REG_CERTREQUIRED					(PKG_REG+161)
	stringtext(ERR_REG_CERTREQUIRED, 			"You must enter a filename for the certifier ID.")
#define ERR_REG_USERREQUIRED					(PKG_REG+162)
	stringtext(ERR_REG_USERREQUIRED, 			"You must enter a filename for the user ID.")
#define ERR_REG_SERVERREQUIRED					(PKG_REG+163)
	stringtext(ERR_REG_SERVERREQUIRED, 			"You must enter a filename for the server ID.")
#define STR_REG_CONVERTING_MAILFILE				(PKG_REG+164)
	stringtext(STR_REG_CONVERTING_MAILFILE,  	"Registration completed.  Now converting mail file for %s...")
#define ERR_REG_STR_IDCHARS						(PKG_REG+165)
	stringtext(ERR_REG_STR_IDCHARS,				"&-. _")
#define STR_REG_DOMAINCHARS						(PKG_REG+166)
	stringtext(STR_REG_DOMAINCHARS,				"&-. _")
#define ERR_REG_UPDATING_ENTRY					(PKG_REG+167)
	errortext(ERR_REG_UPDATING_ENTRY,			"Updating Address Book entry for %A")
#define ERR_REG_UPGRADETEMPLATES				(PKG_REG+168)
	errortext(ERR_REG_UPGRADETEMPLATES,			"Upgrading the design of your databases")
#define ERR_REG_LAUNCH_SETUPDB					(PKG_REG+169)
	errortext(ERR_REG_LAUNCH_SETUPDB,			"You must complete server setup via the Domino setup database.")
#define ERR_REG_INITIALIZATION					(PKG_REG+170)
	stringtext(ERR_REG_INITIALIZATION,			"Setting default information in preferences file...")
#define ERR_REG_LANG_TAG_MISSING_FROM_CERT		(PKG_REG+171)
    errortext(ERR_REG_LANG_TAG_MISSING_FROM_CERT, "The alternate language specified for %s was not contained in the new certifier specified.  Certifier changes were not made for this user.")
#define ERR_REG_CERT_NOT_UPDATED				(PKG_REG+172)
    errortext(ERR_REG_CERT_NOT_UPDATED, 		"Ready for registration, but the certifier was not changed for this user; the existing alternate language for this user did not exist in the new certifier specified.")
#define ERR_REG_UPGRADENAMES					(PKG_REG+173)
	errortext(ERR_REG_UPGRADENAMES,				"Do you want to upgrade the design of your Address Book? This replaces the standard forms and views with ones from the template.")
#define ERR_REG_DO_SETUP						(PKG_REG+174)
	internaltext(ERR_REG_DO_SETUP,				"do client setup")
#define STR_REG_RLAN_RAS_STATIC					(PKG_REG+175)
	stringtext(STR_REG_RLAN_RAS_STATIC,			"RAS$%^Remote connection name:")
#define STR_REG_RLAN_ARA_STATIC					(PKG_REG+176)
	stringtext(STR_REG_RLAN_ARA_STATIC,			"ARA$%^Connection document location:")
#define STR_REG_RLAN_RAS_DRIVER					(PKG_REG+177)
	stringtext(STR_REG_RLAN_RAS_DRIVER,			"Microsoft Dial-Up Networking|RAS")
#define STR_REG_RLAN_ARA_DRIVER					(PKG_REG+178)
	stringtext(STR_REG_RLAN_ARA_DRIVER,			"AppleTalk Remote Access|ARA")
#define STR_REG_REPORTS_TITLE					(PKG_REG+179)
	stringtext(STR_REG_REPORTS_TITLE,			"Reports for")
#define ERR_REG_EVENTS4_SAVED					(PKG_REG+180)
	errortext(ERR_REG_EVENTS4_SAVED,			"Your current Statistics & Events database has been copied to %p. The database %p will be upgraded when the Event task runs and old messages will be deleted.")
#define ERR_REG_MULT_LANG_TAGS_MISSING			(PKG_REG+181)
    errortext(ERR_REG_MULT_LANG_TAGS_MISSING, 	"The new certifier specified does not contain the alternate language(s) set for one or more selected users.  The certifier will not be changed for these users.")
#define ERR_REG_NOT_PRIMARY_DIRECTORY			(PKG_REG+182)
    errortext(ERR_REG_NOT_PRIMARY_DIRECTORY, 	"A duplicate full or short name was found for this user in a non-primary directory (%s).  Full and short user names must be unique to be registered.")
#define ERR_REG_SKIPPED_TASK					(PKG_REG+183)
	errortext(ERR_REG_SKIPPED_TASK,				"Default server task %s will NOT be added to %s in NOTES.INI because %s is set.")
#define STR_DOLADMIN_TITLE						(PKG_REG+184)
	stringtext(STR_DOLADMIN_TITLE,				"Offline Services")

/*	198 - 208 reserved for cross-launching support. Since Mac file types/creators
	can contain spaces, whitespace is NOT ignored in these strings. Only use a space
	where a filetype/creator needs it! The wildcard character '?' is supported in
	file extensions.
*/

#define ERR_XLAUNCH_WP					(PKG_REG+198)
	stringtext(ERR_XLAUNCH_WP,			"WPC2,.WP?,.WP5")
#define ERR_XLAUNCH_WORD				(PKG_REG+199)
	stringtext(ERR_XLAUNCH_WORD,		"MSWD,.DOC,TEXT,.RTF,TEXT")
#define ERR_XLAUNCH_EXCEL				(PKG_REG+200)
	stringtext(ERR_XLAUNCH_EXCEL,		"XCEL,.XLC,XLC ,.XLS,TEXT")
#define ERR_XLAUNCH_123					(PKG_REG+201)
	stringtext(ERR_XLAUNCH_123,			"L123,.WK?,LWKS,.WK1,LWKS,.WK3,LWKS")
#define ERR_XLAUNCH_TEXT				(PKG_REG+202)
	stringtext(ERR_XLAUNCH_TEXT,		"ttxt,.TXT,TEXT,.00?,TEXT")
#define ERR_XLAUNCH_MOVIE				(PKG_REG+203)
	stringtext(ERR_XLAUNCH_MOVIE,		"TVOD,.MOV,Moov")
#define ERR_XLAUNCH_PPOINT				(PKG_REG+204)
	stringtext(ERR_XLAUNCH_PPOINT,		"PPT3,.PPT,SLD3")
#define ERR_XLAUNCH_ACROBAT				(PKG_REG+205)
	stringtext(ERR_XLAUNCH_ACROBAT,		"CARO,.PDF,TEXT")
#define ERR_XLAUNCH_PHOTOSHOP			(PKG_REG+206)
	stringtext(ERR_XLAUNCH_PHOTOSHOP,	"8BIM,.PDS,8BPS,.TIF,TIFF,.GIF,GIFf")
#define ERR_XLAUNCH_STUFFIT_EXPANDER	(PKG_REG+207)
	stringtext(ERR_XLAUNCH_STUFFIT_EXPANDER,	"SITx,.SEA,TEXT,.SIT,TEXT,.HQX,TEXT,.BIN,TEXT")
	
#define ERR_REG_INETADDR_NOT_UNIQUE				(PKG_REG+209)
	errortext(ERR_REG_INETADDR_NOT_UNIQUE,		"The internet address for this user is not unique.")
#define ERR_REG_DUSFULLNAME_CONFLICT			(PKG_REG+210)
	errortext(ERR_REG_DUSFULLNAME_CONFLICT,		"Different address book matches were found for the Notes hierarchical name check and the migrating user name check.  No address book entry can be overwritten.")

/*	211 - 230 reserved for Domino Upgrade Application (DUS) support.
	(migrating foreign directory users) */
#define ERR_DUS_EXTENDED_ERROR 	(PKG_REG+211)
	errortext(ERR_DUS_EXTENDED_ERROR, 	"The upgrade application '%s' returned this error: %s.")

#define ERR_DUS_NO_MORE_USERS		(PKG_REG+212)
	errortext(ERR_DUS_NO_MORE_USERS,	"No more people available from the current upgrade application.")
#define ERR_DUS_NO_MORE_GROUPS		(PKG_REG+213)
	errortext(ERR_DUS_NO_MORE_GROUPS,	"No more groups available from the current upgrade application.")
#define ERR_DUS_NO_USERS		 	(PKG_REG+214)
	errortext(ERR_DUS_NO_USERS,	 	"No people are available from the current upgrade application.")
#define ERR_DUS_CONTEXT_CORRUPT  	(PKG_REG+215)
	errortext(ERR_DUS_CONTEXT_CORRUPT,	"Context information for the current Notes Upgrade Application has been corrupted.")
#define ERR_DUS_UPGRADE_DLL_FAILED 	(PKG_REG+216)
	errortext(ERR_DUS_UPGRADE_DLL_FAILED, 	"The upgrade application dll '%s' could not be found or could not be loaded/initialized.")
#define ERR_DUS_RETRIEVE_FAILED 	(PKG_REG+217)
	errortext(ERR_DUS_RETRIEVE_FAILED,	"Person information could not be retrieved from the current upgrade application.")
#define ERR_DUS_NO_UPGRADE_DLLPATH 	(PKG_REG+218)
	errortext(ERR_DUS_NO_UPGRADE_DLLPATH, 	"No file path was specified for the current upgrade application.")
#define ERR_DUS_MAIL_CONVERSION_FAILED 	(PKG_REG+219)
	errortext(ERR_DUS_MAIL_CONVERSION_FAILED, 	"Mail file conversion for the migrating user '%s' failed or is incomplete.")
#define ERR_DUS_EXTENDED_ERROR2 	(PKG_REG+220)
	errortext(ERR_DUS_EXTENDED_ERROR2, 	"The upgrade application for '%s' returned this error: %s.")
#define ERR_DUS_EXTENDED_ERROR3 	(PKG_REG+221)
	errortext(ERR_DUS_EXTENDED_ERROR3, 	"The current upgrade application returned this error: %s.")
#define ERR_DUS_SKIP_THIS_GROUP 	(PKG_REG+222)
	errortext(ERR_DUS_SKIP_THIS_GROUP, 	"The current group '%s' and its members will not be migrated into Notes.")
#define ERR_DUS_REG_SERVER_DOWN 	(PKG_REG+223)
	errortext(ERR_DUS_REG_SERVER_DOWN, 	"The registration server is down or the Domino directory on that registration server is unavailable.  Change registration servers and try migration again.")
#define ERR_DUS_GROUPWISE_DLLS_ABSENT		(PKG_REG+224)
	errortext(ERR_DUS_GROUPWISE_DLLS_ABSENT, "One or more Groupwise dlls required for Groupwise to Notes migration are not present.")
#define ERR_DUS_NETSCAPE_DLLS_ABSENT		(PKG_REG+225)
	errortext(ERR_DUS_NETSCAPE_DLLS_ABSENT, "One or more Netscape dlls required for Netscape to Notes migration are not present.")
#define ERR_REG_DUS_MAIL_CONVERSION_ONLY 	(PKG_REG+226)
	errortext(ERR_REG_DUS_MAIL_CONVERSION_ONLY, "The mail system must be set to 'None' for users migrated with the 'Convert mail ONLY' option.")
#define STR_REG_DUS_PREREG_NOTIFY		 	(PKG_REG+227)
	stringtext(STR_REG_DUS_PREREG_NOTIFY, "Notifying the current DUS (Domino Upgrade Services) application that registration is about to begin...")
#define ERR_REG_CERT_ALT_LANGUAGE_PROMPT	(PKG_REG+228)
	errortext(ERR_REG_CERT_ALT_LANGUAGE_PROMPT,	"The certifier you have selected does not contain the alternate language tag '%s' (set for the current user).  If you continue, the alternate language tag will be set to 'none' for the selected user(s).  Do you want to continue?")

/*	211 - 230 reserved for Domino Upgrade Application (DUS) support.
	(migrating foreign directory users) */

#define	ERR_REG_CREATINGADDRESSFILE	(PKG_REG+231)
	stringtext(ERR_REG_CREATINGADDRESSFILE,	"Creating your address book")
#define ERR_REG_CREATING_STATS_DB		(PKG_REG+232)
	stringtext(ERR_REG_CREATING_STATS_DB,	"Creating Statistics & Events Configuration Database...")
#define ERR_REG_SERVER_NETWORK_SETTINGS (PKG_REG+233)
	stringtext(ERR_REG_SERVER_NETWORK_SETTINGS, "Updating network settings")
#define ERR_REG_SERVER_CONFIGURE_SMTP (PKG_REG+234)
	stringtext(ERR_REG_SERVER_CONFIGURE_SMTP, "Configuring SMTP")
#define ERR_REG_MINPSWDCHARS			(PKG_REG+235)
	errortext(ERR_REG_MINPSWDCHARS,	"Your password is insufficiently complex. Add more characters or varied characters.")
#define ERR_REG_CREATING_ADMINREQ_DB			(PKG_REG+236)
	stringtext(ERR_REG_CREATING_ADMINREQ_DB,	"Creating Administration Request Database...")
#define ERR_REG_ALT_NAME_NOT_UNIQUE		(PKG_REG+237)
	errortext(ERR_REG_ALT_NAME_NOT_UNIQUE,	"The alternate name '%s' is not unique in the address book.")
#define ERR_REG_CONVERT_ONLY_FAILED		(PKG_REG+238)
	errortext(ERR_REG_CONVERT_ONLY_FAILED,	"Mail conversion failed.  Either the user could not be found or the original full name was not supplied.")
#define STR_REG_YES						(PKG_REG+239)
	stringtext(STR_REG_YES,				"Yes")
#define STR_REG_DATABASES_BM			(PKG_REG+240)
	stringtext(STR_REG_DATABASES_BM,	"Databases")
#define ERR_REG_IMAP_REQUIRES_PASSWORD	(PKG_REG+241)
	errortext(ERR_REG_IMAP_REQUIRES_PASSWORD,	"A Notes password is required for new IMAP mail users.")
#define STR_REG_NO_DC_CONTINUE_PROMPT	(PKG_REG+242)
	stringtext(STR_REG_NO_DC_CONTINUE_PROMPT, "A primary domain controller for the current NT domain cannot be found.  NT Accounts can only be added locally.  Continue?")
#define ERR_NO_SERIAL_PORT				(PKG_REG+243)
	errortext(ERR_NO_SERIAL_PORT,		"You must specify a serial port in order to connect via a modem")
#define STR_REG_LOG_DUPLICATE_NAME		(PKG_REG+244)
	stringtext(STR_REG_LOG_DUPLICATE_NAME,	"The name %a already exits in a different entry in the directory.")
#define ERR_REG_DUPLICATE_NAME			(PKG_REG+245)
	errortext(ERR_REG_DUPLICATE_NAME,	"One of the names to be added to the directory already exists in a different entry in the directory.  See the Notes log for details.")
#define STR_REG_LOG_NAME_REFUSED		(PKG_REG+246)
	errortext(STR_REG_LOG_NAME_REFUSED, "%a refused to accept a name change")
#define ERR_REG_NAB_NOT_PUBLIC			(PKG_REG+247)
	errortext(ERR_REG_NAB_NOT_PUBLIC,	"The Domino directory from the currently selected server is not based on the public directory template (pubnames.ntf).")
#define STR_REG_PERSON_LEFTTOSTORE	  	(PKG_REG+248)
	stringtext(STR_REG_PERSON_LEFTTOSTORE, 	"1 person left to add to the registration queue")
#define STR_REG_PERSON_LEFTTOREAD		(PKG_REG+249)
	stringtext(STR_REG_PERSON_LEFTTOREAD,	"1 person left to retrieve from the registration queue")
#define	ERR_REG_UPDATE_USER_PROMPT		(PKG_REG+250)
	errortext(ERR_REG_UPDATE_USER_PROMPT,	"An entry with the specified person name '%s' is already in the Domino Directory. Update the entry?")
#define	ERR_REG_NO_REG_SERVER_SPECIFIED	(PKG_REG+251)
	errortext(ERR_REG_NO_REG_SERVER_SPECIFIED,	"The registration server is down or was not specified/set.")
#define	ERR_REG_ADDRBOOK_SHORTNAME_EXISTS (PKG_REG+252)
	apitext(ERR_REG_ADDRBOOK_SHORTNAME_EXISTS, "No permission (flag) to modify existing Address Book entry (short name is duplicated)")
#define	ERR_REG_UPDATE_USER_SHORTNAME_PROMPT	(PKG_REG+253)
	errortext(ERR_REG_UPDATE_USER_SHORTNAME_PROMPT,	"A person entry with the short name '%s' already exists in the Domino Directory. Update the entry?")
#define ERR_REG_REQUIRES_PERSON_NOTE	(PKG_REG+254)
	errortext(ERR_REG_REQUIRES_PERSON_NOTE, "Entry found is not a person entry")
#define	ERR_REG_CERTIFIER_NO_RECOVERY_INFO		(PKG_REG+255)
	errortext(ERR_REG_CERTIFIER_NO_RECOVERY_INFO,	"The current certifier ID contains no recovery information and will not allow ID/password recovery on IDs created with this certifier.  The 'EscrowAgent' ID recovery mechanism is no longer supported.\n\nDisplay this warning in the future?")


/* Last available error is PKG_REG+255 */
#endif

