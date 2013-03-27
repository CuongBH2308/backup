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


#pragma once
#include "resource.h"
#include "xcadshell.h"

class FW_WinApp;
class CFWDocument;
class CFWDocuments;

class ATL_NO_VTABLE CFWWinApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWWinApp, &CLSID_FWWinApp>,
	public IDispatchImpl<IFWWinApp, &IID_IFWWinApp, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWWinApp();

DECLARE_REGISTRY_RESOURCEID(IDR_FWWINAPP)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWWinApp)
	COM_INTERFACE_ENTRY(IFWWinApp)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();
	void	FinalRelease();

	// IFWWinApp
public:
	STDMETHOD(Quit)(/*[in]*/ FWSaveOptions);
	STDMETHOD(Activate)();
	STDMETHOD(get_VBE)(/*[out, retval]*/ IDispatch* *ppVal);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IFWWinApp* *ppVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Documents)(/*[out, retval]*/ IFWDocuments* *ppVal);
	STDMETHOD(get_ActiveDocument)(/*[out, retval]*/ IFWDocument* *ppVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IFWWinApp* *ppVal);
	STDMETHOD(get_CmdManager)(/*[out, retval]*/ IFWCmdManager* *ppVal);
	STDMETHOD(get_UIManager)(/*[out, retval]*/ IFWUIManager* *ppVal);
	STDMETHOD(get_EventManager)(/*[out, retval]*/ IFWEventManager* *ppVal);

private:
	FW_WinApp* m_pApp;
};

OBJECT_ENTRY_AUTO(__uuidof(FWWinApp), CFWWinApp)
