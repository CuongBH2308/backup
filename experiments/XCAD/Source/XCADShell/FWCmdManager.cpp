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
#include "fwcmdmanager.h"
#include "..\fw_winapp.h"
#include "..\fw_cmdmanager.h"
#include "..\fw_cmds.h"

CFWCmdManager::CFWCmdManager()
:m_pCmdManager(NULL)
{	
}

HRESULT CFWCmdManager::FinalConstruct()
{
	m_pCmdManager = FW_WinApp::GetWinApp()->GetCmdManager();
	return S_OK;
}

void CFWCmdManager::FinalRelease() 
{
	if(m_pCmdManager)
		m_pCmdManager->ResetInterface();
}

STDMETHODIMP CFWCmdManager::get_Cmds(IFWCmds* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	FW_Cmds* pCmds = m_pCmdManager->GetCmds();
	if(!pCmds)
		return E_OUTOFMEMORY;
	
	*ppVal = pCmds->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}
