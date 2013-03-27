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
#include "s2_crvlinesegcmd.h"
#include "s2_crvlinesegreq.h"
#include "fw_document.h"
#include "fw_mdiframewnd.h"
#include "fw_view.h"
#include "gr_dlcrv.h"
#include "gr_dlnode.h"
#include "gr_dlnodesketch2d.h"
#include "mh_crvlineseg.h"
#include "mh_crdsys.h"
#include "mh_plane.h"
#include "resource.h"
#include "sl_mm.h"

S2_CrvLineSegCmd::S2_CrvLineSegCmd(void)
:FW_Cmd(IDS_S2_CRVLINESEG_DISPNAME,
		IDS_S2_CRVLINESEG_TOOLTIP,
		IDB_S2_CRVLINESEG,_T("S2_CrvLineSegCmd"))
{

}

S2_CrvLineSegCmd::~S2_CrvLineSegCmd(void)
{
}

S2_CrvLineSegCmd* S2_CrvLineSegCmd::GetCmd()
{
	static S2_CrvLineSegCmd* pS2_CrvLineSegCmd = NULL;
	if(!pS2_CrvLineSegCmd)
		pS2_CrvLineSegCmd = new S2_CrvLineSegCmd();
	return pS2_CrvLineSegCmd;
}

BEGIN_MESSAGE_MAP(S2_CrvLineSegCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL S2_CrvLineSegCmd::OnExecute()
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

	m_pPtPrevious	= NULL;
	m_pDLCrvPreview	= NULL;
	return TRUE;
}

// Terminate the command. Such as when ESC is pressed
// virtual
BOOL S2_CrvLineSegCmd::OnTerminate()
{
	if(m_pPtPrevious)
	{
		delete m_pPtPrevious;
		m_pPtPrevious = NULL;
	}

	if(m_pDLCrvPreview)
	{
		m_pDLCrvPreview->Detach();
		delete m_pDLCrvPreview;
		m_pDLCrvPreview = NULL;
	}

	return FW_Cmd::OnTerminate();
}

// LButtonUp message
// virtual 
void S2_CrvLineSegCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	// Get the cross point of the ray and the sketch plane
	MH_Point3 pt;
	MH_CrdSys crdSys(m_pDLNodeSketch2D->GetNetTransform());
	pView->GetPt(point, MH_Plane(crdSys.GetOrigin(), crdSys.GetZAxis()), pt);
	if(!m_pPtPrevious)
		m_pPtPrevious = new MH_Point3(pt);
	else
	{
		// Before execute the request, we should detach the preview DL from the sketch node
		// Because in the request, we changed the DL node
		if(m_pDLCrvPreview)
			m_pDLCrvPreview->Detach();

		S2_CrvLineSegReq req(FW_MDIFrameWnd::GetActiveDoc(), m_pDLNodeSketch2D, MH_CrvLineSeg(*m_pPtPrevious, pt));
		FW_MDIFrameWnd::GetActiveDoc()->ExecuteRequest(&req);
		(*m_pPtPrevious) = pt;

		// Once executed the request, restore the DL
		m_pDLNodeSketch2D->AddDL(m_pDLCrvPreview);
		pView->Invalidate();
	}
}

// MouseMove message
// virtual 
void S2_CrvLineSegCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	// Get the cross point of the ray and the sketch plane
	MH_Point3 pt;
	MH_CrdSys crdSys(m_pDLNodeSketch2D->GetNetTransform());
	pView->GetPt(point, MH_Plane(crdSys.GetOrigin(), crdSys.GetZAxis()), pt);

	if(m_pDLCrvPreview)
	{
		MH_CrvLineSeg* pCrvLineSeg = dynamic_cast<MH_CrvLineSeg*>(m_pDLCrvPreview->GetCrv().GetTarget());
		ASSERT(pCrvLineSeg);
		pCrvLineSeg->SetFrom(*m_pPtPrevious);
		pCrvLineSeg->SetTo(pt);
		pCrvLineSeg->Invalidate(true);
		m_pDLCrvPreview->Invalidate();
	}
	else if(m_pPtPrevious)
		m_pDLCrvPreview = new GR_DLCrv(m_pDLNodeSketch2D, new MH_CrvLineSeg(*m_pPtPrevious, pt));

	// Invalidate the view
	pView->Invalidate();
}
