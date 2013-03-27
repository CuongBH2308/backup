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

class FW_UICmdBar;
class ATL_NO_VTABLE CFWUICmdBar : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWUICmdBar, &CLSID_FWUICmdBar>,
	public IDispatchImpl<IFWUICmdBar, &IID_IFWUICmdBar, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWUICmdBar();

DECLARE_REGISTRY_RESOURCEID(IDR_FWUICMDBAR)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWUICmdBar)
	COM_INTERFACE_ENTRY(IFWUICmdBar)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();
	void	FinalRelease();

public:
	STDMETHOD(SetPrimary)(unsigned char* pVal);
	STDMETHOD(get_CmdBarCtrls)(/*[out, retval]*/IFWUICmdBarCtrls* *ppVal);

private:
	FW_UICmdBar* m_pUICmdBar;
};

OBJECT_ENTRY_AUTO(__uuidof(FWUICmdBar), CFWUICmdBar)
