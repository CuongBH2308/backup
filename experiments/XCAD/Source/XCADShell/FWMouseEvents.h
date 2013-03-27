// FWMouseEvents.h : CFWMouseEvents 
// Implement event source (CFWMouseEvents)
// IFWMouseEvents
// IFWMouseEventsSink

// In order to use it, we should 
// 1. In client, implement a class A derived from IDispEventSimpleImpl
// 2. In client, in this class A, declare the sink map
// 3. In client, instance this class A
// 4. In client, get the mouse-events object from the server
// 5. Call A::DispEventAdvise
//	  to establish a connection between A and the event source (CFWMouseEvents)

#pragma once
#include "resource.h"       
#include "xcadshell.h"
#include "fwmouseeventssink.h"

class ATL_NO_VTABLE CFWMouseEvents : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFWMouseEvents, &CLSID_FWMouseEvents>,
	public IDispatchImpl<IFWMouseEvents, &IID_IFWMouseEvents, &LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IConnectionPointContainerImpl<CFWMouseEvents>,
	public CFWMouseEventsSink<CFWMouseEvents>
{
public:
	CFWMouseEvents()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FWMOUSEEVENTS)

BEGIN_COM_MAP(CFWMouseEvents)
	COM_INTERFACE_ENTRY(IFWMouseEvents)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CFWMouseEvents)
	CONNECTION_POINT_ENTRY(IID_IFWMouseEventsSink)
END_CONNECTION_POINT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(Move)(LONGLONG hWnd, LONG lFlag, LONG x, LONG y);
};

OBJECT_ENTRY_AUTO(__uuidof(FWMouseEvents), CFWMouseEvents)
