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

class ATL_NO_VTABLE CXCADAddIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXCADAddIn, &CLSID_XCADAddIn>,
	public IXCADAddIn
{
public:
	CXCADAddIn()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_XCADADDIN)
DECLARE_NOT_AGGREGATABLE(CXCADAddIn)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXCADAddIn)
	COM_INTERFACE_ENTRY(IXCADAddIn)
//	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

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
};

OBJECT_ENTRY_AUTO(__uuidof(XCADAddIn), CXCADAddIn)
