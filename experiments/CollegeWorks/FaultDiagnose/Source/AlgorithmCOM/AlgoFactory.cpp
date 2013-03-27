// AlgoFactory.cpp: implementation of the CAlgoFactory class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AlgoFactory.h"
#include "Algorithm.h"


//extern LONG g_cObjectAndLocks;
extern LONG g_cObjectAndLocks;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//CAlgoFactory::~CAlgoFactory()
//{

//}



STDMETHODIMP_(ULONG) CAlgoFactory::AddRef(void)
{
	return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CAlgoFactory::Release(void)
{
	return ::InterlockedDecrement(&m_cRef);
}

STDMETHODIMP CAlgoFactory::QueryInterface(REFIID riid,void ** ppv)
{
	*ppv=NULL;
	if(riid==IID_IUnknown||riid==IID_IClassFactory)
	{
		*ppv=static_cast<IClassFactory *>(this);
		//*ppv=reinterpret_cast<IClassFactory *>(this);
		//*ppv=(IClassFactory *)(this);
		reinterpret_cast<IUnknown*>(*ppv)->AddRef();
		return S_OK;
	}
	else
		return (*ppv=0),E_NOINTERFACE;
}

STDMETHODIMP CAlgoFactory::CreateInstance(IUnknown * pUnkOuter,REFIID riid,void ** ppv)
{
	*ppv=NULL;
	
	//现在不支持聚合
	if(pUnkOuter!=NULL)
		return CLASS_E_NOAGGREGATION;
	
	CAlgorithm * pAlgo=new CAlgorithm;
	if(pAlgo==NULL)
		return E_OUTOFMEMORY;
	
	HRESULT hr=pAlgo->QueryInterface(riid,ppv);
	
	if(FAILED(hr))
		delete pAlgo;
	
	return hr;
	
}

STDMETHODIMP CAlgoFactory::LockServer(BOOL fLock)
{
	if(fLock)
		::InterlockedIncrement(&g_cObjectAndLocks);
	else 
		::InterlockedDecrement(&g_cObjectAndLocks);
	return NOERROR;
	
}


