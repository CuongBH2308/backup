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

class FW_DropDownWnd : public CWnd
{
	DECLARE_DYNAMIC(FW_DropDownWnd)

public:
	FW_DropDownWnd(CWnd* pParent);
	virtual ~FW_DropDownWnd(void);

	// Add a new string to the string array
	void AddItem(const CString& str);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnMouseMove(UINT, CPoint);

private:
	CStringArray m_stringArray;
	CFont        m_font;
	CRect		 m_buttonRect;
	int			 m_nDropDownState;	// -1 = Pushed, 1 = Raised.
	bool		 m_bMouseTracking;
};
