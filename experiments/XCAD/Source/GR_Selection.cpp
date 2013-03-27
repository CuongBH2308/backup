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
#include "gr_selection.h"
#include <algorithm>
#include "gr_dl.h"

GR_Selection::GR_Selection(void)
{
}

GR_Selection::~GR_Selection(void)
{
	SetStatus(GR_SelectionSet::eUnSel);
}

// Add a DL into m_vDL
void GR_Selection::Add(GR_DL* pDL)
{
	GR_DLPtrVect::const_iterator it = std::find(m_vDL.begin(), m_vDL.end(), pDL);
	if(it == m_vDL.end())
		m_vDL.push_back(pDL);
}

// Get DLPtrVect
const GR_DLPtrVect& GR_Selection::GetDLPtrVect() const
{
	return m_vDL;
}

// Set m_ptIntersect
void GR_Selection::SetIntersectPt(const MH_Point3& pt)
{
	m_ptIntersect = pt;
}

// Get intersect point 
// The selection ray should intersect one DL in GR_DLPtrVect
const MH_Point3& GR_Selection::GetIntersectPt() const
{
	return m_ptIntersect;
}

// Set the color of the selection
void GR_Selection::SetStatus(const GR_SelectionSet::EStatus eStatus)
{
	GR_DLPtrVect::const_iterator it = m_vDL.begin();
	GR_DLPtrVect::const_iterator itEnd = m_vDL.end();
	for(; it!=itEnd; ++it)
	{
		(*it)->SetSelect(eStatus);
		(*it)->Invalidate();
	}
}