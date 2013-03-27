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
#include "gr_selector.h"
#include "gr_selection.h"
#include "gr_selectionset.h"
#include "gr_selectionfilterset.h"
#include "gr_dl.h"

GR_Selector::GR_Selector(void)
{
}

GR_Selector::~GR_Selector(void)
{
}

// Try to select the DL
// The created selections are stored in selSet
bool GR_Selector::Select(GR_SelectionSet& selSet,
						 const GR_SelectionFilterSet& filterSet,
						 GR_DL* pDL, 
						 const MH_CrvRay& ray,
						 float fTolerance) const
{
	GR_SelectionSet selSetTemp;

	// Determine which kinds of selection can be created from the DL
	bool bOK = OnQualify(selSetTemp, pDL);
	if(!bOK)
		return false;
	ASSERT(selSetTemp.IsNotEmpty());

	filterSet.Filter(&selSetTemp);
	if(!selSetTemp.IsNotEmpty())
		return false;

	MH_Point3 ptIntersect;
	bOK = pDL->HitTest(ray, ptIntersect, fTolerance);
	if(!bOK)
	{
		// Delete all created selections that stored in selSet
		selSetTemp.DeleteAll();
		return false;
	}
	selSetTemp.Add(pDL);
	selSetTemp.SetIntersectPt(ptIntersect);
	selSet.Add(&selSetTemp);
	return true;
}