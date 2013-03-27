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
#include "sl_ptr.h"
#include "sl_obj.h"

class SL_Storage;
class SL_Stream
{
protected:
	SL_Stream(SL_Storage* pStorage, const CString& strName);
	virtual ~SL_Stream(void);

public:
	// Get storage
	SL_Storage* GetStorage() const;

	// m_mObj to this stream
	virtual HRESULT Save() const;

	// Stream to m_mObj
	virtual HRESULT Load();

	// Seek to position
	HRESULT Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition = NULL) const;

	// Seek to the beginning of the steam
	HRESULT SeekToBegin() const;

	// Set the size of the stream
	HRESULT SetSize(const ULARGE_INTEGER& nSize) const;

	// Empty the stream
	HRESULT Empty() const;

	HRESULT operator << (const SL_Obj& obj)		const;
	HRESULT operator >> (SL_Obj& obj)			const;

	template<class T>
	HRESULT operator << (const SL_Ptr<T>& value)const;

	template<class T>
	HRESULT operator >> (SL_Ptr<T>& value)		const;

	template<class T>
	HRESULT operator << (const T& value)const;

	template<class T>
	HRESULT operator >> (T& value)		const;

private:
	template<class T>
	HRESULT Write(const T& value) const;

	template<class T>
	HRESULT Read(T& value) const;

private:
	// IStream of this stream
	CComPtr<IStream> m_spStream;

	// Pointer to storage
	SL_Storage*	m_pStorage;
};

template<class T>
inline HRESULT SL_Stream::Write(const T& value) const
{
	ASSERT(m_spStream);

	LARGE_INTEGER offset;
	memset(&offset, 0, sizeof(LARGE_INTEGER));

	// Backup current position
	// When failed later, should roll back to this position
	ULARGE_INTEGER ulCurrent;
	HRESULT hr = m_spStream->Seek(offset, STREAM_SEEK_CUR, &ulCurrent);
	ASSERT(SUCCEEDED(hr));

	ULONG cbWritten = 0;
	// Write the size of the object
	__int32 nSize = __int32(sizeof(T));
	hr = m_spStream->Write(&nSize, sizeof(__int32), &cbWritten);
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		goto rollback;

	// Write the object
	hr = m_spStream->Write(&value, nSize, &cbWritten);
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		goto rollback;		

rollback:
	if(FAILED(hr))
	{
		LARGE_INTEGER lCurrent;
		memcpy(&lCurrent, &ulCurrent, sizeof(LARGE_INTEGER));

		// Roll back to previous position
		hr = m_spStream->Seek(lCurrent, STREAM_SEEK_SET, 0);
		ASSERT(SUCCEEDED(hr));
	}
	return hr;
}

template<class T>
inline HRESULT SL_Stream::Read(T& value) const
{
	ASSERT(m_spStream);

	// Read the size of the object
	__int32 nSize = 0;
	HRESULT hr = m_spStream->Read(&nSize, sizeof(__int32), 0);
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		return hr;

	ASSERT(__int32(sizeof(T)) == nSize);
	if(__int32(sizeof(T)) != nSize)
		return E_FAIL;

	hr = m_spStream->Read(&value, nSize, 0);
	ASSERT(SUCCEEDED(hr));
	return hr;
}

inline HRESULT SL_Stream::operator << (const SL_Obj& obj) const
{
	return obj.Save(*this);
}

inline HRESULT SL_Stream::operator >> (SL_Obj& obj) const
{
	return obj.Load(*this);
}

template <class T>
inline HRESULT SL_Stream::operator << (const SL_Ptr<T>& value) const
{
	return Write(value.m_guid);
}

template<class T>
inline HRESULT SL_Stream::operator >> (SL_Ptr<T>& value) const
{
    return Read(value.m_guid);
}

template <class T>
inline HRESULT SL_Stream::operator << (const T& value) const
{
	return Write(value);
}

template<class T>
inline HRESULT SL_Stream::operator >> (T& value) const
{
	return Read(value);
}