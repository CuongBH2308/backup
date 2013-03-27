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
#include "sl_guid.h"
#include "sl_manager.h"
//////////////////////////////////////////////////////////////////////////
/*
SL_Ptr is used to store a "pointer", for example:
class A
{
	Save(SL_Stream&)
	SL_Ptr<B> m_slpB;
}

Then:
A::Save(SL_Stream& stream)
{
	stream << m_slpB;
}

stream << m_slpB is equal to:
stream << m_slpB.m_nId

Once m_slpB is used later:
m_slpB->Fuc(), then it will be translated to:
m_slpB->Load(), m_slpB.m_pThis->Fuc()
*/
//////////////////////////////////////////////////////////////////////////
#define NULL_PTR(cls) SL_Ptr<cls>()

template<class T>
class SL_Ptr
{
	friend class SL_Stream;
public:

	SL_Ptr(void)
	:m_pThis(NULL)	
	{
	}

	SL_Ptr(void* pT)
	:m_pThis(reinterpret_cast<T*> (pT))	
	{
	}

	SL_Ptr(T* pT)
	:m_pThis(pT)
	{
		if(pT)
			m_guid = pT->GetGUID();
	}

	SL_Ptr(const SL_Ptr<T>& pT)
	:m_pThis(pT.m_pThis),
	m_guid(pT.m_guid)
	{

	}

	virtual ~SL_Ptr(void)
	{
	}

	const SL_GUID& GetGUID() const;
	T* GetTarget()	const;
	T* operator->() const;
	T& operator*()	const;

	SL_Ptr<T>& operator = (T* pT);
	SL_Ptr<T>& operator = (const T*& pT);
	SL_Ptr<T>& operator = (const SL_Ptr<T>& pT);

	bool operator == (const SL_Ptr<T>& pT) const;
	bool operator != (const SL_Ptr<T>& pT) const;
	bool operator <  (const SL_Ptr<T>& pT) const;
	bool operator >  (const SL_Ptr<T>& pT) const;

private:
	// Object's Id. Should be unique
	SL_GUID m_guid;

	// Before the object is loaded, it is NULL
	// Once loaded, it points to the object
	T*		m_pThis;
};

template<class T>
inline const SL_GUID& SL_Ptr<T>::GetGUID() const
{
	return m_guid;
}

template<class T>
inline T* SL_Ptr<T>::GetTarget() const
{
	if(m_pThis)
		return m_pThis;

	if(m_guid == GUID_NULL)
		return NULL;

	return dynamic_cast<T*> (SL_Manager::Get()->GetObj(m_guid));
}

template <class T>
inline T* SL_Ptr<T>::operator->() const
{ 
	return GetTarget();
}

template <class T>
inline T& SL_Ptr<T>::operator*() const
{ 	
	return *GetTarget();
}

template<class T>
inline SL_Ptr<T>& SL_Ptr<T>::operator = (T* pT)	
{
	m_pThis = pT; 
	m_guid	= pT->GetGUID();
	return *this;
}

template<class T>
inline SL_Ptr<T>& SL_Ptr<T>::operator = (const T*& pT)	
{
	m_pThis = pT; 
	m_guid	= pT->GetGUID();
	return *this;
}

template<class T>
inline SL_Ptr<T>& SL_Ptr<T>::operator = (const SL_Ptr<T>& pT)
{
	m_pThis = pT.m_pThis; 
	m_guid	= pT.m_guid;
	return *this;
}

template<class T>
inline bool SL_Ptr<T>::operator == (const SL_Ptr<T>& pT) const
{
	if(m_pThis && pT.m_pThis)
		return (m_pThis == pT.m_pThis);

	return (m_guid == pT.m_guid);
}

template<class T>
inline bool SL_Ptr<T>::operator != (const SL_Ptr<T>& pT) const
{
	if(m_pThis && pT.m_pThis)
		return (m_pThis != pT.m_pThis);

	return (m_guid != pT.m_guid);
}

template<class T>
inline bool SL_Ptr<T>::operator < (const SL_Ptr<T>& pT) const
{
	return (m_pThis < pT.GetTarget());
}

template<class T>
inline bool SL_Ptr<T>::operator > (const SL_Ptr<T>& pT) const
{
	return (m_pThis > pT.GetTarget());
}
