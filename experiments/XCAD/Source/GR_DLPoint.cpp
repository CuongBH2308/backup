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
#include "gr_dlpoint.h"
#include "gr_dlattribpointsize.h"
#include "mh_point3.h"
#include "mh_crvline.h"
#include "sl_mm.h"

GR_DLPoint::GR_DLPoint(const SL_Ptr<GR_DLNode>& pParentNode,
					   const SL_Ptr<MH_Point3>& pPt)
:GR_DL(pParentNode),
m_pPt(pPt)
{
}


GR_DLPoint::~GR_DLPoint(void)
{
	if(m_pPt.GetTarget())
		DEL_OBJ(m_pPt.GetTarget());
}

// Get the type of the DL
// virtual
GR_DL::EType GR_DLPoint::GetType()
{
	return GR_DL::ePoint;
}

// Is the DL selected
// virtual 
bool GR_DLPoint::HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const
{
	return m_pPt->DistanceTo2(MH_CrvLine(ray), ptHit) <= (fTolerance*fTolerance);
}

// Get math expression
const SL_Ptr<MH_Point3>& GR_DLPoint::GetPoint() const
{
	return m_pPt;
}

// Set size of the point
void GR_DLPoint::SetSize(const float& fSize)
{
	// Get this type of attribute
	GR_DLAttrib* pDLAttrib = GetAttrib(typeid(GR_DLAttribPointSize)).GetTarget();
	if(pDLAttrib)
	{
		GR_DLAttribPointSize* pDLAttribPointSize = dynamic_cast<GR_DLAttribPointSize*>(pDLAttrib);
		ASSERT(pDLAttribPointSize);
		pDLAttribPointSize->SetSize(fSize);
	}
	else
		AddAttrib(NEW_OBJ(GR_DLAttribPointSize, this)(fSize));
}