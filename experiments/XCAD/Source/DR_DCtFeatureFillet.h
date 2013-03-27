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
#include "dr_dctfeature.h"

class DR_DCtFeatureFillet :	public DR_DCtFeature
{
public:
	DR_DCtFeatureFillet(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_DCtFeatureFillet(void);
};
