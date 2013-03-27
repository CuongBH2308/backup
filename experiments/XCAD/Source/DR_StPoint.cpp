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


#include "stdafx.h"
#include "dr_stpoint.h"
#include "dr_uctcvcrv.h"

DR_StPoint::DR_StPoint(const SL_Ptr<DR_Fragment>& pFragment, const MH_Point3& point)
:DR_StGm(pFragment),
m_point(point)
{
}

DR_StPoint::~DR_StPoint(void)
{
}

// Transform this object
// virtual 
void DR_StPoint::Transform(const MH_Matrix44& mtx)
{
	m_point.Transform(mtx);
}

// Set point
void DR_StPoint::SetPoint(const MH_Point3& point)
{
	m_point = point;
}

// Get point
const MH_Point3& DR_StPoint::GetPoint() const
{
	return m_point;
}

// Is it a control point
bool DR_StPoint::IsCV() const
{
	const DR_CtPtrVect& vCt = GetInputs();
	DR_CtPtrVect::const_iterator it = vCt.begin();
	DR_CtPtrVect::const_iterator itEnd = vCt.end();
	for(; it!=itEnd; ++it)
	{
		if(dynamic_cast<DR_UCtCVCrv*>((*it).GetTarget()))
			return true;
	}
	return false;
}
