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
#include "eventsids.h"

template <class T>
class CFWMouseEventsSink : public IConnectionPointImpl<T, &IID_IFWMouseEventsSink, CComDynamicUnkArray>
{
public:
	HRESULT Fire_OnMove(HWND hView, UINT nFlags, const CPoint& point)
	{
		HRESULT hr = S_OK;
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
		int nConnections = m_vec.GetSize();

		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VariantClear(&varResult);
				pvars[3].vt = VT_I8;
				pvars[3].llVal = LONGLONG(hView);
				pvars[2] = long(nFlags);
				pvars[1] = long(point.x);
				pvars[0] = long(point.y);

				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				hr = pDispatch->Invoke(MouseEventsSink_OnMove, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
				ASSERT(SUCCEEDED(hr));
			}
		}
		delete[] pvars;
		return varResult.scode;
	}
};

