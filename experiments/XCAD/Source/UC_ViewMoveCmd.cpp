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
#include "uc_viewmovecmd.h"
#include <math.h>
#include "fw_view.h"
#include "fw_document.h"
#include "resource.h"

UC_ViewMoveCmd::UC_ViewMoveCmd(void)
:FW_Cmd(IDS_UC_VIEW_MOVE_DISPNAME,
		IDS_UC_VIEW_MOVE_TOOLTIP,
		IDB_UC_VIEW_MOVE, 
		_T("UC_ViewMoveCmd"), 
		IDR_UC_VIEW_MOVE)
{
}

UC_ViewMoveCmd::~UC_ViewMoveCmd(void)
{
}

UC_ViewMoveCmd* UC_ViewMoveCmd::GetCmd()
{
	static UC_ViewMoveCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_ViewMoveCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_ViewMoveCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_ViewMoveCmd::OnExecute()
{
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

	m_bStart = false;
	m_hCursor = ::LoadCursor(AfxFindResourceHandle(MAKEINTRESOURCE(IDC_UC_VIEW_MOVE),RT_GROUP_CURSOR),
		MAKEINTRESOURCE(IDC_UC_VIEW_MOVE));
	return TRUE;
}

// LButtonDown message
// virtual 
void UC_ViewMoveCmd::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
	m_hCursorPrev = ::SetCursor(m_hCursor);
	::SetCapture(pWnd->GetSafeHwnd());
	m_ptPrev = point;
	m_bStart = true;
}

// LButtonUp message
// virtual 
void UC_ViewMoveCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	::ReleaseCapture();
	::SetCursor(m_hCursorPrev);
	m_bStart = false;
}

// MouseMove message
// virtual 
void UC_ViewMoveCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(!m_bStart || m_ptPrev==point || !pWnd->IsKindOf(RUNTIME_CLASS(FW_View)))
		return;

	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	float fDeltaX = -(float)(m_ptPrev.x - point.x) * 0.015f;
	float fDeltaY =  (float)(m_ptPrev.y - point.y) * 0.015f;

	MH_Matrix44 mtxMove;
	mtxMove[3] = fDeltaX;
	mtxMove[7] = fDeltaY;

	// Set model view matrix
	pView->SetModelView(mtxMove*pView->GetModelView());

	// Invalidate the view
	pView->Invalidate();
	m_ptPrev = point;
}