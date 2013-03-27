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
#include "gr_dlattribblend.h"

GR_DLAttribBlend::GR_DLAttribBlend(const bool& bBlend)
:m_bBlend(bBlend)
{
}

GR_DLAttribBlend::~GR_DLAttribBlend(void)
{
}

void GR_DLAttribBlend::SetBlend(const bool& bBlend)
{
	m_bBlend = bBlend;
}

const bool& GR_DLAttribBlend::GetBlend() const
{
	return m_bBlend;
}