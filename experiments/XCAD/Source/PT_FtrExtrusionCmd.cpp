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
#include "pt_ftrextrusioncmd.h"
#include "gr_dlnodesketch2d.h"
#include "gr_selectionset.h"
#include "gr_selectionfilterset.h"
#include "gr_selectionfiltersketchcrv.h"
#include "fw_view.h"
#include "mh_crvray.h"
#include "resource.h"

PT_FtrExtrusionCmd::PT_FtrExtrusionCmd(void)
:FW_Cmd(IDS_PT_FTREXTRUSION_DISPNAME,
		IDS_PT_FTREXTRUSION_TOOLTIP,
		IDB_PT_FTREXTRUSION,
		_T("PT_FtrExtrusionCmd"), 
		IDR_PT_FTREXTRUSION),
m_pSelSet(NULL),
m_pFilterSet(NULL)
{
}

PT_FtrExtrusionCmd::~PT_FtrExtrusionCmd(void)
{
}

PT_FtrExtrusionCmd* PT_FtrExtrusionCmd::GetCmd()
{
	static PT_FtrExtrusionCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new PT_FtrExtrusionCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(PT_FtrExtrusionCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL PT_FtrExtrusionCmd::OnExecute()
{
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

	// New up the selection set
	m_pSelSet = new GR_SelectionSet();
	if(!m_pSelSet)
		return FALSE;

	// New up the filter set
	m_pFilterSet = new GR_SelectionFilterSet();
	if(!m_pFilterSet)
		return FALSE;

	// Add sketch curve filter
	GR_SelectionFilterSketchCrv* pSelectionFilterSketchCrv = new GR_SelectionFilterSketchCrv();
	if(!pSelectionFilterSketchCrv)
		return FALSE;

	m_pFilterSet->Add(pSelectionFilterSketchCrv);
	return TRUE;
}

// Terminate the command. Such as when ESC is pressed
// virtual
BOOL PT_FtrExtrusionCmd::OnTerminate()
{
	if(m_pFilterSet)
	{
		m_pFilterSet->DeleteAll();
		delete m_pFilterSet;
		m_pFilterSet = NULL;
	}

	if(m_pSelSet)
	{
		m_pSelSet->DeleteAll();
		delete m_pSelSet;
		m_pSelSet = NULL;
	}

	return FW_Cmd::OnTerminate();
}

// LButtonUp message
// virtual 
void PT_FtrExtrusionCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	// Get root DL Node
	GR_DLNode* pDLNode = pView->GetDLNode();
	if(!pDLNode)
		return;

	// Delete all items in the selection set
	m_pSelSet->DeleteAll();
	MH_CrvRay ray;
	pView->GetRay(point, ray);
	pDLNode->Select(*m_pSelSet, *m_pFilterSet, ray, 0.1f);

	if(m_pSelSet->IsNotEmpty())
		m_pSelSet->SetStatus(GR_SelectionSet::eSel);

	pView->Invalidate();
}

// MouseMove message
// virtual 
void PT_FtrExtrusionCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(nFlags != 0)
		return;

	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	// Get root DL Node
	GR_DLNode* pDLNode = pView->GetDLNode();
	if(!pDLNode)
		return;

	// Delete all items in the selection set
	m_pSelSet->DeleteAll();
	MH_CrvRay ray;
	pView->GetRay(point, ray);
	pDLNode->Select(*m_pSelSet, *m_pFilterSet, ray, 0.1f);

	if(m_pSelSet->IsNotEmpty())
		m_pSelSet->SetStatus(GR_SelectionSet::ePreSel);

	pView->Invalidate();
}