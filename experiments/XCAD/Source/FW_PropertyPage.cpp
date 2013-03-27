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
#include "fw_propertypage.h"
#include "resource.h"

FW_PropertyPage::FW_PropertyPage(UINT nIDTemplate)
:CPropertyPage(nIDTemplate)
{
}

FW_PropertyPage::~FW_PropertyPage(void)
{
}

BEGIN_MESSAGE_MAP(FW_PropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(FW_PropertyPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CALLBACK FW_PropertyPage::EnumChildProc(HWND hwnd, LPARAM lParam)
{
	::EnumChildWindows(hwnd,(WNDENUMPROC)EnumChildProc, lParam);
	::EnableWindow(hwnd, BOOL(lParam));
	return TRUE;
}

void FW_PropertyPage::Enable(BOOL bEnable)
{
	::EnumChildWindows(GetSafeHwnd(),(WNDENUMPROC)EnumChildProc, LPARAM(bEnable));
	EnableWindow(bEnable);
}
