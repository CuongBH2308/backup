/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "fw_mdiframewnd.h"
#include "fw_mdichildwnd.h"
#include "fw_document.h"
#include "fw_view.h"
#include "fw_winapp.h"
#include "pt_environment.h"

IMPLEMENT_DYNAMIC(FW_MDIFrameWnd, CMDIFrameWnd)

FW_MDIFrameWnd::FW_MDIFrameWnd()
:m_wndToolBar(this)
{
}

FW_MDIFrameWnd::~FW_MDIFrameWnd()
{
}

BEGIN_MESSAGE_MAP(FW_MDIFrameWnd, CMDIFrameWnd)
	//{{AFX_MSG_MAP(FW_MDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	ON_WM_CLOSE()
	ON_WM_ENABLE()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// static 
FW_MDIFrameWnd* FW_MDIFrameWnd::GetMDIFrameWnd()
{
	FW_MDIFrameWnd* pMDIFrameWnd = dynamic_cast<FW_MDIFrameWnd*>(FW_WinApp::GetWinApp()->GetMainWnd());
	ASSERT(pMDIFrameWnd);
	return pMDIFrameWnd;
}

// static 
FW_Document* FW_MDIFrameWnd::GetActiveDoc()
{
	CMDIChildWnd* pMDIChildWnd = GetMDIFrameWnd()->MDIGetActive();
	if(pMDIChildWnd)
		return dynamic_cast<FW_Document*>(pMDIChildWnd->GetActiveDocument());
	return NULL;
}

// Get active view
// static 
FW_View* FW_MDIFrameWnd::GetActiveView()
{
	FW_MDIFrameWnd* pMDIFrameWnd = GetMDIFrameWnd();
	CFrameWnd* pFrameWnd = pMDIFrameWnd->GetActiveFrame();
	if(!pFrameWnd->IsKindOf(RUNTIME_CLASS(FW_MDIChildWnd)))
		return NULL;

	FW_MDIChildWnd* pMDIChildWnd = (FW_MDIChildWnd*) pFrameWnd;
	CView* pView = pMDIChildWnd->GetActiveView();
	if(!pView->IsKindOf(RUNTIME_CLASS(FW_View)))
		return NULL;

	return dynamic_cast<FW_View*>(pView);
}

// Update the active view
void FW_MDIFrameWnd::UpdateActiveView()
{
	FW_View* pView = GetActiveView();
	if(pView)
		pView->RedrawWindow();
}

// Get the panel bar
FW_PanelBar* FW_MDIFrameWnd::GetPanelBar()
{
	return &m_wndPanelBar;
}

// Set status bar's text
void FW_MDIFrameWnd::SetStatus(int iIndex, LPCTSTR lpszNewText)
{
	m_wndStatusBar.SetPaneText(iIndex, lpszNewText);
}

// Get status bar's text
CString FW_MDIFrameWnd::GetStatus(int iIndex) const
{
	return m_wndStatusBar.GetPaneText(iIndex);
}

static UINT indicators[] =
{
		ID_SEPARATOR,           // Status
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
};

int FW_MDIFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create status bar
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		return -1; 
	}

	// Create tool bar
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		return -1;
	}
	else
	{
		m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
			CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
		m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	}

	// Create command control bar 
	if(!m_wndPanelBar.Create(_T("Commands"), this, CSize(80, 80), TRUE, 123 + 1))
	{
		return -1;
	}
	else
	{
		m_wndPanelBar.SetBarStyle(m_wndPanelBar.GetBarStyle() |
			CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
		m_wndPanelBar.EnableDocking(CBRS_ALIGN_ANY);
	}

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndPanelBar, AFX_IDW_DOCKBAR_LEFT);

	m_wndPanelBar.LoadState(_T("BarState1"));
	LoadBarState(_T("BarState1"));

	return 0;
}

void FW_MDIFrameWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	FW_WinApp* pApp = FW_WinApp::GetWinApp();
	pApp->ApcHost.WmActivate(nState);
}

void FW_MDIFrameWnd::OnClose() 
{	
	// Prompt the user to save changes
	FW_WinApp* pApp = FW_WinApp::GetWinApp();
	if(pApp->ApcHost)
	{
		VARIANT_BOOL bCanTerminate;
		pApp->ApcHost->APC_RAW(CanTerminate)(&bCanTerminate);
		if (bCanTerminate == VARIANT_FALSE)
			return;
	}

	BOOL bTerminated;
	pApp->ApcHost.WmClose(bTerminated);
	if(!bTerminated)
		return;

	// We are closing the main frame.
	pApp->SetCloseFrame(TRUE);

	// Close all documents
	pApp->CloseAllDocuments(FALSE);

	// Clear documents 
	// pApp->ClearCollection();

	for(std::vector<FW_ToolBar*>::const_iterator it = m_vToolBar.begin();	it != m_vToolBar.end(); ++it)
		delete (*it);

	CMDIFrameWnd::OnClose();
}

void FW_MDIFrameWnd::OnEnable(BOOL bEnable) 
{
	CMDIFrameWnd::OnEnable(bEnable);

	FW_WinApp* pApp = FW_WinApp::GetWinApp();
	pApp->ApcHost.WmEnable(bEnable);
}

BOOL FW_MDIFrameWnd::OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult)
{
	FW_ToolBar* pToolBar = NULL;
	for(std::vector<FW_ToolBar*>::const_iterator it = m_vToolBar.begin();	it != m_vToolBar.end(); ++it)
	{
		if( (*it)->HasCmd(UINT(pNMHDR->idFrom)) )
		{
			pToolBar = *it;
			break;
		}
	}

	if(!pToolBar)
		return TRUE;

	// Get tool tip
	CString strToolTip = pToolBar->GetToolTip(UINT(pNMHDR->idFrom));
	if(strToolTip.IsEmpty())
		return TRUE;

	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXT*  pTTT  = (TOOLTIPTEXT*)pNMHDR;
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	pTTT->hinst = NULL;
#define _countof(array) (sizeof(array)/sizeof(array[0]))
	ZeroMemory(pTTT->szText,_countof(pTTT->szText));

#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strToolTip, _countof(pTTTA->szText));
	else
		_mbstowcsz(pTTTW->szText, strToolTip, _countof(pTTTW->szText));
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strToolTip, _countof(pTTTA->szText));
	else
		lstrcpyn(pTTTW->szText, strToolTip, _countof(pTTTW->szText));
#endif

	*pResult = 0;

	return TRUE;
}

// Add a new toolbar according to pUICmdBar
void FW_MDIFrameWnd::AddToolBar(FW_UICmdBar* pUICmdBar)
{
	FW_ToolBar* pToolBar = NULL;
	for(std::vector<FW_ToolBar*>::const_iterator it = m_vToolBar.begin();	it != m_vToolBar.end(); ++it)
	{
		if((*it)->GetActive() == pUICmdBar)
		{
			pToolBar = *it;
			break;
		}
	}

	if(pToolBar)
		pToolBar->ShowWindow(SW_SHOW);
	else
	{
		pToolBar = new FW_ToolBar(this);
		pToolBar->SetBarStyle(pToolBar->GetBarStyle() |
			CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
		pToolBar->EnableDocking(CBRS_ALIGN_ANY);
		pToolBar->Activate(pUICmdBar);
		DockControlBar(pToolBar);

		m_vToolBar.push_back(pToolBar);
	}
}

