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
#include "pt_ftrrevolvecmd.h"
#include "pt_ftrrevolvereq.h"
#include "dr_stcrv.h"
#include "gr_dlnodesketch2d.h"
#include "gr_selectionset.h"
#include "gr_selectionsketchcrv.h"
#include "gr_selectionfilterset.h"
#include "gr_selectionfiltersketchcrv.h"
#include "fw_document.h"
#include "fw_mdiframewnd.h"
#include "fw_view.h"
#include "mh_crvray.h"
#include "resource.h"

PT_FtrRevolveCmd::PT_FtrRevolveCmd(void)
:FW_Cmd(IDS_PT_FTRREVOLVE_DISPNAME,
		IDS_PT_FTRREVOLVE_TOOLTIP,
		IDB_PT_FTRREVOLVE,
		_T("PT_FtrRevolveCmd"), 
		IDR_PT_FTRREVOLVE),
m_pSelSetProfile(NULL),
m_pFilterSetProfile(NULL),
m_pSelSetAxis(NULL),
m_pFilterSetAxis(NULL)
{
}

PT_FtrRevolveCmd::~PT_FtrRevolveCmd(void)
{
}

PT_FtrRevolveCmd* PT_FtrRevolveCmd::GetCmd()
{
	static PT_FtrRevolveCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new PT_FtrRevolveCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(PT_FtrRevolveCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL PT_FtrRevolveCmd::OnExecute()
{
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

	//////////////////////////////////////////////////////////////////////////
	// Set the selection set for profile
	//////////////////////////////////////////////////////////////////////////
	// New up the selection set
	m_pSelSetProfile = new GR_SelectionSet();
	if(!m_pSelSetProfile)
		return FALSE;

	// New up the filter set
	m_pFilterSetProfile = new GR_SelectionFilterSet();
	if(!m_pFilterSetProfile)
		return FALSE;

	// Add sketch curve filter
	GR_SelectionFilterSketchCrv* pSelectionFilterSketchCrvProfile = new GR_SelectionFilterSketchCrv();
	if(!pSelectionFilterSketchCrvProfile)
		return FALSE;
	m_pFilterSetProfile->Add(pSelectionFilterSketchCrvProfile);

	//////////////////////////////////////////////////////////////////////////
	// Set the selection set for axis
	//////////////////////////////////////////////////////////////////////////
	// New up the selection set
	m_pSelSetAxis = new GR_SelectionSet();
	if(!m_pSelSetAxis)
		return FALSE;

	// New up the filter set
	m_pFilterSetAxis = new GR_SelectionFilterSet();
	if(!m_pFilterSetAxis)
		return FALSE;

	// Add sketch curve filter
	GR_SelectionFilterSketchCrv* pSelectionFilterSketchCrvAxis = new GR_SelectionFilterSketchCrv();
	if(!pSelectionFilterSketchCrvAxis)
		return FALSE;
	m_pFilterSetAxis->Add(pSelectionFilterSketchCrvAxis);

	return TRUE;
}

// Terminate the command. Such as when ESC is pressed
// virtual
BOOL PT_FtrRevolveCmd::OnTerminate()
{
	if(m_pFilterSetProfile)
	{
		m_pFilterSetProfile->DeleteAll();
		delete m_pFilterSetProfile;
		m_pFilterSetProfile = NULL;
	}

	if(m_pSelSetProfile)
	{
		m_pSelSetProfile->DeleteAll();
		delete m_pSelSetProfile;
		m_pSelSetProfile = NULL;
	}

	if(m_pFilterSetAxis)
	{
		m_pFilterSetAxis->DeleteAll();
		delete m_pFilterSetAxis;
		m_pFilterSetAxis = NULL;
	}

	if(m_pSelSetAxis)
	{
		m_pSelSetAxis->DeleteAll();
		delete m_pSelSetAxis;
		m_pSelSetAxis = NULL;
	}

	return FW_Cmd::OnTerminate();
}

// LButtonUp message
// virtual 
void PT_FtrRevolveCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	// Get root DL Node
	GR_DLNode* pDLNode = pView->GetDLNode();
	if(!pDLNode)
		return;

	MH_CrvRay ray;
	pView->GetRay(point, ray);
	if(!m_pSelSetProfile->IsNotEmpty())
	{
		pDLNode->Select(*m_pSelSetProfile, *m_pFilterSetProfile, ray, 0.1f);
		if(m_pSelSetProfile->IsNotEmpty())
			m_pSelSetProfile->SetStatus(GR_SelectionSet::eSel);
	}
	else if(!m_pSelSetAxis->IsNotEmpty())
	{
		pDLNode->Select(*m_pSelSetAxis, *m_pFilterSetAxis, ray, 0.1f);
		if(m_pSelSetAxis->IsNotEmpty())
			m_pSelSetAxis->SetStatus(GR_SelectionSet::eSel);
	}
	
	if(m_pSelSetProfile->IsNotEmpty() && m_pSelSetAxis->IsNotEmpty())
	{
		DR_StCrvPtrVect vStCrv;
		SL_Ptr<DR_StCrv> pStCrvAxis;
		GR_SelectionSketchCrv* pSel = NULL;
		pSel = dynamic_cast<GR_SelectionSketchCrv*>(m_pSelSetProfile->GetAll().front());
		if(pSel)
			vStCrv.push_back(pSel->GetStCrv());

		pSel = dynamic_cast<GR_SelectionSketchCrv*>(m_pSelSetAxis->GetAll().front());
		if(pSel)
			pStCrvAxis = pSel->GetStCrv();
		
		PT_FtrRevolveReq req(FW_MDIFrameWnd::GetActiveDoc(), vStCrv, pStCrvAxis);
		FW_MDIFrameWnd::GetActiveDoc()->ExecuteRequest(&req);

		m_pSelSetProfile->DeleteAll();
		m_pSelSetAxis->DeleteAll();
	}
	pView->Invalidate();
}