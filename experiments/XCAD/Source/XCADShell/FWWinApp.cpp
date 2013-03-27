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
#include "fwwinapp.h"
#include "fwdocuments.h"
#include "..\fw_winapp.h"
#include "..\fw_document.h"
#include "..\fw_cmdmanager.h"
#include "..\fw_uimanager.h"
#include "..\fw_eventmanager.h"

CFWWinApp::CFWWinApp()
:m_pApp(NULL)
{
}

HRESULT CFWWinApp::FinalConstruct()
{
	m_pApp = FW_WinApp::GetWinApp();
	return S_OK;
}

void CFWWinApp::FinalRelease() 
{
	if(m_pApp)
		m_pApp->ResetInterface();
}

STDMETHODIMP CFWWinApp::get_Application(IFWWinApp* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return ((IDispatch*)this)->QueryInterface(IID_IFWWinApp, (LPVOID*)ppVal);
}

STDMETHODIMP CFWWinApp::get_ActiveDocument(IFWDocument* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;

	*ppVal = NULL;
	FW_Document* pDoc = NULL;
	POSITION pos = m_pApp->GetFirstDocTemplatePosition();
	while (pos)
	{
		CDocTemplate* pTemplate = (CDocTemplate*)m_pApp->GetNextDocTemplate(pos);
		POSITION pos2 = pTemplate->GetFirstDocPosition();
		while (pos2)
		{
			CDocument* pDocTemp1 = pTemplate->GetNextDoc(pos2);
			if(!pDocTemp1->IsKindOf(RUNTIME_CLASS(FW_Document)))
				continue;
			FW_Document* pDocTemp2 = (FW_Document*)(pDocTemp1);
			if(pDocTemp2 && pDocTemp2->GetActive())
			{
				pDoc = pDocTemp2;
				break;
			}
		}
		if(pDoc)
			break;
	}

	if(pDoc)
		*ppVal = pDoc->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFWWinApp::get_Name(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;

	CComBSTR bstrName(m_pApp->m_pszAppName);
	*pVal = bstrName.Detach();

	return S_OK;
}

STDMETHODIMP CFWWinApp::get_Parent(IFWWinApp* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return ((IDispatch*)this)->QueryInterface(IID_IFWWinApp, (LPVOID*)ppVal);
}

STDMETHODIMP CFWWinApp::get_VBE(IDispatch* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;

	VBIDE::VBE* pVBE = NULL;
	HRESULT hr = m_pApp->ApcHost->APC_GET(VBE)(&pVBE);
	if(FAILED(hr))
		return hr;

	hr = pVBE->QueryInterface(IID_IDispatch, (LPVOID*)ppVal);
	if(FAILED(hr))
		return hr;
	hr = pVBE->Release();
	return hr;
}

STDMETHODIMP CFWWinApp::Activate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(!m_pApp)
		return E_FAIL;
	((CFrameWnd*)m_pApp->m_pMainWnd)->ActivateFrame();
	return S_OK;
}

STDMETHODIMP CFWWinApp::Quit(FWSaveOptions Option)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CComPtr<IFWDocuments> spDocs;
	HRESULT hr = get_Documents(&spDocs);
	if(FAILED(hr))
		return hr;

	long iCount = 0;
	hr = spDocs->get_Count(&iCount);
	if(FAILED(hr))
		return hr;

	for(long i=0;i<iCount;i++)
	{
		CComPtr<IFWDocument> spDoc;
		hr = spDocs->Item(CComVariant(i), &spDoc);
		if(FAILED(hr))
			return hr;

		hr = spDoc->Close(Option);
		if(FAILED(hr))
			return hr;
	}

	m_pApp->m_pMainWnd->PostMessage(WM_CLOSE, 0, 0);
	return hr;
}

STDMETHODIMP CFWWinApp::get_Documents(IFWDocuments* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = m_pApp->GetDocsInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFWWinApp::get_CmdManager(IFWCmdManager* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	FW_CmdManager* pCmdManager = m_pApp->GetCmdManager();
	if(!pCmdManager)
		return E_OUTOFMEMORY;

	*ppVal = pCmdManager->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFWWinApp::get_UIManager(IFWUIManager* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	FW_UIManager* pUIManager = m_pApp->GetUIManager();
	if(!pUIManager)
		return E_OUTOFMEMORY;

	*ppVal = pUIManager->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CFWWinApp::get_EventManager(IFWEventManager* *ppVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*ppVal = NULL;
	FW_EventManager* pEventManager = m_pApp->GetEventManager();
	if(!pEventManager)
		return E_OUTOFMEMORY;

	*ppVal = pEventManager->GetInterface();
	if(*ppVal == NULL)
		return E_FAIL;

	(*ppVal)->AddRef();
	return S_OK;
}