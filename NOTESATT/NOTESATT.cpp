// NOTESATT.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <lncppapi.h>
#include "NOTESATT.h"
#include <cstdint>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CNOTESATTApp

BEGIN_MESSAGE_MAP(CNOTESATTApp, CWinApp)
	//{{AFX_MSG_MAP(CNOTESATTApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNOTESATTApp construction

CNOTESATTApp::CNOTESATTApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNOTESATTApp object

CNOTESATTApp theApp;

#define DLLSUCCES	1
#define DLLERROR	2
#define LOGNORMAL	1
#define LOGERROR	2
#define LNORM( txt )	Log(txt, LOGNORMAL, FALSE);
#define LERR( txt )		Log(txt, LOGERROR, FALSE);
#define LJNORM( txt )	Log(txt, LOGNORMAL, TRUE);
#define LJERR( txt )	Log(txt, LOGERROR, TRUE);

HANDLE hLogEvent, hLogReady;
TCHAR log_txt[500];
int log_mode, log_job;

void Log(LPCTSTR txt, int mode, int job) {
	WaitForSingleObject(hLogReady, INFINITE);
	strcpy(log_txt, txt);
	log_mode = mode;
	log_job = job;
	SetEvent(hLogEvent);
}

extern "C" int PASCAL EXPORT DllGetLog(LPTSTR txt, int *mode, int *job)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	strcpy(txt, log_txt);
	*mode = log_mode;
	*job = log_job;
	return(0);
}

extern "C" int PASCAL EXPORT DllLogReg( HANDLE set_event, HANDLE set_ready )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	hLogEvent = set_event;
	hLogReady = set_ready;
	return(0);
}

#define ERR_BUF_SIZE 512

extern "C" int PASCAL EXPORT DllWorker ( int argc, char *argv[] )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LJNORM("Send NOTES attachments utility")

	if (argc != 1) {
		LJERR("Forkert brug !!!! Korrekt brug: NOTESATT noteslockfile")
		return(DLLERROR);
	}

	CString header, sendto, filename;
	CString attfilename, noteslockfile(argv[0]);
	int noteslockindex = noteslockfile.Find("noteslock",0);
	attfilename = noteslockfile.Left(noteslockindex) + "postpc" +
		noteslockfile.Mid(noteslockindex+9);
	TRY {
		CStdioFile conffile(noteslockfile, CFile::modeRead);
		conffile.ReadString(header);
		conffile.ReadString(sendto);
		conffile.ReadString(filename);
		conffile.Close();
	}
	CATCH(CFileException, e) {
		LJERR("FEJL i indlaesning af noteslock-fil. ")
		return(DLLERROR);
	}
	END_CATCH

	TRY
	{
		CFile::Remove(noteslockfile);
	}
	CATCH( CFileException, e )
	{
		LJERR("FEJL: kunne ikke slette trigger-fil")
		return(DLLERROR);
	}
	END_CATCH

	LNNotesSession  Session;
	LNMailMessage	newmail;
    LNSTATUS		lnstat = LNNOERROR;

    LNSetThrowAllErrors(TRUE);

	int errors = FALSE;

	try 
	{
		Session.Init(argc, argv);
		Session.CreateMailMessage(&newmail);
		LNString	SubjectString((LPCSTR) header);
        LNString	AttachmentFile((LPCSTR) attfilename);
        LNString	AttachmentName((LPCSTR) filename);
        LNString	SendToString((LPCSTR) sendto);
		LNAttachment	attachment;
		newmail.SetSubject(SubjectString);
		lnstat = newmail.CreateAttachment(AttachmentFile, AttachmentName,
					TRUE, &attachment);
		if (lnstat)
			throw lnstat;
		else
		{
			LJNORM("Sender file som attachment !! ");
			newmail.SendTo(SendToString);
			newmail.Save();
			newmail.Close();
		}

    }
    catch (LNSTATUS lnerror)
    {
        char ErrorBuf[ERR_BUF_SIZE];
        ErrorBuf[0] = '\0';
        LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
        LJERR(ErrorBuf);
		errors = TRUE;
    }
      
	Session.Term();

	if (errors) return(DLLERROR);
	return(DLLSUCCES);
}
