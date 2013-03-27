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

class FW_Document;
class FW_WinApp;
class CFWWinApp;
class ATL_NO_VTABLE CFWDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWDocument, &CLSID_FWDocument>,
	public IDispatchImpl<IFWDocument, &IID_IFWDocument, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWDocument();

DECLARE_REGISTRY_RESOURCEID(IDR_FWDOCUMENT)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWDocument)
	COM_INTERFACE_ENTRY(IFWDocument)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();	
	void	FinalRelease();

public:
	STDMETHOD(SetPrimary)(unsigned char* pVal);
	STDMETHOD(Save)();
	STDMETHOD(Activate)();
	STDMETHOD(Close)(/*[in, optional]*/ FWSaveOptions Option);
	STDMETHOD(get_Saved)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Saved)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Collection)(/*[out, retval]*/ IFWDocuments* *ppVal);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IFWWinApp* *ppVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IFWWinApp* *ppVal);

private:
	FW_WinApp*		m_pApp;
	FW_Document*	m_pDoc;
};

OBJECT_ENTRY_AUTO(__uuidof(FWDocument), CFWDocument)
