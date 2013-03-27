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
#include "gr_dlcrv.h"
#include "mh_crv.h"
#include "mh_crvline.h"
#include "mh_crvlineseg.h"
#include "mh_crvray.h"
#include "mh_collect.h"
#include "sl_mm.h"

GR_DLCrv::GR_DLCrv(const SL_Ptr<GR_DLNode>& pParentNode, 
				   const SL_Ptr<MH_Crv>& pCrv)
:GR_DL(pParentNode),
m_pCrv(pCrv)
{
}

GR_DLCrv::~GR_DLCrv(void)
{
	if(m_pCrv.GetTarget())
		DEL_OBJ(m_pCrv.GetTarget());
}

// Get the type of the DL
// virtual
GR_DL::EType GR_DLCrv::GetType()
{
	return GR_DL::eCrv;
}

// Set math expression
void GR_DLCrv::SetCrv(const SL_Ptr<MH_Crv>& pCrv)
{
	m_pCrv = pCrv;
}

// Get math expression
const SL_Ptr<MH_Crv>& GR_DLCrv::GetCrv() const
{
	return m_pCrv;
}

// Is the DL selected
// virtual 
bool GR_DLCrv::HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const
{
	MH_Matrix44 mtxTransform = GetNetTransform();
	MH_CrvRay rayTemp = ray;
	rayTemp.Transform(mtxTransform.Reverse());
	float fTol2 = fTolerance*fTolerance;
	MH_CrvLine line(rayTemp);

	const MH_CrvPtVect& pts = m_pCrv->GetPts();
	for(int i=0; i<(int)pts.size()-1; i++)
	{
		if((pts[i].GetPoint3()-pts[i+1].GetPoint3()).IsValid() && line.DistanceTo2(MH_CrvLineSeg(pts[i].GetPoint3(), pts[i+1].GetPoint3()), MH_Point3(), ptHit)<=fTol2)
			return true;
	}
	return false;
}
