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
#include "afxwin.h"

class FW_Dialog : public CDialog
{
	DECLARE_DYNAMIC(FW_Dialog)
public:
	FW_Dialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~FW_Dialog(void);

	// Once Apply button is clicked
	virtual void OnApply();

	DECLARE_MESSAGE_MAP()
};
