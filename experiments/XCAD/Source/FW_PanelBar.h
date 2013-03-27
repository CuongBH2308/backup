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
#include "fw_controlbar.h"

class FW_ToolBarContainer;
class FW_UICmdBar;
class FW_PanelBar :	public FW_ControlBar
{
	DECLARE_DYNAMIC(FW_PanelBar)

public:
	FW_PanelBar(void);
	virtual ~FW_PanelBar(void);

	// Show pUICmdBar
	bool Activate(FW_UICmdBar* pUICmdBar);

	// Add a new command menu item
	// Then the user can select a UICmdBar to activate it
	void AddCmdBar2Menu(FW_UICmdBar* pUICmdBar);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	FW_ToolBarContainer* m_pToolBarContainer;

	DECLARE_MESSAGE_MAP()
};
