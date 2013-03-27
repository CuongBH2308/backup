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
#include "gr_selectionset.h"
#include <algorithm>
#include "gr_selection.h"

GR_SelectionSet::GR_SelectionSet(void)
{
}

GR_SelectionSet::~GR_SelectionSet(void)
{
	SetStatus(GR_SelectionSet::eUnSel);
}

// Is the set empty
bool GR_SelectionSet::IsNotEmpty() const
{
	return (m_selVect.size() > 0);
}

// Add pSel into m_selVect
void GR_SelectionSet::Add(GR_Selection* pSel)
{
	GR_SelectionPtrVect::const_iterator it = std::find(m_selVect.begin(), m_selVect.end(), pSel);
	if(it == m_selVect.end())
		m_selVect.push_back(pSel);
}

// Add all items in pSelSet into m_selVect
void GR_SelectionSet::Add(GR_SelectionSet* pSelSet)
{
	GR_SelectionPtrVect::iterator it = pSelSet->m_selVect.begin();
	GR_SelectionPtrVect::iterator itEnd = pSelSet->m_selVect.end();
	for(; it != itEnd; ++it)
	{
		if(*it)
			Add(*it);
	}
}

// Delete all selection
void GR_SelectionSet::DeleteAll()
{
	GR_SelectionPtrVect::iterator it = m_selVect.begin();
	GR_SelectionPtrVect::iterator itEnd = m_selVect.end();
	for(; it != itEnd; ++it)
	{
		if(*it)
			delete (*it);
	}

	m_selVect.clear();
}

// Add a DL into m_vDL of the selection
void GR_SelectionSet::Add(GR_DL* pDL)
{
	GR_SelectionPtrVect::iterator it = m_selVect.begin();
	GR_SelectionPtrVect::iterator itEnd = m_selVect.end();
	for(; it != itEnd; ++it)
	{
		if(*it)
			(*it)->Add(pDL);
	}
}

// Set m_ptIntersect of the selection
void GR_SelectionSet::SetIntersectPt(const MH_Point3& pt)
{
	GR_SelectionPtrVect::iterator it = m_selVect.begin();
	GR_SelectionPtrVect::iterator itEnd = m_selVect.end();
	for(; it != itEnd; ++it)
	{
		if(*it)
			(*it)->SetIntersectPt(pt);
	}
}

// Get m_selVect
GR_SelectionPtrVect& GR_SelectionSet::GetAll()
{
	return m_selVect;
}

// Set the status of the selection
void GR_SelectionSet::SetStatus(const EStatus eStatus)
{
	GR_SelectionPtrVect::iterator it = m_selVect.begin();
	GR_SelectionPtrVect::iterator itEnd = m_selVect.end();
	for(; it != itEnd; ++it)
	{
		if(*it)
			(*it)->SetStatus(eStatus);
	}
}