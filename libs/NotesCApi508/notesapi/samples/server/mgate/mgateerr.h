
#ifndef MGATE_ERR_DEFS
#define MGATE_ERR_DEFS

#define	PKG_MGATE 0x3300 /* must be the same as PKG_ADDIN in GLOBERR.H */

/*	String #0 must always be the add-in application's task name. 
	String #1 must be the version.

	Both of these strings are defined in separate (one per .exe) 
	.h files. 
*/

#define MSG_MGATE_ADDIN_NAME			(PKG_MGATE+0)
	errortext(MSG_MGATE_ADDIN_NAME,		"MGATE")
#define	MSG_MGATE_ADDIN_VERSION		(PKG_MGATE+1)
	errortext(MSG_MGATE_ADDIN_VERSION,	"Version 1.0")


/*  Mail Gateway logging message definitions */

#define ERR_MGATE_STARTED			(PKG_MGATE+2)
	errortext(ERR_MGATE_STARTED, "MGATE Mail gateway started")
#define ERR_MGATE_SHUTDOWN			(PKG_MGATE+3)
	errortext(ERR_MGATE_SHUTDOWN, "MGATE Mail gateway shutdown")

#define ERR_MGATE_NONDELIVERYSUBJ	(PKG_MGATE+4)
	errortext(ERR_MGATE_NONDELIVERYSUBJ, "NON-DELIVERY of: ")
#define ERR_MGATE_MSGLIST			(PKG_MGATE+5)
	errortext(ERR_MGATE_MSGLIST, "MGATE: Unable to create message list")
#define ERR_MGATE_NOUNIQUE			(PKG_MGATE+6)
	errortext(ERR_MGATE_NOUNIQUE, "MGATE: Unable to create a unique file name")
#define ERR_MGATE_RECIPCREATE		(PKG_MGATE+7)
	errortext(ERR_MGATE_RECIPCREATE, "MGATE: Unable to create a recipient message file %s")
#define ERR_MGATE_BODYFILE			(PKG_MGATE+8)
	errortext(ERR_MGATE_BODYFILE, "MGATE: Unable to create a body text file %s")
#define ERR_MGATE_MSGOPEN			(PKG_MGATE+9)
	errortext(ERR_MGATE_MSGOPEN, "MGATE: Unable to open foreign message file %s")
#define ERR_MGATE_SENDSUCCESS		(PKG_MGATE+10)
	errortext(ERR_MGATE_SENDSUCCESS, "MGATE: Mail successfully sent to user %s")
#define ERR_MGATE_SENDERROR			(PKG_MGATE+11)
	errortext(ERR_MGATE_SENDERROR, 	"MGATE: Unable to send to user %s")
#define ERR_MGATE_UNKNOWNITEM		(PKG_MGATE+12)
	errortext(ERR_MGATE_UNKNOWNITEM, "MGATE: Unkown foreign message item: %s")
#define ERR_MGATE_TRANSFERSUCCESS	(PKG_MGATE+13)
	errortext(ERR_MGATE_TRANSFERSUCCESS, "MGATE: Mail successfully received")
#define ERR_MGATE_TRANSFERERROR		(PKG_MGATE+14)
	errortext(ERR_MGATE_TRANSFERERROR, "MGATE: Mail unsuccessfully transferred")
#define ERR_MGATE_MSGFILE_OPEN		(PKG_MGATE+17)
	errortext(ERR_MGATE_MSGFILE_OPEN, "MGATE: Error opening message file %s")
#define ERR_MGATE_TEXT_OPEN		(PKG_MGATE+18)
	errortext(ERR_MGATE_TEXT_OPEN, "MGATE: Error creating/opening body text file %s")
#define ERR_MGATE_MSGFILE_CREATE	(PKG_MGATE+19)
	errortext(ERR_MGATE_MSGFILE_CREATE, "MGATE: Creating new message file %s")
#define ERR_MGATE_ATT_CREATE		(PKG_MGATE+20)
	errortext(ERR_MGATE_ATT_CREATE, "MGATE: Creating temporary attachment file %s")
#define ERR_MGATE_ATT_WRITE			(PKG_MGATE+21)
	errortext(ERR_MGATE_ATT_WRITE, "MGATE: Writing temporary attachment file")
#define ERR_MGATE_ATT_ADD			(PKG_MGATE+22)
	errortext(ERR_MGATE_ATT_ADD, "MGATE: Appending attachment file %s to message")
#define ERR_MGATE_NODOMAIN			(PKG_MGATE+32)
	errortext(ERR_MGATE_NODOMAIN, "MGATE: No MGATEDOMAIN set; use SET CONFIG MGATEDOMAIN=domain to set it")
#define ERR_MGATE_NODRIVE			(PKG_MGATE+33)
	errortext(ERR_MGATE_NODRIVE, "MGATE: No MGATEDRIVE set; use SET CONFIG MGATEDRIVE=driveletter to set it")

/*  Gateway status definitions (for server console display) */

#define ERR_MGATE_INITIALIZING			PKG_MGATE+100
	errortext(ERR_MGATE_INITIALIZING,	"Initializing")
#define ERR_MGATE_IDLE					PKG_MGATE+101
	errortext(ERR_MGATE_IDLE,			"Idle")
#define ERR_MGATE_RECEIVING		  		PKG_MGATE+102
	errortext(ERR_MGATE_RECEIVING,		"Receiving inbound mail from %s")
#define ERR_MGATE_TRANSFERING			PKG_MGATE+104
	errortext(ERR_MGATE_TRANSFERING,	"Searching for outbound mail to transfer")
#define ERR_MGATE_TRANSFERING_TO		PKG_MGATE+105
	errortext(ERR_MGATE_TRANSFERING_TO,	"Transferring mail to %s")

#endif
