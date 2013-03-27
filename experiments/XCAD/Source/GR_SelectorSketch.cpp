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
#include "gr_selectorsketch.h"
#include "gr_selectionset.h"
#include "gr_selectionsketchcv.h"
#include "gr_selectionsketchcrv.h"
#include "gr_selectionsketchpoint.h"
#include "gr_dlpoint.h"
#include "gr_dlcrv.h"
#include "gr_dlnodesketch2d.h"
#include "dr_stpoint.h"
#include "dr_stcrv.h"


GR_SelectorSketch::GR_SelectorSketch(void)
{
}

GR_SelectorSketch::~GR_SelectorSketch(void)
{
}

// Check whether the DL potentially can be that selection
// pSel will be created in OnQualify
// So it should be deleted by the invoker
// virtual 
bool GR_SelectorSketch::OnQualify(GR_SelectionSet& selSet, GR_DL* pDL) const
{
	selSet.DeleteAll();
	GR_DLNodeSketch2D* pDLNodeSketch2D = dynamic_cast<GR_DLNodeSketch2D*>(pDL->GetParent().GetTarget());
	if(!pDLNodeSketch2D)
		return false;

	// Get St
	DR_St* pSt = pDLNodeSketch2D->Get(SL_Ptr<GR_DL>(pDL)).GetTarget();
	if(!pSt)
		return false;

	if(dynamic_cast<DR_StPoint*>(pSt))
	{
		if(dynamic_cast<DR_StPoint*>(pSt)->IsCV())
			selSet.Add(new GR_SelectionSketchCV);
		else
			selSet.Add(new GR_SelectionSketchPoint);
	}
	else if(dynamic_cast<DR_StCrv*>(pSt))
		selSet.Add(new GR_SelectionSketchCrv);

	return (selSet.IsNotEmpty());
}	
