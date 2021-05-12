/************************************************************************

    PROGRAM:    readmail

    FILE:       readmail.c

    PURPOSE:    Prints contents of message file to the screen

    SYNTAX:     readmail  <server>  <msg file database>

    DESCRIPTION:
        Readmail prints the entire contents of a Domino and Notes message file to the 
        screen. Suitable target Domino databases include any database created 
        using the Mail template. Warning: message files containing more than 
        two or three messages may cause the output from readmail to scroll 
        off the screen. READMAIL does not stop in response to Ctl+Break or 
        similar interrupt. Test readmail on small message files. The file
        hfinn.nsf is a small message file included in the API toolkit.

*************************************************************************/

/* OS and C include files */

#if defined(OS400)
#include <global.h>           /* global.h must be first for AS/400 */
#endif

#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#if defined(MAC)
#include <textutils.h>
#elif defined(UNIX)
#include <unistd.h>
#else
#include <stdlib.h>
#include <malloc.h>
#include <io.h>
#include <direct.h>
#include <fcntl.h>
#endif

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#if !defined(OS400)
#include <global.h>
#endif
#include <globerr.h>
#include <names.h>
#include <stdnames.h>                   /* FIELD_FORM, etc */
#include <mail.h>
#include <mailserv.h>
#include <nsf.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsfsearc.h>
#include <nsferr.h>
#include <osfile.h>                     /* OSPathNetConstruct */
#include <osmem.h>                      /* OSUnlockObject */
#include <osenv.h>                      /* OSGetEnvironmentString */
#if defined(OS400)
#include <misc.h>
#endif

#include <lapiplat.h>

/* constants */
#define     ERR_READMAIL_NOUNIQUE   (PKG_ADDIN + 0)
#define     READMAIL_BODY_LINELEN   40

/* function prototypes */
STATUS near pascal GetUniqueFileName(char *Drive, char *Ext,
                                        char *FileName);
                                                                                
void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                               char *server_name, char *db_name); 

#ifdef MAC
pascal        OSErr        GetFullPath(short vRefNum,
                                             long dirID,
                                             StringPtr name,
                                             short *fullPathLength,
                                             Handle *fullPath);

pascal        OSErr        FSMakeFSSpecCompat(short vRefNum,
                                             long dirID,
                                             ConstStr255Param fileName,
                                             FSSpecPtr spec);

#include <folders.h>
#endif

/************************************************************************

    FUNCTION:   NotesMain

    ALGORITHM:
        This opens the specified message file and read memos from it 
        using the Lotus C API for Domino and Notes Mail functions.

        Calls MailCreateMessageList only once, which reads in just the
        first 64K worth of messages, including their summary buffers.

        For each message, this prints out the following items:

            Originator 
            Recipient Name(s) and Domain (s)
            SendTo
            CopyTo
            From
            PostedDate
            Subject
            Body
            Attachments

*************************************************************************/

LAPI_MAIN
{
    STATUS      error = NOERROR;
    char       *szServerName;
    char       *szMailFile;
    char        szMailFilePath[MAXPATH+1];
    HANDLE      hMessageFile;
    HANDLE      hMessageList = NULLHANDLE, hMessage;
    DARRAY     *MessageList;
    WORD        MessageCount, Msg, RecipientCount, Rec;
    char        Originator[MAXRECIPIENTNAME+1];
    WORD        OriginatorLength;
    char        RecipientName[MAXRECIPIENTNAME+1];
    WORD        RecipientNameLength;
    char        UserName[MAXUSERNAME + 1];
    WORD        UserNameLength;
    char        DomainName[MAXDOMAINNAME+1];
    WORD        DomainNameLength;
    char        String[MAXSPRINTF+1];
    WORD        StringLength;
    TIMEDATE    Time;
    BOOL        NonDeliveryReport;
    DWORD       BodyFileSize;
    char        BodyFileName[MAXPATH_OLE];
    FILE       *BodyFile;
    char        OriginalFileName[MAXPATH+1];
    WORD        Att;
    BLOCKID     bhAttachment;
    char        szServer[80];           /* server names are < 80 chars */
    char        szDBName[MAXPATH];  



    LAPI_INIT(error);
    if (error)
      LAPI_INIT_ERROR;
          
    szServerName = szServer;
    szMailFile = szDBName;
    ProcessArgs(argc, argv, szServerName, szMailFile); 

    OSPathNetConstruct( NULL,               /* port name  */
                        szServerName,   
                        szMailFile,
                        szMailFilePath);

    /* Open the message file. */

    if (error = MailOpenMessageFile(szMailFilePath, &hMessageFile))
    {
        printf ("Error: unable to open '%s'.\n", szMailFilePath);
        goto Exit0;
    }

    /* Create message list of messages in the file - just 64K */

    if (error = MailCreateMessageList(hMessageFile, 
                        &hMessageList, &MessageList, &MessageCount))
    {
        printf ("Error: unable to create message list.\n");
        goto Exit1;
    }

    printf ("Mail file contains %d message(s).\n", MessageCount);

    /* Print out each of the outbound messages. */

    for (Msg = 0; Msg < MessageCount; Msg++)
    {
        printf ("\nMessage #%d: \n", Msg+1);

        if (error = MailOpenMessage (MessageList, Msg, &hMessage))
        {
            printf ("Error: unable to open message number %d.\n", Msg+1);
            goto Exit2;
        }

        /* Get the originator's name/address. */

        if (error = MailGetMessageOriginator(MessageList, Msg, 
                Originator, sizeof(Originator), &OriginatorLength))
        {
            printf ("Error: unable to get message originator.\n");
            goto Exit2;
        }

        Originator[OriginatorLength] = '\0';

        printf ("\tOriginator = '%s'\n", Originator);

        if (error = MailGetMessageInfo(MessageList, Msg, 
                            &RecipientCount, NULL, NULL))
        {
            printf ("Error: unable to get number of recipients in message.\n");
            MailCloseMessage (hMessage);
            goto Exit2;
        }

        printf ("\tNumber of Recipients = %d.\n", RecipientCount);

        for (Rec = 0; Rec < RecipientCount; Rec++)
        {
            MailGetMessageRecipient(MessageList, Msg, Rec, RecipientName,
                    sizeof(RecipientName), &RecipientNameLength);
            MailParseMailAddress(RecipientName, RecipientNameLength, 
                    UserName, sizeof(UserName), &UserNameLength,
                    DomainName, sizeof(DomainName), &DomainNameLength);

            UserName[UserNameLength] = '\0';
            DomainName[DomainNameLength] = '\0';

            printf ("\t\tRecipient %d = '%s'\t Domain = '%s'\n", Rec+1,
                                UserName, DomainName);
        }   /* end of loop over recipients */

        /* SendTo */
        MailGetMessageItem (hMessage, MAIL_SENDTO_ITEM_NUM, String, 
                                        MAXSPRINTF, &StringLength);

        String[StringLength] = '\0';
        printf ("\tTo: %s\n", String);

        /* CopyTo */
        MailGetMessageItem (hMessage, MAIL_COPYTO_ITEM_NUM, String, 
                                        MAXSPRINTF, &StringLength);
        String[StringLength] = '\0';
        printf ("\tCc: %s\n", String);

        /* From */
        MailGetMessageItem (hMessage, MAIL_FROM_ITEM_NUM, String, 
                                        MAXSPRINTF, &StringLength);
        String[StringLength] = '\0';
        printf ("\tFrom: %s\n", String);

        /* PostedDate */
        MailGetMessageItemTimeDate(hMessage, MAIL_POSTEDDATE_ITEM_NUM, &Time);
        ConvertTIMEDATEToText(NULL, NULL, &Time, String, 
                                    sizeof(String) - 1, &StringLength);
        String[StringLength] = '\0';
        printf("\tDate: %s\n", String);

        /* Subject. If non-delivery report, prefix with "NonDelivery of:" */

        MailGetMessageItem (hMessage, MAIL_SUBJECT_ITEM_NUM, String, 
                                        MAXSPRINTF, &StringLength);
        String[StringLength] = '\0';
        if (NonDeliveryReport = MailIsNonDeliveryReport(hMessage))
        {
            printf ("\tNonDelivery of: %s\n", String);
        }
        else
        {
            printf ("\tSubject: %s\n", String);
        }

        if (NonDeliveryReport)
        {
            MailGetMessageItem(hMessage, MAIL_INTENDEDRECIPIENT_ITEM_NUM,
                            String, sizeof(String), &StringLength);
            String[StringLength] = '\0';
            printf("\tIntended Recipients: %s\n", String);

            MailGetMessageItem(hMessage, MAIL_FAILUREREASON_ITEM_NUM,
                            String, sizeof(String), &StringLength);
            String[StringLength] = '\0';
            printf("\tFailure Reason: %s\n", String);
        }

        /* Body */


        if (error = GetUniqueFileName("", "TMP", BodyFileName))
        {
            printf ("Error: unable to create temporary file name.\n");
            MailCloseMessage (hMessage);
            goto Exit2;
        }
        if (error = MailGetMessageBodyText(hMessage,
                                    NULL,     /* Use standard Body item */
                                    "\r\n",    /* Newline-terminate */
                                    80,        /* 80 chars per line */
                                    TRUE,     /* Convert TABs */
                                    BodyFileName,
                                    &BodyFileSize))
        {
            printf ("Error: unable to get Message body into temporary file.\n");
            unlink(BodyFileName);
            MailCloseMessage (hMessage);
            goto Exit2;
        }

        /* Print each line of body text to the screen. */

        if (!(BodyFile = fopen(BodyFileName, "r")))
        {
            printf ("Error: unable to open temporary file.\n");
            unlink(BodyFileName);
            MailCloseMessage (hMessage);
            goto Exit2;
        }

        printf ("\tBody:\n");
        while (fgets(String, READMAIL_BODY_LINELEN, BodyFile))
        {
            printf("\t\t%s\n", String);
        }
        fclose(BodyFile);
        unlink(BodyFileName);

        /* Attachments */

        for (Att = 0; MailGetMessageAttachmentInfo(hMessage, Att, 
                                &bhAttachment, OriginalFileName, 
                                NULL, NULL, NULL, NULL, NULL); Att++)
        {
            printf("\tAttachment %d = '%s'\n", Att+1, OriginalFileName);
        }

        MailCloseMessage (hMessage);
    }   /* end of loop over messages */

    /* Free the message list and close the message file */

Exit2:
    if (hMessageList != NULLHANDLE)
    {
        OSUnlockObject(hMessageList);
        OSMemFree(hMessageList);
    }

Exit1:
    if (hMessageFile != NULLHANDLE)
        MailCloseMessageFile(hMessageFile);
Exit0:
    printf("\nProgram completed successfully.\n");    
        LAPI_RETURN (ERR(error));
}

/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    server_name - server name obtained from command line or
                              from prompt.
                db_name -     database name obtained from command line or
                              from prompt.

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *server_name, char *db_name)
{ 
#ifndef MAC
    if (argc != 3)  
    {
#endif

        printf("Enter server name: ");      
        fflush (stdout);
        gets(server_name);
        printf("\n");
        printf ("Enter database filename:  ");
        fflush (stdout);
        gets(db_name);

#ifndef MAC
    }    
    else
    {
        strcpy(server_name, argv[1]);    
        strcpy(db_name, argv[2]);    
    } /* end if */
#endif
} /* ProcessArgs */


/************************************************************************

    FUNCTION:   GetUniqueFileName

    INPUTS:
          Drive - Drive letter string pointer.
          Ext - Extension name string pointer.

    OUTPUTS:
       FileName - Unqiue file name.

*************************************************************************/

#ifndef MAC  /* Non-MAC platforms */

#ifdef UNIX  /* UNIX platforms */

STATUS near pascal GetUniqueFileName(char *Drive, char *Ext,
                                        char *FileName)

{
    int     file;
    WORD    Num;
    char    Name[17];
    char    cwd[MAXPATH];
    char   *Dir;
        
    /* Increment through numbered file names until a non-existent one found. */
   getcwd(cwd, MAXPATH);
   Dir = (char *)&cwd;
                
    for (Num = 0; Num <= 32767; Num++)
    {
         sprintf(Name, "%i", Num); /*_itoa(Num, Name, 10);*/
         sprintf(FileName, "%s%s.%s", Dir,Name,Ext); /* _makepath(FileName, Drive, Dir, Name, Ext);*/
        if ((file = open(FileName, O_RDONLY, 0666)) == -1)
            return(NOERROR);
        close(file);
    }
    FileName[0] = '\0';
    return(ERR_READMAIL_NOUNIQUE);
}

#else  /* Wintel + OS/2 */

STATUS near pascal GetUniqueFileName(char *Drive, char *Ext,
                                        char *FileName)

{
    int     file;
    WORD    Num;
    char    Name[17];
    char    cwd[MAXPATH];
    char   *Dir;
        
    /* Increment through numbered file names until a non-existent one found. */
   getcwd(cwd, MAXPATH);
   Dir = (char *)&cwd;
                
    for (Num = 0; Num <= 32767; Num++)
    {
        _itoa(Num, Name, 10);
        _makepath(FileName, Drive, Dir, Name, Ext);
        if ((file = open(FileName, O_BINARY | O_RDONLY)) == -1)
            return(NOERROR);
        close(file);
    }
    FileName[0] = '\0';
    return(ERR_READMAIL_NOUNIQUE);
}

#endif /* Non-MAC platforms */

#else  /* Pure MAC  */


STATUS near pascal GetUniqueFileName(char *Drive, char *Ext,
                                        char *FileName)

{
    int     file;
    WORD    Num;
    char    Name[17];
    char    cwd[MAXPATH];
    char   *Dir;
    short   vRefNum;
    long    dirId;
    OSErr   myErr;
    short   fullPathLength;
    Handle  fullPath;
    char   *strPtr;
        
        myErr = FindFolder(kOnSystemDisk, kTemporaryFolderType, kCreateFolder, &vRefNum, &dirId);
        
    /* Increment through numbered file names until a non-existent one found. */

    for (Num = 0; Num <= 32767; Num++)
    {
        NumToString(Num, (unsigned char *) Name);
                CtoPstr((char *)(*(StringHandle)Name));
        GetFullPath(vRefNum, dirId, (StringPtr)Name, &fullPathLength, &fullPath);
        strncpy( FileName, (char *)(*(StringHandle)fullPath),fullPathLength);
                FileName[fullPathLength] = NULL;
                DisposeHandle(fullPath);
        if ((file = open(FileName, O_BINARY | O_RDONLY)) == -1)
            return(NOERROR);
        close(file);
    }
    FileName[0] = '\0';
    return(ERR_READMAIL_NOUNIQUE);
}


pascal     OSErr   GetFullPath(short vRefNum,
                               long dirID,
                               StringPtr name,
                               short *fullPathLength,
                               Handle *fullPath)
{
        OSErr             result;
        FSSpec            spec;
        CInfoPBRec        pb;
        
        *fullPathLength = 0;
        *fullPath = NewHandle(0);        /* Allocate a zero-length handle */
        if ( *fullPath != NULL )
        {
                result = FSMakeFSSpecCompat(vRefNum, dirID, name, &spec);
                /* File not found error is ok because it isn't going to be there */
                if ( result == noErr || result == fnfErr)
                {
                        if ( spec.parID == fsRtParID )
                        {
                                /* The object is a volume */
                                
                                /* Add a colon to make it a full pathname */
                                ++spec.name[0];
                                spec.name[spec.name[0]] = ':';
                                
                                /* We're done */
                                (void) Munger(*fullPath, 0, NULL, 0, &spec.name[1], spec.name[0]);
                                result = MemError();
                        }
                        else
                        {
                                /* The object isn't a volume */
                                
                                /* Add the object name */
                                (void) Munger(*fullPath, 0, NULL, 0, &spec.name[1], spec.name[0]);
                                
                                /* Get the ancestor directory names */
                                pb.dirInfo.ioNamePtr = spec.name;
                                pb.dirInfo.ioVRefNum = spec.vRefNum;
                                pb.dirInfo.ioDrParID = spec.parID;
                                do        /* loop until we have an error or find the root directory */
                                {
                                        pb.dirInfo.ioFDirIndex = -1;
                                        pb.dirInfo.ioDrDirID = pb.dirInfo.ioDrParID;
                                        result = PBGetCatInfoSync(&pb);
                                        if ( result == noErr )
                                        {
                                                /* Append colon to directory name */
                                                ++spec.name[0];
                                                spec.name[spec.name[0]] = ':';
                                                
                                                /* Add directory name to fullPath */
                                                (void) Munger(*fullPath, 0, NULL, 0, &spec.name[1], spec.name[0]);
                                                result = MemError();
                                        }
                                } while ( (result == noErr) && (pb.dirInfo.ioDrDirID != fsRtDirID) );
                        }
                }
                
                if ( result == noErr )
                {
                        /* Return the length */
                        *fullPathLength = GetHandleSize(*fullPath);
                }
                else
                {
                        /* Dispose of the handle and return NULL */
                        DisposeHandle(*fullPath);
                        *fullPath = NULL;
                }
        }
        else
        {
                result = memFullErr;
        }
        
        return ( result );
}

/*****************************************************************************/

/*
**        File Manager FSp calls
*/

/*****************************************************************************/

pascal        OSErr        FSMakeFSSpecCompat(short vRefNum,
                                              long dirID,
                                              ConstStr255Param fileName,
                                              FSSpecPtr spec)
{
        OSErr        result;
        
        result = FSMakeFSSpec(vRefNum, dirID, fileName, spec);
                /* Fix a bug in Macintosh PC Exchange's MakeFSSpec code where 0 is */
                /* returned in the parID field when making an FSSpec to the volume's */
                /* root directory by passing a full pathname in MakeFSSpec's */
                /* fileName parameter. */
                if ( (result == noErr) && (spec->parID == 0) )
                        spec->parID = fsRtParID;

        return ( result );
}

#endif
