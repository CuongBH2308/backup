// Diagnose.h : main header file for the DIAGNOSE application
//

#if !defined(AFX_DIAGNOSE_H__ECD2FA78_8D87_4D91_8410_DE0F9DDEF582__INCLUDED_)
#define AFX_DIAGNOSE_H__ECD2FA78_8D87_4D91_8410_DE0F9DDEF582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ModelView.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagnoseApp:
// See Diagnose.cpp for the implementation of this class
//

class CDiagnoseApp : public CWinApp
{
public:
	CDiagnoseApp();
	~CDiagnoseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagnoseApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	class_sqlserver_db m_sqlserver_db;
	
// Implementation
	//{{AFX_MSG(CDiagnoseApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CDiagnoseApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGNOSE_H__ECD2FA78_8D87_4D91_8410_DE0F9DDEF582__INCLUDED_)
