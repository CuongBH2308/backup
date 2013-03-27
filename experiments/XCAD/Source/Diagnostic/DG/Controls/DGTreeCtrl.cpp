// DGTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DGTreeCtrl.h"


// CDGTreeCtrl
IMPLEMENT_DYNAMIC(CDGItemHeaderCtrl, CHeaderCtrl)

BEGIN_MESSAGE_MAP(CDGItemHeaderCtrl, CHeaderCtrl)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

CDGItemHeaderCtrl::CDGItemHeaderCtrl()
{

}

CDGItemHeaderCtrl::~CDGItemHeaderCtrl()
{
}

HBRUSH CDGItemHeaderCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetTextColor(RGB(255, 255,0));
	pDC->SetBkColor(RGB(255, 0, 0));

	HBRUSH hbr = CHeaderCtrl::OnCtlColor(pDC, pWnd, nCtlColor);
	
	CBrush m_brushBackground;
	m_brushBackground.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));

	//return m_brushBackground;
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

BOOL CDGItemHeaderCtrl::Create(UINT nLevel, UINT nIndent, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	
	m_nLevel = nLevel;
	m_nIndent = nIndent;
	return CHeaderCtrl::Create(dwStyle, rect, pParentWnd, nID);
}

void CDGItemHeaderCtrl::SetValue(ProfileItem* pProfileData)
{
	CRect rect;
	this->GetClientRect(&rect);
	int nColInterval = rect.Width()/4;

	CString strTmp;

	CString str;
	HDITEM  hdi;

	hdi.mask = HDI_TEXT | HDI_WIDTH | HDI_FORMAT;
	hdi.cxy = COLUMNWIDTH + m_nIndent * (MAX_LEVEL - m_nLevel); // Make all columns 100 pixels wide.
	hdi.fmt = HDF_STRING | HDF_CENTER;

	strTmp = pProfileData->strRoutineName;
	hdi.pszText = strTmp.GetBuffer(0);
	this->InsertItem(0, &hdi);

	hdi.cxy = COLUMNWIDTH;
	strTmp.Format(_T("%f"), pProfileData->dbTime);
	hdi.pszText = strTmp.GetBuffer(0);
	this->InsertItem(1, &hdi);

	strTmp.Format(_T("%d"), pProfileData->iHitCount);
	hdi.pszText = strTmp.GetBuffer(0);
	this->InsertItem(2, &hdi);

	strTmp.Format(_T("%4.2f"), pProfileData->dbPercentage);
	hdi.pszText = strTmp.GetBuffer(0);
	this->InsertItem(3, &hdi);
}


IMPLEMENT_DYNAMIC(CDGTreeCtrl, CTreeCtrl)

CDGTreeCtrl::CDGTreeCtrl()
{

}

CDGTreeCtrl::~CDGTreeCtrl()
{
}

HTREEITEM CDGTreeCtrl::InsertItem(ProfileItem* pProfileData, HTREEITEM hParent/* = TVI_ROOT*/)
{
	HTREEITEM hTreeItem = this->CTreeCtrl::InsertItem(_T(""), hParent);
	this->Expand(hParent,TVE_EXPAND);

	UINT nItemLevel = GetItemLevel(hTreeItem);

	UINT nIndent = this->GetIndent();

	CRect rect;
	BOOL bOk = this->GetItemRect(hTreeItem, &rect, TRUE);
	rect.right = rect.left + COLUMNWIDTH * 4 + nIndent * (MAX_LEVEL - nItemLevel);

	//rect.InflateRect(0, 0, 200, 0);
	
	CDGItemHeaderCtrl* listCtrl = new CDGItemHeaderCtrl;
	static int i = 100;
	listCtrl->Create(nItemLevel, nIndent, WS_CHILD|WS_VISIBLE|HDS_HORZ, rect, this, ++i);

	listCtrl->SetValue(pProfileData);



	listCtrl->ShowWindow(SW_SHOW);

	return hTreeItem;
}

UINT CDGTreeCtrl::GetItemLevel(HTREEITEM hItem)
{
	UINT nLevel = 0;
	while (hItem)
	{
		hItem = this->GetParentItem(hItem);
		++nLevel;
	}
	return nLevel;
}


BEGIN_MESSAGE_MAP(CDGTreeCtrl, CTreeCtrl)
END_MESSAGE_MAP()



// CDGTreeCtrl message handlers
