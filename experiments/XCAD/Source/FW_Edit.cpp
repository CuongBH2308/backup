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
#include "fw_edit.h"

#define COLOR_TEXT			RGB(0, 0, 0)
#define COLOR_TEXT_INVALID	RGB(255, 0, 0)
#define COLOR_BKGROUND		RGB(255, 255, 255)

IMPLEMENT_DYNCREATE(FW_Edit, CEdit)
FW_Edit::FW_Edit()
{
	m_TextColor = COLOR_TEXT;
	m_BackColor = COLOR_BKGROUND;
}

FW_Edit::~FW_Edit()
{
}

BEGIN_MESSAGE_MAP(FW_Edit, CEdit)
	//{{AFX_MSG_MAP(FW_Edit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void FW_Edit::SetTextColor(COLORREF col) 
{
	m_TextColor = col;
	UpdateCtrl();
}

void FW_Edit::SetBackColor(COLORREF col) 
{
	m_BackColor = col;
	UpdateCtrl(); 
}

// Is the string in the edit is valid
// virtual
BOOL FW_Edit::IsValid() const
{
	return TRUE;
}

HBRUSH FW_Edit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(m_BackColor);
	pDC->SetBkColor(m_BackColor);
	pDC->SetTextColor(m_TextColor);
	return (HBRUSH)m_Brush.GetSafeHandle();
}
 
void FW_Edit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CEdit::OnChar(nChar, nRepCnt, nFlags);

	if(IsValid())
		SetTextColor(COLOR_TEXT);
	else
		SetTextColor(COLOR_TEXT_INVALID);
}

void FW_Edit::OnKillfocus() 
{
	UpdateCtrl();
}

void FW_Edit::OnUpdate() 
{
	UpdateCtrl();
}

void FW_Edit::UpdateCtrl()
{
	CWnd* pParent = GetParent();
	if(pParent)
	{
		CRect rect;
		GetWindowRect(rect);
		pParent->ScreenToClient(rect);
		rect.DeflateRect(2, 2);
		pParent->InvalidateRect(rect);
	}
}