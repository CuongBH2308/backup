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
#include "dr_dctfeaturerevolve.h"
#include "dr_result.h"
#include "dr_stwire.h"
#include "dr_stcrv.h"
#include "dr_stbody.h"
#include "dr_stbool.h"
#include "dr_streal.h"
#include "brep_body.h"
#include "brep_edge.h"
#include "brep_util.h"
#include "brep_wire.h"

DR_DCtFeatureRevolve::DR_DCtFeatureRevolve(const SL_Ptr<DR_Fragment>& pFragment,
										   const SL_Ptr<DR_StWire>& pStWire,
										   const SL_Ptr<DR_StCrv>& pStCrvAxis,
										   const SL_Ptr<DR_StBody>& pStBodyResult)
:DR_DCtFeature(pFragment),
m_pStWire(pStWire),
m_pStCrvAxis(pStCrvAxis),
m_pStBodyResult(pStBodyResult)
{
	AddInput(m_pStWire.GetTarget());
	AddInput(m_pStCrvAxis.GetTarget());
	AddOutput(m_pStBodyResult.GetTarget());
}

DR_DCtFeatureRevolve::~DR_DCtFeatureRevolve(void)
{
}

// Compute the output in new condition
// virtual 
HRESULT DR_DCtFeatureRevolve::Compute()
{
	if( !m_pStWire.GetTarget()	|| 
		!m_pStCrvAxis.GetTarget()/*		||
		!m_pStBoolSolid.GetTarget()		||
		!m_pStRealUFrom.GetTarget()		||
		!m_pStRealUTo.GetTarget() */)
		return DR_RLT_INPUT_MISS;

	BREP_Edge* pEdge = NULL;
	HRESULT hr = BREP_Util::CreateEdge(NULL, m_pStCrvAxis->GetCrv(), NULL, NULL, pEdge);
	if(FAILED(hr))
		return hr;

	BREP_Body* pBody = NULL;
	hr = BREP_Util::BuildRevolve(m_pStWire->GetWire().GetTarget(), pEdge, pBody);
	if(SUCCEEDED(hr))
		m_pStBodyResult->SetBody(pBody);

	//pBody->Dump("body.txt");
	hr = BREP_Util::DeleteEntity(pEdge);
	return hr;


//	BREP_Util::BuildRevolveBody(m_pStWire.GetTarget(), m_pStCrvAxis)
//	MH_Point3 pt;
//	MH_CrvPtrVect vCrv;
//	MH_Point3	ptOrigin;
//	MH_CrvArc*	pCrvArc = NULL;
//	BREP_Edge edgeAxis(reinterpret_cast<BREP_CoEdge*>(0));
//
//	// Get combined body according to wire set
//	BREP_Body* pBody = NULL;
//	HRESULT hr = m_pStSetBodyWire->GetBody(pBody);
//	if(FAILED(hr) || !pBody)
//	{
//        hr = DR_RLT_INPUT_MISS;
//		goto wrapup;
//	}
//
//	// Get line
//	const MH_CrvLine& crvLine = m_pStCrvLine->GetLine();
//
//	// Get radius and the cross-point
//	float fRadius = (float)sqrt(pBody->GetPoint().DistanceTo2(crvLine, ptOrigin));
//
////	edgeAxis.SetCrv(m_pStCrvLine->GetLine().Copy());
//
//	BREP_Body* pBodyRevolve = NULL;
//	hr = BREP_Util::BuildRevolve(pBody->GetWires().front().GetTarget(), &edgeAxis, pBodyRevolve);
//	if(FAILED(hr))
//		goto wrapup;	
//	m_pStBodyResult->SetBody(pBodyRevolve);
//
//wrapup:
//	if(pCrvArc)
//		delete pCrvArc;
//	if(pBody)
//		BREP_Util::DeleteBody(pBody);
//	if(pBodyRevolve)
//		BREP_Util::DeleteBody(pBodyRevolve);

	return S_OK;
}