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

class FW_EventManager;
class ATL_NO_VTABLE CFWEventManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWEventManager, &CLSID_FWEventManager>,
	public IDispatchImpl<IFWEventManager, &IID_IFWEventManager, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWEventManager();

DECLARE_REGISTRY_RESOURCEID(IDR_FWEVENTMANAGER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWEventManager)
	COM_INTERFACE_ENTRY(IFWEventManager)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();	
	void	FinalRelease();

public:
	STDMETHOD(get_MouseEvents)(/*[out, retval]*/IFWMouseEvents* *ppVal);

private:
	FW_EventManager*			m_pEventManager;
};

OBJECT_ENTRY_AUTO(__uuidof(FWEventManager), CFWEventManager)
