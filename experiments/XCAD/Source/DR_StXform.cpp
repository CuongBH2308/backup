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
#include "dr_stxform.h"

DR_StXform::DR_StXform(const SL_Ptr<DR_Fragment>& pFragment)
:DR_St(pFragment)
{
}

DR_StXform::~DR_StXform(void)
{
}

// Set transform matrix
void DR_StXform::SetXform(const MH_Matrix44& mtx)
{
	m_mtx = mtx;
}

// Get transform matrix
const MH_Matrix44& DR_StXform::GetXform() const
{
	return m_mtx;
}