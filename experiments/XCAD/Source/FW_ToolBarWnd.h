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

class FW_ToolBar;
class FW_UICmdBar;
class FW_ToolBarWnd : public CWnd
{
public:
	FW_ToolBarWnd(CWnd* pParent);
	virtual ~FW_ToolBarWnd(void);

	// Show pUICmdBar
	bool Activate(FW_UICmdBar* pUICmdBar);

	void SetToolBar( const CString& strToolBar );
	const CString& GetToolBar() const;
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );
	void RecalcLayout();
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	void LearningModeChange();

	void ResetScrollingInfo();
	void ReconstructToolBar();

protected:
	afx_msg void OnPaint();
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);

private:
	bool ToolBarNeedsScrolling();
	void OnToolBarConfigurationChange();

	int GetCurrentScroll();
	int GetMaxScroll();
	int GetMinScroll();
	void SetCurrentScroll(int val);
	void SetMaxScroll(int val);
	void SetMinScroll(int val);

private:
	CString				m_strToolBar;
	FW_ToolBar*			m_pToolBar;
	int					m_yMinScroll;
	int					m_yCurrentScroll;
	int					m_yMaxScroll; 
	bool				m_bRecalcing;

	DECLARE_MESSAGE_MAP()
};
