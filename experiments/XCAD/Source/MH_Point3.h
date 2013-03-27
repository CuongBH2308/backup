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

class MH_Vector3;
class MH_CrvLine;
class MH_CrvLineSeg;
class MH_Plane;
class MH_Facet;
class MH_Matrix44;
class MH_Point3 : public MH_Obj
{
public:
	MH_Point3();
	MH_Point3(const MH_Point3& pt);
	MH_Point3(const MH_Vector3& A);
	MH_Point3(float x, float y, float z);
	virtual ~MH_Point3(void);

	// Transform this point
	// pt = mtx * [m_f[0], m_f[1], m_f[2], 1]t
	virtual void Transform(const MH_Matrix44& mtx);

	void		Set(float x, float y, float z);

	bool		operator ==(const MH_Point3& pt) const;
	bool		operator !=(const MH_Point3& pt) const;
	MH_Point3&	operator = (const MH_Point3& pt);
	MH_Point3	operator + (const MH_Vector3& A) const;
	MH_Point3   operator - (void) const;
	MH_Vector3	operator - (const MH_Point3& pt) const;
	MH_Point3	operator * (const float s) const;
	MH_Point3	operator / (const float s) const;
	MH_Point3	operator + (const MH_Point3& A) const;

    float DistanceTo2(const MH_Point3& pt) const;
	float DistanceTo2(const MH_CrvLine& line, MH_Point3& ptCross) const;
	float DistanceTo2(const MH_CrvLineSeg& lineSeg, MH_Point3& ptCross) const;
	float DistanceTo2(const MH_Plane& plane, MH_Point3& ptCross) const;
	float DistanceTo2(const MH_Facet& fct, MH_Point3& ptCross) const;

	// Rotate this point around vAxis which is through pt
	// Right-hand rotation
	MH_Point3 Rotate(const MH_Point3& ptOrigin, const MH_Vector3& vAxis, float fAngle) const;

	float m_f[3];
};
