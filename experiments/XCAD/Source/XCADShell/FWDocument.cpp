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
#include "fwdocument.h"
#include "..\fw_document.h"
#include "..\fw_winapp.h"

CFWDocument::CFWDocument()
:m_pDoc(NULL),
m_pApp(NULL)
{
}

HRESULT CFWDocument::FinalConstruct()
{
	m_pApp = FW_WinApp::GetWinApp();
	return S_OK;
}

void CFWDocument::FinalRelease() 
{
	if(m_pDoc)
		m_pDoc->ResetInterface();
}

STDMETHODIMP CFWDocument::SetPrimary(unsigned char* pVal)
{
	m_pDoc = reinterpret_cast<FW_Document*>(pVal);
	return S_OK;
}

STDMETHODIMP CFWDocument::get_Application(IFWWinApp* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*ppVal = NULL;
	if(!m_pDoc || !m_pApp)
		return E_FAIL;

	*ppVal = m_pApp->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFWDocument::get_Name(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pDoc)
		return E_FAIL;

	CComBSTR bstrName(m_pDoc->GetTitle());
	*pVal = bstrName.Detach();

	return S_OK;
}

STDMETHODIMP CFWDocument::get_Parent(IFWWinApp* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

STDMETHODIMP CFWDocument::get_Collection(IFWDocuments* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

STDMETHODIMP CFWDocument::get_Saved(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

STDMETHODIMP CFWDocument::put_Saved(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

STDMETHODIMP CFWDocument::Close(FWSaveOptions Option)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

STDMETHODIMP CFWDocument::Activate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

STDMETHODIMP CFWDocument::Save()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}