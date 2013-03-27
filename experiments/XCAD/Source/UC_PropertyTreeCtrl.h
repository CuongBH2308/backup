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
#include "fw_treectrl.h"

class UC_PropertyTreeCtrl :	public FW_TreeCtrl
{
public:
	UC_PropertyTreeCtrl(void);
	virtual ~UC_PropertyTreeCtrl(void);

	virtual void SetToolTip(HTREEITEM hItem, const CString& strToolTip);
	virtual CString GetToolTip(HTREEITEM hItem) const;

protected:
	virtual void PreSubclassWindow();
	virtual void Cleanup(HTREEITEM hItem);
};
