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
#include "fwuicmdbar.h"
#include "fwuicmdbarctrls.h"
#include "..\fw_uicmdbar.h"
#include "..\fw_uicmdbarctrls.h"

CFWUICmdBar::CFWUICmdBar()
:m_pUICmdBar(NULL)
{
}

HRESULT CFWUICmdBar::FinalConstruct()
{
	return S_OK;
}

void CFWUICmdBar::FinalRelease() 
{
	if(m_pUICmdBar)
		m_pUICmdBar->ResetInterface();
}

STDMETHODIMP CFWUICmdBar::SetPrimary(unsigned char* pVal)
{
	m_pUICmdBar = reinterpret_cast<FW_UICmdBar*>(pVal);
	return S_OK;
}

STDMETHODIMP CFWUICmdBar::get_CmdBarCtrls(IFWUICmdBarCtrls* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	FW_UICmdBarCtrls* pUICmdBarCtrls = m_pUICmdBar->GetUICmdBarCtrls();
	if(!pUICmdBarCtrls)
		return E_OUTOFMEMORY;

	*ppVal = pUICmdBarCtrls->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}
