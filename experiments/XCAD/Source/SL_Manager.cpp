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
#include "sl_manager.h"
#include "sl_guid.h"
#include "sl_storage.h"

SL_Manager::SL_Manager(void)
{
}

SL_Manager::~SL_Manager(void)
{
}

// static
SL_Manager* SL_Manager::Get()
{
	static SL_Manager slMgr;
	return &slMgr;
}

// Create a storage. 
// If existing, then open it
SL_Storage* SL_Manager::CreateStorage(const CString& strName)
{
	// Look for it in the opened storages
	std::vector<SL_Storage*>::const_iterator it = m_vStorage.begin();
	std::vector<SL_Storage*>::const_iterator itEnd = m_vStorage.end();
	for(;it != itEnd; ++it)
	{
		if((*it)->GetName() == strName)
			return (*it);
	}

	// Create a new storage
	SL_Storage* pStorage = new SL_Storage(strName);

	// Record it
	m_vStorage.push_back(pStorage);
	return pStorage;
}

// Get object according to its id
SL_Obj* SL_Manager::GetObj(const SL_GUID& guid) const
{
	SL_Obj* pObj = NULL;

	// Look for it in the opened storages
	std::vector<SL_Storage*>::const_iterator it = m_vStorage.begin();
	std::vector<SL_Storage*>::const_iterator itEnd = m_vStorage.end();
	for(;it != itEnd; ++it)
	{
		pObj = (*it)->GetObj(guid);
		if(pObj)
			break;
	}

	return pObj;
}

// Get stream where the object lives
SL_StreamObj* SL_Manager::GetStream(SL_Obj* pObj) const
{
	// Look for it in the opened storages
	std::vector<SL_Storage*>::const_iterator it = m_vStorage.begin();
	std::vector<SL_Storage*>::const_iterator itEnd = m_vStorage.end();
	for(;it != itEnd; ++it)
	{
		SL_StreamObj* pStreamObj = (*it)->GetStream(pObj);
		if(pStreamObj)
			return pStreamObj;
	}
	return NULL;
}

// Collect the function used to create the object
// The function's pointer is stored in m_mObjCreator
void SL_Manager::RegCreator(const SL_GUID& guidType, const PObjCreator& creator)
{
	m_mObjCreator[guidType] = creator;
}

// Create the object according to its class type
SL_Obj* SL_Manager::CreateObj(const SL_GUID& guidType, SL_StreamObj* pStreamObj) const
{
	std::map<SL_GUID, PObjCreator>::const_iterator it = m_mObjCreator.find(guidType);
	if(it != m_mObjCreator.end())
		return it->second(guidType, pStreamObj);
	return NULL;
}