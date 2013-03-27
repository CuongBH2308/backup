// AddInServer.cpp : CAddInServer 

#include "stdafx.h"
#include "AddInServer.h"
#include "MouseEventsHandler.h"


// CAddInServer
CAddInServer::CAddInServer()
:m_pMouseEventsHandler(NULL)
{
}

STDMETHODIMP CAddInServer::Initialize(IFWWinApp* pApp, VARIANT_BOOL bFirstTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	m_spApp = pApp;

	CComPtr<IFWEventManager> spIFWEventManager;
	HRESULT hr = m_spApp->get_EventManager(&spIFWEventManager);
	if(FAILED(hr))
		return hr;

	CComPtr<IFWMouseEvents> spIFWMouseEvents;
	hr = spIFWEventManager->get_MouseEvents(&spIFWMouseEvents);
	if(FAILED(hr))
		return hr;

	hr = CComObject<CMouseEventsHandler>::CreateInstance(&m_pMouseEventsHandler);
	if(FAILED(hr))
		return hr;

	hr = m_pMouseEventsHandler->DispEventAdvise(spIFWMouseEvents);
	if(FAILED(hr))
		return hr;

	return hr;
}

STDMETHODIMP CAddInServer::Uninitialize(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(m_pMouseEventsHandler)
	{
		CComPtr<IFWEventManager> spIFWEventManager;
		HRESULT hr = m_spApp->get_EventManager(&spIFWEventManager);
		if(FAILED(hr))
			return hr;

		CComPtr<IFWMouseEvents> spIFWMouseEvents;
		hr = spIFWEventManager->get_MouseEvents(&spIFWMouseEvents);
		if(FAILED(hr))
			return hr;
		hr = m_pMouseEventsHandler->DispEventUnadvise(spIFWMouseEvents);
		m_pMouseEventsHandler->Release();
	}

	return S_OK;
}