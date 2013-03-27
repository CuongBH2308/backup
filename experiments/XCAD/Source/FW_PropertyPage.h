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
#include "afxdlgs.h"

class FW_PropertyPage :	public CPropertyPage
{
public:
	FW_PropertyPage(UINT nIDTemplate);
	virtual ~FW_PropertyPage(void);

	// Enable / Disable all controls in this page
	void Enable(BOOL bEnable = TRUE);

protected:
	DECLARE_MESSAGE_MAP()

private:
	static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
};
