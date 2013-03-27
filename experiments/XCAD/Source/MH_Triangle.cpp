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


#include "StdAfx.h"
#include ".\mh_triangle.h"
#include "MH_Vector3.h"

MH_Triangle::MH_Triangle(void)
{
}

MH_Triangle::MH_Triangle(const MH_Point3& pt1,
						 const MH_Point3& pt2,
						 const MH_Point3& pt3)
{
	m_pt[0] = pt1;
	m_pt[1] = pt2;
	m_pt[2] = pt3;
}

MH_Triangle::~MH_Triangle(void)
{
}

void MH_Triangle::Set(const MH_Point3& pt1,
					  const MH_Point3& pt2,
					  const MH_Point3& pt3)
{
	m_pt[0] = pt1;
	m_pt[1] = pt2;
	m_pt[2] = pt3;
}

// Get Normal
MH_Vector3 MH_Triangle::GetNormal() const
{
	return (m_pt[0]-m_pt[1])^(m_pt[0]-m_pt[2]);
}