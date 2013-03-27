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
#include "s2_crvnurbsreq.h"
#include "dr_dctsketch2d.h"
#include "dr_dctsolver.h"
#include "dr_fragment.h"
#include "dr_stcrvnurbs.h"
#include "dr_stpoint.h"
#include "dr_uctcvcrvnurbs.h"
#include "fw_document.h"
#include "gr_color.h"
#include "gr_dlcrv.h"
#include "gr_dlpoint.h"
#include "gr_dlnodesketch2d.h"
#include "sl_mm.h"

S2_CrvNurbsReq::S2_CrvNurbsReq(FW_Document* pDoc, GR_DLNodeSketch2D* pDLNodeSketch2D, const MH_CrvNurbs& crvNurbs)
:FW_RequestTxn(pDoc),
m_DLNodeSketch2D(pDLNodeSketch2D),
m_CrvNurbs(crvNurbs)
{
}

S2_CrvNurbsReq::~S2_CrvNurbsReq(void)
{
}

// Record
// virtual 
HRESULT S2_CrvNurbsReq::Script()
{
	return S_OK;
}

// Prepare the data for Replay
// virtual 
HRESULT S2_CrvNurbsReq::InitFromScript()
{
	return S_OK;
}

// virtual 
HRESULT S2_CrvNurbsReq::OnExecute()
{
	HRESULT hr = S_OK;

	MH_CrvNurbs* pCrvNurbs	= NEW_OBJ(MH_CrvNurbs, m_DLNodeSketch2D)(m_CrvNurbs);
	ASSERT(pCrvNurbs);

	// Create the DLCrv
	GR_DLCrv* pDLCrv		= NEW_OBJ(GR_DLCrv, m_DLNodeSketch2D)(m_DLNodeSketch2D, pCrvNurbs);
	ASSERT(pDLCrv);
	pDLCrv->SetColor(GR_Color(0,1.0f,0,0));

	DR_StCrvNurbs* pStCrvNurbs = NEW_OBJ(DR_StCrvNurbs, m_pDoc->GetFragment())(m_pDoc->GetFragment(), *pCrvNurbs);
	ASSERT(pStCrvNurbs);
	m_DLNodeSketch2D->GetDCtSketch2D()->AddInput(pStCrvNurbs);

	// Update the map
	m_DLNodeSketch2D->Add(pStCrvNurbs, pDLCrv);

	// Create constraints
	DR_DCtSolver* pDCtSolver = NEW_OBJ(DR_DCtSolver, m_pDoc->GetFragment())(m_pDoc->GetFragment());
	ASSERT(pDCtSolver);

	// Design:
	/*
		
		DR_DCtSolver -> DR_StCrvNurbs
					 -> DR_StPoint

			    *
				|
			    |
		DR_UCtCVCrvNurbs -> DR_StPoint
						 -> DR_StCrvNurbs

	    This is an mechanism to implement indirect constraint: 
		the control point is input, the nurbs equation is constraint, the output is the new nurbs constraint
	*/

	// Let solver know
	pDCtSolver->AddOutput(pStCrvNurbs);

	size_t nOrder;
	MH_CVVect vCV;
	m_CrvNurbs.GetInfo(nOrder, vCV, FloatVect());
	for(size_t i=0; i<vCV.size(); ++i)
	{
		DR_StPoint* pStCV = NEW_OBJ(DR_StPoint, pStCrvNurbs)(m_pDoc->GetFragment(), vCV[i].GetPoint3());
		ASSERT(pStCV);
		m_DLNodeSketch2D->GetDCtSketch2D()->AddInput(pStCV);

		// Let solver know
		pDCtSolver->AddOutput(pStCV);

		// Create the un-direct constraint
		DR_UCtCVCrvNurbs* pUCtCVCrv = NEW_OBJ(DR_UCtCVCrvNurbs, pStCrvNurbs)(pDCtSolver, pStCV, pStCrvNurbs, i);
		ASSERT(pUCtCVCrv);

		GR_DLPoint* pDLPoint = NEW_OBJ(GR_DLPoint, pDLCrv)(m_DLNodeSketch2D, NEW_OBJ(MH_Point3, pDLCrv)(vCV[i].GetPoint3()));
		ASSERT(pDLPoint);
		
		// Set point's size
		pDLPoint->SetSize(4);

		// Set point's size
		pDLPoint->SetColor(GR_Color(0,1.0f,0,0));

		// Update the map
		m_DLNodeSketch2D->Add(pStCV, pDLPoint);
	}

	return hr;
}
