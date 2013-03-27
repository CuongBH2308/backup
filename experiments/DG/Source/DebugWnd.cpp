#include "stdafx.h"
#include "BuildOption.h"
#ifdef ENABLE_REPORT

#include "DebugWnd.h"
#include "DebugManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace DG;

IMPLEMENT_DYNAMIC(CDebugWnd, CDialog)

BEGIN_MESSAGE_MAP(CDebugWnd, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDebugWnd::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_CHECK_HOOKSYSTEMASSERT, &CDebugWnd::OnBnClickedCheckHookSystemAssert)
	ON_BN_CLICKED(IDC_BUTTON_OPENLOGFILE, &CDebugWnd::OnBnClickedButtonOpenLogFile)
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()


CDebugWnd::CDebugWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CDebugWnd::IDD, pParent)
{

}

CDebugWnd::~CDebugWnd()
{
}

void CDebugWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ERROR, m_reportList);
	DDX_Control(pDX, IDC_CHECK_IGNOREASSERT, m_btnIgnoreAssert);
	DDX_Control(pDX, IDC_CHECK_STOPONERROR, m_btnStopOnError);
	DDX_Control(pDX, IDC_CHECK_HOOKSYSTEMASSERT, m_btnHookSystemAssert);
}

BOOL CDebugWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Make the dialog accessable in windows Task Bar
	ModifyStyleEx(0,WS_EX_APPWINDOW);

	// Initialize the report list control.
	m_reportList.Initialize();

	// Put the debug window to the right-botton corner.
	RepositionWindow();

	//m_btnHookSystemAssert.SetCheck(BST_CHECKED);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDebugWnd::OnClose()
{
	ShowWindow(SW_SHOWMINIMIZED);
}

BOOL  CDebugWnd::GetIgnoreAssert()
{
#ifdef _DEBUG
	return m_btnIgnoreAssert.GetCheck();
#else
	return TRUE;
#endif
	
}
BOOL  CDebugWnd::GetStopOnError()
{
#ifdef _DEBUG
	return m_btnStopOnError.GetCheck();
#else
	return FALSE;
#endif
}

BOOL  CDebugWnd::GetHookSystemAssert()
{
#ifdef _DEBUG
	return m_btnHookSystemAssert.GetCheck();
#else
	return TRUE;
#endif
}

void  CDebugWnd::SetIgnoreAssert(BOOL bYes)
{
#ifdef _DEBUG
	return m_btnIgnoreAssert.SetCheck(bYes);
#endif

}
void  CDebugWnd::SetStopOnError(BOOL bYes)
{
#ifdef _DEBUG
	return m_btnStopOnError.SetCheck(bYes);
#endif
}

void  CDebugWnd::SetHookSystemAssert(BOOL bYes)
{
#ifdef _DEBUG
	return m_btnHookSystemAssert.SetCheck(bYes);
#endif
}


void CDebugWnd::Report(const CString& strTime, const CString& strSourceLine, const CString& strMsg)
{
	m_reportList.AppendReport(strTime, strSourceLine, strMsg);
}

void CDebugWnd::OnBnClickedButtonClear()
{
	m_reportList.ClearReports();
}

void CDebugWnd::OnBnClickedCheckHookSystemAssert()
{
	CDebugManager::GetInstance()->ToggleSystemAssert();
}

void CDebugWnd::OnBnClickedButtonOpenLogFile()
{
	CDebugManager::GetInstance()->OpenLogFile();
}

void CDebugWnd::OnNcLButtonDblClk(UINT nHitTest,CPoint point)
{
	// double click on the title bar to reposition the window
	if( nHitTest == HTCAPTION)
		RepositionWindow();
	return __super::OnNcLButtonDblClk(nHitTest, point);
}


void CDebugWnd::RepositionWindow()
{
	int nScreenWidth    = ::GetSystemMetrics( SM_CXSCREEN );
	int nScreenHeight   = ::GetSystemMetrics( SM_CYSCREEN );

	RECT wndRect;
	GetWindowRect( &wndRect );

	SetWindowPos( &wndTop, 
		nScreenWidth - ( wndRect.right - wndRect.left ), 
		nScreenHeight - ( wndRect.bottom - wndRect.top ) - 100,	// Make it a little bit higher because it's always curtained off by the XP task bar.
		0, 0, 
		SWP_NOSIZE );
}

#endif