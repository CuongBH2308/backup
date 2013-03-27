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
#include "s2_dragcmd.h"
#include "dr_stgm.h"
#include "fw_view.h"
#include "fw_document.h"
#include "mh_vector3.h"
#include "mh_crvray.h"
#include "mh_crdsys.h"
#include "mh_plane.h"
#include "gr_color.h"
#include "gr_dl.h"
#include "gr_dlnode.h"
#include "gr_dlnodesketch2d.h"
#include "gr_dlattribselect.h"
#include "gr_selectionset.h"
#include "gr_selectionfilterset.h"
#include "gr_selectionfiltersketchcrv.h"
#include "gr_selectionfiltersketchpoint.h"
#include "gr_selectionfiltersketchcv.h"
#include "gr_selectionsketchcrv.h"
#include "gr_selectionsketchpoint.h"
#include "gr_selectionsketchcv.h"
#include "dr_stcrv.h"
#include "dr_stpoint.h"
#include "dr_uctcvcrv.h"
#include "dr_fragment.h"
#include "resource.h"
#include "gr_dlnodebody.h"

extern GR_DLNodeBody* gDLNodeBody;
S2_DragCmd::S2_DragCmd(void)
:FW_Cmd(IDS_S2_DRAG_DISPNAME,
		IDS_S2_DRAG_TOOLTIP,
		IDB_S2_DRAG,
		_T("S2_DragCmd"), 
		IDR_S2_DRAG),
m_pSelSet(NULL)
{
}

S2_DragCmd::~S2_DragCmd(void)
{
}

S2_DragCmd* S2_DragCmd::GetCmd()
{
	static S2_DragCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new S2_DragCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(S2_DragCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL S2_DragCmd::OnExecute()
{
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

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

	// New up the selection set
	m_pSelSet = new GR_SelectionSet();

	return TRUE;
}

// Terminate the command. Such as when ESC is pressed
// virtual 
BOOL S2_DragCmd::OnTerminate()
{
	if(m_pSelSet)
	{
		m_pSelSet->DeleteAll();
		delete m_pSelSet;
		m_pSelSet = NULL;
	}

	return FW_Cmd::OnTerminate();
}

// LButtonDown message
// virtual 
void S2_DragCmd::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	::SetCapture(pWnd->GetSafeHwnd());

	// Keep point in the window
	m_ptPrev = point;

	// Keep point in the sketch
	MH_CrdSys crdSys(m_pDLNodeSketch2D->GetNetTransform());
	pView->GetPt(point, MH_Plane(crdSys.GetOrigin(), crdSys.GetZAxis()), m_pt3Prev);

	// Delete all items in the selection set
	m_pSelSet->DeleteAll();
	GR_SelectionFilterSet filterSet;
	filterSet.Add(new GR_SelectionFilterSketchCrv());
	filterSet.Add(new GR_SelectionFilterSketchPoint());
	filterSet.Add(new GR_SelectionFilterSketchCV());

	MH_CrvRay ray;
	pView->GetRay(point, ray);
	m_pDLNodeSketch2D->Select(*m_pSelSet, filterSet, ray, 0.1f);
	
	// Set preselect status
	m_pSelSet->SetStatus(GR_SelectionSet::ePreSel);

	// Delete all items in the filterSet set
	filterSet.DeleteAll();
	pView->Invalidate();
}

// LButtonUp message
// virtual 
void S2_DragCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	::ReleaseCapture();

	if(m_pSelSet && m_pSelSet->IsNotEmpty())
	{
		m_pSelSet->SetStatus(GR_SelectionSet::eSel);
		pView->Invalidate();
	}
}

// MouseMove message
// virtual 
void S2_DragCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(m_ptPrev==point || !pWnd->IsKindOf(RUNTIME_CLASS(FW_View)))
		return;

	if(MK_LBUTTON & nFlags)
	{
		// Convert the window to FW_View
		FW_View* pView = dynamic_cast<FW_View*>(pWnd);
		if(!pView)
			return;

		if(m_pSelSet && m_pSelSet->IsNotEmpty())
		{
			// Get the cross point of the ray and the sketch plane
			MH_Point3 pt;
			MH_CrdSys crdSys(m_pDLNodeSketch2D->GetNetTransform());
			pView->GetPt(point, MH_Plane(crdSys.GetOrigin(), crdSys.GetZAxis()), pt);
			MH_Matrix44 mtx = MH_Matrix44::Translate(pt-m_pt3Prev);

			GR_SelectionPtrVect& vSel = m_pSelSet->GetAll();
			for(GR_SelectionPtrVect::iterator it = vSel.begin(); it != vSel.end(); ++it)
			{
				GR_SelectionSketchPoint* pSelPt = dynamic_cast<GR_SelectionSketchPoint*>(*it);
				GR_SelectionSketchCV* pSelCV = dynamic_cast<GR_SelectionSketchCV*>(*it);
				GR_SelectionSketchCrv* pSelCrv = dynamic_cast<GR_SelectionSketchCrv*>(*it);
				if(pSelPt)
					pSelPt->GetStPoint()->Transform(mtx);
				else if(pSelCV)
				{
					pSelCV->GetStPoint()->Transform(mtx);
					DR_UCtCVCrvPtrVect vUCtCVCrv = DR_UCtCVCrv::GetUCtCVCrvs(pSelCV->GetStPoint());
					DR_UCtCVCrv::SetCase(vUCtCVCrv, DR_UCtCVCrv::eFixCV);
					pSelCV->GetStPoint()->GetFragment()->Dirty(pSelCV->GetStPoint());
					pSelCV->GetStPoint()->GetFragment()->Compute();

					if(gDLNodeBody)
					gDLNodeBody->Update();
				}
				else if(pSelCrv)
					pSelCrv->GetStCrv()->Transform(mtx);
			}
			m_pDLNodeSketch2D->Update();
			pView->Invalidate();
			m_pt3Prev = pt;
			m_ptPrev  = point;
		}
	}
}