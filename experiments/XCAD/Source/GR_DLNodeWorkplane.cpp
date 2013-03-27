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
#include "gr_dlnodeworkplane.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribblend.h"
#include "gr_dlsrf.h"
#include "dr_stplane.h"
#include "mh_plane.h"
#include "mh_srfrect.h"
#include "sl_mm.h"

GR_DLNodeWorkplane::GR_DLNodeWorkplane(const SL_Ptr<GR_DLNode>& pParentNode, const SL_Ptr<DR_StPlane>& pStPlane, const MH_Vector3& vAxis)
:GR_DLNode(pParentNode),
m_pStPlane(pStPlane)
{
	ASSERT(m_pStPlane.GetTarget());
	const MH_Point3& pt			= m_pStPlane->GetPlane().GetPoint();
	const MH_Vector3& vNormal	= m_pStPlane->GetPlane().GetNormal();

	// Create geometry info
	MH_SrfRect* pSrfRect = NEW_OBJ(MH_SrfRect, this)(pt, vNormal, vAxis);

	// Create DL
	SL_Ptr<GR_DLSrf> pDLSrf = NEW_OBJ(GR_DLSrf, this)(this, pSrfRect);

	// Add attribute - color
	pDLSrf->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 1.0f, 0.0f, 0.3f)));
	
	// Add attribute - blend
	pDLSrf->AddAttrib(NEW_OBJ(GR_DLAttribBlend, this)(true));
}

GR_DLNodeWorkplane::~GR_DLNodeWorkplane(void)
{
}

// Get plane
const SL_Ptr<DR_StPlane>& GR_DLNodeWorkplane::GetStPlane() const
{
	return m_pStPlane;
}