// AddInServer.h : CAddInServer µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ

#include "AddInSample.h"

// CAddInServer
class CMouseEventsHandler;
class ATL_NO_VTABLE CAddInServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAddInServer, &CLSID_AddInServer>,
	public IDispatchImpl<IAddInServer, &IID_IAddInServer, &LIBID_AddInSampleLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IXCADAddIn
{
public:
	CAddInServer();

DECLARE_REGISTRY_RESOURCEID(IDR_ADDINSERVER)

DECLARE_NOT_AGGREGATABLE(CAddInServer)

BEGIN_COM_MAP(CAddInServer)
	COM_INTERFACE_ENTRY(IAddInServer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IXCADAddIn)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	STDMETHOD(Initialize)(IFWWinApp* pApp, VARIANT_BOOL bFirstTime);
	STDMETHOD(Uninitialize)(void);

private:
	CComPtr<IFWWinApp>	m_spApp;

	CComObject<CMouseEventsHandler>* m_pMouseEventsHandler;

};

OBJECT_ENTRY_AUTO(__uuidof(AddInServer), CAddInServer)
