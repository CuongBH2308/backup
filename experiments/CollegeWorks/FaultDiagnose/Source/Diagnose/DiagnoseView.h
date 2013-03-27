// DiagnoseView.h : interface of the CDiagnoseView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAGNOSEVIEW_H__0EA24F1B_87D5_4559_9F40_7D6A3DB687E1__INCLUDED_)
#define AFX_DIAGNOSEVIEW_H__0EA24F1B_87D5_4559_9F40_7D6A3DB687E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDiagnoseView : public CFormView
{
protected: // create from serialization only
	CDiagnoseView();
	DECLARE_DYNCREATE(CDiagnoseView)

public:
	//{{AFX_DATA(CDiagnoseView)
	enum { IDD = IDD_DIAGNOSE_FORM };
	CString	m_nodename;
	CString	m_compname;
	//}}AFX_DATA

// Attributes
public:
	CDiagnoseDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagnoseView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDiagnoseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDiagnoseView)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnData();
	afx_msg void OnRun();
	afx_msg void OnOnestep();
	afx_msg void OnContinue();
	afx_msg void OnOut();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DiagnoseView.cpp
inline CDiagnoseDoc* CDiagnoseView::GetDocument()
   { return (CDiagnoseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGNOSEVIEW_H__0EA24F1B_87D5_4559_9F40_7D6A3DB687E1__INCLUDED_)
