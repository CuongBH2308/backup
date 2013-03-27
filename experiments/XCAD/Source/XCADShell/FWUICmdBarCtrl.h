// FWUICmdBarCtrl.h : CFWUICmdBarCtrl µÄÉùÃ÷

#pragma once
#include "resource.h"
#include "xcadshell.h"

class FW_UICmdBarCtrl;
class ATL_NO_VTABLE CFWUICmdBarCtrl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWUICmdBarCtrl, &CLSID_FWUICmdBarCtrl>,
	public IDispatchImpl<IFWUICmdBarCtrl, &IID_IFWUICmdBarCtrl, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWUICmdBarCtrl();

DECLARE_REGISTRY_RESOURCEID(IDR_FWUICMDBARCTRL)
DECLARE_NOT_AGGREGATABLE(CFWUICmdBarCtrl)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWUICmdBarCtrl)
	COM_INTERFACE_ENTRY(IFWUICmdBarCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();	
	void	FinalRelease();

public:
	STDMETHOD(SetPrimary)(unsigned char* pVal);

private:
	FW_UICmdBarCtrl* m_pUICmdBarCtrl;
};

OBJECT_ENTRY_AUTO(__uuidof(FWUICmdBarCtrl), CFWUICmdBarCtrl)
