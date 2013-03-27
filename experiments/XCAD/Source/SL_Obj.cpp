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
#include "sl_obj.h"
#include "sl_objcreator.h"
#include "sl_stream.h"

// {67A84C2E-1C45-44c3-8FC4-FD62689E100F}
IMPLEMENT_CREATOR(SL_Obj, 
0x67a84c2e, 0x1c45, 0x44c3, 0x8f, 0xc4, 0xfd, 0x62, 0x68, 0x9e, 0x10, 0xf);

SL_Obj::SL_Obj(void)
:m_nVersion(0)
{
}

SL_Obj::~SL_Obj(void)
{
}

HRESULT SL_Obj::Save(const SL_Stream& stream) const
{
	stream << m_nVersion;
	return S_OK;
}

HRESULT SL_Obj::Load(const SL_Stream& stream)
{
	stream >> m_nVersion;
	return S_OK;
}

// Set GUID of this object
void SL_Obj::SetGUID(const SL_GUID& guid)
{
	m_guid = guid;
}

// Get Id of this object
const SL_GUID& SL_Obj::GetGUID() const
{
	return m_guid;
}