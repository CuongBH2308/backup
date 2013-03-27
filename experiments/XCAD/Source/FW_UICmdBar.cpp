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
#include "fw_uicmdbar.h"
#include "fw_uicmdbarctrls.h"

FW_UICmdBar::FW_UICmdBar(FW_UICmdBars* pUICmdBars, const CString& strDisplayName, const CString& strInternalName)
:m_pUICmdBars(pUICmdBars),
m_strDisplayName(strDisplayName),
m_strInternalName(strInternalName),
m_pUICmdBarCtrls(NULL)
{
	GetInterface();
}

FW_UICmdBar::~FW_UICmdBar(void)
{
	if(m_pUICmdBarCtrls)
	{
		delete m_pUICmdBarCtrls;
		m_pUICmdBarCtrls = NULL;
	}
}

// Get m_spIFWUICmdBar;
CComPtr<IFWUICmdBar> FW_UICmdBar::GetInterface()
{
	if(!m_spIFWUICmdBar)
	{
		HRESULT hr = m_spIFWUICmdBar.CoCreateInstance(CLSID_FWUICmdBar,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
		if(SUCCEEDED(hr))
			m_spIFWUICmdBar->SetPrimary(reinterpret_cast<unsigned char*>(this));
	}

	return m_spIFWUICmdBar;
}

// Set m_spIFWUICmdBar to NULL
void FW_UICmdBar::ResetInterface()
{
	if(m_spIFWUICmdBar)
		m_spIFWUICmdBar.p = NULL;
}


CString FW_UICmdBar::GetDisplayName() const
{
	return m_strDisplayName;
}

CString FW_UICmdBar::GetInternalName() const
{
	return m_strInternalName;
}

FW_UICmdBarCtrls* FW_UICmdBar::GetUICmdBarCtrls()
{
	if(!m_pUICmdBarCtrls)
		m_pUICmdBarCtrls = new FW_UICmdBarCtrls(this);
	return m_pUICmdBarCtrls;
}

// Associate a FW_UICmdBarCtrl with a command
FW_UICmdBarCtrl* FW_UICmdBar::Add(FW_Cmd* pCmd)
{
	return GetUICmdBarCtrls()->Add(pCmd);
}
