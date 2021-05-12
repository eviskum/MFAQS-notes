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

#include <iostream.h>
#include <lncppapi.h>

#define ERR_BUF_SIZE 512
#define ATTACH_FILE_NAME        "image.tif"

int main(int argc, char *argv[])
{
    char *			DbFilename;
    char *			DbServer = NULL;
    LNNotesSession  Session;
	LNDatabase		Db;
    LNSTATUS		lnstat = LNNOERROR;

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

    LNSetThrowAllErrors(TRUE);
        
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

        //Create a new file in the database
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
                cout << " Created the attachment in the document !! " << endl << endl;
                //Now let's create some items in the note
                            
                // 1. Create a text item 
                
                LNText	 Txt;
                LNString TxtStr = "This is my text string ";
                LNString ItemName = "MyTextItem";	
                lnstat = Txt.SetValue(TxtStr);
                        
                lnstat = NewDoc.CreateItem(ItemName, Txt);
                cout << " Created an item named " << ItemName << endl;
                
                //2. Create a datetime item

                LNDatetime Today(Session.GetCurrentDatetime());
				LNDatetime Tomorrow(Today);
				
				LNDatetimes Dates;
				Dates.Append(Today);
				Tomorrow.AdjustDay(1);
				Dates.Append(Tomorrow);

                //Once again, name your item!
                LNString DatesName = "MyDatesItem";
                lnstat = NewDoc.CreateItem(DatesName, Dates);

                cout << " Created an item named " << DatesName << endl;

                // Also create subject of Note
                // (used for sorting docs in the default view)
                lnstat = Txt.SetValue("Attachment");	
                NewDoc.CreateItem("Subject", Txt);
            }	
        }
        //Let's check the attachment name and the file name of the 
        //attachment being created in this document.
        LNString name = attachment.GetAttachmentName();
        LNString filename = attachment.GetFilepath();

        cout << " Attachment Name Is: " << name << endl;
        cout << " Attachment File Name Is: " << filename << endl;

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


