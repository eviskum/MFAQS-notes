// CapiErrD.cpp : implementation file
//

#include "stdafx.h"
#include "CapiErr.h"
#include "CapiErrD.h"

#include <global.h>
#include <osmisc.h>
#include <nsfdb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCapiErrD dialog

CCapiErrD::CCapiErrD(CWnd* pParent /*=NULL*/)
	: CDialog(CCapiErrD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCapiErrD)
	m_errCode = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCapiErrD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCapiErrD)
	DDX_Text(pDX, IDC_ERROR_CODE, m_errCode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCapiErrD, CDialog)
	//{{AFX_MSG_MAP(CCapiErrD)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_GET_ERROR, OnGetErrorClick)
	ON_BN_CLICKED(IDC_DEC, OnDecClick)
	ON_BN_CLICKED(IDC_HEX, OnHexClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCapiErrD message handlers

BOOL CCapiErrD::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	STATUS  nError = NotesInit();   /* Init the Domino and Notes runtime system. */
	
	// If the call to NotesInit fails, display an error message
	// and exit the program.
	if (nError != NOERROR)
	{
		 AfxMessageBox ("Unable to Initialize Notes!", MB_OK);
	}

	((CButton *)GetDlgItem(IDC_DEC))->SetCheck(1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCapiErrD::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialog::OnSysCommand(nID, lParam);
}

void CCapiErrD::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCapiErrD::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCapiErrD::OnDestroy() 
{
	CDialog::OnDestroy();
	
	NotesTerm(); /* Terminate the Domino and Notes runtime system. */
}

void CCapiErrD::OnGetErrorClick() 
{
	DWORD nError = NOERROR;
	CString strFormatText = "";
	int		iStatus = 0;
	LPTSTR	s = 0;

	s = m_errCode.GetBuffer(LINEOTEXT);

	GetDlgItemText(IDC_ERROR_CODE, m_errCode); 

	if(((CButton *)GetDlgItem(IDC_DEC))->GetCheck())
		iStatus = sscanf(LPCTSTR(m_errCode), "%d", &nError);
	else
		iStatus = sscanf(LPCTSTR(m_errCode), "%x", &nError);
	
	if(EOF == iStatus ||  0 == iStatus || nError > MAXWORD)
		strFormatText = "\n\n*** Not a valid Notes API STATUS code ***";
	else
	{
		strFormatText.Format("Status:\t %X (hex)\t %d (dec)\n\n", nError, nError);
		OSLoadString(NULLHANDLE, ERR(nError), s, LINEOTEXT-1);
		if(strlen(s)) 
			strFormatText += s;
		else
			strFormatText += "\n*** No matching ASCII text ***";
	}

	SetDlgItemText(IDC_ERROR_MESSAGE, strFormatText);
	m_errCode.ReleaseBuffer();
	((CEdit*)GetDlgItem(IDC_ERROR_CODE))->SetSel((int) 0,(int) -1);
}

void CCapiErrD::OnDecClick() 
{
	SetDlgItemText(IDC_ERROR_MESSAGE, "");	
}

void CCapiErrD::OnHexClick() 
{
	SetDlgItemText(IDC_ERROR_MESSAGE, "");	
}
