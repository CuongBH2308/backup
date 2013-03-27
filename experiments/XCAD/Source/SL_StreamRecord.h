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
#include "sl_stream.h"

//////////////////////////////////////////////////////////////////////////
// SL_StreamRecord: 
// used to record all objects' info in all SL_Streams of that SL_Storage
//////////////////////////////////////////////////////////////////////////
class SL_Storage;
class SL_StreamRecord :	public SL_Stream
{
public:
	SL_StreamRecord(SL_Storage* pStorage);
	virtual ~SL_StreamRecord(void);

	// m_mObj to this stream
	virtual HRESULT Save() const;

	// Stream to m_mObj
	virtual HRESULT Load();

	// Get a record of an object whose id is guid
	// return false if not find
	bool GetRecord(const SL_GUID& guid, int& index);

private:
	// Where can I find the object
	// _Kty:			the object's id
	// int:				the index of the stream in the storage ( >=0 )
	std::map<SL_GUID, int> m_mObj;
};
