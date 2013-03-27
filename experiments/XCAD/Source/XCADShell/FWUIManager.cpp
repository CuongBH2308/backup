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
#include "fwuimanager.h"
#include "fwuicmdbars.h"
#include "..\fw_uicmdbars.h"
#include "..\fw_uimanager.h"
#include "..\fw_winapp.h"

CFWUIManager::CFWUIManager()
:m_pUIManager(NULL)
{
}

HRESULT CFWUIManager::FinalConstruct()
{
	m_pUIManager = FW_WinApp::GetWinApp()->GetUIManager();
	return S_OK;
}

void CFWUIManager::FinalRelease() 
{
	if(m_pUIManager)
		m_pUIManager->ResetInterface();
}

STDMETHODIMP CFWUIManager::get_CmdBars(IFWUICmdBars* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	FW_UICmdBars* pUICmdBars = m_pUIManager->GetUICmdBars();
	if(!pUICmdBars)
		return E_OUTOFMEMORY;

	*ppVal = pUICmdBars->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}
