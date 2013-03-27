#if !defined(AFX_SELECTDATADLG_H__9B5D3015_68A2_43F1_81E8_10CC46D29753__INCLUDED_)
#define AFX_SELECTDATADLG_H__9B5D3015_68A2_43F1_81E8_10CC46D29753__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectDataDlg dialog

class CSelectDataDlg : public CDialog
{
// Construction
public:
	CSelectDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectDataDlg)
	enum { IDD = IDD_SELECTDATA };
	CComboBox	m_DataCombo;
	CString	m_select_time;
	//}}AFX_DATA
	CString m_select_data;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectDataDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTDATADLG_H__9B5D3015_68A2_43F1_81E8_10CC46D29753__INCLUDED_)
