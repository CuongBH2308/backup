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
#include "gr_dlattribcolor.h"

GR_DLAttribColor::GR_DLAttribColor(const GR_Color& color)
:m_color(color)
{
}

GR_DLAttribColor::~GR_DLAttribColor(void)
{
}

// Set color
void GR_DLAttribColor::SetColor(const GR_Color& clr)
{
	m_color = clr;
}

// Get color
const GR_Color& GR_DLAttribColor::GetColor() const
{
	return m_color;
}