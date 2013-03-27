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
#include "sl_streamrecord.h"

#define STREAM_NAME_RECORD _T("SL_StreamRecord")

SL_StreamRecord::SL_StreamRecord(SL_Storage* pStorage)
:SL_Stream(pStorage, STREAM_NAME_RECORD)
{
}

SL_StreamRecord::~SL_StreamRecord(void)
{
}

// m_mObj to this stream
// virtual
HRESULT SL_StreamRecord::Save() const
{
	HRESULT hr = SeekToBegin();
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		return hr;

	std::map<SL_GUID, int>::const_iterator it = m_mObj.begin();
	std::map<SL_GUID, int>::const_iterator itEnd = m_mObj.end();
	for(; it!=itEnd; ++it)
	{
		hr = (*this) << it->first;
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			break;

		hr = (*this) << it->second;
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			break;
	}
	return hr;
}

// Stream to m_mObj
// virtual
HRESULT SL_StreamRecord::Load()
{
	HRESULT hr = SeekToBegin();
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		return hr;

	m_mObj.clear();
	SL_GUID guid;
	int index;
	while(SUCCEEDED(hr = (*this) >> guid))
	{
		hr = (*this) >> index;
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			return hr;

		m_mObj[guid] = index;
	}
	return hr;
}

// Get a record of an object whose id is guid
// return false if not find
bool SL_StreamRecord::GetRecord(const SL_GUID& guid, int& index)
{
	if(m_mObj.size() == 0)
	{
		HRESULT hr = Load();
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			return false;
	}

	std::map<SL_GUID, int>::const_iterator it = m_mObj.find(guid);
	if(it != m_mObj.end())
	{
		index = it->second;
		return true;
	}
	return false;
}