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
#include "s2_crvlinesegreq.h"
#include "dr_dctsketch2d.h"
#include "dr_dctsolver.h"
#include "dr_fragment.h"
#include "dr_stcrvlineseg.h"
#include "dr_stpoint.h"
#include "dr_uctpointlineseg.h"
#include "fw_document.h"
#include "gr_color.h"
#include "gr_dlcrv.h"
#include "gr_dlpoint.h"
#include "gr_dlnodesketch2d.h"
#include "sl_mm.h"

S2_CrvLineSegReq::S2_CrvLineSegReq(FW_Document* pDoc, GR_DLNodeSketch2D* pDLNodeSketch2D, const MH_CrvLineSeg& crvLineSeg)
:FW_RequestTxn(pDoc),
m_DLNodeSketch2D(pDLNodeSketch2D),
m_CrvLineSeg(crvLineSeg)
{
}

S2_CrvLineSegReq::~S2_CrvLineSegReq(void)
{
}

// Record
// virtual 
HRESULT S2_CrvLineSegReq::Script()
{
	return S_OK;
}

// Prepare the data for Replay
// virtual 
HRESULT S2_CrvLineSegReq::InitFromScript()
{
	return S_OK;
}

// virtual 
HRESULT S2_CrvLineSegReq::OnExecute()
{
	HRESULT hr = S_OK;

	// Copy the geometry expression
	MH_CrvLineSeg* pCrvLineSeg	= NEW_OBJ(MH_CrvLineSeg, m_DLNodeSketch2D)(m_CrvLineSeg);
	ASSERT(pCrvLineSeg);

	MH_Point3* pPtFrom			= NEW_OBJ(MH_Point3, pCrvLineSeg)(pCrvLineSeg->GetFrom());
	ASSERT(pPtFrom);

	MH_Point3* pPtTo			= NEW_OBJ(MH_Point3, pCrvLineSeg)(pCrvLineSeg->GetTo());
	ASSERT(pPtTo);


	// Create the DLCrv
	GR_DLCrv* pDLCrv			= NEW_OBJ(GR_DLCrv, m_DLNodeSketch2D)(m_DLNodeSketch2D, pCrvLineSeg);
	ASSERT(pDLCrv);
	pDLCrv->SetColor(GR_Color(0,1.0f,0,0));

	// Create from-DLPoint
	GR_DLPoint* pDLPointFrom	= NEW_OBJ(GR_DLPoint, m_DLNodeSketch2D)(m_DLNodeSketch2D, pPtFrom);
	ASSERT(pDLPointFrom);

	// Create to-DLPoint
	GR_DLPoint* pDLPointTo		= NEW_OBJ(GR_DLPoint, m_DLNodeSketch2D)(m_DLNodeSketch2D, pPtTo);
	ASSERT(pDLPointTo);

	DR_StCrvLineSeg* pStCrvLineSeg = NEW_OBJ(DR_StCrvLineSeg, m_pDoc->GetFragment())(m_pDoc->GetFragment(), *pCrvLineSeg);
	ASSERT(pStCrvLineSeg);
	m_DLNodeSketch2D->GetDCtSketch2D()->AddInput(pStCrvLineSeg);

	DR_StPoint* pStPointFrom = NEW_OBJ(DR_StPoint, m_pDoc->GetFragment())(m_pDoc->GetFragment(), pCrvLineSeg->GetFrom());
	ASSERT(pStPointFrom);
	m_DLNodeSketch2D->GetDCtSketch2D()->AddInput(pStPointFrom);

	DR_StPoint* pStPointTo = NEW_OBJ(DR_StPoint, m_pDoc->GetFragment())(m_pDoc->GetFragment(), pCrvLineSeg->GetTo());
	ASSERT(pStPointTo);
	m_DLNodeSketch2D->GetDCtSketch2D()->AddInput(pStPointTo);

	// Update the map
	m_DLNodeSketch2D->Add(pStCrvLineSeg, pDLCrv);
	m_DLNodeSketch2D->Add(pStPointFrom,	 pDLPointFrom);
	m_DLNodeSketch2D->Add(pStPointTo,    pDLPointTo);

	// Create constraints
	DR_DCtSolver* pDCtSolver = NEW_OBJ(DR_DCtSolver, m_pDoc->GetFragment())(m_pDoc->GetFragment());
	ASSERT(pDCtSolver);

	pDCtSolver->AddOutput(pStPointFrom);
	pDCtSolver->AddOutput(pStPointTo);
	pDCtSolver->AddOutput(pStCrvLineSeg);

	DR_UCtPointLineSeg* pUCtPointLineSeg = NEW_OBJ(DR_UCtPointLineSeg, m_pDoc->GetFragment())(pDCtSolver, pStPointFrom, pStCrvLineSeg);
	ASSERT(pUCtPointLineSeg);

	pUCtPointLineSeg = NEW_OBJ(DR_UCtPointLineSeg, m_pDoc->GetFragment())(pDCtSolver, pStPointTo, pStCrvLineSeg);
	ASSERT(pUCtPointLineSeg);

	return hr;
}
