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
#include "fwmouseevents.h"
#include ".\fwmouseevents.h"

STDMETHODIMP CFWMouseEvents::Move(LONGLONG hWnd, LONG lFlag, LONG x, LONG y)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return Fire_OnMove((HWND)hWnd, lFlag, CPoint(x,y));
}