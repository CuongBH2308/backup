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
#include "fw_uicmdbarctrl.h"

FW_UICmdBarCtrl::FW_UICmdBarCtrl(FW_UICmdBarCtrls* pUICmdBarCtrls)
:m_pUICmdBarCtrls(pUICmdBarCtrls),
m_pCmd(NULL)
{
	GetInterface();
}

FW_UICmdBarCtrl::~FW_UICmdBarCtrl(void)
{
}

// Get IFWUICmdBarCtrl
CComPtr<IFWUICmdBarCtrl> FW_UICmdBarCtrl::GetInterface()
{
	if(!m_spIFWUICmdBarCtrl)
	{
		HRESULT hr = m_spIFWUICmdBarCtrl.CoCreateInstance(CLSID_FWUICmdBarCtrl,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
		if(SUCCEEDED(hr))
			m_spIFWUICmdBarCtrl->SetPrimary(reinterpret_cast<unsigned char*>(this));
	}

	return m_spIFWUICmdBarCtrl;
}

// Set m_spIFWUICmdBarCtrl to NULL
void FW_UICmdBarCtrl::ResetInterface()
{
	if(m_spIFWUICmdBarCtrl)
		m_spIFWUICmdBarCtrl.p = NULL;
}


void FW_UICmdBarCtrl::SetCmd(FW_Cmd* pCmd)
{
	m_pCmd = pCmd;
}

FW_Cmd* FW_UICmdBarCtrl::GetCmd() const
{
	return m_pCmd;
}