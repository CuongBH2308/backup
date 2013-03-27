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
#include "gr_selectionset.h"
#include "mh_point3.h"

class GR_Color;
class GR_Selection
{
protected:
	GR_Selection(void);

public:
	// Destructor
	virtual ~GR_Selection(void);

	// Add a DL into m_vDL
	void Add(GR_DL* pDL);

	// Get DLPtrVect
	const GR_DLPtrVect& GetDLPtrVect() const;

	// Set m_ptIntersect
	void SetIntersectPt(const MH_Point3& pt);

	// Get intersect point 
	// The selection ray should intersect one DL in GR_DLPtrVect
	const MH_Point3& GetIntersectPt() const;

	// Set the color of the selection
	void SetStatus(const GR_SelectionSet::EStatus eStatus);
private:
	GR_DLPtrVect	m_vDL;
	MH_Point3		m_ptIntersect;
};
