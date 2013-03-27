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

class MH_Facet : public MH_Obj
{
public:
	MH_Facet(void);
	MH_Facet(const MH_Point3& pt1, const MH_Point3& pt2, const MH_Point3& pt3);
	virtual ~MH_Facet(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Set points
	void Set(const MH_Point3& pt1, const MH_Point3& pt2, const MH_Point3& pt3);

	// Get Normal
	MH_Vector3 GetNormal() const;

/* Check point in which region.
   v1 = p1 - p;
   v2 = p2 - p1
   point x in p1p2 can be expressed as: p1+v2*t 0<=t<=1
   point in px can be expressed as: p+(x-p)*s 0<=s<=1
   Then:
   All the points in the triangle can be expressed as:
   p + ( (p1+v2*t) - p ) * s =
   p + v1*s + v2*s*t. 0<=s<=1, 0<=t<=1
   if it is in region 0, then return true
	
	          \ 4/
			   \/p2
			   /\
		 <5>  /  \  <3>
			 / 0  \  
		 ---/------\---
	   <6> /p  <1>  \p1  <2>
*/	 
	bool CheckPoint(const MH_Point3& pt, int* piRegion=NULL, float* pS=NULL, float* pT=NULL) const;
	float DistanceTo2(const MH_Facet& fct, MH_Point3& ptCrossThis, MH_Point3& ptCrossThat) const;

//private:
	MH_Point3 m_pt[3];
};
