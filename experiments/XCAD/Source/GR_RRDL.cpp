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
#include "gr_rrdl.h"

GR_RRDL::GR_RRDL(GR_DL* pDL)
:m_pDL(pDL)
{
}

GR_RRDL::~GR_RRDL(void)
{
}

// Get DL
GR_DL* GR_RRDL::GetDL() const
{
	return m_pDL;
}

// Render the display list
bool GR_RRDL::Render() const
{
	if(!m_pDL)
		return false;

	return OnRender();
}
