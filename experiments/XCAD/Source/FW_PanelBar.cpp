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
#include "fw_panelbar.h"
#include "fw_toolbarcontainer.h"

IMPLEMENT_DYNAMIC(FW_PanelBar, FW_ControlBar)

FW_PanelBar::FW_PanelBar(void)
:m_pToolBarContainer(NULL)
{
}

FW_PanelBar::~FW_PanelBar(void)
{
	if(m_pToolBarContainer)
	{
		delete m_pToolBarContainer;
		m_pToolBarContainer = NULL;
	}
}

BEGIN_MESSAGE_MAP(FW_PanelBar, FW_ControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int FW_PanelBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (FW_ControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_pToolBarContainer)
		m_pToolBarContainer = new FW_ToolBarContainer(this);

	return 0;
}

void FW_PanelBar::OnSize(UINT nType, int cx, int cy) 
{
	FW_ControlBar::OnSize(nType, cx, cy);

	if(m_pToolBarContainer)
	{
		CRect rc;
		GetClientRect(rc);
		m_pToolBarContainer->MoveWindow(rc);
		m_pToolBarContainer->Invalidate();
	}
}

// Show pUICmdBar
bool FW_PanelBar::Activate(FW_UICmdBar* pUICmdBar)
{
	if(!m_pToolBarContainer)
		return false;
	return m_pToolBarContainer->Activate(pUICmdBar);
}

// Add a new command menu item
// Then the user can select a UICmdBar to activate it
void FW_PanelBar::AddCmdBar2Menu(FW_UICmdBar* pUICmdBar)
{
	if(m_pToolBarContainer)
		m_pToolBarContainer->AddCmdBar2Menu(pUICmdBar);
}