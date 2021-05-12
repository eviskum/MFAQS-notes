/****************************************************************************

    PROGRAM:    acls

    FILE:       acls.c

    SYNTAX:     acls  <database filename>  <database manager>

    PURPOSE:    demonstrates the Access Control List functions

    DESCRIPTION:

        This program processes the following logic:

        .  The Access Control List for the database is accessed via 
           NSFDbReadACL.

        .  A role is added to the ACL.  

           The first user is obtained from the command line and added 
           to the ACL with Manager access level and is granted the 
           newly added role.

           The second user is then added to the ACL with Author access
           level, but we will refine his access level privileges. 
           He will be unable to create documents and unable to delete 
           documents.

           The third user is then added to the ACL with Designer access
           level.

           The information from the access control list is then printed.

        .  A group is then added to the ACL with Designer access level.
        
           The third user is then deleted from the access control list 
           with the assumption that he is a member of the newly 
           added group.

           The second user's ACL entry is then modified to Editor access
           level.  And we will refine his access level privileges to
           be unable to delete documents.

           The access level for the Default user is modified to READER.
        
           The information from the access control list is then printed 
           again.

        .  ACLLookupAccess is then demonstrated.  This program looks up
           and prints ACL of the first user and the third user who 
           belongs to the newly added group.

        .  The ACL is stored in the database.

***************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Notes API include files */

#include <lapicinc.h>

#include <global.h>
#include <osmisc.h>
#include <nsfdb.h>
#include <names.h>
#include <osmem.h>
#include <textlist.h>
#include <acl.h>

#include <lapiplat.h>

#define LINEOTEXT   256
#define MKT_ROLE "Marketing"

#define MKT_ROLE_NUM ACL_BITPRIVCOUNT      /* Bit number for MKT_ROLE - 
                                              We assign the 6th bit for 
                                              this role.
                                              The first 5 bits were
                                              used for "privilege levels"
                                              which is obsolete now. */


#define USER2 "Johnny Doe"      /* the second user */
#define USER3 "Jayne Doe"       /* the third user  */
#define GROUP1 "Dev Team"

#define  STRING_LENGTH  256

typedef struct 
{
   NAMES_LIST NamesLookupList;
   char UserName[sizeof(USER3)];
   char GroupName[sizeof(GROUP1)];
} ACL_LOOKUP;

/* Function prototypes */

void LNPUBLIC EnumACLCallback (void *pParams, char far *Name,
                               WORD wAccessLevel,
                               ACL_PRIVILEGES far *pRoleBits,
                               WORD wAccessFlags);

void PrintACLLookup (char *pUserName, WORD wAccessLevel, 
                     WORD wAccessFlags,
                     HANDLE hRoleNames);

void GetAccessLevelStr (WORD wAccessLevel, char *pAccessLevelName);

void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                             char *db_name, char *db_mgr); 

/* Notes API subroutine */

LAPI_MAIN
{
   char DBPath[STRING_LENGTH];
   char DBMgr[STRING_LENGTH];      /* the first user */
   DBHANDLE hDB;
   STATUS nError;                  /* status returned from Notes API calls */
   HANDLE hACL;
   ACL_PRIVILEGES RoleBits = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};        
                                  /* A bit is set for each of 80 privileges
                                     granted to user.  The first 5 bits were
                                     used for "privilege level" which is
                                     obsolete.  Each of the rest 75 bits 
                                     is set for a role.                   */
   int i;
   ACL_LOOKUP LookupAccess;
   WORD wAccessLevel;
   WORD wAccessFlags;
   HANDLE hRoleNames;
   char szErrorStr[LINEOTEXT];
   STATUS  error = NOERROR;              /* error code from API calls */
   
   
   LAPI_INIT(error);
   if (error)
		LAPI_INIT_ERROR;

   /* Get the command line parameters that the user entered. */
   ProcessArgs(argc, argv, DBPath, DBMgr);

   /* Open the database */

   nError = NSFDbOpen (DBPath, &hDB);
   if (nError != NOERROR)
      LAPI_RETURN (ERR(nError));
   
   /* Get the ACL - the sample database contains the default ACL */
   nError = NSFDbReadACL(hDB, &hACL);
   if (nError != NOERROR)
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

   /* Set a new Role, Marketing */

   nError = ACLSetPrivName (hACL,           /* handle to ACL */
                            MKT_ROLE_NUM,   /* Role number */
                            MKT_ROLE);      /* Role name */

   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

   /* Set the role Bits to MKT_ROLE_NUM */
   /* DBMgr will be granted this role. */

   ACLSetPriv (RoleBits, MKT_ROLE_NUM);

   nError = ACLAddEntry (hACL,              /* handle to ACL */
                         DBMgr,             /* Name to add */
                         ACL_LEVEL_MANAGER, /* Access level */
                         &RoleBits,         /* role bits */
                         0);                /* Access level privilege 
                                               flag - 
                                               ignored */
   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }


   /* Now clear all role bits for the second user */
   for ( i = 0; i < ACL_PRIVCOUNT; i++)
      ACLClearPriv (RoleBits, i);

   /* Add the second user */

   nError = ACLAddEntry (hACL,              /* handle to ACL */
                         USER2,             /* Name to add */
                         ACL_LEVEL_AUTHOR,  /* Access level */
                         &RoleBits,         /* Role bits */
                         ACL_FLAG_AUTHOR_NOCREATE |
                         ACL_FLAG_NODELETE); /* Access level privilege 
                                                flag - 
                                                do not allow user to delete 
                                                or create docs */
   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

   /* Add USER3 */
   nError = ACLAddEntry (hACL,                /* handle to ACL */
                         USER3,               /* Name to add */
                         ACL_LEVEL_DESIGNER,  /* Access level */
                         &RoleBits,           /* Role bits */
                         0);                  /* access level privilege 
                                                 - ignored. */
   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

   /* List all users and their ACL info */

   printf ("\n*** ACL info after the first set of changes ***\n");
   printf ("\n                    Access Level/");
   printf ("\nName                Privileges           Roles\n");
   printf   ("----------          -------------        ----------\n\n");
   nError = ACLEnumEntries (hACL,            /* handle to ACL */
                            EnumACLCallback, /* callback function pointer */
                            &hACL);          /* pointer to params passed to
                                                callback function */

   if (nError != NOERROR)
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

   /* Add GROUP1 */
   nError = ACLAddEntry (hACL,               /* handle to ACL */
                         GROUP1,             /* Name to add */
                         ACL_LEVEL_DESIGNER, /* Access level */
                         &RoleBits,          /* Role bits */
                         0);                 /* access level privilege
                                                - ignored */
   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

   /* Now delete USER3.  Let's assume USER3 is a member of GROUP1. */
   nError = ACLDeleteEntry (hACL, USER3);
   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

   /* To illustrate ACLUpdateEntry, Update USER2 to Editor access and
    * unable to delete documents. 
    */

   nError = ACLUpdateEntry (hACL,               /* handle to ACL */
                            USER2,              /* user name to be updated */
                            ACL_UPDATE_LEVEL |  /* what is to be updated */
                            ACL_UPDATE_FLAGS,
                            NULL,               /* name - ignored */
                            ACL_LEVEL_EDITOR,   /* new access level */
                            NULL,               /* role - ignored */
                            ACL_FLAG_NODELETE); /* new access level
                                                   privilege flags */

   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

   /* Modify the access level for the Default user from Manager to
      Reader */

   nError = ACLUpdateEntry (hACL,               /* handle to ACL */
                            NULL,               /* update default user  */
                            ACL_UPDATE_LEVEL,   /* what is to be updated */
                            NULL,               /* name - ignored */
                            ACL_LEVEL_READER,   /* new access level */
                            NULL,               /* role - ignored */
                            0);                 /* access level privilage
                                                   flags  - ignored */

   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }


   /* List all users and their ACL info  */

   printf ("*** ACL info after the second set of changes ***\n");
   printf ("\n                    Access Level/");
   printf ("\nName                Privileges           Roles\n");
   printf   ("----------          -------------        ----------\n\n");
   nError = ACLEnumEntries (hACL,            /* handle to ACL */
                            EnumACLCallback, /* callback function pointer */
                            &hACL);          /* pointer to params passed to
                                                callback function */

   if (nError != NOERROR)
   {
      OSMemFree (hACL);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }


   /* Demonstrate ACLLookupAccess - Look up the Manager */
   LookupAccess.NamesLookupList.NumNames = 1; /* number of names in list */
   strcpy (LookupAccess.UserName, DBMgr);
   nError = ACLLookupAccess (hACL,            /* handle to ACL */
                             &(LookupAccess.NamesLookupList),
                                              /* pointer to NAMES_LIST */
                             &wAccessLevel,   /* returned access level */
                             &RoleBits,       /* returned role bits */
                             &wAccessFlags,   /* returned access level
                                                 privilege flags */
                             &hRoleNames);    /* handle to returned buffer of
                                                 role names */
   if (nError != NOERROR)
   {
       OSLoadString(0, ERR(nError), szErrorStr, LINEOTEXT - 1);
       printf ("\nError in ACLLookupAccess:  %s\n", szErrorStr);
   }

   else
      /* print out the info */
      PrintACLLookup (LookupAccess.UserName, wAccessLevel, 
                      wAccessFlags, hRoleNames);

      

   /* Demonstrate ACLLookupAccess - Look up USER3 who is a member of 
      the group, GROUP1 */
   
   LookupAccess.NamesLookupList.NumNames = 2; /* number of names in list */
   strcpy (LookupAccess.UserName, USER3);
   strcpy (LookupAccess.GroupName, GROUP1);
   nError = ACLLookupAccess (hACL,            /* handle to ACL */
                             &(LookupAccess.NamesLookupList),
                                              /* pointer to NAMES_LIST */
                             &wAccessLevel,   /* returned access level */
                             &RoleBits,       /* returned role bits */
                             &wAccessFlags,   /* returned access level
                                                 privilege flags */
                             &hRoleNames);    /* handle to returned buffer of
                                                 role names */
   if (nError != NOERROR)
   {
       OSLoadString(0, ERR(nError), szErrorStr, LINEOTEXT - 1);
       printf ("\nError in ACLLookupAccess:  %s\n", szErrorStr);
   }

   else
      /* print out the info */
      PrintACLLookup (LookupAccess.UserName, wAccessLevel, 
                      wAccessFlags, hRoleNames);

   /* Attach the ACL to the database */

   nError = NSFDbStoreACL (hDB,               /* database handle */
                           hACL,              /* ACL handle */
                           0L,                /* Reserved */
                           0);                /* Method - 0 to Update ACL
                                                          1 for store new
                                                          ACL */
   /* Free the memory associated with the ACL */

   OSMemFree (hACL);

   if (nError != NOERROR)
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(nError));
   }

  
   /* Close the database */
   nError = NSFDbClose (hDB);

   /* if there's no error print success message */
   if (nError == NOERROR)
     printf("\n\nProgram completed successfully.\n");

   LAPI_RETURN (ERR(nError));
}


void LNPUBLIC EnumACLCallback (void *pParams, char far *Name, 
                                 WORD wAccessLevel, 
                                 ACL_PRIVILEGES far *pRoleBits, 
                                 WORD wAccessFlags)

/*   EnumACLCallback - This function is called by ACLEnumEntries.
 *   It prints out ACL information for each name in the ACL.
 *
 *   Inputs:
 *      pParams      - pointer to parameters that have been passed to
 *                     ACLEnumEntries to be used by this callback function.
 *      Name         - user name.
 *      wAccessLevel - Access level.
 *      pRoleBits    - Pointer to role bits.
 *      wAccessFlags - Access level privilege flags (eg: unable to delete 
 *                     docs).
 */
{
   char szTempStr[LINEOTEXT];   /* this array is large enough to hold
                                   a variety of strings */
   int i;
   STATUS nError;

   printf ("%-20s", Name);
   
   /* Get the access level */
   GetAccessLevelStr (wAccessLevel, szTempStr);
   printf ("%-20s", szTempStr);

   /* Get the role name from the role bits */
   
   for (i = 0; i < ACL_PRIVCOUNT; i++)
      if (ACLIsPrivSet(*pRoleBits, i))
      {
         /* Get the role name */
         nError = ACLGetPrivName (
                     *(HANDLE *)pParams, /* handle to ACL */
                     (WORD)i,            /* role number */
                     szTempStr);         /* returned role name */
         if (nError == NOERROR)
            printf ("%s\n                                        ", 
                    szTempStr);
         else
         {
             OSLoadString(0, ERR(nError), szTempStr, LINEOTEXT - 1);
             printf ("%s\n                                        ",
                     szTempStr);
         }
      }

   printf("\n");

   /* Interpret the access level privilege flags */
   if (wAccessFlags & ACL_FLAG_AUTHOR_NOCREATE)
      printf ("                    Cannot create docs.\n");
   if (wAccessFlags & ACL_FLAG_NODELETE)
      printf ("                    Cannot delete docs.\n");
   printf("\n\n");
}


void PrintACLLookup (char *pUserName, WORD wAccessLevel, 
                     WORD wAccessFlags, 
                     HANDLE hRoleNames)

/*   PrintACLLookup - This function prints out the information obtained 
 *                    from ACLLookupAccess
 *
 *   Inputs:
 *      pUserName    - pointer to user that was looked up.
 *      wAccessLevel - access level.
 *      wAccessFlags - access level privilege flags (eg:  unable to 
 *                     delete documents).
 *      hRoleNames   - handle to buffer of role names.
 */

{
   char szTempStr[LINEOTEXT];      /* this array is large enough to hold
                                      a variety of strings */
   BOOL PrivLevels = FALSE;        /* are there any privilege levels? */
   void *pTList;                   /* pointer to text list */
   char szText[ACL_PRIVSTRINGMAX], *pText; /* contains role name */
   USHORT nEntries, i;
   WORD wTextSize;
   STATUS nError;

   printf ("\n\n*** \"%s\" ACL info from ACLLookupAccess function ***\n",
               pUserName);
   printf ("\n%s has the following access:\n", pUserName);
   GetAccessLevelStr (wAccessLevel, szTempStr);
   printf ("      Access Level:  %s\n", szTempStr);

   /* Interpret the access level privilege flags */
   if (wAccessFlags & ACL_FLAG_AUTHOR_NOCREATE)
      printf ("                     Cannot create docs.\n");
   if (wAccessFlags & ACL_FLAG_NODELETE)
      printf ("                     Cannot delete docs.\n");


   /* if there are no role names, just return */

   if (hRoleNames == NULLHANDLE)
      return;

   /* Role names may be obtained by the handle to the role names
    * handle which is a handle to a text list buffer.
    * First get the pointer to the buffer
    */
   pTList = OSLockObject (hRoleNames);
   nEntries = ListGetNumEntries(pTList,      /* pointer to text list */
                                FALSE);      /* indicates that the text
                                                list has no prefix */

   pText = szText;                             /* set up a pointer to a
                                                  text list entry */
   if (nEntries)
      printf ("      Roles:");

   for (i = 0; i < nEntries; i++)
   {
      nError = ListGetText (pTList,            /* pointer to text list */
                            FALSE,             /* text list has no prefix */
                            i,                 /* which text list entry */
                            &pText,            /* ptr to text string ptr */
                            &wTextSize);       /* num chars in text above */

      if (nError != NOERROR)
      {
         /* Get the text for that error */
         OSLoadString(0, ERR(nError), szTempStr, LINEOTEXT - 1);
      }
      else
      {
         /* Copy the entry to the print buffer */
         strncpy (szTempStr, pText, wTextSize);
         szTempStr [wTextSize] = '\0';
      }
      printf (" %s\n", szTempStr);
   }
   
   OSUnlockObject (hRoleNames);

   /* Free the memory associated with hRoleNames */
   OSMemFree (hRoleNames);

}

void GetAccessLevelStr (WORD wAccessLevel, char *pAccessLevelName)

/*   GetAccessLevelStr - This function translates a given access level
 *                       number to the corresponding character string. 
 *                       The caller is responsible 
 *                       for providing adequate space for the string.
 *
 *   Inputs:
 *      wAccessLevel     - access level.
 *      
 *   Outputs:    
 *      pAccessLevelName - contains the returned access level name.
 */

{
   switch (wAccessLevel)
   {
      case ACL_LEVEL_NOACCESS:
         strcpy (pAccessLevelName, "No Access");
         break;
      case ACL_LEVEL_DEPOSITOR:
         strcpy (pAccessLevelName, "Depositor");
         break;
      case ACL_LEVEL_READER:
         strcpy (pAccessLevelName, "Reader");
         break;
      case ACL_LEVEL_AUTHOR:
         strcpy (pAccessLevelName, "Author");
         break;
      case ACL_LEVEL_EDITOR:
         strcpy (pAccessLevelName, "Editor");
         break;
      case ACL_LEVEL_DESIGNER:
         strcpy (pAccessLevelName, "Designer");
         break;
      case ACL_LEVEL_MANAGER:
         strcpy (pAccessLevelName, "Manager");
         break;
      default:
         strcpy (pAccessLevelName, "Unknown");

   } /* switch */
}


/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    db_name -     database name obtained from command line or
                              from prompt.
							 
		db_mgr  -     the name of the database manager

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *db_name, char *db_mgr)
{ 
#ifndef MAC
    if (argc != 3)  
    {
#endif

        printf("Enter database name: ");      
        fflush (stdout);
        gets(db_name);
        printf("\n");
        printf ("Enter the manager name:  ");
        fflush (stdout);
        gets(db_mgr);

#ifndef MAC
    }    
    else
    {
        strcpy(db_name, argv[1]);    
        strcpy(db_mgr, argv[2]);    
    } /* end if */
#endif
} /* ProcessArgs */
