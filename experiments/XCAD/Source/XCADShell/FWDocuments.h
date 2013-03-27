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

class FW_WinApp;
class ATL_NO_VTABLE CFWDocuments : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWDocuments, &CLSID_FWDocuments>,
	public IDispatchImpl<IFWDocuments, &IID_IFWDocuments, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFWDocuments();

DECLARE_REGISTRY_RESOURCEID(IDR_FWDOCUMENTS)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFWDocuments)
	COM_INTERFACE_ENTRY(IFWDocuments)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	HRESULT FinalConstruct();	
	void	FinalRelease();

	// IFWDocuments
public:	
	STDMETHOD(Add)(/*[out retval]*/IFWDocument* *ppVal);
	STDMETHOD(Open)(/*[in]*/ BSTR FileName, /*[out, retval]*/ IFWDocument* *ppVal);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ IFWDocument* *ppVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *ppVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IFWWinApp* *ppVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IFWWinApp* *ppVal);

private:
	FW_WinApp* m_pApp;
};

OBJECT_ENTRY_AUTO(__uuidof(FWDocuments), CFWDocuments)


class CFWEnumDocs : public IEnumVARIANT
{
public:
	CFWEnumDocs(CFWDocuments* pDocs); //main constructor
	CFWEnumDocs(CFWEnumDocs* pEnum); //clone constructor

	//IUnknown methods
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID* ppvObj);
	STDMETHOD_(ULONG, AddRef)() { return ++m_cRef; }
	STDMETHOD_(ULONG, Release)() { if (--m_cRef == 0) { delete this; return 0;} return m_cRef; }

	//IEnumVARIANT methods
	STDMETHOD(Next)(ULONG celt, VARIANT* rgvar, ULONG* celtFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)();
	STDMETHOD(Clone)(IEnumVARIANT** ppenum);

private:
	ULONG m_cRef;
	CPtrList* m_plistDocs;
	POSITION m_posCur;
};