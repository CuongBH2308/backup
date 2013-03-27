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
#include "fw_mdichildwnd.h"
#include "fw_cmdmanager.h"
#include "fw_cmds.h"
#include "fw_document.h"
#include "fw_winapp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(FW_MDIChildWnd, CMDIChildWnd)

FW_MDIChildWnd::FW_MDIChildWnd()
{
}

FW_MDIChildWnd::~FW_MDIChildWnd()
{
}

BEGIN_MESSAGE_MAP(FW_MDIChildWnd, CMDIChildWnd)
END_MESSAGE_MAP()

// virtual
BOOL FW_MDIChildWnd::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	if(CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}