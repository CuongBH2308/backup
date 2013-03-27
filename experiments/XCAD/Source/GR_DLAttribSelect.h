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


#pragma once
#include "gr_dlattrib.h"
#include "gr_color.h"
#include "gr_selectionset.h"

class GR_DLAttribSelect : public GR_DLAttrib
{
public:
	GR_DLAttribSelect(void);
	virtual ~GR_DLAttribSelect(void);

	// Set select status
	void SetStatus(const GR_SelectionSet::EStatus& eStatus);

	// Get select status
	const GR_SelectionSet::EStatus& GetStatus() const;

	// Set the preselect and select color
	void SetColor(GR_SelectionSet::EStatus eStatus, const GR_Color& clr);

	// Get the preselect and select color
	const GR_Color& GetColor(GR_SelectionSet::EStatus eStatus) const;
private:
	// Select status
	GR_SelectionSet::EStatus m_eStatus;

	// Preselect color
	GR_Color m_clrPreSel;

	// Select color
	GR_Color m_clrSel;
};
