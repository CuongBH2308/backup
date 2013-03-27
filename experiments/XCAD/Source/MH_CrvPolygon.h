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
#include "mh_crv.h"
#include "mh_collect.h"

class MH_CrvPolygon : public MH_Crv
{
public:
	MH_CrvPolygon(const MH_Point3Vect& vPt3);
	virtual ~MH_CrvPolygon(void);
};
