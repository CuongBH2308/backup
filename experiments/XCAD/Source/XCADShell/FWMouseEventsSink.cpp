// FWMouseEventsSink.cpp : CFWMouseEventsSink µÄÊµÏÖ

#include "stdafx.h"
#include "FWMouseEventsSink.h"


// CFWMouseEventsSink
//template<class T>
//HRESULT CFWMouseEventsSink<T>::Fire_OnMove(HWND hView, UINT nFlags, const CPoint& point)
//{
//	CComVariant varResult;
//	T* pT = static_cast<T*>(this);
//	int nConnectionIndex;
//	CComVariant* pvars = new CComVariant[4];
//	int nConnections = m_vec.GetSize();
//
//	for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
//	{
//		pT->Lock();
//		CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
//		pT->Unlock();
//		IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
//		if (pDispatch != NULL)
//		{
//			VariantClear(&varResult);
//			pvars[0] = long(hView);
//			pvars[1] = long(nFlags);
//			pvars[2] = long(point.x);
//			pvars[3] = long(point.y);
//
//			DISPPARAMS disp = { pvars, NULL, 4, 0 };
//			pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
//		}
//	}
//	delete[] pvars;
//	return varResult.scode;
//}
