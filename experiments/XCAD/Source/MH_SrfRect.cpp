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
#include "mh_srfrect.h"
#include "mh_crvline.h"
#include "mh_facet.h"
#include "mh_srfpt.h"
#include "mh_util.h"
#include "sl_mm.h"

MH_SrfRect::MH_SrfRect(void)
{
}

MH_SrfRect::MH_SrfRect(const MH_Point3& pt, const MH_Vector3& vNormal, const MH_Vector3& vXAxis)
:m_pt(pt),
m_vNormal(vNormal),
m_vXAxis(vXAxis)
{
}

MH_SrfRect::~MH_SrfRect(void)
{
}

// Triangulate the surface
// The triangles are stored in m_vTriangles
// virtual 
bool MH_SrfRect::Facet(float fTolerance)
{
	Cleanup();

	m_vSrfPt.push_back(m_pt);
	m_vSrfPt.push_back(m_pt+m_vXAxis);
	m_vSrfPt.push_back((m_pt+m_vXAxis*1.41421f).Rotate(m_pt, m_vNormal, PI/4.0f));
	m_vSrfPt.push_back((m_pt+m_vXAxis).Rotate(m_pt, m_vNormal, PI/2.0f));

	SetFacetType(eTriangleFan);
	return true;
}

// Transform this object
// virtual 
void MH_SrfRect::Transform(const MH_Matrix44& mtx)
{
	m_pt.Transform(mtx);
	m_vNormal.Transform(mtx);
	m_vXAxis.Transform(mtx);
}

// Is the surface selected
// virtual 
bool MH_SrfRect::HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const
{
	ASSERT(m_vSrfPt.size() == 4);
	if(m_vSrfPt.size() != 4)
		return false;

	float fTol2 = fTolerance*fTolerance;
	MH_CrvLine line(ray);

	MH_Point3 pt[4];
	pt[0] = m_vSrfPt[0].GetPoint3();
	pt[1] = m_vSrfPt[1].GetPoint3();
	pt[2] = m_vSrfPt[2].GetPoint3();
	pt[3] = m_vSrfPt[3].GetPoint3();

	if( line.DistanceTo2(MH_Facet(pt[0], pt[1], pt[2]), MH_Point3(), ptHit) <= fTol2 )
		return true;
	else if( line.DistanceTo2(MH_Facet(pt[2], pt[3], pt[0]), MH_Point3(), ptHit) <= fTol2 )
		return true;
	return false;
}

// Copy this surface
// virtual 
MH_Srf* MH_SrfRect::Copy()
{
	MH_SrfRect* pSrf = NEW_OBJ(MH_SrfRect, this)();
	*pSrf = *this;
	return pSrf;
}

// Get the nurbs expression
// virtual 
MH_SrfNurbs MH_SrfRect::GetNurbs() const
{
	return MH_SrfNurbs();
}

// Assignment
MH_SrfRect& MH_SrfRect::operator = (const MH_SrfRect& srf)
{
	m_nVersion	= srf.m_nVersion;
	m_pt		= srf.m_pt;
	m_vNormal	= srf.m_vNormal;
	m_vXAxis	= srf.m_vXAxis;
	return *this;
}

const MH_Point3& MH_SrfRect::GetPt() const
{
	return m_pt;
}
const MH_Vector3& MH_SrfRect::GetNormal() const
{
	return m_vNormal;
}
const MH_Vector3& MH_SrfRect::GetXAxis() const
{
	return m_vXAxis;
}