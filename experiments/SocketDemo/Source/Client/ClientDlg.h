// ClientDlg.h : header file
//

#pragma once

#include "../NetLib/DataSocket.h"
#include "../NetLib/ProtocolDef.h"
#include "../NetLib/Protocol.h"
#include "map"

// CClientDlg dialog
class CClientDlg : public CDialog, public IDataEvent
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnOK();

private:
	virtual void on_packet(CDataSocket* from, const PACKET p);

	void	DisplayResult(int index, LPCTSTR result);

// Implementation
protected:
	HICON m_hIcon;
	CListBox	m_listbox;
	CDataSocket	m_socket;

	typedef struct
	{
		bool	isLong;
		int		listboxIndex;
	}KEY;

	typedef std::map<unsigned long, KEY> data_map;
	data_map	m_data;

private:
	//	dialog data
	int		m_a, m_b;
	CString	m_op;
	CString	m_msg;

	Protocol	m_protocol;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
