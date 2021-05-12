/*
 *      extwin.c - Windows DLL framework for extension manager password override.
 */

        /* Windows header files */
#include "windows.h"

        /* Domino and Notes header files */
#include "global.h"
#include "extmgr.h"
#include "bsafeerr.h"

        /* Sample program header files */
#include "extpwd.h"
#include "extenv.h"
#include "extpwdrs.h"

HINSTANCE        hDllInstance = (HINSTANCE) 0;

/*
 *                DLL Management
 */

#if defined (_WIN32)

        /* Win32 DLL Startup/Shutdown routine */
        DLL_EXPORT_PREFIX BOOL WINAPI LibMain (
                HANDLE                hInst,
                ULONG                 dwReason,
                LPVOID                lpReserved
        ) {
                switch (dwReason)
                {
                        case DLL_PROCESS_ATTACH:
                                        /* Save the instance handle */
                                hDllInstance = hInst;
                                break;

                        case DLL_PROCESS_DETACH:
                                        /* Deregister extension manager callbacks */
                                ExtClear ();
                                break;
                }

                return (TRUE);
        }

#endif

        /* Use a Windows dialog box to get the password */
int LNPUBLIC ExtGetPasswordText (
        DWORD             MaxPwdLen,
        char far *        FileName,
        char far *        OwnerName,
        DWORD far *       retLength,
        char far *        retPassword
) {
        FARPROC                lpfnPasswordDlgProc;
        EXT_DLG_DATA data;

        data.MaxPwdLen = MaxPwdLen;
        data.FileName = FileName;
        data.OwnerName = OwnerName;
        data.retLength = retLength;
        data.retPassword = retPassword;

        lpfnPasswordDlgProc = MakeProcInstance (
                (FARPROC) PasswordDlgProc,
                hDllInstance);

        return (DialogBoxParam (
                hDllInstance,
                "PwdDialog",
                HWND_DESKTOP,
                (DLGPROC)lpfnPasswordDlgProc,
                (LPARAM) (&data)));
}

        /* Windows dialog proc to obtain password */
BOOL CALLBACK PasswordDlgProc (
        HWND                hWndDlg,
        UINT                uMsg,
        WPARAM              wParam,
        LPARAM              lParam
) {
        EXT_DLG_DATA far *       pData;
        static DWORD             MaxPwdLen;
        static char far *        OwnerName;
        static DWORD far *       retLength;
        static char far *        retPassword;
        WORD                     wNotify;
        WORD                     wID;
        HWND                     hControl;

        switch (uMsg)
        {
                case WM_INITDIALOG:
                        pData = (EXT_DLG_DATA far *) lParam;
                        MaxPwdLen = pData->MaxPwdLen;
                        OwnerName = pData->OwnerName;
                        retLength = pData->retLength;
                        retPassword = pData->retPassword;

                        SetDlgItemText (hWndDlg, IDD_USERNAME, OwnerName);
                        return (TRUE);

                case WM_COMMAND:
#if defined (_WIN32)
                        wNotify = HIWORD (wParam);
                        wID = LOWORD (wParam);
                        hControl = (HWND) lParam;
#else
                        wNotify = HIWORD (lParam);
                        wID = wParam;
                        hControl = (HWND) LOWORD (lParam);
#endif
                        switch (wID)
                        {
                                case IDOK:
                                        *retLength = GetDlgItemText (
                                                hWndDlg,
                                                IDD_PASSWORD,
                                                retPassword,
                                                (int) MaxPwdLen);

                                        if (0 != *retLength)
                                                EndDialog (hWndDlg, DLG_ANSWER_OK);
                                        else
                                                EndDialog (hWndDlg, DLG_ANSWER_ERROR);
                                        return (TRUE);

                                case IDCANCEL:
                                        EndDialog (hWndDlg, DLG_ANSWER_CANCEL);
                                        return (TRUE);
                        }

                        return (FALSE);

        }
        
        return (FALSE);
}

        /* Message box routine */
STATUS LNPUBLIC ExtDisplayMessageBox (
        char far *pMessage,
        char far *pBoxTitle
) {
        MessageBox (GetFocus (), pMessage, pBoxTitle, MB_OK);
        return (NOERROR);
}
