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

class FW_UIManager;
class ATL_NO_VTABLE CFWUIManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWUIManager, &CLSID_FWUIManager>,
	public IDispatchImpl<IFWUIManager, &IID_IFWUIManager, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWUIManager();

DECLARE_REGISTRY_RESOURCEID(IDR_FWUIMANAGER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWUIManager)
	COM_INTERFACE_ENTRY(IFWUIManager)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();	
	void	FinalRelease();

public:
	STDMETHOD(get_CmdBars)(/*[out, retval]*/IFWUICmdBars* *ppVal);

private:
	FW_UIManager*				m_pUIManager;
};

OBJECT_ENTRY_AUTO(__uuidof(FWUIManager), CFWUIManager)
