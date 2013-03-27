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
#include "gr_selectionsketchcrv.h"
#include "gr_dlnodesketch2d.h"
#include "dr_stcrv.h"

GR_SelectionSketchCrv::GR_SelectionSketchCrv(void)
{
}

GR_SelectionSketchCrv::~GR_SelectionSketchCrv(void)
{
}

// Get StCrv
DR_StCrv* GR_SelectionSketchCrv::GetStCrv() const
{
	const GR_DLPtrVect& vDL = GetDLPtrVect();
	ASSERT(vDL.size() == 1);
	if(vDL.size() != 1)
		return NULL;

	GR_DL* pDL = vDL.front().GetTarget();
	if(!pDL)
		return NULL;

	GR_DLNodeSketch2D* pDLNodeSketch2D = dynamic_cast<GR_DLNodeSketch2D*>(pDL->GetParent().GetTarget());
	if(!pDLNodeSketch2D)
		return NULL;

	DR_St* pSt = pDLNodeSketch2D->Get(SL_Ptr<GR_DL>(pDL)).GetTarget();
	if(!pSt)
		return NULL;

	return (dynamic_cast<DR_StCrv*>(pSt));
}