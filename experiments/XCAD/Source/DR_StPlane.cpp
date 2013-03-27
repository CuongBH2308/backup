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
#include "dr_stplane.h"

DR_StPlane::DR_StPlane(const SL_Ptr<DR_Fragment>& pFragment, const MH_Plane& plane)
:DR_St(pFragment),
m_plane(plane)
{
}

DR_StPlane::~DR_StPlane(void)
{
}

void DR_StPlane::SetPlane(const MH_Plane& plane)
{
	m_plane = plane;
}

const MH_Plane& DR_StPlane::GetPlane() const
{
	return m_plane;
}