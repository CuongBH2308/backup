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
#include "afxcmn.h"

class FW_TreeCtrlData
{
public:
	FW_TreeCtrlData(HTREEITEM hItem, const CString& strToolTip);
	virtual ~FW_TreeCtrlData(void);

	void SetItem(HTREEITEM hItem);
	HTREEITEM GetItem();
	void SetToolTip(const CString& strToolTip);
	const CString& GetToolTip() const;
private:
	HTREEITEM	m_hItem;
	CString		m_strToolTip;
};

class FW_TreeCtrl :	public CTreeCtrl
{
public:
	FW_TreeCtrl(void);
	virtual ~FW_TreeCtrl(void);
	BOOL OnToolTipText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	virtual void SetToolTip(HTREEITEM hItem, const CString& strToolTip);
	virtual CString GetToolTip(HTREEITEM hItem) const;

protected:
	virtual void Cleanup(HTREEITEM hItem);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

private:
	LPSTR	m_pToolTipByte;
	LPWSTR  m_pToolTipWideByte;
};
