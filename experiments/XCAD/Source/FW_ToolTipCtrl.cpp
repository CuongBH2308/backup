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
#include "fw_tooltipctrl.h"

FW_ToolTipCtrl::FW_ToolTipCtrl(void)
{
}

FW_ToolTipCtrl::~FW_ToolTipCtrl(void)
{
}

BEGIN_MESSAGE_MAP(FW_ToolTipCtrl, CToolTipCtrl)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()

LRESULT FW_ToolTipCtrl::OnSetText(WPARAM wParam, LPARAM lParam)
{
	return NULL;
}
