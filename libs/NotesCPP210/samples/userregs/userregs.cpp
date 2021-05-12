//===========================================================================
//
//      Module: USERREGS.CPP
//
//      Description:
//              This program illustrates user registration capabilities
//              via the use of the C++ API LNCertifier class.
//
//      Syntax: USERREGS <server's distinguished name>
//
//        First, a new organization certifier, ABCorp, is created.  Then 
//        a new organization unit certifier, Sales, is created.  This 
//        certifier is a descendant of the organization certifier.  Then 
//        a new server, OTTO, is registered and certified with the 
//        organization certifier.  Last, a new user, Jayne Doe, is registered 
//        and certified with the organization unit certifier. 
//
//        Each of these steps creates an ID file. If this program is run under
//        NT or OS/2, the ID files are written to disk A:.  If this program 
//        is run under Unix, the files are written to /tmp.
//
//        Each of these steps creates an entry in the Public Address book.
//        Therefore, you must have proper access to the Public Address
//        book on the server specified on the command line in order for
//        this program to succeed.
//
//        The entries for the organization certifier, organization unit 
//        certifier, new server, and new user can be found in the 
//        Public Address book, along with their Notes IDs.
//
//===========================================================================

#include <iostream.h>
#include <lncppapi.h>

#ifndef LNREG_HPP
#define LNREG_HPP
#include "lnreg.hpp"
#endif

//Symbolic constants.
#define ORG_CERTNAME            "ABCorp"
#define ORGUNIT_CERTNAME        "Sales"
#define NEW_SERVNAME            "OTTO"
#define NEW_USERNAME            "Jayne Doe"

//Symbolic constants that depend on the enviroment.
#if defined(DOS) || defined(OS2) || defined(NT)  //FAT names on A: disk 
    #define ORG_CERT_ID         "A:\\ABCORP.ID"
    #define ORGUNIT_CERT_ID "A:\\ABSALES.ID"
    #define SERVER_ID           "A:\\OTTO.ID"
    #define USER_ID             "A:\\JDOE.ID"
    #define MAILFILENAME        "mail\\jdoe.nsf"
#elif defined(UNIX)                                     //UNIX names in /tmp dir. 
    #define ORG_CERT_ID         "/tmp/abcorp.id"
    #define ORGUNIT_CERT_ID "/tmp/absales.id"
    #define SERVER_ID           "/tmp/otto.id"
    #define USER_ID             "/tmp/jdoe.id"
    #define MAILFILENAME        "mail/jdoe.nsf"
#endif

#define DOMAIN_NAME "ABC"
#define MIN_PASS_LEN 3

#define NA_NAME                         "names.nsf"

#define ERR_BUF_SIZE 512

static void SetCreateCertifierOptions ( LNRegistrationOptions *CreateCertOptions,
			char * SrvrName);
static void SetRegCertifierOptions ( LNRegistrationOptions *RegCertOptions,
			char * SrvrName);
static void SetRegServerOptions ( LNRegistrationOptions *RegServerOptions,
			char * SrvrName);
static void SetRegUserOptions ( LNRegistrationOptions *RegUserOptions,
			char * SrvrName);

int main(int argc, char *argv[])
{
	//Server name entered on the command line.
	char *          ServerName = NULL;

	LNNotesSession  Session;
	LNSTATUS                lnstat = LNNOERROR;

	// Check the command line.
	if (argc < 2 || argc > 3) 
	{
		cout << "\nUsage:\n\t" << argv[0]
			<< " <server name> \n"
			<< endl;
		return(1); 
	}

	// Get info from command line.
	ServerName = argv[1];
	

	LNSetThrowAllErrors(TRUE);

	// Initialize the C++ API.
	lnstat = Session.Init(argc, argv);
	if (lnstat)
	{
		cout << "\nUnable to initialize the API" << endl;
		return(1);
	}

	// Begin TRY block. 
	// Throw all errors encountered during command execution.
	try
	{                       
	LNCertifier     certifier;
	LNString                logfile;

		LNRegistrationOptions   createcertopt;
		SetCreateCertifierOptions( &createcertopt, ServerName );

		//Set the date components of the date/time. 
		//Uses the current time zone.
		LNDatetime  expiration;
		expiration.SetDate(7,15,1997);

		//Set the expiration date to two years from today (Notes default).
		expiration.AdjustDate(0,0,2);

		//Create and register new organizational certifier, ABCorp.
		//Creates an organizational certifier (certification context).

		cout << "Calling LNNotesSession::CreateCertifier " << endl;
		lnstat = Session.CreateCertifier(ORG_CERT_ID, createcertopt, 
			ORG_CERTNAME, expiration, &certifier, logfile);
		if (lnstat)
			throw lnstat;
	
		//Prepare to call RegisterCertifier to create and register a new 
		//organizational unit certifier, Sales org unit of ABCorp. 
		//Use the above organization certifier context for ABCorp
		//to RegisterCertifier.

		LNRegistrationOptions   regcertoptions;
		SetRegCertifierOptions( &regcertoptions, ServerName );

		cout << "Calling LNCertifier::RegisterCertifier " << endl;
		lnstat = certifier.RegisterCertifier(ORGUNIT_CERT_ID,
			regcertoptions, ORGUNIT_CERTNAME);
		if (lnstat)
			throw lnstat;

		//Prepare to call RegisterServer to create and register a new 
		//server.  Certify server with the organization certifier created 
		//earlier (use the above organization certifier context).

		LNRegistrationOptions   regsrvroptions;
		SetRegServerOptions( &regsrvroptions, ServerName );

		cout << "Calling LNCertifier::RegisterServer " << endl;
		lnstat = certifier.RegisterServer(SERVER_ID,
			regsrvroptions, NEW_SERVNAME, DOMAIN_NAME);
		if (lnstat)
			throw lnstat;              

		//Prepare to call RegisterUser to create and register a new user.
		//First get the organization unit certifier context for ABCorp, 
		//Sales Unit. Then, use this certifier context to RegisterUser. 
		//It will certify the new user with this certifier. 

		LNRegistrationOptions   reguseroptions;
		SetRegUserOptions( &reguseroptions, ServerName );

		LNCertifier     orgunitcertifier;

		cout << "Calling LNNotesSession::GetCertifier " << endl;
		lnstat = Session.GetCertifier(ORGUNIT_CERT_ID, expiration, &orgunitcertifier);
		if (lnstat)
			throw lnstat;

		cout << "Calling LNCertifier::RegisterUser " << endl;
		lnstat = orgunitcertifier.RegisterUser(USER_ID, reguseroptions, "Doe", 
				"Jayne", "");
		if (lnstat)
			throw lnstat;

	}

	//Error handler.  If an error occurred, get the text of the error
	//message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		ErrorBuf[0] = '\0';
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}
	  
	//Terminate the API.
	Session.Term();

	char    CommandBuf[10];

	cout << endl;   
	cout << "All Done. Hit return to exit: ";
	cin.getline(CommandBuf, 10);

	//All done.
	return(0);
}

//---------------------------------------------------------------------------
//
// Name:
//              SetCreateCertifierOptions
//
// Description:
//              Sets up the CreateCertifier options.
//---------------------------------------------------------------------------
static void SetCreateCertifierOptions ( LNRegistrationOptions *CreateCertOptions,
		char * SrvrName )
{
		CreateCertOptions->SetRegistrationServer(SrvrName); //Required
		CreateCertOptions->SetCountry("US");                            //Optional
		CreateCertOptions->SetPassword("password");             //Required
		CreateCertOptions->SetLocation("");                             //Optional
		CreateCertOptions->SetComment("");                                      //Optional
		CreateCertOptions->SetMailServer("");                           //Optional
		CreateCertOptions->SetMailFilepath("");                         //Optional
		CreateCertOptions->SetForwardingAddress("");            //Optional
		CreateCertOptions->SetMinPasswordLength(3);                     //Required
		CreateCertOptions->SetOrganizationUnit("");             //Optional

		//Set the flags so that we only create ID file in the address book.
		CreateCertOptions->SetCreateIDFile(TRUE);                 
		CreateCertOptions->SetCreateNorthAmericanID(TRUE);
		CreateCertOptions->SetCreateAddressBookEntry(TRUE);
		CreateCertOptions->SetSaveIDInAddressBook(TRUE);
	
} // END SetCreateCertifierOptions()


//---------------------------------------------------------------------------
//
// Name:
//              SetRegCertifierOptions
//
// Description:
//              Sets up the RegisterCertifier options.
//---------------------------------------------------------------------------
static void SetRegCertifierOptions ( LNRegistrationOptions *RegCertOptions,
		char * SrvrName )
{
		RegCertOptions->SetRegistrationServer(SrvrName);        //Required
		RegCertOptions->SetCountry("US");                                       //Optional
		RegCertOptions->SetPassword("password");                        //Required
		RegCertOptions->SetLocation("");                                        //Optional
		RegCertOptions->SetComment("");                                         //Optional
		RegCertOptions->SetMailServer("");                                      //Optional
		RegCertOptions->SetMailFilepath("");                            //Optional
		RegCertOptions->SetForwardingAddress("");                       //Optional
		RegCertOptions->SetMinPasswordLength(3);                        //Required
		RegCertOptions->SetOrganizationUnit("");                        //Optional

		//Set the flags so that we only create ID file in the address book.
		RegCertOptions->SetCreateIDFile(TRUE);
		RegCertOptions->SetCreateNorthAmericanID(TRUE);
		RegCertOptions->SetCreateAddressBookEntry(TRUE);
		RegCertOptions->SetSaveIDInAddressBook(TRUE);
	
} // END SetRegCertifierOptions()


//---------------------------------------------------------------------------
//
// Name:
//              SetRegServerOptions
//
// Description:
//              Sets up the RegisterServer options.
//---------------------------------------------------------------------------
static void SetRegServerOptions ( LNRegistrationOptions *RegServerOptions,
		char * SrvrName )
{
		RegServerOptions->SetRegistrationServer(SrvrName);      //Required
		RegServerOptions->SetCountry("US");                             //Optional
		RegServerOptions->SetPassword("password");                      //Required
		RegServerOptions->SetLocation("");                              //Optional
		RegServerOptions->SetComment("");                                       //Optional
		RegServerOptions->SetMailServer("");                            //Optional
		RegServerOptions->SetMailFilepath("");                          //Optional
		RegServerOptions->SetForwardingAddress("");             //Optional
		RegServerOptions->SetMinPasswordLength(3);                      //Required
		RegServerOptions->SetOrganizationUnit("");                      //Optional
		RegServerOptions->SetTitle("Corporate Server");         //Optional
		RegServerOptions->SetAdministrator(NEW_USERNAME);       //Optional

		//Set the flags so that we only create ID file in the address book.
		RegServerOptions->SetCreateIDFile(TRUE);
		RegServerOptions->SetCreateNorthAmericanID(TRUE);
		RegServerOptions->SetCreateAddressBookEntry(TRUE);
		RegServerOptions->SetSaveIDInAddressBook(TRUE);

} // END SetRegServerOptions()


//---------------------------------------------------------------------------
//
// Name:
//              SetRegUserOptions
//
// Description:
//              Sets up the RegisterUser options.
//---------------------------------------------------------------------------
static void SetRegUserOptions ( LNRegistrationOptions *RegUserOptions,
		char * SrvrName )
{
		RegUserOptions->SetRegistrationServer(SrvrName);         //Required
		RegUserOptions->SetCountry("US");                                        //Optional
		RegUserOptions->SetPassword("password");                         //Required
		RegUserOptions->SetLocation("");                                         //Optional
		RegUserOptions->SetComment("");                                          //Optional
		RegUserOptions->SetMailServer(SrvrName);                         //Required
		RegUserOptions->SetMailProgram(LNMAILPROGRAM_NOTES); //Required
		RegUserOptions->SetMailFilepath(MAILFILENAME);           //Required
		RegUserOptions->SetForwardingAddress("");                        //Optional
		RegUserOptions->SetMinPasswordLength(3);                         //Required
		RegUserOptions->SetOrganizationUnit("Inside Sales"); //Optional
								  
		//Set the flags so that we only create ID file in the address book.
		RegUserOptions->SetCreateIDFile(TRUE);
		RegUserOptions->SetCreateNorthAmericanID(TRUE);
		RegUserOptions->SetCreateAddressBookEntry(TRUE);
		RegUserOptions->SetCreateMailDatabase(TRUE);
		RegUserOptions->SetSaveIDInAddressBook(TRUE);


} // END SetRegUserOptions()

