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
#include "gr_dlattribselect.h"

#define COLOR_PRESEL	GR_Color(1.0f, 0.0f, 0.0f, 0.5f)
#define COLOR_SEL		GR_Color(0.0f, 1.0f, 1.0f, 0.5f)

GR_DLAttribSelect::GR_DLAttribSelect(void)
:m_eStatus(GR_SelectionSet::eUnSel),
m_clrPreSel(COLOR_PRESEL),
m_clrSel(COLOR_SEL)
{
}

GR_DLAttribSelect::~GR_DLAttribSelect(void)
{
}

void GR_DLAttribSelect::SetStatus(const GR_SelectionSet::EStatus& eStatus)
{
	m_eStatus = eStatus;
}

const GR_SelectionSet::EStatus& GR_DLAttribSelect::GetStatus() const
{
	return m_eStatus;
}

// Set the preselect and select color
void GR_DLAttribSelect::SetColor(GR_SelectionSet::EStatus eStatus, const GR_Color& clr)
{
	switch(eStatus)
	{
	case GR_SelectionSet::ePreSel:
		m_clrPreSel = clr;
		break;
	case GR_SelectionSet::eSel:
		m_clrSel = clr;
		break;
	default:
		ASSERT(0);
		break;
	}
}

// Get the preselect and select color
const GR_Color& GR_DLAttribSelect::GetColor(GR_SelectionSet::EStatus eStatus) const
{
	switch(eStatus)
	{
	case GR_SelectionSet::ePreSel:
	default:
		return m_clrPreSel;
	case GR_SelectionSet::eSel:
		return m_clrSel;
	}
}