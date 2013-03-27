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
#include "afxwin.h"

class FW_DropDownWnd;
class FW_PanelContainer : public CWnd
{
	DECLARE_DYNAMIC(FW_PanelContainer)

public:
	FW_PanelContainer(void);
	virtual ~FW_PanelContainer(void);

	// Get pane rect
	void GetPaneRect( LPRECT lpRect ) const;

	// Drop down to show the menu
	void DropDown(CPoint& point);

	// Set the display name of the drop down window
	void SetDisplayName(const CString& strDisplayName) const;

protected:
	// Get the menu that need to be shown
	virtual bool GetMenu(CMenu& menu);
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnSize( UINT nType, int cx, int cy );

private:
	FW_DropDownWnd* m_pDropDownWnd;
	CRect m_rcPane;

	DECLARE_MESSAGE_MAP()
};
