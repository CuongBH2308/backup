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
#include <map>
#include <vector>

class SL_GUID;
class SL_Obj;
class SL_Storage;
class SL_StreamObj;
class SL_Manager
{
public:
	SL_Manager(void);
	virtual ~SL_Manager(void);

	// Function to get the SL_Manager
	// In one process, there should be only one instance
	static SL_Manager* Get();

	// Create a storage.
	// It should be a file
	// If existing, then open it
	SL_Storage*		CreateStorage(const CString& strName);

	// Get object according to its id
	SL_Obj*			GetObj(const SL_GUID& guid) const;

	// Get stream where the object lives
	SL_StreamObj*	GetStream(SL_Obj* pObj) const;

	// Function to create the object
	typedef SL_Obj* (*PObjCreator)(const SL_GUID& guidType, SL_StreamObj* pStreamObj);

	// Collect the functions used to create the object
	// The function's pointer is stored in m_mObjCreator
	void			RegCreator(const SL_GUID& guidType, const PObjCreator& creator);

	// Create the object according to its class type id
	SL_Obj*			CreateObj(const SL_GUID& guidType, SL_StreamObj* pStreamObj) const;

private:
	// Collector of the functions to create the objects
	// _Kty: the object's type id
	std::map<SL_GUID, PObjCreator> m_mObjCreator;

	// Storages
	// Such as many files are opened
	std::vector<SL_Storage*> m_vStorage;
};
