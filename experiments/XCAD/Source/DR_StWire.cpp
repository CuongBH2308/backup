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
#include "dr_stwire.h"

DR_StWire::DR_StWire(const SL_Ptr<DR_Fragment>& pFragment)
:DR_St(pFragment)
{
}

DR_StWire::~DR_StWire(void)
{
}

// Set BREP_Wire
void DR_StWire::SetWire(const SL_Ptr<BREP_Wire>& pWire)
{
	m_pWire = pWire;
}

// Get BREP_Wire
const SL_Ptr<BREP_Wire>& DR_StWire::GetWire() const
{
	return m_pWire;
}