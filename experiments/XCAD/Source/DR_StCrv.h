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
#include "dr_stgm.h"

class MH_Crv;
class DR_StCrv : public DR_StGm
{
public:
	DR_StCrv(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_StCrv(void);

	// Get curve
	virtual MH_Crv* GetCrv() = 0;

	// Get start DR_StPoint
	virtual SL_Ptr<DR_StPoint> GetStartPt() const;

	// Get end DR_StPoint
	virtual SL_Ptr<DR_StPoint> GetEndPt() const;
};
