
#ifndef BSAFE_ERR_DEFS
#define	BSAFE_ERR_DEFS


/* BSAFE (Security package) Error Code Definitions			*/

#define	ERR_BSAFE_PSW_PROMPT				(PKG_BSAFE+0)
#ifdef OS400
	errortext(ERR_BSAFE_PSW_PROMPT,			"Enter password (press the F3 key to abort): ")
#else
	errortext(ERR_BSAFE_PSW_PROMPT,			"Enter password (press the Esc key to abort): ")
#endif
#define	ERR_BSAFE_FALSE						(PKG_BSAFE+1)
	internaltext(ERR_BSAFE_FALSE,			"Do not suspend operation")
#define ERR_BSAFE_ALLOCATE					(PKG_BSAFE+2)
	internaltext(ERR_BSAFE_ALLOCATE,		"Error allocating security block")
#define ERR_BSAFE_FREE						(PKG_BSAFE+3)
	internaltext(ERR_BSAFE_FREE,			"Error freeing security block")
#define ERR_BSAFE_ENTRY						(PKG_BSAFE+4)
	internaltext(ERR_BSAFE_ENTRY,			"Error initializing security block")
#define ERR_BSAFE_EXIT						(PKG_BSAFE+5)
	internaltext(ERR_BSAFE_EXIT,			"Error cleaning up security block")
#define ERR_BSAFE_PAUSE						(PKG_BSAFE+6)
	internaltext(ERR_BSAFE_PAUSE,			"Security operation temporarily suspended")
#define ERR_BSAFE_BADKEY					(PKG_BSAFE+7)
	errortext(ERR_BSAFE_BADKEY,				"The encrypted data has been modified or the wrong key was used to decrypt it")
#define ERR_BSAFE_BADCTX					(PKG_BSAFE+8)
	errortext(ERR_BSAFE_BADCTX,				"Bad Security Context information")
#define ERR_BSAFE_BADOPCODE					(PKG_BSAFE+9)
	errortext(ERR_BSAFE_BADOPCODE,			"Illegal Security function code")
#define	ERR_BSAFE_BADCHECKSUM				(PKG_BSAFE+10)
	errortext(ERR_BSAFE_BADCHECKSUM,		"The encrypted data has been modified or the wrong key was used to decrypt it")
#define	ERR_BSAFE_BADDATA					(PKG_BSAFE+11)
	errortext(ERR_BSAFE_BADDATA,			"The encrypted data has been modified or the wrong key was used to decrypt it")

#define ERR_BSAFE_BUG_1						(PKG_BSAFE+12)
	errortext(ERR_BSAFE_BUG_1,				"BSAFE package software error #1")
#define ERR_BSAFE_POOLFULL					(PKG_BSAFE+13)
	errortext(ERR_BSAFE_POOLFULL,			"Insufficient memory - BSAFE pool is full")

#define ERR_BSAFE_CACHEFULL					(PKG_BSAFE+14)
	errortext(ERR_BSAFE_CACHEFULL,			"Insufficient memory - BSAFE Name lookup cache is full")

#define ERR_BSAFE_TOOSMALL					(PKG_BSAFE+15)
	errortext(ERR_BSAFE_TOOSMALL,			"Buffer used to receive cryptographic output was too small")
#define ERR_BSAFE_BAD_ATTRIBUTES			(PKG_BSAFE+16)
	errortext(ERR_BSAFE_BAD_ATTRIBUTES,		"Inconsistent name attributes")
#define ERR_BSAFE_MDLENGTH					(PKG_BSAFE+17)
	errortext(ERR_BSAFE_MDLENGTH,			"Bad Message Digest length")
#define ERR_BSAFE_NOT_ALLOWED				(PKG_BSAFE+18)
	errortext(ERR_BSAFE_NOT_ALLOWED,		"Attempted encryption operation is not supported by this version of Notes.")
#define	ERR_BSAFE_ILLEGAL_IDFILE			(PKG_BSAFE+19)
	errortext(ERR_BSAFE_ILLEGAL_IDFILE,		"The specified ID file may only be used inside of North America.")
#define	ERR_BSAFE_BAD_PI_VERSION			(PKG_BSAFE+20)
	errortext(ERR_BSAFE_BAD_PI_VERSION,		"The public key or certificate version stored in the Address Book is not supported.")
#define	ERR_BSAFE_BAD_PI_CHECKSUM			(PKG_BSAFE+21)
	errortext(ERR_BSAFE_BAD_PI_CHECKSUM,	"The public key or certificate stored in the Address Book has been corrupted.")
#define ERR_BSAFE_MISSING_PI				(PKG_BSAFE+22)
	errortext(ERR_BSAFE_MISSING_PI,			"There is no certificate in the Address Book.")
#define ERR_BSAFE_TABLE_MUST_BE_HI			(PKG_BSAFE+23)
	errortext(ERR_BSAFE_TABLE_MUST_BE_HI, 	"The supplied certificate table does not contain any hierarchical certificates")
#define	ERR_BSAFE_NO_COMMON_CERT			(PKG_BSAFE+24)
	errortext(ERR_BSAFE_NO_COMMON_CERT,		"No certificates in common")
#define	ERR_BSAFE_CERTTABLE_VERSION			(PKG_BSAFE+25)
	errortext(ERR_BSAFE_CERTTABLE_VERSION,	"Unrecognized certificate table version")
#define ERR_BSAFE_ILLUSE_GENID				(PKG_BSAFE+26)
	errortext(ERR_BSAFE_ILLUSE_GENID,		"Illegal use of an ID generator file")
#define	ERR_BSAFE_NOT_GENID					(PKG_BSAFE+27)
	errortext(ERR_BSAFE_NOT_GENID,			"Specified file is not an ID generator file")
#define	ERR_BSAFE_NOSUCH_PRVKEY				(PKG_BSAFE+28)
	errortext(ERR_BSAFE_NOSUCH_PRVKEY,		"Specified private key does not exist")
#define ERR_BSAFE_NOSUCH_ESCROW				(PKG_BSAFE+29)
	errortext(ERR_BSAFE_NOSUCH_ESCROW,		"This version of the software does not know the key of a required escrow authority")
#define	ERR_BSAFE_NETFILE					(PKG_BSAFE+30)
	errortext(ERR_BSAFE_NETFILE,			"WARNING: Network-based ID files should be password protected!")
#define	ERR_BSAFE_BAD_IDFILE_VERSION 		(PKG_BSAFE+31)
	errortext(ERR_BSAFE_BAD_IDFILE_VERSION,	"Unsupported ID file version.")
#define	ERR_BSAFE_NOSUCH_PUBKEY				(PKG_BSAFE+32)
	errortext(ERR_BSAFE_NOSUCH_PUBKEY,		"Specified public key does not exist")
#define ERR_BSAFE_PROC_NOT_INITED			(PKG_BSAFE+33)
	errortext(ERR_BSAFE_PROC_NOT_INITED,	"Process has not initialized with the security package")
#define ERR_BSAFE_SUBPROCESS				(PKG_BSAFE+34)
	errortext(ERR_BSAFE_SUBPROCESS,			"A sub-process cannot change to a new ID file.")
#define	ERR_BSAFE_NOMEMORY					(PKG_BSAFE+35)
	errortext(ERR_BSAFE_NOMEMORY,			"Insufficient memory for attempted security operation.")
#define	ERR_BSAFE_ILLFUNC					(PKG_BSAFE+36)
	debugtext(ERR_BSAFE_ILLFUNC,			"Unknown security function code.")
#define ERR_BSAFE_NULLPARAM					(PKG_BSAFE+37)
	debugtext(ERR_BSAFE_NULLPARAM,			"Illegal null parameter to security function.")
#define ERR_BSAFE_DISPLAY_IDFILE			(PKG_BSAFE+38)
	stringtext(ERR_BSAFE_DISPLAY_IDFILE,	"The ID file being used is: ")
#define ERR_BSAFE_ILLUSE_SAFECOPY			(PKG_BSAFE+39)
	errortext(ERR_BSAFE_ILLUSE_SAFECOPY,	"The ID file is a safe copy and cannot be used for that purpose.")
#define ERR_BSAFE_USER_ABORT				(PKG_BSAFE+40)
	stringtext(ERR_BSAFE_USER_ABORT,		"The prompt for password was aborted by user")
#define ERR_BSAFE_ID_PROTECTED				(PKG_BSAFE+41)
	errortext(ERR_BSAFE_ID_PROTECTED,		"Cannot access or create the ID file")
#define ERR_BSAFE_ID_CREATE					(PKG_BSAFE+42)
	errortext(ERR_BSAFE_ID_CREATE,			"ID file cannot be created")
#define ERR_BSAFE_ID_TRUNC					(PKG_BSAFE+43)
#define ERR_BSAFE_CORRUPTIDFILE				ERR_BSAFE_ID_TRUNC
	errortext(ERR_BSAFE_ID_TRUNC,			"The specified ID file has been corrupted, or is not an ID file")
#define ERR_BSAFE_ID_INVFILENAME			(PKG_BSAFE+44)
	errortext(ERR_BSAFE_ID_INVFILENAME,		"Illegal ID file name: too long or uses invalid syntax")
#define ERR_BSAFE_ID_WRITETRUNC				(PKG_BSAFE+45)
	errortext(ERR_BSAFE_ID_WRITETRUNC,		"Cannot write to ID file; either it is READ-ONLY or the disk is out of space")
#define ERR_BSAFE_ID_INVDRIVE				(PKG_BSAFE+46)
	errortext(ERR_BSAFE_ID_INVDRIVE,		"Invalid drive specified for ID file")
#define ERR_BSAFE_NON_EXISTENT				(PKG_BSAFE+47)
	errortext(ERR_BSAFE_NON_EXISTENT,		"The requested item does not exist")
#define ERR_BSAFE_NEK_NOT_FOUND				(PKG_BSAFE+48)
	errortext(ERR_BSAFE_NEK_NOT_FOUND,		"You don't have any of the specified encryption keys")
#define ERR_BSAFE_KEY_NOT_FOUND				(PKG_BSAFE+49)
	errortext(ERR_BSAFE_KEY_NOT_FOUND,		"The cryptographic key was not found")
#define ERR_BSAFE_KEY_INV_FORMAT			(PKG_BSAFE+50)
	errortext(ERR_BSAFE_KEY_INV_FORMAT,		"The cryptographic key's format is invalid")
#define ERR_BSAFE_NO_KEYS					(PKG_BSAFE+51)
	errortext(ERR_BSAFE_NO_KEYS, 			"Your ID file does not contain any encryption keys")
#define ERR_BSAFE_UNKNOWN_CERTIFICATE		(PKG_BSAFE+52)
	errortext(ERR_BSAFE_UNKNOWN_CERTIFICATE,"Unrecognized or unsupported certificate type")
#define ERR_BSAFE_UNKNOWN_IDFILE			(PKG_BSAFE+53)
	errortext(ERR_BSAFE_UNKNOWN_IDFILE, 	"Unrecognized or unsupported ID File type")
#define ERR_BSAFE_UNKNOWN_DOCKEY			(PKG_BSAFE+54)
	errortext(ERR_BSAFE_UNKNOWN_DOCKEY, 	"Unrecognized or unsupported document encryption key type stored in the ID file")
#define ERR_BSAFE_UNKNOWN_USERINFO			(PKG_BSAFE+55)
	errortext(ERR_BSAFE_UNKNOWN_USERINFO, 	"Unrecognized or unsupported user-information structure")
#define ERR_BSAFE_UNKNOWN_ITEM				(PKG_BSAFE+56)
	debugtext(ERR_BSAFE_UNKNOWN_ITEM,		"Internal error: unknown BSAFE-item code or version")
#define ERR_BSAFE_INV_DNAME					(PKG_BSAFE+57)
	debugtext(ERR_BSAFE_INV_DNAME,			"Invalid name syntax")

/* Note: next error message name is misleading; the error was reused for
*		exceeding a 64K buffer length in a variety of cases.
*/

#define ERR_BSAFE_ODSCERT_TOOBIG			(PKG_BSAFE+58)
	errortext(ERR_BSAFE_ODSCERT_TOOBIG,		"Internal error: 64K max buffer length exceeded")
#define ERR_BSAFE_UNKNOWN_UDO				(PKG_BSAFE+59)
	errortext(ERR_BSAFE_UNKNOWN_UDO, 		"Unrecognized or unsupported user-descriptor object found in the ID file")
#define ERR_BSAFE_FILE_NOT_OPENED			(PKG_BSAFE+60)
	errortext(ERR_BSAFE_FILE_NOT_OPENED,	"You must first open the ID file before attempting that operation")

#define STR_BSAFE_RSA_PRIMARY				(PKG_BSAFE+61)
	stringtext(STR_BSAFE_RSA_PRIMARY,		"Primary RSA")
#define STR_BSAFE_RSA_SECONDARY				(PKG_BSAFE+62)
	stringtext(STR_BSAFE_RSA_SECONDARY,		"Secondary RSA")
#define STR_BSAFE_RC2						(PKG_BSAFE+63)
	stringtext(STR_BSAFE_RC2,				"RC2")
#define STR_BSAFE_RC4						(PKG_BSAFE+64)
	stringtext(STR_BSAFE_RC4,				"RC4")
#define STR_BSAFE_USA						(PKG_BSAFE+65)
	stringtext(STR_BSAFE_USA,				"North American")
#define	STR_BSAFE_NONUSA					(PKG_BSAFE+66)
	stringtext(STR_BSAFE_NONUSA,			"International")
#define STR_BSAFE_SIGNED_MAIL				(PKG_BSAFE+67)
	stringtext(STR_BSAFE_SIGNED_MAIL,		"Signed mail using %d bit %e key")
#define STR_BSAFE_SEALED_DOC				(PKG_BSAFE+68)
	stringtext(STR_BSAFE_SEALED_DOC,		"Encrypted document using %d/%d bit %e/%e keys")
#define STR_BSAFE_CERTIFY					(PKG_BSAFE+69)
	stringtext(STR_BSAFE_CERTIFY, 			"Created certificate using %d bit %e key")
#define STR_BSAFE_IDFILE_ENCRYPTED			(PKG_BSAFE+70)
	stringtext(STR_BSAFE_IDFILE_ENCRYPTED,	"ID file is encrypted with %d bit %e key")
#define STR_BSAFE_AUTHENTICATED				(PKG_BSAFE+71)
	stringtext(STR_BSAFE_AUTHENTICATED,		"Authenticated: %d bit Ticket, %d bit %e session key, %e on RC4 escrow.")
#define STR_BSAFE_FORCED_AUTH				(PKG_BSAFE+72)
	stringtext(STR_BSAFE_FORCED_AUTH,		"Authentication is being forced due to secure channel setting.")
#define STR_BSAFE_CERT_EXPIRES				(PKG_BSAFE+73)
	stringtext(STR_BSAFE_CERT_EXPIRES,		"WARNING:  Your certificate issued to %s by %s will expire on %s. Request a new certificate by choosing File - Tools - User ID - Certificate - Request Certificate.")
#define STR_BSAFE_CERT_EXPIRED				(PKG_BSAFE+74)
	stringtext(STR_BSAFE_CERT_EXPIRED,		"WARNING:  Your certificate issued to %s by %s expired on %s and can no longer be used.  Contact your Domino administrator.")
#define STR_BSAFE_INVALID					(PKG_BSAFE+75)
	stringtext(STR_BSAFE_INVALID,			"Invalid")
#define STR_BSAFE_UNKNOWN					(PKG_BSAFE+76)
	stringtext(STR_BSAFE_UNKNOWN,			"Unknown")
#define	ERR_BSAFE_IDFILE_LOCKED				(PKG_BSAFE+77)
	errortext(ERR_BSAFE_IDFILE_LOCKED,		"The ID File is in use elsewhere and cannot be modified")
#define ERR_BSAFE_NEK_EXISTS				(PKG_BSAFE+78)
	errortext(ERR_BSAFE_NEK_EXISTS,			"Cannot add the encryption key to your ID file.  A key with that name already exists.")
#define ERR_BSAFE_KFM_INVREADOPT			(PKG_BSAFE+79)
	debugtext(ERR_BSAFE_KFM_INVREADOPT,		"Software error: conflicting read ID File options")
#define ERR_BSAFE_MERGE_NONCOPY				(PKG_BSAFE+80)
	errortext(ERR_BSAFE_MERGE_NONCOPY,		"The certificate(s) have not been issued to you and cannot be merged into your ID file.  They have been issued to")
#define ERR_BSAFE_MERGE_NOPRVKEY			(PKG_BSAFE+81)
	errortext(ERR_BSAFE_MERGE_NOPRVKEY,		"The Public Key cannot be accepted since there is no matching Private Key found in the ID file.")
#define	ERR_BSAFE_NONAMECHANGE				(PKG_BSAFE+82)
	errortext(ERR_BSAFE_NONAMECHANGE,		"If you change your name you will lose all of your certificates.  Do you want to continue?")
#define ERR_BSAFE_NOMERGECERT				(PKG_BSAFE+83)
	errortext(ERR_BSAFE_NOMERGECERT,		"There are no certificates to be merged into your ID file")
#define	ERR_BSAFE_INVUSERIDFILE				(PKG_BSAFE+84)
	errortext(ERR_BSAFE_INVUSERIDFILE,		"Your ID file has been corrupted, or is not an ID file.")
#define ERR_BSAFE_CORRUPTFILE				(PKG_BSAFE+85)
	errortext(ERR_BSAFE_CORRUPTFILE,		"The specified ID file has been corrupted, or is not an ID file.")
#define ERR_BSAFE_REQUIRES_NONFLATID 		(PKG_BSAFE+86)
	errortext(ERR_BSAFE_REQUIRES_NONFLATID, "This request is not supported with the version of your ID file.  An ID file containing a hierarchical name is required.")
#define ERR_BSAFE_NO_CROSS_CERT		 		(PKG_BSAFE+87)
	errortext(ERR_BSAFE_NO_CROSS_CERT,		"The Address Book does not contain a cross certificate capable of validating the public key.")
#define ERR_BSAFE_INCOMPLETE_CERTTABLE	 	(PKG_BSAFE+88)
	errortext(ERR_BSAFE_INCOMPLETE_CERTTABLE, "There are not enough certificates attached to the document to verify the identity of its signer")
#define ERR_BSAFE_ILLUSE_CERTIFIER			(PKG_BSAFE+89)
	errortext(ERR_BSAFE_ILLUSE_CERTIFIER,	"Illegal use of a Certifier ID file")
#define ERR_BSAFE_MUSTBE_CERTIFIER			(PKG_BSAFE+90)
	errortext(ERR_BSAFE_MUSTBE_CERTIFIER,	"The ID file is not a Certifier ID file and cannot be used to issue certificates")
#define ERR_BSAFE_WRITEPROTECTED			(PKG_BSAFE+91)
	errortext(ERR_BSAFE_WRITEPROTECTED,		"The ID file is write protected")
#define ERR_BSAFE_NOPSW_ON_SAFECOPY			(PKG_BSAFE+92)
	errortext(ERR_BSAFE_NOPSW_ON_SAFECOPY,	"This is a safe-copy version of an ID file and cannot be password protected")
#define ERR_BSAFE_YOU_MUST_BE_HI			(PKG_BSAFE+93)
	errortext(ERR_BSAFE_YOU_MUST_BE_HI,		"The local system cannot complete the operation because it is not running with a hierarchical name")
#define ERR_BSAFE_WRONG_SUBJECT_KEY			(PKG_BSAFE+94)
	errortext(ERR_BSAFE_WRONG_SUBJECT_KEY,	"The public key that is being used does not match the one that was certified.")
#define ERR_BSAFE_ILL_CERTTABLE				(PKG_BSAFE+95)
	errortext(ERR_BSAFE_ILL_CERTTABLE,		"The supplied certificate table used to validate the signer's public key is improperly formed")
#define ERR_BSAFE_CERTIFIER_MUST_BE_HI		(PKG_BSAFE+96)
	errortext(ERR_BSAFE_CERTIFIER_MUST_BE_HI, "You must specify a hierarchical certifier ID")
#define ERR_BSAFE_EXTERNAL_PASSWORD			(PKG_BSAFE+97)
	errortext(ERR_BSAFE_EXTERNAL_PASSWORD,	"Password Externally Supplied")
#define ERR_BSAFE_EXTERNAL_PWD_AND_DATA		(PKG_BSAFE+98)
	errortext(ERR_BSAFE_EXTERNAL_PWD_AND_DATA, "Password and Data Externally Supplied")
#define ERR_BSAFE_FLAT_KEY_TOO_BIG			(PKG_BSAFE+99)
	errortext(ERR_BSAFE_FLAT_KEY_TOO_BIG,	"RSA key size limit for a flat ID exceeded")
#define STR_BSAFE_CERTIFYING				(PKG_BSAFE+100)
	stringtext(STR_BSAFE_CERTIFYING,		"Certifying %A")
#define	STR_BSAFE_CERTIFIED					(PKG_BSAFE+101)
	stringtext(STR_BSAFE_CERTIFIED,			"%A successfully certified")
#define STR_BSAFE_REPLACE_ANCESTRY			(PKG_BSAFE+102)
	stringtext(STR_BSAFE_REPLACE_ANCESTRY,	"A certificate hierarchy has already been assigned to this ID.  Do you wish to continue and replace it?")
#define ERR_BSAFE_CANCELED					(PKG_BSAFE+103)
	errortext(ERR_BSAFE_CANCELED,			"Operation canceled")
#define STR_BSAFE_UPGRADETOHI				(PKG_BSAFE+104)
	stringtext(STR_BSAFE_UPGRADETOHI,		"The ID file will be upgraded to hierarchical format.  Do you wish to continue?")
#define ERR_BSAFE_ASSIGNED_TO_DIFF_LANG		(PKG_BSAFE+105)
	stringtext(ERR_BSAFE_ASSIGNED_TO_DIFF_LANG,	"That name has already been associated with another language specifier.")


/* Use OSLoadSubString to load substrings - english total length<80! 
*/

#define STR_BSAFE_LIST_IDFILE				(PKG_BSAFE+106)
	stringtext(STR_BSAFE_LIST_IDFILE,		"Non-Hierarchical ID|Hierarchical User or Server|Hierarchical Certifier")

#define IDX_BSAFE_IDFILE_FLAT		1
#define IDX_BSAFE_IDFILE_HIUSER		2
#define IDX_BSAFE_IDFILE_HICA		3

#define STR_BSAFE_LIST_MISCID				(PKG_BSAFE+107)
	stringtext(STR_BSAFE_LIST_MISCID,		"Safe Copy|Unknown ID type|Internet Certifier| ")

#define IDX_BSAFE_MISCID_SAFE		1
#define IDX_BSAFE_MISCID_UNKNOWN	2
#define IDX_BSAFE_MISCID_INETCA		3
#define IDX_BSAFE_MISCID_BLANK		4

#define ERR_BSAFE_CERT_HAS_ALTNAME			(PKG_BSAFE+108)
	errortext(ERR_BSAFE_CERT_HAS_ALTNAME,	"The operation cannot be completed because the certificate contains an alternate name")
#define STR_BSAFE_HICERTIFIERID				(PKG_BSAFE+109)
	stringtext(STR_BSAFE_HICERTIFIERID,		"Hierarchical Certifier")
#define STR_BSAFE_UNKNOWNID					(PKG_BSAFE+110)
	stringtext(STR_BSAFE_UNKNOWNID,			"Unknown ID type")


#define	ERR_BSAFE_USA_KEY_ONLY				(PKG_BSAFE+111)
	errortext(ERR_BSAFE_USA_KEY_ONLY,		"This key may only be stored in ID files with North American licenses")
#define ERR_BSAFE_ID_READ_ONLY				(PKG_BSAFE+112)
	errortext(ERR_BSAFE_ID_READ_ONLY,		"The ID file was not opened for write access")
#define ERR_BSAFE_NO_PUBLIC_INFO			(PKG_BSAFE+113)
	errortext(ERR_BSAFE_NO_PUBLIC_INFO,		"Your public key was not found in the Name and Address Book")
#define ERR_BSAFE_TOOMANY_ORG_UNITS			(PKG_BSAFE+114)
	errortext(ERR_BSAFE_TOOMANY_ORG_UNITS,	"You can create only as many as four Organizational Unit levels")
#define ERR_BSAFE_MUSTBE_HIERARCHICAL		(PKG_BSAFE+115)
	errortext(ERR_BSAFE_MUSTBE_HIERARCHICAL, "This request is not supported for the specified ID file.  An ID file containing a hierarchical name is required.")
#define ERR_BSAFE_ID_DRIVE_NOT_READY		(PKG_BSAFE+116)
	errortext(ERR_BSAFE_ID_DRIVE_NOT_READY,	"The disk drive specified for the ID file is not ready")
#define ERR_BSAFE_ID_DISK					(PKG_BSAFE+117)
	errortext(ERR_BSAFE_ID_DISK,			"Cannot update the ID file; insufficient disk space")
#define ERR_BSAFE_ID_IOERROR	  			(PKG_BSAFE+118)
	errortext(ERR_BSAFE_ID_IOERROR,			"I/O error experienced while accessing the ID file")
#define ERR_BSAFE_PASSWORD_REQUIRED			(PKG_BSAFE+119)
	errortext(ERR_BSAFE_PASSWORD_REQUIRED,	"A password is required for this ID file")
#define ERR_BSAFE_BAD_AUTH_CODE				(PKG_BSAFE+120)
	errortext(ERR_BSAFE_BAD_AUTH_CODE,		"The authentication code has failed the consistency check")
#define ERR_BSAFE_ILL_AUTH_CODE_VERSION		(PKG_BSAFE+121)
	errortext(ERR_BSAFE_ILL_AUTH_CODE_VERSION, "The authentication code version number is not supported")
#define ERR_BSAFE_NEWNAME_TOO_LONG			(PKG_BSAFE+122)
	errortext(ERR_BSAFE_NEWNAME_TOO_LONG,	"Cannot create certificate, resultant subject name would be too long")
#define ERR_BSAFE_CERT_NOT_ANCESTOR			(PKG_BSAFE+123)
	errortext(ERR_BSAFE_CERT_NOT_ANCESTOR,	"The certifier is not an ancestor of the subject in the certificate.")
#define ERR_BSAFE_ILL_ATFUNC				(PKG_BSAFE+124)
	errortext(ERR_BSAFE_ILL_ATFUNC,			"Unrecognized or unsupported @CERTIFICATE code")
#define ERR_BSAFE_CERTIFIER_NOT_IN_NAB		(PKG_BSAFE+125)
	errortext(ERR_BSAFE_CERTIFIER_NOT_IN_NAB, "A required certifier entry was not found in the Name and Address Book; consult the Notes Log for details on the specific entry")
#define ERR_BSAFE_ILL_DISTINFO				(PKG_BSAFE+126)
	errortext(ERR_BSAFE_ILL_DISTINFO,		"Unrecognized or unsupported Distinguished Name structure")
#define ERR_BSAFE_INSUF_INPUT_ARGS			(PKG_BSAFE+127)
	errortext(ERR_BSAFE_INSUF_INPUT_ARGS,	"Internal error: too few parametes passed in subroutine call")
#define ERR_BSAFE_CERT_MISMATCH				(PKG_BSAFE+128)
	errortext(ERR_BSAFE_CERT_MISMATCH,		"Either the certificates' issuers or the certificates' subjects don't match")
#define ERR_BSAFE_ILLUSE_XCERT				(PKG_BSAFE+129)
	errortext(ERR_BSAFE_ILLUSE_XCERT,		"A cross-certificate was illegally used as a substitute for an ordinary certificate")
#define ERR_BSAFE_TOO_MANY_CERTS			(PKG_BSAFE+130)
	errortext(ERR_BSAFE_TOO_MANY_CERTS,		"Certificate table could not be constructed because there are too many certificates")
#define ERR_BSAFE_TOO_FEW_CERTS				(PKG_BSAFE+131)
	errortext(ERR_BSAFE_TOO_FEW_CERTS,		"The supplied Certificate Table is missing a required certificate to complete the operation")
#define ERR_BSAFE_ID_MUST_BE_HI				(PKG_BSAFE+132)
	errortext(ERR_BSAFE_ID_MUST_BE_HI,		"This operation is only supported for ID file's containing hierarchical names")
#define ERR_BSAFE_INV_KFHANDLE				(PKG_BSAFE+133)
	errortext(ERR_BSAFE_INV_KFHANDLE,		"Invalid KFHANDLE")
#define ERR_BSAFE_FILE_LOCKED				(PKG_BSAFE+134)
	errortext(ERR_BSAFE_FILE_LOCKED,		"The ID file is locked by another process. Try again later")
#define ERR_BSAFE_MUST_BE_SERVER			(PKG_BSAFE+135)
	errortext(ERR_BSAFE_MUST_BE_SERVER,		"Only the server process is allowed to attempt that operation")
#define ERR_BSAFE_INAPPROPRIATE_ORGUNIT		(PKG_BSAFE+136)
	errortext(ERR_BSAFE_INAPPROPRIATE_ORGUNIT, "Org Unit may only be supplied when upgrading flat to hierarchical")


#define STR_BSAFE_ID_FULL					(PKG_BSAFE+137)
     stringtext(STR_BSAFE_ID_FULL,			"Notes")
#define STR_BSAFE_ID_DESKTOP				(PKG_BSAFE+138)
     stringtext(STR_BSAFE_ID_DESKTOP,		"Notes Desktop")
#define ERR_BSAFE_INVCERT_DATA				(PKG_BSAFE+139)
	errortext(ERR_BSAFE_INVCERT_DATA,		"Error processing certificate created by %s for %s")
#define ERR_BSAFE_INVCROSSCERT_SIG			(PKG_BSAFE+140)
	errortext(ERR_BSAFE_INVCROSSCERT_SIG,	"The signature on the cross certificate was found to be invalid.  Check the log file for details.")
#define ERR_BSAFE_WRONG_CERT_SUBJECT		(PKG_BSAFE+141)
	errortext(ERR_BSAFE_WRONG_CERT_SUBJECT,	"The certificate contains the wrong subject name")
#define ERR_BSAFE_WRONG_CERT_ISSUER			(PKG_BSAFE+142)
	errortext(ERR_BSAFE_WRONG_CERT_ISSUER,	"The certificate contains the wrong issuer name")

#define STR_BSAFE_CROSS_CERTIFYING			(PKG_BSAFE+143)
	stringtext(STR_BSAFE_CROSS_CERTIFYING,	"Cross certifying %A")
#define	STR_BSAFE_CROSS_CERTIFIED			(PKG_BSAFE+144)
	stringtext(STR_BSAFE_CROSS_CERTIFIED,	"%A successfully cross certified")

#define ERR_BSAFE_INVCERT_SIG				(PKG_BSAFE+145)
	errortext(ERR_BSAFE_INVCERT_SIG,		"The signature on the certificate was found to be invalid.  Check the log file for details.")

#define STR_BSAFE_MAX_IBULKDATAKEY			(PKG_BSAFE+146)
#ifdef FRANCE_ENGLISH
	stringtext(STR_BSAFE_MAX_IBULKDATAKEY,	"40")
#else
	stringtext(STR_BSAFE_MAX_IBULKDATAKEY,	"64")
#endif

#define ERR_BSAFE_WRONG_SUBJECT_KEY_SRV			(PKG_BSAFE+147)
	errortext(ERR_BSAFE_WRONG_SUBJECT_KEY_SRV, "The public key that is being used does not match the one that was certified.  Check the server's log file for details.")
#define ERR_BSAFE_WRONG_SUBJECT_KEY_LOC			(PKG_BSAFE+148)
	errortext(ERR_BSAFE_WRONG_SUBJECT_KEY_LOC,	"The public key that is being used does not match the one that was certified.  Check the local log file for details.")
#define ERR_BSAFE_CERT_NOT_ANCESTOR_SRV			(PKG_BSAFE+149)
	errortext(ERR_BSAFE_CERT_NOT_ANCESTOR_SRV,	"The certifier is not an ancestor of the subject in the certificate.  Check the server's log file for details.")
#define ERR_BSAFE_CERT_NOT_ANCESTOR_LOC			(PKG_BSAFE+150)
	errortext(ERR_BSAFE_CERT_NOT_ANCESTOR_LOC,	"The certifier is not an ancestor of the subject in the certificate.  Check the local log file for details.")

#define ERR_BSAFE_ADDBOOK_CERT_ENTRY			(PKG_BSAFE+151)
	errortext(ERR_BSAFE_ADDBOOK_CERT_ENTRY,		"Error locating an Address Book entry for Certifier %s")


/* (PKG_BSAFE ends at 151 */


#define	ERR_BSAFE2_ATTRIBUTE_UNKNOWN			(PKG_BSAFE2+0)
	errortext(ERR_BSAFE2_ATTRIBUTE_UNKNOWN,		"Attribute type is Unrecognized ")

#define	ERR_BSAFE2_UNABLE_TO_PARSE_CERT 		(PKG_BSAFE2+1)
	errortext(ERR_BSAFE2_UNABLE_TO_PARSE_CERT,	"Unable to Parse Certificate ")

#define	ERR_BSAFE2_BAD_RECOVERY_INFO 	    	(PKG_BSAFE2+2)
	errortext(ERR_BSAFE2_BAD_RECOVERY_INFO,		"Nonexistent or invalid recovery information")

#define	ERR_BSAFE2_KEY_USAGE_RESTRICTION 		(PKG_BSAFE2+3)
	errortext(ERR_BSAFE2_KEY_USAGE_RESTRICTION,	"A cross certificate will not be made due to key usage restrictions in the input certificate.")

#define ERR_BSAFE_BIG_CERT_ELEMENT				(PKG_BSAFE2+4)
	errortext (ERR_BSAFE_BIG_CERT_ELEMENT,		"Certificate element too large for processing.")
#define ERR_BSAFE_NAMELIST_VERSION				(PKG_BSAFE2+5)
	errortext (ERR_BSAFE_NAMELIST_VERSION,		"Unrecognized name list version.")
#define ERR_BSAFE_NAMELIST_MALFORMED			(PKG_BSAFE2+6)
	errortext (ERR_BSAFE_NAMELIST_MALFORMED,	 "The name list is improperly formed and may has been corrupted.")
#define ERR_BSAFE_NAMELIST_NOSUCH_INDEX			(PKG_BSAFE2+7)
	errortext (ERR_BSAFE_NAMELIST_NOSUCH_INDEX,	"The requested name list element does not exist.")
#define ERR_BSAFE_TOO_MANY_ALTNAMES				(PKG_BSAFE2+8)
	errortext (ERR_BSAFE_TOO_MANY_ALTNAMES,		"Too many alternate names in the name list.")
#define ERR_BSAFE_LANGTAG_EXISTS				(PKG_BSAFE2+9)
	errortext (ERR_BSAFE_LANGTAG_EXISTS,		"A name with the specified language already exits.")
#define ERR_BSAFE_LANGTAG_UNKNOWN				(PKG_BSAFE2+10)
	errortext (ERR_BSAFE_LANGTAG_UNKNOWN,		"The specified language is unknown")
#define ERR_BSAFE_NAME_MALFORMED				(PKG_BSAFE2+11)
	errortext (ERR_BSAFE_NAME_MALFORMED,		"An improperly formed name was encountered")
#define ERR_BSAFE_INV_CERT						(PKG_BSAFE2+12)
	errortext (ERR_BSAFE_INV_CERT,				"Invalid certificate contents or format")
#define ERR_ASN1_ILL_OID						(PKG_BSAFE2+13)
	errortext (ERR_ASN1_ILL_OID,				"Illegal ASN.1 Object ID field")
#define ERR_ASN1_ILL_DATATYPE					(PKG_BSAFE2+14)
	errortext (ERR_ASN1_ILL_DATATYPE,			"Illegal or unexpected ASN.1 data type")
#define ERR_ASN1_ILL_DATALENGTH					(PKG_BSAFE2+15)
	errortext (ERR_ASN1_ILL_DATALENGTH,			"Illegal or unsupported ASN.1 data length")

/* 		(PKG_BSAFE2:  Available, limited to 0-15 */
/* TIPEM errors */

#define ERR_BSAFE3_TE_UNKNOWN					(PKG_BSAFE3+0)
    errortext (ERR_BSAFE3_TE_UNKNOWN,			"Unknown S/MIME error")
#define ERR_BSAFE3_TE_ASN_SIGNATURE				(PKG_BSAFE3+1)
    errortext (ERR_BSAFE3_TE_ASN_SIGNATURE,		"Invalid signature on certificate or CRL")
#define ERR_BSAFE3_TE_ATTRIBUTES_OBJ			(PKG_BSAFE3+2)
    errortext (ERR_BSAFE3_TE_ATTRIBUTES_OBJ,	 "Invalid cryptographic attributes object")
#define ERR_BSAFE3_TE_EOS						(PKG_BSAFE3+3)
    errortext (ERR_BSAFE3_TE_EOS, 				"End of cryptographic data stream")

#define ERR_BSAFE4_TE_MEMORY_OBJ				(PKG_BSAFE3+4)
    errortext (ERR_BSAFE4_TE_MEMORY_OBJ,		"Invalid cryptographic memory object")
#define ERR_BSAFE4_TE_OVER_32K					(PKG_BSAFE3+5)
    errortext (ERR_BSAFE4_TE_OVER_32K,			"Cryptographic data block is too big to be processed")
#define ERR_BSAFE4_TE_PARAMETER					(PKG_BSAFE3+6)
    errortext (ERR_BSAFE4_TE_PARAMETER,			"Invalid parameter passed to cryptographic function")
#define ERR_BSAFE5_TE_VERSION					(PKG_BSAFE3+7)
    errortext (ERR_BSAFE5_TE_VERSION,			"S/MIME version not supported")

#define ERR_BSAFE5_ERROR						(PKG_BSAFE3+8)
    errortext (ERR_BSAFE5_ERROR,				"Error -- ")
#define ERR_BSAFE5_WARNING						(PKG_BSAFE3+9)
    errortext (ERR_BSAFE5_WARNING,				"Warning -- ")
#define ERR_BSAFE5_LOG							(PKG_BSAFE3+10)
	errortext(ERR_BSAFE5_LOG,					"%s %s")
#define ERR_BSAFE5_TE_UNTRUSTED_CERTS_CRLS		(PKG_BSAFE3+11)
	errortext (ERR_BSAFE5_TE_UNTRUSTED_CERTS_CRLS,	"Cannot establish trust in a certificate or CRL.")

#define ERR_NOCA_KEYMATCH						(PKG_BSAFE3+12)
	errortext (ERR_NOCA_KEYMATCH,				"The certifier key in the certificate does not match the key stored in the directory.")
#define ERR_ILL_RECERT_FCT						(PKG_BSAFE3+13)
	errortext (ERR_ILL_RECERT_FCT,				"The requested rename or recertify function is unknown or unsupported.")
#define ERR_NO_ANCESTOR_LANGTAG					(PKG_BSAFE3+14)
	errortext (ERR_NO_ANCESTOR_LANGTAG,			"The certifier has not yet been assigned a name associated with the proposed language.")
#define ERR_NO_INET_KEY							(PKG_BSAFE3+15)
	errortext (ERR_NO_INET_KEY,					"This entry has not been assigned a public key suitable for use on the internet.")

#define ERR_BSAFE_NAME_EXISTS               	(PKG_BSAFE3+16)
	errortext (ERR_BSAFE_NAME_EXISTS,      		"This name already exists.")

#define ERR_BSAFE_INVALID_BB                	(PKG_BSAFE3+17)
    errortext (ERR_BSAFE_INVALID_BB,       		"You are not authorized to recover this ID file.")

	
	
#define ERR_ASN1_INV_SYNTAX						(PKG_BSAFE3+18)
	errortext (ERR_ASN1_INV_SYNTAX,				"Invalid ASN.1 syntax")
#define ERR_BSAFE_INV_CRL						(PKG_BSAFE3+19)
	errortext (ERR_BSAFE_INV_CRL,				"Invalid CRL contents or format")
#define ERR_BSAFE_INV_EXTENSIONS_OBJ 			(PKG_BSAFE3+20)
	errortext (ERR_BSAFE_INV_EXTENSIONS_OBJ, 	"Invalid certificate extensions object")
#define ERR_BSAFE_INV_MSG_FORMAT				(PKG_BSAFE3+21)
	errortext (ERR_BSAFE_INV_MSG_FORMAT,		"Cryptographic error: invalid message format")
#define ERR_BSAFE_BAD_KEY_LENGTH				(PKG_BSAFE3+22)
	errortext (ERR_BSAFE_BAD_KEY_LENGTH,		"Invalid cryptographic key length")
#define ERR_BSAFE_BAD_SIGNATURE					(PKG_BSAFE3+23)
	errortext (ERR_BSAFE_BAD_SIGNATURE,			"Could not verify cryptographic signature")
#define ERR_BSAFE_BAD_RANDOM_STATE				(PKG_BSAFE3+24)
	errortext (ERR_BSAFE_BAD_RANDOM_STATE,		"Bad random number generator state")
#define ERR_BSAFE_CERTCRL_NOT_FOUND				(PKG_BSAFE3+25)
	errortext (ERR_BSAFE_CERTCRL_NOT_FOUND,		"Certificate, private key or CRL was not found")
#define ERR_BSAFE_MAKING_CERT_CHAIN				(PKG_BSAFE3+26)
	errortext (ERR_BSAFE_MAKING_CERT_CHAIN,		"A certificate chain could not be constructed")
#define ERR_BSAFE_CRYPTO_UPDATE_COUNT			(PKG_BSAFE3+27)
	errortext (ERR_BSAFE_CRYPTO_UPDATE_COUNT,	"Cryptographic error: update operation called an inappropriate number of times")
#define ERR_BSAFE_DATA_STREAM					(PKG_BSAFE3+28)
	errortext (ERR_BSAFE_DATA_STREAM,			"Data streaming error encountered during cryptographic operation")
#define ERR_BSAFE_CERT_EXT_EXISTS				(PKG_BSAFE3+29)
	errortext (ERR_BSAFE_CERT_EXT_EXISTS,		"Certificate extension already exists")
#define ERR_BSAFE_GENERIC_DATA					(PKG_BSAFE3+30)
	errortext (ERR_BSAFE_GENERIC_DATA,			"Unknown data error occurred during cryptographic processing")
#define ERR_BSAFE_HARDWARE		 				(PKG_BSAFE3+31)
	errortext (ERR_BSAFE_HARDWARE,		 		"Cryptographic hardware error")

/* 		(PKG_BSAFE3:  Limited to 0-31 */


#define ERR_BSAFE_UNSUPPORTED_CERTCRLSIG		(PKG_BSAFE4+0)
	errortext (ERR_BSAFE_UNSUPPORTED_CERTCRLSIG,"Unsupported certificate or CRL signature algorithm")
#define ERR_BSAFE_UNSUPPORTED_CRYPTO_OP			(PKG_BSAFE4+1)
	errortext (ERR_BSAFE_UNSUPPORTED_CRYPTO_OP,	"An unsupported cryptographic operation was requested")
#define ERR_BSAFE_WEAK_KEY						(PKG_BSAFE4+2)
	errortext (ERR_BSAFE_WEAK_KEY,				"The data supplied would generate a known weak cryptographic key")
#define STR_BSAFE_BACKUP_ON_REG_SBJ             (PKG_BSAFE4+3)
	errortext (STR_BSAFE_BACKUP_ON_REG_SBJ,     "Backup of newly registered ID file for %A")
#define STR_BSAFE_BACKUP_ON_ACCEPT_SBJ          (PKG_BSAFE4+4)
	errortext (STR_BSAFE_BACKUP_ON_ACCEPT_SBJ,  "Backup of newly changed recovery information for %A")
#define STR_BSAFE_BACKUP_ON_MODIFY_SBJ          (PKG_BSAFE4+5)
	errortext (STR_BSAFE_BACKUP_ON_MODIFY_SBJ,  "Backup of recent changes to ID file for %A")
#define STR_BSAFE_NEW_REC_INFO_SBJ              (PKG_BSAFE4+6)
	errortext (STR_BSAFE_NEW_REC_INFO_SBJ,      "New ID file recovery information is attached.  Please add it to your ID file by using the Actions menu %s option.")
#define STR_BSAFE_DUP_NAMES_IN_DIRECTORY		(PKG_BSAFE4+7)
	stringtext (STR_BSAFE_DUP_NAMES_IN_DIRECTORY, "%A and %A both already exist in the directory but in different entries")


/* 		PKG_BSAFE4:  Limited to 0-31 */


#define ERR_BSAFE_RECOVERY_INFO_TOO_OLD         (PKG_BSAFE5+0)
    errortext (ERR_BSAFE_RECOVERY_INFO_TOO_OLD, "The recovery information could not be accepted because it is older than your current recovery information")
#define ERR_BSAFE_NOT_LEAF_CERT                 (PKG_BSAFE5+1)
    errortext (ERR_BSAFE_NOT_LEAF_CERT,         "Only leaf certificates can be deleted from the ID file")
#define ERR_BSAFE_NO_REPOSITORY_NAME            (PKG_BSAFE5+2)
    errortext (ERR_BSAFE_NO_REPOSITORY_NAME,    "You must specify a name for the backup repository address")
#define ERR_BSAFE_PKCS12_IMPORT_ADD_KEY  	(PKG_BSAFE5+3)
	errortext(ERR_BSAFE_PKCS12_IMPORT_ADD_KEY, "Cannot add key from the import file.")
#define ERR_BSAFE_PKCS12_IMPORT_ADD_CERT  	(PKG_BSAFE5+4)
	errortext(ERR_BSAFE_PKCS12_IMPORT_ADD_CERT, "Cannot add certificate from the import file.")

/* 		PKG_BSAFE5:  Available, limited to 0-15 */

#define ERR_BSAFE_TE_UNTRUSTED_SIGNER			(PKG_BSAFE6+0)
	errortext (ERR_BSAFE_TE_UNTRUSTED_SIGNER, 	"The signer's certificate is not trusted.")
#define ERR_BSAFE_INCOMPLETE_CERT_CHAIN			(PKG_BSAFE6+1)
	errortext (ERR_BSAFE_INCOMPLETE_CERT_CHAIN,	"Cannot accept internet certificate because the certificate authority certificate is unavailable.")
#define ERR_BSAFE_MISSING_PRIVATE_KEY			(PKG_BSAFE6+2)
	errortext (ERR_BSAFE_MISSING_PRIVATE_KEY,	"Cannot accept internet certificate because the current ID file was not used to create the original request.")
#define ERR_BSAFE_CERT_ALREADY_IN_ID_FILE		(PKG_BSAFE6+3)
	errortext (ERR_BSAFE_CERT_ALREADY_IN_ID_FILE,	"Cannot accept internet certificate because the certificate is already in the ID file.")
		

/*	Note: Put here, because there was space, but these really belong
* 	elsewhere
*/

/* LATER:
*	In some cases, copies of ERR_DESK codes moved here because they can
*	be returned by the SDK. Corresponding ERR_DESK codes should be eliminated
*/

#define ERR_BSAFE_ILL_IDCHAR			(PKG_BSAFE6+4)
	errortext(ERR_BSAFE_ILL_IDCHAR,		"The only allowed characters for a person, server, or certifier name are letters, numbers, ampersand, apostrophe, hyphen, period, space, and underscore")
#define ERR_BSAFE_ILL_DOMAIN			(PKG_BSAFE6+5)
	errortext(ERR_BSAFE_ILL_DOMAIN,		"The only allowed characters for a domain name are letters, numbers, ampersand, apostrophe, hyphen, space, and underscore")
#define ERR_BSAFE_NA_ENTRY_NOT_FOUND	(PKG_BSAFE6+6)
	stringtext(ERR_BSAFE_NA_ENTRY_NOT_FOUND, "The ID was certified but there was no corresponding entry in the Address Book to be updated")
#define ERR_BSAFE_OLDNSF				(PKG_BSAFE6+7)
	errortext(ERR_BSAFE_OLDNSF,			"Unable to perform this operation; options were selected that cannot be used with this older format Notes database.")
#define ERR_BSAFE_INV_RECERT_FORM		(PKG_BSAFE6+8)
	errortext(ERR_BSAFE_INV_RECERT_FORM,"Cannot certify this entry because the form used to create it is not supported for this operation.")
#define ERR_BSAFE_NOT_IMPLEMENTED		(PKG_BSAFE6+9)
	errortext(ERR_BSAFE_NOT_IMPLEMENTED,"Operation is not yet implemented")
#define ERR_BSAFE_DUP_NAME				(PKG_BSAFE6+10)
	errortext(ERR_BSAFE_DUP_NAME,		"Duplicate name found")
#define ERR_BSAFE_ILL_CERTIFIER_NAME	(PKG_BSAFE6+11)
	errortext(ERR_BSAFE_ILL_CERTIFIER_NAME, "You specified an illegal certifier name")
#define ERR_BSAFE_NO_INET_CERTS			(PKG_BSAFE6+12)
	errortext(ERR_BSAFE_NO_INET_CERTS,	"Could not locate or process internet certificates for this ID.")
#define ERR_BSAFE_PKCS12_IMPORT_BAD_FILE_READ  	(PKG_BSAFE6+13)
	errortext(ERR_BSAFE_PKCS12_IMPORT_BAD_FILE_READ, "Import file could not be read.  Check file permissions.")
#define ERR_BSAFE_PKCS12_IMPORT_BAD_INFO  	(PKG_BSAFE6+14)
	errortext(ERR_BSAFE_PKCS12_IMPORT_BAD_INFO, "Unsupported PKCS12 version or content.  Check the import file.")
#define ERR_BSAFE_PKCS12_IMPORT_BAD_UNKNOWN  	(PKG_BSAFE6+15)
	errortext(ERR_BSAFE_PKCS12_IMPORT_BAD_UNKNOWN, "Cannot handle the import file.  Check file name and file password.")

/* 		PKG_BSAFE6:  Available, limited to 0-15 */



#define ERR_BSAFE3_TE_ALLOC						ERR_BSAFE_NOMEMORY
#define ERR_BSAFE3_TE_ATTRIBUTE_COUNT			ERR_ASN1_INV_SYNTAX
#define ERR_BSAFE3_TE_ATTRIBUTE_NOT_FOUND		ERR_ASN1_INV_SYNTAX
#define ERR_BSAFE3_TE_ATTRIBUTE_TAG				ERR_ASN1_INV_SYNTAX
#define ERR_BSAFE3_TE_ATTRIBUTE_TYPE			ERR_BSAFE2_ATTRIBUTE_UNKNOWN
#define ERR_BSAFE3_TE_ATTRIBUTE_VALUE			ERR_ASN1_ILL_DATATYPE
#define ERR_BSAFE3_TE_ATTRIBUTE_VALUE_LEN		ERR_ASN1_ILL_DATALENGTH

#define ERR_BSAFE3_TE_BEGIN_PEM					ERR_BSAFE_INV_MSG_FORMAT
#define ERR_BSAFE3_TE_BER_ENCODING				ERR_ASN1_INV_SYNTAX

#define ERR_BSAFE3_TE_CANCEL					ERR_BSAFE_CANCELED
#define ERR_BSAFE3_TE_CERT_ENCODING				ERR_BSAFE_INV_CERT
#define ERR_BSAFE3_TE_CERT_OBJ					ERR_BSAFE_INV_CERT

#define ERR_BSAFE3_TE_CO_SET					ERR_BSAFE_BADCTX

#define ERR_BSAFE3_TE_CRL_ENCODING				ERR_BSAFE_INV_CRL
#define ERR_BSAFE3_TE_CRL_OBJ					ERR_BSAFE_INV_CRL

#define ERR_BSAFE3_TE_DATA						ERR_BSAFE_GENERIC_DATA
#define ERR_BSAFE3_TE_DBASE						ERR_BSAFE_BADCTX
#define ERR_BSAFE3_TE_DEK_ALG_NOT_SUPPORTED		ERR_BSAFE_UNSUPPORTED_CRYPTO_OP
#define ERR_BSAFE3_TE_DEK_ALG_UNKNOWN			ERR_BSAFE_UNSUPPORTED_CRYPTO_OP
#define ERR_BSAFE3_TE_DIGEST_OBJ				ERR_BSAFE_BADCTX
#define ERR_BSAFE3_TE_ENHANCED_TEXT_STREAM		ERR_BSAFE_DATA_STREAM

#define ERR_BSAFE3_TE_EXPONENT_EVEN				ERR_BSAFE_KEY_INV_FORMAT
#define ERR_BSAFE3_TE_EXPONENT_LEN				ERR_BSAFE_KEY_INV_FORMAT
#define ERR_BSAFE3_TE_EXTENSIONS_OBJ			ERR_BSAFE_INV_EXTENSIONS_OBJ
#define ERR_BSAFE3_TE_EXTENSION_ALREADY_EXISTS	ERR_BSAFE_CERT_EXT_EXISTS
#define ERR_BSAFE3_TE_HARDWARE					ERR_BSAFE_HARDWARE
#define ERR_BSAFE3_TE_HEADER					ERR_BSAFE_INV_MSG_FORMAT
#define ERR_BSAFE3_TE_INDEX						ERR_BSAFE4_TE_PARAMETER

#define ERR_BSAFE4_TE_CERT_CHAIN				ERR_BSAFE_MAKING_CERT_CHAIN
#define ERR_BSAFE4_TE_INPUT_LEN					ERR_BSAFE_GENERIC_DATA
#define ERR_BSAFE4_TE_INPUT_STREAM				ERR_BSAFE_DATA_STREAM

#define ERR_BSAFE4_TE_IO						ERR_BSAFE_DATA_STREAM
#define ERR_BSAFE4_TE_LIST_OBJ					ERR_BSAFE_BADCTX
#define ERR_BSAFE4_TE_ME_SET					ERR_BSAFE_BADCTX
#define ERR_BSAFE4_TE_MESSAGE_SIGNATURE			ERR_BSAFE_BAD_SIGNATURE
#define ERR_BSAFE4_TE_MIC_ALG_NOT_SUPPORTED		ERR_BSAFE_UNSUPPORTED_CRYPTO_OP
#define ERR_BSAFE4_TE_MIC_ALG_UNKNOWN			ERR_BSAFE_UNSUPPORTED_CRYPTO_OP
#define ERR_BSAFE4_TE_MODULUS_LEN				ERR_BSAFE_BAD_KEY_LENGTH
#define ERR_BSAFE4_TE_NAME_OBJ					ERR_BSAFE_BADCTX
#define ERR_BSAFE4_TE_NEED_RANDOM				ERR_BSAFE_BAD_RANDOM_STATE
#define ERR_BSAFE4_TE_NOT_FOUND					ERR_BSAFE_CERTCRL_NOT_FOUND
#define ERR_BSAFE4_TE_NOT_ME					(PKG_NSF+101)			/* ERR_NOT_SEALED_FOR_YOU	nsferr.h */
#define ERR_BSAFE4_TE_NOT_SUPPORTED				ERR_BSAFE_UNSUPPORTED_CRYPTO_OP
#define ERR_BSAFE4_TE_OUTPUT_LEN				ERR_BSAFE_TOOSMALL
#define ERR_BSAFE4_TE_OUTPUT_STREAM				ERR_BSAFE_DATA_STREAM

#define ERR_BSAFE4_TE_PASSWORD					(PKG_SECURE+8)			/* ERR_SECURE_BADPASSWORD	secerr.h */
#define ERR_BSAFE4_TE_PBE_ALG_NOT_SUPPORTED		ERR_BSAFE_UNSUPPORTED_CRYPTO_OP
#define ERR_BSAFE4_TE_PBE_ALG_UNKNOWN			ERR_BSAFE_UNSUPPORTED_CRYPTO_OP
#define ERR_BSAFE4_TE_PKCS_INPUT_STREAM			ERR_BSAFE_DATA_STREAM
#define ERR_BSAFE4_TE_PKCS_OUTPUT_STREAM		ERR_BSAFE_DATA_STREAM
#define ERR_BSAFE4_TE_PKCS_STREAM				ERR_BSAFE_DATA_STREAM

#define ERR_BSAFE4_TE_PRIVATE_KEY				ERR_BSAFE_KEY_INV_FORMAT
#define ERR_BSAFE4_TE_PROCESS					ERR_BSAFE4_TE_PARAMETER
#define ERR_BSAFE4_TE_PROTECTED_DATA			ERR_BSAFE_BADDATA
#define ERR_BSAFE4_TE_PUBLIC_KEY				ERR_BSAFE_KEY_INV_FORMAT
#define ERR_BSAFE4_TE_RANDOM_OBJ				ERR_BSAFE_BAD_RANDOM_STATE
#define ERR_BSAFE4_TE_SIGNATURE_ALG_NOT_SUPPORTED	ERR_BSAFE_UNSUPPORTED_CERTCRLSIG
#define ERR_BSAFE5_TE_SIGNATURE_ALG_UNKNOWN			ERR_BSAFE_UNSUPPORTED_CERTCRLSIG

#define ERR_BSAFE5_TE_TEXT_ENCODING				ERR_BSAFE_INV_MSG_FORMAT
#define ERR_BSAFE5_TE_TEXT_STREAM				ERR_BSAFE_DATA_STREAM
#define ERR_BSAFE5_TE_TOKEN						ERR_BSAFE4_TE_PARAMETER
#define ERR_BSAFE5_TE_VALIDITY					(PKG_SECURE+28)			/* ERR_SECURE_EXPIRED_CERT	secerr.h */
#define ERR_BSAFE5_TE_YOU_SET					ERR_BSAFE_BADCTX

#define ERR_CERT_MALFORMED						ERR_BSAFE_INV_CERT


#endif
