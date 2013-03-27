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
#include "fw_cmdmanager.h"
#include "fw_cmd.h"
#include "fw_cmds.h"
#include "fw_mdiframewnd.h"

FW_CmdManager::FW_CmdManager(FW_WinApp* pApp)
:m_pApp(pApp),
m_pCmds(NULL)
{
}

FW_CmdManager::~FW_CmdManager(void)
{
	if(m_pCmds)
	{
		delete m_pCmds;
		m_pCmds = NULL;
	}
}

// Get m_spIFWCmdManager
CComPtr<IFWCmdManager> FW_CmdManager::GetInterface()
{
	if(!m_spIFWCmdManager)
	{
		HRESULT hr = m_spIFWCmdManager.CoCreateInstance(CLSID_FWCmdManager,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
	}

	return m_spIFWCmdManager;
}

// Set m_spIFWCmdManager to NULL
void FW_CmdManager::ResetInterface()
{
	if(m_spIFWCmdManager)
		m_spIFWCmdManager.p = NULL;
}


FW_Cmds* FW_CmdManager::GetCmds(void)
{
	if(!m_pCmds)
		m_pCmds = new FW_Cmds(this);
	return m_pCmds;
}

// Execute command
BOOL FW_CmdManager::Execute(FW_Cmd* pCmd)
{
	FW_MDIFrameWnd::GetMDIFrameWnd()->SendMessage(WM_COMMAND, MAKEWPARAM(pCmd->GetCmdId(), 0), 0);
	return TRUE;
}

// Terminate command
BOOL FW_CmdManager::Terminate(FW_Cmd* pCmd)
{
	pCmd->OnTerminate();
	return TRUE;	
}