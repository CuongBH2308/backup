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
#include "gr_dlattribcurvewidth.h"

GR_DLAttribCurveWidth::GR_DLAttribCurveWidth(const float& fWidth)
:m_fWidth(fWidth)
{
}

GR_DLAttribCurveWidth::~GR_DLAttribCurveWidth(void)
{
}

// Set Width
void GR_DLAttribCurveWidth::SetWidth(const float& fWidth)
{
	m_fWidth = fWidth;
}

// Get Width
const float& GR_DLAttribCurveWidth::GetWidth() const
{
	return m_fWidth;
}
