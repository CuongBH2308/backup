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
#include "fw_mouseevents.h"

FW_MouseEvents::FW_MouseEvents(FW_EventManager* pEventManager)
:m_pEventManager(pEventManager),
m_spIFWMouseEvents(NULL)
{
}

FW_MouseEvents::~FW_MouseEvents(void)
{
}

// Get m_spIFWMouseEvents;
CComPtr<IFWMouseEvents> FW_MouseEvents::GetInterface()
{
	if(!m_spIFWMouseEvents)
	{
		HRESULT hr = m_spIFWMouseEvents.CoCreateInstance(CLSID_FWMouseEvents,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
	}

	return m_spIFWMouseEvents;
}

// Set m_spIFWMouseEvents to NULL
void FW_MouseEvents::ResetInterface()
{
	if(m_spIFWMouseEvents)
		m_spIFWMouseEvents.p = NULL;
}

// Mouse Move 
void FW_MouseEvents::OnMove(HWND hView, UINT nFlags, const CPoint& point)
{
	GetInterface();
	if(m_spIFWMouseEvents)
		m_spIFWMouseEvents->Move((LONGLONG)hView,nFlags,point.x,point.y);
}

