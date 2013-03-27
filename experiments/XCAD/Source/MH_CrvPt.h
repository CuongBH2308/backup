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

class MH_CrvPt : public MH_Obj
{
public:
	MH_CrvPt(const MH_Point3& pt3, float fU = 0.0f);
	virtual ~MH_CrvPt(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Get the point in the curve
	const MH_Point3& GetPoint3() const;

	// Get the parameter of the point
	float	GetU() const;
private:
	MH_Point3	m_pt3;
	float		m_fU;
};
