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
#include "mh_point3.h"
#include "mh_crvnurbs.h"

class MH_CrvRay;
class MH_CrvLineSeg : public MH_Crv
{
public:
	MH_CrvLineSeg(void);
	MH_CrvLineSeg(const MH_Point3& ptFrom,const MH_Point3& ptTo);
	MH_CrvLineSeg(const MH_Point3& ptFrom,const MH_Vector3& vFrom2To);
	virtual ~MH_CrvLineSeg(void);

	// Triangulate the surface
	// The triangles are stored in m_vTriangles
	virtual bool Tessellate(float fTolerance);

	// Transform this lineseg's points
	// pt = mtx * [m_f[0], m_f[1], m_f[2], 1]t
	virtual void Transform(const MH_Matrix44& mtx);

	// Is the line segment selected
	virtual bool HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const;

	// Copy this curve
	virtual MH_Crv*	Copy();

	// Get the nurbs expression
	virtual MH_CrvNurbs GetNurbs() const;

	// Assignment
	MH_CrvLineSeg& operator = (const MH_CrvLineSeg& crv);

	void SetFrom(const MH_Point3& pt);
	void SetTo(const MH_Point3& pt);
	const MH_Point3& GetFrom() const;
	const MH_Point3& GetTo() const;

	//m_ptFrom + (m_ptTo-m_ptFrom)*s
	//<1> -----<0>------ <2>
	//return 0 is 0<=s<=1
	bool CheckPoint(const MH_Point3& pt, int* piRegion=NULL, float* pS=NULL) const;

	// Get the distance to another line segment
	float DistanceTo2(const MH_CrvLineSeg& lineSeg, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const;

	// ptCrossThis = m_ptInLine + m_vDir*u
	// ptCrossThat = fct.m_pt[0] + (fct.m_pt[1]-fct.m_pt[0])*s + (fct.m_pt[2]-fct.m_pt[1])*t
	float DistanceTo2(const MH_Facet& fct, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const;

private:
	MH_Point3 m_ptFrom;
	MH_Point3 m_ptTo;
};
