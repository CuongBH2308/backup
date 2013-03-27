/* --------------------------------------------------------------------------
 * apcImpl.cpp
 *
 * This file is part of the Microsoft Applications Programability Control (APC)
 * Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
 * Information Contained Herein Is Proprietary and Confidential.
 * -------------------------------------------------------------------------- */
/*
 * Include this file in your application.  Typically, it will be
 * included with #include in your stdafx.cpp, or comparible file
 *
 * Preprocessor modifiers for this file:
 *
 * define APC_USE_STL to use the STL implementation of the list and vector
 *        classes.  The default is to use the CApcVector and CApcList
 *        provided in this file.
 */

#ifdef APC_USE_STL
	#include <vector>
	#include <list>
#else
	#include <new>
#endif

#if !defined(_INC_COMUTIL)
	#include <comutil.h> //for _bstr_t
#endif

/////////////////////////////////////////////////////////////////////////////

namespace MSAPC 
{

/////////////////////////////////////////////////////////////////////////////

#ifdef APCCPP_H_INCLUDED

/////////////////////////////////////////////////////////////////////////////

extern "C" const IID	IID_IApcRegProject			={ 0xdb117191,0xe5fa,0x11d1, { 0x9a,0x70,0x00,0xa0,0x24,0x94,0x1e,0xf0 }};
extern "C" const IID	IID_IApcRegProjItems		={ 0xdb117192,0xe5fa,0x11d1, { 0x9a,0x70,0x00,0xa0,0x24,0x94,0x1e,0xf0 }};
extern "C" const IID	IID_IApcRegProjItem			={ 0xdb117193,0xe5fa,0x11d1, { 0x9a,0x70,0x00,0xa0,0x24,0x94,0x1e,0xf0 }};
extern "C" const IID	IID_IApcRegControls			={ 0xdb117194,0xe5fa,0x11d1, { 0x9a,0x70,0x00,0xa0,0x24,0x94,0x1e,0xf0 }};
extern "C" const IID	IID_IApcRegControl			={ 0xdb117195,0xe5fa,0x11d1, { 0x9a,0x70,0x00,0xa0,0x24,0x94,0x1e,0xf0 }};

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// IApcWrapperCollectionImpl -- 
//
// returns (bstr1 == bstr2)
// this is included to eliminate dependencies on runtime libraries.
//
bool ApcEqualBSTR(const BSTR bstr1, const BSTR bstr2)
{
	if (bstr1 == NULL) 
		return bstr2 ? false : true;

	if (bstr2 == NULL) 
		return false;

	const unsigned int len1 = ::SysStringLen(bstr1);
	const unsigned int len2 = ::SysStringLen(bstr2);

	if (len1 != len2) 
		return false;

	BSTR tbstr1 = bstr1;
	BSTR tbstr2 = bstr2;

	unsigned int len = len1;
	while (len-- > 0) 
		if (*tbstr1++ != *tbstr2++) 
			return false;

	return true;
}

template <class T>
struct IApcWrapperCollectionImpl : public IDispatch
{
	STDMETHODIMP GetTypeInfoCount(UINT* pctinfo)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid)
	{
		if (!rgszNames)
			return DISP_E_EXCEPTION;
		if (cNames > 2)
			return DISP_E_BADPARAMCOUNT;

		HRESULT hr = S_OK;

		BSTR bstrCount = ::SysAllocString(OLESTR("Count"));
		BSTR bstrItem = ::SysAllocString(OLESTR("Item"));
		BSTR bstrName = NULL;

		try
		{
			for(UINT i = 0; i < cNames; i++)
			{
				//CompareString
				bstrName = ::SysAllocString(rgszNames[i]);
				if (ApcEqualBSTR(bstrName, bstrCount))
					rgdispid[i] = DISPID_WRAPPER_COUNT;
				else if (ApcEqualBSTR(bstrName, bstrItem))
					rgdispid[i] = DISPID_WRAPPER_ITEM;
				else
				{
					hr = DISP_E_UNKNOWNNAME;
					rgdispid[i] = DISP_E_UNKNOWNNAME;
				}
				::SysFreeString(bstrName);
				bstrName = NULL;
			}
		}
		catch(...)
		{
			hr = DISP_E_EXCEPTION;
			if (bstrName)
				::SysFreeString(bstrName);
		}
		::SysFreeString(bstrCount);
		::SysFreeString(bstrItem);

		return hr;
	}

	STDMETHODIMP Invoke(DISPID dispID, REFIID riid, LCID lcid, WORD wFlags, 
		DISPPARAMS* pDispParams, VARIANT* pVarResult,
		EXCEPINFO* pExcepInfo, UINT* puArgErr)
	{
		if (!pVarResult)
			return DISP_E_EXCEPTION;
		if (wFlags & ~(DISPATCH_METHOD | DISPATCH_PROPERTYGET))
			return E_INVALIDARG;

		HRESULT hr = DISP_E_MEMBERNOTFOUND;

		switch(dispID)
		{
			case DISPID_WRAPPER_COUNT:
			{
				// check param count
				if (pDispParams && (0 != pDispParams->cArgs))
				{
					if (puArgErr)
						*puArgErr = 0;
					return DISP_E_BADPARAMCOUNT;
				}

				// call method
				T* pT = static_cast<T*>(this);
				long nCount;
				hr = pT->APC_RAW(Count)(&nCount);

				// set return value
				if (SUCCEEDED(hr))
				{
					VariantInit(pVarResult);
					V_VT(pVarResult) = VT_I4;
					V_I4(pVarResult) = nCount;
				}

				break;
			}
			case DISPID_WRAPPER_ITEM:
			{
				// check param count
				if (!pDispParams || (1 != pDispParams->cArgs))
				{
					if (puArgErr)
						*puArgErr = 0;
					return DISP_E_BADPARAMCOUNT;
				}
				// no named args supported
				if (pDispParams->cNamedArgs)
					return DISP_E_NONAMEDARGS;

				// call method
				T* pT = static_cast<T*>(this);
				hr = pT->APC_RAW(Item)(&pDispParams->rgvarg[0], pVarResult);

				break;
			}
		};

		return hr;
	}

private:
	enum
	{
		DISPID_WRAPPER_ITEM = 1,
		DISPID_WRAPPER_COUNT = 2,
	};
};

/////////////////////////////////////////////////////////////////////////////
// CApcList and CApcVector-simple list and vector
//
// would rather be using std::list and std::vector, but this is more 
// portable between compiler versions

#ifdef APC_USE_STL

	//derive CApcList and CApcVector from std::list and std::vector
	template <class T> class CApcVector: public std::vector<T> {};
	template <class T> class CApcList: public std::list<T> {};

#else

	// hand-coded stuff
	template <class T> class CApcVector 
	{
	public:
		typedef int size_type;

		size_type capacity() { return m_pLast - m_pFirst; }
		size_type size() { return m_pEnd - m_pFirst; }
		bool empty() { return 0 == size(); }
		
		CApcVector() : m_pFirst(0), m_pLast(0), m_pEnd(0) {}
		~CApcVector() { clear(); }

		void clear()
		{
			// destruct data
			for (T* p=m_pFirst; p!=m_pLast; p++)
				p->~T();

			// deallocate buffer
			delete[sizeof(T)*capacity()] (char*)m_pFirst;

			m_pEnd = 0;
			m_pLast = 0;
			m_pFirst = 0;
		}

		void reserve(size_type nCap)
		{
			if (capacity() < nCap)
			{
				// allocate new buffer
				T* pFirst = (T*)new char[sizeof(T)*nCap];
				T* pLast = pFirst + size();

				// copy-construct new data from old data
				T* pDest=pFirst;
				T* pSrc=m_pFirst;
				for (; pSrc!=m_pLast; pDest++, pSrc++)
					new((void*)pDest) T(*pSrc);

				// destruct old data
				for (T* p=m_pFirst; p!=m_pLast; p++)
					p->~T();

				// deallocate old buffer
				delete[sizeof(T)*capacity()] (char*)m_pFirst;

				m_pEnd = pFirst + nCap;
				m_pLast = pLast;
				m_pFirst = pFirst; 
			}
		}

		void push_back(const T& t)
		{
			if (size() == capacity())
				reserve(size() + size()/2);

			*m_pLast++ = t;
		}

		T& operator[](size_type i)
		{
			_ASSERTE(i < size());
			return m_pFirst[i];
		}

	private:
		T* m_pFirst;
		T* m_pLast; // last-first=size
		T* m_pEnd;  // end-first=capacity
	};

	template <class T> class CApcList 
	{
		class node;
		friend class node;
	public:
		class iterator;
		friend class iterator;
		typedef T value_type;
		typedef int size_type;

		CApcList(): m_pFirst(NULL), m_pLast(NULL), m_nSize(0) {}
		~CApcList() {clear();}

		iterator begin() { return iterator(m_pFirst); }
		iterator end() { return iterator(); }
		T& front() { return *m_pFirst; }
		T& back() { return *m_pLast; }
		size_type size() { return m_nSize; }
		bool empty() { return 0 == size(); }

		void push_front(const T& t) { new node(t,this,NULL,m_pFirst); }
		void push_back(const T& t) { new node(t,this,m_pLast,NULL); }
		void clear() { while (m_pFirst) delete m_pFirst; }

		iterator erase(iterator it) {
			node* pNext = it.m_pNode->m_pNext;
			delete it.m_pNode;
			return iterator(pNext);
		}

		class iterator {
			friend class CApcList<T>;
			node* m_pNode;
			iterator(node* pNode): m_pNode(pNode) {}
		public:
			iterator(): m_pNode(NULL) {}
			operator T*() { return m_pNode; }
			T* operator->() { return m_pNode; }
			bool operator!() const { return !m_pNode; }
			bool operator==(const iterator& x) { 
				return (!x&&!*this)||(!!x&&!!*this&&*m_pNode==*x); 
			}
			iterator& operator++() {
				_ASSERTE(m_pNode);
				m_pNode = m_pNode->m_pNext;
				return (*this); 
			}
			iterator operator++(int) {
				iterator it = *this;
				_ASSERTE(m_pNode);
				m_pNode = m_pNode->m_pNext;
				return it; 
			}
		};

	private:
		class node: public T { 
			friend class CApcList<T>;
			friend class iterator;

			CApcList<T>* m_pList;
			node* m_pPrev; 
			node* m_pNext; 

			node(const T& t, CApcList<T>* pList, node* pPrev, node* pNext) 
			:
				T(t), m_pList(pList), m_pPrev(pPrev), m_pNext(pNext)
			{
				*(m_pPrev ? &m_pPrev->m_pNext : &m_pList->m_pFirst) = this;
				*(m_pNext ? &m_pNext->m_pPrev : &m_pList->m_pLast) = this;
				m_pList->m_nSize++;
			}

			~node()
			{
				m_pList->m_nSize--;
				*(m_pPrev ? &m_pPrev->m_pNext : &m_pList->m_pFirst) = m_pNext;
				*(m_pNext ? &m_pNext->m_pPrev : &m_pList->m_pLast) = m_pPrev;
			}
		};

		node* m_pFirst;
		node* m_pLast;
		size_type m_nSize;
	};

#endif

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcRegProjItemEntry -- info from regisering one host project item
// CApcRegProjItemList -- list of host project items for one project 

struct CApcRegProjItemEntry
{
	CComQIPtr<IApcRegProjItem, &IID_IApcRegProjItem> m_spReg;
	CComBSTR m_bstrName;
	long m_nID;
	CComPtr<IDispatch> m_disp;
	CComPtr<IApcProjectItem> m_spApc;

	CApcRegProjItemEntry()
	:
		m_nID(-1)
	{
	}

	CApcRegProjItemEntry(IUnknown* punkReg, BSTR bstrName, long nID, IDispatch* pdisp)
	:
		m_spReg(punkReg),
		m_bstrName(bstrName),
		m_nID(nID),
		m_disp(pdisp)
	{
		_ASSERTE(punkReg); // argument required?
		_ASSERTE(m_spReg.p); // QI for IID_IApcRegProjItem failed
	}

	DWORD Cookie() const
	{
		return (DWORD)m_spReg.p;
	}

	bool operator==(const CApcRegProjItemEntry& that) const {
		return Cookie() == that.Cookie();
	}
};

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcRegProjItemList

class CApcRegProjItemList: private CApcList<CApcRegProjItemEntry>
{
	CApcVector<CApcRegProjItemEntry*> m_vecIndex;
	typedef CApcList<CApcRegProjItemEntry> list;

	void clearCache() { m_vecIndex.clear(); }
public:
	typedef list::iterator iterator;
	typedef list::size_type size_type;

	iterator begin() { return list::begin(); }
	iterator end() { return list::end(); }
	size_type size() { return list::size(); }
	void clear() { clearCache(); list::clear(); }

	HRESULT FindByID(long nID, CApcRegProjItemEntry** ppEntry)
	{
		_ASSERTE(nID != -1); // -1 is not a valid value for an ID
		_ASSERTE(ppEntry && !*ppEntry); // should point to NULL on entry

		for (iterator iter = begin(); iter != end(); iter++)
		{
			if (iter->m_nID == nID)
			{
				if (ppEntry)
					*ppEntry = &*iter;
				return NOERROR;
			}
		}

		return S_FALSE;
	}

	HRESULT FindByName(BSTR bstrName, CApcRegProjItemEntry** ppEntry)
	{
		_ASSERTE(bstrName && *bstrName); // bstrName is required arg
		_ASSERTE(ppEntry && !*ppEntry); // should point to NULL on entry

		for (iterator iter = begin(); iter != end(); iter++)
		{
			if (iter->m_bstrName.Length() && ApcEqualBSTR(iter->m_bstrName, bstrName)) //was 0 == wcscmp
			{
				if (ppEntry)
					*ppEntry = &*iter;
				return NOERROR;
			}
		}

		return S_FALSE;
	}

	HRESULT FindByIndex(long index, CApcRegProjItemEntry** ppEntry)
	{
		_ASSERTE(ppEntry && !*ppEntry); // should point to NULL on entry

		if (index < 0 || index >= size())
			return E_INVALIDARG; // index out of range

		if (m_vecIndex.empty())
		{

#pragma warning(disable:4530)
			try { m_vecIndex.reserve(size()); }
			catch(...) { return E_OUTOFMEMORY; }
#pragma warning(default:4530)

			for (iterator iter = begin(); iter != end(); iter++)
				m_vecIndex.push_back(&*iter);
		}

		*ppEntry = m_vecIndex[index];
		return NOERROR;
	}

	HRESULT Add(const CApcRegProjItemEntry& entry, DWORD* pdwCookie)
	{
		_ASSERTE(pdwCookie && !*pdwCookie); // should point to NULL on entry

		clearCache();

#pragma warning(disable:4530)
		try { push_back(entry); }
		catch(...) { return E_OUTOFMEMORY; }
#pragma warning(default:4530)

		if (pdwCookie)
		{
			*pdwCookie = back().Cookie();
			_ASSERTE(*pdwCookie); // should have value on exit
		}

		return NOERROR;
	}

	HRESULT Remove(DWORD dwCookie)
	{
		if (!dwCookie)
			return S_FALSE;

		for (iterator iter = begin(); iter != end(); iter++)
		{
			if (iter->Cookie() == dwCookie)
			{
				iter->m_spReg.Release();
				clearCache();
				erase(iter);
				return NOERROR;
			}
		}

		return E_FAIL;
	}
};

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcRegProjItems -- implements IApcRegProjItems

class CApcRegProjItems
:
	public CApcRegProjItemList,
	public CComCoClass<CApcRegProjItems, NULL>,
	public IApcWrapperCollectionImpl<CApcRegProjItems>,
	public IApcRegProjItems, 
	public CComObjectRootEx< CComObjectThreadModel >
{
	CComPtr<IApcRegProject> m_spRegProject;
	BOOL m_fAfterInitialCheck;

public:
	BEGIN_COM_MAP(CApcRegProjItems)
		COM_INTERFACE_ENTRY_IID(IID_IApcRegProjItems, IApcRegProjItems)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	CApcRegProjItems()
	:
		m_fAfterInitialCheck(FALSE)
	{
	}

	~CApcRegProjItems()
	{
		LoadComplete(FALSE);
	}

	// IApcRegProjItems
	//

	STDMETHOD(Init)(IUnknown* punkProject)
	{
		ApcEntryHR(IApcRegProjItems::Init);
		ApcCallHR(punkProject->QueryInterface(IID_IApcRegProject, (void**)&m_spRegProject));
		ApcReturnHR(NOERROR);
	}																																														

	STDMETHOD(Register)(IUnknown* punkRegProjItem, BSTR bstrName, long nID, IDispatch* pdisp, DWORD* pdwCookie)
	{
		ApcEntryHR(IApcRegProjItems::Register);

		ApcCallHR(CApcRegProjItemList::Add(CApcRegProjItemEntry(punkRegProjItem, bstrName, nID, pdisp), pdwCookie));

		_ASSERTE((!pdwCookie) || *pdwCookie); // cookie should have value on exit

		ApcReturnHR(NOERROR);
	}

	STDMETHOD(Revoke)(DWORD dwCookie)
	{
		ApcEntryHR(IApcRegProjItems::Revoke);
		ApcCallHR(CApcRegProjItemList::Remove(dwCookie));
		ApcReturnHR(NOERROR);
	}

	STDMETHOD(Bind)(IApcProject* pProject)
	{
		ApcEntryHR(IApcRegProjItems::Bind);

		// Attach each registered IApcCppProjItem to its IApcProjectItem
		
		for (iterator iter = begin(); iter != end(); iter++)
		{
			_ASSERTE(!iter->m_spApc.p); // already attached?
			_ASSERTE(iter->m_bstrName.Length() || iter->m_nID != -1); // must specify name or cookie

			if (iter->m_bstrName.Length())
			{
				ApcCallHR(ApcFindProjectItem(pProject, iter->m_bstrName, &iter->m_spApc.p));
			}
			else
			{
				ApcCallHR(ApcFindProjectItem(pProject, iter->m_nID, &iter->m_spApc.p));
			}

			if (iter->m_spReg)
			{
				ApcCallHR(iter->m_spReg->Attach(iter->m_spApc));
			}
		}

		// call FinishedLoadingControls on each IApcProjectItem

		for (iterator iter = begin(); iter != end(); iter++)
		{
			CComPtr<IApcControls> spControls;
			hr = iter->m_spApc->APC_GET(Controls)(&spControls);
			if (SUCCEEDED(hr))
			{
				if (spControls)
					ApcCallHR(spControls->APC_RAW(FinishedLoadingControls)());
			}
			else
			{
				_ASSERTE(hr == APC_E_ONLYDOCITEMS);
			}
		}

		ApcReturnHR(NOERROR);
	}

	STDMETHOD(FinishLoad)()
	{
		ApcEntryHR(IApcRegProjItems::FinishLoading);

		for (iterator iter = begin(); iter != end(); iter++)
		{
			if (iter->m_spReg)
			{
				ApcCallHR(iter->m_spReg->FinishLoad());
			}
		}

		ApcReturnHR(NOERROR);
	}

	STDMETHOD(LoadComplete)(BOOL fGood)
	{
		ApcEntryV(IApcRegProjItems::LoadComplete);

		// notify each CApcProjectItem and CApcControl that we're finished loading
		for (iterator iterThis, iterNext = begin(); iterNext != end(); )
		{
			iterThis = iterNext++;

			// LoadComplete(false) deletes and Releases the smart pointers
			if (iterThis->m_spReg)
			{
				iterThis->m_spReg->LoadComplete(fGood);
				if (fGood)
					iterThis->m_spReg.Release();
			}
			if (fGood)
				iterThis->m_spApc.Release();
		}

		clear();

		return NOERROR;
	}

	// VBA::_Collection interface
	//

	STDMETHODIMP APC_RAW(Item)(VARIANT* pvtIndex, VARIANT* pvtRet)
	{
		ApcEntryHR(CApcRegProjItems::Item);
		CApcRegProjItemEntry* pEntry = NULL;

		if (!pvtIndex)
			ApcReturnHR(E_POINTER);
		if (!pvtRet)
			ApcReturnHR(E_POINTER);

		m_fAfterInitialCheck = TRUE;

		// Q: is index a long?
		if (VT_I4 == V_VT(pvtIndex))
		{
			// Y: lookup by physical index
			ApcCallHR(FindByIndex(V_I4(pvtIndex) - 1, &pEntry));
		}
		else
		{
			// N: index is either a name or an ID value
			
			// convert index to a string
			CComVariant svtBstr;
			ApcCallHR(svtBstr.ChangeType(VT_BSTR, pvtIndex));
			BSTR bstr = V_BSTR(&svtBstr);

			// Q: does string start with a digit?
			if (bstr && *bstr >= L'0' && *bstr <= L'9')
			{
				// Y: assume index is ID expressed as a string
				
				//convert to numeric value, lookup by ID
				CComVariant svtI4;
				ApcCallHR(svtI4.ChangeType(VT_I4, &svtBstr));
				ApcCallHR(FindByID(V_I4(&svtI4), &pEntry));
			}
			else
			{
				// N: assume index is a valid VBA identifier

				// Q: is project item registered?
				ApcCallHR(FindByName(bstr, &pEntry));
				if (NULL == pEntry)
				{
					// N: give client a chance to register it
					ApcCallHR(m_spRegProject->Request(bstr));

					// Q: is project item registered?
					ApcCallHR(FindByName(bstr, &pEntry));
					if (NULL == pEntry)
					{
						// N: then fail the lookup
						ApcReturnHR(E_FAIL); 
					}
				}
			}
		}

		_ASSERTE(pEntry);
		ApcVariantAliasForDispatch vtRet(pEntry->m_disp);
		ApcCallHR(VariantCopy(pvtRet, &vtRet));
		ApcReturnHR(NOERROR);
	}

	STDMETHODIMP APC_RAW(Count)(long* pRet)
	{
		if (!m_fAfterInitialCheck)
			return E_NOTIMPL;

		*pRet = size();
		return S_OK;
	}
}; // class CApcRegProjItems

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcRegControlEntry -- info from regisering one host control
// CApcRegControlList -- list of host controls for one project item

class CApcRegControlEntry
{
public:
	CComQIPtr<IApcRegControl, &IID_IApcRegControl> m_spReg;
	CComBSTR m_bstrName;
	long m_nID;
	CComPtr<IDispatch> m_spHostControl;
	CComPtr<IDispatch> m_spExtender;
	CComPtr<IApcControl> m_spApc;

	CApcRegControlEntry(int=0)
	:
		m_nID(-1)
	{
	}

	CApcRegControlEntry(IUnknown* punkRegControl, BSTR bstrName, long nID, IDispatch* pHostControl, IDispatch* pExtender)
	:
		m_spReg(punkRegControl),
		m_bstrName(bstrName),
		m_nID(nID),
		m_spHostControl(pHostControl),
		m_spExtender(pExtender)
	{
	}

	DWORD Cookie() const
	{
		return (DWORD)m_spReg.p;
	}

	bool operator==(const CApcRegControlEntry& that) const {
		return Cookie() == that.Cookie();
	}
}; // class CApcRegControlEntry

class CApcRegControlList: private CApcList<CApcRegControlEntry>
{
	typedef CApcList<CApcRegControlEntry> list;
	void clearCache() {}
public:
	typedef list::iterator iterator;
	typedef list::size_type size_type;

	iterator begin() { return list::begin(); }
	iterator end() { return list::end(); }
	size_type size() { return list::size(); }
	void clear() { clearCache(); list::clear(); }

	HRESULT Add(const CApcRegControlEntry& entry, DWORD* pdwCookie)
	{
		_ASSERTE(pdwCookie && !*pdwCookie); // must be ptr to NULL

		clearCache();

#pragma warning(disable:4530)
		try { push_back(entry); }
		catch(...) { return E_OUTOFMEMORY; }
#pragma warning(default:4530)

		if (pdwCookie)
		{
			*pdwCookie = back().Cookie();
			_ASSERTE(*pdwCookie); // cookie should have value on exit
		}

		return NOERROR;
	}

	HRESULT Remove(DWORD dwCookie)
	{
		if (!dwCookie)
			return S_FALSE;

		for (iterator iter = begin(); iter != end(); iter++)
		{
			if (iter->Cookie() == dwCookie)
			{
				clearCache();
				erase(iter);
				return NOERROR;
			}
		}

		return E_FAIL;
	}
};

/////////////////////////////////////////////////////////////////////////////
//*private: intended only for internal use.
// CApcRegControls -- implements IApcRegControls

class ATL_NO_VTABLE CApcRegControls
:
	public CApcRegControlList,
	public CComCoClass<CApcRegControls, NULL>,
	public IApcRegControls, 
	public CComObjectRootEx< CComObjectThreadModel >
{
public:
	BEGIN_COM_MAP(CApcRegControls)
		COM_INTERFACE_ENTRY_IID(IID_IApcRegControls, IApcRegControls)
	END_COM_MAP()

	CApcRegControls()
	{
	}

	~CApcRegControls()
	{
		LoadComplete(FALSE);
	}

	// IApcRegControls
	//

	STDMETHOD(Register)(IUnknown* punkRegControl, BSTR bstrName, long nID, IDispatch* pHostControl, IDispatch* pExtender, DWORD* pdwCookie)
	{
		ApcEntryHR(IApcRegControls::Register);

		_ASSERTE(pdwCookie || !punkRegControl); // cookie return requires punkRegControl

		ApcCallHR(CApcRegControlList::Add(CApcRegControlEntry(punkRegControl, bstrName, nID, pHostControl, pExtender), pdwCookie));
		_ASSERTE((!pdwCookie) || *pdwCookie); // cookie should have value on exit

		ApcReturnHR(NOERROR);
	}

	STDMETHOD(Revoke)(DWORD dwCookie)
	{
		ApcEntryHR(IApcRegControls::Revoke);

		ApcCallHR(CApcRegControlList::Remove(dwCookie));
		ApcReturnHR(S_OK);
	}

	STDMETHOD(Bind)(IApcProjectItem* pProjectItem)
	{
		ApcEntryHR(IApcRegControls::Bind);

		// Attach each registered IApcCppControl to its IApcProjectItem
		
		// hook up registered controls
		
		for (iterator iter = begin(); iter != end(); iter++)
		{
			_ASSERTE(iter->m_bstrName.Length() || iter->m_nID != -1); // must specify name or cookie

			if (iter->m_bstrName.Length())
			{
				ApcCallHR(ApcFindControl(pProjectItem, iter->m_bstrName, &iter->m_spApc.p));
			}
			else
			{
				ApcCallHR(ApcFindControl(pProjectItem, iter->m_nID, &iter->m_spApc.p));
			}

			ApcCallHR(iter->m_spApc->APC_PUT(HostControl)( iter->m_spHostControl ));
			if (iter->m_spExtender.p)
				ApcCallHR(iter->m_spApc->APC_PUT(Extender)( iter->m_spExtender ));
			ApcCallHR(iter->m_spReg->Attach(iter->m_spApc));
		}

		ApcReturnHR(NOERROR);
	}

	STDMETHOD(FinishLoad)()
	{
		ApcEntryHR(IApcRegControls::FinishLoading);

		// call FinishedLoadingControls on each IApcProjectItem

		for (iterator iter = begin(); iter != end(); iter++)
		{
			if (iter->m_spReg)
			{
				ApcCallHR(iter->m_spReg->FinishLoad());
				iter->m_spReg.Release();
			}
		}

		ApcReturnHR(NOERROR);
	}

	STDMETHOD(LoadComplete)(BOOL fGood)
	{
		ApcEntryV(IApcRegControls::LoadComplete);

		// notify each CApcProjectItem and CApcControl that we're finished loading
		for (iterator iterThis, iterNext = begin(); iterNext != end(); )
		{
			iterThis = iterNext++;

			if (iterThis->m_spReg)
			{
				iterThis->m_spReg->LoadComplete(fGood);
				if (fGood)
					iterThis->m_spReg.Release();
			}
			if (fGood)
				iterThis->m_spApc.Release();
		}

		clear();

		return NOERROR;
	}


}; // class CApcRegControls

/////////////////////////////////////////////////////////////////////////////

HRESULT ApcCreateRegProjItems(IApcRegProjItems** ppRegProjItems)
{
	return CApcRegProjItems::_CreatorClass::CreateInstance(NULL, IID_IApcRegProjItems, (void**)ppRegProjItems);
}

HRESULT ApcCreateRegControls(IApcRegControls** ppRegControls)
{
	return CApcRegControls::_CreatorClass::CreateInstance(NULL, IID_IApcRegControls, (void**)ppRegControls);
}

/////////////////////////////////////////////////////////////////////////////

HRESULT ApcQueryService(IUnknown* punkContainer, REFGUID guidService, REFIID iid, void** ppv)
{
	ApcEntryHR(::ApcQueryService);

	CComPtr<IServiceProvider> spspContainer;

	ApcCallHR(punkContainer->QueryInterface(IID_IServiceProvider, (void**)&spspContainer));
	ApcCallHR(spspContainer->QueryService(guidService, iid, ppv));

	ApcReturnHR(NOERROR);
}

/////////////////////////////////////////////////////////////////////////////

HRESULT ApcFindProject(IApc* pHost, BSTR bstrRefName, IApcProject** ppProject)
{
	ApcEntryHR(::ApcFindProject);

	_ASSERTE(pHost); // argument required
	_ASSERTE(bstrRefName); // argument required
	_ASSERTE(ppProject); // argument required
	_ASSERTE(!*ppProject); // on entry, should point to a null

	ApcVariantAliasForBstr vtRefName(bstrRefName);
	CComPtr<IApcProjects> spProjects;
	CComPtr<IUnknown> spunkEnumProjects;
	CComPtr<IEnumVARIANT> spEnumProjects;
	CComVariant svtProject;
	CComPtr<IApcProject> spProject;
	CComVariant svtRefName;
	ULONG cFetched = 0;

	// For Each spProject In pHost.Projects ...

	ApcCallHR(pHost->APC_GET(Projects)(&spProjects.p));
	ApcCallHR(spProjects->APC_GET(NewEnum)(&spunkEnumProjects.p));
	ApcCallHR(spunkEnumProjects->QueryInterface(IID_IEnumVARIANT, (void**)&spEnumProjects));

	while (SUCCEEDED(spEnumProjects->Next(1, &svtProject, &cFetched)) && cFetched)
	{
		if (V_VT(&svtProject) != VT_DISPATCH) 
			ApcReturnHR(E_UNEXPECTED);

		_ASSERTE(V_DISPATCH(&svtProject)); // next returned Nothing!
		ApcCallHR(V_DISPATCH(&svtProject)->QueryInterface(APC_IID(IApcProject), (void**)&spProject));

		// If spProject.ReferenceName = bstrReferenceName ...

		_ASSERTE(!V_BSTR(&svtRefName));
		ApcCallHR(spProject->APC_GET(ReferenceName)(&V_BSTR(&svtRefName)));
		V_VT(&svtRefName) = VT_BSTR;

		if (svtRefName == vtRefName)
		{
			// Then Set *ppProject = spProject and Exit Function

			*ppProject = spProject;
			spProject.p = 0;
			ApcReturnHR(S_OK);
		}

		svtRefName.Clear();
		spProject.Release();
		svtProject.Clear();
	}

	ApcReturnHR(E_FAIL);
}

HRESULT ApcFindProjectItem(IApcProject* pProject, long nID, IApcProjectItem** ppProjectItem)
{
	ApcEntryHR(::ApcFindControl);

	_ASSERTE(pProject); // argument required
	_ASSERTE(-1 != nID); // -1 is invalid value for ID
	_ASSERTE(ppProjectItem); // argument required
	_ASSERTE(!*ppProjectItem); // on entry, should point to a null

	CComPtr<IApcProjectItems> spProjectItems;

	// Set ApcFindProjectItem = pProject.ProjectItems.Item(pProject.Host.Parent.ID(nID))

	ApcCallHR(pProject->APC_GET(ProjectItems)(&spProjectItems.p));
	ApcCallHR(spProjectItems->APC_GET(ItemByID)(nID, ppProjectItem));

	ApcReturnHR(NOERROR);
}

HRESULT ApcFindProjectItem(IApcProject* pProject, BSTR bstrName, IApcProjectItem** ppProjectItem)
{
	ApcEntryHR(::ApcFindProjectItem);

	_ASSERTE(pProject); // argument required
	_ASSERTE(bstrName); // argument required
	_ASSERTE(ppProjectItem); // argument required
	_ASSERTE(!*ppProjectItem); // on entry, should point to a null

	CComPtr<IApcProjectItems> spProjectItems;

	// Set ApcFindProjectItem = pProject.ProjectItems.Item(bstrName)

	ApcCallHR(pProject->APC_GET(ProjectItems)(&spProjectItems.p));
	ApcVariantAliasForBstr vtIndex(bstrName);
	ApcCallHR(spProjectItems->APC_GET(Item)(vtIndex, ppProjectItem));

	ApcReturnHR(NOERROR);
}

HRESULT ApcFindControl(IApcProjectItem* pProjectItem, long nID, IApcControl** ppControl)
{
	ApcEntryHR(::ApcFindControl);

	_ASSERTE(pProjectItem); // argument required
	_ASSERTE(-1 != nID); // -1 is invalid value for ID
	_ASSERTE(ppControl); // argument required
	_ASSERTE(!*ppControl); // on entry, should point to a null

	CComPtr<IApcControls> spControls;

	// Set ApcFindControl = pProjectItem.Controls.Item(pProjectItem.Host.Parent.ID(nID))

	ApcCallHR(pProjectItem->APC_GET(Controls)(&spControls.p));
	if (!spControls)
		ApcReturnHR(E_FAIL);
	ApcCallHR(spControls->APC_GET(ItemByID)(nID, ppControl));

	ApcReturnHR(NOERROR);
}

HRESULT ApcFindControl(IApcProjectItem* pProjectItem, BSTR bstrName, IApcControl** ppControl)
{
	ApcEntryHR(::ApcFindControl);

	_ASSERTE(pProjectItem); // argument required
	_ASSERTE(bstrName); // argument required
	_ASSERTE(ppControl); // argument required
	_ASSERTE(!*ppControl); // on entry, should point to a null

	CComPtr<IApcControls> spControls;

	// Set ApcFindControl = pProjectItem.Controls.Item(bstrName)

	ApcCallHR(pProjectItem->APC_GET(Controls)(&spControls.p));
	ApcVariantAliasForBstr vtIndex(bstrName);
	ApcCallHR(spControls->APC_GET(Item)(vtIndex, ppControl));
	ApcReturnHR(NOERROR);
}

/////////////////////////////////////////////////////////////////////////////
//CApcProjectItemPtr

// 
// Accessors
// 

#ifdef APC_MANGLED_ID
	long CApcProjectItemPtr::ApcID() 
#else
	long CApcProjectItemPtr::ID() 
#endif
{ 
	long nID = -1; 
	if (GetApcProjectItem()) 
		GetApcProjectItem()->APC_GET(ID)(&nID);
	return nID;
}


//
// Lifetime
//

CApcProjectItemPtr::CApcProjectItemPtr()
:
	m_dwAdvise(0),
	m_dwRegister(0)
{
}

CApcProjectItemPtr::~CApcProjectItemPtr()
{
}

//
// Operations
//

HRESULT CApcProjectItemPtr::OnDefine(IApcProject* pProject, IDispatch* pdisp, AxProjectItemType projectItemType, BSTR bstrRequestName, IApcProjectItem** ppProjectItem)
{
	ApcEntryHR(CApcProjectItemPtr::OnDefine);
	CComPtr<IApcProjectItems> spProjectItems;
	ApcCallHR(pProject->APC_GET(ProjectItems)(&spProjectItems.p));
	ApcVariantAliasForDispatch vtItem(pdisp);
	switch (projectItemType)
	{
		case axTypeHostProjectItem:
			ApcCallHR(spProjectItems->APC_RAW(AddHostProjectItem)(&vtItem, bstrRequestName, ppProjectItem ));
			break;
		case axTypeHostClass:
			ApcCallHR(spProjectItems->APC_RAW(AddHostClass)(&vtItem, bstrRequestName, ppProjectItem ));
			break;
		case axTypeCodeModule:
			//ApcCallHR(spProjectItems->APC_RAW(AddCodeModule)(bstrRequestName, ppProjectItem ));
			//break;
		case axTypeClassModule:
			//ApcCallHR(spProjectItems->APC_RAW(AddClassModule)(bstrRequestName, ppProjectItem ));
			//break;
		case axTypeDesigner:
		case axTypeOther:
			_ASSERTE(0);
			hr = APC_E_CANT_CREATE_PROJITEM;
	}

	ApcReturnHR(NOERROR);
}

HRESULT CApcProjectItemPtr::OnUndefine()
{
	ApcEntryHR(CApcProjectItemPtr::OnUndefine);

	_ASSERTE(GetApcProjectItem()); // must be attached

	ApcCallHR((*this)->APC_RAW(Delete)());
	ApcReturnHR(NOERROR);
}

HRESULT CApcProjectItemPtr::OnRegister(IApcRegProjItems* pRegProjItems, IDispatch* pdisp, BSTR bstrName, long nID)
{
	ApcEntryHR(CApcProjectItemPtr::OnRegister);

	_ASSERTE(pRegProjItems); // required argument
	_ASSERTE(pdisp); // required argument
	_ASSERTE(bstrName || -1 != nID); // must specify name or ID

	_ASSERTE(!GetApcProjectItem()); // already attached?
	_ASSERTE(m_spProjectItemEvents.p); // derived should have created a sink
	_ASSERTE(!m_dwRegister); // already registered?

	ApcCallHR(pRegProjItems->Register(m_spProjectItemEvents, bstrName, nID, pdisp, &m_dwRegister));

	// success!
	m_spRegProjItems = pRegProjItems;
	ApcReturnHR(NOERROR);
}

HRESULT CApcProjectItemPtr::OnAttach(IApcProjectItem* pProjectItem)
{
	ApcEntryHR(CApcProjectItemPtr::OnAttach);

	_ASSERTE(pProjectItem); // argument is required
	_ASSERTE(!GetApcProjectItem()); // already attached?
	_ASSERTE(m_spProjectItemEvents.p); // derived should have created sink

	_ApcComPtr::OnAttach(pProjectItem);

	ApcCallHR(GetApcProjectItem()->APC_RAW(AdviseProjectItemEvents)(m_spProjectItemEvents, &m_dwAdvise));

	if (m_spRegControls)
	{
		ApcCallHR(m_spRegControls->Bind(pProjectItem));
	}

	// success!
	ApcReturnHR(NOERROR);
}

void CApcProjectItemPtr::OnDetach()
{
	ApcEntryV(CApcProjectItemPtr::OnDetach);

	if (m_spRegControls)
	{
		m_spRegControls->LoadComplete(FALSE);
		m_spRegControls.Release();
	}

	if (m_spRegProjItems)
	{
		m_spRegProjItems->Revoke(m_dwRegister);
		m_spRegProjItems.Release();
		m_dwRegister = 0;
	}

	if (GetApcProjectItem())
	{
		if (m_dwAdvise)
		{
			GetApcProjectItem()->APC_RAW(UnadviseProjectItemEvents)(m_dwAdvise);
			m_dwAdvise = 0;
		}
	}

	m_spProjectItemEvents.Release();
	_ApcComPtr::OnDetach();
}

HRESULT CApcProjectItemPtr::OnFinishLoad()
{
	ApcEntryHR(CApcProjectItemPtr::OnFinishLoad);
	_ASSERTE(GetApcRegControls());
	ApcCallHR(GetApcRegControls()->FinishLoad());
	ApcReturnHR(NOERROR);
}

void CApcProjectItemPtr::OnLoadComplete()
{
	ApcEntryV(CApcProjectItemPtr::OnLoadComplete);

	if (m_spRegControls)
	{
		m_spRegControls->LoadComplete(TRUE);
		m_spRegControls.Release();
	}

	m_spRegProjItems.Release();
	m_dwRegister = 0;
}

HRESULT CApcProjectItemPtr::RegisterControl(BSTR bstrName, IDispatch* pHostControl, IDispatch* pExtender)
{
	ApcEntryHR(CApcProjectItemPtr::RegisterControl);
	_ASSERTE(GetApcRegControls()); 
	ApcCallHR(GetApcRegControls()->Register(NULL, bstrName, -1, pHostControl, pExtender, NULL));
	ApcReturnHR(NOERROR);
}

HRESULT CApcProjectItemPtr::RegisterControl(long nID, IDispatch* pHostControl, IDispatch* pExtender)
{
	ApcEntryHR(CApcProjectItemPtr::RegisterControl);
	_ASSERTE(GetApcRegControls()); 
	ApcCallHR(GetApcRegControls()->Register(NULL, NULL, nID, pHostControl, pExtender, NULL));
	ApcReturnHR(NOERROR);
}

/////////////////////////////////////////////////////////////////////////////
// CApcControlPtr

// 
// Accessors
// 

#ifdef APC_MANGLED_ID
	long CApcControlPtr::ApcID() 
#else
	long CApcControlPtr::ID() 
#endif
{ 
	long nID = -1; 
	if (GetApcControl()) 
		GetApcControl()->APC_GET(ID)(&nID);
	return nID;
}

//
// Lifetime
//

CApcControlPtr::CApcControlPtr()
: 
	m_dwRegister(0),
	m_dwAdvise(0)
{
}

CApcControlPtr::~CApcControlPtr()
{
}

//
// Operations
//

HRESULT CApcControlPtr::OnDefine(IApcProjectItem* pProjectItem, IDispatch* pHostControl, AxControlFlag controlFlag, IDispatch* pExtender, IApcControl** ppControl)
{
	ApcEntryHR(CApcControlPtr::OnDefine);
	
	_ASSERTE(!GetApcControl()); // already attached?

	CComPtr<IApcControl> spControl;
	CComPtr<IApcControls> spControls;
	ApcCallHR(pProjectItem->APC_GET(Controls)( &spControls.p ));
	AxControlFlag flags = controlFlag;
	ApcCallHR(spControls->APC_RAW(Add)( pHostControl, pExtender, flags, ppControl ));
	ApcReturnHR(NOERROR);
}

HRESULT CApcControlPtr::OnUndefine()
{
	ApcEntryHR(CApcControlPtr::OnUndefine);

	_ASSERTE(GetApcControl()); // must be attached

	ApcCallHR((*this)->APC_RAW(Delete)());
	ApcReturnHR(NOERROR);
}

HRESULT CApcControlPtr::OnRegister(IApcRegControls* pRegs, BSTR bstrName, long nID, IDispatch* pHostControl, IDispatch* pExtender)
{
	ApcEntryHR(CApcControlPtr::OnRegister);

	_ASSERTE(pRegs); // required argument
	_ASSERTE(bstrName || nID != -1); // required argument
	_ASSERTE(pHostControl); // required argument

	_ASSERTE(!GetApcControl()); // already attached?
	_ASSERTE(m_spControlEvents.p); // derived should have set a value
	_ASSERTE(!m_dwRegister); // already registered?

	ApcCallHR(pRegs->Register(m_spControlEvents, bstrName, nID, pHostControl, pExtender, &m_dwRegister ));

	// success!
	m_spRegs = pRegs;
	ApcReturnHR(NOERROR);
}

HRESULT CApcControlPtr::OnAttach(IApcControl* pControl)
{
	ApcEntryHR(CApcControlPtr::OnAttach);

	_ASSERTE(pControl); // argument is required
	_ASSERTE(!GetApcControl()); // already attached?
	_ASSERTE(m_spControlEvents.p); // derived should have created this

	ApcCallHR(pControl->APC_RAW(AdviseControlEvents)(m_spControlEvents, &m_dwAdvise ));

	// success!
	_ApcComPtr::OnAttach(pControl);
	ApcReturnHR(NOERROR);
}

void CApcControlPtr::OnDetach()
{
	ApcEntryV(CApcControlPtr::OnDetach);

	if (GetApcControl() && m_dwAdvise)
	{
		GetApcControl()->APC_RAW(UnadviseControlEvents)(m_dwAdvise);
		m_dwAdvise = 0;
	}

	if (m_spRegs)
	{
		m_spRegs->Revoke(m_dwRegister);
		m_spRegs.Release();
		m_dwRegister = 0;
	}

	m_spControlEvents.Release();
	_ApcComPtr::OnDetach();
}

/////////////////////////////////////////////////////////////////////////////

HRESULT ApcApplyPropertyMap(IApcControl* pControl, const APC_PROPERTY_MAP* pmap)
{
	ApcEntryHR(::ApcApplyPropertyMap);

	if (pmap)
	{
		CComPtr<IApcCategories> spCategories;
		hr = pControl->APC_GET(Categories)(&spCategories);
		if (spCategories)
		{
			int i = 0;
			while(pmap[i].m_apcreserved == 0)
			{
				CComPtr<IApcCategory> spCat;
				hr = spCategories->APC_RAW(Add)(CComBSTR(pmap[i].m_name), pmap[i].m_propcat, CComBSTR(pmap[i].m_user), &spCat);

				#ifdef _DEBUG
					if (APC_E_UNKNOWNPROPERTYNAME == hr) {
						OutputDebugString(_T("Unknown property name in APC_PROPCAT macro: "));
						OutputDebugString(pmap[i].m_name);
						OutputDebugString(_T("\r\n"));
					}
					else
					{
						_ASSERT(SUCCEEDED(hr));
					}
				#endif

				pmap[i].m_name;
				i++;
			}
			_ASSERTE(pmap[i].m_apcreserved == -1);
		}
	}

	ApcReturnHR(NOERROR);
}

HRESULT ApcFireEvent(IUnknown* punk, REFIID iid, DISPID dispid, DISPPARAMS* pDispParams /*= NULL*/, VARIANT* pVarResult /*= NULL*/)
{
	ApcEntryHR(::ApcFireEvent);

	CComPtr<IConnectionPointContainer> spCPC;
	ApcCallHR(punk->QueryInterface(IID_IConnectionPointContainer, (void**)&spCPC));

	// get connection point for source interface
	CComPtr<IConnectionPoint> spCP;
	ApcCallHR(spCPC->FindConnectionPoint(iid, &spCP));

	// get connections for
	CComPtr<IEnumConnections> spEnum;
	ApcCallHR(spCP->EnumConnections(&spEnum));

	// prepare arguments to Invoke
	UINT err = 0;
	DISPPARAMS dispParamsDefault = { NULL, NULL, 0, 0 };
	if (NULL == pDispParams)
		pDispParams = &dispParamsDefault;

	// iterate over each event sink
	CONNECTDATA item;
	ULONG cFetched = 0;
	CComVariant varResult;
	BOOL fResultCopied = FALSE;

	while (SUCCEEDED(spEnum->Next(1, &item, &cFetched)) && cFetched)
	{
		// QI the sink for IDispatch
		CComQIPtr<IDispatch, &IID_IDispatch> spDisp(item.pUnk);
		item.pUnk->Release();

		if (!spDisp)
		{
			_ASSERTE(FALSE);	// event sink should support IDispatch
			continue;		// ignore this event sink
		}

		// Clear previous result, ignoring errors
#pragma warning(disable:4530)
		try { varResult.Clear(); } 
		catch (...) { }
#pragma warning(default:4530)

		// Invoke the event handler in the event sink, ignoring errors
#pragma warning(disable:4530)
		try
		{
			hr = spDisp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, pDispParams, &varResult, NULL, &err);
		}
		catch (...) 
		{ 
		}
#pragma warning(default:4530)

		if (pVarResult)
		{
			if ((V_VT(&varResult) != VT_NULL) && (V_VT(&varResult) != VT_EMPTY))
			{
				ApcCallHR(VariantCopy(pVarResult, &varResult));
				fResultCopied = TRUE;
			}
		}
	}

	if (pVarResult && !fResultCopied)
		ApcCallHR(VariantCopy(pVarResult, &varResult));

	ApcReturnHR(NOERROR);
}

#endif //APCCPP_H_INCLUDED

/////////////////////////////////////////////////////////////////////////////

#ifdef APCMFC_H_INCLUDED

extern "C" const IID	IID_IApcDual				={ 0xdb40fa30,0x928f,0x11d1, { 0x9a,0x5a,0x00,0xa0,0x24,0x94,0x1e,0xf0 }};
extern "C" const IID	IID_IApcDualSite			={ 0xdb40fa31,0x928f,0x11d1, { 0x9a,0x5a,0x00,0xa0,0x24,0x94,0x1e,0xf0 }};

IApc* g_pApcHost = NULL;

void AFXAPI ApcOleTermOrFreeLib(BOOL bTerm, BOOL bJustRevoke)
{
	try
	{
		AfxOleTermOrFreeLib(bTerm, bJustRevoke);
	}
	catch (...)
	{
	}
}

void ApcSerializeGUID(CArchive& ar, GUID& guid)
{
	int	nByte;

	if (ar.IsStoring())
	{
		ar << guid.Data1;
		ar << guid.Data2;
		ar << guid.Data3;

		for (nByte = 0; nByte < 8; nByte++) 
		{
			ar << guid.Data4[nByte];
		}
	}
	else
	{
		ar >> guid.Data1;
		ar >> guid.Data2;
		ar >> guid.Data3;

		for (nByte = 0; nByte < 8; nByte++) 
		{
			ar >> guid.Data4[nByte];
		}
	}
}

const AFX_INTERFACEMAP_ENTRY* ApcGetEntryFromIID(const void* iid, 
	const AFX_INTERFACEMAP* pMap)
{
	ASSERT(pMap != NULL);

	// walk the interface map to find the matching IID
	do
	{
		const AFX_INTERFACEMAP_ENTRY* pEntry = pMap->pEntry;
		ASSERT(pEntry != NULL);
		while (pEntry->piid != NULL)
		{
			if (((DWORD*)pEntry->piid)[0] == ((DWORD*)iid)[0] &&
				((DWORD*)pEntry->piid)[1] == ((DWORD*)iid)[1] &&
				((DWORD*)pEntry->piid)[2] == ((DWORD*)iid)[2] &&
				((DWORD*)pEntry->piid)[3] == ((DWORD*)iid)[3])
			{
				return pEntry;
			}

			// entry did not match -- keep looking
			++pEntry;
		}
#ifdef _AFXDLL
	} while ((pMap = (*pMap->pfnGetBaseMap)()) != NULL);
#else
	} while ((pMap = pMap->pBaseMap) != NULL);
#endif

	return NULL;
}

LPUNKNOWN ApcGetPtrFromEntry(const void* pThis, 
	const AFX_INTERFACEMAP_ENTRY* pEntry)
{
	if (!pEntry)
		return NULL;

	// check INTERFACE_ENTRY macro
	LPUNKNOWN lpUnk = ((LPUNKNOWN)((BYTE*)pThis + pEntry->nOffset));

	// check vtable pointer (can be NULL)
	if (*(DWORD*)lpUnk != 0)
		return lpUnk;

	return NULL;
}

//
// public access to protected members required for to WORKAROUND 
// various MFC coding errors.
//
class COleDocumentFriend : public COleDocument
{
public:
	//
	// WORKAROUND 1: COleClientItem::Draw improper call to IViewObject::Draw
	//
	DVTARGETDEVICE* GetPTD() { return m_ptd; }
	//
	// WORKAROUND 2: COleClientItem::Serialize improper sequencing of OleSave and SaveCompleted
	//
	BOOL GetSameAsLoad() { return m_bSameAsLoad; }
};

BOOL ApcGetSameAsLoad(COleDocument* pDoc)
{
	return ((COleDocumentFriend*) pDoc)->GetSameAsLoad();
}

DVTARGETDEVICE* ApcGetTargetDevice(COleDocument* pDoc)
{
	return ((COleDocumentFriend*) pDoc)->GetPTD();
}

BOOL ApcGetEmbedded(COleServerDoc* pThis)
{
	return pThis->m_bEmbedded; //Happens to be public in MFC
}

BOOL ApcGetEmbedded(CDocument* pThis)
{
	return FALSE;
}

class COleServerDocFriend : public COleServerDoc
{
public:
	void OnSaveEmbeddingFriend(LPSTORAGE pStgSave) { COleServerDoc::OnSaveEmbedding(pStgSave);}
};

void ApcOnSaveEmbedded(COleServerDoc* pThis, LPSTORAGE pStgSave)
{
	((COleServerDocFriend*)pThis)->OnSaveEmbeddingFriend(pStgSave); //Happens to be protected in MFC
	return;
}

void ApcOnSaveEmbedded(CDocument* pThis, LPSTORAGE pStgSave)
{
	return;
}

void ApcNotifySaved(COleServerDoc* pThis)
{
	pThis->NotifySaved();	//Happens to be public in MFC
	return;
}

void ApcNotifySaved(CDocument* pThis)
{
	return;
}

#ifndef _UNICODE

//the follwing code is here to workaround an MFC bug

//it shows up with VBA6 using MSO 10. The dialogs that
//come from MSO 10 are UNICODE windows on UNICODE systems
//but if the host app is ANSI MFC screws up the message handling.

//MFC installs a WindowsHook that hooks the creation of all windows in the
//process, and then replaces the window procedure to do special processing.
//Unfortuanately they assume that all the windows are ANSI windows, and so
//only call the ANSI APIs. This results in the system thinking that the MSO
//dialogs are ANSI windows, so it passes ANSI messages to the MFC wndproc.
//MFC then passes them on to the original UNICODE MSO wndproc, resulting 
//in various problems

//the workaround is to install another windows hook ahead of the MFC one.
//this hook saves both the original wndproc and the MFC one, and replaces the wndproc
//with yet another one. In the implementation of the hookproc and wndproc we
//specifically call the appropriate ANSI/UNICODE APIs.

HHOOK g_hHookOldCbtFilter = NULL;
WNDPROC g_wndprocOld = NULL;
WNDPROC g_wndprocOriginal = NULL;
static const char szMSODlgWndClass[] = "bosa_sdm_Mso96";
LRESULT CALLBACK ApcActivationWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

extern "C" typedef LONG (WINAPI *SETWINDOWLONGW)(HWND hWnd, int nIndex, LONG dwNewLong);
extern "C" typedef LRESULT (WINAPI *CALLWINDOWPROCW)(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK ApcCBTWindowsHook(int code, WPARAM wParam, LPARAM lParam)
{
	if (code != HCBT_CREATEWND)
	{
		// wait for HCBT_CREATEWND just pass others on...
		return CallNextHookEx(g_hHookOldCbtFilter, code,
			wParam, lParam);
	}

	
	ASSERT(lParam != NULL);
	LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;
	ASSERT(lpcs != NULL);

	//next check the class. If this is the MSO windows class that is Unicode and
	//we know about, we have to reset the wndproc to make the window unicode again

	if(IsWindowUnicode((HWND)wParam) && 
		NULL != (((DWORD)(lpcs->lpszClass)) & 0xFFFF0000) && 
		!strcmp(lpcs->lpszClass, szMSODlgWndClass))
	{
		//do our work here
		//link up to the wide API we need
        SETWINDOWLONGW SetWindowLongWAPI = NULL;
		HMODULE hMod = GetModuleHandle("User32.dll");

		ASSERT(hMod);

	    SetWindowLongWAPI = (SETWINDOWLONGW)GetProcAddress(hMod, "SetWindowLongW");

		ASSERT(SetWindowLongWAPI);

		//now save out the current wndproc
		//this is the original

		//there is only going to be one of these dialogs up at a time
		//so we can use a global for the old hwnd
		
		// it should always be NULL when we get here
		ASSERT(g_wndprocOriginal == NULL);
		g_wndprocOriginal = (WNDPROC)GetWindowLong((HWND)wParam, GWL_WNDPROC);

		//then call the next hook, as it will change the
		//wnd proc and screw it up
        LRESULT lRes = CallNextHookEx(g_hHookOldCbtFilter, code, wParam, lParam);


		
		ASSERT(g_wndprocOld == NULL);

		//now set our wndproc using W to make it a unicode window again
		g_wndprocOld = (WNDPROC)(*SetWindowLongWAPI)((HWND)wParam, GWL_WNDPROC, (LONG)ApcActivationWndProc);

		return lRes;

	}

	return CallNextHookEx(g_hHookOldCbtFilter, code,
			wParam, lParam);

}

LRESULT CALLBACK ApcActivationWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	//Short circuit MFC, they won't care about these windows
	//and they screw it up anyway.

    static CALLWINDOWPROCW CallWindowProcWAPI = NULL;
	
	if(CallWindowProcWAPI == NULL)
	{
		//link in the wide function we need
		HMODULE hMod = GetModuleHandle("User32.dll");

		ASSERT(hMod);

	    CallWindowProcWAPI = (CALLWINDOWPROCW)GetProcAddress(hMod, "CallWindowProcW");

		ASSERT(CallWindowProcWAPI);
	}

	if(nMsg == WM_NCDESTROY)
	{
		SetWindowLongA(hWnd, GWL_WNDPROC, (LONG)g_wndprocOld);
		LRESULT lRes = CallWindowProcA(g_wndprocOld, hWnd, nMsg, wParam, lParam);
		g_wndprocOld = NULL;
		g_wndprocOriginal = NULL;
		return lRes;
	}

	return (*CallWindowProcWAPI)(g_wndprocOriginal, hWnd, nMsg, wParam, lParam);
}

#endif //!(UNICODE)

#endif //APCMFC_H_INCLUDED

/////////////////////////////////////////////////////////////////////////////

} // namespace MSAPC

/////////////////////////////////////////////////////////////////////////////

