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
#include "fw_uicmdbars.h"

FW_UICmdBars::FW_UICmdBars(FW_UIManager* pUIManager)
:m_pUIManager(pUIManager)
{
}

FW_UICmdBars::~FW_UICmdBars(void)
{
	for(std::vector<FW_UICmdBar*>::const_iterator it=m_vUICmdBar.begin();it!=m_vUICmdBar.end();it++)
		delete (*it);

	m_vUICmdBar.clear();
}

// Get m_spIFWUICmdBars;
CComPtr<IFWUICmdBars> FW_UICmdBars::GetInterface()
{
	if(!m_spIFWUICmdBars)
	{
		HRESULT hr = m_spIFWUICmdBars.CoCreateInstance(CLSID_FWUICmdBars,NULL,CLSCTX_INPROC_SERVER);
		ASSERT(SUCCEEDED(hr));
	}

	return m_spIFWUICmdBars;
}

// Set m_spIFWUICmdBars to NULL
void FW_UICmdBars::ResetInterface()
{
	if(m_spIFWUICmdBars)
		m_spIFWUICmdBars.p = NULL;
}

FW_UICmdBar* FW_UICmdBars::Add(const CString& strDisplayName,
							   const CString& strInternalName)
{
	FW_UICmdBar* pUICmdBar = GetItem(strInternalName);
	ASSERT(!pUICmdBar);

	pUICmdBar = new FW_UICmdBar(this, strDisplayName, strInternalName);
	if(pUICmdBar) 
		m_vUICmdBar.push_back(pUICmdBar);

	return pUICmdBar;
}

// Get command bar according to the internal name
FW_UICmdBar* FW_UICmdBars::GetItem(const CString& strInternalName) const
{
	FW_UICmdBar* pUICmdBar = NULL;
	for(std::vector<FW_UICmdBar*>::const_iterator it=m_vUICmdBar.begin();it!=m_vUICmdBar.end();it++)
	{
		if((*it)->GetInternalName().Compare(strInternalName)==0)
		{
			pUICmdBar = (*it);
			break;
		}
	}
	return pUICmdBar;
}

// Get command bar according to the index
FW_UICmdBar* FW_UICmdBars::GetItem(int iIndex) const
{
	if(size_t(iIndex)<m_vUICmdBar.size())
		return m_vUICmdBar[iIndex];
	else
		return NULL;
}
