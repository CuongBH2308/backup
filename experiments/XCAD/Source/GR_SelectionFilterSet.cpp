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
#include "gr_selectionfilterset.h"
#include <algorithm>
#include "gr_selectionfilter.h"
#include "gr_selection.h"
#include "gr_selectionset.h"

GR_SelectionFilterSet::GR_SelectionFilterSet(void)
{
}

GR_SelectionFilterSet::~GR_SelectionFilterSet(void)
{
}

// Add new filter
void GR_SelectionFilterSet::Add(GR_SelectionFilter* pFilter)
{
	GR_SelectionFilterPtrVect::const_iterator it = std::find(m_vFilter.begin() , m_vFilter.end(), pFilter);
	if(it== m_vFilter.end())
		m_vFilter.push_back(pFilter);

}

// Delete all filters
void GR_SelectionFilterSet::DeleteAll()
{
	GR_SelectionFilterPtrVect::const_iterator it = m_vFilter.begin();
	GR_SelectionFilterPtrVect::const_iterator itEnd = m_vFilter.end();
	for(; it!=itEnd; ++it)
		delete (*it);

	m_vFilter.clear();
}

// Free unexpected selection
void GR_SelectionFilterSet::Filter(GR_SelectionSet* pSelSet) const
{
	GR_SelectionPtrVect& vSel = pSelSet->GetAll();
	GR_SelectionPtrVect::iterator it = vSel.begin();
	GR_SelectionPtrVect::iterator itEnd = vSel.end();
	for(; it!=itEnd; ++it)
	{
		if(!Qualify(*it))
		{
			delete (*it);
			(*it) = NULL;
		}
	}
}

// Is the selection wanted
bool GR_SelectionFilterSet::Qualify(GR_Selection* pSel) const
{
	GR_SelectionFilterPtrVect::const_iterator it = m_vFilter.begin();
	GR_SelectionFilterPtrVect::const_iterator itEnd = m_vFilter.end();
	for(; it!=itEnd; ++it)
	{
		if((*it)->Qualify(pSel))
			return true;
	}
	return false;
}
