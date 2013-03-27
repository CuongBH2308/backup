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


#include "stdafx.h"
#include "sl_stream.h"
#include "sl_storage.h"

SL_Stream::SL_Stream(SL_Storage* pStorage, const CString& strName)
:m_pStorage(pStorage)
{
	HRESULT hr = pStorage->GetPtr()->OpenStream(CComBSTR(strName), 
		NULL, 
		STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 
		0, &m_spStream);
	if(FAILED(hr) || !m_spStream.p)
	{
		hr = pStorage->GetPtr()->CreateStream(CComBSTR(strName), 
			STGM_CREATE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 
			0, 0, 
			&m_spStream);
		ASSERT(SUCCEEDED(hr));
	}
}

SL_Stream::~SL_Stream(void)
{
}

// Get storage
SL_Storage* SL_Stream::GetStorage() const
{
	return m_pStorage;
}

// m_mObj to this stream
// virtual
HRESULT SL_Stream::Save() const
{
	ASSERT(0);
	return E_NOTIMPL;
}

// Stream to m_mObj
// virtual
HRESULT SL_Stream::Load()
{
	ASSERT(0);
	return E_NOTIMPL;
}

// Seek to position
HRESULT SL_Stream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition) const
{
	ASSERT(m_spStream.p);
	return m_spStream->Seek(dlibMove, dwOrigin, plibNewPosition);
}

// Seek to the beginning of the steam
HRESULT SL_Stream::SeekToBegin() const
{
	ASSERT(m_spStream.p);
	LARGE_INTEGER offset;
	memset(&offset, 0, sizeof(LARGE_INTEGER));
	return m_spStream->Seek(offset, STREAM_SEEK_SET, NULL);
}

// Set the size of the stream
HRESULT SL_Stream::SetSize(const ULARGE_INTEGER& nSize) const
{
	ASSERT(m_spStream.p);
	return m_spStream->SetSize(nSize);
}

// Empty the stream
HRESULT SL_Stream::Empty() const
{
	ULARGE_INTEGER nSize;
	memset(&nSize, 0, sizeof(ULARGE_INTEGER));
	return SetSize(nSize);	
}