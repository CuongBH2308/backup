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
#include <map>

class FW_UICmdBar;
class FW_ToolBar : public CToolBar
{
	DECLARE_DYNAMIC(FW_ToolBar)

public:
	FW_ToolBar(CWnd* pParent);
	virtual ~FW_ToolBar();

	void AdjustRows(int iWidth);

	// Show pUICmdBar
	bool Activate(FW_UICmdBar* pUICmdBar);

	// Get active FW_UICmdBar
	FW_UICmdBar* GetActive();

	// helper
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );

	// Get tool tip
	CString GetToolTip(UINT nCmdId);

	// Is command in this tool bar
	bool HasCmd(UINT nCmdId) const;

protected:
	DECLARE_MESSAGE_MAP()

private:
	// Active FW_UICmdBar whose buttons are showed
	FW_UICmdBar* m_pUICmdBar;

	CToolTipCtrl* m_pToolTipCtrl;
	CImageList* m_pImageList;
	CImageList* m_pImageListDisabled;
	CImageList* m_pImageListHot;
	std::map<UINT,CString> m_mToolTip;
};


