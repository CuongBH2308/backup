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
#include "uc_viewzoomcmd.h"
#include <math.h>
#include "fw_document.h"
#include "fw_view.h"
#include "resource.h"

UC_ViewZoomCmd::UC_ViewZoomCmd(void)
:FW_Cmd(IDS_UC_VIEW_ZOOM_DISPNAME,
		IDS_UC_VIEW_ZOOM_TOOLTIP,
		IDB_UC_VIEW_ZOOM,
		_T("UC_ViewZoomCmd"), 
		IDR_UC_VIEW_ZOOM)
{
}

UC_ViewZoomCmd::~UC_ViewZoomCmd(void)
{
}

UC_ViewZoomCmd* UC_ViewZoomCmd::GetCmd()
{
	static UC_ViewZoomCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_ViewZoomCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_ViewZoomCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_ViewZoomCmd::OnExecute()
{
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

	m_bStart = false;
	m_hCursor = ::LoadCursor(AfxFindResourceHandle(MAKEINTRESOURCE(IDC_UC_VIEW_ZOOM),RT_GROUP_CURSOR),
		MAKEINTRESOURCE(IDC_UC_VIEW_ZOOM));
	return TRUE;
}

// LButtonDown message
// virtual 
void UC_ViewZoomCmd::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
	m_hCursorPrev = ::SetCursor(m_hCursor);
	::SetCapture(pWnd->GetSafeHwnd());
	m_ptPrev = point;
	m_bStart = true;
}

// LButtonUp message
// virtual 
void UC_ViewZoomCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	::ReleaseCapture();
	::SetCursor(m_hCursorPrev);
	m_bStart = false;
}

// MouseMove message
// virtual 
void UC_ViewZoomCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(!m_bStart || m_ptPrev==point || !pWnd->IsKindOf(RUNTIME_CLASS(FW_View)))
		return;

	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	float fRatio = 1.0f - (float)(m_ptPrev.y - point.y) * 0.015f;
	if(fRatio < 0.0f)
		fRatio = 0.001f;

	MH_Matrix44 mtxZoom;
	mtxZoom[0]	= fRatio;
	mtxZoom[5]	= fRatio;
	mtxZoom[10] = fRatio;	

	// Set model view matrix
	pView->SetModelView(mtxZoom*pView->GetModelView());

	// Invalidate the view
	pView->Invalidate();

	m_ptPrev = point;
}
