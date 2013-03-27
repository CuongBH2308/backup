// MouseEventsHandler.h : CMouseEventsHandler µÄÉùÃ÷

#pragma once
#include "resource.h"       // Ö÷·ûºÅ
#include "AddInSample.h"
#include "..\XCADShell\EventsIds.h"

#define MOUSE_EVENTS 0

// If this Add-In wants to receive the mouse events sent by XACD
// it should implement a class as below:
// implement IDispEventImpl, which relates to a sink map <eventId - handleFunc>

// CMouseEventsHandler
class ATL_NO_VTABLE CMouseEventsHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMouseEventsHandler, &CLSID_MouseEventsHandler>,
	public IDispatchImpl<IMouseEventsHandler, &IID_IMouseEventsHandler, &LIBID_AddInSampleLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispEventImpl<MOUSE_EVENTS,CMouseEventsHandler,&IID_IFWMouseEventsSink,&LIBID_XCADShell, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMouseEventsHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MOUSEEVENTSHANDLER)

BEGIN_COM_MAP(CMouseEventsHandler)
	COM_INTERFACE_ENTRY(IMouseEventsHandler)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

BEGIN_SINK_MAP(CMouseEventsHandler)
	SINK_ENTRY_EX(MOUSE_EVENTS,IID_IFWMouseEventsSink,MouseEventsSink_OnMove,OnMove)
END_SINK_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	STDMETHOD (OnMove) (LONGLONG hWnd, long nFlags, long x, long y);
};

OBJECT_ENTRY_AUTO(__uuidof(MouseEventsHandler), CMouseEventsHandler)
