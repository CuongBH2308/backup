#if !defined(AFX_TIPVIEW_H__2C0EAB85_5382_49AD_A43F_9541FD64B280__INCLUDED_)
#define AFX_TIPVIEW_H__2C0EAB85_5382_49AD_A43F_9541FD64B280__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipView.h : header file
//

#include "datastruct.h"

/////////////////////////////////////////////////////////////////////////////
// CTipView view

class CTipView : public CListView
{
protected:
	CTipView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTipView)

// Attributes
public:
	long item_count;

// Operations
public:
	void DisplayItem(TipShowData curdata);
	void ClearTipData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTipView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTipView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPVIEW_H__2C0EAB85_5382_49AD_A43F_9541FD64B280__INCLUDED_)
