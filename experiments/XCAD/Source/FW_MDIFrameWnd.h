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

#include <vector>
#include "fw_controlbar.h"
#include "fw_panelbar.h"
#include "fw_statusbar.h"
#include "fw_toolbar.h"

class FW_Document;
class FW_View;
class FW_MDIFrameWnd : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(FW_MDIFrameWnd)

public:
	FW_MDIFrameWnd();
	virtual ~FW_MDIFrameWnd();

	// Get main frame
	static FW_MDIFrameWnd*	GetMDIFrameWnd();

	// Get active document
	static FW_Document*		GetActiveDoc();

	// Get active view
	static FW_View*			GetActiveView();

	// Update the active view
	static void				UpdateActiveView();

	// Get the panel bar
	FW_PanelBar*			GetPanelBar();

	// Add a new toolbar according to pUICmdBar
	void					AddToolBar(FW_UICmdBar* pUICmdBar);

	// Set status bar's text
	void					SetStatus(int iIndex, LPCTSTR lpszNewText);

	// Get status bar's text
	CString					GetStatus(int iIndex) const;

protected:  
	FW_StatusBar	m_wndStatusBar;
	FW_ToolBar		m_wndToolBar;
	FW_PanelBar		m_wndPanelBar;
	FW_ControlBar	m_wndControlBarBrowser;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void	OnClose();
	afx_msg void	OnEnable(BOOL bEnabled);
	afx_msg BOOL	OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);

private:
	std::vector<FW_ToolBar*>	m_vToolBar;
};


