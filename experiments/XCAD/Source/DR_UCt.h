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
#include "dr_ct.h"

class DR_DCtSolver;
class DR_UCt : public DR_Ct
{
public:
	DR_UCt(const SL_Ptr<DR_DCtSolver>& pSolver);
	virtual ~DR_UCt(void);
};
