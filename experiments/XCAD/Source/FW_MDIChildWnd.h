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

class FW_MDIChildWnd : public CMDIChildWnd
{
	DECLARE_DYNCREATE(FW_MDIChildWnd)
public:
	FW_MDIChildWnd();
	virtual ~FW_MDIChildWnd();

	// Message handler
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
