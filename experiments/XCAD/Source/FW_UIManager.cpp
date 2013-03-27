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
#include "fw_uimanager.h"
#include "fw_uicmdbars.h"

FW_UIManager::FW_UIManager(FW_WinApp* pApp)
:m_pApp(pApp),
m_pUICmdBars(NULL)
{
}

FW_UIManager::~FW_UIManager(void)
{
	if(m_pUICmdBars)
	{
		delete m_pUICmdBars;
		m_pUICmdBars = NULL;
	}
}

// Get m_spIFWUIManager;
CComPtr<IFWUIManager> FW_UIManager::GetInterface()
{
	if(!m_spIFWUIManager)
	{
		HRESULT hr = m_spIFWUIManager.CoCreateInstance(CLSID_FWUIManager,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
	}

	return m_spIFWUIManager;
}

// Set m_spIFWUIManager to NULL
void FW_UIManager::ResetInterface()
{
	if(m_spIFWUIManager)
		m_spIFWUIManager.p = NULL;
}

FW_UICmdBars* FW_UIManager::GetUICmdBars()
{
	if(!m_pUICmdBars)
		m_pUICmdBars = new FW_UICmdBars(this);
	return m_pUICmdBars;
}

// Add a command bar according to the type
FW_UICmdBar* FW_UIManager::Add(const CString& strDisplayName,
							   const CString& strInternalName)
{
	return GetUICmdBars()->Add(strDisplayName,strInternalName);
}