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
#include "fw_button.h"

class FW_ButtonColor : public FW_Button
{
	DECLARE_DYNCREATE(FW_ButtonColor)

public:
	FW_ButtonColor(void);
	virtual ~FW_ButtonColor(void);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	void SetColor(const COLORREF& clr, BOOL bUpdate = TRUE);
protected:
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()

private:
	COLORREF m_color;
};
