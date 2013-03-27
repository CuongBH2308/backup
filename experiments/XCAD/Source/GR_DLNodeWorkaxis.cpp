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
#include "gr_dlnodeworkaxis.h"
#include "dr_stcrvline.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribcurvewidth.h"
#include "gr_dlcrv.h"
#include "mh_crvlineseg.h"
#include "sl_mm.h"

#define LENGTH_AXIS 2.0

GR_DLNodeWorkaxis::GR_DLNodeWorkaxis(const SL_Ptr<GR_DLNode>& pParentNode, const SL_Ptr<DR_StCrvLine>& pStLine)
:GR_DLNode(pParentNode),
m_pStLine(pStLine)
{
	ASSERT(m_pStLine.GetTarget());
	const MH_Point3&	pt		= m_pStLine->GetLine().GetPtInLine();
	const MH_Vector3&	vDir	= m_pStLine->GetLine().GetDir();

	// Create geometry info
	MH_CrvLineSeg* pCrvLineSeg = NEW_OBJ(MH_CrvLineSeg, this)(pt, vDir*LENGTH_AXIS);
	
	// Create DL
	SL_Ptr<GR_DLCrv> pDLCrv = NEW_OBJ(GR_DLCrv, this)(this, pCrvLineSeg);

	// Add attribute - color
	pDLCrv->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 1.0f, 0.0f, 0.3f)));
	
	// Add attribute - width
	pDLCrv->AddAttrib(NEW_OBJ(GR_DLAttribCurveWidth, this)(2.0f));
}

GR_DLNodeWorkaxis::~GR_DLNodeWorkaxis(void)
{
}

// Get line
const SL_Ptr<DR_StCrvLine>& GR_DLNodeWorkaxis::GetStLine() const
{
	return m_pStLine;
}

// Set the color of the DL
void GR_DLNodeWorkaxis::SetColor(float r, float g, float b)
{
	GR_DLNodePtrVect*	pDLNodeVect = NULL;
	GR_DLPtrVect*			pDLVect = NULL;
	GetChildren(pDLNodeVect, pDLVect);
	ASSERT(pDLNodeVect->size() == 0);
	ASSERT(pDLVect->size() == 1);
	SL_Ptr<GR_DL> pDL = pDLVect->front();
	ASSERT(pDL.GetTarget());
	SL_Ptr<GR_DLAttribColor> pDLAttribColor = pDL->GetAttrib(typeid(GR_DLAttribColor)).GetTarget();
	ASSERT(pDLAttribColor.GetTarget());
	pDLAttribColor->SetColor(GR_Color(r,g,b,0));
}