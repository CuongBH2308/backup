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
#include "mh_srfpt.h"

MH_SrfPt::MH_SrfPt()
{
}

MH_SrfPt::MH_SrfPt(const MH_Point3& pt3)
:m_pt3(pt3),
m_fS(0),
m_fT(0)
{
}

MH_SrfPt::MH_SrfPt(const MH_Point3& pt3, float fS, float fT, const MH_Vector3& vNormal)
:m_pt3(pt3),
m_fS(fS),
m_fT(fT),
m_vNormal(vNormal)
{
}

MH_SrfPt::~MH_SrfPt(void)
{
}

// Transform this object
// virtual 
void MH_SrfPt::Transform(const MH_Matrix44& mtx)
{
	m_pt3.Transform(mtx);
}

// Get the point in the curve
const MH_Point3& MH_SrfPt::GetPoint3() const
{
	return m_pt3;
}

// Get the parameter of the point
float MH_SrfPt::GetS() const
{
	return m_fS;
}

// Get the parameter of the point
float MH_SrfPt::GetT() const
{
	return m_fT;
}