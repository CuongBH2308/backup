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
#include "gr_selectorsketch2d.h"
#include "gr_dlpoint.h"
#include "gr_dlcrv.h"
#include "gr_selectionsketchcrv.h"
#include "gr_selectionsketchpoint.h"

GR_SelectorSketch2D::GR_SelectorSketch2D(void)
{
}

GR_SelectorSketch2D::~GR_SelectorSketch2D(void)
{
}

// Check whether the DL potentially can be that selection
// pSel will be created in OnQualify
// So it should be deleted by the invoker
// virtual 
bool GR_SelectorSketch2D::OnQualify(GR_SelectionSet* pSelSet, GR_DL* pDL) const
{
	pSelSet->DeleteAll();
	if(dynamic_cast<GR_DLPoint*>(pDL))
		pSelSet->Add(new GR_SelectionSketchPoint);
	else if(dynamic_cast<GR_DLCrv*>(pDL))
		pSelSet->Add(new GR_SelectionSketchCrv);
	return (!pSelSet->IsEmpty());
}	
