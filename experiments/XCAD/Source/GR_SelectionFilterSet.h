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
#include "gr_collect.h"

class GR_DL;
class GR_SelectionSet;
class GR_SelectionFilterSet
{
public:
	GR_SelectionFilterSet(void);
	virtual ~GR_SelectionFilterSet(void);

	// Add new filter
	void Add(GR_SelectionFilter* pFilter);

	// Delete all filters
	void DeleteAll();

	// Free unexpected selection
	void Filter(GR_SelectionSet* pSelSet) const;

private:
	// Is the selection wanted
	bool Qualify(GR_Selection* pSel) const;

	// All filters
	GR_SelectionFilterPtrVect m_vFilter;
};
