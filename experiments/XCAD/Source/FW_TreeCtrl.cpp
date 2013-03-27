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
#include "fw_treectrl.h"

//////////////////////////////////////////////////////////////////////////
// FW_TreeCtrlData
//////////////////////////////////////////////////////////////////////////
FW_TreeCtrlData::FW_TreeCtrlData(HTREEITEM hItem, const CString& strToolTip)
:m_hItem(hItem),
m_strToolTip(strToolTip)
{
}

FW_TreeCtrlData::~FW_TreeCtrlData(void)
{
}

void FW_TreeCtrlData::SetItem(HTREEITEM hItem)
{
	m_hItem = hItem;
}

HTREEITEM FW_TreeCtrlData::GetItem()
{
	return m_hItem;
}

void FW_TreeCtrlData::SetToolTip(const CString& strToolTip)
{
	m_strToolTip = strToolTip;
}

const CString& FW_TreeCtrlData::GetToolTip() const
{
	return m_strToolTip;
}


//////////////////////////////////////////////////////////////////////////
// FW_TreeCtrl
//////////////////////////////////////////////////////////////////////////
FW_TreeCtrl::FW_TreeCtrl(void)
:m_pToolTipByte(NULL),
m_pToolTipWideByte(NULL)
{
}

FW_TreeCtrl::~FW_TreeCtrl(void)
{
	if(m_pToolTipByte)
	{
		delete [] m_pToolTipByte;
		m_pToolTipByte = NULL;
	}

	if(m_pToolTipWideByte)
	{
		delete [] m_pToolTipWideByte;
		m_pToolTipWideByte = NULL;
	}
}

BEGIN_MESSAGE_MAP(FW_TreeCtrl, CTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL FW_TreeCtrl::OnToolTipText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	*pResult = 0;

	// Get the mouse position
	const MSG* pMessage = GetCurrentMessage();
	if(!pMessage)
		return FALSE;

	CPoint pt = pMessage->pt;
	ScreenToClient(&pt);

	UINT nFlags;
	//Get item pointed by mouse
	HTREEITEM hItem = HitTest( pt, &nFlags );
	if(!hItem)
		return FALSE;

	CString strToolTip = GetToolTip(hItem);
	if (strToolTip.IsEmpty())
		return FALSE;

	CToolTipCtrl* pToolTipCtrl = GetToolTips();
	if(pToolTipCtrl)
		pToolTipCtrl->SetMaxTipWidth(1000);

	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXT*  pTTT  = (TOOLTIPTEXT*)pNMHDR;
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	pTTT->hinst = NULL;
	memset(pTTT->szText, 0, sizeof(pTTT->szText)*sizeof(WCHAR));

	if(m_pToolTipByte)
	{
		delete [] m_pToolTipByte;
		m_pToolTipByte = NULL;
	}

	if(m_pToolTipWideByte)
	{
		delete [] m_pToolTipWideByte;
		m_pToolTipWideByte = NULL;
	}

	int iLen = strToolTip.GetLength();
	if (pNMHDR->code == TTN_NEEDTEXTA)
	{
		m_pToolTipByte = new char [iLen+1];
		if(!m_pToolTipByte)
			return TRUE;

		m_pToolTipByte[iLen] = 0;
		pTTTA->lpszText = m_pToolTipByte;
	}
	else
	{
		m_pToolTipWideByte = new WCHAR [iLen+1];
		if(!m_pToolTipWideByte)
			return TRUE;

		m_pToolTipWideByte[iLen] = 0;
		pTTTW->lpszText = m_pToolTipWideByte;
	}

#ifndef _UNICODE
	if(pNMHDR->code == TTN_NEEDTEXTA)
		memcpy(m_pToolTipByte, strToolTip, iLen);
	else
		mbstowcs(m_pToolTipWideByte, strToolTip, iLen);
#else
	if(pNMHDR->code == TTN_NEEDTEXTA)
		wcstombs(m_pToolTipByte, strToolTip, iLen);
	else
		memcpy(m_pToolTipWideByte, strToolTip, iLen*sizeof(WCHAR));
#endif

	return TRUE;
}

int FW_TreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int iRes = CTreeCtrl::OnCreate(lpCreateStruct);
	EnableToolTips();
	return iRes;
}

void FW_TreeCtrl::OnDestroy()
{
	HTREEITEM hRoot = GetRootItem();
	Cleanup(hRoot);
	CTreeCtrl::OnDestroy();
}

void FW_TreeCtrl::SetToolTip(HTREEITEM hItem, const CString& strToolTip)
{
	DWORD_PTR data = GetItemData(hItem);
	if(data)
	{
		FW_TreeCtrlData* pData = (FW_TreeCtrlData*)data;
		pData->SetToolTip(strToolTip);
	}
}

CString FW_TreeCtrl::GetToolTip(HTREEITEM hItem) const
{
	CString strTooTip;
	DWORD_PTR data = GetItemData(hItem);
	if(data)
	{
		FW_TreeCtrlData* pData = (FW_TreeCtrlData*)data;
		strTooTip = pData->GetToolTip();
	}

	strTooTip.Format(_T("0x%x %s"), hItem, strTooTip);
	return strTooTip;
}

void FW_TreeCtrl::Cleanup(HTREEITEM hItem)
{
	if(!hItem)
		return;

	DWORD_PTR data = GetItemData(hItem);
	if (data != NULL)
	{
		FW_TreeCtrlData* pData = (FW_TreeCtrlData*)data;
		delete pData ;
	}

	hItem = GetChildItem(hItem);
	do
	{
		Cleanup(hItem);
	}
	while( (hItem = GetNextSiblingItem( hItem )) != NULL );
}
