#if !defined(AFX_ZOOMLEVELDLG_H__1BFC36D2_88DF_4C45_B2E5_E12FA01EF594__INCLUDED_)
#define AFX_ZOOMLEVELDLG_H__1BFC36D2_88DF_4C45_B2E5_E12FA01EF594__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomLevelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomLevelDlg dialog

class CZoomLevelDlg : public CDialog
{
// Construction
public:
	CZoomLevelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZoomLevelDlg)
	enum { IDD = IDD_ZOOMLEVEL };
	CSpinButtonCtrl	m_ZoomSpin;
	int		m_ZoomPercentage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomLevelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomLevelDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMLEVELDLG_H__1BFC36D2_88DF_4C45_B2E5_E12FA01EF594__INCLUDED_)
