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
#include "mh_srfnurbs.h"

class MH_SrfSphere : public MH_Srf
{
public:
	MH_SrfSphere();
	MH_SrfSphere(const MH_Point3& ptCenter, const float& fRadius);
	virtual ~MH_SrfSphere(void);

	// Triangulate the surface
	// The triangles are stored in m_vTriangles
	virtual bool Facet(float fTolerance);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Copy this surface
	virtual MH_Srf* Copy();

	// Get the nurbs expression
	virtual MH_SrfNurbs GetNurbs() const;

	// Assignment
	MH_SrfSphere& operator = (const MH_SrfSphere& srf);

private:
	MH_Point3 m_ptCenter;
	float m_fRadius;	
};
