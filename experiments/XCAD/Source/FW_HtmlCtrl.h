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
#include "afxhtml.h"

class FW_HtmlCtrl : public CHtmlView
{
	DECLARE_DYNAMIC(FW_HtmlCtrl)
public:
	FW_HtmlCtrl(void);
	virtual ~FW_HtmlCtrl(void);
	
	BOOL CreateFromStatic(UINT nID, CWnd* pParent);
	virtual void PostNcDestroy();
	
	// Get IHTMLDocument2
	CComPtr<IHTMLDocument2> GetHTMLDocument2();

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg);
	
	DECLARE_MESSAGE_MAP();

private:
	CComPtr<IHTMLDocument2> m_spHTMLDocument2;
};
