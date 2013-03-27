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
#include "fw_dialog.h"
#include "resource.h"
#include "uc_propertytreectrl.h"

template<class T> class SL_Ptr;
class FW_Cmd;
class FW_PropertySheet;
class UC_PropertyPagePoint;
class UC_PropertyPageCurve;
class UC_PropertyPageSurface;
class GR_DLNode;
class UC_PropertyDlg : public FW_Dialog
{
	DECLARE_DYNAMIC(UC_PropertyDlg)

public:
	UC_PropertyDlg(FW_Cmd* pCmd, CWnd* pParent = NULL);
	virtual ~UC_PropertyDlg();

	enum { IDD = IDD_UC_PROPERTY };

	virtual void OnOK();
	virtual void OnCancel();
	virtual void OnApply();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void TreeNodeSelected(LPNMHDR pnmhdr, LRESULT *pLResult);

private:
	BOOL BuildTree();
	BOOL AddChildren(HTREEITEM hItem, const SL_Ptr<GR_DLNode>& pDLNode);

	UC_PropertyTreeCtrl		m_tree;
	FW_PropertySheet*		m_pPropertySheet;
	UC_PropertyPagePoint*	m_pPagePoint;
	UC_PropertyPageCurve*	m_pPageCurve;
	UC_PropertyPageSurface*	m_pPageSurface;
	FW_Cmd*					m_pCmd;
	DECLARE_MESSAGE_MAP()
};
