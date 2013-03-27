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
#include "sl_streamobj.h"
#include <algorithm>
#include <comutil.h>
#include "sl_manager.h"
#include "sl_obj.h"

#define STREAM_NAME_OBJ_PREFIX _T("SL_StreamObj_")

SL_StreamObj::SL_StreamObj(SL_Storage* pStorage, int index)
:SL_Stream(pStorage, CString(STREAM_NAME_OBJ_PREFIX) + CString(_bstr_t(index).GetBSTR()))
{
}

SL_StreamObj::~SL_StreamObj(void)
{
}

// m_vObj to this stream
HRESULT SL_StreamObj::Save() const
{
	// Seek to the beginning of the stream
	HRESULT hr = SeekToBegin();
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		return hr;

	// Empty the stream
	hr = Empty();
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		return hr;

	std::vector<SL_Obj*, MM_Allocator<SL_Obj*> >::const_iterator it = m_vObj.begin();
	std::vector<SL_Obj*, MM_Allocator<SL_Obj*> >::const_iterator itEnd = m_vObj.end();
	for(; it!=itEnd; ++it)
	{
		// Save guidType
		hr = (*this) << (*it)->GetTypeId();
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			break;

		// Save ObjId
		hr = (*this) << (*it)->GetGUID();
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			break;

		// Save ObjData
		hr = (*it)->Save(*this);
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			break;
	}
	return hr;
}

// Stream to m_vObj
HRESULT SL_StreamObj::Load()
{
	HRESULT hr = SeekToBegin();
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		return hr;

	m_vObj.clear();
	SL_GUID guidType;
	// Load guidType
	while( SUCCEEDED(hr = (*this) >> guidType) )
	{
		// Load ObjId
		SL_GUID objId;
		hr = (*this) >> objId;
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			return hr;

		// Create the object according to the type id
		// The object will be pushed into m_vObj
		SL_Obj* pObj = SL_Manager::Get()->CreateObj(guidType, this);
		ASSERT(pObj);
		if(!pObj)
			return E_FAIL;

		// Load ObjData
		hr = pObj->Load(*this);
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			return hr;

		pObj->SetGUID(objId);
	}
	return hr;
}

// Get object
SL_Obj* SL_StreamObj::GetObj(const SL_GUID& guid)
{
	if(m_vObj.size() == 0)
	{
		HRESULT hr = Load();
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			return NULL;
	}

	std::vector<SL_Obj*, MM_Allocator<SL_Obj*> >::const_iterator it = m_vObj.begin();
	std::vector<SL_Obj*, MM_Allocator<SL_Obj*> >::const_iterator itEnd = m_vObj.end();
	for(; it!=itEnd; ++it)
	{
		if((*it)->GetGUID() == guid)
			return (*it);
	}

	return NULL;
}

// Add pObj into m_vObj
void SL_StreamObj::AddObj(SL_Obj* pObj)
{
	m_vObj.push_back(pObj);
}

// Does the object live in this stream
BOOL SL_StreamObj::IsIn(SL_Obj* pObj) const
{
	std::vector<SL_Obj*, MM_Allocator<SL_Obj*> >::const_iterator it = std::find(m_vObj.begin(), m_vObj.end(), pObj);
	if(it != m_vObj.end())
		return TRUE;
	return FALSE;
}