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

class MH_Model;
class MH_Matrix44;
class MH_Vector3;
class MH_Point3;
class MH_MinDistUtil
{
	
	static float MinDist(const MH_Model& o1, const MH_Matrix44& r1, const MH_Vector3& t1,
		const MH_Model& o2, const MH_Matrix44& r2, const MH_Vector3& t2,
		MH_Point3& pt1, MH_Point3& pt2);
};
