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
#include "fw_cmds.h"
#include "fw_cmd.h"

FW_Cmds::FW_Cmds(FW_CmdManager* pCmdManager)
:m_pCmdManager(pCmdManager)
{
}

FW_Cmds::~FW_Cmds(void)
{
	for(std::vector<FW_Cmd*>::iterator it=m_vCmd.begin(); it!=m_vCmd.end(); ++it)
		delete (*it);
	m_vCmd.clear();
}

// Get m_spIFWCmds;
CComPtr<IFWCmds> FW_Cmds::GetInterface()
{
	if(!m_spIFWCmds)
	{
		HRESULT hr = m_spIFWCmds.CoCreateInstance(CLSID_FWCmds,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
	}

	return m_spIFWCmds;
}

// Set m_spIFWCmds to NULL
void FW_Cmds::ResetInterface()
{
	if(m_spIFWCmds)
		m_spIFWCmds.p = NULL;
}

// Handle messages
// virtual 
BOOL FW_Cmds::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	for(std::vector<FW_Cmd*>::const_iterator it=m_vCmd.begin(); it!=m_vCmd.end(); ++it)
	{
		if((*it)->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;
	}
	return FALSE;
}


int FW_Cmds::GenerateCmdId() const
{
	static int iCmd = 3000;
	return iCmd++;
}

// Add a command
void FW_Cmds::Add(FW_Cmd* pCmd)
{
	m_vCmd.push_back(pCmd);
}

// Add a command
FW_Cmd* FW_Cmds::Add(UINT nDisplayName,
					 UINT nTooltip,
					 UINT nImages,
					 const CString& strInternalName,
					 const int& iCmdId)
{
	FW_Cmd* pCmd = new FW_Cmd(nDisplayName,nTooltip,nImages,
		strInternalName,iCmdId);
	return pCmd;
}

// Add a command
FW_Cmd* FW_Cmds::Add(const CString& strDisplayName,
					 const CString& strTooltip,
					 CImageList& imageList,
					 const CString& strInternalName,
					 const int& iCmdId)
{
	FW_Cmd* pCmd = new FW_Cmd(strDisplayName,strTooltip,imageList,
		strInternalName,iCmdId);
	return pCmd;
}

// Get the command upon the command id
FW_Cmd* FW_Cmds::GetCmd(int iCmdId) const
{
	for(std::vector<FW_Cmd*>::const_iterator it=m_vCmd.begin();it!=m_vCmd.end();++it)
	{
		if((*it)->GetCmdId() == iCmdId)
			return *it;
	}

	return NULL;
}

// Get the active command
FW_Cmd* FW_Cmds::GetActiveCmd() const
{
	for(std::vector<FW_Cmd*>::const_iterator it=m_vCmd.begin();it!=m_vCmd.end();++it)
	{
		if((*it)->GetActive())
			return *it;
	}

	return NULL;
}
