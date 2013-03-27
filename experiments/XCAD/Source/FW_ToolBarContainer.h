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


#pragma once
#include "fw_panelcontainer.h"
#include <map>

class FW_ToolBarWnd;
class FW_UICmdBar;
class FW_ToolBarContainer : public FW_PanelContainer
{
	DECLARE_DYNAMIC(FW_ToolBarContainer)

public:
	FW_ToolBarContainer(CWnd* pParent);
	virtual ~FW_ToolBarContainer(void);

	// Show pUICmdBar
	bool			Activate(FW_UICmdBar* pUICmdBar);

	// Add a new command menu item
	// Then the user can select a UICmdBar to activate it
	void			AddCmdBar2Menu(FW_UICmdBar* pUICmdBar);

	// Dispatch the messages 
	virtual BOOL	OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );

protected:
	// Show the menu that lists the FW_UICmdBar(s) that can be activated
	virtual bool	GetMenu(CMenu& menu);

	// Create FW_ToolBarWnd
	afx_msg int		OnCreate( LPCREATESTRUCT lpCreateStruct );

	// When the size of the container changed, we should adjust the layout
	afx_msg void	OnSize( UINT nType, int cx, int cy );

private:
	// Window to store FW_ToolBar
	FW_ToolBarWnd*	m_pToolBarWnd;

	// _Kty: the command id. 
	//		 Once it is clicked, then the corresponding UICmdBar will be activated
	// _Ty: the pointer of FW_UICmdBar
	std::map<UINT, FW_UICmdBar*> m_mUICmdBar;

	DECLARE_MESSAGE_MAP()
};
