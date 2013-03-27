// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

#pragma comment(lib, "../Debug/NetLib.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CClientDlg dialog




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
	, m_socket(this)
	, m_a(0), m_b(0), m_op(_T("+"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Text(pDX, IDC_EDIT1, m_a);
	DDX_Text(pDX, IDC_EDIT2, m_b);
	DDX_Text(pDX, IDC_COMBO2, m_op);
	DDX_Text(pDX, IDC_EDIT3, m_msg);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO2);
	box->AddString(_T("+"));
	box->AddString(_T("-"));
	box->AddString(_T("*"));
	box->AddString(_T("/"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientDlg::OnOK()
{
	if (m_socket.m_hSocket != INVALID_SOCKET)	return;
	m_socket.Create();
	m_socket.Connect(_T("127.0.0.1"), 1600);
}

void CClientDlg::on_packet(CDataSocket *from, const PACKET p)
{
	//	find the data
	data_map::const_iterator i = m_data.find(p->sn);
	if (i == m_data.end())
	{
		CString err;
		err.Format(_T("Error reply SN: %08x"), p->sn);
		MessageBox(err, _T("SN Error"), MB_OK | MB_ICONSTOP);
		return;
	}

	if (p->status != ERR_OK)
	{
		CString err;
		err.Format(_T("%04x"), p->status);
		DisplayResult(i->second.listboxIndex, err);
		m_data.erase(i);
		return;
	}

	//	display the text
	if (i->second.isLong)
	{
		if (p->len < sizeof(HEADER) + sizeof(long))
		{	//	error format
			DisplayResult(i->second.listboxIndex, _T("Error Format"));
			m_data.erase(i);
			return;
		}
		CString ret;
		ret.Format(_T("%d"), *(long*)(p->body));
		DisplayResult(i->second.listboxIndex, ret);
	}
	else
	{	//	string
		CString ret(p->body);
		DisplayResult(i->second.listboxIndex, ret);
	}
	m_data.erase(i);
}

void CClientDlg::DisplayResult(int index, LPCTSTR text)
{
	CString item;
	m_listbox.GetText(index, item);
	item += text;
	m_listbox.DeleteString(index);
	m_listbox.InsertString(index, item);
}

void CClientDlg::OnBnClickedButton1()
{
	UpdateData();

	CString text;
	text.Format(_T("%d %s %d = "), m_a, m_op, m_b);
	int index = m_listbox.AddString(text);
	KEY k = { true, index };
	PACKET p = m_protocol.arithmetics(m_a, m_b, m_op[0]);
	m_data[p->sn] = k;
	//	send
	m_socket.send_packet(p);
	//	free
	m_protocol.free_packet(p);
}

void CClientDlg::OnBnClickedButton2()
{
	USES_CONVERSION;

	UpdateData();

	if (m_msg.IsEmpty())	return;
	PACKET p = m_protocol.message(T2CA(m_msg));
	m_msg += _T(" = ");
	//	add to list box
	int index = m_listbox.AddString(m_msg);
	KEY k = { false, index };
	m_data[p->sn] = k;
	//	send
	m_socket.send_packet(p);
	//	free
	m_protocol.free_packet(p);
}
