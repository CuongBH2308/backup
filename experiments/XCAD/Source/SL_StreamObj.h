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
#include <vector>
#include "sl_stream.h"
#include "mm_allocator.h"

//////////////////////////////////////////////////////////////////////////
/*
	data in the stream:
	guidType, ObjId, ObjData
*/
//////////////////////////////////////////////////////////////////////////
class SL_GUID;
class SL_Storage;
class SL_StreamObj : public SL_Stream
{
public:
	SL_StreamObj(SL_Storage* pStorage, int index);
	virtual ~SL_StreamObj(void);

	// m_vObj to this stream
	virtual HRESULT Save() const;

	// Stream to m_vObj
	virtual HRESULT Load();

	// Add pObj into m_vObj
	void AddObj(SL_Obj* pObj);

	// Get object
	SL_Obj* GetObj(const SL_GUID& guid);

	// Does the object live in this stream
	BOOL IsIn(SL_Obj* pObj) const;

private:
	// Cache the objects
	std::vector<SL_Obj*, MM_Allocator<SL_Obj*> > m_vObj;
};
