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
#include "sl_guid.h"

// Declare the default constructor of thisCls (based on SL_Stream)
#define DECLARE_CREATOR(thisCls) \
	public:\
	thisCls(SL_Stream* pStream);\
	static const SL_GUID& GetTypeId();

// Implement the default constructor of thisCls (based on SL_Stream)
#define IMPLEMENT_CREATOR(thisCls,aaaa,bb,cc,b0,b1,b2,b3,b4,b5,b6,b7) \
	static const SL_ObjCreator<thisCls> s##thisClsCreator; \
	thisCls::thisCls(SL_Stream* pStream){}\
	const SL_GUID& thisCls::GetTypeId()\
	{static const GUID guid = {aaaa,bb,cc,{ b0,b1,b2,b3,b4,b5,b6,b7}}; static const SL_GUID slGUID(guid); return slGUID;}

class SL_Stream;
class SL_Obj
{
public:
	SL_Obj(void);
	virtual ~SL_Obj(void);

	// Declare the default constructor of thisCls (based on SL_Stream)
	DECLARE_CREATOR(SL_Obj);

	// Save this object to the stream
	virtual HRESULT Save(const SL_Stream& stream) const;

	// Load an object from the stream
	virtual HRESULT Load(const SL_Stream& stream);

	// Set GUID of this object
	void SetGUID(const SL_GUID& guid);

	// Get Id of this object
	const SL_GUID& GetGUID() const;

protected:
	SL_GUID	m_guid;
	__int8	m_nVersion;
};
