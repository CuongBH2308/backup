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
#include "dr_stbool.h"

DR_StBool::DR_StBool(const SL_Ptr<DR_Fragment>& pFragment)
:DR_St(pFragment)
{
}

DR_StBool::~DR_StBool(void)
{
}

// Get value of the boolean
bool DR_StBool::GetValue() const
{
	return m_b;
}
