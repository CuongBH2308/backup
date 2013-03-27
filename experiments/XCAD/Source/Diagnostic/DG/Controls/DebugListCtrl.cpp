// DebugListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DebugListCtrl.h"


// CDebugListCtrl

IMPLEMENT_DYNAMIC(CDebugListCtrl, CListCtrl)

CDebugListCtrl::CDebugListCtrl()
{

}

CDebugListCtrl::~CDebugListCtrl()
{
}

void CDebugListCtrl::Initialize()
{
	// Insert some columns
	this->ModifyStyle(0, LVS_REPORT);
	CRect rect;
	this->GetClientRect(&rect);
	int nColInterval = rect.Width()/5;

	this->InsertColumn(0, _T("Time"), LVCFMT_LEFT, nColInterval);
	this->InsertColumn(1, _T("TickCount"), LVCFMT_LEFT, nColInterval);
	this->InsertColumn(2, _T("File"), LVCFMT_LEFT, nColInterval);
	this->InsertColumn(3, _T("Line"), LVCFMT_LEFT, nColInterval);
	this->InsertColumn(4, _T("Message"), LVCFMT_LEFT, nColInterval);
}

int CDebugListCtrl::InsertItem(CString strTime, DWORD dTickCount, CString strFileName, int nLineNumber, CString strError)
{
	LVITEM lvi;
	CString strItem;

	int iIndex;

	// Insert the first item
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = this->GetItemCount();

	// Time
	lvi.iSubItem = 0;
	strItem = strTime;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	iIndex = CListCtrl::InsertItem(&lvi);

	// Tick count
	lvi.iSubItem = 1;
	strItem.Format(_T("%d"), dTickCount);
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	CListCtrl::SetItem(&lvi);

	// File name
	lvi.iSubItem = 2;
	int ipos = strFileName.ReverseFind(_T('\\'));
	strItem = strFileName.Mid(ipos+1);
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	CListCtrl::SetItem(&lvi);

	// Line Number
	lvi.iSubItem = 3;
	strItem.Format(_T("%d"), nLineNumber);
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	CListCtrl::SetItem(&lvi);

	// error msg
	lvi.iSubItem = 4;
	strItem = strError;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	CListCtrl::SetItem(&lvi);

	return lvi.iItem;
}


BEGIN_MESSAGE_MAP(CDebugListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CDebugListCtrl message handlers


