// CalculatorDlg.h : header file
//

#if !defined(AFX_CALCULATORDLG_H__30641DE3_E72C_403F_8947_17F2D405B027__INCLUDED_)
#define AFX_CALCULATORDLG_H__30641DE3_E72C_403F_8947_17F2D405B027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalculatorLib/Calculator.h"
//#include<cmath>

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

class CCalculatorDlg : public CDialog
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalculatorDlg)
	enum { IDD = IDD_CALCULATOR_DIALOG };
	
	CListBox	m_VarsList;

	int		m_CalType;

	CString	m_strExp;
	CString	m_strResult;


	CString	m_VarName;
	double	m_dVarValue;

	bool m_bModify;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	
	bool IsAlpha(char ch);
	HICON m_hIcon;

	CCalculator m_Cal;

	CRect m_rclarge,m_rcsmall;

	// Generated message map functions
	//{{AFX_MSG(CCalculatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtoncal();
	afx_msg void OnRadioType1();
	afx_msg void OnRadioType2();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBtnsetupvar();
	afx_msg void OnButtonSubmit();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonModify();
	afx_msg void OnSelchangeListVars();
	afx_msg void OnDblclkListVars();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATORDLG_H__30641DE3_E72C_403F_8947_17F2D405B027__INCLUDED_)
