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
#include "s2_crvbezierreq.h"
#include "dr_dctsketch2d.h"
#include "dr_dctsolver.h"
#include "dr_fragment.h"
#include "dr_stcrvnurbs.h"
#include "dr_stpoint.h"
#include "fw_document.h"
#include "gr_color.h"
#include "gr_dlcrv.h"
#include "gr_dlpoint.h"
#include "gr_dlnodesketch2d.h"
#include "sl_mm.h"

S2_CrvBezierReq::S2_CrvBezierReq(FW_Document* pDoc, GR_DLNodeSketch2D* pDLNodeSketch2D, const MH_CrvBezier& crvBezier)
:FW_RequestTxn(pDoc),
m_DLNodeSketch2D(pDLNodeSketch2D),
m_CrvBezier(crvBezier)
{
}

S2_CrvBezierReq::~S2_CrvBezierReq(void)
{
}

// Record
// virtual 
HRESULT S2_CrvBezierReq::Script()
{
	return S_OK;
}

// Prepare the data for Replay
// virtual 
HRESULT S2_CrvBezierReq::InitFromScript()
{
	return S_OK;
}

// virtual 
HRESULT S2_CrvBezierReq::OnExecute()
{
	HRESULT hr = S_OK;

	MH_CrvBezier* pCrvBezier= NEW_OBJ(MH_CrvBezier, m_DLNodeSketch2D)(m_CrvBezier);
	ASSERT(pCrvBezier);

	// Create the DLCrv
	GR_DLCrv* pDLCrv		= NEW_OBJ(GR_DLCrv, m_DLNodeSketch2D)(m_DLNodeSketch2D, pCrvBezier);
	ASSERT(pDLCrv);
	pDLCrv->SetColor(GR_Color(0,1.0f,0,0));

	//DR_StCrvNurbs* pStCrvNurbs = NEW_OBJ(DR_StCrvNurbs, m_pDoc->GetFragment())(m_pDoc->GetFragment(), *pCrvNurbs);
	//ASSERT(pStCrvNurbs);
	//m_DLNodeSketch2D->GetDCtSketch2D()->AddInput(pStCrvNurbs);

	//// Update the map
	//m_DLNodeSketch2D->Add(pStCrvNurbs, pDLCrv);

	return hr;
}
