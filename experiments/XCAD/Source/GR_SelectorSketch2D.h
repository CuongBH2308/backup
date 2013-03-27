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
#include "gr_selector.h"

class GR_SelectorSketch2D :	public GR_Selector
{
public:
	GR_SelectorSketch2D(void);
	virtual ~GR_SelectorSketch2D(void);

	// Define the types that can be selected in the sketch node
	enum EType
	{
		ePoint		= 1,
		eCrvLine	= 1<<1,
		eCrvLineSeg	= 1<<2,
		eCrvCircle	= 1<<3,
		eCrvEllipse	= 1<<4,
		eCrvSpline	= 1<<5,
		eCrvNurbs	= 1<<6,
		eCrv		= eCrvLine|eCrvLineSeg|eCrvCircle|eCrvEllipse|eCrvSpline|eCrvNurbs,
		eAll		= ePoint|eCrv
	};

protected:
	// Check whether the DL potentially can be that selection
	// pSel will be created in OnQualify
	// So it should be deleted by the invoker
	virtual bool OnQualify(GR_SelectionSet* pSelSet, GR_DL* pDL) const;
};
