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
#include "s2_crvbeziercmd.h"
#include "s2_crvbezierreq.h"
#include "fw_document.h"
#include "fw_mdiframewnd.h"
#include "fw_view.h"
#include "gr_dlcrv.h"
#include "gr_dlnode.h"
#include "gr_dlnodesketch2d.h"
#include "mh_crvnurbs.h"
#include "mh_crdsys.h"
#include "mh_plane.h"
#include "resource.h"
#include "sl_mm.h"

S2_CrvBezierCmd::S2_CrvBezierCmd(void)
:FW_Cmd(IDS_S2_CRVBEZIER_DISPNAME,
		IDS_S2_CRVBEZIER_TOOLTIP,
		IDB_S2_CRVBEZIER,_T("S2_CrvBezierCmd"))
{

}

S2_CrvBezierCmd::~S2_CrvBezierCmd(void)
{
}

S2_CrvBezierCmd* S2_CrvBezierCmd::GetCmd()
{
	static S2_CrvBezierCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new S2_CrvBezierCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(S2_CrvBezierCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL S2_CrvBezierCmd::OnExecute()
{
	// Initialize
	FW_Cmd::OnExecute();

	// Get active view
	FW_View* pView = GetView();
	if(!pView)
		return FALSE;

	// Get root node
	GR_DLNode* pDLNode = pView->GetDLNode();
	if(!pDLNode)
		return FALSE;

	m_pDLNodeSketch2D = GR_DLNodeSketch2D::GetActive(pDLNode);
	if(!m_pDLNodeSketch2D)
		return FALSE;

	m_pDLCrvPreview	= NULL;
	return TRUE;
}

// Terminate the command. Such as when ESC is pressed
// virtual
BOOL S2_CrvBezierCmd::OnTerminate()
{
	if(m_pDLCrvPreview)
	{
		m_pDLCrvPreview->Detach();
		delete m_pDLCrvPreview;
		m_pDLCrvPreview = NULL;
	}

	m_vCV.clear();
	return FW_Cmd::OnTerminate();
}

// LButtonUp message
// virtual 
void S2_CrvBezierCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	// Get the cross point of the ray and the sketch plane
	MH_Point3 pt;
	MH_CrdSys crdSys(m_pDLNodeSketch2D->GetNetTransform());
	pView->GetPt(point, MH_Plane(crdSys.GetOrigin(), crdSys.GetZAxis()), pt);
	m_vCV.push_back(pt);
	if(!m_pDLCrvPreview)
		m_pDLCrvPreview = new GR_DLCrv(m_pDLNodeSketch2D, new MH_CrvBezier(m_vCV));
	else
	{
		MH_CrvBezier* pCrvBezier = dynamic_cast<MH_CrvBezier*>(m_pDLCrvPreview->GetCrv().GetTarget());
		ASSERT(pCrvBezier);
		pCrvBezier->SetCVs(m_vCV);
		pCrvBezier->Invalidate(true);
	}
	pView->Invalidate();
}

// MouseMove message
// virtual 
void S2_CrvBezierCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(!m_pDLCrvPreview)
		return;

	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	// Get the cross point of the ray and the sketch plane
	MH_Point3 pt;
	MH_CrdSys crdSys(m_pDLNodeSketch2D->GetNetTransform());
	pView->GetPt(point, MH_Plane(crdSys.GetOrigin(), crdSys.GetZAxis()), pt);

	MH_CrvBezier* pCrvBezier = dynamic_cast<MH_CrvBezier*>(m_pDLCrvPreview->GetCrv().GetTarget());
	ASSERT(pCrvBezier);
	MH_CVVect vCV = m_vCV;
	vCV.push_back(pt);
	pCrvBezier->SetCVs(vCV);
	pCrvBezier->Invalidate(true);
	m_pDLCrvPreview->Invalidate();

	// Invalidate the view
	pView->Invalidate();
}


// RButtonUp message
// virtual 
void S2_CrvBezierCmd::OnRButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(!m_pDLCrvPreview)
		return;

	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	MH_CrvBezier* pCrvBezier = dynamic_cast<MH_CrvBezier*>(m_pDLCrvPreview->GetCrv().GetTarget());
	ASSERT(pCrvBezier);
	pCrvBezier->SetCVs(m_vCV);
	S2_CrvBezierReq req(FW_MDIFrameWnd::GetActiveDoc(), m_pDLNodeSketch2D, *pCrvBezier);
	FW_MDIFrameWnd::GetActiveDoc()->ExecuteRequest(&req);

	// Invalidate the view
	pView->Invalidate();

	OnTerminate();
}