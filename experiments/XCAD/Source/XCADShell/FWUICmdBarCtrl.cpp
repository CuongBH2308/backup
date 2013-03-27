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
#include "fwuicmdbarctrl.h"
#include "..\fw_uicmdbarctrl.h"

CFWUICmdBarCtrl::CFWUICmdBarCtrl()
:m_pUICmdBarCtrl(NULL)
{
}

HRESULT CFWUICmdBarCtrl::FinalConstruct()
{
	return S_OK;
}

void CFWUICmdBarCtrl::FinalRelease() 
{
	if(m_pUICmdBarCtrl)
		m_pUICmdBarCtrl->ResetInterface();
}

STDMETHODIMP CFWUICmdBarCtrl::SetPrimary(unsigned char* pVal)
{
	m_pUICmdBarCtrl = reinterpret_cast<FW_UICmdBarCtrl*>(pVal);
	return S_OK;
}
