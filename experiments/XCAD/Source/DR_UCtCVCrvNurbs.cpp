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
#include "dr_uctcvcrvnurbs.h"
#include "dr_stcrvnurbs.h"
#include "dr_stpoint.h"

DR_UCtCVCrvNurbs::DR_UCtCVCrvNurbs(const SL_Ptr<DR_DCtSolver>&	pSolver, 
								   const SL_Ptr<DR_StPoint>&	pStCV,
								   const SL_Ptr<DR_StCrvNurbs>& pStCrvNurbs,
								   size_t nIndex)
:DR_UCtCVCrv(pSolver, pStCV, pStCrvNurbs.GetTarget(), nIndex),
m_pStCrvNurbs(pStCrvNurbs)
{
}

DR_UCtCVCrvNurbs::~DR_UCtCVCrvNurbs(void)
{
}

// Compute the output in new condition
// virtual 
HRESULT DR_UCtCVCrvNurbs::Compute()
{
	ASSERT(m_pStCrvNurbs.GetTarget());
	ASSERT(m_pStCV.GetTarget());

	HRESULT hr = S_OK;
	switch(m_eCase)
	{
	case DR_UCtCVCrv::eFixCV:
		{
			if(!m_pStCrvNurbs->SetCV(m_nIndex, m_pStCV->GetPoint()))
				hr = E_FAIL;
		}
		break;
	case DR_UCtCVCrv::eFixCrv:
		{
			MH_CV cv;
			if(!m_pStCrvNurbs->GetNurbs().GetCV(m_nIndex, cv))
				hr = E_FAIL;
			else
                m_pStCV->SetPoint(cv.GetPoint3());
		}
		break;
	default:
		break;
	}
	return hr;
}