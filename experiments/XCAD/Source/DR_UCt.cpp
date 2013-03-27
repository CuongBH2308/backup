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
#include "dr_uct.h"
#include "dr_dctsolver.h"

DR_UCt::DR_UCt(const SL_Ptr<DR_DCtSolver>& pSolver)
:DR_Ct(pSolver->GetFragment())
{
	pSolver->AddUCt(this);
}

DR_UCt::~DR_UCt(void)
{
}
