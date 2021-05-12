// NTRACKER.h : main header file for the NTRACKER DLL
//

#if !defined(AFX_NTRACKER_H__D2C409A5_9EE8_4380_BBE0_6AAD75A0B54D__INCLUDED_)
#define AFX_NTRACKER_H__D2C409A5_9EE8_4380_BBE0_6AAD75A0B54D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNTRACKERApp
// See NTRACKER.cpp for the implementation of this class
//

class CNTRACKERApp : public CWinApp
{
public:
	CNTRACKERApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNTRACKERApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNTRACKERApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTRACKER_H__D2C409A5_9EE8_4380_BBE0_6AAD75A0B54D__INCLUDED_)
