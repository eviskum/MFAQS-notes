//===========================================================================
//
//      Module: ATTACH.CPP
//
//      Description:
//              This program illustrates how to create new document in the
//              database and then add an attachment and other items to it.
//
//      Syntax: ATTACH <dbname> [server]
//                      dbname = RTXTSAMP.NSF
//
//===========================================================================
//
// Copyright (c) 1997, 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================


#include <iostream.h>
#include <lncppapi.h>


#if defined(MAC)
    // These headers are only needed for Macintosh applications.
#include <Types.h>
#include <Quickdraw.h>
#define thePort qd.thePort
#include <Dialogs.h>
#include <Menus.h>
#include <Windows.h>
#include <Fonts.h>
#include <Memory.h>
#include <stdio.h>
#endif

#define ERR_BUF_SIZE 512
#define ATTACH_FILE_NAME        "image.tif"

int main(int argc, char *argv[])
{
    char *			DbFilename;
    char *			DbServer = NULL;
    LNNotesSession  Session;
	LNDatabase		Db;
    LNSTATUS		lnstat = LNNOERROR;

#if defined(MAC)
    // On the Macintosh, we need to prompt for parameters
    // since they are not being passed in on the command line.

    char	fileBuffer[MAXPATH];
    char	serverBuffer[MAXPATH];
    
    // Initialize things for the Macintosh.
    InitGraf(&thePort); 
    InitFonts();
    InitWindows(); 
    InitDialogs(0);
    SetApplLimit(GetApplLimit()-8192); 
    MaxApplZone();
    MoreMasters(); 
    MoreMasters(); 
    MoreMasters();      
    
    DbFilename = fileBuffer;
    DbServer = serverBuffer;
    
    // Prompt for parameters since they are not being passed in on the command line.
    cout << endl << "Enter database filename: " << flush;
    gets(DbFilename);
    cout << "Enter server name:  " << flush;
    gets(DbServer);
#else
    // On anything other than the Macintosh, the parameters
    // are entered on the command line.

    // Check the command line.
    if (argc < 2 || argc > 3) 
    {
        cout << "\nUsage:\n\t" << argv[0]
            << " <filename> [<server>] \n"
            << endl;
        return(1); 
    }

    // Get info from command line.
    DbFilename = argv[1];
    
    if (argc == 3)
        DbServer = argv[2];
#endif

    LNSetThrowAllErrors(TRUE);

    // Initialize the C++ API.

 
   
        
    // Begin TRY Block. 
    // Throw all errors encountered during command execution.
    try 
    {
		 
		Session.Init(argc, argv);

        //Construct attachment file path.
        char  szFullPathName[LNMAXPATH];

        //Check the data path length first.
        LNINT   len = (Session.GetDataDirectory()).GetByteLength();

        if ( (len+12) <= LNMAXPATH )
        {
            memcpy(szFullPathName, Session.GetDataDirectory(), (size_t)len+1);
        }
        else
        {
            cout << "Data Directory path too long." << endl;
            return (1);
        }


#if defined(DOS) || defined(OS2) || defined(NT)  
        strcat(szFullPathName, "\\");
#elif defined(MAC)
        //      strcat(szFullPathName, ":");  
        //      not needed, colon included in string already
#elif defined(UNIX)
        strcat(szFullPathName, "/");
#endif
        strcat(szFullPathName, ATTACH_FILE_NAME);

        //Get the specified database.
        Session.GetDatabase(DbFilename, &Db, DbServer);

        //Open it.
        Db.Open();
    
        LNDocument	NewDoc;
        LNString	AttachmentFile(szFullPathName);
        LNString	AttachmentName("MyAttachment");
        LNAttachment	attachment;

        //create a new file in the database
        lnstat = Db.CreateDocument(&NewDoc	);
        if (lnstat)
            throw lnstat;
        else 
        {
            NewDoc.Open();
            //Let's create a compressed attachment in the document now.
            lnstat = NewDoc.CreateAttachment(AttachmentFile, AttachmentName,
                       TRUE, &attachment);
            if (lnstat)
                throw lnstat;
            else
            {
                cout << " Created the attachment in the document !! " << endl;
                cout << "\n" << endl;
                //Now let's create some items in the note
                            
                // 1. Create an LNText item 
                
                LNText	 Txt;
                LNString TxtStr = "This is my text string ";
                LNString ItemName = "MyItem";	
                lnstat = Txt.SetValue(TxtStr);
                        
                lnstat = NewDoc.CreateItem(ItemName, Txt);
                cout << " Created an item named " << ItemName << endl;
                
                //2. Create a LNDatetimes item (body of Note)

                LNDatetime Today;
                LNDatetime Tomorrow;
                Today.SetDate(6, 18, 1998);
                Tomorrow.SetDate(6, 19, 1998);

                LNDatetimes Dates;

                Dates.Append(Today);
                Dates.Append(Tomorrow);

                //Once again, name your item!
                LNString DatesName = "Dates";
                cout << " Created an item named " << DatesName << endl;

                // Also create subject of Note
                // (used for sorting docs in the default view)
                lnstat = Txt.SetValue("Attachment");	
                NewDoc.CreateItem("Subject", Txt);
            }	
        }
        //Let's check the attachment name and the file name of the 
        //attachment being created in this document.
        LNString filename = attachment.GetAttachmentName();
        LNString name = attachment.GetFilepath();

        cout << " Attachment Name Is: " << name << endl;
        cout << " and, the Attachment File Name Is: " << filename << endl;

        NewDoc.Save();

        // Close the document, free item memory.
        NewDoc.Close();
    
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
      
    //Close the database, free document memory.
    if (Db.IsOpen())
        Db.Close(); 

    //Terminate the API.
    Session.Term();

    char    CommandBuf[10];

    cout << endl;   
    cout << "All Done. Hit return to exit: ";
    cin.getline(CommandBuf, 10);

    //All done.
    return(0);
}
 
