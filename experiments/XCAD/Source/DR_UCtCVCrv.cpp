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
#include "dr_uctcvcrv.h"
#include "dr_st.h"
#include "dr_stpoint.h"
#include "dr_stcrv.h"

DR_UCtCVCrv::DR_UCtCVCrv(const SL_Ptr<DR_DCtSolver>& pSolver, 
						 const SL_Ptr<DR_StPoint>&	pStCV,
						 const SL_Ptr<DR_StCrv>& pStCrv,
						 size_t nIndex)
:DR_UCt(pSolver),
m_pStCV(pStCV),
m_pStCrv(pStCrv),
m_nIndex(nIndex)
{
	AddOutput(m_pStCV.GetTarget());
	AddOutput(m_pStCrv.GetTarget());
}

DR_UCtCVCrv::~DR_UCtCVCrv(void)
{
}

// Get DR_UCtCVCrv according to DR_StPoint
// static
DR_UCtCVCrvPtrVect DR_UCtCVCrv::GetUCtCVCrvs(const SL_Ptr<DR_St>& pSt)
{
	DR_UCtCVCrvPtrVect vUCtCVCrv;
	const DR_CtPtrVect& vInput = pSt->GetInputs();
	DR_CtPtrVect::const_iterator it = vInput.begin();
	DR_CtPtrVect::const_iterator itEnd = vInput.end();
	for(; it!=itEnd; ++it)
	{
		DR_UCtCVCrv* pUCtCVCrv = dynamic_cast<DR_UCtCVCrv*>((*it).GetTarget());
		if(pUCtCVCrv)
			vUCtCVCrv.push_back(pUCtCVCrv);
	}
	return vUCtCVCrv;
}

// Set case to all UCtCVCrv
// static 
void DR_UCtCVCrv::SetCase(const DR_UCtCVCrvPtrVect& vUCtCVCrv, const DR_UCtCVCrv::ECase& eCase)
{
	DR_UCtCVCrvPtrVect::const_iterator it = vUCtCVCrv.begin();
	DR_UCtCVCrvPtrVect::const_iterator itEnd = vUCtCVCrv.end();
	for(; it!=itEnd; ++it)
		(*it)->SetCase(eCase);
}

// Compute all UCtCVCrv
// static
HRESULT DR_UCtCVCrv::ComputeAll(const DR_UCtCVCrvPtrVect& vUCtCVCrv)
{
	HRESULT hr = S_OK;
	DR_UCtCVCrvPtrVect::const_iterator it = vUCtCVCrv.begin();
	DR_UCtCVCrvPtrVect::const_iterator itEnd = vUCtCVCrv.end();
	for(; it!=itEnd; ++it)
	{
		hr = (*it)->Compute();
		if(FAILED(hr))
			return hr;
	}

	return hr;
}

// Set the case
void DR_UCtCVCrv::SetCase(const DR_UCtCVCrv::ECase& eCase)
{
	m_eCase = eCase;
}

// Get m_eCase
const DR_UCtCVCrv::ECase& DR_UCtCVCrv::GetCase() const
{
	return m_eCase;
}

// Get m_nIndex
size_t DR_UCtCVCrv::GetIndex() const
{
	return m_nIndex;
}

// Get m_pStCV
const SL_Ptr<DR_StPoint>& DR_UCtCVCrv::GetStPoint() const
{
	return m_pStCV;
}
