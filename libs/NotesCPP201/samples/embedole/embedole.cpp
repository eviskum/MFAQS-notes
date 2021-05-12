/****************************************************************************

	Copyright (c) 1998 Lotus Development Corporation

	Program:    EMBEDOLE

	File:       EMBEDOLE.CPP

	Syntax:     embedole <dbname> [<server>]

	Description:
		This program illustrates embedding an OLE object in a rich text item.
		A new document is created with a "Title" and "Body" fields.  The
		body contains rich text and an embedded OLE object.

****************************************************************************/

#include <ole2.h>

#include <lncppapi.h>
#include <iostream.h>

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

#define ERR_BUF_SIZE	512			// Size of error buffer

char CommandBuf[80];

//
//		Main program
//

int main(int argc, char *argv[])
{
	char *					DocPath = NULL;
	char					FullPathName [MAXPATH] = "";
	char *					pFilePart;
	char *                  DbFilename;
	char *                  DbServer = NULL;
	WCHAR					widePathName [MAXPATH_OLE];
	CLSID					oleClsid;
	LNOLEGUID *				pApiGuid = (LNOLEGUID *) (&oleClsid);
								// Deal with the structure conversion issue
	LPMALLOC				lpMalloc = NULL;


#if defined MAC
		// On the Macintosh, we need to prompt for parameters
		// since they are not being passed in on the command line.

	char                    docBuffer[MAXPATH];
	char                    fileBuffer[MAXPATH];
	char                    serverBuffer[MAXPATH];

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

	DocPath = docBuffer;
    DbFilename = fileBuffer;
	DbServer = serverBuffer;

	// Prompt for parameters since they are not being passed in on the command line.
	cout << endl << "Enter path to input file: " << flush;
	gets (DocPath);
	cout << "Enter database filename: " << flush;
    gets(DbFilename);
    cout << "Enter server name:  " << flush;
    gets(DbServer);
#else
		// On anything other than the Macintosh, the parameters
		// are entered on the command line.

	// Check the command line.
	if (argc < 3 || argc > 4)
	{
		cout << "\nUsage:\n\t" << argv[0]
			<< " <docfile> <filename> [<server>] \n"
			<< endl;
		return(1);
	}

	// Get info from command line.
	DocPath = argv[1];
	DbFilename = argv[2];
	if (argc == 4)
		DbServer = argv[3];
#endif

#ifdef W32
	// On Win32 systems, the OS can expand the pathname for us.
	GetFullPathName (DocPath, MAXPATH, FullPathName, &pFilePart);
#else
	// Everybody else must pass in the fully-qualified pathname
	strcpy (FullPathName, DocPath);
#endif

	// This is going to be LOTS of fun!  OLE has strict requirements for
	// the order of events and for releasing memory objects - hence the
	// incredibly deep nesting!!

	// Initialize the OLE interface
	if (FAILED(OleInitialize(NULL)))
	{
		cout << "Cannot initialize OLE" << endl;
		return (1);
	}

	// Get the current OLE memory allocation interface
	CoGetMalloc(MEMCTX_TASK, &lpMalloc);

	// Convert the file's pathname to UNICODE
	MultiByteToWideChar (
		CP_ACP,
		0,
		FullPathName,
		-1,
		widePathName,
		MAXPATH_OLE);

	// Find the OLE class ID for the file
	if(FAILED(GetClassFile(widePathName, &oleClsid)))
	{
		cout << "No CLSID found for " << DocPath << endl;
	}
	else
	{
		LPOLESTR		lpProgID = NULL;		// Content must be freed using lpMalloc

		// Next, get the ProgID for the OLE server
		if(FAILED(ProgIDFromCLSID(oleClsid, &lpProgID)))
		{
			cout << "Cannot convert CLSID to ProgID for " << DocPath << endl;
		}
		else
		{
			char			oleProgID [MAXPATH_OLE];	// Buffer for multi-byte copy of name
			LPOLESTR		lpUserType = NULL;			// Content must be freed using lpMalloc

			// Convert from UNICODE to platform characters
			WideCharToMultiByte (
				CP_ACP,
				0,
				lpProgID,
				-1,
				oleProgID,
				MAXPATH_OLE,
				NULL,
				NULL);

			// Get the OLE user type for the OLE server
			if(FAILED(OleRegGetUserType(oleClsid, USERCLASSTYPE_FULL, &lpUserType)))
			{
				cout << "Cannot obtain OLE user type for " << DocPath << endl;
			}
			else
			{
				char		oleUserType [MAXPATH_OLE];	// Buffer for multi-byte copy of string
				LPSTORAGE	lpRootStorage = NULL;		// Pointer to root IStorage

				// Convert from UNICODE to platform characters
				WideCharToMultiByte (
					CP_ACP,
					0,
					lpUserType,
					-1,
					oleUserType,
					MAXPATH_OLE,
					NULL,
					NULL);

				// Create a temporary OLE storage file
				if (FAILED(StgCreateDocfile (
					NULL,
					STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_DELETEONRELEASE,
					0,
					&lpRootStorage)))
				{
					cout << "Cannot create temporary storage file" << endl;
				}
				else
				{
					LPSTORAGE	lpSubStorage = NULL;	// Pointer to content IStorage

					// Create the sub-storage for the object data
					if (FAILED(lpRootStorage->CreateStorage(
						lpProgID,						// Needs the UNICODE version!
						STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
						0,
						0,
						&lpSubStorage)))
					{
						cout << "Cannot create object data sub-storage" << endl;
					}
					else
					{
						LPOLEOBJECT	lpOleObject = NULL;	// IOleObject interface

						// Create an OLE object based on the input file
						if (FAILED(OleCreateFromFile (
							CLSID_NULL,					// We do what the OLE documentation says . . .
							widePathName,				// Pathname
							IID_IOleObject,				// We'll need the IOleObject interface
							OLERENDER_DRAW,
							NULL,
							NULL,
							lpSubStorage,				// Create the content in the substorage
							(void FAR * FAR *) &lpOleObject)))
						{
							cout << "Failed to create OLE object from file" << endl;
						}
						else
						{
							LPPERSISTSTORAGE	lpPersistStorage = NULL;

							// Get the IPersistStorage interface for this object
							if (FAILED(lpOleObject->QueryInterface (
								IID_IPersistStorage,
								(void FAR * FAR *) &lpPersistStorage)))
							{
								cout << "Cannot obtain IPersistStorage interface" << endl;
							}
							else
							{
								// Copy the server's data to the substorage
								if (FAILED(OleSave (lpPersistStorage, lpSubStorage, TRUE)))
								{
									cout << "Storing object data failed" << endl;
								}
								else
								{
									// Provide the expected SaveCompleted() call
									if (SUCCEEDED(lpPersistStorage->SaveCompleted (NULL)))
									{
										STATSTG		StatStg;		// OLE storage info

										// Fetch the name of the temp file
										if (SUCCEEDED(lpRootStorage->Stat (&StatStg, STATFLAG_DEFAULT)))
										{
											char			tempFilePath [MAXPATH_OLE];
											LNNotesSession	Session;
											LNDatabase		Db;
											LNDocument		Doc;
											LNText			TitleText;
											LNRichText		BodyItem;
											LNRTCursor		Cursor;

											// Convert that name to multi-byte form
											WideCharToMultiByte (
												CP_ACP,
												0,
												StatStg.pwcsName,
												-1,
												tempFilePath,
												MAXPATH_OLE,
												NULL,
												NULL);

											// Release the storage for the OLE pathname
											lpMalloc->Free (StatStg.pwcsName);

											// If all that worked, we're finally ready to deal with Notes!!

											// Initialize the C++ API.
											if (LNNOERROR == Session.Init(argc, argv))
											{

												// Make the error handler throw all errors encountered during execution.
												LNSetThrowAllErrors(TRUE);

												try
												{
													// Get the specified database.
													Session.GetDatabase(DbFilename, &Db, DbServer);

													// Open it.
													Db.Open();

													// Create a new document.
													Db.CreateDocument (&Doc);

													// Open the document.
													Doc.Open();

													cout << "Created new document." << endl;

													// Create the Title.
													TitleText.SetValue ("Embedded OLE Object");
													Doc.CreateItem ("Subject", TitleText, LNITEMFLAGS_SUMMARY);

													// Create the Body.
													Doc.CreateItem("Body", &BodyItem);

													// Obtain a cursor.
													BodyItem.GetCursor(&Cursor);

													// Add the opening text
													BodyItem.Insert ("Embedding OLE object from file ", &Cursor);
													BodyItem.Insert (DocPath, &Cursor);
													BodyItem.Insert (" (Application ", &Cursor);
													BodyItem.Insert (oleUserType, &Cursor);
													BodyItem.Insert (")", &Cursor);

													// An embedded OLE object has 3 components in the C++ API:
													//	1)	The LNRTOLEObject is the rich text component.
													//	2)	The LNOLEObject contains the OLE activation information.
													//	3)	The actual OLE object content, stored as file attachments.

													// This sample uses LNRichText::CreateOLEObject () to construct
													// all these components.

													// Embed the OLE object.
													BodyItem.CreateOLEObject (
														tempFilePath,
														*pApiGuid,
														LNOLECLIPBOARDFORMAT_METAFILE,
														oleProgID,
														oleUserType,
														&Cursor);

													// Add the trailing text.
													BodyItem.Insert ("End of body", &Cursor);

													// Update the document (and write the BodyItem to the database).
													Doc.Save(); 

													// Close the document, free item memory.
													Doc.Close();

													cout << "Embedded OLE object from file " << DocPath <<
														" using application " << oleUserType << endl;
												}

												// Error handler.  If an error occurred, get the text of the error
												// message and display it.
												catch (LNSTATUS lnerror)
												{
													char ErrorBuf[ERR_BUF_SIZE];
													ErrorBuf[0] = '\0';
													LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
													cout << "Error: " << ErrorBuf << endl;
												}

												// Close the database, free document memory.
												Db.Close();

												// Terminate the API.
												Session.Term();
											}

											else
											{
												cout << "\nUnable to initialize the API" << endl;
											}
										}
									}
								}

								// Release the IOleObject interface
								lpPersistStorage->Release ();
								lpPersistStorage = NULL;
							}

							// Release the IOleObject interface
							lpOleObject->Release ();
							lpOleObject = NULL;
						}

						// Release the sub-storage
						lpSubStorage->Release ();
						lpSubStorage = NULL;
					}

					// Release the root storage
					lpRootStorage->Release ();
					lpRootStorage = NULL;
				}

				// Free the memory for the user type string
				lpMalloc->Free (lpUserType);
			}

			// Free the memory for the ProgID
			lpMalloc->Free (lpProgID);
		}
	}

	// Release the pointer to the IMalloc interface
	lpMalloc->Release ();
	lpMalloc = NULL;

	// Terminate OLE.
	OleUninitialize ();

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);

	// All done.
	return(0);
}
