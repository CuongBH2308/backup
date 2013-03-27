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
#include "mh_srfpolygon.h"
#include "mh_point3.h"
#include "sl_mm.h"

MH_SrfPolygon::MH_SrfPolygon()
{
}

MH_SrfPolygon::MH_SrfPolygon(const MH_Point3Vect& vPt3)
{
	m_vPt3 = vPt3;
}

MH_SrfPolygon::~MH_SrfPolygon(void)
{
}

// Triangulate the surface
// The triangles are stored in m_vTriangles
// virtual 
bool MH_SrfPolygon::Facet(float fTolerance)
{
	return true;
}

// Transform this object
// virtual 
void MH_SrfPolygon::Transform(const MH_Matrix44& mtx)
{
	MH_Point3Vect::iterator it = m_vPt3.begin();
	MH_Point3Vect::iterator itEnd = m_vPt3.end();
	for(; it!=itEnd; ++it)
		(*it).Transform(mtx);
}

// Copy this surface
// virtual 
MH_Srf* MH_SrfPolygon::Copy()
{
	MH_SrfPolygon* pSrf = NEW_OBJ(MH_SrfPolygon, this)();
	*pSrf = *this;
	return pSrf;
}

// Assignment
MH_SrfPolygon& MH_SrfPolygon::operator = (const MH_SrfPolygon& srf)
{
	m_nVersion	= srf.m_nVersion;
	m_vPt3		= srf.m_vPt3;
	return *this;
}