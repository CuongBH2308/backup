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
#include "fw_panelcontainer.h"
#include "fw_dropdownwnd.h"

IMPLEMENT_DYNAMIC(FW_PanelContainer, CWnd)

FW_PanelContainer::FW_PanelContainer(void)
:m_pDropDownWnd(NULL)
{
}

FW_PanelContainer::~FW_PanelContainer(void)
{
	if(m_pDropDownWnd)
	{
		delete m_pDropDownWnd;
		m_pDropDownWnd = NULL;
	}
}

BEGIN_MESSAGE_MAP(FW_PanelContainer, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int FW_PanelContainer::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
	int ret = CWnd::OnCreate(lpCreateStruct);
	if(!m_pDropDownWnd)
		m_pDropDownWnd = new FW_DropDownWnd(this);
	return ret;
}

void FW_PanelContainer::OnSize( UINT nType, int cx, int cy ) 
{
	CWnd::OnSize(nType, cx, cy);

	int iDropHeight = 0;
	if(m_pDropDownWnd)
	{
		int cyMenu = GetSystemMetrics(SM_CYICON) - 12;

		if( cyMenu < cy)
			iDropHeight = cyMenu;

		m_pDropDownWnd->MoveWindow(0, 0, cx, iDropHeight);
		m_pDropDownWnd->Invalidate();
	}

	m_rcPane.SetRect(0, iDropHeight, cx, cy);
}

void FW_PanelContainer::GetPaneRect( LPRECT lpRect ) const
{
	*lpRect = m_rcPane;
}


// Get the menu that need to be shown
// virtual 
bool FW_PanelContainer::GetMenu(CMenu& menu)
{
	return false;
}

void FW_PanelContainer::DropDown(CPoint& point)
{
	CMenu menu;
	menu.CreatePopupMenu();

	if(!GetMenu(menu))
		return;

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
}

// Set the display name of the drop down window
void FW_PanelContainer::SetDisplayName(const CString& strDisplayName) const
{
	if(m_pDropDownWnd)
	{
		m_pDropDownWnd->SetWindowText(strDisplayName);
		m_pDropDownWnd->RedrawWindow();
	}
}
