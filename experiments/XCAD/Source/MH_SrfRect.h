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
#include "mh_srf.h"
#include "mh_point3.h"
#include "mh_vector3.h"
#include "mh_srfnurbs.h"

/************************************************************************/
/* 
	N 
	|  ___________
	| /Y		 /
    |/__________/
	pt			X
*/
/************************************************************************/

class MH_SrfRect : public MH_Srf
{
public:
	MH_SrfRect();
	MH_SrfRect(const MH_Point3& pt, const MH_Vector3& vNormal, const MH_Vector3& vXAxis);
	virtual ~MH_SrfRect(void);

	// Triangulate the surface
	// The triangles are stored in m_vTriangles
	virtual bool Facet(float fTolerance);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Is the surface selected
	virtual bool HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const;

	// Copy this surface
	virtual MH_Srf* Copy();

	// Get the nurbs expression
	virtual MH_SrfNurbs GetNurbs() const;

	// Assignment
	MH_SrfRect& operator = (const MH_SrfRect& srf);

	const MH_Point3&	GetPt() const;
	const MH_Vector3&	GetNormal() const;
	const MH_Vector3&	GetXAxis() const;

private:
	MH_Point3	m_pt;
	MH_Vector3	m_vNormal;
	MH_Vector3	m_vXAxis;
};
