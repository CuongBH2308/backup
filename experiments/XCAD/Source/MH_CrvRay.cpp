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
#include "mh_crvray.h"
#include "mh_plane.h"
#include "mh_util.h"
#include "sl_mm.h"

MH_CrvRay::MH_CrvRay()
{
}

MH_CrvRay::MH_CrvRay(const MH_Point3& ptFrom, const MH_Vector3& vDir)
:m_ptFrom(ptFrom),
m_vDir(vDir)
{
}

MH_CrvRay::~MH_CrvRay(void)
{
}

const MH_Point3& MH_CrvRay::GetFrom() const
{
	return m_ptFrom;
}

const MH_Vector3& MH_CrvRay::GetDir() const
{
	return m_vDir;
}

void MH_CrvRay::Set(const MH_Point3& ptFrom, const MH_Vector3& vDir)
{
	m_ptFrom = ptFrom;
	m_vDir = vDir;
}

// return false if I'm parallel to the plane
bool MH_CrvRay::CrossPoint(const MH_Plane& plane, MH_Point3* pPt, float* pU) const
{
	const MH_Point3&  ptInPlane = plane.GetPoint();
	const MH_Vector3& vNormal = plane.GetNormal();

	float f = m_vDir*vNormal;
	float fAbs = f>0 ? f:-f;

	// Parallel to the facet
	if(fAbs <= MH_Util::GetTolerance()) return false;

	// m_ptInLine + m_vDir*u is the cross point of the line and the plane
	float u = -((m_ptFrom-ptInPlane)*vNormal)/f;
	if(pU)	*pU		= u;
	if(pPt) *pPt	= m_ptFrom + m_vDir*u;
	return true;
}

// Transform this ray by matrix
void MH_CrvRay::Transform(const MH_Matrix44& mtx)
{
	m_ptFrom.Transform(mtx);
	m_vDir.Transform(mtx);
}

// Copy this curve
// virtual
MH_Crv*	MH_CrvRay::Copy()
{
	MH_CrvRay* pCrv = NEW_OBJ(MH_CrvRay, this)();
	*pCrv = *this;
	return pCrv;
}

// Get the nurbs expression
// virtual
MH_CrvNurbs MH_CrvRay::GetNurbs() const
{
	return MH_CrvNurbs();
}

// Assignment
MH_CrvRay& MH_CrvRay::operator = (const MH_CrvRay& crv)
{
	m_nVersion	= crv.m_nVersion;
	m_ptFrom	= crv.m_ptFrom;
	m_vDir		= crv.m_vDir;
	return *this;
}