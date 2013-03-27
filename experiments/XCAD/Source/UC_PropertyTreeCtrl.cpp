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
#include "uc_propertytreectrl.h"
#include <typeinfo.h>
#include "gr_dl.h"
#include "gr_dlnode.h"
#include "gr_dlattribcolor.h"

UC_PropertyTreeCtrl::UC_PropertyTreeCtrl(void)
{
}

UC_PropertyTreeCtrl::~UC_PropertyTreeCtrl(void)
{
}

// virtual 
void UC_PropertyTreeCtrl::SetToolTip(HTREEITEM hItem, const CString& strToolTip)
{
}

void UC_PropertyTreeCtrl::PreSubclassWindow() 
{
	FW_TreeCtrl::PreSubclassWindow();
}

// virtual
CString UC_PropertyTreeCtrl::GetToolTip(HTREEITEM hItem) const
{
	CString strToolTip;
	DWORD_PTR data = GetItemData(hItem);
	if(data)
	{
		GR_DL* pDL			= reinterpret_cast<GR_DL*>(data);
		GR_DLNode* pDLNode	= dynamic_cast<GR_DLNode*>(pDL);

		CString str;
		if(pDL)
		{
			const GR_DLAttribPtrVect& vAttrib = pDL->GetAttribs();
			for(GR_DLAttribPtrVect::const_iterator it = vAttrib.begin(); it != vAttrib.end(); it++)
			{
				CString strTemp;
				strTemp.Format(_T("\r\n0x%x %s"), DWORD_PTR((*it).GetTarget()), CString(typeid(**it).name()).TrimLeft("class "));
				str += strTemp;
			}
		}
		strToolTip.Format(_T("0x%x %s "), data, CString(typeid(*pDL).name()).TrimLeft("class "));
		strToolTip = strToolTip + str;
	}	
	return strToolTip;
}

// virtual 
void UC_PropertyTreeCtrl::Cleanup(HTREEITEM hItem)
{
}