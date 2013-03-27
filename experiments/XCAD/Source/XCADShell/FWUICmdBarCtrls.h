// FWUICmdBarCtrls.h : CFWUICmdBarCtrls µÄÉùÃ÷

#pragma once
#include "resource.h"
#include "xcadshell.h"

class FW_UICmdBarCtrls;
class ATL_NO_VTABLE CFWUICmdBarCtrls : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWUICmdBarCtrls, &CLSID_FWUICmdBarCtrls>,
	public IDispatchImpl<IFWUICmdBarCtrls, &IID_IFWUICmdBarCtrls, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWUICmdBarCtrls();

DECLARE_REGISTRY_RESOURCEID(IDR_FWUICMDBARCTRLS)
DECLARE_NOT_AGGREGATABLE(CFWUICmdBarCtrls)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWUICmdBarCtrls)
	COM_INTERFACE_ENTRY(IFWUICmdBarCtrls)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();	
	void	FinalRelease();

public:
	STDMETHOD(SetPrimary)(unsigned char* pVal);

	// Associate a FW_UICmdBarCtrl with a command
	STDMETHOD(Add)(IFWCmd* pIFWCmd, IFWUICmdBarCtrl* *ppVal);

private:
	FW_UICmdBarCtrls* m_pUICmdBarCtrls;
};

OBJECT_ENTRY_AUTO(__uuidof(FWUICmdBarCtrls), CFWUICmdBarCtrls)
