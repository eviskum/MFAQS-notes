#define FILE_GET_SERVER_LIST    WM_USER+100
#define FILE_QUIT               WM_USER+110

#define SERVLIST_LISTBOX  101

int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

LRESULT FAR PASCAL MainWndProc(HWND, UINT, WPARAM, LPARAM);

BOOL FAR PASCAL ServListDlg(HWND, WORD, WPARAM, LPARAM);

STATUS GetSummary (BYTE far *, LPSTR);
