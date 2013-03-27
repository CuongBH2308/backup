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
#include "dr_dctprofile.h"

DR_DCtProfile::DR_DCtProfile(const SL_Ptr<DR_Fragment>& pFragment,
							 const SL_Ptr<DR_StSetBodyWire>& pStSetBodyWire)
:DR_DCt(pFragment),
m_pStSetBodyWire(pStSetBodyWire)
{
}

DR_DCtProfile::~DR_DCtProfile(void)
{
}

// Compute the output in new condition
// virtual 
HRESULT DR_DCtProfile::Compute()
{
	return S_OK;
}