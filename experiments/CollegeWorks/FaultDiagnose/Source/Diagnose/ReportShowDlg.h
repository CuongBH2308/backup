#if !defined(AFX_REPORTSHOWDLG_H__8E01D80B_5566_4174_853F_0B8634FBA022__INCLUDED_)
#define AFX_REPORTSHOWDLG_H__8E01D80B_5566_4174_853F_0B8634FBA022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportShowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportShowDlg dialog

class CReportShowDlg : public CDialog
{
// Construction
public:

	CReportShowDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportShowDlg)
	enum { IDD = IDD_REPORTSHOW };
	CListCtrl	m_reportlist;
	//}}AFX_DATA

	CString m_file_format;
	BOOL IsPrint;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static void DrawInfo(CDC &memDC, PRNINFO PrnInfo);
	// Generated message map functions
	//{{AFX_MSG(CReportShowDlg)
	afx_msg void OnSavereport();
	afx_msg void OnPrintreport();
	virtual BOOL OnInitDialog();
	afx_msg void OnPriview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTSHOWDLG_H__8E01D80B_5566_4174_853F_0B8634FBA022__INCLUDED_)
