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
#include "sl_storage.h"
#include <comutil.h>
#include "sl_streamobj.h"
#include "sl_streamrecord.h"

#define STORAGE_NAME_PREFIX	_T("SL_Storage_")

// Constructor. Create a file
SL_Storage::SL_Storage(const CString& name)
:m_pStreamRecord(NULL)
{
	CString strName = name;
    if(strName.IsEmpty())
		strName = _T("C:\\temp.dat");

	// Try to open the storage first
	HRESULT hr = ::StgOpenStorageEx(CComBSTR(strName),
		STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
		STGFMT_STORAGE,
		0, NULL, NULL,
		IID_IStorage,
		reinterpret_cast<void**>(&m_spStorage));

	// If the storage is not existing, create a new one
	if(FAILED(hr))
	{
		hr = ::StgCreateStorageEx( CComBSTR(strName),
			STGM_CREATE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE,
			STGFMT_STORAGE,
			0, NULL, NULL,
			IID_IStorage,
			reinterpret_cast<void**>(&m_spStorage));
		ASSERT(SUCCEEDED(hr));
	}
}

// Constructor. Create a storage under pStorage
SL_Storage::SL_Storage(SL_Storage* pStorage, int index)
:m_pStreamRecord(NULL)
{
	const _bstr_t bstrName = _bstr_t(STORAGE_NAME_PREFIX)+_bstr_t(index);
	HRESULT hr = pStorage->m_spStorage->OpenStorage(bstrName, 
		NULL, 
		STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 
		NULL, 0, 
		&m_spStorage);
	if(FAILED(hr) || !m_spStorage.p)
	{
		hr = pStorage->m_spStorage->CreateStorage(bstrName, 
			STGM_CREATE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 
			0, 0, 
			&m_spStorage);
		ASSERT(SUCCEEDED(hr));
	}
}

// De-constructor
SL_Storage::~SL_Storage(void)
{
	if(m_pStreamRecord)
		delete m_pStreamRecord;

	// Delete the storage's child streams
	for(std::map<int, SL_StreamObj*>::const_iterator it = m_mStreamObj.begin(); it != m_mStreamObj.end(); ++it)
		delete it->second;

	// Delete the storage's child storages
	for(std::map<int, SL_Storage*>::const_iterator it = m_mStorage.begin(); it != m_mStorage.end(); ++it)
		delete it->second;
}

// Save the content of the storage
HRESULT SL_Storage::Save() const
{
	if(m_pStreamRecord)
		m_pStreamRecord->Save();

	// Delete the storage's child streams
	for(std::map<int, SL_StreamObj*>::const_iterator it = m_mStreamObj.begin(); it != m_mStreamObj.end(); ++it)
		it->second->Save();

	// Delete the storage's child storages
	for(std::map<int, SL_Storage*>::const_iterator it = m_mStorage.begin(); it != m_mStorage.end(); ++it)
		it->second->Save();

	return S_OK;
}

// Load the required storage
HRESULT SL_Storage::Load()
{
	return S_OK;
}

// Get IStorage
CComPtr<IStorage> SL_Storage::GetPtr() const
{
	return m_spStorage;
}

// Get name of the storage
CString SL_Storage::GetName() const
{
	CString strName;
	ASSERT(m_spStorage);
	STATSTG stg;
	HRESULT hr = m_spStorage->Stat(&stg, STATFLAG_DEFAULT);
	ASSERT(SUCCEEDED(hr));
	if(SUCCEEDED(hr))
	{
		strName = CString(stg.pwcsName);
		::CoTaskMemFree(stg.pwcsName);
	}
	return strName;
}

// Create a storage
// If existing, then open it
SL_Storage* SL_Storage::CreateStorage(int index)
{
	SL_Storage* pStorage = NULL;
	std::map<int, SL_Storage*>::const_iterator it = m_mStorage.find(index);
	if(it != m_mStorage.end())
		pStorage = it->second;
	else
	{
		pStorage = new SL_Storage(this, index);
		m_mStorage[index] = pStorage;
	}

	return pStorage;
}

// Create a stream
// If existing, then open it
SL_StreamObj* SL_Storage::CreateStreamObj(int index)
{
	SL_StreamObj* pStreamObj = NULL;
	std::map<int, SL_StreamObj*>::const_iterator it = m_mStreamObj.find(index);
	if(it != m_mStreamObj.end())
		pStreamObj = it->second;
	else
	{
		pStreamObj = new SL_StreamObj(this, index);
		m_mStreamObj[index] = pStreamObj;
	}

	return pStreamObj;
}

// Create a record stream
// If existing, then open it
SL_StreamRecord* SL_Storage::CreateStreamRecord()
{
	if(!m_pStreamRecord)
		m_pStreamRecord = new SL_StreamRecord(this);

	return m_pStreamRecord;
}

// Get object according to object's id
SL_Obj*	SL_Storage::GetObj(const SL_GUID& guid)
{
	if(!m_pStreamRecord)
		m_pStreamRecord = CreateStreamRecord();

	SL_Obj* pObj = NULL;

	// Which stream can I find the object
	int index;
	bool bOK = m_pStreamRecord->GetRecord(guid, index);
	if(bOK)
	{
		SL_StreamObj* pStreamObj = NULL;
		std::map<int, SL_StreamObj*>::const_iterator it = m_mStreamObj.find(index);
		if(it != m_mStreamObj.end())
			pStreamObj = it->second;
		else
			pStreamObj = CreateStreamObj(index);

		ASSERT(pStreamObj);
		pObj = pStreamObj->GetObj(guid);
	}
	else
	{
		// Look for it in the storage's child storages
		for(std::map<int, SL_Storage*>::const_iterator it = m_mStorage.begin(); it != m_mStorage.end(); ++it)
		{
			pObj = it->second->GetObj(guid);
			if(pObj)
				break;
		}
	}

	return pObj;
}

// Get stream where the object lives
SL_StreamObj* SL_Storage::GetStream(SL_Obj* pObj) const
{
	SL_StreamObj* pStreamObj = NULL;

	// Look for it in the storage's child streams
	for(std::map<int, SL_StreamObj*>::const_iterator it = m_mStreamObj.begin(); it != m_mStreamObj.end(); ++it)
	{
		if(it->second->IsIn(pObj))
			return it->second;
	}

	// Look for it in the storage's child storages
	for(std::map<int, SL_Storage*>::const_iterator it = m_mStorage.begin(); it != m_mStorage.end(); ++it)
	{
		SL_StreamObj* pStreamObj = it->second->GetStream(pObj);
		if(pStreamObj)
			return pStreamObj;
	}
	return NULL;
}