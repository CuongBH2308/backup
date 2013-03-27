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
#include "gr_selectionfiltersketchcrv.h"
#include "gr_selectionsketchcrv.h"

GR_SelectionFilterSketchCrv::GR_SelectionFilterSketchCrv(void)
{
}

GR_SelectionFilterSketchCrv::~GR_SelectionFilterSketchCrv(void)
{
}

// Is the selection wanted
// virtual 
bool GR_SelectionFilterSketchCrv::Qualify(GR_Selection* pSel) const
{
	return (dynamic_cast<GR_SelectionSketchCrv*>(pSel) != NULL);
}