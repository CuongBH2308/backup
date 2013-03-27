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

class GR_SelectionSet
{
public:
	GR_SelectionSet(void);
	virtual ~GR_SelectionSet(void);

	enum EStatus
	{
		eUnSel,
		ePreSel,
		eSel
	};

	// Is the set empty
	bool IsNotEmpty() const;

	// Add pSel into m_selVect
	void Add(GR_Selection* pSel);

	// Add all items in pSelSet into m_selVect
	void Add(GR_SelectionSet* pSelSet);

	// Delete all selection
	void DeleteAll();

	// Add a DL into m_vDL of the selection
	void Add(GR_DL* pDL);

	// Set m_ptIntersect of the selection
	void SetIntersectPt(const MH_Point3& pt);

	// Get m_selVect
	GR_SelectionPtrVect& GetAll();

	// Set the status of the selection
	void SetStatus(const EStatus eStatus);
private:
	GR_SelectionPtrVect m_selVect;
};
