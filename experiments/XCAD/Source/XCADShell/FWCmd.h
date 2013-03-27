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

class FW_Cmd;
class ATL_NO_VTABLE CFWCmd : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWCmd, &CLSID_FWCmd>,
	public IDispatchImpl<IFWCmd, &IID_IFWCmd, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWCmd();

DECLARE_REGISTRY_RESOURCEID(IDR_FWCMD)
DECLARE_NOT_AGGREGATABLE(CFWCmd)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWCmd)
	COM_INTERFACE_ENTRY(IFWCmd)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();	
	void	FinalRelease();

public:
	STDMETHOD(SetPrimary)(unsigned char* pVal);
	STDMETHOD(get_CmdId)(int* pVal);

private:
	FW_Cmd* m_pCmd;
};

OBJECT_ENTRY_AUTO(__uuidof(FWCmd), CFWCmd)
