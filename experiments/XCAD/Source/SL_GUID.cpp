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
#include "sl_guid.h"

SL_GUID::SL_GUID(void)
:m_guid(GUID_NULL)
{
}

SL_GUID::SL_GUID(const GUID& guid)
:m_guid(guid)
{
}

SL_GUID::~SL_GUID(void)
{
}

SL_GUID& SL_GUID::operator = (const SL_GUID& guid)
{
	m_guid = guid.m_guid;
	return *this;
}

bool SL_GUID::operator == (const SL_GUID& guid) const
{
	return (::IsEqualGUID(m_guid, guid.m_guid) == TRUE);
}

bool SL_GUID::operator == (const GUID& guid) const
{
	return (::IsEqualGUID(m_guid, guid) == TRUE);
}

bool SL_GUID::operator != (const SL_GUID& guid) const
{
	return (::IsEqualGUID(m_guid, guid.m_guid) == FALSE);
}

bool SL_GUID::operator != (const GUID& guid) const
{
	return (::IsEqualGUID(m_guid, guid) == FALSE);
}

bool SL_GUID::operator < (const SL_GUID& guid) const
{
	return false;
}

bool SL_GUID::operator > (const SL_GUID& guid) const
{
	return true;
}
