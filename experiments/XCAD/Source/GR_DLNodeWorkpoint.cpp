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
#include "gr_dlnodeworkpoint.h"
#include "dr_stpoint.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribpointsize.h"
#include "gr_dlattribpointsmooth.h"
#include "gr_dlpoint.h"
#include "sl_mm.h"

GR_DLNodeWorkpoint::GR_DLNodeWorkpoint(const SL_Ptr<GR_DLNode>& pParentNode, const SL_Ptr<DR_StPoint>& pStPoint)
:GR_DLNode(pParentNode),
m_pStPoint(pStPoint)
{
	ASSERT(m_pStPoint.GetTarget());
	const MH_Point3& pt = m_pStPoint->GetPoint();

	// Create geometry info
	MH_Point3* pPt = NEW_OBJ(MH_Point3, this)(pt);

	// Create DL
	SL_Ptr<GR_DLPoint> pDLPoint = NEW_OBJ(GR_DLPoint, this)(this, pPt);
	ASSERT(pDLPoint.GetTarget());
    
	// Add attribute - color
	pDLPoint->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 1.0f, 1.0f, 1.0f)));

	// Add attribute - size
	pDLPoint->AddAttrib(NEW_OBJ(GR_DLAttribPointSize, this)(4.0));

	// Add attribute - make point smooth
	pDLPoint->AddAttrib(NEW_OBJ(GR_DLAttribPointSmooth, this)(true));
}

GR_DLNodeWorkpoint::~GR_DLNodeWorkpoint(void)
{
}

const SL_Ptr<DR_StPoint>& GR_DLNodeWorkpoint::GetStPoint() const
{
	return m_pStPoint;
}