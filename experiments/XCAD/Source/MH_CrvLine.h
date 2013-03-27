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
#include "mh_crvlineseg.h"
#include "mh_point3.h"
#include "mh_vector3.h"

class MH_CrvRay;
class MH_CrvLine : public MH_Crv
{
public:
	MH_CrvLine(void);
	MH_CrvLine(const MH_Point3& ptInLine, const MH_Vector3& vDir);
	MH_CrvLine(const MH_CrvRay& ray);
	MH_CrvLine(const MH_CrvLineSeg& lineSeg);
	virtual ~MH_CrvLine(void);

	// Transform this lineseg's points
	// pt = mtx * [m_f[0], m_f[1], m_f[2], 1]t
	virtual void Transform(const MH_Matrix44& mtx);

	// Copy this curve
	virtual MH_Crv*	Copy();

	// Get the nurbs expression
	virtual MH_CrvNurbs GetNurbs() const;

	// Assignment
	MH_CrvLine& operator = (const MH_CrvLine& crv);

	// Get point in line
    const MH_Point3&	GetPtInLine() const;

	// Get direction
	const MH_Vector3&	GetDir() const;

	// return false if I'm parallel to the plane
	bool  CrossPoint(const MH_Plane& plane, MH_Point3* pPt = NULL, float* pU = NULL) const;
	float DistanceTo2(const MH_CrvLine& line, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const;
	float DistanceTo2(const MH_CrvLineSeg& lineSeg, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const;

	// ptCrossThis = m_ptInLine + m_vDir*u
	// ptCrossThat = fct.m_pt[0] + (fct.m_pt[1]-fct.m_pt[0])*s + (fct.m_pt[2]-fct.m_pt[1])*t
	float DistanceTo2(const MH_Facet& fct, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const;

	// Is the point in this line
	bool IsIn(const MH_Point3& pt) const;

	// Is the line in this line
	bool IsIn(const MH_CrvLine& line) const;

	// Is the line in this line
	bool IsIn(const MH_CrvLineSeg& lineSeg) const;
private:
	MH_Point3	m_ptInLine;
	MH_Vector3	m_vDir;
};
