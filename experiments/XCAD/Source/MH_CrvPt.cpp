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
#include "mh_crvpt.h"

MH_CrvPt::MH_CrvPt(const MH_Point3& pt3, float fU)
:m_pt3(pt3),
m_fU(fU)
{
}

MH_CrvPt::~MH_CrvPt(void)
{
}

// Transform this object
// virtual 
void MH_CrvPt::Transform(const MH_Matrix44& mtx)
{
	m_pt3.Transform(mtx);
}

// Get the point in the curve
const MH_Point3& MH_CrvPt::GetPoint3() const
{
	return m_pt3;
}

// Get the parameter of the point
float MH_CrvPt::GetU() const
{
	return m_fU;
};