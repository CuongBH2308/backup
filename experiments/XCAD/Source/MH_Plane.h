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

class MH_Facet;
class MH_Plane : public MH_Obj
{
public:
	MH_Plane();
	MH_Plane(const MH_Point3& pt, const MH_Vector3& vNormal);
	MH_Plane(const MH_Point3& pt0, const MH_Point3& pt1, const MH_Point3& pt2);
	MH_Plane(const MH_Facet& fct);
	virtual ~MH_Plane(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Get plane's origin.
	const MH_Point3& GetPoint() const;

	// Get plane's normal.
	const MH_Vector3& GetNormal() const;

	// Is the plane valid
	bool IsValid() const;
private:
	MH_Point3  m_pt;
	MH_Vector3 m_vNormal;
};
