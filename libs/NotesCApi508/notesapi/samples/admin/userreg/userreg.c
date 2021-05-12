/****************************************************************************

    PROGRAM:    userreg

    FILE:       userreg.c

    SYNTAX:     userreg  <server's distinguished name>

    PURPOSE:    demonstrates the User Registration capabilities

    DESCRIPTION:
        This program demonstrates the User Registration capabilities of
        the Lotus C API for Domino and Notes.  

        First, a new Organization certifier, ABCorp, is created.  Then, 
        a new Organization Unit certifier, Sales, is created.  This 
        certifier is a descendent of the Organization certifier.  Then, 
        a new server, OTTO, is registered and certified with the 
        Organization certifier.  Last, a new user, Jayne Doe is registered 
        and certified with the Organization Unit certifier. 

        Each of these steps create ID files. If this program is run under
        OS/2, these ID files are written to disk A:.  If this program is 
        run under Unix, these files are written to /tmp.

        Each of these steps create entries in the Name & Address book.
        Therefore, you must have proper access to the Name & Address
        book on the server specified on the command line in order for
        this program to succeed.

        The entries for the Organization certifier, Organization Unit 
        certifier, new server, and new user are then looked up in the 
        Name and Address book and their Note IDs are printed out.

****************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <global.h>
#include <names.h>
#include <nsfdb.h>
#include <reg.h>
#include <osmisc.h>
#include <misc.h>
#include <ostime.h>

#if defined(OS400)
#include "lapiplat.h"
#endif

/* symbolic constants */
#define ORG_CERTNAME "ABCorp"
#define ORGUNIT_CERTNAME "Sales"
#define NEW_SERVNAME "OTTO"
#define NEW_USERNAME "Jayne Doe"

/* symbolic constants that depend on the enviroment */
#if defined(DOS) || defined(OS2) || defined(NT) /* FAT names on A: disk */
    #define ORG_CERT_ID "A:\\ABCORP.ID"
    #define ORGUNIT_CERT_ID "A:\\ABSALES.ID"
    #define SERVER_ID "A:\\OTTO.ID"
    #define USER_ID "A:\\JDOE.ID"
    #define MAILFILENAME  "MAIL\\JDOE.NSF"
#elif defined(UNIX) && !defined(OS400)        /* UNIX names in /tmp dir */
    #define ORG_CERT_ID "/tmp/abcorp.id"
    #define ORGUNIT_CERT_ID "/tmp/absales.id"
    #define SERVER_ID "/tmp/otto.id"
    #define USER_ID "/tmp/jdoe.id"
    #define MAILFILENAME  "mail/jdoe.nsf"
#elif defined (OS400)                        /* OS/400 names in default data dir */
    #define ORG_CERT_ID "abcorp.id"
    #define ORGUNIT_CERT_ID "absales.id"
    #define SERVER_ID "otto.id"
    #define USER_ID "jdoe.id"
    #define MAILFILENAME  "jdoe.nsf"
#endif

#define DOMAIN_NAME "ABC"
#define MIN_PASS_LEN 3

#define DNAME_ORG_CERT "O=ABCorp/C=US"
#define DNAME_ORGUNIT_CERT "OU=Sales/O=ABCorp/C=US"
#define DNAME_OTTO "CN=OTTO/O=ABCorp/C=US"
#define DNAME_JAYNE \
"CN=Jayne Doe/OU=Inside Sales/OU=Sales/O=ABCorp/C=US"

#define NA_NAME "names.nsf"

/* local function prototypes */
void LNCALLBACK REGCallback (char far *);
STATUS GetCertCtx (char far *, HCERTIFIER *, char far *);

TIMEDATE ExpireDate;
BOOL LocalServer;

/************************************************************************

    FUNCTION:   NotesMain

    PURPOSE:    Lotus C API for Domino and Note subroutine

*************************************************************************/

STATUS LNPUBLIC NotesMain(int argc, char *argv[])
{
   STATUS   error;              /* return code from API calls */
   char     *ServName;          /* server name entered on the command line */
   char     MailServName[MAXUSERNAME + 1]; /* mail server name */
   char     FullDBPath[MAXPATH];  /* complete pathname for Name and Address
                                     Book */
	char		ServLocation[MAXLOCATIONNAME] = "Sales LAB";
	char		WorkLocation[MAXLOCATIONNAME] = "323 West";

   HCERTIFIER hCertCtx;
   DBHANDLE hNABook;              /* handle to name and address book */
   NOTEID NoteID;
   char szErr[MAXSPRINTF];

   /* if no server name on the command line, assume local machine */
   if (argc == 1) 
   {
      ServName = '\0';
      LocalServer = TRUE;
   }
   else if (argc == 2) /* else we have the remote server name */
   {
      ServName = argv[1];
      strcpy(MailServName, ServName);
      LocalServer = FALSE;
   }

   FullDBPath[0] = '\0';

   printf ("\n");
   /* Create and register new organizational certifier - ABCorp */
   error = REGNewCertifier (
              NULLHANDLE,            /* no certifier context */
              KFM_IDFILE_TYPE_ORG,   /* Organizational certifier */
              ServName,              /* registration server */
              "US",                  /* country code - optional */
              ORG_CERTNAME,          /* Organization */
              NULL,                  /* Org Unit */
              "abcorp",              /* password */
              ORG_CERT_ID,           /* ID file for new certifier */
              NULL,                  /* location of certifier - optional */
              NULL,                  /* comment - optional */
              NULL,                  /* Mail Server's name - optional */
              NULL,                  /* Mail file's name - optional */
              NULL,                  /* no forwarding address */
              fREGCreateIDFileNow |  /* flags - only create ID file */
              fREGUSARequested |
              fREGCreateAddrBookEntry,
              0,                     /* key width (must be 0) */
              MIN_PASS_LEN,          /* minimum password length */
              &REGCallback,          /* pointer to callback function */
              FullDBPath);           /* returned pathname of file where
                                        error occurred */

   printf ("\n\n");

   if (error)
   {
      printf("Error: unable to register new organizational certifier.\n");
      if (FullDBPath[0] != '\0')
         printf ("Error occurred in file %s\n", FullDBPath);
      return (ERR(error));
   }

   /* Prepare to call REGNewCertifier to create and register a new 
      organizational unit certifier - Sales org unit of ABCorp. 
      First get the Organization Certifier context for ABCorp, then pass
      this context as input to REGNewCertifier. 
   */

   if (error = GetCertCtx(ORG_CERT_ID, &hCertCtx, "abcorp"))
   {
      return (ERR(error));
   }
   
   error = REGNewCertifier (
              hCertCtx,              /* certifier context */
              KFM_IDFILE_TYPE_ORGUNIT, /* Organizational Unit certifier */
              ServName,              /* registration server */
              NULL,                  /* country code - optional*/
              NULL,                  /* Organization - Just use the above
                                        certifier context */
              ORGUNIT_CERTNAME,      /* Org Unit */
              "abcorp",              /* password */
              ORGUNIT_CERT_ID,       /* ID file for new certifier */
              NULL,                  /* location of certifier - optional */
              NULL,                  /* comment - optional*/
              NULL,                  /* Mail Server's name - optional */
              NULL,                  /* Mail file's name - optional */
              DNAME_JAYNE,           /* forwarding address */
              fREGCreateIDFileNow |  /* flags */
              fREGUSARequested    |
              fREGCreateAddrBookEntry,
              0,                     /* key width (must be 0) */
              MIN_PASS_LEN,          /* minimum password length */
              &REGCallback,          /* pointer to callback function */
              FullDBPath);           /* returned pathname of file where
                                        error occurred */

   printf ("\n\n");

   if (error)
   {
      printf("Error: unable to register new organizational unit certifier.\n");
      if (FullDBPath[0] != '\0')
         printf ("Error occurred in file %s\n", FullDBPath);
      SECKFMFreeCertifierCtx (hCertCtx);
      return (ERR(error));
   }

   /* Create and Register a new server.  Certify server with the Organization
      certifier created earlier (use the above Organization certifier 
      context).
    */

   error = REGNewServer (
              hCertCtx,              /* certifier context */
              KFM_IDFILE_TYPE_DERIVED, /* derived from certifier context */
              ServName,              /* registration server */
              NULL,                  /* Org Unit - optional */
              NEW_SERVNAME,          /* name of this new server */
              "abcorp",              /* password */
              SERVER_ID,             /* ID file for new server */
              ServLocation,          /* location of server - optional */
              NULL,                  /* comment - optional*/
              DOMAIN_NAME,           /* Domino domain of new server */
              NULL,                  /* network name - optional */
              NEW_USERNAME,          /* administrator's name - optional */
              "Corporate Server",       /* server title */
              fREGCreateIDFileNow |  /* flags */
              fREGUSARequested    |
              fREGCreateAddrBookEntry,
              MIN_PASS_LEN,           /* minimum password length */
              &REGCallback,           /* pointer to callback function */
              FullDBPath);            /* returned pathname of file where
                                         error occurred */

   printf ("\n\n");

   /* Free the certifier context */
   SECKFMFreeCertifierCtx (hCertCtx);

   if (error)
   {
      printf("Error: unable to register new server.  Error:%x\n", error);
      if (FullDBPath[0] != '\0')
         printf ("Error occurred in file %s\n", FullDBPath);
      return (ERR(error));
   }

  /* Prepare to call REGNewWorkstation() to create and register a new user.
     First get the Organization Unit Certifier context for ABCorp, 
     Sales Unit. Then, pass this certifier context as input to 
     REGNewWorkstation(). It will certify the new user with this certifier. 
   */
   if (error = GetCertCtx(ORGUNIT_CERT_ID, &hCertCtx, "abcorp"))
   {
      return (ERR(error));
   }

   /* if local machine, need to get the User Name of this workstation */
   if (LocalServer)
   {
     if (error = SECKFMGetUserName(MailServName))
       return(ERR(error));
   }

   error = REGNewWorkstation (
              hCertCtx,              /* certifier context */
              KFM_IDFILE_TYPE_DERIVED, /* derived from certifier context */
              ServName,              /* Registration server */
              "Inside Sales",        /* Org Unit - provides uniqueness
                                        to the name */
              "Doe",                 /* Last name */
              "Jayne",               /* First name */
              NULL,                  /* no middle initial */
              NULL,                  /* no password initially */
              USER_ID,               /* ID file name */
              WorkLocation,          /* location - optional */
              NULL,                  /* comment - optional */
              MAILSYSTEM_NOTES,      /* mail system  */
              MailServName,              /* mail server name */
              MAILFILENAME,          /* pathname of mail file */
              NULL,                  /* forward address - optional */
              fREGCreateIDFileNow |  /* flags */
              fREGUSARequested    |
              fREGCreateMailFileNow |
              fREGCreateAddrBookEntry,
              0,                      /* minimum password length */
              &REGCallback,           /* pointer to callback function */
              FullDBPath);            /* returned pathname of file where
                                         error occurred */

   printf ("\n\n");

   /* Free the certifier context */
   SECKFMFreeCertifierCtx (hCertCtx);

   if (error)
   {
      printf("Error: unable to register a new user. Error:%x\n", error);
      OSLoadString(NULLHANDLE, ERR(error), szErr, MAXSPRINTF-1);
      printf("Error: %s\n", szErr);
      if (FullDBPath[0] != '\0')
         printf ("Error occurred in file %s\n", FullDBPath);
      return (ERR(error));
   }


  /* Prepare to call REGReCertifyID() to recertify a new user.
     First get the Organization Unit Certifier context for ABCorp, 
     Sales Unit. Then, pass this certifier context as input to 
     REGReCertify(). It will recertify the new user with this certifier. 
   */
   if (error = GetCertCtx(ORGUNIT_CERT_ID, &hCertCtx, "abcorp"))
   {
      return (ERR(error));
   }

   printf("Begin recertifying %s...\n", NEW_USERNAME);

   error = REGReCertifyID (
              hCertCtx,              /* certifier context */
              0,                     /* Spare1 - reserved */
              ServName,              /* Registration server */
              NULL,                  /* Org Unit name */
              USER_ID,               /* ID file name */
              &ExpireDate,           /* Expiration Date */
              0,                     /* Spare2 - reserved */
              NULL,                  /* Spare3 - reserved */
              NULL,                  /* pointer to callback function - optional */
              NULL);                 /* Error path name */

   if (!error)
     printf("%s successfully recertified.\n", NEW_USERNAME);

   printf ("\n\n");

   /* Free the certifier context */
   SECKFMFreeCertifierCtx (hCertCtx);

   if (error)
   {
      printf("Error: unable to recertify a new user. Error:%x\n", error);
      OSLoadString(NULLHANDLE, ERR(error), szErr, MAXSPRINTF-1);
      printf("Error: %s\n", szErr);
      if (FullDBPath[0] != '\0')
         printf ("Error occurred in file %s\n", FullDBPath);
      return (ERR(error));
   }


   /* Find the new entries in the Name and Address book */

   /* Construct the path for the Name and Address book */

   if (error = OSPathNetConstruct(NULL, ServName, NA_NAME, FullDBPath))
   {
      printf("Error: unable to construct network path to N&A book.\n");
      return (ERR(error));
   }
   
   /* Open the database. */

   if (error = NSFDbOpen (FullDBPath, &hNABook))
   {
      printf("Error: unable to open N&A book '%s'.\n", FullDBPath);
      return (ERR(error));
   }

   /* Look up the Organization certifier entry */
   if (error = REGFindAddressBookEntry (hNABook, 
                                        "$Certifiers", 
                                        DNAME_ORG_CERT,
                                        &NoteID))
   {
      printf("Unable to find orgainizational certifier entry in N&A book.\n");
      OSLoadString(NULLHANDLE, ERR(error), szErr, ((WORD) (MAXSPRINTF-1)));
      printf("\n\n%s\n",szErr);
   }

   if (NoteID)
      printf (
         "\nOrganization Certifier, %s, found in NA Book.\nNoteID = %#lX\n\n",
         DNAME_ORG_CERT, NoteID);

   /* Look for the Org Unit certifier entry */
   if (error = REGFindAddressBookEntry (hNABook, 
                                       "$Certifiers", 
                                       DNAME_ORGUNIT_CERT,
                                       &NoteID))
   {
      printf("Unable to find orgainizational unit certifier entry in N&A book.\n");
      OSLoadString(NULLHANDLE, ERR(error), szErr, ((WORD) (MAXSPRINTF-1)));
      printf("\n%s\n",szErr);
   }

   if (NoteID)
      printf (
         "\nOrg Unit Certifier, %s, found in NA Book.\nNoteID = %#lX\n\n",
         DNAME_ORGUNIT_CERT, NoteID);

   /* Look for the new server entry */

   if (error = REGFindAddressBookEntry (hNABook, 
                                       "$Servers", 
                                       DNAME_OTTO,
                                       &NoteID))
   {
      printf("Error: unable to find server entry in N&A book.\n");
      OSLoadString(NULLHANDLE, ERR(error), szErr, ((WORD) (MAXSPRINTF-1)));
      printf("\n%s\n",szErr);
   }

   if (NoteID)
      printf ("\nServer, %s, found in NA Book.\nNoteID = %#lX\n\n", 
              DNAME_OTTO, NoteID);

   /* Look for the new user entry */

   if (error = REGFindAddressBookEntry (hNABook, 
                                       "$Users", 
                                       DNAME_JAYNE,
                                       &NoteID))
   {
      printf("Unable to find new user entry in N&A book.\n");
      OSLoadString(NULLHANDLE, ERR(error), szErr, ((WORD) (MAXSPRINTF-1)));
      printf("\n%s\n",szErr);
   }

   if (NoteID)
      printf ("\nUser, %s, found in NA Book.\nNoteID = %#lX\n\n",
              DNAME_JAYNE, NoteID);

   /* Close the database. */

   error = NSFDbClose (hNABook);
   return (ERR(error));
}


/************************************************************************

    FUNCTION:    REGCallback

    PURPOSE:     callback function - displays status during registration

    INPUT:       msg   - message to be displayed

*************************************************************************/

void LNCALLBACK REGCallback (char far *msg)
{
   printf("%s\n",msg);
}

/************************************************************************

    FUNCTION:    GetCertCtx

    PURPOSE:     returns a handle to the certifier context.

    INPUTS:      
        pCertFilePath - pointer to full path spec of certifier id file
        szPassword - password

    OUTPUTS:     
        phCertCtx     - pointer to handle to Certifier context

    RETURNS:    status code from API Call

*************************************************************************/

STATUS GetCertCtx (char far *pCertFile, HCERTIFIER *phCertCtx, 
                   char far *szPassword)
{
   TIMEDATE ExpDate;
   STATUS error;
   char CertName[MAXSPRINTF];    /* Note:  Org names may be up to 64 chars
                                   The CertName in this example is an org 
                                   name plus a  country code. */
   BOOL IsHierarchical;
   WORD FileVersion;
   KFM_PASSWORD KFMPassword, *pKFMPassword;    /* encoded password */

   OSCurrentTIMEDATE(&ExpDate);

   /* set the expiration date to two years from today (Domino and Notes default) */
   error = TimeDateAdjust(&ExpDate, 0, 0, 0, 0, 0, 2);
   ExpireDate = ExpDate;
  
   if (error)
      return (error);

   /* get the encoded password */
   if (szPassword == NULL)
      pKFMPassword = NULL;
   else
   {
      pKFMPassword = &KFMPassword;
      SECKFMCreatePassword (szPassword, pKFMPassword);
   }

   /* get the certifier context */
   error = SECKFMGetCertifierCtx (
              pCertFile,       /* Certifier file path spec */
              pKFMPassword,    /* encoded password */
              NULL,            /* no certifier log */
              &ExpDate,        /* expiration date */
              CertName,        /* returned name of certifier */
              phCertCtx,       /* returned handle to certifier context */
              &IsHierarchical, /* returned TRUE if certifier is 
                                  hierarchical */
              &FileVersion);   /* returned file version */

   return (error);
}
                                  
