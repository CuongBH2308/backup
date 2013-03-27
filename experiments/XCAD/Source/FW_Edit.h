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

class FW_Edit : public CEdit
{
	DECLARE_DYNCREATE(FW_Edit)
public:
	FW_Edit();
	virtual ~FW_Edit();

protected:
	// Is the string in the edit is valid
	virtual BOOL IsValid() const;

	//{{AFX_MSG(FW_Edit)
	afx_msg HBRUSH	CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void	OnUpdate();
	afx_msg void	OnKillfocus();
	//}}AFX_MSG

private:
	// Set text's color
	void SetTextColor(COLORREF col);

	// Set background's color
	void SetBackColor(COLORREF col);

	// Update the control
	void		UpdateCtrl();

	COLORREF	m_TextColor;
	COLORREF	m_BackColor;
	CBrush		m_Brush;

	DECLARE_MESSAGE_MAP()
};