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
#include "fweventmanager.h"
#include "fwmouseevents.h"
#include "..\fw_eventmanager.h"
#include "..\fw_mouseevents.h"
#include "..\fw_winapp.h"

CFWEventManager::CFWEventManager()
:m_pEventManager(NULL)
{
}

HRESULT CFWEventManager::FinalConstruct()
{
	m_pEventManager = FW_WinApp::GetWinApp()->GetEventManager();
	return S_OK;
}

void CFWEventManager::FinalRelease() 
{
	if(m_pEventManager)
		m_pEventManager->ResetInterface();
}

STDMETHODIMP CFWEventManager::get_MouseEvents(IFWMouseEvents* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;
	*ppVal = NULL;
	FW_MouseEvents* pMouseEvents = m_pEventManager->GetMouseEvents();
	if(!pMouseEvents)
		return E_FAIL;
	
	*ppVal = pMouseEvents->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}
