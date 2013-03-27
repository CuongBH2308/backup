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

class MH_CV : public MH_Obj
{
public:
	MH_CV(void);
	MH_CV(float wx, float wy, float wz, float w);
	MH_CV(const MH_Point3& pt3, float w = 1.0);
	virtual ~MH_CV(void);

	// Transform this control point
	// pt = mtx * [m_f[0], m_f[1], m_f[2], 1]t
	virtual void Transform(const MH_Matrix44& mtx);

	// Equals
	bool operator ==(const MH_CV& cv) const;

	// Set point
	void SetPoint3(const MH_Point3& pt);

	// Get coordinate 
	MH_Point3 GetPoint3() const;
    
	MH_CV	operator + (const MH_CV& cv) const;
	MH_CV	operator - (const MH_CV& cv) const;
	MH_CV	operator * (const float s) const;
	MH_CV	operator / (const float s) const;

	// wx, wy, wz, w
	float m_f[4];
};
