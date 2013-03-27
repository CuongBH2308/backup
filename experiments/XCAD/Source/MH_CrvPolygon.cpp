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
#include "mh_crvpolygon.h"

MH_CrvPolygon::MH_CrvPolygon(const MH_Point3Vect& vPt3)
{
	Cleanup();
	m_vCrvPt.insert(m_vCrvPt.end(), vPt3.begin(), vPt3.end());
	//MH_Point3Vect::const_iterator it = vPt3.begin();
	//MH_Point3Vect::const_iterator itEnd = vPt3.end();
	//for(; it!=itEnd; ++it)
	//{
	//	//m_vCrvPt.push_back(MH_CrvPt)
	//}
}

MH_CrvPolygon::~MH_CrvPolygon(void)
{
}
