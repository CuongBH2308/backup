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

class SL_GUID
{
public:
	SL_GUID();
	SL_GUID(const GUID& guid);
	virtual ~SL_GUID(void);

	SL_GUID& operator = (const SL_GUID& guid);
	bool operator == (const SL_GUID& guid) const;
	bool operator == (const GUID& guid) const;
	bool operator != (const SL_GUID& guid) const;
	bool operator != (const GUID& guid) const;
	bool operator <  (const SL_GUID& guid) const;
	bool operator >  (const SL_GUID& guid) const;

private:
	GUID m_guid;
};
