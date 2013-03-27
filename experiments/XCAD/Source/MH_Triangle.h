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

#include "MH_Point3.h"

class MH_Triangle
{
public:
	MH_Triangle(void);
	MH_Triangle(const MH_Point3& pt1,
		const MH_Point3& pt2,
		const MH_Point3& pt3);
	virtual ~MH_Triangle(void);

	void Set(const MH_Point3& pt1,
		const MH_Point3& pt2,
		const MH_Point3& pt3);

	// Get Normal
	MH_Vector3 GetNormal() const;

	MH_Point3 m_pt[3];
};
