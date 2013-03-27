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

class FW_Cmds;
class ATL_NO_VTABLE CFWCmds : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWCmds, &CLSID_FWCmds>,
	public IDispatchImpl<IFWCmds, &IID_IFWCmds, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWCmds();

DECLARE_REGISTRY_RESOURCEID(IDR_FWCMDS)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWCmds)
	COM_INTERFACE_ENTRY(IFWCmds)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();
	void	FinalRelease();

public:
	STDMETHOD(Add) (BSTR bstrDisplayName, 
		BSTR bstrTooltip,
		BSTR bstrInternalName,
		IPictureDisp* pPictureDispEnable,
		IPictureDisp* pPictureDispDisable,
		IPictureDisp* pPictureDispHot,
		IFWCmd* *ppVal);

private:
	FW_Cmds* m_pCmds;
};

OBJECT_ENTRY_AUTO(__uuidof(FWCmds), CFWCmds)
