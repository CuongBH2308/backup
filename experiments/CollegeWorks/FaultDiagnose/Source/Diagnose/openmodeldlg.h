#if !defined(AFX_OPENMODELDLG_H__038F784E_2058_4864_87AA_C993858EA58E__INCLUDED_)
#define AFX_OPENMODELDLG_H__038F784E_2058_4864_87AA_C993858EA58E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenModelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenModelDlg dialog

class COpenModelDlg : public CDialog
{
// Construction
public:
	COpenModelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenModelDlg)
	enum { IDD = IDD_OPENMODEL };
	CComboBox	m_ModelCombo;
	CString	m_select_model;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenModelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenModelDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENMODELDLG_H__038F784E_2058_4864_87AA_C993858EA58E__INCLUDED_)
