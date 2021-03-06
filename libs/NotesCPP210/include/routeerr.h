
/* PUBLIC error messages returned by Router library routines,
	which may be returned to programs other than the Router itself. */

#ifndef ROUTER_ERR_DEFS
#define ROUTER_ERR_DEFS

#define	ERR_ROUTER_UNKNOWN			(PKG_ROUTER+1)
	errortext(ERR_ROUTER_UNKNOWN,	"*** UNKNOWN ROUTER ERROR ***")
#define ERR_ROUTER_MSGTRACK_REQUEST_UPDATE	(PKG_ROUTER+2)
	errortext(ERR_ROUTER_MSGTRACK_REQUEST_UPDATE, "Error updating message tracking request")
#define ERR_ROUTER_MSGTRACK_REQUEST_QUEUE	(PKG_ROUTER+3)
	errortext(ERR_ROUTER_MSGTRACK_REQUEST_QUEUE, "Error queuing message tracking request")
#define ERR_ROUTER_NOTUNIQUE		(PKG_ROUTER+4)
	errortext(ERR_ROUTER_NOTUNIQUE,	"Recipient user name %a not unique.  Several matches found in Name & Address Book.")
#define ERR_ROUTER_NOSUCHUSER		(PKG_ROUTER+5)
	errortext(ERR_ROUTER_NOSUCHUSER,"User %a not listed in public Name & Address Book")
#define ERR_ROUTER_NOMAILFILE		(PKG_ROUTER+6)
	errortext(ERR_ROUTER_NOMAILFILE, "Recipient's Name & Address Book entry does not specify a valid Notes mail file")
#define ERR_ROUTER_NEWMAIL			(PKG_ROUTER+7)
	errortext(ERR_ROUTER_NEWMAIL, "New mail has been delivered to you!")
#define ERR_ROUTER_NOROUTETOSERVERFROM (PKG_ROUTER+8)
	errortext(ERR_ROUTER_NOROUTETOSERVERFROM, "No route found to server %a from server %a.  Check Server and Connection documents in Name & Address Book.")
#define ERR_ROUTER_NOROUTETODOMAINFROM (PKG_ROUTER+9)
	errortext(ERR_ROUTER_NOROUTETODOMAINFROM, "No route found to domain %s from server %a.  Check Server, Connection and Domain documents in Name & Address Book.")
#define ERR_ROUTER_NOROUTETODOMAINVIA (PKG_ROUTER+10)
	errortext(ERR_ROUTER_NOROUTETODOMAINVIA, "No route found to domain %s from server %a via server %a.  Check Server, Connection and Domain documents in Name & Address Book.")
#define ERR_ROUTER_DELIVERY_FILE	(PKG_ROUTER+11)
	errortext(ERR_ROUTER_DELIVERY_FILE, "Error delivering to %a %p; %e")
#define ERR_ROUTER_TRANSFER_FILE	(PKG_ROUTER+12)
	errortext(ERR_ROUTER_TRANSFER_FILE, "Error transferring to %p; %e %s")
#define ERR_ROUTER_NOGROUP			(PKG_ROUTER+13)
	errortext(ERR_ROUTER_NOGROUP, 	"Unsupported use of group name; Cannot send to a Group @ Domain nor auto-forward to a Group")
#define ERR_ROUTER_ROUTING_LOOP		(PKG_ROUTER+14)
	errortext(ERR_ROUTER_ROUTING_LOOP, 	"Maximum hop count exceeded.  Message probably in a routing loop.")
#define ERR_ROUTER_ACCESS_DENIED 	(PKG_ROUTER+15)
	errortext(ERR_ROUTER_ACCESS_DENIED, "Your Domain does not have access to route messages to the specified domain.")
#define ERR_ROUTER_MESSAGE_QUEUE 	(PKG_ROUTER+16)
	errortext(ERR_ROUTER_MESSAGE_QUEUE, "Unable to allocate mail message queue entry.")
#define ERR_ROUTER_MSGQ_POOLFULL 	(PKG_ROUTER+17)
	errortext(ERR_ROUTER_MSGQ_POOLFULL, "Insufficient memory - Router message queue is full.")
#define ERR_ROUTER_TRANSFER_Q_POOLFULL 	(PKG_ROUTER+18)
	errortext(ERR_ROUTER_TRANSFER_Q_POOLFULL, "Insufficient memory - Router transfer queue is full.")
#define ERR_ROUTER_TOO_MANY_RECIPS 	(PKG_ROUTER+19)
	errortext(ERR_ROUTER_TOO_MANY_RECIPS, "Message contains too many recipients (over 4 megabytes).")
#define ERR_ROUTER_LIST_LOOP		(PKG_ROUTER+20)
	errortext(ERR_ROUTER_LIST_LOOP,	"Groups cannot be nested more than 20 levels deep.")
#define ERR_ROUTER_BILLING_NOMEM	(PKG_ROUTER+21)
	errortext(ERR_ROUTER_BILLING_NOMEM, "Billing record not written. Insufficient memory.")  
#define STR_ROUTER_MSGSIZE_FORMULA 		(PKG_ROUTER+22)
	stringtext(STR_ROUTER_MSGSIZE_FORMULA,	"default MAIL_MSGSIZE:=@doclength;@all")
#define ERR_ROUTER_DELIVER_LOOP		(PKG_ROUTER+23)
	errortext(ERR_ROUTER_DELIVER_LOOP, 	"Maximum forwarding loop count exceeded.  Message probably in a forwarding loop. Examine Forwarding Address of intended recipient in Address Book.")
#define ERR_ROUTER_NOROUTETODOMAIN		(PKG_ROUTER+24)
	errortext(ERR_ROUTER_NOROUTETODOMAIN,"No route found to domain %s.  Check Server, Connection and Domain documents in Name & Address Book.")
#define ERR_ROUTER_NOROUTETOSERVER		(PKG_ROUTER+25)
	errortext(ERR_ROUTER_NOROUTETOSERVER,"No route found to server %a.  Check Server and Connection documents in Name & Address Book.")
#define ERR_ROUTER_NOLOCALSERVER		(PKG_ROUTER+26)
	errortext(ERR_ROUTER_NOLOCALSERVER,	"No Server entry in Address Book for local server.")

/* (PKG_ROUTER+27 available) */

#define ERR_ROUTER_UPGRADE_FAILED	 	(PKG_ROUTER+28)
	errortext(ERR_ROUTER_UPGRADE_FAILED, "Upgrade of mailbox file %p failed; %e")
#define ERR_ROUTER_TOOMANYCONN			(PKG_ROUTER+29)
	errortext(ERR_ROUTER_TOOMANYCONN,	"Too many Connections")
#define ERR_ROUTER_TOOMANYSERVERS		(PKG_ROUTER+30)
	errortext(ERR_ROUTER_TOOMANYSERVERS,"Too many Servers")
#define ERR_ROUTER_TOOMANYDOMAINS		(PKG_ROUTER+31)
	errortext(ERR_ROUTER_TOOMANYDOMAINS,"Too many Domains")
#define ERR_ROUTER_SYMBOL_TASKS_FULL	(PKG_ROUTER+32)
	errortext(ERR_ROUTER_SYMBOL_TASKS_FULL,"Insufficient memory - Router unable to allocate a new symbol for mailbox task.")
#define ERR_ROUTER_TABLE_MEM_ERROR	 	(PKG_ROUTER+33)
	errortext(ERR_ROUTER_TABLE_MEM_ERROR, "Insufficient memory - Router unable to allocate routing tables.")
#define ERR_ROUTER_DOMAIN_NAMESPACE	 	(PKG_ROUTER+34)
	errortext(ERR_ROUTER_DOMAIN_NAMESPACE, "Unable to add namespace $Domains to Indexer's queue.")
#define ERR_ROUTER_CONNECTION_NAMESPACE	 	(PKG_ROUTER+35)
	errortext(ERR_ROUTER_CONNECTION_NAMESPACE, "Unable to add namespace $Connections to Indexer's queue.")
#define ERR_ROUTER_SERVER_NAMESPACE	 	(PKG_ROUTER+36)
	errortext(ERR_ROUTER_SERVER_NAMESPACE, "Unable to add namespace $Servers to Indexer's queue.")
#define ERR_ROUTER_TOOMANYADJDOMAINS		(PKG_ROUTER+37)
	errortext(ERR_ROUTER_TOOMANYADJDOMAINS,	"Router: Too many Adjacent Domains")
#define ERR_ROUTER_FIND_VIEW_ERR			(PKG_ROUTER+38)
	errortext(ERR_ROUTER_FIND_VIEW_ERR,	"Router: Unable to find view in Address Book")
#define ERR_ROUTER_OPEN_VIEW_ERR			(PKG_ROUTER+39)
	errortext(ERR_ROUTER_OPEN_VIEW_ERR,	"Router: Unable to open view in Address Book")

#define ERR_ROUTER_MBOX_UPGRADE				(PKG_ROUTER+40)
	errortext(ERR_ROUTER_MBOX_UPGRADE, 		"Upgrading mailbox file %p")

#define ERR_ROUTER_DOMAIN_BUFFER_EXCEEDED	(PKG_ROUTER+41)
	errortext(ERR_ROUTER_DOMAIN_BUFFER_EXCEEDED, "Insufficient memory - Forwarding address + domain name exceeds buffer size for recipient %s.")

#define ERR_ROUTER_SYMBOL_TABLE						(PKG_ROUTER+42)
	errortext(ERR_ROUTER_SYMBOL_TABLE,				"Unable to add name to routing symbol table")
#define ERR_ROUTER_SERVERNOTLOCALDOMAIN				(PKG_ROUTER+43)
	errortext(ERR_ROUTER_SERVERNOTLOCALDOMAIN,		"Router: Server %a not in local domain; Server ignored.")
#define ERR_ROUTER_DUPSERVER						(PKG_ROUTER+44)
	errortext(ERR_ROUTER_DUPSERVER,					"Router: Duplicate server entry in address book for %a")
#define ERR_ROUTER_NOSERVERENTRY					(PKG_ROUTER+45)
	errortext(ERR_ROUTER_NOSERVERENTRY,				"Router: Connection from server %a not used; Server not found in Address Book.")
#define ERR_ROUTER_CONNNOTLOCALDOMAIN				(PKG_ROUTER+46)
	errortext(ERR_ROUTER_CONNNOTLOCALDOMAIN,		"Router: Connection from server %a not used; Server not in local domain.")
#define ERR_ROUTER_ROUTE_TO_SELF					(PKG_ROUTER+47)
	errortext(ERR_ROUTER_ROUTE_TO_SELF, 	"Attempt made to transfer message to self via SMTP. Possible DNS configuration error.")
#define ERR_ROUTER_DNS_UNAVAILABLE					(PKG_ROUTER+48)
	errortext(ERR_ROUTER_DNS_UNAVAILABLE,			"DNS is unavailable, message will be requeued.")
#define ERR_ROUTER_TOO_BIG							(PKG_ROUTER+49)
	errortext(ERR_ROUTER_TOO_BIG,					"The size of this message exceeds the administrator specified maximum message size for this server")
#define ERR_ROUTER_DUPPULLCONN						(PKG_ROUTER+50)
	errortext(ERR_ROUTER_DUPPULLCONN,				"Router: Duplicate Pull Routing connection entry in address book for %a")

#define ERR_ROUTER_DELIVERY_USER	(PKG_ROUTER+51)
	errortext(ERR_ROUTER_DELIVERY_USER, "Error delivering to %a; %e")

#define ERR_ROUTER_MSGTRACK_UNDERQUALIFIED			(PKG_ROUTER+52)
	errortext(ERR_ROUTER_MSGTRACK_UNDERQUALIFIED,	"Message tracking query returned more than one result")
#define ERR_ROUTER_MSGTRACK_INPROGRESS				(PKG_ROUTER+53)
	errortext(ERR_ROUTER_MSGTRACK_INPROGRESS,		"Tracking operation is in progress.") 
#define ERR_ROUTER_MSGTRACK_NOTFOUND				(PKG_ROUTER+54)
	errortext(ERR_ROUTER_MSGTRACK_NOTFOUND,			"Message tracking query returned no results")
#define ERR_ROUTER_MSGTRACK_DUPLICATE				(PKG_ROUTER+55)
	errortext(ERR_ROUTER_MSGTRACK_DUPLICATE,		"Found an unexpected duplicate message")
#define ERR_ROUTER_MBOX_TITLE	 					(PKG_ROUTER+56)
	errortext(ERR_ROUTER_MBOX_TITLE,				"%.*s Mailbox")
#define ERR_ROUTER_PROFILE_OPEN_ERROR				(PKG_ROUTER+57)
	errortext(ERR_ROUTER_PROFILE_OPEN_ERROR,		"Router: Unable to retrieve mail filters from database %s; %e")
#define ERR_ROUTER_MSGTRACK_AUTHENTICATION			(PKG_ROUTER+58)
	errortext(ERR_ROUTER_MSGTRACK_AUTHENTICATION,	"You are not authorized to do message tracking")
#define ERR_ROUTER_MSGTRACK_SUBJECT					(PKG_ROUTER+59)
	errortext(ERR_ROUTER_MSGTRACK_SUBJECT,			"You are not authorized to track message subjects.")
#define ERR_ROUTER_FILE_IN_USE						(PKG_ROUTER+60)
	errortext(ERR_ROUTER_FILE_IN_USE,				"Delivery to mail file in progress by another thread, try again later")
#define ERR_ROUTER_MBOX_CREATE						(PKG_ROUTER+61)
	errortext(ERR_ROUTER_MBOX_CREATE,				"Creating new mailbox file %p")
#define ERR_ROUTER_MBOX_OPEN						(PKG_ROUTER+62)
	errortext(ERR_ROUTER_MBOX_OPEN, 				"Unable to open mailbox file %p")

/* NOTE:	PKG_ROUTER+63 is the LAST code available for this file.  See */
/* globerr.h for dependency which restricts this string ID space. */

#endif


