// NTRACKER.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "NTRACKER.h"

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
// CNTRACKERApp

BEGIN_MESSAGE_MAP(CNTRACKERApp, CWinApp)
	//{{AFX_MSG_MAP(CNTRACKERApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNTRACKERApp construction

CNTRACKERApp::CNTRACKERApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNTRACKERApp object

CNTRACKERApp theApp;

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


class UserElm {
public:
	UserElm(CString& setopr, CString& setusername, CString& setdb, CString& setnoteid, CTime& setaccesstime);
	CString username, noteid, db, opr;
	CTime accesstime;
	UserElm *next;
};


class UserAccess {
public:
	UserAccess();
	~UserAccess();
	UserElm *startelm;
	int testdata(CString& opr, CString& username, CString& db, CString& noteid, CTime& accesstime);
};

class DataElm {
public:
	DataElm(CTime& set_time, CString set_task, CString set_operation, CString set_username,
			CString set_db, CString set_noteid, CString set_flags, CString set_flagstxt);
	CTime time;
	CString task, operation, username, db, noteid, flags, flagstxt;
	DataElm *next;
};


class UserData {
public:
	DataElm *data, *current;
	CString user;
	UserData();
	~UserData();
	void AddElm(CTime& time, CString task, CString operation, CString username,
				CString db, CString noteid, CString flags, CString flagstxt);
};

class UsersData {
public:
	UserData *users[1000];
	UsersData();
	~UsersData();
};


void AddData(CTime& time, CString task, CString operation, CString username,
			 CString db, CString noteid, CString flags, CString flagstxt);
void PrintData();



int NotesData(LPCTSTR filename);
int ProcessTrack(LPCTSTR trackpath);



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

extern "C" int PASCAL EXPORT DllWorker ( int argc, char *argv[] )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LJNORM("Starter NTRACKER data indlaesning")

	if (argc != 2) {
		LJERR("Forkert brug !!!! Korrekt brug: NTRACKER pattern trigger")
		return(DLLERROR);
	}

	Sleep(5000);
	TRY
	{
		CFile::Remove(argv[1]);
	}
	CATCH( CFileException, e )
	{
		LJERR("FEJL: kunne ikke slette trigger-fil")
		return(DLLERROR);
	}
	END_CATCH
	
	if (ProcessTrack(argv[0]) == FALSE) return(DLLERROR);
	return(DLLSUCCES);
}

TCHAR logstr[1024];

UsersData *usersdata;
DataElm *trackdata_start = NULL, *trackdata_current = NULL;

int ProcessTrack(LPCTSTR trackpath) {
	int retcode, succescode;
	CString searchpath, active_file, current_file;
	searchpath = trackpath;
	searchpath += "\\TR*.DAT";

	succescode = TRUE;

	CFileFind filefind;
	if (filefind.FindFile(searchpath)) {
		do {
			trackdata_start = NULL; trackdata_current = NULL;
			retcode = filefind.FindNextFile();
			active_file = (CTime::GetCurrentTime()).Format("TR%d%m%y.DAT");
			if (filefind.GetFileName() != active_file) {
				current_file = filefind.GetFilePath();
				sprintf(logstr, "NTRACKER> Trackfil indlaeses %s", (LPCTSTR) filefind.GetFileName());
				LJNORM(logstr)
				if (NotesData((LPCTSTR) current_file)) {
					CString newlocation;
					newlocation = trackpath;
					newlocation += "\\PROCESSED\\";
					newlocation += filefind.GetFileName();
					if (MoveFile((LPCTSTR) current_file, newlocation) == 0) {
						LJERR("NTACKER> FEJL kunne ikke rename fil")
						succescode = FALSE;
					}
				} else succescode = FALSE;
			}
		} while (retcode != 0);
	}
	filefind.Close();
	return(succescode);
}

int NotesData(LPCTSTR filename) {
	CStdioFile logdata;
	CString data;
	CString task, operation, username, db, noteid, flags, flagstxt;
	CString output;

	usersdata = new UsersData;

	UserAccess usac;
	if (logdata.Open(filename, CFile::modeRead) == 0) {
		delete usersdata;
		LJERR("NTRACKER> FEJL - kunne ikke aabne input fil")
		return(FALSE);
	}

	while (logdata.ReadString(data)) {
		if ((data.GetLength() == 300) && (data[1] == '1')) {
			CTime time(atoi((LPCTSTR) data.Mid(9,4)), atoi((LPCTSTR) data.Mid(14,2)),
				atoi((LPCTSTR) data.Mid(17,2)), atoi((LPCTSTR) data.Mid(20,2)),
				atoi((LPCTSTR) data.Mid(23,4)), atoi((LPCTSTR) data.Mid(26,2)));
			task = data.Mid(3,5);
			operation = data.Mid(30,13); operation.TrimRight();
			username = data.Mid(45,50); username.TrimRight();
			db = data.Mid(95,60); db.TrimRight();
			noteid = data.Mid(155,10);
			flags = data.Mid(174,7);
			flagstxt = data.Mid(183); flagstxt.TrimRight();

			if ((username == "CN=administrator/O=Aarhus Olie") ||
				(username == "CN=AO Notes Development/O=Aarhus Olie") ||
				(username == "CN=E-Prod/O=Internet") ||
				(username == "CN=Malaysia1/O=Aarhus Olie") ||
				((task > "00000") &&
				 ((username == "CN=Jan Løkkegaard Rasmussen/O=Aarhus Olie") ||
				  (username == "CN=Kim Korreborg/O=Aarhus Olie") ||
				  (username == "CN=Esben Viskum/O=Aarhus Olie"))));
			else {
				db.MakeUpper();
				if (usac.testdata(operation, username, db, noteid, time)) {
					AddData(time, task, operation, username, db, noteid, flags, flagstxt);
				}
			}
		}
	}
	PrintData();

	logdata.Close();
	delete usersdata;

	LJNORM("NTRACKER> SQL-indlaeser data.........")

	CDatabase SQLDB;

	TRY {
		SQLDB.Open("MSSQL", FALSE, FALSE, "ODBC;DATABASE=dwuserdef;UID=dwhm;PWD=golf;", FALSE);
	}
	CATCH(CDBException, e) {
		sprintf(logstr, "NTRACKER> FEJL i ODBC-connect: %s", (LPCTSTR) e->m_strError);
		LJERR(logstr)
		return(FALSE);
	}
	END_CATCH

	trackdata_current = trackdata_start;
	while (trackdata_current != NULL) {
		output = "insert into NOTESTRACK values (\'";
		output += trackdata_current->time.Format("%Y-%m-%d %H:%M:%S") + "\', \'";
		output += trackdata_current->task + "\', \'";
		output += trackdata_current->operation + "\', \'";
		output += trackdata_current->username + "\', \'";
		output += trackdata_current->db + "\', \'";
		output += trackdata_current->noteid + "\', \'";
		output += trackdata_current->flags + "\', \'";
		output += trackdata_current->flagstxt + "\')";
		trackdata_start = trackdata_current;
		trackdata_current = trackdata_current->next;
		delete trackdata_start;
		TRY {
			SQLDB.ExecuteSQL((LPCTSTR) output);
		}
		CATCH(CDBException, e) {
			sprintf(logstr, "NTRACKER> FEJL i sql-eksekvering: %s", (LPCTSTR) e->m_strError);
			LJERR(logstr)
			while (trackdata_current != NULL) {
				trackdata_start = trackdata_current;
				trackdata_current = trackdata_current->next;
				delete trackdata_start;
			}
			SQLDB.Close();
			return(FALSE);
		}
		END_CATCH
	}

	SQLDB.Close();

	LJNORM("NTRACKER> data indlaest")

	return(TRUE);
}



UserElm::UserElm(CString& setopr, CString& setusername, CString& setdb,
				 CString& setnoteid, CTime& setaccesstime) {
	next = NULL;
	username = setusername;
	noteid = setnoteid;
	db = setdb;
	accesstime = setaccesstime;
	opr = setopr;
}




UserAccess::UserAccess() {
	startelm = NULL;
}

UserAccess::~UserAccess() {
	UserElm *current = startelm;
	while (current != NULL) {
		startelm = current->next;
		delete current;
		current = startelm;
	}
}

int UserAccess::testdata(CString& opr, CString& username, CString& db, CString& noteid, CTime& accesstime) {
	UserElm *current, *prev;
	current = startelm;
	while (current != NULL) {
		if (current->username == username) {
			if ((current->db == db) && (current->noteid == noteid) && (current->opr == opr) &&
				(current->accesstime >= accesstime - CTimeSpan(0,0,15,0))) return(FALSE);
			else {
				current->opr = opr;
				current->db = db;
				current->noteid = noteid;
				current->accesstime = accesstime;
				return (TRUE);
			}
		}
		prev = current;
		current = current->next;
	}
	if (startelm == NULL) {
		startelm = new UserElm(opr, username, db, noteid, accesstime);
		return (TRUE);
	}
	prev->next = new UserElm(opr, username, db, noteid, accesstime);
	return (TRUE);
}


DataElm::DataElm(CTime& set_time, CString set_task, CString set_operation, CString set_username,
				 CString set_db, CString set_noteid, CString set_flags, CString set_flagstxt) {
	time = set_time;
	task = set_task;
	operation = set_operation;
	username = set_username;
	db = set_db;
	noteid = set_noteid;
	flags = set_flags;
	flagstxt = set_flagstxt;
	next = NULL;
}


UserData::UserData() {
	data = NULL;
}

UserData::~UserData() {
	DataElm *current, *next;
	current = data;
	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}
}

void UserData::AddElm(CTime& time, CString task, CString operation, CString username,
					  CString db, CString noteid, CString flags, CString flagstxt) {
	if (data == NULL) current = data = new DataElm(time, task, operation, username, db,
										noteid, flags, flagstxt);
	else current = current->next = new DataElm(time, task, operation, username, db,
											noteid, flags, flagstxt);
	user = username;
}


UsersData::UsersData() {
	for (int i = 0; i < 1000; i++) users[i] = NULL;
}

UsersData::~UsersData() {
	for (int i = 0; i < 1000; i++) {
		if (users[i] != NULL) delete users[i];
	}
}


void AddData(CTime& time, CString task, CString operation, CString username,
			 CString db, CString noteid, CString flags, CString flagstxt) {
	for (int i = 0; i < 1000; i++) {
		if (usersdata->users[i] == NULL) {
			usersdata->users[i] = new UserData();
			usersdata->users[i]->user = username;
			break;
		}
		if (usersdata->users[i]->user == username) {
			break;
		}
	}
	usersdata->users[i]->AddElm(time, task, operation, username, db, noteid, flags, flagstxt);
}

void PrintData() {
	CString lastdb;
	CTime lasttime;
	int noterepl = 0, notewrite = 0, noteread = 0;

	for (int i = 0; usersdata->users[i] != NULL; i++) {
		DataElm *rec;

		rec = usersdata->users[i]->data;
		lastdb = rec->db;
		lasttime = rec->time;

		if (trackdata_start == NULL) trackdata_start = trackdata_current =
			new DataElm(rec->time, rec->task, rec->operation, rec->username, rec->db,
						rec->noteid, rec->flags, rec->flagstxt);
		else trackdata_current = trackdata_current->next =
			new DataElm(rec->time, rec->task, rec->operation, rec->username, rec->db,
						rec->noteid, rec->flags, rec->flagstxt);
		if (rec->operation == "NoteOpen") noteread++;
		else notewrite++;

		while (rec->next != NULL) {
			rec = rec->next;
			if ((rec->db == lastdb) && (lasttime + CTimeSpan(0,0,0,5) > rec->time)
				&& rec->operation == "NoteOpen") noterepl++;
			else {
				trackdata_current = trackdata_current->next =
				new DataElm(rec->time, rec->task, rec->operation, rec->username, rec->db,
						rec->noteid, rec->flags, rec->flagstxt);
				if (rec->operation == "NoteOpen") noteread++;
				else notewrite++;
			}

			lastdb = rec->db;
			lasttime = rec->time;
		}
	}
	sprintf(logstr, "%d repl.noter, %d noteupdates, %d notereads registreret",
		noterepl, notewrite, noteread);
	LJNORM(logstr)
}
