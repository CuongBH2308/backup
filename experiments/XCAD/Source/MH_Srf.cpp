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
#include "mh_srf.h"
#include "mh_srfpt.h"
#include "mh_crvray.h"


MH_Srf::MH_Srf(void)
{
}

MH_Srf::~MH_Srf(void)
{
	Cleanup();
}

// Get points
const MH_SrfPtVect& MH_Srf::GetPts() const
{
	return m_vSrfPt;
}

// Cleanup the MH_LineSeg in m_vLineSegs
bool MH_Srf::Cleanup()
{
	m_vSrfPt.clear();
	return true;
}

// Set facet type
void MH_Srf::SetFacetType(const EFacetType& eFacetType)
{
	m_eFacetType = eFacetType;
}

// Get facet type
const MH_Srf::EFacetType& MH_Srf::GetFacetType() const
{
	return m_eFacetType;
}

// Is the surface selected
// virtual 
bool MH_Srf::HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const
{
	return false;
}
