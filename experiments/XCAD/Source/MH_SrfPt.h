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
#include "mh_obj.h"
#include "mh_point3.h"
#include "mh_vector3.h"

class MH_SrfPt : public MH_Obj
{
public:
	MH_SrfPt();
	MH_SrfPt(const MH_Point3& pt3);
	MH_SrfPt(const MH_Point3& pt3, float fS, float fT, const MH_Vector3& vNormal = MH_Vector3(1,0,0));
	virtual ~MH_SrfPt(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Get the point in the curve
	const MH_Point3& GetPoint3() const;

	// Get the parameter of the point
	float	GetS() const;

	// Get the parameter of the point
	float	GetT() const;

private:
	MH_Vector3	m_vNormal;
	MH_Point3	m_pt3;
	float		m_fS;
	float		m_fT;
};
