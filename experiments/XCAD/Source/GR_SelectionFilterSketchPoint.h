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


#pragma once
#include "gr_selectionfilter.h"

class GR_SelectionFilterSketchPoint : public GR_SelectionFilter
{
public:
	GR_SelectionFilterSketchPoint(void);
	virtual ~GR_SelectionFilterSketchPoint(void);

	// Is the selection wanted
	virtual bool Qualify(GR_Selection* pSel) const;
};
