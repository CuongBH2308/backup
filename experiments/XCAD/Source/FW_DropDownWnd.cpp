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
#include "fw_dropdownwnd.h"
#include "fw_panelcontainer.h"

IMPLEMENT_DYNAMIC(FW_DropDownWnd, CWnd)

FW_DropDownWnd::FW_DropDownWnd(CWnd* pParent) : m_nDropDownState(0),
m_bMouseTracking(false), m_buttonRect(0,0,0,0)
{
	CString str = AfxRegisterWndClass(CS_DBLCLKS);

	CreateEx(0,str, _T(""), WS_VISIBLE | WS_CHILD, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, pParent->m_hWnd, NULL);

	CRect rect(0,0,250,100);
	CalcWindowRect(&rect);

	SetWindowPos(NULL,200,400,rect.Width(),rect.Height(),
		SWP_NOZORDER);
}

FW_DropDownWnd::~FW_DropDownWnd(void)
{
}

BEGIN_MESSAGE_MAP(FW_DropDownWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void FW_DropDownWnd::AddItem(const CString& str)
{
	m_stringArray.Add(str);
}

void FW_DropDownWnd::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	dc.FillSolidRect(rect, GetSysColor(COLOR_APPWORKSPACE));
	CRect rcText(0,0,0,0);
	dc.SetTextColor(GetSysColor(COLOR_WINDOW));

	CBrush brush(GetSysColor(COLOR_WINDOW));
	CBrush* pOldBrush = dc.SelectObject(&brush);
	//CFont* pOldFont = dc.SelectObject(&m_font);

	CString text;
	GetWindowText(text);
	dc.DrawText(text, rcText, DT_NOPREFIX | DT_CALCRECT);

	int width = 8;	// Down arrow width.
	int space = 4;	// Space between text and down arrow.
	rcText.OffsetRect(width, 0);
	rcText.bottom = rect.bottom;
	if (rcText.right > (rect.right - width*2 - space - rect.Height()))
		rcText.right = (rect.right - width*2 - space - rect.Height());
	CRgn  rgn;
	CPoint ptVertex[4];
	CPoint org(rcText.right + space, rect.Height()/2 - width/4);

	ptVertex[0].x = org.x;
	ptVertex[0].y = org.y;
	ptVertex[1].x = org.x + width;
	ptVertex[1].y = org.y;
	ptVertex[2].x = org.x + width/2;
	ptVertex[2].y = org.y + width/2;
	ptVertex[3].x = org.x;
	ptVertex[3].y = org.y;

	VERIFY(rgn.CreatePolygonRgn( ptVertex, 4, ALTERNATE));

	dc.DrawText(text, rcText, DT_NOPREFIX | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	dc.PaintRgn(&rgn);

	rect.right = rcText.right + width*2 + space;
	m_buttonRect = rect;
	if (m_nDropDownState)
	{
		// Draw the button edge.
		COLORREF white = RGB(255,255,255);
		COLORREF black = RGB(  0,  0,  0);
		CPen bottomRight(PS_SOLID, 1, m_nDropDownState < 0 ? white : black);
		CPen topLeft(PS_SOLID, 1, m_nDropDownState < 0 ? black : white);
		--rect.bottom;
		CPen* pOldPen = dc.SelectObject(&topLeft);
		dc.MoveTo(rect.left, rect.bottom);
		dc.LineTo(rect.left, rect.top);
		dc.LineTo(rect.right, rect.top);
		dc.SelectObject(&bottomRight);
		dc.LineTo(rect.right, rect.bottom);
		dc.LineTo(rect.left, rect.bottom);
		dc.SelectObject(pOldPen);
	}

	//dc.SelectObject(pOldFont);
	dc.SelectObject(pOldBrush);
}

void FW_DropDownWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	FW_PanelContainer* pParentWnd = (FW_PanelContainer*) GetParent();
	ASSERT_VALID(pParentWnd);

	CRect rect;
	GetClientRect(&rect);
	CPoint popupPoint(rect.left, rect.bottom);

	if (m_buttonRect.PtInRect(point))
	{
		m_nDropDownState = -1;
		Invalidate();

		ClientToScreen(&popupPoint);
		pParentWnd->DropDown(popupPoint);

		m_nDropDownState = 0;
		Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void FW_DropDownWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_buttonRect.PtInRect(point))
	{
		// Raise the button if it is not already.
		if (m_nDropDownState != 1)
		{
			m_nDropDownState = 1;
			Invalidate();

			// Start mouse tracking if it is not already running.
			if (!m_bMouseTracking)
			{
				TRACKMOUSEEVENT tme;
				memset(&tme, 0, sizeof(tme));
				tme.cbSize = sizeof(tme);
				tme.hwndTrack = GetSafeHwnd();
				tme.dwFlags = TME_LEAVE;
				if (_TrackMouseEvent(&tme))
					m_bMouseTracking = true;
			}
		}
	}

	// Reset the button if it is raised.
	else if (m_nDropDownState == 1)
	{
		m_nDropDownState = 0;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}

