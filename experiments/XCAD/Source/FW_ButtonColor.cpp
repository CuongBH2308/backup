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
#include "fw_buttoncolor.h"

IMPLEMENT_DYNCREATE(FW_ButtonColor, FW_Button)

FW_ButtonColor::FW_ButtonColor(void)
:m_color(RGB(0,0,0))
{
}

FW_ButtonColor::~FW_ButtonColor(void)
{
}

BEGIN_MESSAGE_MAP(FW_ButtonColor, FW_Button)
END_MESSAGE_MAP()

void FW_ButtonColor::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
	ModifyStyle( 0, BS_OWNERDRAW ); 
}

void FW_ButtonColor::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	VERIFY(lpDrawItemStruct->CtlType == ODT_BUTTON);
	if(lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		CBrush brush(m_color);
		dc.FillRect(&(lpDrawItemStruct->rcItem), &brush);
	}

	if( (lpDrawItemStruct->itemState  & ODS_SELECTED) && 
		(lpDrawItemStruct->itemAction &	(ODA_SELECT | ODA_DRAWENTIRE)) )
	{
		COLORREF fc = RGB(255 - GetRValue(m_color),
			255 - GetGValue(m_color), 
			255 - GetBValue(m_color));
		CBrush brush(fc);
		dc.FrameRect(&(lpDrawItemStruct->rcItem),&brush);
	}

	if( !(lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & ODA_SELECT) )
	{
		CBrush brush(m_color);
		dc.FrameRect(&lpDrawItemStruct->rcItem, &brush);
	}

	dc.Detach();
}

void FW_ButtonColor::SetColor(const COLORREF& clr, BOOL bUpdate)
{
	m_color = clr;
	if(bUpdate)
		Invalidate();
}
