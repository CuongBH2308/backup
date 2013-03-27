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
#include "gr_selectorbody.h"
#include "gr_selectionset.h"
#include "gr_dlnodebody.h"

GR_SelectorBody::GR_SelectorBody(void)
{
}

GR_SelectorBody::~GR_SelectorBody(void)
{
}

// Check whether the DL potentially can be that selection
// pSel will be created in OnQualify
// So it should be deleted by the invoker
// virtual 
bool GR_SelectorBody::OnQualify(GR_SelectionSet& selSet, GR_DL* pDL) const
{
	selSet.DeleteAll();
	GR_DLNodeBody* pDLNodeBody = dynamic_cast<GR_DLNodeBody*>(pDL->GetParent().GetTarget());
	if(!pDLNodeBody)
		return false;


	return (selSet.IsNotEmpty());
}	