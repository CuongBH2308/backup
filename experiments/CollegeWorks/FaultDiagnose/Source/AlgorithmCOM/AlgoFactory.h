// AlgoFactory.h: interface for the CAlgoFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGOFACTORY_H__C2139805_91F9_4C13_B626_D669350E1C0E__INCLUDED_)
#define AFX_ALGOFACTORY_H__C2139805_91F9_4C13_B626_D669350E1C0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <unknwn.h>

class CAlgoFactory:IClassFactory
{
public:
	CAlgoFactory():m_cRef(0){}
	//virtual ~CAlgoFactory();

	
	
	//IUnknow Method
	STDMETHODIMP QueryInterface(REFIID,void**);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	
	//IClassFactory Method
	STDMETHODIMP CreateInstance(IUnknown * ,REFIID ,void **);
	STDMETHODIMP LockServer(BOOL fLock);
	
protected:
	LONG m_cRef;
	

};

#endif // !defined(AFX_ALGOFACTORY_H__C2139805_91F9_4C13_B626_D669350E1C0E__INCLUDED_)
