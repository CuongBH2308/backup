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
#include "gr_dlattribcurvestipple.h"

GR_DLAttribCurveStipple::GR_DLAttribCurveStipple(int iFactor, unsigned short pattern)
:m_iFactor(iFactor),
m_pattern(pattern)
{
}

GR_DLAttribCurveStipple::~GR_DLAttribCurveStipple(void)
{
}

void GR_DLAttribCurveStipple::Set(const int& iFactor, const unsigned short& pattern)
{
	m_iFactor = iFactor;
	m_pattern = pattern;
}

void GR_DLAttribCurveStipple::Get(int& iFactor, unsigned short& pattern)
{
	iFactor = m_iFactor;
	pattern = m_pattern;
}