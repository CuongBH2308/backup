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
#include "mh_plane.h"
#include "mh_facet.h"

MH_Plane::MH_Plane()
{
}

MH_Plane::MH_Plane(const MH_Point3& pt, const MH_Vector3& vNormal)
:m_pt(pt),
m_vNormal(vNormal)
{
	m_vNormal.Normalize();
}

MH_Plane::MH_Plane(const MH_Facet& fct)
:m_pt(fct.m_pt[0]),
m_vNormal(((fct.m_pt[1] - fct.m_pt[0])^(fct.m_pt[2] - fct.m_pt[1])))
{
	m_vNormal.Normalize();
}

MH_Plane::MH_Plane(const MH_Point3& pt0, const MH_Point3& pt1, const MH_Point3& pt2)
:m_pt(pt0),
m_vNormal((pt1-pt0)^(pt2-pt1))
{
	m_vNormal.Normalize();
}

MH_Plane::~MH_Plane(void)
{
}

// Transform this object
// virtual 
void MH_Plane::Transform(const MH_Matrix44& mtx)
{
	m_pt.Transform(mtx);
	m_vNormal.Transform(mtx);
}

// Get plane's point.
const MH_Point3& MH_Plane::GetPoint() const
{
	return m_pt;
}

// Get plane's normal.
const MH_Vector3& MH_Plane::GetNormal() const
{
	return m_vNormal;
}

// Is the plane valid
bool MH_Plane::IsValid() const
{
	return m_vNormal.IsValid();
}