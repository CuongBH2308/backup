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

interface IFWMouseEvents;
class FW_EventManager;
class XCAD_EXPORT FW_MouseEvents
{
public:
	FW_MouseEvents(FW_EventManager* pEventManager);
	virtual ~FW_MouseEvents(void);

	// Get m_spIFWMouseEvents;
	CComPtr<IFWMouseEvents> GetInterface();

	// Set m_spIFWMouseEvents to NULL
	void ResetInterface();

	// Mouse Move 
	void OnMove(HWND hView, UINT nFlags, const CPoint& point);

private:
	CComPtr<IFWMouseEvents> m_spIFWMouseEvents;
	FW_EventManager* m_pEventManager;
};
