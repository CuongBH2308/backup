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
#include "mh_crvline.h"
#include "mh_crvray.h"
#include "mh_facet.h"
#include "mh_plane.h"
#include "mh_util.h"
#include "sl_mm.h"

MH_CrvLine::MH_CrvLine(void)
{
}

MH_CrvLine::MH_CrvLine(const MH_Point3& ptInLine, const MH_Vector3& vDir)
:m_ptInLine(ptInLine),
m_vDir(vDir)
{
}

MH_CrvLine::MH_CrvLine(const MH_CrvRay& ray)
:m_ptInLine(ray.GetFrom()),
m_vDir(ray.GetDir())
{
}

MH_CrvLine::MH_CrvLine(const MH_CrvLineSeg& lineSeg)
:m_ptInLine(lineSeg.GetFrom()),
m_vDir(lineSeg.GetTo()-lineSeg.GetFrom())
{
}

MH_CrvLine::~MH_CrvLine(void)
{
}

// Transform this lineseg's points
// pt = mtx * [m_f[0], m_f[1], m_f[2], 1]t
void MH_CrvLine::Transform(const MH_Matrix44& mtx)
{
	m_ptInLine.Transform(mtx);
	m_vDir.Transform(mtx);
}

// Copy this curve
// virtual
MH_Crv*	MH_CrvLine::Copy()
{
	MH_CrvLine* pCrv = NEW_OBJ(MH_CrvLine, this)();
	*pCrv = *this;
	return pCrv;
}

// Get the nurbs expression
// virtual 
MH_CrvNurbs MH_CrvLine::GetNurbs() const
{
	return MH_CrvNurbs();
}

// Assignment
MH_CrvLine& MH_CrvLine::operator = (const MH_CrvLine& crv)
{
	m_nVersion	= crv.m_nVersion;
	m_ptInLine	= crv.m_ptInLine;
	m_vDir		= crv.m_vDir;
	return *this;
}

const MH_Point3& MH_CrvLine::GetPtInLine() const
{
	return m_ptInLine;
}

const MH_Vector3& MH_CrvLine::GetDir() const
{
	return m_vDir;
}

bool  MH_CrvLine::CrossPoint(const MH_Plane& plane, MH_Point3* pPt, float* pU) const
{
	const MH_Point3&  ptInPlane = plane.GetPoint();
	const MH_Vector3& vNormal = plane.GetNormal();

	float f = m_vDir*vNormal;
	float fAbs = f>0 ? f:-f;

	// Parallel to the facet
	if(fAbs <= MH_Util::GetTolerance()) return false;

	// m_ptInLine + m_vDir*u is the cross point of the line and the plane
	float u = -((m_ptInLine-ptInPlane)*vNormal)/f;
	if(pU)	*pU		= u;
	if(pPt) *pPt	= m_ptInLine + m_vDir*u;
	return true;
}

float MH_CrvLine::DistanceTo2(const MH_CrvLine& line, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const
{
	const MH_Vector3& v2 = line.GetDir();
	
	// Parallel to each other
	if(!(m_vDir^v2).IsValid())
	{
		ptCrossThis = m_ptInLine;
		return ptCrossThis.DistanceTo2(line, ptCrossThat);
	}
	const MH_Point3& pt2 = line.GetPtInLine();

	float f11 = m_vDir*m_vDir;
	float f22 = v2*v2;
	float f12 = m_vDir*v2;
	float f1 = (m_ptInLine-pt2)*m_vDir;
	float f2 = (m_ptInLine-pt2)*v2;

	ptCrossThis = m_ptInLine + m_vDir * ((f1*f22-f2*f12)/(f12*f12-f11*f22));
	ptCrossThat = pt2 + v2 * ((f1*f12-f2*f11)/(f12*f12-f11*f22));

	return ptCrossThis.DistanceTo2(ptCrossThat);
}

float MH_CrvLine::DistanceTo2(const MH_CrvLineSeg& lineSeg, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const
{
	float fDist2 = DistanceTo2(MH_CrvLine(lineSeg), ptCrossThis, ptCrossThat);
	int nRegion = 0;
	lineSeg.CheckPoint(ptCrossThat, &nRegion);

	switch(nRegion)
	{
	case 0:
		return fDist2;
	case 1:
		ptCrossThat = lineSeg.GetFrom();
		break;
	case 2:
		ptCrossThat = lineSeg.GetTo();
		break;
	default:
		ASSERT(0);
		break;
	}

	return ptCrossThis.DistanceTo2(ptCrossThat);
}

/************************************************************************/
/*        \ 4/
		   \/p2
		   /\
	 <5>  /  \  <3>
		 /    \  
	 ---/------\---
   <6> /p  <1>  \p1  <2>

p1 = p + v1*s
p2 = p1 + v2*t

All points in the triangle can be expressed as:
p + v1*s + v2*s*t. 0<=s<=1, 0<=t<=1

Assuming p0 is outside this triangle in 3d space, then the distance to this triangle is
s^2*t^2*(v2*v2) + 2*s^2*t*(v1*v2) + s^2*(v1*v1) + 2*s*t*(B*v2) + 2*s*(B*v1) + (B*B)
where B = p-p0.

Then the question become: get the min value of above expression.

region <1>: 0<=s<=1; t<=0
region <2>: s>=1;t<=0
region <3>: s>=1; 0<=t<=1
region <4>: s>=1; t>=1
region <6>: s<=0; 0<=t<=1
region <5>: others

// ptCrossThis = m_ptInLine + m_vDir*u
// ptCrossThat = fct.m_pt[0] + (fct.m_pt[1]-fct.m_pt[0])*s + (fct.m_pt[2]-fct.m_pt[1])*t
*/
/************************************************************************/
float MH_CrvLine::DistanceTo2(const MH_Facet& fct, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const
{
	bool bCross = CrossPoint(MH_Plane(fct), &ptCrossThis);

	// Parallel to the facet
	if(!bCross)
	{
		MH_Point3 pt[4];
		DistanceTo2(MH_CrvLineSeg(fct.m_pt[0], fct.m_pt[1]), pt[0], pt[1]);
		DistanceTo2(MH_CrvLineSeg(fct.m_pt[1], fct.m_pt[2]), pt[2], pt[3]);
		if(pt[0].DistanceTo2(pt[1]) < pt[2].DistanceTo2(pt[3]))
		{
			ptCrossThis = pt[0];
			ptCrossThat = pt[1];
		}
		else
		{
			ptCrossThis = pt[2];
			ptCrossThat = pt[3];
		}
		return ptCrossThis.DistanceTo2(ptCrossThat);
	}

	int nRegion;
	fct.CheckPoint(ptCrossThis, &nRegion);

	switch(nRegion)
	{
	case 0:
		ptCrossThat = ptCrossThis;
		return 0.0f;
	case 1:
		return DistanceTo2(MH_CrvLineSeg(fct.m_pt[0], fct.m_pt[1]), ptCrossThis, ptCrossThat);
	case 2:
		ptCrossThat = fct.m_pt[1];
		return ptCrossThat.DistanceTo2((*this), ptCrossThis);
	case 3:
		return DistanceTo2(MH_CrvLineSeg(fct.m_pt[1], fct.m_pt[2]), ptCrossThis, ptCrossThat);
	case 4:
		ptCrossThat = fct.m_pt[2];
		return ptCrossThat.DistanceTo2((*this), ptCrossThis);
	case 5:
		return DistanceTo2(MH_CrvLineSeg(fct.m_pt[2], fct.m_pt[0]), ptCrossThis, ptCrossThat);
	case 6:
		ptCrossThat = fct.m_pt[0];
		return ptCrossThat.DistanceTo2((*this), ptCrossThis);
	default:
		ASSERT(0);
		break;
	}

	return 0.0f;
}


// Is the point in this line
bool MH_CrvLine::IsIn(const MH_Point3& pt) const
{
	if( pt.DistanceTo2(*this, MH_Point3()) <= (MH_Util::GetTolerance()*MH_Util::GetTolerance()) )
		return true;

	return false;
}

// Is the line in this line
bool MH_CrvLine::IsIn(const MH_CrvLine& line) const
{
	if(IsIn(line.m_ptInLine) && IsIn(line.m_ptInLine + line.m_vDir))
		return true;

	return false;
}

// Is the line in this line
bool MH_CrvLine::IsIn(const MH_CrvLineSeg& lineSeg) const
{
	if(IsIn(lineSeg.GetFrom()) && IsIn(lineSeg.GetTo()))
		return true;

	return false;
}