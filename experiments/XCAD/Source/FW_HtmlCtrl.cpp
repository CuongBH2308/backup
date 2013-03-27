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
#include "fw_htmlctrl.h"

IMPLEMENT_DYNAMIC(FW_HtmlCtrl, CHtmlView)
FW_HtmlCtrl::FW_HtmlCtrl(void)
{
}

FW_HtmlCtrl::~FW_HtmlCtrl(void)
{
}

BEGIN_MESSAGE_MAP(FW_HtmlCtrl, CHtmlView)
	ON_WM_DESTROY()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

BOOL FW_HtmlCtrl::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CStatic wndStatic;
	if (!wndStatic.SubclassDlgItem(nID, pParent))
		return FALSE;
	
	CRect rc;
	wndStatic.GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	wndStatic.ShowWindow(SW_HIDE);
	
	return Create(NULL,
		NULL,
		(WS_CHILD | WS_VISIBLE ),
		rc,
		pParent,
		nID,
		NULL);
}

// virtual 
void FW_HtmlCtrl::PostNcDestroy()
{
	delete this;
}

void FW_HtmlCtrl::OnDestroy()
{
	if (m_pBrowserApp)
		m_pBrowserApp = NULL;
	
	CWnd::OnDestroy();
}

int FW_HtmlCtrl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg)
{
	// Bypass doc/view
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, msg);
}

// Get IHTMLDocument2
CComPtr<IHTMLDocument2> FW_HtmlCtrl::GetHTMLDocument2()
{
	if(!m_spHTMLDocument2)
	{
		LPDISPATCH pDisp = GetContainer();
		if(pDisp)
		{
			IHTMLDocument2* pHTMLDocument2 = NULL;
			HRESULT hr = pDisp->QueryInterface(__uuidof(IHTMLDocument2), (void**)&pHTMLDocument2);
			if(SUCCEEDED(hr))
				m_spHTMLDocument2.Attach(pHTMLDocument2);
		}
	}

	return m_spHTMLDocument2;
}