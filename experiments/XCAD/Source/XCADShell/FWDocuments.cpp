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
#include "fwdocuments.h"
#include "fwdocument.h"
#include "..\fw_document.h"
#include "..\fw_winapp.h"

CFWDocuments::CFWDocuments()
:m_pApp(NULL)
{
}

HRESULT CFWDocuments::FinalConstruct()
{
	m_pApp = FW_WinApp::GetWinApp();
	return S_OK;
}

void CFWDocuments::FinalRelease() 
{
	if(m_pApp)
		m_pApp->ResetDocsInterface();
}

STDMETHODIMP CFWDocuments::Add(IFWDocument* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;

//	m_pApp->OnFileNew();

	return S_OK;
}

STDMETHODIMP CFWDocuments::Open(BSTR bstrFileName, IFWDocument* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

STDMETHODIMP CFWDocuments::Item(VARIANT Index, IFWDocument* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;

	*ppVal = NULL;
	FW_Document* pDoc = NULL;
	int nIndex = 0;
	POSITION pos = m_pApp->GetFirstDocTemplatePosition();
	while (pos)
	{
		CDocTemplate* pTemplate = (CDocTemplate*)m_pApp->GetNextDocTemplate(pos);
		POSITION pos2 = pTemplate->GetFirstDocPosition();
		while (pos2)
		{
			FW_Document* pDocTemp = (FW_Document*)(pTemplate->GetNextDoc(pos2));
			if(pDocTemp)
			{
				if( (Index.vt==VT_I4 && (Index.lVal-1)==nIndex) ||
					(Index.vt==VT_BSTR && pDocTemp->GetTitle()==CString(Index.bstrVal)) )
				{
					pDoc = pDocTemp;
					break;
				}
				nIndex++;
			}
		}
		if(pDoc)
			break;
	}
	if(pDoc)
		*ppVal = pDoc->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CFWDocuments::get__NewEnum(IUnknown* *ppVal)
{
	if(!ppVal)
		return E_INVALIDARG;
	CFWEnumDocs* pNew = new CFWEnumDocs(this);
	if(!pNew)
		return E_OUTOFMEMORY;
	return pNew->QueryInterface(IID_IUnknown, (LPVOID*)ppVal);
}

STDMETHODIMP CFWDocuments::get_Count(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;

	*pVal = 0;
	int nIndex = 0;
	POSITION pos = m_pApp->GetFirstDocTemplatePosition();
	while (pos)
	{
		CDocTemplate* pTemplate = (CDocTemplate*)m_pApp->GetNextDocTemplate(pos);
		POSITION pos2 = pTemplate->GetFirstDocPosition();
		while (pos2)
		{
			CDocument* pDoc = pTemplate->GetNextDoc(pos2);
			if(pDoc->IsKindOf(RUNTIME_CLASS(FW_Document)))
				(*pVal)++;
		}
	}

	return S_OK;
}

STDMETHODIMP CFWDocuments::get_Parent(IFWWinApp* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;
	*ppVal = m_pApp->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFWDocuments::get_Application(IFWWinApp* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;
	*ppVal = m_pApp->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}



STDMETHODIMP CFWEnumDocs::QueryInterface(REFIID riid, LPVOID* ppvObj)
{
	if(IsEqualGUID(riid, IID_IUnknown))
		*ppvObj = (LPVOID)(IUnknown*)this;
	else if(IsEqualGUID(riid, IID_IEnumVARIANT))
		*ppvObj = (LPVOID)(IEnumVARIANT*)this;
	else
		return E_NOINTERFACE;

	AddRef();
	return NOERROR;
}

STDMETHODIMP CFWEnumDocs::Next(ULONG celt, VARIANT* rgvar, ULONG* celtFetched)
{
	ULONG ulFetched = 0;
	IFWDocument* pDoc;

	for(ULONG i = 0; i < celt; i++)
	{
		if(m_posCur == NULL)
			break;
		VariantInit(&(rgvar[i]));
		pDoc = (IFWDocument*)m_plistDocs->GetNext(m_posCur);
		V_VT(&(rgvar[i])) = VT_DISPATCH;
		pDoc->QueryInterface(IID_IDispatch, (LPVOID*)&(rgvar[i].pdispVal));
		ulFetched++;
	}

	if(celtFetched != NULL)
		*celtFetched = ulFetched;

	return ulFetched < celt ? S_FALSE : NOERROR;
}

STDMETHODIMP CFWEnumDocs::Skip(ULONG celt)
{
	ULONG ulSkipped = 0;
	void* pSkip;
	for(ULONG i = 0; i < celt; i++)
	{
		if(m_posCur == NULL)
			break;
		pSkip = m_plistDocs->GetNext(m_posCur);
		ulSkipped++;
	}
	return ulSkipped < celt ? S_FALSE : NOERROR;
}

STDMETHODIMP CFWEnumDocs::Reset()
{
	m_posCur = m_plistDocs->GetHeadPosition();
	return NOERROR;
}

STDMETHODIMP CFWEnumDocs::Clone(IEnumVARIANT** ppEnum)
{
	if(!ppEnum)
		return E_INVALIDARG;
	CFWEnumDocs* pNew = new CFWEnumDocs(this);
	if( !pNew ) 
		return E_OUTOFMEMORY;
	return pNew->QueryInterface(IID_IEnumVARIANT, (LPVOID*)ppEnum);
}

CFWEnumDocs::CFWEnumDocs(CFWDocuments* pDocs)
{
	m_cRef = 0;
// test	m_plistDocs = &(pDocs->m_listDocs);
	m_posCur = m_plistDocs->GetHeadPosition();
}

CFWEnumDocs::CFWEnumDocs(CFWEnumDocs* pEnum)
{
	m_cRef = 0;
	m_plistDocs = pEnum->m_plistDocs;
	m_posCur = pEnum->m_posCur;
}
