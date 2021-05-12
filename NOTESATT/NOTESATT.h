// NOTESATT.h : main header file for the NOTESATT DLL
//

#if !defined(AFX_NOTESATT_H__9E4CB2E6_28EE_11D3_9021_00104BA3042C__INCLUDED_)
#define AFX_NOTESATT_H__9E4CB2E6_28EE_11D3_9021_00104BA3042C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNOTESATTApp
// See NOTESATT.cpp for the implementation of this class
//

class CNOTESATTApp : public CWinApp
{
public:
	CNOTESATTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNOTESATTApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNOTESATTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTESATT_H__9E4CB2E6_28EE_11D3_9021_00104BA3042C__INCLUDED_)
