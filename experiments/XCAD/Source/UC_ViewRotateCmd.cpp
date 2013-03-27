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
#include "uc_viewrotatecmd.h"
#include <math.h>
#include "fw_view.h"
#include "fw_document.h"
#include "resource.h"

UC_ViewRotateCmd::UC_ViewRotateCmd(void)
:FW_Cmd(IDS_UC_VIEW_ROTATE_DISPNAME,
		IDS_UC_VIEW_ROTATE_TOOLTIP,
		IDB_UC_VIEW_ROTATE,
		_T("UC_ViewRotateCmd"),
		IDR_UC_VIEW_ROTATE)
{
}

UC_ViewRotateCmd::~UC_ViewRotateCmd(void)
{
}

UC_ViewRotateCmd* UC_ViewRotateCmd::GetCmd()
{
	static UC_ViewRotateCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_ViewRotateCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_ViewRotateCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_ViewRotateCmd::OnExecute()
{
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

	m_bStart = false;
	m_hCursor = ::LoadCursor(AfxFindResourceHandle(MAKEINTRESOURCE(IDC_UC_VIEW_ROTATE),RT_GROUP_CURSOR),
		MAKEINTRESOURCE(IDC_UC_VIEW_ROTATE));
	return TRUE;
}

// LButtonDown message
// virtual 
void UC_ViewRotateCmd::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
	m_hCursorPrev = ::SetCursor(m_hCursor);
	::SetCapture(pWnd->GetSafeHwnd());
	m_ptPrev = point;
	m_bStart = true;
}

// LButtonUp message
// virtual 
void UC_ViewRotateCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	::ReleaseCapture();
	::SetCursor(m_hCursorPrev);
	m_bStart = false;
}

// MouseMove message
// virtual 
void UC_ViewRotateCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(!m_bStart || m_ptPrev==point || !pWnd->IsKindOf(RUNTIME_CLASS(FW_View)))
		return;

	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	float fRoundY = -(float)(m_ptPrev.x - point.x) * 0.015f;
	float fRoundX = -(float)(m_ptPrev.y - point.y) * 0.015f;

	MH_Matrix44 mtxRoundX, mtxRoundY;
	mtxRoundX[5] = cos(fRoundX);
	mtxRoundX[6] = sin(-fRoundX);
	mtxRoundX[9] = sin(fRoundX);
	mtxRoundX[10] = cos(fRoundX);

	mtxRoundY[0] = cos(fRoundY);
	mtxRoundY[2] = sin(fRoundY);
	mtxRoundY[8] = -sin(fRoundY);
	mtxRoundY[10]= cos(fRoundY);
	pView->SetModelView(mtxRoundX*mtxRoundY*pView->GetModelView());
	pView->Invalidate();
	m_ptPrev = point;
}