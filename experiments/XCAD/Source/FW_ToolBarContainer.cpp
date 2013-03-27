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
#include "fw_toolbarcontainer.h"
#include "fw_toolbarwnd.h"
#include "fw_uicmdbar.h"

IMPLEMENT_DYNAMIC(FW_ToolBarContainer, FW_PanelContainer)

FW_ToolBarContainer::FW_ToolBarContainer(CWnd* pParent)
:m_pToolBarWnd(NULL)
{
	// If you call AfxRegisterWndClass multiple times with identical parameters, 
	// it only registers a class on the first call. 
	// Subsequent calls to AfxRegisterWndClass with identical parameters 
	// simply return the already-registered classname.
	// Sets the mouse style to CS_DBLCLKS, which sends double-click messages to the window procedure 
	// when the user double-clicks the mouse. 
	CString str = AfxRegisterWndClass(CS_DBLCLKS);

	CreateEx(0,str, _T("FW_ToolBarContainer"),
		WS_VISIBLE | WS_CHILD, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, pParent->m_hWnd, NULL);

	CRect rect(0,0,250,100);
	
	// This method computes the required size of the window rectangle, 
	// based on the desired client-rectangle size
	CalcWindowRect(&rect);

	SetWindowPos(NULL,200,400,rect.Width(),rect.Height(),
		SWP_NOZORDER);
}

FW_ToolBarContainer::~FW_ToolBarContainer(void)
{
	if(m_pToolBarWnd)
	{
		delete m_pToolBarWnd;
		m_pToolBarWnd = NULL;
	}
}

BEGIN_MESSAGE_MAP(FW_ToolBarContainer, FW_PanelContainer)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL FW_ToolBarContainer::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	if(m_pToolBarWnd)
	{
		if(m_pToolBarWnd->OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
			return TRUE;
	}

	switch(nCode)
	{
	case CN_COMMAND:
		{
			// pHandlerInfo!=NULL means it is checking whether the command should be enable,
			// otherwise the command is executed
			if(!pHandlerInfo)	
			{
				std::map<UINT, FW_UICmdBar*>::const_iterator it = m_mUICmdBar.find(nID);
				if(it != m_mUICmdBar.end())
					Activate(it->second);
			}
		}
		break;
	default:
		break;
	}
	return FW_PanelContainer::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}

// Add a new command menu item
// Then the user can select a UICmdBar to activate it
void FW_ToolBarContainer::AddCmdBar2Menu(FW_UICmdBar* pUICmdBar)
{
	static UINT nId = 0x6570;
	std::map<UINT, FW_UICmdBar*>::const_iterator it = m_mUICmdBar.begin();
	std::map<UINT, FW_UICmdBar*>::const_iterator itEnd = m_mUICmdBar.end();
	BOOL bFind = FALSE;
	for(; it != itEnd; ++it)
	{
		if(it->second == pUICmdBar)
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
		m_mUICmdBar[nId++] = pUICmdBar;
}

//virtual 
bool FW_ToolBarContainer::GetMenu(CMenu& menu)
{
	std::map<UINT, FW_UICmdBar*>::const_iterator it = m_mUICmdBar.begin();
	std::map<UINT, FW_UICmdBar*>::const_iterator itEnd = m_mUICmdBar.end();
	for(; it != itEnd; ++it)
		menu.AppendMenu(MF_STRING, it->first, it->second->GetDisplayName());

	return true;
}

int FW_ToolBarContainer::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	int ret = FW_PanelContainer::OnCreate(lpCreateStruct);
	if(!m_pToolBarWnd)
		m_pToolBarWnd = new FW_ToolBarWnd(this);
	return ret;
}

void FW_ToolBarContainer::OnSize(UINT nType, int cx, int cy) 
{
	FW_PanelContainer::OnSize(nType, cx, cy);

	if(m_pToolBarWnd)
	{
		CRect rcPane;
		GetPaneRect(rcPane);
		m_pToolBarWnd->MoveWindow(rcPane);
		m_pToolBarWnd->Invalidate();
	}
}

// Show pUICmdBar
bool FW_ToolBarContainer::Activate(FW_UICmdBar* pUICmdBar)
{
	if(!m_pToolBarWnd || !pUICmdBar)
		return false;

	// Get the display name of the command bar
	CString strDisplayName = pUICmdBar->GetDisplayName();

	// Set the display name
	SetDisplayName(strDisplayName);

	return m_pToolBarWnd->Activate(pUICmdBar);
}