/*
 *      extenv.h - Environment header file for Extension 
 *                 Manager password program
 *
 *      This file declares the platform-specific functions used to build the
 *      Extension Manager password dialog box DLL.
 */

#ifndef _EXTENV_H_
#define _EXTENV_H_

/*
 *      Function Declarations
 */

#if defined (NT)

        /* Win32 DLL Startup/Shutdown routine */
        DLL_EXPORT_PREFIX BOOL WINAPI LibMain (
                HANDLE          hInst,
                ULONG           whyCalled,
                LPVOID          lpReserved
        );


#elif defined (OS2_2x)

        /* OS/2 DLL Startup/Shutdown routine */
        ULONG DLL_EXPORT_INFIX _DLL_InitTerm (
                HMODULE         hModule,
                ULONG           dwFlag
        );

#endif

#if defined(NT) 

        /* Windows dialog proc to obtain password */
BOOL CALLBACK PasswordDlgProc (
        HWND            hWndDlg,
        UINT            uMsg,
        WPARAM          wParam,
        LPARAM          lParam
);

#elif defined(OS2_2x)

        /* Presentation Manager proc to obtain password */
MRESULT EXPENTRY PasswordDlgProc (
        HWND            hWndDlg,
        ULONG           uMsg,
        MPARAM          mParam1,
        MPARAM          mParam2
);

#endif

#endif
