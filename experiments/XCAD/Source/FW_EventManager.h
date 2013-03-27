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
#include "xcad.h"

interface IFWEventManager;
class FW_MouseEvents;
class FW_WinApp;
class XCAD_EXPORT FW_EventManager
{
public:
	FW_EventManager(FW_WinApp* pApp);
	virtual ~FW_EventManager(void);

	// Get m_spIFWEventManager
	CComPtr<IFWEventManager> GetInterface();

	// Set m_spIFWEventManager to NULL
	void ResetInterface();

	// Get/Create mouse events
	FW_MouseEvents* GetMouseEvents(void);

private:
	CComPtr<IFWEventManager> m_spIFWEventManager;
	FW_WinApp* m_pApp;
	FW_MouseEvents* m_pMouseEvents;
};
