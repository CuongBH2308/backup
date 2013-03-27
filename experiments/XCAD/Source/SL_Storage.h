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

//////////////////////////////////////////////////////////////////////////
/*
	SL_Storage
		|__SL_Storage
		|	  |__SL_Stream
		|	  |__...
		|__SL_Stream
		|__...

	Each Storage can contain many children (Storages and Streams)

	Protocol:
	1. The 1st SL_Stream of a SL_Storage is an object record, 
	   which records all objects' info in all SL_Streams of that SL_Storage
    2. The name of the SL_Stream of a SL_Storage should be:
	   StreamRecord, Stream0, Stream1, ...
	3. The name of the SL_Storage of a SL_Storage should be:
	   Storage0, Storage1,...
*/
//////////////////////////////////////////////////////////////////////////
class SL_GUID;
class SL_Obj;
class SL_StreamObj;
class SL_StreamRecord;
class SL_Storage
{
public:
	// Constructor. Create a file
	SL_Storage(const CString& strName);

	// Constructor. Create a storage under pStorage
	SL_Storage(SL_Storage* pStorage, int index);

	// De-constructor
	virtual ~SL_Storage(void);

	// Save the content of the storage
	virtual HRESULT Save() const;

	// Load the required storage
	virtual HRESULT Load();

	// Get IStorage
	CComPtr<IStorage> GetPtr() const;

	// Get name of the storage
	CString			GetName() const;

	// Create a storage
	// If existing, then open it
	SL_Storage*		CreateStorage(int index);

	// Create a stream
	// If existing, then open it
	SL_StreamObj*	CreateStreamObj(int index);

	// Create a record stream
	// If existing, then open it
	SL_StreamRecord*CreateStreamRecord();

	// Get object according to object's id
	SL_Obj*			GetObj(const SL_GUID& guid);

	// Get stream where the object lives
	SL_StreamObj*	GetStream(SL_Obj* pObj) const;
private:
	// IStorage of this Storage
	CComPtr<IStorage>			m_spStorage;

	// The first stream of this storage used to 
	// record all objects' info in all SL_Streams of that SL_Storage
	SL_StreamRecord*			m_pStreamRecord;

	// Storages of this Storage
	std::map<int, SL_Storage*>	m_mStorage;

	// Streams of this Storage
	// _Kty: the index of the stream in the storage
	std::map<int, SL_StreamObj*>m_mStreamObj;
};
