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
#include "dr_dctsketch.h"

class DR_DCtSketch3D : public DR_DCtSketch
{
public:
	DR_DCtSketch3D(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_DCtSketch3D(void);
};
