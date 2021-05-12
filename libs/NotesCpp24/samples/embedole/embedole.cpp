/****************************************************************************

	Program:    EMBEDOLE

	File:       EMBEDOLE.CPP

	Syntax:     embedole <dbname> [<server>]

	Description:
		This program illustrates embedding an OLE object in a rich text item.
		A new document is created with a "Title" and "Body" fields.  The
		body contains rich text and an embedded OLE object.

		This is a new version of EMBEDOLE which has been restructured and
		enhanced to store an appropriate bitmap representation of the OLE
		object.

****************************************************************************/

#include <ole2.h>

#include <lncppapi.h>
#include <iostream.h>

#define ERR_BUF_SIZE	512			// Size of error buffer

char CommandBuf[80];

//
//		CFailure - Application failure class
//

class CFailure
{
	public:
		CFailure (void) { ; }
		~CFailure (void) { ; }
};

//
//		Function declarations
//

	// Embed the OLE object into Notes
void EmbedInNotes (
	LNNotesSession &	Session,
	char *				pDocPath,
	char *				pDbFilename,
	char *				pDbServer,
	char *				pOleUserType,
	char *				pFilePath,
	LNOLEGUID *			pApiGuid,
	char *				pOleProgID,
	LNRichText *		pGraphicContainer
);

	// Get the file name (if any) for an OLE object, and
	// convert the name from UNICODE to multi-byte characters.
void GetMultiByteTempFileName (
	LPMALLOC		lpMalloc,
	LPSTORAGE		lpStorage,
	char *			pBuffer,
	int				bufferSize
);

	// Copy the contents of an OLE object into
	// the destination IStorage.
void CopyObjectToIStorage (
	LPOLEOBJECT			lpOleObject,
	LPSTORAGE			lpDestStorage
);

	// Try to get the graphic representation
	// of the OLE object.
void GetGraphic (
	LPOLEOBJECT			lpOleObject,
	LNRichText *		pGraphicContainer
);

	// Convert a Windows bitmap to a Notes LNGraphic
void ConvertBitmapToLNGraphic (
	STGMEDIUM *			pStgMedium,
	LNRichText *		pGraphicContainer
);

// Microsoft routines to store bitmap in a file
extern "C" PBITMAPINFO CreateBitmapInfoStruct (
	HBITMAP		hBmp
);

extern "C" BOOL CreateBMPFile (
	LPTSTR		pszFile,
	PBITMAPINFO	pbi, 
	HBITMAP		hBMP,
	HDC			hDC
);

//
//		Main program
//

int main(int argc, char *argv[])
{
	LNNotesSession		Session;

		// Cleanup controls
	BOOL				IsNotesInitialized = FALSE;
	BOOL				IsOleInitialized = FALSE;

		// Argument pointers
	char *				DocPath = NULL;
	char *				pFilePart;
	char *				DbFilename;
	char *				DbServer = NULL;

	CLSID				oleClsid;
	LNOLEGUID *			pApiGuid = (LNOLEGUID *) (&oleClsid);
								// Deal with the structure conversion issue

		// Some name strings must be converted from UNICODE to multi-byte (native)
		// characters, or vice-versa.
	char				FullPathName [MAXPATH] = "";
	WCHAR				widePathName [MAXPATH_OLE];

	LPOLESTR			lpProgID = NULL;			// Program ID string (UNICODE);  must be freed using lpMalloc
	char				oleProgID [MAXPATH_OLE];	// Buffer for multi-byte copy of name
	
	LPOLESTR			lpUserType = NULL;			// OLE user type string (UNICODE);  must be freed using lpMalloc
	char				oleUserType [MAXPATH_OLE];	// Buffer for multi-byte copy of string

		// OLE interface pointers
	LPMALLOC			lpMalloc = NULL;			// Pointer to IMalloc interface
	LPSTORAGE			lpRootStorage = NULL;		// Pointer to root IStorage
	LPSTORAGE			lpSubStorage = NULL;		// Pointer to content IStorage
	LPOLEOBJECT			lpOleObject = NULL;			// IOleObject interface

	char				tempFilePath [MAXPATH_OLE];	// Name of OLE's temporary file

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

#ifdef W32
	// On Win32 systems, the OS can expand the pathname for us.
	GetFullPathName (DocPath, MAXPATH, FullPathName, &pFilePart);
#else
	// Everybody else must pass in the fully-qualified pathname
	strcpy (FullPathName, DocPath);
#endif

	try
	{
		// Initialize the Notes C++ API
		if (LNNOERROR != Session.Init(argc, argv))
			throw ("Unable to initialize the C++ API");

		IsNotesInitialized = TRUE;

		// Initialize the OLE interface
		if (FAILED(OleInitialize(NULL)))
			throw ("Cannot initialize OLE");

		IsOleInitialized = TRUE;

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
			throw (CFailure ());
		}

			// Next, get the ProgID for the OLE server
		if(FAILED(ProgIDFromCLSID(oleClsid, &lpProgID)))
		{
			cout << "Cannot convert CLSID to ProgID for " << DocPath << endl;
			throw (CFailure ());
		}

			// Convert ProgID from UNICODE to platform characters
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
			throw (CFailure ());
		}

			// Convert UserType from UNICODE to platform characters
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
			throw ("Cannot create temporary storage file");
		}

			// Create the sub-storage for the object data
		if (FAILED(lpRootStorage->CreateStorage(
			lpProgID,						// Needs the UNICODE version!
			STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
			0,
			0,
			&lpSubStorage)))
		{
			throw ("Cannot create object data sub-storage");
		}

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
			throw ("Failed to create OLE object from file");
		}

			// Store the contents of the OLE object into the substorage
		CopyObjectToIStorage (lpOleObject, lpSubStorage);

			// Get the name of the OLE temporary file
		GetMultiByteTempFileName (lpMalloc, lpRootStorage, tempFilePath, MAXPATH_OLE);

			// Get the graphical representation of the OLE object
		LNRichText	graphicContainer;
		GetGraphic (lpOleObject, &graphicContainer);

			// Everything is ready - store into Notes!
		EmbedInNotes (
			Session,
			DocPath,
			DbFilename,
			DbServer,
			oleUserType,
			tempFilePath,
			pApiGuid,
			oleProgID,
			&graphicContainer);
	}
	catch (char * pMessage)
	{
		cout << "*** Error:  " << pMessage << endl;
	}
	catch (CFailure)
	{
		;
	}

	/////////////////////////////////
	// Clean up and free resources //
	/////////////////////////////////

		// Release the IOleObject interface
	if (((LPOLEOBJECT) NULL) != lpOleObject)
	{
		lpOleObject->Release ();
		lpOleObject = NULL;
	}

		// Release the sub-storage
	if (((LPSTORAGE) NULL) != lpSubStorage)
	{
		lpSubStorage->Release ();
		lpSubStorage = NULL;
	}

		// Release the root storage
	if (((LPSTORAGE) NULL) != lpRootStorage)
	{
		lpRootStorage->Release ();
		lpRootStorage = NULL;
	}

		// Free the memory for the user type string
	if (((LPOLESTR) NULL) != lpUserType)
		lpMalloc->Free (lpUserType);

		// Free the memory for the ProgID
	if (((LPOLESTR) NULL) != lpProgID)
		lpMalloc->Free (lpProgID);

		// Release the IMalloc interface pointer
	if (((LPMALLOC) NULL) != lpMalloc)
	{
		lpMalloc->Release ();
		lpMalloc = NULL;
	}

		// Close the OLE session
	if (IsOleInitialized)
		OleUninitialize ();

		// Close the Notes session
	if (IsNotesInitialized)
		Session.Term();

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);

	// All done.
	return(0);
}

void EmbedInNotes (
	LNNotesSession &	Session,
	char *				pDocPath,
	char *				pDbFilename,
	char *				pDbServer,
	char *				pOleUserType,
	char *				pFilePath,
	LNOLEGUID *			pApiGuid,
	char *				pOleProgID,
	LNRichText *		pGraphicContainer
) {
	BOOL				throwFailure = FALSE;
	LNDatabase			Db;
	LNDocument			Doc;
	LNText				TitleText;
	LNRichText			BodyItem;
	LNRTCursor			Cursor;
	LNRTCursor			graphicCursor;
	LNRTOLEObject		rtOleObject;
	LNGraphic			newGraphic;

	// Make the error handler throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try
	{
		// Try to fetch the new graphic for the OLE object
		pGraphicContainer->GetCursor (&graphicCursor);
		graphicCursor.GotoFirst (LNRTTYPE_GRAPHIC, &newGraphic);

		// Get the specified database.
		Session.GetDatabase(pDbFilename, &Db, pDbServer);

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
		BodyItem.Insert (pDocPath, &Cursor);
		BodyItem.Insert (" (Application ", &Cursor);
		BodyItem.Insert (pOleUserType, &Cursor);
		BodyItem.Insert (")", &Cursor);

		BodyItem.StartNewParagraph (&Cursor);

		// An embedded OLE object has 3 components in the C++ API:
		//	1)	The LNRTOLEObject is the rich text component.
		//	2)	The LNOLEObject contains the OLE activation information.
		//	3)	The actual OLE object content, stored as file attachments.

		// This sample uses LNRichText::CreateOLEObject () to construct
		// all these components.

		// Embed the OLE object.
		BodyItem.CreateOLEObject (
			pFilePath,
			*pApiGuid,
			LNOLECLIPBOARDFORMAT_METAFILE,
			pOleProgID,
			pOleUserType,
			&Cursor,
			"",
			&rtOleObject);

			// If we have a new graphic, insert it
		if (!newGraphic.IsNull ())
		{
			rtOleObject.SetGraphic (newGraphic);
		}

		BodyItem.StartNewParagraph (&Cursor);

		// Add the trailing text.
		BodyItem.Insert ("End of body", &Cursor);

		// Update the document (and write the BodyItem to the database).
		Doc.Save(); 

		// Close the document, free item memory.
		Doc.Close();

		cout << "Embedded OLE object from file " << pDocPath <<
			" using application " << pOleUserType << endl;
	}

	// Error handler.  If an error occurred, get the text of the error
	// message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		ErrorBuf[0] = '\0';
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
		throwFailure = TRUE;
	}

	// Close the database, free document memory.
	Db.Close();

	if (throwFailure)
		throw (CFailure ());
}

	// Get the file name (if any) for an OLE object, and
	// convert the name from UNICODE to multi-byte characters.
void GetMultiByteTempFileName (
	LPMALLOC		lpMalloc,
	LPSTORAGE		lpStorage,
	char *			pBuffer,
	int				bufferSize
) {
	STATSTG				StatStg;					// OLE storage info

		// Fetch the name of the temp file
	if (FAILED(lpStorage->Stat (&StatStg, STATFLAG_DEFAULT)))
		throw ("Stat failed;  serious OLE error!!");

		// Convert that name to multi-byte form
	WideCharToMultiByte (
		CP_ACP,
		0,
		StatStg.pwcsName,
		-1,
		pBuffer,
		bufferSize,
		NULL,
		NULL);

		// Release the storage for the OLE pathname
	lpMalloc->Free (StatStg.pwcsName);
}

	// Copy the contents of an OLE object into
	// the destination IStorage.
void CopyObjectToIStorage (
	LPOLEOBJECT			lpOleObject,
	LPSTORAGE			lpDestStorage
) {
	BOOL				throwFailure = FALSE;
	LPPERSISTSTORAGE	lpPersistStorage = NULL;	// Pointer to OLE object's IPersistStorage interface

		// Get the IPersistStorage interface for this object
	if (FAILED(lpOleObject->QueryInterface (
		IID_IPersistStorage,
		(void FAR * FAR *) &lpPersistStorage)))
	{
		throw ("Cannot obtain IPersistStorage interface");
	}

	try
	{
			// Copy the server's data to the substorage
		if (FAILED(OleSave (lpPersistStorage, lpDestStorage, TRUE)))
			throw ("Storing object data failed");

			// Provide the expected SaveCompleted() call
		if (FAILED(lpPersistStorage->SaveCompleted (NULL)))
			throw ("SaveCompleted failed;  OLE server error!!");

	}
	catch (char * pMessage)
	{
		cout << "*** Error:  " << pMessage << endl;
		throwFailure = TRUE;
	}
	catch (CFailure)
	{
		throwFailure = TRUE;
	}

		//Release the IPersistStorage interface
	if (((LPPERSISTSTORAGE) NULL) != lpPersistStorage)
	{
		lpPersistStorage->Release ();
		lpPersistStorage = NULL;
	}

	if (throwFailure)
		throw (CFailure ());
}

	// Try to get the graphic representation
	// of the OLE object.
	// Note that a failure in this routine shouldn't
	// cause an error in the application!
void GetGraphic (
	LPOLEOBJECT			lpOleObject,
	LNRichText *		pGraphicContainer
) {
	LPDATAOBJECT		lpDataObject = NULL;
	FORMATETC			formatEtc;
	STGMEDIUM			stgMedium;

	try
	{
		if (!OleIsRunning (lpOleObject))
			if (FAILED (OleRun (lpOleObject)))
				throw ("Cannot run OLE object");

			// Try to get the IDataObject interface
		if (FAILED (lpOleObject->QueryInterface (IID_IDataObject, (void **) (&lpDataObject))))
			throw ("Object does not support IDataObject");

//			// Set up the FORMATETC structure for the metafile
//		formatEtc.cfFormat = CF_METAFILEPICT;
//		formatEtc.ptd = NULL;
//		formatEtc.dwAspect = DVASPECT_CONTENT;
//		formatEtc.lindex = -1;
//		formatEtc.tymed = TYMED_MFPICT;
//
//			// Clear the STGMEDIUM structure
//		memset ((void *) (&stgMedium), 0, sizeof (stgMedium));
//
//		if ((SUCCEEDED (lpDataObject->GetData (&formatEtc, &stgMedium))) &&
//			(NULL != stgMedium.hGlobal))
//		{
//				// Got the metafile - convert to Notes format
//			ConvertMetafileToNotes (stgMedium, &metaFile);
//
//			if (NULL != stgMedium.pUnkForRelease)
//				(stgMedium.pUnkForRelease)->Release ();
//			else
//				DeleteMetaFile (stgMedium.hMetaFilePict);
//		}

			// Set up the FORMATETC structure for the bitmap
		formatEtc.cfFormat = CF_BITMAP;
		formatEtc.ptd = NULL;
		formatEtc.dwAspect = DVASPECT_CONTENT;
		formatEtc.lindex = -1;
		formatEtc.tymed = TYMED_GDI;

			// Clear the STGMEDIUM structure
		memset ((void *) (&stgMedium), 0, sizeof (stgMedium));

		if ((SUCCEEDED (lpDataObject->GetData (&formatEtc, &stgMedium))) &&
			(NULL != stgMedium.hGlobal))
		{
				// Got the bitmap - convert to Notes format
			ConvertBitmapToLNGraphic (&stgMedium, pGraphicContainer);

			if (NULL != stgMedium.pUnkForRelease)
				(stgMedium.pUnkForRelease)->Release ();
			else
				DeleteObject (stgMedium.hBitmap);
		}
	}
	catch (char * pMessage)
	{
		cout << ">>> Warning:  " << pMessage << endl;
	}
	catch (CFailure)
	{
		;
	}

		// Release resources
	if (((LPDATAOBJECT) NULL) != lpDataObject)
	{
		lpDataObject->Release ();
		lpDataObject = NULL;
	}
}

	// Since Notes won't convert a bitmap directly to rich text,
	// let's use the C++ API facility to call an import library
	// to do the job for us!
	//
	// If unable to convert the bitmap to an LNGraphic, the
	// LNGraphic is left uninitialized.
void ConvertBitmapToLNGraphic (
	STGMEDIUM *			pStgMedium,
	LNRichText *		pGraphicContainer
) {
	char				tempFilePath [] = "d:\\apipp\\samples\\embedole\\temp.bmp";
	PBITMAPINFO			pBitmapInfo;
	LNRTCursor			cursor;
	HDC					hDc;

	pBitmapInfo = CreateBitmapInfoStruct (pStgMedium->hBitmap);
	if (((PBITMAPINFO) NULL) == pBitmapInfo)
		return;

	hDc = CreateCompatibleDC (NULL);
	if (((HDC) NULL) == hDc)
		return;

	if (!CreateBMPFile (tempFilePath, pBitmapInfo, pStgMedium->hBitmap, hDc))
	{
		DeleteDC (hDc);
		return;
	}

	try
	{
		pGraphicContainer->GetEndCursor (&cursor);
		pGraphicContainer->Import (tempFilePath, &cursor);
	}
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		ErrorBuf[0] = '\0';
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error: " << ErrorBuf << endl;
	}

	DeleteDC (hDc);
	DeleteFile (tempFilePath);
}


