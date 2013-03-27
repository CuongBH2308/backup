#if !defined(AFX_REPORTDEFDLG_H__9191B521_98E4_4D29_8AC3_0D1BDD293C8C__INCLUDED_)
#define AFX_REPORTDEFDLG_H__9191B521_98E4_4D29_8AC3_0D1BDD293C8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDefDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportDefDlg dialog

class CReportDefDlg : public CDialog
{
// Construction
public:
	CReportDefDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportDefDlg)
	enum { IDD = IDD_REPORTDEFINE };
	BOOL	m_outnode;
	BOOL	m_rule_id;
	BOOL	m_task_id;
	BOOL	m_node_name;
	BOOL	m_comp_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDefDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportDefDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDEFDLG_H__9191B521_98E4_4D29_8AC3_0D1BDD293C8C__INCLUDED_)
