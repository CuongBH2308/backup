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
#include "gr_dlsrf.h"
#include "mh_srf.h"
#include "sl_mm.h"

GR_DLSrf::GR_DLSrf(const SL_Ptr<GR_DLNode>& pParentNode, const SL_Ptr<MH_Srf>& pSrf)
:GR_DL(pParentNode),
m_pSrf(pSrf)
{
}

GR_DLSrf::~GR_DLSrf(void)
{
	if(m_pSrf.GetTarget())
		DEL_OBJ(m_pSrf.GetTarget());
}

// Get the type of the DL
// virtual
GR_DL::EType GR_DLSrf::GetType()
{
	return GR_DL::eSrf;
}

// Get math expression
const SL_Ptr<MH_Srf>& GR_DLSrf::GetSrf() const
{
	return m_pSrf;
}

// Is the DL selected
// virtual 
bool GR_DLSrf::HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const
{
	return m_pSrf->HitTest(ray, ptHit, fTolerance);
}