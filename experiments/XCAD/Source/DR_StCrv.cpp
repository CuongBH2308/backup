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
#include "dr_stcrv.h"
#include "dr_stpoint.h"

DR_StCrv::DR_StCrv(const SL_Ptr<DR_Fragment>& pFragment)
:DR_StGm(pFragment)
{
}

DR_StCrv::~DR_StCrv(void)
{
}

// Get start DR_StPoint
// virtual 
SL_Ptr<DR_StPoint> DR_StCrv::GetStartPt() const
{
	return reinterpret_cast<DR_StPoint*>(NULL);
}

// Get end DR_StPoint
// virtual
SL_Ptr<DR_StPoint> DR_StCrv::GetEndPt() const
{
	return reinterpret_cast<DR_StPoint*>(NULL);
}