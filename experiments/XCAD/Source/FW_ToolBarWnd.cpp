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
#include "fw_toolbarwnd.h"
#include "fw_toolbar.h"
#include "resource.h"

#define SCROLL_DELTA	22

FW_ToolBarWnd::FW_ToolBarWnd(CWnd* pParent) 
:m_strToolBar(),
m_pToolBar(NULL),
m_yMinScroll(0),
m_yCurrentScroll(0),
m_yMaxScroll(0),
m_bRecalcing(false)
{
	CString str = AfxRegisterWndClass(CS_DBLCLKS);

	CreateEx(0, str, _T("FW_ToolBarWnd"), 
		WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, pParent->m_hWnd, NULL);
}

FW_ToolBarWnd::~FW_ToolBarWnd(void)
{
	if(m_pToolBar)
	{
		delete m_pToolBar;
		m_pToolBar = NULL;
	}
}

BEGIN_MESSAGE_MAP(FW_ToolBarWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_VSCROLL()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

BOOL FW_ToolBarWnd::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message == WM_RBUTTONDOWN)
	{
		CWnd* pParent = GetParent();
		if(pParent)
			pParent->PostMessage(WM_RBUTTONDOWN, pMsg->wParam,pMsg->lParam);

		return TRUE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

int FW_ToolBarWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_pToolBar)
	{
		m_pToolBar = new FW_ToolBar(this);
		//m_pToolBar->LoadToolBar(IDR_MAINFRAME);
		m_pToolBar->SetBarStyle(m_pToolBar->GetBarStyle() |
			CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	}

	return 0;
}

void FW_ToolBarWnd::SetToolBar( const CString& strToolBar )
{
	m_strToolBar = strToolBar;

	if(m_pToolBar)
	{
		//m_pToolBar->ApplyToolBarProperties(strToolBar);
		m_pToolBar->ShowWindow(!strToolBar.IsEmpty() ? SW_SHOW : SW_HIDE);
	}

	Invalidate();
}

void FW_ToolBarWnd::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	dc.FillSolidRect(rect, GetSysColor(COLOR_BTNFACE));
	if(m_pToolBar)
		m_pToolBar->Invalidate();
}

void FW_ToolBarWnd::RecalcLayout()
{
	// Ensure not enter when handling
	if (m_bRecalcing)
		return;
	m_bRecalcing = true;

	CRect rect;
	GetClientRect(&rect);

	//if(FWxToolBarManager::Get()->LearningMode())
	//	m_pToolBar->AutoAdjustRows(0);
	//else
	//	m_pToolBar->AutoAdjustRows(rect.Width());

	if(rect.Width()>0)
		m_pToolBar->AdjustRows(rect.Width());

	// Calculate the dimensions of a dynamic toolbar
	CSize vert = m_pToolBar->CalcDynamicLayout(-1, LM_HORZ);

	// Calculate the height of the toolbar in the toolbar-window.
	int iHeight = ((rect.Height() > vert.cy) ? rect.Height() : vert.cy);

	// Determine whether the toolbar-window need VSCROLL
	OnToolBarConfigurationChange(); // possible configuration change

	// Show the toolbar in the VSCROLLed toolbar-window
	m_pToolBar->SetWindowPos(NULL,0,-GetCurrentScroll(),rect.Width(),iHeight,SWP_NOZORDER);

	// The client area is marked for painting when the next WM_PAINT message occurs
	m_pToolBar->Invalidate();

	// Finish handling. Ensure this function can be entered again
	m_bRecalcing = false;
}

void FW_ToolBarWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	// Recalcualte the layout of the toolbar in the toolbar-window
	// Determine whether the toolbar-window need VSCROLL
	// Show the toolbar in the VSCROLLed toolbar-window
	RecalcLayout();
}

// If the height of the toolbar is larger than that of the toolbar-window,
// Then we need VSCROLL
bool FW_ToolBarWnd::ToolBarNeedsScrolling()
{
	ASSERT_VALID(m_pToolBar);
	CSize szVert = m_pToolBar->CalcDynamicLayout(-1, LM_HORZ); 
	CRect rect;
	GetClientRect(&rect);

	if((szVert.cy - 15) > rect.Height())
		return true;

	return false;
}

void FW_ToolBarWnd::OnToolBarConfigurationChange()
{
	// If the height of the toolbar is larger than that of the toolbar-window,
	// Then we need VSCROLL
	if(ToolBarNeedsScrolling())
	{
		if(!(GetStyle() & WS_VSCROLL)) 
		{
			ModifyStyle(0,WS_VSCROLL,SWP_FRAMECHANGED);
			Invalidate();
		}
	}
	else if(GetStyle() & WS_VSCROLL)
	{
		ModifyStyle(WS_VSCROLL, 0, SWP_FRAMECHANGED);
		SetCurrentScroll(0); // It must be 0
		Invalidate();
	}

	if(GetStyle() & WS_VSCROLL)
	{
		CSize vert = m_pToolBar->CalcDynamicLayout(-1, LM_HORZ);

		CRect rect;
		GetClientRect(&rect);

		SCROLLINFO si;

		SetMaxScroll(max(vert.cy, 0)); 
		SetCurrentScroll(min(GetCurrentScroll(), GetMaxScroll())); 
		si.cbSize = sizeof(si); 
		si.fMask  = SIF_ALL;//SIF_RANGE | SIF_PAGE | SIF_POS; 
		si.nMin   = GetMinScroll();         
		si.nMax   = GetMaxScroll(); 
		si.nPage  = rect.Height();         
		si.nPos   = GetCurrentScroll(); 
		si.nTrackPos = 0;
		SetScrollInfo(SB_VERT, &si, TRUE); 
	}
}

BOOL FW_ToolBarWnd::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	if(m_pToolBar->m_hWnd)
	{
		if(m_pToolBar->OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
			return TRUE;
	}

	return CWnd::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}

void FW_ToolBarWnd::LearningModeChange()
{
	ASSERT_VALID(m_pToolBar);

	// Refresh the toolbar
	ReconstructToolBar();
}

const CString& FW_ToolBarWnd::GetToolBar() const
{ 
	return m_strToolBar;
}

void FW_ToolBarWnd::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	int yNewPos;

	CRect rect;
	GetClientRect(rect);
	int nScrollPage = rect.Height();

	switch (nSBCode)
	{
	case SB_PAGEUP:
		yNewPos = GetCurrentScroll() - nScrollPage;
		break;
		// User clicked the shaft below the scroll box.
	case SB_PAGEDOWN:
		yNewPos = GetCurrentScroll() + nScrollPage;
		break;              // User clicked the top arrow.
	case SB_LINEUP:
		yNewPos = GetCurrentScroll() - SCROLL_DELTA;
		break;              // User clicked the bottom arrow.
	case SB_LINEDOWN:
		yNewPos = GetCurrentScroll() + SCROLL_DELTA;
		break;              // User dragged the scroll box.
	case SB_THUMBTRACK:
		yNewPos = nPos;
		break;
	case SB_TOP:
		yNewPos = GetMinScroll();
		break;
	case SB_BOTTOM:
		yNewPos = GetMaxScroll() - nScrollPage;
		break;
	default:
		yNewPos = GetCurrentScroll();
	}


	yNewPos = max(0, yNewPos);
	yNewPos = min(GetMaxScroll() - nScrollPage, yNewPos);
	// If the current position does not change, do not scroll.
	if (yNewPos == GetCurrentScroll())
		goto exitFunc;

	// Reset the current scroll position.  
	SetCurrentScroll(yNewPos);  

	m_pToolBar->SetWindowPos(NULL,0,-yNewPos,0,0,SWP_NOSIZE|SWP_NOZORDER);
	m_pToolBar->UpdateWindow();

	SCROLLINFO si;

	GetScrollInfo(SB_VERT,&si);

	// Reset the scroll bar.          
	si.cbSize = sizeof(si); 
	//si.fMask  = SIF_POS;
	si.nPos   = GetCurrentScroll(); 
	SetScrollInfo(SB_VERT, &si, TRUE); 

exitFunc:
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void FW_ToolBarWnd::ResetScrollingInfo()
{
	m_yMinScroll = 0;
	m_yCurrentScroll = 0;
	m_yMaxScroll = 0;
}

void FW_ToolBarWnd::SetCurrentScroll(int val)
{
	m_yCurrentScroll = val;
}

void FW_ToolBarWnd::SetMaxScroll(int val)
{
	m_yMaxScroll = val;
}

void FW_ToolBarWnd::SetMinScroll(int val)
{
	m_yMinScroll = val;
}

int FW_ToolBarWnd::GetCurrentScroll()
{
	return m_yCurrentScroll;
}

int FW_ToolBarWnd::GetMaxScroll()
{
	return m_yMaxScroll;
}

int FW_ToolBarWnd::GetMinScroll()
{
	return m_yMinScroll;
}

void FW_ToolBarWnd::ReconstructToolBar()
{
	//FWxToolBarManager* pMgr = FWxToolBarManager::Get();
	//FWxCommandList* pList = pMgr->GetCommandList(m_pToolBar);
	//if (m_pToolBar && pList)
	//	m_pToolBar->Apply(pList);
}

// Show pUICmdBar
bool FW_ToolBarWnd::Activate(FW_UICmdBar* pUICmdBar)
{
	if(!m_pToolBar)
		return false;

	EnableToolTips();
	return m_pToolBar->Activate(pUICmdBar);
}

BOOL FW_ToolBarWnd::OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult)
{
	if(!m_pToolBar)
		return TRUE;

	// Get tooltip
	CString strToolTip = m_pToolBar->GetToolTip(UINT(pNMHDR->idFrom));
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
