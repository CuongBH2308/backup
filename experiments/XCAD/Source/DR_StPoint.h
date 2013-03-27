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
#include "dr_stgm.h"
#include "mh_point3.h"

class DR_StPoint : public DR_StGm
{
public:
	DR_StPoint(const SL_Ptr<DR_Fragment>& pFragment, const MH_Point3& point);
	virtual ~DR_StPoint(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Set point
	void SetPoint(const MH_Point3& point);

	// Get point
	const MH_Point3& GetPoint() const;

	// Is it a control point
	bool IsCV() const;
private:
	MH_Point3 m_point;
};
