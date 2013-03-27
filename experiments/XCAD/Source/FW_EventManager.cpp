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
#include "fw_eventmanager.h"
#include "fw_mouseevents.h"

FW_EventManager::FW_EventManager(FW_WinApp* pApp)
:m_pApp(pApp),
m_pMouseEvents(NULL)
{
}

FW_EventManager::~FW_EventManager(void)
{
	if(m_pMouseEvents)
	{
		delete m_pMouseEvents;
		m_pMouseEvents = NULL;
	}
}

// Get m_spIFWEventManager
CComPtr<IFWEventManager> FW_EventManager::GetInterface()
{
	if(!m_spIFWEventManager)
	{
		HRESULT hr = m_spIFWEventManager.CoCreateInstance(CLSID_FWEventManager,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
	}

	return m_spIFWEventManager;
}

// Set m_spIFWEventManager to NULL
void FW_EventManager::ResetInterface()
{
	if(m_spIFWEventManager)
		m_spIFWEventManager.p = NULL;
}

// Get/Create mouse events
FW_MouseEvents* FW_EventManager::GetMouseEvents(void)
{
	if(!m_pMouseEvents)
		m_pMouseEvents = new FW_MouseEvents(this);
	return m_pMouseEvents;
}
