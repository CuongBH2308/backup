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
#include "mh_vector3.h"
#include "mh_crvnurbs.h"

class MH_CrvRay : public MH_Crv
{
public:
	MH_CrvRay();
	MH_CrvRay(const MH_Point3& ptFrom, const MH_Vector3& vDir);
	virtual ~MH_CrvRay(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Copy this curve
	virtual MH_Crv*	Copy();

	// Get the nurbs expression
	virtual MH_CrvNurbs GetNurbs() const;

	// Assignment
	MH_CrvRay& operator = (const MH_CrvRay& crv);

	// Set info
	void Set(const MH_Point3& ptFrom, const MH_Vector3& vDir);

	// Get from point
	const MH_Point3&	GetFrom() const;

	// Get direction
	const MH_Vector3&	GetDir() const;

	// return false if I'm parallel to the plane
	bool				CrossPoint(const MH_Plane& plane, MH_Point3* pPt = NULL, float* pU = NULL) const;
private:
	MH_Point3	m_ptFrom;
	MH_Vector3	m_vDir;
};
