// SocketDemoDlg.h : header file
//

#pragma once

#include "NetListener.h"

// CSocketDemoDlg dialog
class CSocketDemoDlg : public CDialog
{
// Construction
public:
	CSocketDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SOCKETDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:

// Implementation
protected:
	HICON m_hIcon;
	CNetListener	m_listener;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
