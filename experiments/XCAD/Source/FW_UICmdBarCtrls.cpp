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
#include "fw_uicmdbarctrls.h"
#include "fw_uicmdbarctrl.h"

FW_UICmdBarCtrls::FW_UICmdBarCtrls(FW_UICmdBar* pUICmdBar)
:m_pUICmdBar(pUICmdBar)
{
}

FW_UICmdBarCtrls::~FW_UICmdBarCtrls(void)
{
	for(std::vector<FW_UICmdBarCtrl*>::const_iterator it=m_vUICmdBarCtrl.begin();it!=m_vUICmdBarCtrl.end();it++)
		delete (*it);

	m_vUICmdBarCtrl.clear();
}

// 	Get m_spIFWUICmdBarCtrls;
CComPtr<IFWUICmdBarCtrls> FW_UICmdBarCtrls::GetInterface()
{
	if(!m_spIFWUICmdBarCtrls)
	{
		HRESULT hr = m_spIFWUICmdBarCtrls.CoCreateInstance(CLSID_FWUICmdBarCtrls,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));

		if(SUCCEEDED(hr))
			m_spIFWUICmdBarCtrls->SetPrimary(reinterpret_cast<unsigned char*>(this));
	}

	return m_spIFWUICmdBarCtrls;
}

// Set m_spIFWUICmdBarCtrls to NULL
void FW_UICmdBarCtrls::ResetInterface()
{
	if(m_spIFWUICmdBarCtrls)
		m_spIFWUICmdBarCtrls.p = NULL;
}

// Associate a FW_UICmdBarCtrl with a command
FW_UICmdBarCtrl* FW_UICmdBarCtrls::Add(FW_Cmd* pCmd)
{
	FW_UICmdBarCtrl* pUICmdBarCtrl = new FW_UICmdBarCtrl(this);
	if(pUICmdBarCtrl)
	{
		pUICmdBarCtrl->SetCmd(pCmd);
		m_vUICmdBarCtrl.push_back(pUICmdBarCtrl);
	}
	return pUICmdBarCtrl;
}

// Get count
size_t FW_UICmdBarCtrls::GetCount() const
{
	return m_vUICmdBarCtrl.size();
}

// Get command
FW_Cmd* FW_UICmdBarCtrls::GetCmd(int iIndex)
{
	return m_vUICmdBarCtrl[iIndex]->GetCmd();
}