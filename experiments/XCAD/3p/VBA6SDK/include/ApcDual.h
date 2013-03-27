/* --------------------------------------------------------------------------
 * apcDual.h 
 *
 * This file is part of the Microsoft Applications Programability Control (APC)
 * Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
 * Information Contained Herein Is Proprietary and Confidential.
 * -------------------------------------------------------------------------- */
#ifndef APCDUAL_H_INCLUDED			// protect against multiple inclusions
#define APCDUAL_H_INCLUDED

///////////////////////////////////////////////////////////////////////////
#ifdef APC_IMPORT_MIDL
	#include "apcTLB.h"
#endif

///////////////////////////////////////////////////////////////////////////

namespace MSAPC 
{

///////////////////////////////////////////////////////////////////////////
// private:

extern "C" const IID IID_IApcDual;
extern "C" const IID IID_IApcDualSite;

struct __declspec(uuid("db40fa30-928f-11d1-9a5a-00a024941ef0")) IApcDual: IUnknown
{
	STDMETHOD(ApcDualAttach)(void* pvCmdTarget) = 0;
	STDMETHOD(ApcDualDetach)() = 0;
	STDMETHOD(ApcDualGet)(void** ppvCmdTarget) = 0;
};

struct __declspec(uuid("db40fa31-928f-11d1-9a5a-00a024941ef0")) IApcDualSite: IUnknown
{
	STDMETHOD(Detached)() = 0;
	STDMETHOD(HasDual)() = 0;
	STDMETHOD(GetPrimaryIID)(IID* pIID) = 0;
	STDMETHOD(GetDual)(REFIID riid, void** ppvObj) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// public:
// IApcDualImpl< MfcClass >, a required base class for ATL object
//
// Use this class as one of your base classes for your ATL object
// You must also put COM_INTEFACE_ENTRY(IApcDual) in the interface map

template <class MfcClass>
class ATL_NO_VTABLE IApcDualImpl : public IApcDual
{
public:
	typedef MfcClass _MfcClass;

	IApcDualImpl()
	{
		m_pThis = NULL;
		m_pSite = NULL;
		m_pModuleState = AfxGetModuleState();
	}

	~IApcDualImpl()
	{
		ApcDualDetach();
	}

	STDMETHOD(ApcDualAttach)(void* pvThis)
	{
		ASSERT(NULL == m_pThis);
		ASSERT(NULL == m_pSite);
		ASSERT(pvThis);

		MfcClass* pThis = (MfcClass*)pvThis;
		IApcDualSite* pSite = (IApcDualSite*) pThis->GetInterface( &IID_IApcDualSite );
		ASSERT(pSite);

		m_pThis = pThis;
		m_pSite = pSite;
		return NOERROR;
	}

	STDMETHOD(ApcDualDetach)()
	{
		if (m_pSite)
			m_pSite->Detached();

		m_pThis = NULL;
		m_pSite = NULL;

		return NOERROR;
	}

	STDMETHOD(ApcDualGet)(void** ppvThis)
	{
		*ppvThis = (void*) m_pThis;
		return NOERROR;
	}

	STDMETHOD(ApcErrorDetached)()
	{
		return E_UNEXPECTED;
	}

protected:
	_MfcClass* m_pThis;
	IApcDualSite* m_pSite;
	AFX_MODULE_STATE* m_pModuleState;
};

/////////////////////////////////////////////////////////////////////////////
// public:
// 
// The APC_DUAL_PROLOGUE macro declares a local variable called "pThis" 
// that points to the MFC class. Use the APC_DUAL_PROLOGUE macro at the 
// top of a member function of a dual class. This macro much like the 
// METHOD_PROLOGUE macro used at the top of COM functions in straight MFC. 
// The APC_DUAL_PROLOGUE macro does not take any parameters.
//
// The APC_DUAL_PROLOGUE_ macro is a variation that does not manage state.
// (The name is the same except for the trailing underscore).
// This macro is provided for performance reasons, but is not safe in a
// function that directly or indirectly uses mfc's per-thread state. 
//
// If you have any doubt about which macro to use, then use the safe one,
// the one without the trailing underscore: APC_DUAL_PROLOGUE.
//

#define APC_DUAL_PROLOGUE \
	_MfcClass* pThis = m_pThis; \
	if (!pThis) return ApcErrorDetached(); \
	AFX_MANAGE_STATE(m_pModuleState) \

#define APC_DUAL_PROLOGUE_ \
	_MfcClass* pThis = m_pThis; \
	if (!pThis) return ApcErrorDetached(); \

#define APC_CATCH(hr) \
	catch(CException* e) \
	{ \
		hr = COleException::Process(e); \
		e->Delete(); \
	} \
	catch(...) \
	{ \
		hr = E_UNEXPECTED; \
	} \

/////////////////////////////////////////////////////////////////////////////
// public:
// 
// The ATLPTR macro provides a way to get to the full ATL class from the
// MFC class. It would typically be used to fire events, thus:
//
//	ATLPTR(IDualInterface CDualImpl)
//	pCDualImpl->FireEvent();

#ifndef _ATL_DEBUG_INTERFACES
#define ATLPTR(x,y) \
	CComPtr<x> p##x;\
	y* p##y = NULL;\
	ApcGetPrimary(&p##x);\
	p##y = static_cast<y*>(p##x.p);
#else
#define ATLPTR(x,y) \
	CComPtr<x> p##x;\
	y* p##y = NULL;\
	ApcGetPrimary(&p##x);\
	p##y = static_cast<y*>(((x*)((_QIThunk*)(p##x.p))->pUnk));
#endif;



/////////////////////////////////////////////////////////////////////////////
// public:
// ApcGetPrimary function
//
// Use this function to get the primary interface for an MFC class.
// The dual object will be created if needed.

inline HRESULT ApcGetPrimary(CCmdTarget& cmdTarget, void** ppv, IID* piidIn = NULL, IID* piidOut = NULL)
{
	IApcDualSite* pDualSite = static_cast<IApcDualSite*> (
		cmdTarget.GetInterface( &IID_IApcDualSite ));
	if (!pDualSite)
		return E_NOINTERFACE;

	IID iid;
	if (piidIn)
		iid = *piidIn;
	else
		VERIFY(SUCCEEDED(pDualSite->GetPrimaryIID(&iid)));

	HRESULT hr = pDualSite->GetDual(iid, ppv);

	if (piidOut)
		*piidOut = iid;

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// private:
// CApcDualSite< MfcBaseClass, AtlClass, Primary, piidPrimary>
//
// The base class for CApcDualSiteAgg and CApcDualSiteDyn.
//
// This class maintains a m_pApcPrimary pointer to the ATL object, but
// it does not hold a reference to the object.
//
// This class implements IApcDualSite, except for the GetDual funciton

template <class AtlClass, class Primary, const IID* piidPrimary>
class ATL_NO_VTABLE CApcDualSite: public IApcDualSite
{

public:
	CApcDualSite(CCmdTarget* pCmdTarget)
	{
		m_pCmdTarget = pCmdTarget;
		m_pApcPrimary = NULL;
	}

	~CApcDualSite()
	{
		if (m_pApcPrimary)
		{
			// get pIApcDual
			IApcDual* pIApcDual = NULL;
			HRESULT hr = m_pApcPrimary->QueryInterface(IID_IApcDual, (void**)&pIApcDual);
			ASSERT(SUCCEEDED(hr));

			// detach
			pIApcDual->ApcDualDetach();
			ASSERT(m_pApcPrimary == NULL);

			pIApcDual->Release();
		}
	}

	STDMETHODIMP QueryInterface(REFIID iid, void** ppv)
	{
		if ( InlineIsEqualGUID(iid, IID_IApcDualSite) )
		{
			*ppv = static_cast<void*>( static_cast<IApcDualSite*>(this) );
			AddRef();
			return NOERROR;
		}

		return m_pCmdTarget->ExternalQueryInterface(&iid, ppv);
	}

	STDMETHODIMP_(DWORD) AddRef()
	{
		return m_pCmdTarget->ExternalAddRef();
	}
	
	STDMETHODIMP_(DWORD) Release()
	{
		return m_pCmdTarget->ExternalRelease();
	}
	
	STDMETHODIMP Detached()
	{
		m_pApcPrimary = NULL;
		return NOERROR;
	}

	STDMETHODIMP HasDual()
	{
		return m_pApcPrimary ? S_OK : S_FALSE;
	}

	STDMETHOD(GetPrimaryIID)(IID* pIID)
	{
		*pIID = *piidPrimary;
		return NOERROR;
	}

protected:
	HRESULT ApcDualCreate(IUnknown* punkOuter, REFIID iid, void** ppv)
	{
		HRESULT hr;
		ASSERT(!m_pApcPrimary);
		ASSERT(ppv);
		ASSERT(!*ppv);
		IUnknown* p = NULL;
		IApcDual* pDual = NULL;
		Primary* pPrimary = NULL;

		*ppv = NULL;

		// create dual object
		// dual object must support caller-specified iid

		hr = AtlClass::_CreatorClass::CreateInstance(punkOuter, iid, (void**)&p);
		if (FAILED(hr))
			return hr;

		hr = p->QueryInterface(IID_IApcDual, (void**)&pDual);
		if (SUCCEEDED(hr))
		{
			// dual object must support primary interface
			hr = p->QueryInterface(*piidPrimary, (void**)&pPrimary);
			if (SUCCEEDED(hr))
			{
				// attach to dual object
				hr = pDual->ApcDualAttach(m_pCmdTarget);
				if (SUCCEEDED(hr))
				{
					// success!

					// we keep a pointer to the primary interface, but we
					// don't hold a reference on that pointer
					// this is safe because the dual object will notify us
					// when it is destroyed
					#ifndef _ATL_DEBUG_INTERFACES
						m_pApcPrimary = pPrimary;
						VERIFY(m_pApcPrimary->Release() > 0);
					#else
						// With _ATL_DEBUG_INTERFACES defined, m_pApcPrimary points to a wrapper
						//   which will be destoryed in the release below.
						// We get a pointer to the wrapped object before release.
						m_pApcPrimary= (Primary *)(((_QIThunk *)pPrimary)->pUnk);
						pPrimary->Release();
					#endif 

					// ppv assumes ownership of pv's reference
					*ppv = (void*)p; 

					pDual->Release();
					return NOERROR;
				}
			}
		}

		if (pPrimary)
			pPrimary->Release();
		if (p)
			p->Release();
		if (pDual)
			pDual->Release();
		return hr;
	}

	Primary* m_pApcPrimary;
	CCmdTarget* m_pCmdTarget;
};

/////////////////////////////////////////////////////////////////////////////
// private:
// CApcDualSiteAgg< AtlClass, Primary, piidPrimary>
//
// The m_ApcDualSite member of the CApcDualAgg class is a CApcDualSiteAgg
//
// This class implements the IApcDualSite::GetDual funciton

template <class AtlClass, class Primary, const IID* piidPrimary>
class CApcDualSiteAgg: 
	public CApcDualSite< AtlClass, Primary, piidPrimary >
{
	HRESULT CreateDualIfNeeded()
	{
		static bool fGuard = false;

		if (m_pApcPrimary)
			return NOERROR;

		if (fGuard)
			return E_NOINTERFACE;

		fGuard = true;

		// get pointer to outer unknown for aggregate
		IUnknown* punkOuter = m_pCmdTarget->GetControllingUnknown();
		ASSERT(punkOuter);

		HRESULT hr = ApcDualCreate(punkOuter, IID_IUnknown, (void**)&m_spunkApcDual);

		fGuard = false;

		ASSERT(FAILED(hr) || 0 != m_pApcPrimary);
		ASSERT(FAILED(hr) || 0 != m_spunkApcDual.p);

		return hr;
	}

public:
	CApcDualSiteAgg(CCmdTarget* pCmdTarget)
	: CApcDualSite< AtlClass, Primary, piidPrimary >(pCmdTarget)
	{
	}

	~CApcDualSiteAgg()
	{
		if (m_pApcPrimary)
		{
			m_pCmdTarget->ExternalAddRef();
			m_pCmdTarget->ExternalDisconnect();
		}
	}

	HRESULT InternalQueryInterface(REFIID iid, void** ppv)
	{
		// The MFC object exposes an IApcDualSite interface.
		if (InlineIsEqualGUID(iid, IID_IApcDualSite) || InlineIsEqualUnknown(iid))
		{
			*ppv = static_cast<void*>( static_cast<IApcDualSite*>(this) );
			AddRef();
			return NOERROR;
		}

		HRESULT hr = CreateDualIfNeeded();
		if (FAILED(hr))
			return hr;

		// The MFC object blindly exposes all interfaces of the ATL object.
		return m_spunkApcDual->QueryInterface(iid, ppv);
	}

	STDMETHODIMP GetDual(REFIID iid, void** ppv)
	{
		HRESULT hr = CreateDualIfNeeded();
		if (FAILED(hr))
			return hr;

		return m_pApcPrimary->QueryInterface(iid, ppv);
	}

	STDMETHODIMP Detached()
	{
		m_spunkApcDual.p = NULL;
		CApcDualSite< AtlClass, Primary, piidPrimary >::Detached();
		return NOERROR;
	}

protected:
	CComPtr<IUnknown> m_spunkApcDual;
};

/////////////////////////////////////////////////////////////////////////////
// public:
// CApcDualAgg< MfcBaseClass, AtlClass, Primary, piidPrimary>
//
// CApcDualAgg manages the ATL object as an aggregate of the MFC object.
//
// Any interface exposed by the ATL object take precedence over those of the
// MFC object.
//
// The ATL object is created by the first call to GetInterface for any
// interface except IUnknown
//
// The ATL object is destroyed when the MFC object is destroyed.

template <class MfcBaseClass, class AtlClass, class Primary, const IID* piidPrimary>
class ATL_NO_VTABLE CApcDualAgg : public MfcBaseClass
{
public:
	CApcDualAgg(): m_ApcDualSite(this) {}
	template <class X> CApcDualAgg(X* pX) : MfcBaseClass(pX), m_ApcDualSite(this) {}

	LPUNKNOWN GetInterfaceHook(const void* pvIID)
	{
		IUnknown* pUnk = NULL;
		const IID& iid = *(const IID*) pvIID;

		if (SUCCEEDED(m_ApcDualSite.InternalQueryInterface(iid, (void**)&pUnk)))
		{
			// successful QI bumped the ref count, but this function shouldn't change the ref count
			if (0 == pUnk->Release())
				return NULL;
			else
				return pUnk;
		}

		return MfcBaseClass::GetInterfaceHook(pvIID);
	}

	HRESULT ApcGetPrimary(Primary** ppPrimary)
	{
		return MSAPC::ApcGetPrimary(*this, (void**) ppPrimary);
	}

protected:
	CApcDualSiteAgg<AtlClass, Primary, piidPrimary> m_ApcDualSite;
};

/////////////////////////////////////////////////////////////////////////////
// private:
// CApcDualSiteDyn< AtlClass, Primary, piidPrimary>
//
// The m_ApcDualSite member of the CApcDualDyn class is a CApcDualSiteDyn
//
// This class implements the IApcDualSite::GetDual funciton

template <class AtlClass, class Primary, const IID* piidPrimary>
class CApcDualSiteDyn: 
	public CApcDualSite< AtlClass, Primary, piidPrimary >
{
public:
	CApcDualSiteDyn(CCmdTarget* pCmdTarget)
	: 
		CApcDualSite <AtlClass, Primary, piidPrimary> (pCmdTarget)
	{
	}

	HRESULT InternalQueryInterface(REFIID iid, void** ppv)
	{
		// The MFC object exposes an IApcDualSite interface.
		if (InlineIsEqualGUID(iid, IID_IApcDualSite) || InlineIsEqualUnknown(iid))
		{
			*ppv = static_cast<void*>( static_cast<IApcDualSite*>(this) );
			AddRef();
			return NOERROR;
		}

		return E_NOINTERFACE;
	}

	STDMETHODIMP GetDual(REFIID iid, void** ppv)
	{
		if (!m_pApcPrimary)
			return ApcDualCreate(NULL, iid, ppv);

		return m_pApcPrimary->QueryInterface(iid, ppv);
	}
};

/////////////////////////////////////////////////////////////////////////////
// public:
// CApcDualDyn< MfcBaseClass, AtlClass, Primary, piidPrimary>
//
// CApcDualDyn manages the ATL object as an independent COM object.
//
// The interfaces exposed by the ATL object are completely independent of the
// interfaces of the MFC object.
//
// The ATL object has a lifetime independent of the MFC object.
// The ATL object is created by the first call to ApcGetPrimary().
// The ATL object is destroyed when its reference count becomes zero.
//
// The ATL object can live longer than the MFC object. If the ATL object
// gets a call after the MFC object has died, then code in the macro
// APC_DUAL_PROLOGUE will call the ApcErrorDetached function.

template <class MfcBaseClass, class AtlClass, class Primary, const IID* piidPrimary>
class ATL_NO_VTABLE CApcDualDyn : public MfcBaseClass
{
public:
	CApcDualDyn(): m_ApcDualSite(this) {}
	template <class X> CApcDualDyn(X* pX) : MfcBaseClass(pX), m_ApcDualSite(this) {}

	LPUNKNOWN GetInterfaceHook(const void* pvIID)
	{
		IUnknown* pUnk = NULL;
		const IID& iid = *(const IID*) pvIID;

		if (	(!InlineIsEqualUnknown(iid))
			&&	SUCCEEDED(m_ApcDualSite.InternalQueryInterface(iid, (void**)&pUnk)))
		{
			// successful QI bumped the ref count, but this function shouldn't change the ref count
			VERIFY(pUnk->Release() > 0); 
			return pUnk;
		}

		return MfcBaseClass::GetInterfaceHook(pvIID);
	}

	HRESULT ApcGetPrimary(Primary** ppPrimary)
	{
		return MSAPC::ApcGetPrimary(*this, (void**) ppPrimary);
	}

protected:
	CApcDualSiteDyn<AtlClass, Primary, piidPrimary> m_ApcDualSite;
};

/////////////////////////////////////////////////////////////////////////////

} // namespace MSAPC
#endif // APCDUAL_H_INCLUDED

