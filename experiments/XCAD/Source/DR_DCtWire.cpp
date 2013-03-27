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
#include "dr_dctwire.h"
#include "dr_stcrv.h"
#include "dr_stpoint.h"
#include "dr_stwire.h"
#include "brep_wire.h"
#include "brep_util.h"
#include "mh_crv.h"

DR_DCtWire::DR_DCtWire(const SL_Ptr<DR_Fragment>& pFragment,
					   const DR_StCrvPtrVect& vCrv,
					   const DR_StPointPtrVect& vPt,
					   const SL_Ptr<DR_StWire>& pStWire)
:DR_DCt(pFragment),
m_vCrv(vCrv),
m_vPt(vPt),
m_pStWire(pStWire)
{
	DR_StCrvPtrVect::const_iterator itCrv		= m_vCrv.begin();
	DR_StCrvPtrVect::const_iterator itCrvEnd	= m_vCrv.end();
	for(; itCrv!=itCrvEnd; ++itCrv)
		AddInput((*itCrv).GetTarget());

	DR_StPointPtrVect::const_iterator itPt		= m_vPt.begin();
	DR_StPointPtrVect::const_iterator itPtEnd	= m_vPt.end();
	for(; itPt!=itPtEnd; ++itPt)
		AddInput((*itPt).GetTarget());

	AddOutput(m_pStWire.GetTarget());
}

DR_DCtWire::~DR_DCtWire(void)
{
}

// Compute the output in new condition
// virtual
HRESULT DR_DCtWire::Compute()
{
	HRESULT hr = S_OK;
	MH_CrvPtrVect vCrv;
	MH_Point3Vect vPt;

	DR_StCrvPtrVect::const_iterator itCrv		= m_vCrv.begin();
	DR_StCrvPtrVect::const_iterator itCrvEnd	= m_vCrv.end();
	for(; itCrv!=itCrvEnd; ++itCrv)
		vCrv.push_back((*itCrv)->GetCrv());

	DR_StPointPtrVect::const_iterator itPt		= m_vPt.begin();
	DR_StPointPtrVect::const_iterator itPtEnd	= m_vPt.end();
	for(; itPt!=itPtEnd; ++itPt)
		vPt.push_back((*itPt)->GetPoint());

	if(m_pStWire->GetWire().GetTarget())
	{
		hr = BREP_Util::DeleteEntity(m_pStWire->GetWire().GetTarget());
		ASSERT(SUCCEEDED(hr));
		if(FAILED(hr))
			return hr;
	}

	BREP_Wire* pWire = NULL;
	hr = BREP_Util::BuildWire(vCrv, vPt, pWire);
	if(SUCCEEDED(hr))
		m_pStWire->SetWire(pWire);

	return hr;
}