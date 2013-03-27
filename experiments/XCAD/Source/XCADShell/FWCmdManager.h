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

class FW_CmdManager;
class ATL_NO_VTABLE CFWCmdManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWCmdManager, &CLSID_FWCmdManager>,
	public IDispatchImpl<IFWCmdManager, &IID_IFWCmdManager, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWCmdManager();

DECLARE_REGISTRY_RESOURCEID(IDR_FWCMDMANAGER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWCmdManager)
	COM_INTERFACE_ENTRY(IFWCmdManager)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();	
	void	FinalRelease();

public:
	STDMETHOD(get_Cmds)(/*[out, retval]*/IFWCmds* *ppVal);

private:
	FW_CmdManager*			m_pCmdManager;
};

OBJECT_ENTRY_AUTO(__uuidof(FWCmdManager), CFWCmdManager)
