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
#include "gr_dlattribpointsmooth.h"

GR_DLAttribPointSmooth::GR_DLAttribPointSmooth(const bool& bSmooth)
:m_bSmooth(bSmooth)
{
}

GR_DLAttribPointSmooth::~GR_DLAttribPointSmooth(void)
{
}

// Set smooth
void GR_DLAttribPointSmooth::SetSmooth(const bool& bSmooth)
{
	m_bSmooth = bSmooth;
}

// Get size
const bool& GR_DLAttribPointSmooth::GetSmooth() const
{
	return m_bSmooth;
}