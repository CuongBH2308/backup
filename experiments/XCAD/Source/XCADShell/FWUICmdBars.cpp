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
#include "fwuicmdbars.h"
#include "..\fw_uimanager.h"
#include "..\fw_uicmdbars.h"
#include "..\fw_winapp.h"

CFWUICmdBars::CFWUICmdBars()
{
	m_pUICmdBars = FW_WinApp::GetWinApp()->GetUIManager()->GetUICmdBars();
}

HRESULT CFWUICmdBars::FinalConstruct()
{
	return S_OK;
}

void CFWUICmdBars::FinalRelease() 
{
	if(m_pUICmdBars)
		m_pUICmdBars->ResetInterface();
}

STDMETHODIMP CFWUICmdBars::Add(BSTR bstrDisplayName, BSTR bstrInternalName, IFWUICmdBar* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	FW_UICmdBar* pUICmdBar = m_pUICmdBars->Add(CString(bstrDisplayName),CString(bstrInternalName));
	if(pUICmdBar)
		*ppVal = pUICmdBar->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CFWUICmdBars::Item(VARIANT Index, IFWUICmdBar* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	if(!m_pUICmdBars)
		return E_FAIL;

	FW_UICmdBar* pUICmdBar = NULL;
	if(Index.vt==VT_I2)
		pUICmdBar = m_pUICmdBars->GetItem(Index.iVal-1);
	else if(Index.vt==VT_I4)
		pUICmdBar = m_pUICmdBars->GetItem(Index.lVal-1);
	else if(Index.vt==VT_BSTR)
		pUICmdBar = m_pUICmdBars->GetItem(CString(Index.bstrVal));

	if(pUICmdBar)
		*ppVal = pUICmdBar->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CFWUICmdBars::get__NewEnum(IUnknown* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;
	return hr;
}

STDMETHODIMP CFWUICmdBars::get_Count(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;
	*pVal = 0;
	return hr;
}

STDMETHODIMP CFWUICmdBars::get_Parent(IFWUIManager* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hr = S_OK;
	return hr;
}
